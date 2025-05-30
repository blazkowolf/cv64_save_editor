#include "windows/items.h"
#include "ui_items.h"
#include "save/Save.h"
#include "save/SaveManager.h"
#include "util/checkbox.h"
#include "util/lineedit.h"

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

Save::Item actualItemId(const SaveManager *instance, Save::Item item)
{
    if (instance->getRegion() != Save::Region::USA) {
        return static_cast<decltype(item)>(static_cast<std::underlying_type_t<decltype(item)>>(item) + 1);
    }
    return item;
}

void ItemsForm::setup()
{
    const QRegularExpression acceptDecimalAndHexRegex(R"(^(\d{1,8}|0[xX][0-9A-Fa-f]{1,8})$)");
    const auto *validator = new QRegularExpressionValidator(acceptDecimalAndHexRegex, this);

    // Jewels
    CheckBox::setup(
        m_ui->chbSpecial1,
        [] { SaveManager::setItem(Save::Item::SPECIAL1, 1); },
        [] {  SaveManager::setItem(Save::Item::SPECIAL1, 0); }
    );

    CheckBox::setup(
        m_ui->chbSpecial2,
        [] { SaveManager::setItem(Save::Item::SPECIAL2, 1); },
        [] {  SaveManager::setItem(Save::Item::SPECIAL2, 0); }
    );

    // LineEdit::setup(m_ui->leItemsSpecial3, QString::number(0), validator, [this](const QString &text) {
    //     const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
    //     m_ui->leItemsSpecial3->setText(QString::number(value));
    //     // This item is version exclusive. Ensure we're only setting it when its associated region is set.
    //     FIXME: bring back this conditional logic for SPECIAL3
    //     if (const auto *inst = SaveManager::getInstance();
    //         inst->getRegion() == Save::Region::PAL || inst->getRegion() == Save::Region::JPN) {
    //         SaveManager::setItem(Save::Item::SPECIAL3, value);
    //     }
    // });
    CheckBox::setup(
        m_ui->chbSpecial3,
        [] { SaveManager::setItem(Save::Item::SPECIAL3, 1); },
        [] {  SaveManager::setItem(Save::Item::SPECIAL3, 0); }
    );

    // Healing and effect-cure items
    // LineEditHelper::setup(ui->leItemsRoastChicken, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = Save::Item::ITEM_ID_ROAST_CHICKEN;
    //         if (SaveManager::getInstance()->getRegion() == Save::PAL ||
    //             SaveManager::getInstance()->getRegion() == Save::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsRoastChicken, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsRoastChicken->setText(QString::number(value));
        const auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        SaveManager::setItem(actualItemId(inst, Save::Item::ROAST_CHICKEN), value);
    });

    // LineEditHelper::setup(ui->leItemsRoastBeef, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = Save::Item::ITEM_ID_ROAST_BEEF;
    //         if (SaveManager::getInstance()->getRegion() == Save::PAL ||
    //             SaveManager::getInstance()->getRegion() == Save::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsRoastBeef, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsRoastBeef->setText(QString::number(value));
        const auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        SaveManager::setItem(actualItemId(inst, Save::Item::ROAST_BEEF), value);
    });

    // LineEditHelper::setup(ui->leItemsPurifying, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = Save::Item::ITEM_ID_PURIFYING;
    //         if (SaveManager::getInstance()->getRegion() == Save::PAL ||
    //             SaveManager::getInstance()->getRegion() == Save::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsPurifying, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsPurifying->setText(QString::number(value));
        const auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        SaveManager::setItem(actualItemId(inst, Save::Item::PURIFYING), value);
    });

    // LineEditHelper::setup(ui->leItemsCureAmpoule, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = Save::Item::ITEM_ID_CURE_AMPOULE;
    //         if (SaveManager::getInstance()->getRegion() == Save::PAL ||
    //             SaveManager::getInstance()->getRegion() == Save::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsCureAmpoule, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsCureAmpoule->setText(QString::number(value));
        const auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        SaveManager::setItem(actualItemId(inst, Save::Item::CURE_AMPOULE), value);
    });

    // LineEditHelper::setup(ui->leItemsPoutPourri, 0, 10,
    //     [](std::uint8_t value) {
    //         // This item is version exclusive. Ensure we're only setting it when its associated region is set.
    //         if (SaveManager::getInstance()->getRegion() == Save::USA) {
    //             SaveManager::getInstance()->setItem(Save::Item::ITEM_ID_POUT_POURRI, value);
    //         }
    //     }
    // );
    LineEdit::setup(m_ui->leItemsPoutPourri, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsPoutPourri->setText(QString::number(value));
        // This item is version exclusive. Ensure we're only setting it when its associated region is set.
        if (const auto *inst = SaveManager::getInstance(); inst->getRegion() == Save::Region::USA) {
            SaveManager::setItem(Save::Item::POUT_POURRI, value);
        }
    });

    // LineEditHelper::setup(ui->leItemsHealingKit, 0, 10,
    //     [](std::uint8_t value) {
    //         // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
    //         std::int32_t actualItemId = Save::Item::ITEM_ID_HEALING_KIT;
    //         if (SaveManager::getInstance()->getRegion() == Save::PAL ||
    //             SaveManager::getInstance()->getRegion() == Save::JPN) {
    //             actualItemId++;
    //         }
    //
    //         SaveManager::getInstance()->setItem(actualItemId, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsHealingKit, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsHealingKit->setText(QString::number(value));
        const auto *inst = SaveManager::getInstance();
        // In the JPN and PAL versions, this item's ID is the same as USA, but added +1.
        SaveManager::setItem(actualItemId(inst, Save::Item::HEALING_KIT), value);
    });

    // Quest Items
    // LineEditHelper::setup(ui->leItemsSunCard, 0, 10,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Item::ITEM_ID_SUN_CARD, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsSunCard, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsSunCard->setText(QString::number(value));
        SaveManager::setItem(Save::Item::SUN_CARD, value);
    });

    // LineEditHelper::setup(ui->leItemsMoonCard, 0, 10,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Item::ITEM_ID_MOON_CARD, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsMoonCard, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 10);
        m_ui->leItemsMoonCard->setText(QString::number(value));
        SaveManager::setItem(Save::Item::MOON_CARD, value);
    });

    // LineEditHelper::setup(ui->leItemsNitro, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Item::ITEM_ID_MAGICAL_NITRO, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsNitro, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsNitro->setText(QString::number(value));
        SaveManager::setItem(Save::Item::MAGICAL_NITRO, value);
    });

    // LineEditHelper::setup(ui->leItemsMandragora, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Item::ITEM_ID_MANDRAGORA, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsMandragora, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsMandragora->setText(QString::number(value));
        SaveManager::setItem(Save::Item::MANDRAGORA, value);
    });

    // Keys
    CheckBox::setup(
        m_ui->chbScienceKey1,
        [] { SaveManager::setItem(Save::Item::SCIENCE_KEY1, 1); },
        [] { SaveManager::setItem(Save::Item::SCIENCE_KEY1, 0); }
    );

    CheckBox::setup(
        m_ui->chbScienceKey2,
        [] { SaveManager::setItem(Save::Item::SCIENCE_KEY2, 1); },
        [] { SaveManager::setItem(Save::Item::SCIENCE_KEY2, 0); }
    );

    CheckBox::setup(
        m_ui->chbScienceKey3,
        [] { SaveManager::setItem(Save::Item::SCIENCE_KEY3, 1); },
        [] { SaveManager::setItem(Save::Item::SCIENCE_KEY3, 0); }
    );

    CheckBox::setup(
        m_ui->chbClocktowerKey1,
        [] { SaveManager::setItem(Save::Item::CLOCKTOWER_KEY1, 1); },
        [] { SaveManager::setItem(Save::Item::CLOCKTOWER_KEY1, 0); }
    );

    CheckBox::setup(
        m_ui->chbClocktowerKey2,
        [] { SaveManager::setItem(Save::Item::CLOCKTOWER_KEY2, 1); },
        [] { SaveManager::setItem(Save::Item::CLOCKTOWER_KEY2, 0); }
    );

    CheckBox::setup(
        m_ui->chbClocktowerKey3,
        [] { SaveManager::setItem(Save::Item::CLOCKTOWER_KEY3, 1); },
        [] { SaveManager::setItem(Save::Item::CLOCKTOWER_KEY3, 0); }
    );

    CheckBox::setup(
        m_ui->chbChamberKey,
        [] { SaveManager::setItem(Save::Item::CHAMBER_KEY, 1); },
        [] { SaveManager::setItem(Save::Item::CHAMBER_KEY, 0); }
    );

    CheckBox::setup(
        m_ui->chbCopperKey,
        [] { SaveManager::setItem(Save::Item::COPPER_KEY, 1); },
        [] { SaveManager::setItem(Save::Item::COPPER_KEY, 0); }
    );

    CheckBox::setup(
        m_ui->chbExecutionKey,
        [] { SaveManager::setItem(Save::Item::EXECUTION_KEY, 1); },
        [] { SaveManager::setItem(Save::Item::EXECUTION_KEY, 0); }
    );

    CheckBox::setup(
        m_ui->chbGardenKey,
        [] { SaveManager::setItem(Save::Item::GARDEN_KEY, 1); },
        [] { SaveManager::setItem(Save::Item::GARDEN_KEY, 0); }
    );

    CheckBox::setup(
        m_ui->chbLeftTowerKey,
        [] { SaveManager::setItem(Save::Item::LEFT_TOWER_KEY, 1); },
        [] { SaveManager::setItem(Save::Item::LEFT_TOWER_KEY, 0); }
    );

    CheckBox::setup(
        m_ui->chbArchivesKey,
        [] { SaveManager::setItem(Save::Item::ARCHIVES_KEY, 1); },
        [] { SaveManager::setItem(Save::Item::ARCHIVES_KEY, 0); }
    );

    CheckBox::setup(
        m_ui->chbStoreroomKey,
        [] { SaveManager::setItem(Save::Item::STOREROOM_KEY, 1); },
        [] { SaveManager::setItem(Save::Item::STOREROOM_KEY, 0); }
    );

    // Unused items
    // LineEditHelper::setup(ui->leItemsER, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Item::ITEM_ID_ENGAGEMENT_RING, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsER, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsER->setText(QString::number(value));
        SaveManager::setItem(Save::Item::ENGAGEMENT_RING, value);
    });

    // LineEditHelper::setup(ui->leItemsIG, 0, 1,
    //     [](std::uint8_t value) {
    //         SaveManager::getInstance()->setItem(Save::Item::ITEM_ID_INCANDESCENT_GAZE, value);
    //     }
    // );
    LineEdit::setup(m_ui->leItemsIG, QString::number(0), validator, [this](const QString &text) {
        const auto value = LineEdit::handleUnsignedInteger<std::uint8_t>(text, 0, 1);
        m_ui->leItemsIG->setText(QString::number(value));
        SaveManager::setItem(Save::Item::INCANDESCENT_GAZE, value);
    });
}

