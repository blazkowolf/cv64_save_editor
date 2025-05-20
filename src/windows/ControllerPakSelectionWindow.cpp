/**
 * @file ControllerPakSelectionWindow.cpp
 * @brief ControllerPakSelectionWindow class source code file
 *
 * This file contains the source code for the Controller Pak save selection window
 * (shown when opening a Controller Pak-formatted file)
 *
 * @author 
 */

#include "../../include/windows/ControllerPakSelectionWindow.h"
#include "file/FileManager.h"
#include <QPushButton>

ControllerPakSelectionWindow::ControllerPakSelectionWindow(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::ControllerPakSelectionWindow)
{
    m_ui->setupUi(this);

    // Make sure to only set this window up if we're working with Controller Pak or DexDrive saves
    if (((FileManager::getInstance()->getFileFormat() == FileManager::FORMAT_CONTROLLERPAK) || (FileManager::getInstance()->getFileFormat() == FileManager::FORMAT_DEXDRIVE))
        && (FileManager::getInstance()->getLoader() != nullptr)) {
        setupButtonBox();
    }
}

ControllerPakSelectionWindow::~ControllerPakSelectionWindow()
{
    delete m_ui;
}

QString ControllerPakSelectionWindow::getRegionName(const std::int16_t region) const {
    switch (region) {
        default:
        case Save::USA:
            return "USA";

        case Save::JPN:
            return "JPN";

        case Save::PAL:
            return "PAL";
    }
}

/**
 * @brief Setup the list containing each button corresponding to each save file.
 */
void ControllerPakSelectionWindow::setupButtonBox() {
    // Get the Controller Pak Castlevania 64 save array
    const auto* saveArray = FileManager::getInstance()->getControllerPakNoteTableDataArray();

    for (std::uint32_t i = 0; i < saveArray->size(); i++) {
        std::int32_t index = (*saveArray)[i].index;
        if (index == -1) {
            continue;
        }

        std::int16_t region = (*saveArray)[i].region;

        QString buttonText = "Save " + QString::number(index + 1) + "\n" +
                             getRegionName(region);

        QPushButton* button = new QPushButton(buttonText);
        button->setFixedWidth(500);
        m_ui->buttonBox->addButton(button, QDialogButtonBox::ActionRole);

        connect(button, &QPushButton::clicked, this, [this, index]() {
            onButtonClicked(index);
        });
    }
}

/**
 * @brief Runs when clicking one of the save list buttons.
 */
void ControllerPakSelectionWindow::onButtonClicked(std::int32_t saveIndex) {
    // Set the save index needed for knowing what save file to load
    // (see FileLoaderControllerPak::getRawDataOffsetStart())
    FileManager::getInstance()->setControllerPakCurrentlySelectedSaveIndex(saveIndex);

    // Make sure we return QDialog::Accepted upon exiting the window in order to tell FileManager that we can continue loading the file
    // (see closeEvent() for the opposite case, where X is pressed to exit the window instead)
    accept();
}
