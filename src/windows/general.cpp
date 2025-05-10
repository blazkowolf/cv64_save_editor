#include "windows/general.h"
#include "ui_general.h"
#include "save/SaveManager.h"

GeneralForm::GeneralForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralForm)
{
    ui->setupUi(this);

    // Initialize line edits
    // setupLineEditNumberUnsigned(ui->leLife, 1, 100,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setLife(value);
    //     }
    // );
    // ui->leLife->setText(QString::number(100));
    //
    // setupLineEditNumberUnsigned(ui->leGold, 0, 99999,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setGold(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leRedJewels, 0, 99,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_RED_JEWEL, value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leSpawn, 0, SHRT_MAX,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setSpawn(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leWhiteJewel, 0, USHRT_MAX,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setWhiteJewel(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leTimesSaved, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setTimesSaved(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leDeathCount, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setDeathCount(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leGoldRenon, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setGoldRenon(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leHourVamp, 0, 23,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setHourVamp(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leHealthDepletionRate, 0, SHRT_MAX,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setHealthDepletionRate(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leWeek, 0, SHRT_MAX,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setWeek(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leDay, 0, 7 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setDay(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leHour, 0, 24 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setHour(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leMinutes, 0, 60 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setMinutes(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leSeconds, 0, 60 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setSeconds(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leMilliseconds, 0, 600 - 1,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setMilliseconds(value);
    //     }
    // );
    //
    // setupLineEditNumberUnsigned(ui->leFrameCount, 0, UINT_MAX,
    //     [this](std::uint32_t value) {
    //         SaveManager::getInstance()->setFramecount(value);
    //         convertFrameToTime(SaveManager::getInstance()->getFrameCount(), ui->labelPlaytime);
    //     }
    // );
    //
    // // Initialize combo boxes and set their default values
    // ComboBoxHelper::setup<SaveData::MapID>(
    //     ui->cbMap,
    //     SaveData::MORI,
    //     {
    //         {"Forest of Silence", SaveData::MORI},
    //         {"Castle Wall (Towers)", SaveData::TOU},
    //         {"Castle Wall (Main)", SaveData::TOUOKUJI},
    //         {"Villa (Yard)", SaveData::NAKANIWA},
    //         {"Villa (Foyer)", SaveData::BEKKAN_1F},
    //         {"Villa (Hallway)", SaveData::BEKKAN_2F},
    //         {"Villa (Maze Garden)", SaveData::MEIRO_TEIEN},
    //         {"Tunnel", SaveData::CHIKA_KODO},
    //         {"Underground Waterway", SaveData::CHIKA_SUIRO},
    //         {"Castle Center (Main)", SaveData::HONMARU_B1F},
    //         {"Castle Center (Bottom Elevator)", SaveData::HONMARU_1F},
    //         {"Castle Center (Gears)", SaveData::HONMARU_2F},
    //         {"Castle Center (Friendly Lizard-man)", SaveData::HONMARU_3F_MINAMI},
    //         {"Castle Center (Library)", SaveData::HONMARU_4F_MINAMI},
    //         {"Castle Center (Nitro Room)", SaveData::HONMARU_3F_KITA},
    //         {"Castle Center (Top Elevator)", SaveData::HONMARU_5F},
    //         {"Tower of Execution", SaveData::SHOKEI_TOU},
    //         {"Tower of Sorcery", SaveData::MAHOU_TOU},
    //         {"Tower of Science", SaveData::KAGAKU_TOU},
    //         {"Duel Tower", SaveData::KETTOU_TOU},
    //         {"Castle Keep Stairs", SaveData::TURO_TOKEITOU},
    //         {"Castle Keep", SaveData::TENSHU},
    //         {"Intro Cutscene Map", SaveData::ENDING_DUMMY},
    //         {"Clock Tower", SaveData::TOKEITOU_NAI},
    //         {"Dracula Desert", SaveData::DRACULA},
    //         {"Rose / Actrice Fan Room", SaveData::ROSE},
    //         {"Villa (Vampire Crypt)", SaveData::BEKKAN_BOSS},
    //         {"Room of Clocks", SaveData::TOU_TURO},
    //         {"Ending Map", SaveData::ENDING},
    //         {"Test Grid", SaveData::TEST_GRID}
    //     },
    //     [](SaveData::MapID value) { SaveManager::getInstance()->setMap(value); }
    // );
    //
    // ComboBoxHelper::setup<SaveData::PlayerCharacterID>(
    //     ui->cbCharacter, SaveData::REINHARDT,
    //     {
    //         {"Reinhardt", SaveData::REINHARDT},
    //         {"Carrie", SaveData::CARRIE}
    //     },
    //     [](SaveData::PlayerCharacterID value) { SaveManager::getInstance()->setCharacter(value); }
    // );
    //
    // ComboBoxHelper::setup<std::int32_t>(
    //     ui->cbButtonConfig,
    //     0,
    //     {
    //         {"Type A", 0},
    //         {"Type B", 1},
    //         {"Type C", 2}
    //     },
    //     [](std::int32_t value) { SaveManager::getInstance()->setButtonConfig(value); }
    // );
    //
    // ComboBoxHelper::setup<std::int32_t>(
    //     ui->cbSoundMode,
    //     0,
    //     {
    //         {"Stereo", 0},
    //         {"Monoaural", 1}
    //     },
    //     [](std::int32_t value) { SaveManager::getInstance()->setSoundMode(value); }
    // );
    //
    // ComboBoxHelper::setup<SaveData::SubweaponID>(
    //     ui->cbSubweapon,
    //     SaveData::SUBWEAPON_NONE,
    //     {
    //         {"None", SaveData::SUBWEAPON_NONE},
    //         {"Knife", SaveData::SUBWEAPON_KNIFE},
    //         {"Holy Water", SaveData::SUBWEAPON_HOLY_WATER},
    //         {"Cross", SaveData::SUBWEAPON_CROSS},
    //         {"Axe", SaveData::SUBWEAPON_AXE},
    //         {"Wooden Stake", SaveData::SUBWEAPON_WOODEN_STAKE},
    //         {"Rose", SaveData::SUBWEAPON_ROSE}
    //     },
    //     [](SaveData::SubweaponID value) { SaveManager::getInstance()->setSubweapon(value); }
    // );
    //
    // setupComboBoxBitflag(ui->cbDifficulty, comboBoxDataDifficulty);
    // setupComboBoxBitflag(ui->cbReinhardtEnding, comboBoxDataEndingReinhardt);
    // setupComboBoxBitflag(ui->cbCarrieEnding, comboBoxDataEndingCarrie);
    //
    // ComboBoxHelper::setup<SaveData::eRegion>(
    //     ui->cbRegion,
    //     SaveData::USA,
    //     {
    //         {"USA", SaveData::USA},
    //         {"JPN", SaveData::JPN},
    //         {"PAL", SaveData::PAL}
    //     },
    //     [this](SaveData::eRegion value) {
    //         SaveManager::getInstance()->setRegion(value);
    //         switch (value) {
    //         default:
    //         case SaveData::USA:
    //             ui->cbLanguage->setEnabled(false);
    //             ui->cbLanguage->setCurrentIndex(0);
    //             ui->cbLanguage->setItemText(0, "English");
    //             ui->leItemsSpecial3->setEnabled(false);
    //             ui->leItemsPoutPourri->setEnabled(true);
    //             break;
    //
    //         case SaveData::JPN:
    //             ui->cbLanguage->setEnabled(false);
    //             ui->cbLanguage->setCurrentIndex(0);
    //             ui->cbLanguage->setItemText(0, "Japanese");
    //             ui->leItemsSpecial3->setEnabled(true);
    //             ui->leItemsPoutPourri->setEnabled(false);
    //             break;
    //
    //         case SaveData::PAL:
    //             ui->cbLanguage->setEnabled(true);
    //             ui->cbLanguage->setCurrentIndex(0);
    //             ui->cbLanguage->setItemText(0, "English");
    //             ui->leItemsSpecial3->setEnabled(true);
    //             ui->leItemsPoutPourri->setEnabled(false);
    //             break;
    //         }
    //     }
    // );
    //
    // ComboBoxHelper::setup<SaveData::eLanguage>(
    //     ui->cbLanguage,
    //     SaveData::ENGLISH,
    //     {
    //         {"English", SaveData::ENGLISH},
    //         {"German", SaveData::GERMAN},
    //         {"French", SaveData::FRENCH}
    //     },
    //     [](std::int32_t value) { SaveManager::getInstance()->setLanguage(value); }
    // );
    //
    // // Initialize cbLanguage to USA values
    // ui->cbLanguage->setEnabled(false);
    // ui->cbLanguage->setCurrentIndex(0);
    // ui->cbLanguage->setCurrentText("English");
    //
    // // Initialize pages and the buttons that travel to those pages
    // // When each button is pressed, "onPageButtonClicked" will be called passing
    // // the desired page by arguments
    // connect(ui->buttonMain, &QPushButton::clicked, this, [this]() {
    //     onPageButtonClicked(ui->stackedWidgetPages, pageGeneral);
    // });
    //
    // connect(ui->buttonItems, &QPushButton::clicked, this, [this]() {
    //     onPageButtonClicked(ui->stackedWidgetPages, pageItems);
    // });
    //
    // connect(ui->buttonEventFlags, &QPushButton::clicked, this, [this]() {
    //     onPageButtonClicked(ui->stackedWidgetPages, pageEventFlags);
    // });
    //
    // // In order to avoid the checkbox from being disabled,
    // // we ensure that its parent is MainWindow (since it's never disabled by the "enableUiComponents" function)
    // ui->cboxEnabled->setParent(this);
    // setupCheckBox(ui->cboxEnabled, SaveData::SAVE_FLAG_ACTIVE,
    //     [this](std::uint32_t value) {
    //         SaveManager::getInstance()->setFlags(value);
    //         updateWindowVisibility(true);
    //     },
    //
    //     [this](std::uint32_t value) {
    //         SaveManager::getInstance()->unsetFlags(value);
    //         updateWindowVisibility(false);
    //     }
    // );
    //
    // setupCheckBox(ui->cboxHardMode, SaveData::SAVE_FLAG_HARD_MODE_UNLOCKED,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    // );
    //
    // setupCheckBox(ui->cboxUseAlternateCostume, SaveData::SAVE_FLAG_COSTUME_IS_BEING_USED,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    // );
    //
    // setupCheckBox(ui->cboxReinhardtCostume, SaveData::SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    // );
    //
    // setupCheckBox(ui->cboxCarrieCostume, SaveData::SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    // );
    //
    // setupCheckBox(ui->cboxNitro, SaveData::SAVE_FLAG_CAN_EXPLODE_ON_JUMPING,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    // );
    //
    // setupCheckBox(ui->cboxVamp, SaveData::PLAYER_FLAG_VAMP,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setPlayerStatus(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetPlayerStatus(value); }
    // );
    //
    // setupCheckBox(ui->cboxPoison, SaveData::PLAYER_FLAG_POISON,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setPlayerStatus(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetPlayerStatus(value); }
    // );
    //
    // setupCheckBox(ui->cboxSto, SaveData::PLAYER_FLAG_STO,
    //     [](std::uint32_t value) { SaveManager::getInstance()->setPlayerStatus(value); },
    //     [](std::uint32_t value) { SaveManager::getInstance()->unsetPlayerStatus(value); }
    // );
}

GeneralForm::~GeneralForm()
{
    delete ui;
}
