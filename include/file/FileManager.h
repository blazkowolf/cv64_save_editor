#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/**
 * @file FileManager.h
 * @brief FileManager header file
 *
 * @author 
 */

#include "save/Save.h"
#include "file/FileLoader.h"
#include <QFile>
#include <QtEndian>
#include <QFileInfo>

namespace ControllerPak {

/**
 * Helper struct that contains variables needed for identifying
 * individual saves inside Controller Pak-formatted files.
 */
struct NoteTableData {
    std::int32_t index = -1;
    Save::Region region = Save::Region::USA;
    std::uint32_t rawDataStartOffset = 0;

    NoteTableData() { clearEntry(); }

    void clearEntry() {
        index = -1;
        region = Save::Region::USA;
        rawDataStartOffset = 0;
    }
};

constexpr std::uint32_t NOTE_TABLE_ENTRY_SIZE = 0x20;  /**< Size of each entry in the note table */
constexpr std::uint32_t NOTE_TABLE_NUM_ENTRIES = 16;   /**< Total number of elements in the note table */

}

/**
 * @class FileManager
 * @brief FileManager singleton class definition
 *
 * This singleton handles file-related operations.
 * This class is a wrapper for file tasks. The specific operations are handled
 * by the pre-assigned file parser (see the "loader" member variable).
 */
class FileManager {
    public:
        /**
         * @brief The file format of the opened file
         */
        enum eFormat {
            FORMAT_NOTE,                  // .note
            FORMAT_CONTROLLERPAK,         // .pak, .mpk
            FORMAT_CARTRIDGE,             // .eep
            FORMAT_DEXDRIVE               // .n64, .t64
        };


        // Singleton-related functions
        static FileManager* getInstance() {
            if (m_instance == nullptr) {
                createInstance();
            }

            return m_instance;
        }

        static void createInstance() {
            m_instance = new FileManager();
        }

        static void destroyInstance() {
            delete m_instance;
            m_instance = nullptr;
        }

        // Inline getters and setters
        [[nodiscard]] std::int32_t getFileFormat() const {
            return m_format;
        }

        void setFileFormat(const std::int32_t format) {
            m_format = format;
        }

        QString& getFilepath() {
            return m_filepath;
        }

        void setFilePath(const QString& filepath) {
            m_filepath = filepath;
        }

        [[nodiscard]] QFile& getFile() const {
            return *m_file;
        }

        [[nodiscard]] QByteArray& getBuffer() const {
            return *m_buffer;
        }

        [[nodiscard]] FileLoader* getLoader() const {
            return m_loader;
        }

        [[nodiscard]] std::int32_t getControllerPakCurrentlySelectedSaveIndex() const {
            return m_controllerPakCurrentlySelectedSaveIndex;
        }

        void setControllerPakCurrentlySelectedSaveIndex(const std::int32_t controllerPakCurrentlySelectedSaveIndex) {
            m_controllerPakCurrentlySelectedSaveIndex = controllerPakCurrentlySelectedSaveIndex;
        }

        std::vector<ControllerPak::NoteTableData>* getControllerPakNoteTableDataArray() {
            return &m_noteTableArray;
        }

        [[nodiscard]] bool wasFileOpened() const {
            return m_fileOpened;
        }

        void setFileOpened(const bool fileOpened_) {
            m_fileOpened = fileOpened_;
        }

        // Functions for the main file operations
        std::int32_t openFile(const QString& filepath);
        std::int32_t writeFile(const QString& filepath, bool isReplacingOldFile);

        // Functions or handling the note table data array
        std::uint32_t initNoteTableData(QFile& file);

        void clearNoteTableData() {
            for (auto &i : m_noteTableArray) {
                i.clearEntry();
            }
        }

    private:
        static FileManager* m_instance;

        // Constructors and destructor
        FileManager()
            : m_buffer(new QByteArray)
            , m_filepath("")
        {
        }

        ~FileManager() {
            if (m_file != nullptr) {
                m_file->close();

                delete m_file;
                m_file = nullptr;
            }

            if (m_loader != nullptr) {
                delete m_loader;
                m_loader = nullptr;
            }

            if (m_buffer != nullptr) {
                delete m_buffer;
                m_buffer = nullptr;
            }
        }

        FileManager(const FileManager& obj) = delete; // Remove the copy constructor
        std::int32_t determineFormat();

        std::int32_t m_format = FORMAT_NOTE;                           /**< File format */
        std::int32_t m_controllerPakCurrentlySelectedSaveIndex = 0;    /**< The index of the currently selected save in a loaded Controller Pak */

        QFile* m_file = nullptr;                              /**< Currently-opened file */
        QByteArray* m_buffer = nullptr;                       /**< File buffer containing the raw bytes for the currently-opened file */
        QString m_filepath;                                   /**< File path of the currently-opened file */
        FileLoader* m_loader = nullptr;                       /**< File format */
        /**< A file was opened at least once. Used for knowing if we have to enable or disable the Save buttons */
        bool m_fileOpened = false;

        /**
         * An array of "ControllerPak::NoteTableData". This is use on Controller Pak-specific formats to
         * store all the entries in the note table that contain Castlevania 64 saves.
         */
        std::vector<ControllerPak::NoteTableData> m_noteTableArray{ControllerPak::NOTE_TABLE_NUM_ENTRIES};
};

#endif
