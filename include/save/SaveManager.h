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
    [[nodiscard]] Save::Region getRegion() const;
    void setRegion(Save::Region);
    static void setLanguage(Save::Language);
    [[nodiscard]] static Save::Language getLanguage();
    static void setLife(std::int16_t);
    static void setGold(std::uint32_t);
    static void setItem(Save::Item, std::uint8_t);
    static void setSpawn(std::int16_t);
    static void setWhiteJewel(std::uint16_t);

    static void setTimesSaved(std::uint32_t);
    static void setDeathCount(std::uint32_t);
    static void setGoldRenon(std::uint32_t);

    static void setHourVamp(std::uint16_t);
    static void setHealthDepletionRate(std::uint16_t);
    static void setWeek(std::int16_t);
    static void setDay(std::int16_t);
    static void setHour(std::int16_t);

    static void setMinutes(std::int16_t);
    static void setSeconds(std::int16_t);

    static void setMilliseconds(std::uint16_t);

    static void setFrameCount(std::uint32_t);
    [[nodiscard]] static std::uint32_t getFrameCount();
    static void setCharacter(Save::PlayerCharacter);
    static void setButtonConfig(std::int16_t);
    static void setSoundMode(std::int16_t);
    static void setSubweapon(Save::Subweapon);
    static void setMap(Save::Map);
    [[nodiscard]] static std::uint32_t getFlags();
    static void setFlags(std::uint32_t);
    static void unsetFlags(std::uint32_t);

    static void setEventFlags(std::int32_t, std::uint32_t);
    [[nodiscard]] static std::uint32_t getPlayerStatus();

    static void setPlayerStatus(std::uint32_t status);
    static void unsetPlayerStatus(std::uint32_t status);
    static void assignEventFlags(std::int32_t, std::uint32_t);
    static void unassignEventFlags(std::int32_t, std::uint32_t);
    static std::uint32_t calcFirstChecksum(const QByteArray&);
    static std::uint32_t calcSecondChecksum(const QByteArray&);
    [[nodiscard]] bool areAllSavesDisabled() const;

    Save::Slot& getSaveSlot(const std::int32_t index) {
        return m_saves[index];
    }

    Save::Slot& getCurrentSaveSlot() {
        return m_saves[m_currentSave];
    }

    Save::Data& getSave(const std::int32_t index, const bool isMain) {
        return (isMain) ? getSaveSlot(index).mainSave : getSaveSlot(index).beginningOfStage;
    }

    Save::Data& getCurrentSave() {
        return (m_isMain) ? getSaveSlot(m_currentSave).mainSave : getSaveSlot(m_currentSave).beginningOfStage;
    }

    Save::Slot* getAllSaves() {
        return m_saves;
    }

    void setSaveSlot(const Save::Slot& save, const std::int32_t index) {
        m_saves[index] = save;
    }

    void clear();
    void assignDefaultValues();

private:
    static SaveManager* m_instance;

    // Constructors and destructor
    SaveManager() {}
    ~SaveManager() = default;

    Save::Slot m_saves[Save::NUM_SAVES];
    Save::Region m_region = Save::Region::USA;
};

#endif
