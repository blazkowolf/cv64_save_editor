/**
 * @file FileLoader.cpp
 * @brief FileLoader source code file
 *
 * This source code file contains the code for the file-handling operations.
 *
 * @author 
 */

#include "file/FileLoader.h"
#include "file/FileManager.h"
#include <QDataStream>
#include <QDebug>
#include <algorithm> // std::search, std::distance
#include <cstdint>
#include <cstddef>   // offsetof

/**
 * @brief Reads the data associated to a save slot from a file given the start offset within said file.
 */
void FileLoader::readSaveSlot(QFile& file, Save::Slot& slot, const std::uint32_t startOffset) {
    QDataStream inputStream(&file);

    // Return if we reached the end of the file
    if (startOffset >= getMaxFileSize()) {
        return;
    }

    slot.mainSave = readSaveData(inputStream, startOffset);
    slot.beginningOfStage = readSaveData(inputStream, inputStream.device()->pos());
    slot.checksum1 = readData<std::uint32_t>(inputStream, inputStream.device()->pos());
    slot.checksum2 = readData<std::uint32_t>(inputStream, inputStream.device()->pos());
}

/**
 * @brief Writes the data associated from a save slot to a file at the start offset within said file.
 */
void FileLoader::writeSaveSlot(QFile& file, Save::Slot& slot, const std::uint32_t startOffset) {
    auto* saveManager = SaveManager::getInstance();
    QDataStream outputStream(&file);

    std::uint32_t firstChecksumOffset = 0;
    std::uint32_t secondChecksumOffset = 0;
    std::uint32_t saveDataSize = 0;

    if (saveManager->getRegion() == Save::Region::PAL) {
        firstChecksumOffset = offsetof(Save::Slot, checksum1);
        secondChecksumOffset = offsetof(Save::Slot, checksum2);
        saveDataSize = sizeof(Save::Data);
    } else {
        // Since the PAL version of the Save::Slot added 4 extra bytes (and this project uses the PAL definition of the struct),
        // we will remove those extra 4 bytes (plus 4 -> 8 bytes) from the offset to get the correct address to write the checksums to.
        firstChecksumOffset = offsetof(Save::Slot, checksum1) - 8;
        secondChecksumOffset = offsetof(Save::Slot, checksum2) - 8;
        saveDataSize = sizeof(Save::Data) - 4;
    }

    // Write the main and beginning of stage saves
    writeSaveData(outputStream, slot.mainSave, startOffset);
    writeSaveData(outputStream, slot.beginningOfStage, outputStream.device()->pos());

    /**
     * Write the checksums. To ensure the checksums are properly calculated,
     * we convert the data to a byte array, then swap the endianness (since the save file is stored in big endian)
     */
    auto* device = outputStream.device();
    device->seek(startOffset);
    auto rawData = device->read(saveDataSize);

    // Convert "rawData" to big-endian
    swapEndianness(&rawData);

    // Write the Save::Slot main's checksum at the specific offsets within the Save::Slot struct
    const auto firstChecksum = saveManager->calcFirstChecksum(rawData);
    const auto secondChecksum = saveManager->calcSecondChecksum(rawData);

    device->seek(startOffset + firstChecksumOffset);
    outputStream << firstChecksum;
    device->seek(startOffset + secondChecksumOffset);
    outputStream << secondChecksum;
}

/**
 * @brief Returns the region numeric ID given its equivalent character ID.
 */
Save::Region FileLoader::getRegionEnumFromChar(const std::uint8_t regionFromFile) {
    switch (regionFromFile) {
        default:
        case 'E':
            return Save::Region::USA;

        case 'J':
            return Save::Region::JPN;

        case 'P':
            return Save::Region::PAL;
    }
}

/**
 * @brief Finds the region's character ID and sets the actual region value within the program accordingly.
 */
void FileLoaderNote::parseRegion(QFile& file) {
    SaveManager* saveManager = SaveManager::getInstance();
    QDataStream inputStream(&file);

    const auto regionFromFile = readData<std::uint8_t>(inputStream, getRegionIdOffset());
    saveManager->setRegion(getRegionEnumFromChar(regionFromFile));
}

