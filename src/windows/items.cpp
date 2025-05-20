#include "windows/items.h"
#include "ui_items.h"
#include "save/Save.h"
#include "save/SaveManager.h"
#include "LineEditHelper.h"

ItemsForm::ItemsForm(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::ItemsForm)
{
    m_ui->setupUi(this);
}

ItemsForm::~ItemsForm()
{
    delete m_ui;
}

SaveData::eItemId actualItemId(const SaveManager *instance, SaveData::eItemId item)
{
    if (instance->getRegion() == SaveData::PAL || instance->getRegion() == SaveData::JPN) {
        return static_cast<decltype(item)>(static_cast<std::int32_t>(item) + 1);
    }
    return item;
}

void ItemsForm::setup()
{
    const QRegularExpression acceptDecimalAndHexRegex(R"(^(\d{1,8}|0[xX][0-9A-Fa-f]{1,8})$)");
    const auto *validator = new QRegularExpressionValidator(acceptDecimalAndHexRegex, this);
    // Jewels
    LineEditHelper::setup(m_ui->leItemsSpecial1, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsSpecial1->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SPECIAL1, value);
    });

    // LineEditHelper::setup(ui->leItemsSpecial2, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SPECIAL2, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsSpecial2, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsSpecial2->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SPECIAL2, value);
    });

    // LineEditHelper::setup(ui->leItemsSpecial3, 0, 1,
    //     [](std::uint8_t value) {
    //         // This item is version exclusive. Ensure we're only setting it when its associated region is set.
    //         if (SaveManager::getInstance()->getRegion() == SaveData::PAL ||
    //             SaveManager::getInstance()->getRegion() == SaveData::JPN) {
    //             SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SPECIAL3, value);
    //         }
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsSpecial3, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsSpecial3->setText(QString::number(value));
        // This item is version exclusive. Ensure we're only setting it when its associated region is set.
        if (auto *inst = SaveManager::getInstance(); inst->getRegion() == SaveData::PAL || inst->getRegion() == SaveData::JPN) {
            inst->setItem(SaveData::ITEM_ID_SPECIAL3, value);
        }
    });

    // Healing and effect-cure items
    // LineEditHelper::setup(ui->leItemsRoastChicken, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = SaveData::ITEM_ID_ROAST_CHICKEN;
    //         if (SaveManager::getInstance()->getRegion() == SaveData::PAL ||
    //             SaveManager::getInstance()->getRegion() == SaveData::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsRoastChicken, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsRoastChicken->setText(QString::number(value));
        auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        inst->setItem(actualItemId(inst, SaveData::ITEM_ID_ROAST_CHICKEN), value);
    });

    // LineEditHelper::setup(ui->leItemsRoastBeef, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = SaveData::ITEM_ID_ROAST_BEEF;
    //         if (SaveManager::getInstance()->getRegion() == SaveData::PAL ||
    //             SaveManager::getInstance()->getRegion() == SaveData::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsRoastBeef, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsRoastBeef->setText(QString::number(value));
        auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        inst->setItem(actualItemId(inst, SaveData::ITEM_ID_ROAST_BEEF), value);
    });

    // LineEditHelper::setup(ui->leItemsPurifying, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = SaveData::ITEM_ID_PURIFYING;
    //         if (SaveManager::getInstance()->getRegion() == SaveData::PAL ||
    //             SaveManager::getInstance()->getRegion() == SaveData::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsPurifying, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsPurifying->setText(QString::number(value));
        auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        inst->setItem(actualItemId(inst, SaveData::ITEM_ID_PURIFYING), value);
    });

    // LineEditHelper::setup(ui->leItemsCureAmpoule, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = SaveData::ITEM_ID_CURE_AMPOULE;
    //         if (SaveManager::getInstance()->getRegion() == SaveData::PAL ||
    //             SaveManager::getInstance()->getRegion() == SaveData::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsCureAmpoule, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsCureAmpoule->setText(QString::number(value));
        auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        inst->setItem(actualItemId(inst, SaveData::ITEM_ID_CURE_AMPOULE), value);
    });

    // LineEditHelper::setup(ui->leItemsPoutPourri, 0, 10,
    //     [](std::uint8_t value) {
    //         // This item is version exclusive. Ensure we're only setting it when its associated region is set.
    //         if (SaveManager::getInstance()->getRegion() == SaveData::USA) {
    //             SaveManager::getInstance()->setItem(SaveData::ITEM_ID_POUT_POURRI, value);
    //         }
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsPoutPourri, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsPoutPourri->setText(QString::number(value));
        // This item is version exclusive. Ensure we're only setting it when its associated region is set.
        if (auto *inst = SaveManager::getInstance(); inst->getRegion() == SaveData::USA) {
            inst->setItem(SaveData::ITEM_ID_POUT_POURRI, value);
        }
    });

    // LineEditHelper::setup(ui->leItemsHealingKit, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = SaveData::ITEM_ID_HEALING_KIT;
    //         if (SaveManager::getInstance()->getRegion() == SaveData::PAL ||
    //             SaveManager::getInstance()->getRegion() == SaveData::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsHealingKit, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsHealingKit->setText(QString::number(value));
        auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        inst->setItem(actualItemId(inst, SaveData::ITEM_ID_HEALING_KIT), value);
    });

    // Quest Items
    // LineEditHelper::setup(ui->leItemsSunCard, 0, 10,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SUN_CARD, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsSunCard, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsSunCard->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SUN_CARD, value);
    });

    // LineEditHelper::setup(ui->leItemsMoonCard, 0, 10,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_MOON_CARD, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsMoonCard, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsMoonCard->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_MOON_CARD, value);
    });

    // LineEditHelper::setup(ui->leItemsNitro, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_MAGICAL_NITRO, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsNitro, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsNitro->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_MAGICAL_NITRO, value);
    });

    // LineEditHelper::setup(ui->leItemsMandragora, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_MANDRAGORA, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsMandragora, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsMandragora->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_MANDRAGORA, value);
    });

    // Keys
    // LineEditHelper::setup(ui->leKeyScience1, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SCIENCE_KEY1, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyScience1, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyScience1->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SCIENCE_KEY1, value);
    });

    // LineEditHelper::setup(ui->leKeyScience2, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SCIENCE_KEY2, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyScience2, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyScience2->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SCIENCE_KEY2, value);
    });

    // LineEditHelper::setup(ui->leKeyScience3, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SCIENCE_KEY3, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyScience3, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyScience3->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_SCIENCE_KEY3, value);
    });

    // LineEditHelper::setup(ui->leKeyClocktower1, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CLOCKTOWER_KEY1, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyClocktower1, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyClocktower1->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CLOCKTOWER_KEY1, value);
    });

    // LineEditHelper::setup(ui->leKeyClocktower2, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CLOCKTOWER_KEY2, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyClocktower2, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyClocktower2->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CLOCKTOWER_KEY2, value);
    });

    // LineEditHelper::setup(ui->leKeyClocktower3, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CLOCKTOWER_KEY3, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyClocktower3, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyClocktower3->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CLOCKTOWER_KEY3, value);
    });

    // LineEditHelper::setup(ui->leKeyChamber, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CHAMBER_KEY, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyChamber, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyChamber->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_CHAMBER_KEY, value);
    });

    // LineEditHelper::setup(ui->leKeyCopper, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_COPPER_KEY, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyCopper, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyCopper->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_COPPER_KEY, value);
    });

    // LineEditHelper::setup(ui->leKeyExecution, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_EXECUTION_KEY, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyExecution, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyExecution->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_EXECUTION_KEY, value);
    });

    // LineEditHelper::setup(ui->leKeyGarden, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_GARDEN_KEY, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyGarden, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyGarden->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_GARDEN_KEY, value);
    });

    // LineEditHelper::setup(ui->leKeyLeftTower, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_LEFT_TOWER_KEY, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyLeftTower, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyLeftTower->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_LEFT_TOWER_KEY, value);
    });

    // LineEditHelper::setup(ui->leKeyArchives, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_ARCHIVES_KEY, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyArchives, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyArchives->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_ARCHIVES_KEY, value);
    });

    // LineEditHelper::setup(ui->leKeyStoreroom, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_STOREROOM_KEY, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leKeyStoreroom, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leKeyStoreroom->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_STOREROOM_KEY, value);
    });

    // Unused items
    // LineEditHelper::setup(ui->leItemsER, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_ENGAGEMENT_RING, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsER, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsER->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_ENGAGEMENT_RING, value);
    });

    // LineEditHelper::setup(ui->leItemsIG, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(SaveData::ITEM_ID_INCANDESCENT_GAZE, value);
    //     }
    // );
    LineEditHelper::setup(m_ui->leItemsIG, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEditHelper::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsIG->setText(QString::number(value));
        SaveManager::getInstance()->setItem(SaveData::ITEM_ID_INCANDESCENT_GAZE, value);
    });
}