void ItemsForm::populate(Save::Data *saveData) const
{
    if (saveData == nullptr) {
        return;
    }

    const auto *inst = SaveManager::getInstance();

    m_ui->chbSpecial1->setChecked(saveData->getItem(Save::Item::SPECIAL1) > 0);
    m_ui->chbSpecial2->setChecked(saveData->getItem(Save::Item::SPECIAL2) > 0);

    // if (inst->getRegion() == Save::Region::PAL || inst->getRegion() == Save::Region::JPN) {
    //     m_ui->leItemsSpecial3->setText(QString::number(saveData->getItem(Save::Item::SPECIAL3)));
    // } else {
    //     m_ui->leItemsSpecial3->setText("0");
    // }
    m_ui->chbSpecial3->setChecked(
        (inst->getRegion() == Save::Region::PAL || inst->getRegion() == Save::Region::JPN) &&
        saveData->getItem(Save::Item::SPECIAL3) > 0
    );

    m_ui->leItemsRoastChicken->setText(QString::number(saveData->getItem(actualItemId(inst, Save::Item::ROAST_CHICKEN))));
    m_ui->leItemsRoastBeef->setText(QString::number(saveData->getItem(actualItemId(inst, Save::Item::ROAST_BEEF))));
    m_ui->leItemsHealingKit->setText(QString::number(saveData->getItem(actualItemId(inst, Save::Item::HEALING_KIT))));
    m_ui->leItemsPurifying->setText(QString::number(saveData->getItem(actualItemId(inst, Save::Item::PURIFYING))));
    m_ui->leItemsCureAmpoule->setText(QString::number(saveData->getItem(actualItemId(inst, Save::Item::CURE_AMPOULE))));

    if (inst->getRegion() == Save::Region::USA) {
        m_ui->leItemsPoutPourri->setText(QString::number(saveData->getItem(Save::Item::POUT_POURRI)));
    } else {
        m_ui->leItemsPoutPourri->setText("0");
    }

    m_ui->leItemsSunCard->setText(QString::number(saveData->getItem(Save::Item::SUN_CARD)));
    m_ui->leItemsMoonCard->setText(QString::number(saveData->getItem(Save::Item::MOON_CARD)));
    m_ui->leItemsNitro->setText(QString::number(saveData->getItem(Save::Item::MAGICAL_NITRO)));
    m_ui->leItemsMandragora->setText(QString::number(saveData->getItem(Save::Item::MANDRAGORA)));
    m_ui->chbArchivesKey->setChecked(saveData->getItem(Save::Item::ARCHIVES_KEY) > 0);
    m_ui->chbLeftTowerKey->setChecked(saveData->getItem(Save::Item::LEFT_TOWER_KEY) > 0);
    m_ui->chbStoreroomKey->setChecked(saveData->getItem(Save::Item::STOREROOM_KEY) > 0);
    m_ui->chbGardenKey->setChecked(saveData->getItem(Save::Item::GARDEN_KEY) > 0);
    m_ui->chbCopperKey->setChecked(saveData->getItem(Save::Item::COPPER_KEY) > 0);
    m_ui->chbChamberKey->setChecked(saveData->getItem(Save::Item::CHAMBER_KEY) > 0);
    m_ui->chbExecutionKey->setChecked(saveData->getItem(Save::Item::EXECUTION_KEY) > 0);
    m_ui->chbScienceKey1->setChecked(saveData->getItem(Save::Item::SCIENCE_KEY1) > 0);
    m_ui->chbScienceKey2->setChecked(saveData->getItem(Save::Item::SCIENCE_KEY2) > 0);
    m_ui->chbScienceKey3->setChecked(saveData->getItem(Save::Item::SCIENCE_KEY3) > 0);
    m_ui->chbClocktowerKey1->setChecked(saveData->getItem(Save::Item::CLOCKTOWER_KEY1) > 0);
    m_ui->chbClocktowerKey2->setChecked(saveData->getItem(Save::Item::CLOCKTOWER_KEY2) > 0);
    m_ui->chbClocktowerKey3->setChecked(saveData->getItem(Save::Item::CLOCKTOWER_KEY3) > 0);
    m_ui->leItemsER->setText(QString::number(saveData->getItem(Save::Item::ENGAGEMENT_RING)));
    m_ui->leItemsIG->setText(QString::number(saveData->getItem(Save::Item::INCANDESCENT_GAZE)));
}