/**
 * @brief Reads an entire save from the given file. The start offset for this data depends on the file format.
 */
void FileLoader::readAllSaveSlots(QFile& file) {
    for (std::uint32_t i = 0; i < Save::NUM_SAVES; i++) {
        readSaveSlot(file, SaveManager::getInstance()->getSaveSlot(i), getRawDataOffsetStart() + (getSaveSlotPaddedSize() * i));
    }
}

/**
 * @brief Writes an entire save to the given file. The start offset for this data depends on the file format.
 */
void FileLoader::writeAllSaveSlots(QFile& file) {
    for (std::uint32_t i = 0; i < Save::NUM_SAVES; i++) {
        writeSaveSlot(file, SaveManager::getInstance()->getSaveSlot(i), getRawDataOffsetStart() + (getSaveSlotPaddedSize() * i));
    }
}

/**
 * @brief Reads a save data entry from the given data stream. The start offset for this data depends on the file format.
 */
const Save::Data& FileLoader::readSaveData(QDataStream& inputStream, const std::uint32_t startOffset) {
    auto* currentSave = new Save::Data();

    // Seek to the start of the save data
    inputStream.device()->seek(startOffset);

    // Read save data contents into "currentSave"
    for (auto &flag : currentSave->event_flags) {
        flag = readData<std::uint32_t>(inputStream, inputStream.device()->pos());
    }
    currentSave->flags = readData<std::uint32_t>(inputStream, inputStream.device()->pos());

    currentSave->week = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->day = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->hour = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->minute = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->seconds = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->milliseconds = readData<std::uint16_t>(inputStream, inputStream.device()->pos());
    currentSave->gameplay_framecount = readData<std::uint32_t>(inputStream, inputStream.device()->pos());

    currentSave->button_config = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->sound_mode = readData<std::int16_t>(inputStream, inputStream.device()->pos());

    // PAL-exclusive data
    if (SaveManager::getInstance()->getRegion() == Save::Region::PAL) {
        currentSave->language = readData<Save::Language>(inputStream, inputStream.device()->pos());
        currentSave->padding5A_PAL = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    }

    currentSave->character = readData<Save::PlayerCharacter>(inputStream, inputStream.device()->pos());
    currentSave->life = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->field_0x5C = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->subweapon = readData<Save::Subweapon>(inputStream, inputStream.device()->pos());
    currentSave->gold = readData<std::uint32_t>(inputStream, inputStream.device()->pos());

    for (auto &item : currentSave->items) {
        item = readData<std::uint8_t>(inputStream, inputStream.device()->pos());
    }

    currentSave->player_status = readData<std::uint32_t>(inputStream, inputStream.device()->pos());
    currentSave->health_depletion_rate_while_poisoned = readData<std::int16_t>(inputStream, inputStream.device()->pos());

    currentSave->current_hour_VAMP = readData<std::uint16_t>(inputStream, inputStream.device()->pos());
    currentSave->map = readData<Save::Map>(inputStream, inputStream.device()->pos());
    currentSave->spawn = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->save_crystal_number = readData<std::uint16_t>(inputStream, inputStream.device()->pos());

    currentSave->field51_0xb2 = readData<std::uint8_t>(inputStream, inputStream.device()->pos());
    currentSave->field52_0xb3 = readData<std::uint8_t>(inputStream, inputStream.device()->pos());

    currentSave->time_saved_counter = readData<std::uint32_t>(inputStream, inputStream.device()->pos());
    currentSave->death_counter = readData<std::uint32_t>(inputStream, inputStream.device()->pos());

    currentSave->field55_0xbc = readData<std::int32_t>(inputStream, inputStream.device()->pos());
    currentSave->field59_0xc0 = readData<std::int32_t>(inputStream, inputStream.device()->pos());
    currentSave->field63_0xc4 = readData<std::int32_t>(inputStream, inputStream.device()->pos());
    currentSave->field67_0xc8 = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->field69_0xca = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->field71_0xcc = readData<std::int32_t>(inputStream, inputStream.device()->pos());
    currentSave->field75_0xd0 = readData<std::int32_t>(inputStream, inputStream.device()->pos());
    currentSave->field77_0xd2 = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->field79_0xd4 = readData<std::int16_t>(inputStream, inputStream.device()->pos());
    currentSave->field83_0xd8 = readData<std::int32_t>(inputStream, inputStream.device()->pos());
    currentSave->gold_spent_on_Renon = readData<std::uint32_t>(inputStream, inputStream.device()->pos());

    return *currentSave;
}

