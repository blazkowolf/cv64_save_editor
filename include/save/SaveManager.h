#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

/**
 * @file SaveManager.h
 * @brief SaveManager header file
 *
 * @author 
 */

#include "Save.h"
#include <cstdint>

#include <QFile>
#include <QtEndian>

/**
 * @class SaveManager
 * @brief SaveManager singleton class definition
 *
 * This singleton handles save-related operations.
 */
class SaveManager {
    public:
        SaveManager(const SaveManager& obj) = delete; // Remove the copy constructor

        // Singleton-related functions
        static SaveManager* getInstance() {
            if (m_instance == nullptr) {
                createInstance();
            }

            return m_instance;
        }

        static void createInstance() {
            m_instance = new SaveManager();
        }

        static void destroyInstance() {
            delete m_instance;
            m_instance = nullptr;
        }

        std::int32_t m_currentSave = 0;
        bool m_isMain = true;

        // Getters, setters and helper functions
        void parseRegion(QFile& file);
        [[nodiscard]] std::int16_t getRegion() const;
        void setRegion(std::int16_t);
        void setLanguage(std::int16_t);
        [[nodiscard]] std::int16_t getLanguage() const;
        void setLife(std::int16_t);
        void setGold(std::uint32_t);
        void setItem(std::int32_t, std::uint8_t);
        void setSpawn(std::int16_t);
        void setWhiteJewel(std::uint16_t);
        void setTimesSaved(std::uint32_t);
        void setDeathCount(std::uint32_t);
        void setGoldRenon(std::uint32_t);
        void setHourVamp(std::uint16_t);
        void setHealthDepletionRate(std::uint16_t);
        void setWeek(std::int16_t);
        void setDay(std::int16_t);
        void setHour(std::int16_t);
        void setMinutes(std::int16_t);
        void setSeconds(std::int16_t);
        void setMilliseconds(std::uint16_t);
        void setFrameCount(std::uint32_t);
        [[nodiscard]] std::uint32_t getFrameCount() const;
        void setCharacter(std::int16_t);
        void setButtonConfig(std::int16_t);
        void setSoundMode(std::int16_t);
        void setSubweapon(std::int16_t);
        void setMap(std::int16_t);
        [[nodiscard]] std::uint32_t getFlags() const;
        void setFlags(std::uint32_t);
        void unsetFlags(std::uint32_t);
        void setEventFlags(std::int32_t, std::uint32_t);
        [[nodiscard]] std::uint32_t getPlayerStatus() const;
        void setPlayerStatus(std::uint32_t status);
        void unsetPlayerStatus(std::uint32_t status);
        void assignEventFlags(std::int32_t, std::uint32_t);
        void unassignEventFlags(std::int32_t, std::uint32_t);
        std::uint32_t calcFirstChecksum(const QByteArray&);
        std::uint32_t calcSecondChecksum(const QByteArray&);
        [[nodiscard]] bool areAllSavesDisabled() const;

        SaveSlot& getSaveSlot(const std::int32_t index) {
            return saves[index];
        }

        SaveSlot& getCurrentSaveSlot() {
            return saves[m_currentSave];
        }

        SaveData& getSave(const std::int32_t index, const bool isMain) {
            return (isMain) ? getSaveSlot(index).mainSave : getSaveSlot(index).beginningOfStage;
        }

        SaveData& getCurrentSave() {
            return (m_isMain) ? getSaveSlot(m_currentSave).mainSave : getSaveSlot(m_currentSave).beginningOfStage;
        }

        SaveSlot* getAllSaves() {
            return saves;
        }

        void setSaveSlot(const SaveSlot& save, const std::int32_t index) {
            saves[index] = save;
        }

        void clear();
        void assignDefaultValues();

    private:
        static SaveManager* m_instance;

        // Constructors and destructor
        SaveManager() {}
        ~SaveManager() = default;

        SaveSlot saves[Save::NUM_SAVES];
        std::int16_t region = SaveData::USA;
};

#endif
