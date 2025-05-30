#include "windows/general.h"

#include "util/checkbox.h"
#include "util/combobox.h"
#include "util/lineedit.h"
#include "ui_general.h"
#include "save/SaveManager.h"

GeneralForm::GeneralForm(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::GeneralForm)
{
    m_ui->setupUi(this);
}

GeneralForm::~GeneralForm()
{
    delete m_ui;
}

void convertFrameToTime(const std::uint32_t frameCount, QLabel* output) {
    const std::int32_t totalSeconds = frameCount / 30;
    const std::int32_t hours = totalSeconds / 3600;
    const std::int32_t minutes = (totalSeconds % 3600) / 60;
    const std::int32_t seconds = totalSeconds % 60;
    output->setText(
        QString("%1:%2:%3")
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'))
    );
}

void GeneralForm::setup()
{
    const QRegularExpression acceptDecimalAndHexRegex(R"(^(\d{1,8}|0[xX][0-9A-Fa-f]{1,8})$)");
    const auto *validator = new QRegularExpressionValidator(acceptDecimalAndHexRegex, this);
    // Initialize line edits
    // LineEditHelper::setup(ui->leLife, 1, 100,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setLife(value);
    //     }
    // );
    // ui->leLife->setText(QString::number(100));
    LineEdit::setup(m_ui->leLife, QString::number(100), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 1, 100);
        m_ui->leLife->setText(QString::number(value));
        SaveManager::setLife(value);
    });

    // LineEditHelper::setup(ui->leGold, 0, 99999,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setGold(value);
    //     }
    // );
    LineEdit::setup(m_ui->leGold, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint32_t>(text, 0, 99999);
        m_ui->leGold->setText(QString::number(value));
        SaveManager::setGold(value);
    });

    // LineEditHelper::setup(ui->leRedJewels, 0, 99,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Data::ITEM_ID_RED_JEWEL, value);
    //     }
    // );
    LineEdit::setup(m_ui->leRedJewels, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 99);
        m_ui->leRedJewels->setText(QString::number(value));
        SaveManager::setItem(Save::Item::RED_JEWEL, value);
    });

    // LineEditHelper::setup(ui->leSpawn, 0, SHRT_MAX,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setSpawn(value);
    //     }
    // );
    LineEdit::setup(m_ui->leSpawn, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, SHRT_MAX);
        m_ui->leSpawn->setText(QString::number(value));
        SaveManager::setSpawn(value);
    });

    // LineEditHelper::setup(ui->leWhiteJewel, 0, USHRT_MAX,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setWhiteJewel(value);
    //     }
    // );
    LineEdit::setup(m_ui->leWhiteJewel, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, USHRT_MAX);
        m_ui->leWhiteJewel->setText(QString::number(value));
        SaveManager::setWhiteJewel(value);
    });

    // LineEditHelper::setup(ui->leTimesSaved, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setTimesSaved(value);
    //     }
    // );
    LineEdit::setup(m_ui->leTimesSaved, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leTimesSaved->setText(QString::number(value));
        SaveManager::setTimesSaved(value);
    });

    // LineEditHelper::setup(ui->leDeathCount, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setDeathCount(value);
    //     }
    // );
    LineEdit::setup(m_ui->leDeathCount, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leDeathCount->setText(QString::number(value));
        SaveManager::setDeathCount(value);
    });

    // LineEditHelper::setup(ui->leGoldRenon, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setGoldRenon(value);
    //     }
    // );
    LineEdit::setup(m_ui->leGoldRenon, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leGoldRenon->setText(QString::number(value));
        SaveManager::setGoldRenon(value);
    });

    // LineEditHelper::setup(ui->leHourVamp, 0, 23,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setHourVamp(value);
    //     }
    // );
    LineEdit::setup(m_ui->leHourVamp, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, 23);
        m_ui->leHourVamp->setText(QString::number(value));
        SaveManager::setHourVamp(value);
    });

    // LineEditHelper::setup(ui->leHealthDepletionRate, 0, SHRT_MAX,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setHealthDepletionRate(value);
    //     }
    // );
    LineEdit::setup(m_ui->leHealthDepletionRate, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, SHRT_MAX);
        m_ui->leHealthDepletionRate->setText(QString::number(value));
        SaveManager::setHealthDepletionRate(value);
    });

    // LineEditHelper::setup(ui->leWeek, 0, SHRT_MAX,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setWeek(value);
    //     }
    // );
    LineEdit::setup(m_ui->leWeek, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, SHRT_MAX);
        m_ui->leWeek->setText(QString::number(value));
        SaveManager::setWeek(value);
    });

    // LineEditHelper::setup(ui->leDay, 0, 7 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setDay(value);
    //     }
    // );
    LineEdit::setup(m_ui->leDay, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, 7 - 1);
        m_ui->leDay->setText(QString::number(value));
        SaveManager::setDay(value);
    });

    // LineEditHelper::setup(ui->leHour, 0, 24 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setHour(value);
    //     }
    // );
    LineEdit::setup(m_ui->leHour, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, 24 - 1);
        m_ui->leHour->setText(QString::number(value));
        SaveManager::setHour(value);
    });

    // LineEditHelper::setup(ui->leMinutes, 0, 60 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setMinutes(value);
    //     }
    // );
    LineEdit::setup(m_ui->leMinutes, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, 60 - 1);
        m_ui->leMinutes->setText(QString::number(value));
        SaveManager::setMinutes(value);
    });

    // LineEditHelper::setup(ui->leSeconds, 0, 60 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setSeconds(value);
    //     }
    // );
    LineEdit::setup(m_ui->leSeconds, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, 60 - 1);
        m_ui->leSeconds->setText(QString::number(value));
        SaveManager::setSeconds(value);
    });

    // LineEditHelper::setup(ui->leMilliseconds, 0, 600 - 1,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setMilliseconds(value);
    //     }
    // );
    LineEdit::setup(m_ui->leMilliseconds, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEdit::handleUnsignedInteger<std::uint16_t>(text, 0, 600 - 1);
        m_ui->leMilliseconds->setText(QString::number(value));
        SaveManager::setMilliseconds(value);
    });

    // LineEditHelper::setup(ui->leFrameCount, 0, UINT_MAX,
    //     [this](std::uint32_t value) {
    //         SaveManager::getInstance()->setFramecount(value);
    //         convertFrameToTime(SaveManager::getInstance()->getFrameCount(), ui->labelPlaytime);
    //     }
    // );
    LineEdit::setup(m_ui->leFrameCount, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leFrameCount->setText(QString::number(value));
        SaveManager::setFrameCount(value);
        convertFrameToTime(SaveManager::getFrameCount(), m_ui->labelPlaytime);
    });

    // Initialize combo boxes and set their default values
    ComboBox::setup<Save::Map>(
        m_ui->cbMap,
        Save::Map::MORI,
        {
            {"Forest of Silence", Save::Map::MORI},
            {"Castle Wall (Towers)", Save::Map::TOU},
            {"Castle Wall (Main)", Save::Map::TOUOKUJI},
            {"Villa (Yard)", Save::Map::NAKANIWA},
            {"Villa (Foyer)", Save::Map::BEKKAN_1F},
            {"Villa (Hallway)", Save::Map::BEKKAN_2F},
            {"Villa (Maze Garden)", Save::Map::MEIRO_TEIEN},
            {"Tunnel", Save::Map::CHIKA_KODO},
            {"Underground Waterway", Save::Map::CHIKA_SUIRO},
            {"Castle Center (Main)", Save::Map::HONMARU_B1F},
            {"Castle Center (Bottom Elevator)", Save::Map::HONMARU_1F},
            {"Castle Center (Gears)", Save::Map::HONMARU_2F},
            {"Castle Center (Friendly Lizard-man)", Save::Map::HONMARU_3F_MINAMI},
            {"Castle Center (Library)", Save::Map::HONMARU_4F_MINAMI},
            {"Castle Center (Nitro Room)", Save::Map::HONMARU_3F_KITA},
            {"Castle Center (Top Elevator)", Save::Map::HONMARU_5F},
            {"Tower of Execution", Save::Map::SHOKEI_TOU},
            {"Tower of Sorcery", Save::Map::MAHOU_TOU},
            {"Tower of Science", Save::Map::KAGAKU_TOU},
            {"Duel Tower", Save::Map::KETTOU_TOU},
            {"Castle Keep Stairs", Save::Map::TURO_TOKEITOU},
            {"Castle Keep", Save::Map::TENSHU},
            {"Intro Cutscene Map", Save::Map::ENDING_DUMMY},
            {"Clock Tower", Save::Map::TOKEITOU_NAI},
            {"Dracula Desert", Save::Map::DRACULA},
            {"Rose / Actrice Fan Room", Save::Map::ROSE},
            {"Villa (Vampire Crypt)", Save::Map::BEKKAN_BOSS},
            {"Room of Clocks", Save::Map::TOU_TURO},
            {"Ending Map", Save::Map::ENDING},
            {"Test Grid", Save::Map::TEST_GRID}
        },
        [](Save::Map value) { SaveManager::setMap(value); }
    );

    ComboBox::setup<Save::PlayerCharacter>(
        m_ui->cbCharacter, Save::PlayerCharacter::REINHARDT,
        {
            {"Reinhardt", Save::PlayerCharacter::REINHARDT},
            {"Carrie", Save::PlayerCharacter::CARRIE}
        },
        [](Save::PlayerCharacter value) { SaveManager::setCharacter(value); }
    );

    ComboBox::setup<std::int32_t>(
        m_ui->cbButtonConfig,
        0,
        {
            {"Type A", 0},
            {"Type B", 1},
            {"Type C", 2}
        },
        [](std::int32_t value) { SaveManager::setButtonConfig(value); }
    );

    ComboBox::setup<std::int32_t>(
        m_ui->cbSoundMode,
        0,
        {
            {"Stereo", 0},
            {"Monoaural", 1}
        },
        [](std::int32_t value) { SaveManager::setSoundMode(value); }
    );

    ComboBox::setup<Save::Subweapon>(
        m_ui->cbSubweapon,
        Save::Subweapon::NONE,
        {
            {"None", Save::Subweapon::NONE},
            {"Knife", Save::Subweapon::KNIFE},
            {"Holy Water", Save::Subweapon::HOLY_WATER},
            {"Cross", Save::Subweapon::CROSS},
            {"Axe", Save::Subweapon::AXE},
            {"Wooden Stake", Save::Subweapon::WOODEN_STAKE},
            {"Rose", Save::Subweapon::ROSE}
        },
        [](Save::Subweapon value) { SaveManager::setSubweapon(value); }
    );

    // setupComboBoxBitflag(ui->cbDifficulty, comboBoxDataDifficulty);
    const QVector<ComboBox::Item<Save::SaveFlag>> difficultyChoices = {
        {"Easy", Save::SAVE_FLAG_EASY},
        {"Normal", Save::SAVE_FLAG_NORMAL},
        {"Hard", Save::SAVE_FLAG_HARD}
    };
    ComboBox::setup<Save::SaveFlag>(
        m_ui->cbDifficulty,
        Save::SAVE_FLAG_EASY,
        difficultyChoices,
        [difficultyChoices](std::int32_t value) {
            for (const auto &[k, v] : difficultyChoices) {
                SaveManager::unsetFlags(v);
            }
            SaveManager::setFlags(value);
        }
    );

    // setupComboBoxBitflag(ui->cbReinhardtEnding, comboBoxDataEndingReinhardt);
    const QVector<ComboBox::Item<std::int32_t>> reinhardtEndingChoices = {
        {"-", 0},
        {"Good", Save::SAVE_FLAG_REINHARDT_GOOD_ENDING},
        {"Bad", Save::SAVE_FLAG_REINHARDT_BAD_ENDING}
    };
    ComboBox::setup<std::int32_t>(
        m_ui->cbReinhardtEnding,
        0,
        reinhardtEndingChoices,
        [reinhardtEndingChoices](std::int32_t value) {
            for (const auto &[k, v] : reinhardtEndingChoices) {
                SaveManager::unsetFlags(v);
            }
            SaveManager::setFlags(value);
        }
    );

    // setupComboBoxBitflag(ui->cbCarrieEnding, comboBoxDataEndingCarrie);
    const QVector<ComboBox::Item<std::int32_t>> carrieEndingChoices = {
        {"-", 0},
        {"Good", Save::SAVE_FLAG_CARRIE_GOOD_ENDING},
        {"Bad", Save::SAVE_FLAG_CARRIE_BAD_ENDING}
    };
    ComboBox::setup<std::int32_t>(
        m_ui->cbCarrieEnding,
        0,
        carrieEndingChoices,
        [carrieEndingChoices](std::int32_t value) {
            for (const auto &[k, v] : carrieEndingChoices) {
                SaveManager::unsetFlags(v);
            }
            SaveManager::setFlags(value);
        }
    );

    ComboBox::setup<Save::Region>(
        m_ui->cbRegion,
        Save::Region::USA,
        {
            {"USA", Save::Region::USA},
            {"JPN", Save::Region::JPN},
            {"PAL", Save::Region::PAL}
        },
        [this](Save::Region value) {
            SaveManager::getInstance()->setRegion(value);
            switch (value) {
            default:
            case Save::Region::USA:
                m_ui->cbLanguage->setEnabled(false);
                m_ui->cbLanguage->setCurrentIndex(0);
                m_ui->cbLanguage->setItemText(0, "English");
                // itemsUi->leItemsSpecial3->setEnabled(false);
                // itemsUi->leItemsPoutPourri->setEnabled(true);
                break;

            case Save::Region::JPN:
                m_ui->cbLanguage->setEnabled(false);
                m_ui->cbLanguage->setCurrentIndex(0);
                m_ui->cbLanguage->setItemText(0, "Japanese");
                // itemsUi->leItemsSpecial3->setEnabled(true);
                // itemsUi->leItemsPoutPourri->setEnabled(false);
                break;

            case Save::Region::PAL:
                m_ui->cbLanguage->setEnabled(true);
                m_ui->cbLanguage->setCurrentIndex(0);
                m_ui->cbLanguage->setItemText(0, "English");
                // itemsUi->leItemsSpecial3->setEnabled(true);
                // itemsUi->leItemsPoutPourri->setEnabled(false);
                break;
            }
        }
    );

    ComboBox::setup<Save::Language>(
        m_ui->cbLanguage,
        Save::Language::ENGLISH,
        {
            {"English", Save::Language::ENGLISH},
            {"German", Save::Language::GERMAN},
            {"French", Save::Language::FRENCH}
        },
        [](Save::Language value) { SaveManager::setLanguage(value); }
    );

    // Initialize cbLanguage to USA values
    // ui->cbLanguage->setEnabled(false);
    // ui->cbLanguage->setCurrentIndex(0);
    // ui->cbLanguage->setCurrentText("English");
    // ComboBox::setCurrentValue(ui->cbRegion, Save::USA);

    // In order to avoid the checkbox from being disabled,
    // we ensure that its parent is MainWindow (since it's never disabled by the "enableUiComponents" function)
    m_ui->cboxEnabled->setParent(this);
    CheckBox::setup<std::uint32_t>(
        m_ui->cboxEnabled,
        Save::SAVE_FLAG_ACTIVE,
        [](std::uint32_t value) {
            SaveManager::setFlags(value);
            // updateWindowVisibility(true);
        },
        [](std::uint32_t value) {
            SaveManager::unsetFlags(value);
            // updateWindowVisibility(false);
        }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxHardMode,
        Save::SAVE_FLAG_HARD_MODE_UNLOCKED,
        [](std::uint32_t value) { SaveManager::setFlags(value); },
        [](std::uint32_t value) { SaveManager::unsetFlags(value); }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxUseAlternateCostume,
        Save::SAVE_FLAG_COSTUME_IS_BEING_USED,
        [](std::uint32_t value) { SaveManager::setFlags(value); },
        [](std::uint32_t value) { SaveManager::unsetFlags(value); }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxReinhardtCostume,
        Save::SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME,
        [](std::uint32_t value) { SaveManager::setFlags(value); },
        [](std::uint32_t value) { SaveManager::unsetFlags(value); }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxCarrieCostume,
        Save::SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME,
        [](std::uint32_t value) { SaveManager::setFlags(value); },
        [](std::uint32_t value) { SaveManager::unsetFlags(value); }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxNitro,
        Save::SAVE_FLAG_CAN_EXPLODE_ON_JUMPING,
        [](std::uint32_t value) { SaveManager::setFlags(value); },
        [](std::uint32_t value) { SaveManager::unsetFlags(value); }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxVamp,
        Save::PLAYER_FLAG_VAMP,
        [](std::uint32_t value) { SaveManager::setPlayerStatus(value); },
        [](std::uint32_t value) { SaveManager::unsetPlayerStatus(value); }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxPoison,
        Save::PLAYER_FLAG_POISON,
        [](std::uint32_t value) { SaveManager::setPlayerStatus(value); },
        [](std::uint32_t value) { SaveManager::unsetPlayerStatus(value); }
    );

    CheckBox::setup<std::uint32_t>(
        m_ui->cboxSto,
        Save::PLAYER_FLAG_STO,
        [](std::uint32_t value) { SaveManager::setPlayerStatus(value); },
        [](std::uint32_t value) { SaveManager::unsetPlayerStatus(value); }
    );

    // Uncheck the "save enabled checkbox" when opening the program
    m_ui->cboxEnabled->setChecked(false);
}