/**
 * @brief Writes a save data entry to the given data stream. The start offset for this data depends on the file format.
 */
void FileLoader::writeSaveData(QDataStream& outputStream, const Save::Data& saveData, const std::uint32_t startOffset) {
    outputStream.device()->seek(startOffset);

    for (const auto flag : saveData.event_flags) {
        writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), flag);
    }

    writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), saveData.flags);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.week);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.day);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.hour);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.minute);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.seconds);
    writeData<std::uint16_t>(outputStream, outputStream.device()->pos(), saveData.milliseconds);
    writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), saveData.gameplay_framecount);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.button_config);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.sound_mode);

    // PAL-related saves
    if (SaveManager::getInstance()->getRegion() == Save::Region::PAL) {
        writeData<Save::Language>(outputStream, outputStream.device()->pos(), saveData.language);
        writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.padding5A_PAL);
    }

    writeData<Save::PlayerCharacter>(outputStream, outputStream.device()->pos(), saveData.character);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.life);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.field_0x5C);
    writeData<Save::Subweapon>(outputStream, outputStream.device()->pos(), saveData.subweapon);
    writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), saveData.gold);

    for (const auto item : saveData.items) {
        writeData<std::uint8_t>(outputStream, outputStream.device()->pos(), item);
    }

    writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), saveData.player_status);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.health_depletion_rate_while_poisoned);
    writeData<std::uint16_t>(outputStream, outputStream.device()->pos(), saveData.current_hour_VAMP);
    writeData<Save::Map>(outputStream, outputStream.device()->pos(), saveData.map);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.spawn);
    writeData<std::uint16_t>(outputStream, outputStream.device()->pos(), saveData.save_crystal_number);
    writeData<std::uint8_t>(outputStream, outputStream.device()->pos(), saveData.field51_0xb2);
    writeData<std::uint8_t>(outputStream, outputStream.device()->pos(), saveData.field52_0xb3);
    writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), saveData.time_saved_counter);
    writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), saveData.death_counter);
    writeData<std::int32_t>(outputStream, outputStream.device()->pos(), saveData.field55_0xbc);
    writeData<std::int32_t>(outputStream, outputStream.device()->pos(), saveData.field59_0xc0);
    writeData<std::int32_t>(outputStream, outputStream.device()->pos(), saveData.field63_0xc4);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.field67_0xc8);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.field69_0xca);
    writeData<std::int32_t>(outputStream, outputStream.device()->pos(), saveData.field71_0xcc);
    writeData<std::int32_t>(outputStream, outputStream.device()->pos(), saveData.field75_0xd0);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.field77_0xd2);
    writeData<std::int16_t>(outputStream, outputStream.device()->pos(), saveData.field79_0xd4);
    writeData<std::int32_t>(outputStream, outputStream.device()->pos(), saveData.field83_0xd8);
    writeData<std::uint32_t>(outputStream, outputStream.device()->pos(), saveData.gold_spent_on_Renon);
}

/**
 * @brief Get the raw header bytes for Note-formatted files.
 *
 * @note source: https://github.com/bryc/mpkedit/wiki/Note-file-formats
 * @note This implements the format last updated on Sep 29, 2023.
 */