void ItemsForm::populate(SaveData *saveData) const
{
    if (saveData == nullptr) {
        return;
    }

    m_ui->leItemsSpecial1->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_SPECIAL1)));
    m_ui->leItemsSpecial2->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_SPECIAL2)));

    if (SaveManager::getInstance()->getRegion() == SaveData::PAL ||
        SaveManager::getInstance()->getRegion() == SaveData::JPN) {
        m_ui->leItemsSpecial3->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_SPECIAL3)));
    }
    else {
        m_ui->leItemsSpecial3->setText("0");
    }

    if (SaveManager::getInstance()->getRegion() == SaveData::USA) {
        m_ui->leItemsRoastChicken->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_ROAST_CHICKEN)));
        m_ui->leItemsRoastBeef->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_ROAST_BEEF)));
        m_ui->leItemsHealingKit->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_HEALING_KIT)));
        m_ui->leItemsPurifying->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_PURIFYING)));
        m_ui->leItemsCureAmpoule->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_CURE_AMPOULE)));
    }
    else {
        m_ui->leItemsRoastChicken->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_ROAST_CHICKEN + 1)));
        m_ui->leItemsRoastBeef->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_ROAST_BEEF + 1)));
        m_ui->leItemsHealingKit->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_HEALING_KIT + 1)));
        m_ui->leItemsPurifying->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_PURIFYING + 1)));
        m_ui->leItemsCureAmpoule->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_CURE_AMPOULE + 1)));
    }

    if (SaveManager::getInstance()->getRegion() == SaveData::USA) {
        m_ui->leItemsPoutPourri->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_POUT_POURRI)));
    }
    else {
        m_ui->leItemsPoutPourri->setText("0");
    }

    m_ui->leItemsSunCard->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_SUN_CARD)));
    m_ui->leItemsMoonCard->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_MOON_CARD)));
    m_ui->leItemsNitro->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_MAGICAL_NITRO)));
    m_ui->leItemsMandragora->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_MANDRAGORA)));
    m_ui->leKeyArchives->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_ARCHIVES_KEY)));
    m_ui->leKeyLeftTower->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_LEFT_TOWER_KEY)));
    m_ui->leKeyStoreroom->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_STOREROOM_KEY)));
    m_ui->leKeyGarden->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_GARDEN_KEY)));
    m_ui->leKeyCopper->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_COPPER_KEY)));
    m_ui->leKeyChamber->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_CHAMBER_KEY)));
    m_ui->leKeyExecution->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_EXECUTION_KEY)));
    m_ui->leKeyScience1->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_SCIENCE_KEY1)));
    m_ui->leKeyScience2->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_SCIENCE_KEY2)));
    m_ui->leKeyScience3->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_SCIENCE_KEY3)));
    m_ui->leKeyClocktower1->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_CLOCKTOWER_KEY1)));
    m_ui->leKeyClocktower2->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_CLOCKTOWER_KEY2)));
    m_ui->leKeyClocktower3->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_CLOCKTOWER_KEY3)));
    m_ui->leItemsER->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_ENGAGEMENT_RING)));
    m_ui->leItemsIG->setText(QString::number(saveData->getItem(SaveData::ITEM_ID_INCANDESCENT_GAZE)));
}
