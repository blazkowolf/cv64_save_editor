/**
 * @file FileManager.cpp
 * @brief FileManager source code file
 *
 * This source code file contains the code for the FileManager singleton.
 *
 * @author 
 */

#include "file/FileManager.h"
#include "save/SaveManager.h"
#include "windows/ControllerPakSelectionWindow.h"
#include <QMessageBox>

/**
 * @brief Given the loaded file format extension, it assigns the appropiate file-handling class.
 */
std::int32_t FileManager::determineFormat() {
    if (!m_filepath.isEmpty()) {

        if (m_loader != nullptr) {
            delete m_loader;
            m_loader = nullptr;
        }

        QFileInfo fileInfo(m_filepath);

        QString fileExtension = fileInfo.suffix();

        if (fileExtension == "note") {
            m_loader = new FileLoaderNote();
            m_format = FORMAT_NOTE;
        }
        else if (fileExtension == "eep") {
            m_loader = new FileLoaderCartridge();
            m_format = FORMAT_CARTRIDGE;
        }
        else if (fileExtension == "mpk" || fileExtension == "pak") {
            m_loader = new FileLoaderControllerPak();
            m_format = FORMAT_CONTROLLERPAK;
        }
        else if (fileExtension == "n64" || fileExtension == "t64") {
            m_loader = new FileLoaderDexDrive();
            m_format = FORMAT_DEXDRIVE;
        }
        else {
            // Unsupported file
            return -1;
        }

        return 0;
    }

    return -1;
}

std::int32_t FileManager::openFile(const QString& filepath) {
    if (!filepath.isEmpty()) {
        setFilePath(filepath);

        if (determineFormat() == -1)  {
            return -1;
        }

        m_file = new QFile(m_filepath);

        if (m_file->open(QIODevice::ReadOnly)) {
            // First, write to the buffer
            QDataStream inputStream(m_file);

            QByteArray fileData = m_file->readAll();
            *m_buffer = m_file->readAll();
            m_buffer->resize(fileData.size());
            *m_buffer = fileData;

            // Then, parse the contents of the file
            if (m_loader != nullptr) {
                if (m_loader->checkFileOpenErrors() != 0) {
                    return -1;
                }

                // Initialize Controller Pak specific data
                if (m_format == FORMAT_CONTROLLERPAK || m_format == FORMAT_DEXDRIVE) {
                    std::uint32_t numCV64Saves = initNoteTableData(*m_file);

                    // Stop opening the file if the Controller Pak doesn't have any Castlevania saves
                    // previously stored on it
                    if (numCV64Saves == 0) {
                        m_buffer->clear();
                        m_buffer->resize(0);
                        m_file->close();

                        QMessageBox::critical(nullptr, "Error", "This file doesn't have any active, valid saves.");
                        return -1;
                    }

                    // Open the selection window with the gathered Castlevania 64 saves
                    ControllerPakSelectionWindow* PakSaveSelectWindow = new ControllerPakSelectionWindow();
                    std::int32_t result = PakSaveSelectWindow->exec();

                    // Return early if the user clicked on the X instead of on a button
                    if (result == QDialog::Rejected) {
                        m_buffer->clear();
                        m_buffer->resize(0);
                        m_file->close();
                        return -2;
                    }
                }

                // Actually parse the contents from the file
                m_loader->parseRegion(*m_file);
                m_loader->readAllSaveSlots(*m_file);

                if (m_fileOpened == false) {
                    m_fileOpened = true;
                }
            }
        }
        else {
            return -1;
        }

        m_file->close();
    }

    return 0;
}

std::int32_t FileManager::writeFile(const QString& filepath, bool isReplacingOldFile) {
    if (SaveManager::getInstance()->areAllSavesDisabled()) {
        return -2;
    }

    if (!filepath.isEmpty()) {
        setFilePath(filepath);

        if (determineFormat() == -1)  {
            return -1;
        }

        m_file = new QFile(m_filepath);

        if (m_file->open(QIODevice::ReadWrite)) {
            if (isReplacingOldFile) {
                // If we're replacing a file (i.e. when using the "Save As..." feature),
                // ensure that we clear the file before proceeding.
                m_file->resize(0);
            }
            else {
                // Copy the contents of the file buffer containing the previously unsaved data.
                // Then, overwrite with the new data.
                m_file->write(*m_buffer);
            }

            if (m_loader != nullptr) {
                m_loader->writeAllSaveSlots(*m_file);
            }
        }
        else {
            return -1;
        }

        m_file->close();

        return 0;
    }

    return -1;
}

/**
 * @brief Initialize the FileManager's "noteTableArray", in order to know extra information regarding each Castlevania 64 save it has in Controller Pak-formatted files.
 */
std::uint32_t FileManager::initNoteTableData(QFile& file) {
    std::uint32_t numCV64Saves = 0;

    if (m_loader != nullptr && (m_format == FORMAT_CONTROLLERPAK || m_format == FORMAT_DEXDRIVE)) {
        SaveManager* saveManager = SaveManager::getInstance();
        QDataStream inputStream(&file);
        std::vector<ControllerPak::NoteTableData>* noteTableArray = FileManager::getInstance()->getControllerPakNoteTableDataArray();

        // If opening another Controller Pak file, make sure to clear the index data array first
        clearNoteTableData();

        /**
         * Find the note table data (by searching the game ID, like "ND3EA4").
         * If found, it means a Castlevania 64 save is in the Controller Pak, so we can proceed to initialize the note table data.
         */
        for (std::int32_t i = 0; i < m_loader->getNoteTableNumEntries(); i++) {
            const std::uint32_t GAMEID_SIZE = 6;
            QByteArray gameId(GAMEID_SIZE, '\0');

            inputStream.device()->seek(m_loader->getNoteTableOffset() + (m_loader->getNoteTableEntrySize() * i));   // This is where the current entry data starts
            std::uint32_t bytesRead = inputStream.readRawData(gameId.data(), GAMEID_SIZE);
            inputStream.device()->seek(m_loader->getNoteTableOffset() + (m_loader->getNoteTableEntrySize() * i));   // Go back to where we were previously to reading gameId

            if (bytesRead != GAMEID_SIZE) {
                return 0;
            }

            // If the game save stored doesn't belong to any of the Castlevania 64 versions, skip to the next save
            if (gameId != "ND3EA4" && gameId != "ND3PA4" && gameId != "ND3JA4") {
                continue;
            }

            // Get the save index within the Controller Pak data
            (*noteTableArray)[i].index = i;

            // Parse the region (at offset +3)
            std::uint8_t regionFromFile = m_loader->readData<std::uint8_t>(inputStream, inputStream.device()->pos() + 3);
            (*noteTableArray)[i].region = m_loader->getRegionEnumFromChar(regionFromFile);

            // Parse the raw data start offset (at offset +3 after the region, and then multiplied by 0x100)
            // If this is 0, we skip over this save entry (acting as if it wasn't present), and go to the next one
            std::uint32_t rawDataStartOffsetByte = m_loader->readData<std::uint8_t>(inputStream, inputStream.device()->pos() + 3);
            if (rawDataStartOffsetByte == 0) {
                (*noteTableArray)[i].clearEntry();
                numCV64Saves--;
                continue;
            }
            (*noteTableArray)[i].rawDataStartOffset = m_loader->getRawDataOffsetPerEntry(rawDataStartOffsetByte);

            numCV64Saves++;
        }
    }

    return numCV64Saves;
}