std::vector<std::uint8_t> FileLoaderNote::getHeaderBytes() const {
    switch (SaveManager::getInstance()->getRegion()) {
        case Save::Region::USA:
            return {
                0x01, 0x4D, 0x50, 0x4B, 0x4E, 0x6F, 0x74, 0x65, 0x00, 0x00, 0x00, 0x67,
                0x89, 0x7E, 0x56, 0x00, 0x4E, 0x44, 0x33, 0x45, 0x41, 0x34, 0xCA, 0xFE,
                0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1A, 0x2C, 0x2D,
                0x25, 0x1E, 0x2F, 0x1A, 0x27, 0x22, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00
            };

        case Save::Region::JPN:
            return {
                0x01, 0x4D, 0x50, 0x4B, 0x4E, 0x6F, 0x74, 0x65, 0x00, 0x00, 0x00, 0x67,
                0x89, 0x7E, 0x56, 0x00, 0x4E, 0x44, 0x33, 0x4A, 0x41, 0x34, 0xCA, 0xFE,
                0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1A, 0x2C, 0x2D,
                0x25, 0x1E, 0x2F, 0x1A, 0x27, 0x22, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00
            };

        case Save::Region::PAL:
            return {
                0x01, 0x4D, 0x50, 0x4B, 0x4E, 0x6F, 0x74, 0x65, 0x00, 0x00, 0x00, 0x67,
                0x89, 0x7E, 0x56, 0x00, 0x4E, 0x44, 0x33, 0x50, 0x41, 0x34, 0xCA, 0xFE,
                0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1A, 0x2C, 0x2D,
                0x25, 0x1E, 0x2F, 0x1A, 0x27, 0x22, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00
            };
    }

    return {};
}

/**
 * @note Cartridge saves are exclusive to the Japanese version.
 */
void FileLoaderCartridge::parseRegion(QFile& file) {
    SaveManager::getInstance()->setRegion(Save::Region::JPN);
}

std::vector<std::uint8_t> FileLoaderCartridge::getHeaderBytes() const {
    return {
        0x4B, 0x43, 0x45, 0x4B, 0x20, 0x46, 0x6F, 0x72, 0x6D, 0x61, 0x74, 0x20, 0x31, 0x32, 0x30, 0x39
    };
}

/**
 * @brief Get the raw save slot size + its padding.
 */
std::uint32_t FileLoaderNote::getSaveSlotPaddedSize() const {
    return sizeof(Save::Slot) + (getSavePaddedSize() - sizeof(Save::Slot));
}

/**
 * @note Always 0x900 bytes in practice.
 */
std::uint32_t FileLoaderNote::getMaxFileSize() const {
    const std::uint32_t headerSize = getHeaderBytes().size();
    const std::uint32_t maxFileSize = headerSize + (getSaveSlotPaddedSize() * Save::NUM_SAVES) + getUnusedExtraSize();

    return maxFileSize;
};

bool FileLoader::searchHexInFile(const QByteArray& data, const std::vector<std::uint8_t>& target) {
    if (data.isEmpty() || target.empty()) {
        return false;
    }

    // Convert QByteArray to std::vector<std::uint8_t>
    std::vector<std::uint8_t> fileContents(data.begin(), data.end());

    // Search for the target sequence
    const auto it = std::search(fileContents.begin(), fileContents.end(), target.begin(), target.end());

    return it != fileContents.end(); // True if found, false otherwise
}

std::uint32_t FileLoaderNote::countHexOccurrences(const QByteArray& data, const std::vector<std::uint8_t>& target) const {
    if (data.isEmpty() || target.empty()) {
        return 0;
    }

    // Convert QByteArray to std::vector<std::uint8_t>
    std::vector<std::uint8_t> fileContents(data.begin(), data.end());

    std::int32_t count = 0;
    auto it = fileContents.begin();

    // Search for all occurrences
    while (searchHexInFile(data, target)) {
        ++count;
        // Move past this occurrence
        it += getSaveSlotPaddedSize();

        // Break if the iterator reaches or exceeds the end of the buffer
        if (std::distance(fileContents.begin(), it) >= fileContents.size()) {
            break;
        }
    }

    return count;
}

std::uint32_t FileLoaderCartridge::countHexOccurrences(const QByteArray& data, const std::vector<std::uint8_t>& target) const {
    if (data.isEmpty() || target.empty()) {
        return 0;
    }

    // Convert QByteArray to std::vector<std::uint8_t>
    std::vector<std::uint8_t> fileContents(data.begin(), data.end());

    std::int32_t count = 0;
    auto it = fileContents.begin();

    // Search for all occurrences
    while (searchHexInFile(data, target)) {
        ++count;
        // Move past this occurrence
        it += getSaveSlotPaddedSize();

        // Break if the iterator reaches or exceeds the end of the buffer
        if (std::distance(fileContents.begin(), it) >= fileContents.size()) {
            break;
        }
    }

    return count;
}

