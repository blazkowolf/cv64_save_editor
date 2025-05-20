/**
 * @file SaveManager.cpp
 * @brief SaveManager class source code file
 *
 * This file contains the source code for the SaveManager singleton.
 *
 * @author 
 */

#include "save/Save.h"
#include "save/SaveManager.h"

std::int16_t SaveManager::getRegion() const {
    return region;
}

void SaveManager::setRegion(const std::int16_t region_) {
    region = region_;
}

void SaveManager::setLanguage(const std::int16_t language) {
    getInstance()->getCurrentSave().language = language;
}

std::int16_t SaveManager::getLanguage() const {
    return getInstance()->getCurrentSave().language;
}

void SaveManager::setLife(const std::int16_t life) {
    getInstance()->getCurrentSave().life = life;
}

void SaveManager::setGold(const std::uint32_t gold) {
    getInstance()->getCurrentSave().gold = gold;
}

void SaveManager::setItem(const std::int32_t itemId, const std::uint8_t amount) {
    getInstance()->getCurrentSave().items[itemId - 1] = amount;
}

void SaveManager::setSpawn(const std::int16_t spawn) {
    getInstance()->getCurrentSave().spawn = spawn;
}

void SaveManager::setWhiteJewel(const std::uint16_t save_crystal_number) {
    getInstance()->getCurrentSave().save_crystal_number = save_crystal_number;
}

void SaveManager::setTimesSaved(const std::uint32_t time_saved_counter) {
    getInstance()->getCurrentSave().time_saved_counter = time_saved_counter;
}

void SaveManager::setDeathCount(const std::uint32_t death_counter) {
    getInstance()->getCurrentSave().death_counter = death_counter;
}

void SaveManager::setGoldRenon(const std::uint32_t gold_spent_on_Renon) {
    getInstance()->getCurrentSave().gold_spent_on_Renon = gold_spent_on_Renon;
}

void SaveManager::setHourVamp(const std::uint16_t current_hour_VAMP) {
    getInstance()->getCurrentSave().current_hour_VAMP = current_hour_VAMP;
}

void SaveManager::setHealthDepletionRate(const std::uint16_t health_depletion_rate_while_poisoned) {
    getInstance()->getCurrentSave().health_depletion_rate_while_poisoned = health_depletion_rate_while_poisoned;
}

void SaveManager::setWeek(const std::int16_t week) {
    getInstance()->getCurrentSave().week = week;
}

void SaveManager::setDay(const std::int16_t day) {
    getInstance()->getCurrentSave().day = day;
}

void SaveManager::setHour(const std::int16_t hour) {
    getInstance()->getCurrentSave().hour = hour;
}

void SaveManager::setMinutes(const std::int16_t minutes) {
    getInstance()->getCurrentSave().minute = minutes;
}

void SaveManager::setSeconds(const std::int16_t seconds) {
    getInstance()->getCurrentSave().seconds = seconds;
}

void SaveManager::setMilliseconds(const std::uint16_t milliseconds) {
    getInstance()->getCurrentSave().milliseconds = milliseconds;
}

void SaveManager::setFrameCount(const std::uint32_t gameplay_framecount) {
    getInstance()->getCurrentSave().gameplay_framecount = gameplay_framecount;
}

std::uint32_t SaveManager::getFrameCount() const {
    return getInstance()->getCurrentSave().gameplay_framecount;
}

void SaveManager::setCharacter(const std::int16_t character) {
    getInstance()->getCurrentSave().character = character;
}

void SaveManager::setButtonConfig(const std::int16_t button_config) {
    getInstance()->getCurrentSave().button_config = button_config;
}

void SaveManager::setSoundMode(const std::int16_t sound_mode) {
    getInstance()->getCurrentSave().sound_mode = sound_mode;
}

void SaveManager::setSubweapon(const std::int16_t subweapon) {
    getInstance()->getCurrentSave().subweapon = subweapon;
}

void SaveManager::setMap(const std::int16_t map) {
    getInstance()->getCurrentSave().map = map;
}

std::uint32_t SaveManager::getFlags() const {
    return getInstance()->getCurrentSave().flags;
}

void SaveManager::setFlags(const std::uint32_t flags) {
    BITS_SET(getInstance()->getCurrentSave().flags, flags);
}

void SaveManager::unsetFlags(const std::uint32_t flags) {
    BITS_UNSET(getInstance()->getCurrentSave().flags, flags);
}

std::uint32_t SaveManager::getPlayerStatus() const {
    return getInstance()->getCurrentSave().player_status;
}

void SaveManager::setPlayerStatus(const std::uint32_t status) {
    BITS_SET(getInstance()->getCurrentSave().player_status, status);
}

void SaveManager::unsetPlayerStatus(const std::uint32_t status) {
    BITS_UNSET(getInstance()->getCurrentSave().player_status, status);
}

/**
 * @brief Set a whole event flag word
 */
void SaveManager::setEventFlags(const std::int32_t flagSet, const std::uint32_t flags) {
    getInstance()->getCurrentSave().event_flags[flagSet] = flags;
}

/**
 * @brief Assign individual flags to an event flag word.
 */
void SaveManager::assignEventFlags(const std::int32_t flagSet, const std::uint32_t flags) {
    BITS_SET(getInstance()->getCurrentSave().event_flags[flagSet], flags);
}

/**
 * @brief Remove individual flags from an event flag word.
 */
void SaveManager::unassignEventFlags(const std::int32_t flagSet, const std::uint32_t flags) {
    BITS_UNSET(getInstance()->getCurrentSave().event_flags[flagSet], flags);
}

/**
 * @brief Calculates the save file's first checksum
 *
 * @note source: https://decomp.me/scratch/6UIVU
 */
std::uint32_t SaveManager::calcFirstChecksum(const QByteArray& dataFromFile) {
    std::uint32_t checksum = 0;

    std::uint32_t numElements = dataFromFile.size();
    const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(dataFromFile.constData());

    for (std::int32_t i = 0; i < numElements; i++) {
        checksum += data[i];
    }

    return checksum;
}

/**
 * @brief Calculates the save file's second checksum
 *
 * @note source: https://decomp.me/scratch/oi0s4
 */
std::uint32_t SaveManager::calcSecondChecksum(const QByteArray& dataFromFile) {
    std::uint32_t checksum = 0;

    std::uint32_t numElements = dataFromFile.size() / 4;
    const std::uint32_t* data = reinterpret_cast<const std::uint32_t*>(dataFromFile.constData());

    for (std::int32_t i = 0; i < numElements; i++) {
        checksum ^= data[i];
    }

    return checksum;
}

/**
 * If none of the saves are enabled, return true.
 * This allows us, for example, to prevent saving if none of the saves's "Enabled" checkbox are checked.
 */
bool SaveManager::areAllSavesDisabled() const {
    return std::all_of(std::cbegin(saves), std::cend(saves), [](const SaveSlot& save) {
        return BITS_HAS(save.mainSave.flags, Save::SAVE_FLAG_ACTIVE);
    });
    // for (const auto &save : saves) {
    //     if (BITS_HAS(save.mainSave.flags, Save::SAVE_FLAG_ACTIVE)) {
    //         return false;
    //     }
    // }
    //
    // return true;
}

/**
 * @brief Assign default (i.e. new game) values to all save game fields.
 */
void SaveManager::assignDefaultValues() {
    for (auto &save : saves) {
        save.assignDefaultValues();
    }
}

/**
 * @brief Clears all save game fields.
 */
void SaveManager::clear() {
    for (auto &save : saves) {
        save.clear();
    }
}
