#ifndef FILELOADER_H
#define FILELOADER_H

/**
 * @file FileLoader.h
 * @brief FileLoader header file
 *
 * @author 
 */

#include "save/Save.h"
#include "save/SaveManager.h"
#include <cstdint>
#include <vector>

/**
 * @class FileLoader
 * @brief FileLoader abstract class
 *
 * This abstract class contains the default implementation for the FileLoader data structure,
 * which is in charge of all file-related operations (opening files, closing them, parsing them, etc).
 */
class FileLoader {
    /// @note All of these offsets are relative to the very beginning of the file.
    const std::uint32_t rawDataStartOffset = 0;  /**< Offset where the binary SaveData starts within the file */
    const std::uint32_t regionIdOffset = 0;      /**< Offset where region identification is stored at */
    const std::uint32_t maxFileSize = 0;         /**< Maximum allowed size for the file format we're currently handling */

    public:
        // Constructors and destructor
        FileLoader() {}
        virtual ~FileLoader() {}

        // Main file read and write functions
        virtual void parseRegion(QFile& file) = 0;
        void readAllSaveSlots(QFile& file);
        virtual void writeAllSaveSlots(QFile& file);
        void readSaveSlot(QFile& file, SaveSlot& slot, std::uint32_t startOffset);
        void writeSaveSlot(QFile& file, SaveSlot& slot, std::uint32_t startOffset);
        const SaveData& readSaveData(QDataStream& inputStream, std::uint32_t startOffset);
        void writeSaveData(QDataStream& outputStream, const SaveData& saveData, std::uint32_t startOffset);

        // Search-related functions
        // Search occurences of an array of bytes in a QByteArray, and count its occurences, respectively.
        static bool searchHexInFile(const QByteArray& data, const std::vector<std::uint8_t>& target);
        virtual std::uint32_t countHexOccurrences(const QByteArray& data, const std::vector<std::uint8_t>& target) const = 0;

        // Getter functions related to file-handling tasks
        virtual std::uint32_t getRawDataOffsetStart() const { return rawDataStartOffset; }
        virtual std::uint32_t getRegionIdOffset() const { return regionIdOffset; }
        virtual std::uint32_t getMaxFileSize() const { return 0; }
        virtual std::uint32_t getUnusedExtraSize() const { return 0; }
        virtual std::uint32_t getSaveSlotPaddedSize() const = 0;
        virtual std::uint32_t getSaveSlotPaddingBytesSize() const { return 0; }
        virtual std::uint32_t getSavePaddedSize() const { return 0x200; }

        /**
         * @brief getHeaderBytes
         * Get the raw bytes associated to the file's header, when applicable.
         */
        virtual std::vector<std::uint8_t> getHeaderBytes() const = 0;
        virtual std::uint32_t getNoteTableOffset() const { return 0; }
        virtual std::uint32_t getNoteTableEntrySize() const { return 0; }
        virtual std::uint32_t getNoteTableNumEntries() const { return 0; }

        /**
         * @brief getRawDataOffsetPerEntry
         *
         * Given a single raw data offset byte, it calculates the actual offset where the save
         * can be found relative to the start of the whole binary file
         *
         * For example, for Controller Paks, if the raw data byte is associated to a given save is 0x05,
         * then the actual offset where the raw data for that save starts is at 0x05 * 0x100 = 0x500
         */
        virtual std::uint32_t getRawDataOffsetPerEntry(std::uint32_t rawDataStartOffsetByte) const { return 0; }

        void swapEndianness(QByteArray*);

        std::int16_t getRegionEnumFromChar(const std::uint8_t regionFromFile);

        /**
         * Reads a value of type T at the given offset within the input stream's raw data.
         */
        template<typename T>
        T readData(QDataStream& inputStream, long offset) {
            inputStream.device()->seek(offset);

            T value;
            inputStream.readRawData(reinterpret_cast<char*>(&value), sizeof(T));

            return qFromBigEndian(value);
        }

        /**
         * Writes a value of type T at the given offset within the input stream's raw data.
         */
        template<typename T>
        void writeData(QDataStream& outputStream, long offset, T value) {
            outputStream.device()->seek(offset);

            T bigEndianValue = qToBigEndian(value);
            outputStream.writeRawData(reinterpret_cast<char*>(&bigEndianValue), sizeof(T));
        }

        /**
         * Error verification when opening a file.
         *
         * @return -1 on fail. 0 on success.
         */
        virtual std::int32_t checkFileOpenErrors() = 0;
};

/**
 * @class FileLoaderNote
 * @brief FileLoaderNote class
 *
 * This class handles reading and writing .note files (individual notes from a Controller Pak)
 */
class FileLoaderNote: public FileLoader {
    /// @note The raw data starts right after the header,
    /// hence why we just get the size of the header bytes
    const std::uint32_t rawDataStartOffset = getHeaderBytes().size();
    const std::uint32_t regionIdOffset = 0x13;

    public:
        // Constructors and destructor
        FileLoaderNote() {}
        ~FileLoaderNote() {}

        // Main file read and write functions
        void parseRegion(QFile& file);
        void writeAllSaveSlots(QFile& file);

        // Getter functions related to file-handling tasks
        std::uint32_t countHexOccurrences(const QByteArray& data, const std::vector<std::uint8_t>& target) const;
        std::uint32_t getRawDataOffsetStart() const { return rawDataStartOffset; }
        std::uint32_t getRegionIdOffset() const { return regionIdOffset; }
        std::uint32_t getMaxFileSize() const;
        std::uint32_t getUnusedExtraSize() const { return 0x100; }  // Unused extra 100 bytes at the end of notes
        std::uint32_t getSaveSlotPaddedSize() const;
        std::vector<std::uint8_t> getHeaderBytes() const;
        std::uint32_t getSaveSlotPaddingBytesSize() const;
        std::int32_t checkFileOpenErrors();
};