std::uint32_t FileLoaderControllerPak::countHexOccurrences(const QByteArray& data, const std::vector<std::uint8_t>& target) const {
    if (data.isEmpty() || target.empty()) {
        return 0;
    }

    // Convert QByteArray to std::vector<std::uint8_t>
    std::vector<std::uint8_t> fileContents(data.begin(), data.end());

    std::int32_t count = 0;
    auto it = fileContents.begin();

    // Search for all occurrences
    while (searchHexInFile(data, target)) {
        ++count;
        // Move past this occurrence
        it += getSaveSlotPaddedSize();

        // Break if the iterator reaches or exceeds the end of the buffer
        if (std::distance(fileContents.begin(), it) >= fileContents.size()) {
            break;
        }
    }

    return count;
}

/**
 * @brief Given a cartridge save (which has dynamic size), return the number of saves it currently has.
 */
std::uint32_t FileLoaderCartridge::getCartridgeNumSaves() const {
    // We search the number of times the cartridge header data has been found, which is equal to the number of saves the file has
    return countHexOccurrences(FileManager::getInstance()->getBuffer(), getHeaderBytes());
}

std::uint32_t FileLoaderCartridge::getSaveSlotPaddedSize() const {
    const std::uint32_t headerSize = getHeaderBytes().size();

    // The complete save slot ends at offset 0x1F0, not 0x200, so we remove -0x10 bytes from it.
    // Besides, each slot now starts with the header data.
    return headerSize + (sizeof(Save::Slot) + (getSavePaddedSize() - sizeof(Save::Slot))) - 0x10;
}

/**
 * @note Cartridge saves have variable size.
 */
std::uint32_t FileLoaderCartridge::getMaxFileSize() const {
    const std::uint32_t maxFileSize = getSaveSlotPaddedSize() * getCartridgeNumSaves();

    return maxFileSize;
};

void FileLoaderControllerPak::parseRegion(QFile& file) {
    const auto* noteTableArray = FileManager::getInstance()->getControllerPakNoteTableDataArray();

    // Set the region of the currently selected Controller Pak save
    SaveManager::getInstance()->setRegion((*noteTableArray)[FileManager::getInstance()->getControllerPakCurrentlySelectedSaveIndex()].region);
}

std::uint32_t FileLoaderControllerPak::getRawDataOffsetStart() const {
    // We obtain the raw data offset start from the note table data.
    const auto* noteTableArray = FileManager::getInstance()->getControllerPakNoteTableDataArray();
    return (*noteTableArray)[FileManager::getInstance()->getControllerPakCurrentlySelectedSaveIndex()].rawDataStartOffset;
}

std::uint32_t FileLoaderControllerPak::getSaveSlotPaddedSize() const {
    return sizeof(Save::Slot) + (getSavePaddedSize() - sizeof(Save::Slot));
}

/**
 * @note Always 0x8000 bytes
 */
std::uint32_t FileLoaderControllerPak::getMaxFileSize() const {
    return 0x8000;
};

/**
 * @note In DexDrive saves, the Controller Pak data actually starts at 0x1040.
 */
std::uint32_t FileLoaderDexDrive::getMaxFileSize() const {
    return 0x8000 + 0x1040;
};

/**
 * @brief Given an byte array, it swaps the endianness between little endian<->big endian
 */
void FileLoader::swapEndianness(QByteArray* rawData) {
    if (!rawData || rawData->size() < 4) {
        return;
    }

    char* data = rawData->data();
    std::int32_t dataSize = rawData->size();

    for (std::int32_t i = 0; i + 3 < dataSize; i += 4) {
        std::swap(data[i], data[i + 3]);
        std::swap(data[i + 1], data[i + 2]);
    }
}

