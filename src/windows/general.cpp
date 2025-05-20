#include "windows/general.h"

#include "CheckBoxHelper.h"
#include "ComboBoxHelper.h"
#include "LineEditHelper.h"
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
    LineEditHelper::setup(m_ui->leLife, QString::number(100), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 1, 100);
        m_ui->leLife->setText(QString::number(value));
        SaveManager::getInstance()->setLife(value);
    });

    // LineEditHelper::setup(ui->leGold, 0, 99999,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setGold(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leGold, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint32_t>(text, 0, 99999);
        m_ui->leGold->setText(QString::number(value));
        SaveManager::getInstance()->setGold(value);
    });

    // LineEditHelper::setup(ui->leRedJewels, 0, 99,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Data::ITEM_ID_RED_JEWEL, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leRedJewels, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 99);
        m_ui->leRedJewels->setText(QString::number(value));
        SaveManager::getInstance()->setItem(Save::ITEM_ID_RED_JEWEL, value);
    });

    // LineEditHelper::setup(ui->leSpawn, 0, SHRT_MAX,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setSpawn(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leSpawn, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, SHRT_MAX);
        m_ui->leSpawn->setText(QString::number(value));
        SaveManager::getInstance()->setSpawn(value);
    });

    // LineEditHelper::setup(ui->leWhiteJewel, 0, USHRT_MAX,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setWhiteJewel(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leWhiteJewel, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, USHRT_MAX);
        m_ui->leWhiteJewel->setText(QString::number(value));
        SaveManager::getInstance()->setWhiteJewel(value);
    });

    // LineEditHelper::setup(ui->leTimesSaved, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setTimesSaved(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leTimesSaved, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leTimesSaved->setText(QString::number(value));
        SaveManager::getInstance()->setTimesSaved(value);
    });

    // LineEditHelper::setup(ui->leDeathCount, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setDeathCount(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leDeathCount, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leDeathCount->setText(QString::number(value));
        SaveManager::getInstance()->setDeathCount(value);
    });

    // LineEditHelper::setup(ui->leGoldRenon, 0, UINT_MAX,
    //     [](std::uint32_t value) {
    //         SaveManager::getInstance()->setGoldRenon(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leGoldRenon, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leGoldRenon->setText(QString::number(value));
        SaveManager::getInstance()->setGoldRenon(value);
    });

    // LineEditHelper::setup(ui->leHourVamp, 0, 23,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setHourVamp(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leHourVamp, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, 23);
        m_ui->leHourVamp->setText(QString::number(value));
        SaveManager::getInstance()->setHourVamp(value);
    });

    // LineEditHelper::setup(ui->leHealthDepletionRate, 0, SHRT_MAX,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setHealthDepletionRate(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leHealthDepletionRate, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, SHRT_MAX);
        m_ui->leHealthDepletionRate->setText(QString::number(value));
        SaveManager::getInstance()->setHealthDepletionRate(value);
    });

    // LineEditHelper::setup(ui->leWeek, 0, SHRT_MAX,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setWeek(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leWeek, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, SHRT_MAX);
        m_ui->leWeek->setText(QString::number(value));
        SaveManager::getInstance()->setWeek(value);
    });

    // LineEditHelper::setup(ui->leDay, 0, 7 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setDay(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leDay, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, 7 - 1);
        m_ui->leDay->setText(QString::number(value));
        SaveManager::getInstance()->setDay(value);
    });

    // LineEditHelper::setup(ui->leHour, 0, 24 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setHour(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leHour, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, 24 - 1);
        m_ui->leHour->setText(QString::number(value));
        SaveManager::getInstance()->setHour(value);
    });

    // LineEditHelper::setup(ui->leMinutes, 0, 60 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setMinutes(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leMinutes, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, 60 - 1);
        m_ui->leMinutes->setText(QString::number(value));
        SaveManager::getInstance()->setMinutes(value);
    });

    // LineEditHelper::setup(ui->leSeconds, 0, 60 - 1,
    //     [](std::int16_t value) {
    //         SaveManager::getInstance()->setSeconds(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leSeconds, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, 60 - 1);
        m_ui->leSeconds->setText(QString::number(value));
        SaveManager::getInstance()->setSeconds(value);
    });

    // LineEditHelper::setup(ui->leMilliseconds, 0, 600 - 1,
    //     [](std::uint16_t value) {
    //         SaveManager::getInstance()->setMilliseconds(value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leMilliseconds, QString::number(0), validator, [this](const QString &text) {
        // FIXME: uint16_t should be int16_t
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint16_t>(text, 0, 600 - 1);
        m_ui->leMilliseconds->setText(QString::number(value));
        SaveManager::getInstance()->setMilliseconds(value);
    });

    // LineEditHelper::setup(ui->leFrameCount, 0, UINT_MAX,
    //     [this](std::uint32_t value) {
    //         SaveManager::getInstance()->setFramecount(value);
    //         convertFrameToTime(SaveManager::getInstance()->getFrameCount(), ui->labelPlaytime);
    //     }
    // );
    LineEditHelper::setup(m_ui->leFrameCount, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint32_t>(text, 0, UINT_MAX);
        m_ui->leFrameCount->setText(QString::number(value));
        SaveManager::getInstance()->setFrameCount(value);
        convertFrameToTime(SaveManager::getInstance()->getFrameCount(), m_ui->labelPlaytime);
    });

    // Initialize combo boxes and set their default values
    ComboBoxHelper::setup<Save::Map>(
        m_ui->cbMap,
        Save::MORI,
        {
            {"Forest of Silence", Save::MORI},
            {"Castle Wall (Towers)", Save::TOU},
            {"Castle Wall (Main)", Save::TOUOKUJI},
            {"Villa (Yard)", Save::NAKANIWA},
            {"Villa (Foyer)", Save::BEKKAN_1F},
            {"Villa (Hallway)", Save::BEKKAN_2F},
            {"Villa (Maze Garden)", Save::MEIRO_TEIEN},
            {"Tunnel", Save::CHIKA_KODO},
            {"Underground Waterway", Save::CHIKA_SUIRO},
            {"Castle Center (Main)", Save::HONMARU_B1F},
            {"Castle Center (Bottom Elevator)", Save::HONMARU_1F},
            {"Castle Center (Gears)", Save::HONMARU_2F},
            {"Castle Center (Friendly Lizard-man)", Save::HONMARU_3F_MINAMI},
            {"Castle Center (Library)", Save::HONMARU_4F_MINAMI},
            {"Castle Center (Nitro Room)", Save::HONMARU_3F_KITA},
            {"Castle Center (Top Elevator)", Save::HONMARU_5F},
            {"Tower of Execution", Save::SHOKEI_TOU},
            {"Tower of Sorcery", Save::MAHOU_TOU},
            {"Tower of Science", Save::KAGAKU_TOU},
            {"Duel Tower", Save::KETTOU_TOU},
            {"Castle Keep Stairs", Save::TURO_TOKEITOU},
            {"Castle Keep", Save::TENSHU},
            {"Intro Cutscene Map", Save::ENDING_DUMMY},
            {"Clock Tower", Save::TOKEITOU_NAI},
            {"Dracula Desert", Save::DRACULA},
            {"Rose / Actrice Fan Room", Save::ROSE},
            {"Villa (Vampire Crypt)", Save::BEKKAN_BOSS},
            {"Room of Clocks", Save::TOU_TURO},
            {"Ending Map", Save::ENDING},
            {"Test Grid", Save::TEST_GRID}
        },
        [](Save::Map value) { SaveManager::getInstance()->setMap(value); }
    );

    ComboBoxHelper::setup<Save::PlayerCharacter>(
        m_ui->cbCharacter, Save::REINHARDT,
        {
            {"Reinhardt", Save::REINHARDT},
            {"Carrie", Save::CARRIE}
        },
        [](Save::PlayerCharacter value) { SaveManager::getInstance()->setCharacter(value); }
    );

    ComboBoxHelper::setup<std::int32_t>(
        m_ui->cbButtonConfig,
        0,
        {
            {"Type A", 0},
            {"Type B", 1},
            {"Type C", 2}
        },
        [](std::int32_t value) { SaveManager::getInstance()->setButtonConfig(value); }
    );

    ComboBoxHelper::setup<std::int32_t>(
        m_ui->cbSoundMode,
        0,
        {
            {"Stereo", 0},
            {"Monoaural", 1}
        },
        [](std::int32_t value) { SaveManager::getInstance()->setSoundMode(value); }
    );

    ComboBoxHelper::setup<Save::Subweapon>(
        m_ui->cbSubweapon,
        Save::SUBWEAPON_NONE,
        {
            {"None", Save::SUBWEAPON_NONE},
            {"Knife", Save::SUBWEAPON_KNIFE},
            {"Holy Water", Save::SUBWEAPON_HOLY_WATER},
            {"Cross", Save::SUBWEAPON_CROSS},
            {"Axe", Save::SUBWEAPON_AXE},
            {"Wooden Stake", Save::SUBWEAPON_WOODEN_STAKE},
            {"Rose", Save::SUBWEAPON_ROSE}
        },
        [](Save::Subweapon value) { SaveManager::getInstance()->setSubweapon(value); }
    );

    // setupComboBoxBitflag(ui->cbDifficulty, comboBoxDataDifficulty);
    const QVector<ComboBoxHelper::Item<Save::SaveFlag>> difficultyChoices = {
        {"Easy", Save::SAVE_FLAG_EASY},
        {"Normal", Save::SAVE_FLAG_NORMAL},
        {"Hard", Save::SAVE_FLAG_HARD}
    };
    ComboBoxHelper::setup<Save::SaveFlag>(
        m_ui->cbDifficulty,
        Save::SAVE_FLAG_EASY,
        difficultyChoices,
        [difficultyChoices](std::int32_t value) {
            for (const auto &[k, v] : difficultyChoices) {
                SaveManager::getInstance()->unsetFlags(v);
            }
            SaveManager::getInstance()->setFlags(value);
        }
    );

    // setupComboBoxBitflag(ui->cbReinhardtEnding, comboBoxDataEndingReinhardt);
    const QVector<ComboBoxHelper::Item<std::int32_t>> reinhardtEndingChoices = {
        {"-", 0},
        {"Good", Save::SAVE_FLAG_REINHARDT_GOOD_ENDING},
        {"Bad", Save::SAVE_FLAG_REINHARDT_BAD_ENDING}
    };
    ComboBoxHelper::setup<std::int32_t>(
        m_ui->cbReinhardtEnding,
        0,
        reinhardtEndingChoices,
        [reinhardtEndingChoices](std::int32_t value) {
            for (const auto &[k, v] : reinhardtEndingChoices) {
                SaveManager::getInstance()->unsetFlags(v);
            }
            SaveManager::getInstance()->setFlags(value);
        }
    );

    // setupComboBoxBitflag(ui->cbCarrieEnding, comboBoxDataEndingCarrie);
    const QVector<ComboBoxHelper::Item<std::int32_t>> carrieEndingChoices = {
        {"-", 0},
        {"Good", Save::SAVE_FLAG_CARRIE_GOOD_ENDING},
        {"Bad", Save::SAVE_FLAG_CARRIE_BAD_ENDING}
    };
    ComboBoxHelper::setup<std::int32_t>(
        m_ui->cbCarrieEnding,
        0,
        carrieEndingChoices,
        [carrieEndingChoices](std::int32_t value) {
            for (const auto &[k, v] : carrieEndingChoices) {
                SaveManager::getInstance()->unsetFlags(v);
            }
            SaveManager::getInstance()->setFlags(value);
        }
    );

    ComboBoxHelper::setup<Save::Region>(
        m_ui->cbRegion,
        Save::USA,
        {
            {"USA", Save::USA},
            {"JPN", Save::JPN},
            {"PAL", Save::PAL}
        },
        [this](Save::Region value) {
            SaveManager::getInstance()->setRegion(value);
            switch (value) {
            default:
            case Save::USA:
                m_ui->cbLanguage->setEnabled(false);
                m_ui->cbLanguage->setCurrentIndex(0);
                m_ui->cbLanguage->setItemText(0, "English");
                // itemsUi->leItemsSpecial3->setEnabled(false);
                // itemsUi->leItemsPoutPourri->setEnabled(true);
                break;

            case Save::JPN:
                m_ui->cbLanguage->setEnabled(false);
                m_ui->cbLanguage->setCurrentIndex(0);
                m_ui->cbLanguage->setItemText(0, "Japanese");
                // itemsUi->leItemsSpecial3->setEnabled(true);
                // itemsUi->leItemsPoutPourri->setEnabled(false);
                break;

            case Save::PAL:
                m_ui->cbLanguage->setEnabled(true);
                m_ui->cbLanguage->setCurrentIndex(0);
                m_ui->cbLanguage->setItemText(0, "English");
                // itemsUi->leItemsSpecial3->setEnabled(true);
                // itemsUi->leItemsPoutPourri->setEnabled(false);
                break;
            }
        }
    );

    ComboBoxHelper::setup<Save::Language>(
        m_ui->cbLanguage,
        Save::ENGLISH,
        {
            {"English", Save::ENGLISH},
            {"German", Save::GERMAN},
            {"French", Save::FRENCH}
        },
        [](std::int32_t value) { SaveManager::getInstance()->setLanguage(value); }
    );

    // Initialize cbLanguage to USA values
    // ui->cbLanguage->setEnabled(false);
    // ui->cbLanguage->setCurrentIndex(0);
    // ui->cbLanguage->setCurrentText("English");
    // ComboBoxHelper::setCurrentValue(ui->cbRegion, Save::USA);

    // In order to avoid the checkbox from being disabled,
    // we ensure that its parent is MainWindow (since it's never disabled by the "enableUiComponents" function)
    m_ui->cboxEnabled->setParent(this);
    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxEnabled,
        Save::SAVE_FLAG_ACTIVE,
        [this](std::uint32_t value) {
            SaveManager::getInstance()->setFlags(value);
            // updateWindowVisibility(true);
        },
        [this](std::uint32_t value) {
            SaveManager::getInstance()->unsetFlags(value);
            // updateWindowVisibility(false);
        }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxHardMode,
        Save::SAVE_FLAG_HARD_MODE_UNLOCKED,
        [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxUseAlternateCostume,
        Save::SAVE_FLAG_COSTUME_IS_BEING_USED,
        [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxReinhardtCostume,
        Save::SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME,
        [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxCarrieCostume,
        Save::SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME,
        [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxNitro,
        Save::SAVE_FLAG_CAN_EXPLODE_ON_JUMPING,
        [](std::uint32_t value) { SaveManager::getInstance()->setFlags(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetFlags(value); }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxVamp,
        Save::PLAYER_FLAG_VAMP,
        [](std::uint32_t value) { SaveManager::getInstance()->setPlayerStatus(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetPlayerStatus(value); }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxPoison,
        Save::PLAYER_FLAG_POISON,
        [](std::uint32_t value) { SaveManager::getInstance()->setPlayerStatus(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetPlayerStatus(value); }
    );

    CheckBoxHelper::setup<std::uint32_t>(
        m_ui->cboxSto,
        Save::PLAYER_FLAG_STO,
        [](std::uint32_t value) { SaveManager::getInstance()->setPlayerStatus(value); },
        [](std::uint32_t value) { SaveManager::getInstance()->unsetPlayerStatus(value); }
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
    // selectComboBoxOption(*ui->cbCharacter, saveData->character);
    ComboBoxHelper::setCurrentValue(m_ui->cbCharacter, saveData->character);
    // selectComboBoxOption(*ui->cbButtonConfig, saveData->button_config);
    ComboBoxHelper::setCurrentValue(m_ui->cbButtonConfig, saveData->button_config);
    // selectComboBoxOption(*ui->cbSoundMode, saveData->sound_mode);
    ComboBoxHelper::setCurrentValue(m_ui->cbSoundMode, saveData->sound_mode);
    // selectComboBoxOption(*ui->cbSubweapon, saveData->subweapon);
    ComboBoxHelper::setCurrentValue(m_ui->cbSubweapon, saveData->subweapon);
    // selectComboBoxOption(*ui->cbMap, saveData->map);
    ComboBoxHelper::setCurrentValue(m_ui->cbMap, saveData->map);

    ComboBoxHelper::setCurrentValue(m_ui->cbDifficulty, saveData->getFlag(Save::SAVE_FLAG_EASY | Save::SAVE_FLAG_NORMAL | Save::SAVE_FLAG_HARD));
    ComboBoxHelper::setCurrentValue(m_ui->cbReinhardtEnding, saveData->getFlag(Save::SAVE_FLAG_REINHARDT_GOOD_ENDING | Save::SAVE_FLAG_REINHARDT_BAD_ENDING));
    ComboBoxHelper::setCurrentValue(m_ui->cbCarrieEnding, saveData->getFlag(Save::SAVE_FLAG_CARRIE_GOOD_ENDING | Save::SAVE_FLAG_CARRIE_BAD_ENDING));
    ComboBoxHelper::setCurrentValue(m_ui->cbRegion, inst->getRegion());

    if (inst->getRegion() == Save::PAL) {
        ComboBoxHelper::setCurrentValue(m_ui->cbLanguage, saveData->language);
    }

    // Numerical Line edits
    m_ui->leLife->setText(QString::number(saveData->life));
    m_ui->leGold->setText(QString::number(saveData->gold));
    m_ui->leRedJewels->setText(QString::number(saveData->getItem(Save::ITEM_ID_RED_JEWEL)));
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