/**
 * @class FileLoaderCartridge
 * @brief FileLoaderCartridge class
 *
 * This class handles reading and writing .eep files
 * (save files embedded in the cartridge, only found in the Japanese version of the game)
 */
class FileLoaderCartridge: public FileLoader {
    /// @note The raw data starts right after the header,
    /// hence why we just get the size of the header bytes
    const std::uint32_t rawDataStartOffset = getHeaderBytes().size();
    const std::uint32_t regionIdOffset = 0;  /// @note Not needed for cartridge saves

    public:
        // Constructors and destructor
        FileLoaderCartridge() {}
        ~FileLoaderCartridge() {}

        // Main file read and write functions
        void parseRegion(QFile& file);
        void writeAllSaveSlots(QFile& file);

        // Getter functions related to file-handling tasks
        std::uint32_t countHexOccurrences(const QByteArray& data, const std::vector<std::uint8_t>& target) const;
        std::uint32_t getRawDataOffsetStart() const { return rawDataStartOffset; }
        std::uint32_t getRegionIdOffset() const { return 0; }   // Not needed for cartridge saves, so we return 0
        std::uint32_t getMaxFileSize() const;
        std::uint32_t getUnusedExtraSize() const { return 0; }
        std::uint32_t getSaveSlotPaddedSize() const;
        std::vector<std::uint8_t> getHeaderBytes() const;
        std::uint32_t getCartridgeNumSaves() const;
        std::uint32_t getSaveSlotPaddingBytesSize() const;
        std::int32_t checkFileOpenErrors();
};

/**
 * @class FileLoaderControllerPak
 * @brief FileLoaderControllerPak class
 *
 * This class handles reading and writing .mpk / .pak files (Controller Pak containers).
 *
 * The "note table" referenced below is a table that contains metadata for each save, including
 * the start offset of the raw data associated to each save, its region, etc.
 */
struct FileLoaderControllerPak: public FileLoader {
    const std::uint32_t CONTROLLER_PAK_NOTE_TABLE_OFFSET = 0x300;    /**< Offset where the note table starts */
    const std::uint32_t CONTROLLER_PAK_NOTE_TABLE_ENTRY_SIZE = 0x20; /**< Size of each entry in the note table */
    const std::uint32_t CONTROLLER_PAK_NOTE_TABLE_NUM_ENTRIES = 16;  /**< Total number of elements in the note table */

    public:
        // Constructors and destructor
        FileLoaderControllerPak() {}
        ~FileLoaderControllerPak() {}

        // Main file read and write functions
        void parseRegion(QFile& file);

        // Getter functions related to file-handling tasks
        std::uint32_t countHexOccurrences(const QByteArray& data, const std::vector<std::uint8_t>& target) const;
        std::uint32_t getRawDataOffsetStart() const;
        std::uint32_t getRegionIdOffset() const { return 0; }
        std::uint32_t getMaxFileSize() const;
        std::uint32_t getUnusedExtraSize() const { return 0x100; }  // Unused extra 100 bytes at the end of notes
        std::uint32_t getSaveSlotPaddedSize() const;
        std::vector<std::uint8_t> getHeaderBytes() const { return {}; }
        std::uint32_t getNoteTableOffset() const { return CONTROLLER_PAK_NOTE_TABLE_OFFSET; }
        std::uint32_t getNoteTableEntrySize() const { return CONTROLLER_PAK_NOTE_TABLE_ENTRY_SIZE; }
        std::uint32_t getNoteTableNumEntries() const { return CONTROLLER_PAK_NOTE_TABLE_NUM_ENTRIES; }
        std::uint32_t getRawDataOffsetPerEntry(std::uint32_t rawDataStartOffsetByte) const { return rawDataStartOffsetByte * 0x100; }
        std::int32_t checkFileOpenErrors();
};

/**
 * @class FileLoaderDexDrive
 * @brief FileLoaderDexDrive class
 *
 * This class handles reading and writing .t64 / .n64 files
 * (Controller Pak containers in the DexDrive format. This is why it inherits from FileLoaderControllerPak)
 *
 * @note In DexDrive saves, the Controller Pak data actually starts at 0x1040, which is why
 * there are various 0x1040 constants in the code for this class.
 */
struct FileLoaderDexDrive: public FileLoaderControllerPak {
    const std::uint32_t CONTROLLER_PAK_NOTE_TABLE_OFFSET = 0x300 + 0x1040;
    const std::uint32_t CONTROLLER_PAK_NOTE_TABLE_ENTRY_SIZE = 0x20;
    const std::uint32_t CONTROLLER_PAK_NOTE_TABLE_NUM_ENTRIES = 16;

    public:
        // Constructors and destructor
        FileLoaderDexDrive() {}
        ~FileLoaderDexDrive() {}

        // Getter functions related to file-handling tasks
        std::uint32_t getMaxFileSize() const;
        std::uint32_t getNoteTableOffset() const { return CONTROLLER_PAK_NOTE_TABLE_OFFSET; }
        std::uint32_t getNoteTableEntrySize() const { return CONTROLLER_PAK_NOTE_TABLE_ENTRY_SIZE; }
        std::uint32_t getNoteTableNumEntries() const { return CONTROLLER_PAK_NOTE_TABLE_NUM_ENTRIES; }
        std::uint32_t getRawDataOffsetPerEntry(std::uint32_t rawDataStartOffsetByte) const { return (rawDataStartOffsetByte * 0x100) + 0x1040; }
};

#endif