void FileLoaderCartridge::writeAllSaveSlots(QFile& file) {
    file.seek(0);

    for (std::uint32_t i = 0; i < Save::NUM_SAVES; i++) {
        // First, write the header, then the saveslot data
        std::vector<std::uint8_t> headerBytes = getHeaderBytes();

        if (!headerBytes.empty()) {
            file.write(reinterpret_cast<const char*>(headerBytes.data()), headerBytes.size());
        }

        writeSaveSlot(file, SaveManager::getInstance()->getSaveSlot(i), getRawDataOffsetStart() + (getSaveSlotPaddedSize() * i));

        // Add padding bytes at the end of each saveslot
        std::vector<std::uint8_t> paddingBytes(getSaveSlotPaddingBytesSize(), 0);
        file.write(reinterpret_cast<const char*>(paddingBytes.data()), paddingBytes.size());
    }
}

void FileLoaderNote::writeAllSaveSlots(QFile& file) {
    file.seek(0);

    // First, write the header, then the saveslot data
    std::vector<std::uint8_t> headerBytes = getHeaderBytes();
    if (!headerBytes.empty()) {
        file.write(reinterpret_cast<const char*>(headerBytes.data()), headerBytes.size());
    }

    for (std::uint32_t i = 0; i < Save::NUM_SAVES; i++) {
        writeSaveSlot(file, SaveManager::getInstance()->getSaveSlot(i), getRawDataOffsetStart() + (getSaveSlotPaddedSize() * i));

        // Add padding bytes at the end of each saveslot
        std::vector<std::uint8_t> paddingSlotBytes(getSaveSlotPaddingBytesSize(), 0);
        file.write(reinterpret_cast<const char*>(paddingSlotBytes.data()), paddingSlotBytes.size());
    }

    // Add padding bytes at the end of the whole file
    std::vector<std::uint8_t> paddingBytes(getUnusedExtraSize(), 0);
    file.write(reinterpret_cast<const char*>(paddingBytes.data()), paddingBytes.size());
}

/**
 * @brief Get the size of the padding data after the end of the actual save slot data.
 */
std::uint32_t FileLoaderNote::getSaveSlotPaddingBytesSize() const {
    std::uint32_t paddingBytes = getSavePaddedSize() - sizeof(Save::Slot);

    switch (SaveManager::getInstance()->getRegion()) {
        case Save::Region::USA:
        case Save::Region::JPN:
        default:
            // Add the extra 8 bytes found in the PAL version of the saveslot
            return paddingBytes + 8;

        case Save::Region::PAL:
            return paddingBytes;
    }
}

/**
 * @brief Get the size of the padding data after the end of the actual save slot data.
 */
std::uint32_t FileLoaderCartridge::getSaveSlotPaddingBytesSize() const {
    const auto region = SaveManager::getInstance()->getRegion();

    // Remove the extra 8 bytes found in the PAL version of the saveslot
    // (when applicable)
    const std::uint32_t extraByteData = (region == Save::Region::PAL) ? 0 : 8;
    const std::uint32_t paddingBytes = getSavePaddedSize() - (sizeof(Save::Slot) - extraByteData) - getHeaderBytes().size();

    return paddingBytes;
}

std::int32_t FileLoaderNote::checkFileOpenErrors() {
    FileManager* fileManager = FileManager::getInstance();

    // Ensure the file has the predefined size (0x900 bytes in practice)
    if (fileManager->getFile().size() != getMaxFileSize()) {
        return -1;
    }

    return 0;
}

std::int32_t FileLoaderCartridge::checkFileOpenErrors() {
    FileManager* fileManager = FileManager::getInstance();

    // Ensure the file has the predefined size (0x900 bytes in practice),
    // + that there's at least one valid save on it.
    if (fileManager->getFile().size() != getMaxFileSize() ||
        getCartridgeNumSaves() == 0) {
        return -1;
    }

    return 0;
}

std::int32_t FileLoaderControllerPak::checkFileOpenErrors() {
    FileManager* fileManager = FileManager::getInstance();

    // Ensure the file has the predefined size (0x900 bytes in practice)
    if (fileManager->getFile().size() != getMaxFileSize()) {
        return -1;
    }

    return 0;
}