void GeneralForm::populate(Save::Data *saveData) const
{
    if (saveData == nullptr) {
        return;
    }

    const auto *inst = SaveManager::getInstance();

    // Combo boxes
    ComboBox::setCurrentValue(m_ui->cbCharacter, saveData->character);
    ComboBox::setCurrentValue(m_ui->cbButtonConfig, saveData->button_config);
    ComboBox::setCurrentValue(m_ui->cbSoundMode, saveData->sound_mode);
    ComboBox::setCurrentValue(m_ui->cbSubweapon, saveData->subweapon);
    ComboBox::setCurrentValue(m_ui->cbMap, saveData->map);

    ComboBox::setCurrentValue(m_ui->cbDifficulty, saveData->getFlag(Save::SAVE_FLAG_EASY | Save::SAVE_FLAG_NORMAL | Save::SAVE_FLAG_HARD));
    ComboBox::setCurrentValue(m_ui->cbReinhardtEnding, saveData->getFlag(Save::SAVE_FLAG_REINHARDT_GOOD_ENDING | Save::SAVE_FLAG_REINHARDT_BAD_ENDING));
    ComboBox::setCurrentValue(m_ui->cbCarrieEnding, saveData->getFlag(Save::SAVE_FLAG_CARRIE_GOOD_ENDING | Save::SAVE_FLAG_CARRIE_BAD_ENDING));
    ComboBox::setCurrentValue(m_ui->cbRegion, inst->getRegion());

    if (inst->getRegion() == Save::Region::PAL) {
        ComboBox::setCurrentValue(m_ui->cbLanguage, saveData->language);
    }

    // Numerical Line edits
    m_ui->leLife->setText(QString::number(saveData->life));
    m_ui->leGold->setText(QString::number(saveData->gold));
    m_ui->leRedJewels->setText(QString::number(saveData->getItem(Save::Item::RED_JEWEL)));
    m_ui->leSpawn->setText(QString::number(saveData->spawn));
    m_ui->leWhiteJewel->setText(QString::number(saveData->save_crystal_number));
    m_ui->leTimesSaved->setText(QString::number(saveData->time_saved_counter));
    m_ui->leDeathCount->setText(QString::number(saveData->death_counter));
    m_ui->leGoldRenon->setText(QString::number(saveData->gold_spent_on_Renon));
    m_ui->leHourVamp->setText(QString::number(saveData->current_hour_VAMP));
    m_ui->leHealthDepletionRate->setText(QString::number(saveData->health_depletion_rate_while_poisoned));
    m_ui->leWeek->setText(QString::number(saveData->week));
    m_ui->leDay->setText(QString::number(saveData->day));
    m_ui->leHour->setText(QString::number(saveData->hour));
    m_ui->leMinutes->setText(QString::number(saveData->minute));
    m_ui->leSeconds->setText(QString::number(saveData->seconds));
    m_ui->leMilliseconds->setText(QString::number(saveData->milliseconds));
    m_ui->leFrameCount->setText(QString::number(saveData->gameplay_framecount));
    convertFrameToTime(saveData->gameplay_framecount, m_ui->labelPlaytime);

    // Checkboxes
    m_ui->cboxEnabled->setChecked(saveData->getFlag(Save::SAVE_FLAG_ACTIVE));
    // TODO: make the following function available
    // updateCheckboxEnabledVisibility();

    m_ui->cboxHardMode->setChecked(saveData->getFlag(Save::SAVE_FLAG_HARD_MODE_UNLOCKED));
    m_ui->cboxUseAlternateCostume->setChecked(saveData->getFlag(Save::SAVE_FLAG_COSTUME_IS_BEING_USED));
    m_ui->cboxReinhardtCostume->setChecked(saveData->getFlag(Save::SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME));
    m_ui->cboxCarrieCostume->setChecked(saveData->getFlag(Save::SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME));
    m_ui->cboxNitro->setChecked(saveData->getFlag(Save::SAVE_FLAG_CAN_EXPLODE_ON_JUMPING));
    m_ui->cboxVamp->setChecked(saveData->getPlayerStatus(Save::PLAYER_FLAG_VAMP));
    m_ui->cboxPoison->setChecked(saveData->getPlayerStatus(Save::PLAYER_FLAG_POISON));
    m_ui->cboxSto->setChecked(saveData->getPlayerStatus(Save::PLAYER_FLAG_STO));
}
