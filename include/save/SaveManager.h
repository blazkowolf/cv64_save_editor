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
        // Singleton-related functions
        static SaveManager* getInstance() {
            if (instance == nullptr) {
                createInstance();
            }

            return instance;
        }

        static void createInstance() {
            instance = new SaveManager();
        }

        static void destroyInstance() {
            delete instance;
            instance = nullptr;
        }

        std::int32_t currentSave = 0;
        bool isMain = true;

        // Getters, setters and helper functions
        void parseRegion(QFile& file);
        std::int16_t getRegion() const;
        void setRegion(const std::int16_t);
        void setLanguage(const std::int16_t);
        std::int16_t getLanguage() const;
        void setLife(const std::int16_t);
        void setGold(const std::uint32_t);
        void setItem(const std::int32_t, const std::uint8_t);
        void setSpawn(const std::int16_t);
        void setWhiteJewel(const std::uint16_t);
        void setTimesSaved(const std::uint32_t);
        void setDeathCount(const std::uint32_t);
        void setGoldRenon(const std::uint32_t);
        void setHourVamp(const std::uint16_t);
        void setHealthDepletionRate(const std::uint16_t);
        void setWeek(const std::int16_t);
        void setDay(const std::int16_t);
        void setHour(const std::int16_t);
        void setMinutes(const std::int16_t);
        void setSeconds(const std::int16_t);
        void setMilliseconds(const std::uint16_t);
        void setFramecount(const std::uint32_t);
        std::uint32_t getFrameCount() const;
        void setCharacter(const std::int16_t);
        void setButtonConfig(const std::int16_t);
        void setSoundMode(const std::int16_t);
        void setSubweapon(const std::int16_t);
        void setMap(const std::int16_t);
        std::uint32_t getFlags() const;
        void setFlags(const std::uint32_t);
        void unsetFlags(const std::uint32_t);
        void setEventFlags(const std::int32_t, const std::uint32_t);
        std::uint32_t getPlayerStatus() const;
        void setPlayerStatus(const std::uint32_t status);
        void unsetPlayerStatus(const std::uint32_t status);
        void assignEventFlags(const std::int32_t, const std::uint32_t);
        void unassignEventFlags(const std::int32_t, const std::uint32_t);
        std::uint32_t calcFirstChecksum(const QByteArray&);
        std::uint32_t calcSecondChecksum(const QByteArray&);
        bool areAllSavesDisabled();

        SaveSlot& getSaveSlot(const std::int32_t index) {
            return saves[index];
        }

        SaveSlot& getCurrentSaveSlot() {
            return saves[currentSave];
        }

        SaveData& getSave(const std::int32_t index, const bool isMain) {
            return (isMain) ? getSaveSlot(index).mainSave : getSaveSlot(index).beginningOfStage;
        }

        SaveData& getCurrentSave() {
            return (isMain) ? getSaveSlot(currentSave).mainSave : getSaveSlot(currentSave).beginningOfStage;
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
        static SaveManager* instance;

        // Constructors and destructor
        SaveManager() {}
        ~SaveManager() {}
        SaveManager(const SaveManager& obj) = delete; // Remove the copy constructor

        SaveSlot saves[NUM_SAVES];
        std::int16_t region = SaveData::USA;
};

#endif
