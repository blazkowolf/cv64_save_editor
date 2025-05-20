#include "windows/eventflags.h"

#include "CheckBoxHelper.h"
#include "ui_eventflags.h"
#include "save/SaveManager.h"

EventFlagsForm::EventFlagsForm(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::EventFlagsForm)
{
    m_ui->setupUi(this);
}

EventFlagsForm::~EventFlagsForm()
{
    delete m_ui;
}

/**
 * @brief Creates the event flag grid dynamically.
 */
template <typename TTarget>
QLineEdit* createGridFlag(SaveManager *instance, TTarget *target, QGridLayout* gridLayout, std::int32_t flagSet, std::uint32_t flags) {
    auto* hexBitflagDisplay = new QLineEdit();
    hexBitflagDisplay->setAlignment(Qt::AlignRight);
    hexBitflagDisplay->setText(QString("%1").arg(flags, 1, 10, QChar('0')));

    /// Ensure that we're putting "hexBitflagDisplay" in the right most part of the checkboxes, on the 1st row, 8th column
    /// @note We also add an extra row and column for printing the column / row number
    gridLayout->addWidget(hexBitflagDisplay, 0, 9, 5, 1);
    // Add numbers on top and to the right showing the column / row number respectively
    for (std::uint32_t i = 0; i < 8; ++i) {
        auto* colLabel = new QLabel(QString::number(7 - i));
        colLabel->setAlignment(Qt::AlignCenter);  // Center the row numbers
        gridLayout->addWidget(colLabel, 0, i + 1);
    }

    for (std::uint32_t i = 0; i < 4; ++i) {
        auto* rowLabel = new QLabel(QString::number(i));
        rowLabel->setAlignment(Qt::AlignCenter);  // Center the row numbers
        gridLayout->addWidget(rowLabel, 4 - i, 0);
    }

    QVector<QCheckBox*> checkBoxes(32);

    // Create 32 checkboxes (one for each bit)
    for (std::uint32_t i = 0; i < 32; ++i) {
        auto* checkBox = new QCheckBox();
        // Set the checked state based on the flag value
        checkBox->setChecked(flags & (1 << i));
        // Add the checkbox to the grid layout. Then place it in a 4x8 grid
        // We add +1 so that we don't print the checkboxes in the same row / column as the numbers
        std::int32_t row = 3 - (i / 8);
        std::int32_t col = 8 - (i % 8);
        gridLayout->addWidget(checkBox, row + 1, col);

        checkBoxes[i] = checkBox;
    }

    // Since now each checkbox is initialized, we can go ahead and connect them + add the function to handle them when toggled
    for (std::uint32_t j = 0; j < 32; j++) {
        // Make sure that each checkbox is updated *on-the-fly* as we edit the hex value from the line edit
        // To do so, we directly define a lambda function that does target for us. This is executed when pressing any of the checkboxes
        QObject::connect(checkBoxes[j], &QCheckBox::toggled, target, [checkBoxes, hexBitflagDisplay]() {
            std::uint32_t updatedFlags = 0;
            for (std::int32_t m = 0; m < 32; ++m) {
                if (checkBoxes[m]->isChecked()) {
                    updatedFlags |= (1 << m);
                }
            }
            hexBitflagDisplay->setText(QString("%1").arg(updatedFlags, 1, 10, QChar('0')));
        });
    }

    // Lastly, we connect the "hexBitflagDisplay" and add a handling function that will update all
    // checkboxes depending on the hex bitflag value passed in the "hexBitflagDisplay" line edit
    QObject::connect(hexBitflagDisplay, &QLineEdit::textChanged, target, [instance, checkBoxes, hexBitflagDisplay, flagSet](const QString& text) {
        bool ok = false;
        std::uint32_t newFlags = text.toUInt(&ok, 10);

        instance->setEventFlags(flagSet, newFlags);

        // Ensure we limit the input value up to 0xFFFFFFFF
        if (ok && newFlags <= 0xFFFFFFFF) {
            for (std::int32_t k = 0; k < 32; ++k) {
                checkBoxes[k]->setChecked(newFlags & (1 << k));
            }
        }
        else {
            hexBitflagDisplay->setText("0");
        }
    });

    // We return "hexBitflagDisplay" so that we can access to it later for changing the event flag values by editing the lineEdit
    return hexBitflagDisplay;
}

void EventFlagsForm::setup()
{
    auto *inst = SaveManager::getInstance();

    /* Page 1 */
    m_ui->labelSet0->setText("Set 0 (Forest of Silence, Intro Narration Map, Test Grid)");
    m_hexBitflagLineEdits[0] = createGridFlag(inst, this, m_ui->gridFlagSet0, 0, 0);

    m_ui->labelSet1->setText("Set 1 (Villa Foyer, Villa Hallway)");
    m_hexBitflagLineEdits[1] = createGridFlag(inst, this, m_ui->gridFlagSet1, 1, 0);

    m_ui->labelSet2->setText("Set 2 (Underground Waterway, Castle Center - Top elevator room)");
    m_hexBitflagLineEdits[2] = createGridFlag(inst, this, m_ui->gridFlagSet2, 2, 0);

    /* Page 2 */
    m_ui->labelSet3->setText("Set 3 (Castle Center - Friendly lizard man, Castle Center - Nitro room)");
    m_hexBitflagLineEdits[3] = createGridFlag(inst, this, m_ui->gridFlagSet3, 3, 0);

    m_ui->labelSet4->setText("Set 4 (Tower of Execution, Tower of Sorcery, Duel Tower)");
    m_hexBitflagLineEdits[4] = createGridFlag(inst, this, m_ui->gridFlagSet4, 4, 0);

    m_ui->labelSet5->setText("Set 5 (Castle Keep - Stairs, Castle Keep, Clock Tower)");
    m_hexBitflagLineEdits[5] = createGridFlag(inst, this, m_ui->gridFlagSet5, 5, 0);

    /* Page 3 */
    m_ui->labelSet6->setText("Set 6 (Dracula Desert, Rose / Actriese room, Room of Clocks)");
    m_hexBitflagLineEdits[6] = createGridFlag(inst, this, m_ui->gridFlagSet6, 6, 0);

    m_ui->labelSet7->setText("Set 7 (Tower of Science - Turrets)");
    m_hexBitflagLineEdits[7] = createGridFlag(inst, this, m_ui->gridFlagSet7, 7, 0);

    m_ui->labelSet8->setText("Set 8 (Castle Center - Bottom Elevator, Castle Center - Gears room)");
    m_hexBitflagLineEdits[8] = createGridFlag(inst, this, m_ui->gridFlagSet8, 8, 0);

    /* Page 4 */
    m_ui->labelSet9->setText("Set 9 (Villa - Front Yard)");
    m_hexBitflagLineEdits[9] = createGridFlag(inst, this, m_ui->gridFlagSet9, 9, 0);

    m_ui->labelSet10->setText("Set 10 (Castle Wall - Main)");
    m_hexBitflagLineEdits[10] = createGridFlag(inst, this, m_ui->gridFlagSet10, 10, 0);

    m_ui->labelSet11->setText("Set 11 (Maze Garden, Castle Center - Library)");
    m_hexBitflagLineEdits[11] = createGridFlag(inst, this, m_ui->gridFlagSet11, 11, 0);

    /* Page 5 */
    m_ui->labelSet12->setText("Set 12 (Tunnel)");
    m_hexBitflagLineEdits[12] = createGridFlag(inst, this, m_ui->gridFlagSet12, 12, 0);

    m_ui->labelSet13->setText("Set 13 (Castle Center - Main)");
    m_hexBitflagLineEdits[13] = createGridFlag(inst, this, m_ui->gridFlagSet13, 13, 0);

    m_ui->labelSet14->setText("Set 14 (Castle Wall - Towers)");
    m_hexBitflagLineEdits[14] = createGridFlag(inst, this, m_ui->gridFlagSet14, 14, 0);

    /* Page 6 */
    m_ui->labelSet15->setText("Set 15 (Tower of Science)");
    m_hexBitflagLineEdits[15] = createGridFlag(inst, this, m_ui->gridFlagSet15, 15, 0);


    // Initialize pages and the buttons that travel to those pages
    // When each button is pressed, "onPageButtonClicked" will be called passing
    // the desired page by arguments
    QObject::connect(m_ui->rbEventFlagPage1, &QRadioButton::clicked, this, [this]() {
        m_ui->stackWidgetEventFlagsPages->setCurrentWidget(m_ui->EventFlagsPage1);
    });

    QObject::connect(m_ui->rbEventFlagPage2, &QRadioButton::clicked, this, [this]() {
        m_ui->stackWidgetEventFlagsPages->setCurrentWidget(m_ui->EventFlagsPage2);
    });

    QObject::connect(m_ui->rbEventFlagPage3, &QRadioButton::clicked, this, [this]() {
        m_ui->stackWidgetEventFlagsPages->setCurrentWidget(m_ui->EventFlagsPage3);
    });

    QObject::connect(m_ui->rbEventFlagPage4, &QRadioButton::clicked, this, [this]() {
        m_ui->stackWidgetEventFlagsPages->setCurrentWidget(m_ui->EventFlagsPage4);
    });

    QObject::connect(m_ui->rbEventFlagPage5, &QRadioButton::clicked, this, [this]() {
        m_ui->stackWidgetEventFlagsPages->setCurrentWidget(m_ui->EventFlagsPage5);
    });

    QObject::connect(m_ui->rbEventFlagPage6, &QRadioButton::clicked, this, [this]() {
        m_ui->stackWidgetEventFlagsPages->setCurrentWidget(m_ui->EventFlagsPage6);
    });

    m_ui->stackWidgetEventFlagsPages->setCurrentWidget(m_ui->EventFlagsPage1);
}

void EventFlagsForm::populate(SaveData *saveData) const
{
    if (saveData == nullptr) {
        return;
    }
    // Event flag grids. We edit each of the line edits associated to the event flags to assign the hex value gotten
    // from the save data. Then, the checkboxes will be ticked / unticked automatically
    for (unsigned int i = 0; i < Save::NUM_EVENT_FLAGS; i++) {
        m_hexBitflagLineEdits[i]->setText(QString::number(saveData->getEventFlags(i)));
    }
}
