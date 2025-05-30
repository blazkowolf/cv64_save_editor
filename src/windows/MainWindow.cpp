/**
 * @file MainWindow.cpp
 * @brief Main window source code file
 *
 * This file contains the source code for the main window of the application
 * (the first window that opens up when booting the application).
 *
 * @author 
 */

#include "windows/MainWindow.h"
#include "util/combobox.h"
#include "save/Save.h"
#include "save/SaveManager.h"
#include "file/FileManager.h"

#include <QIntValidator>    // With "QIntValidator", we can validate the contents of an integer (see "handleNumberOnlyInput()")
#include <QtGlobal>         // qBound()
#include <climits>          // SHRT_MAX, UINT_MAX, etc
#include <QMessageBox>      // QMessageBox
#include <QDir>             // QDir
#include <QFileDialog>      // QFileDialog
#include <QSpinBox>         // QSpinBox
#include <QLineEdit>

// Static instance for this window. We use this to access this window's functions in some parts of the code
MainWindow* MainWindow::m_instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_pageGeneral(new GeneralForm)
    , m_pageItems(new ItemsForm)
    , m_pageEventFlags(new EventFlagsForm)
{
    m_instance = this;

    m_ui->setupUi(this);

    // Avoid being able to maximize the window, as the layout looks worse
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // Initialize pages
    m_ui->stackedWidgetPages->addWidget(m_pageGeneral);
    m_ui->stackedWidgetPages->addWidget(m_pageItems);
    m_ui->stackedWidgetPages->addWidget(m_pageEventFlags);

    m_pageGeneral->setup();
    m_pageItems->setup();
    m_pageEventFlags->setup();

    // Initialize pages and the buttons that travel to those pages
    // When each button is pressed, "onPageButtonClicked" will be called passing
    // the desired page by arguments
    QObject::connect(m_ui->buttonMain, &QPushButton::clicked, this, [this]() {
        m_ui->stackedWidgetPages->setCurrentWidget(m_pageGeneral);
    });

    QObject::connect(m_ui->buttonItems, &QPushButton::clicked, this, [this]() {
        m_ui->stackedWidgetPages->setCurrentWidget(m_pageItems);
    });

    QObject::connect(m_ui->buttonEventFlags, &QPushButton::clicked, this, [this]() {
        m_ui->stackedWidgetPages->setCurrentWidget(m_pageEventFlags);
    });

    // Initialize toolbar options
    setupFileMenu();
    setupSlotMenu();
    setupEditMenu();

    // Set default values to the savegame at boot
    SaveManager::getInstance()->clear();
    SaveManager::getInstance()->setRegion(Save::Region::USA);
    // ui->leItemsSpecial3->setEnabled(false);
    // ui->leItemsPoutPourri->setEnabled(true);

    // Ensure that we start in the "Main" page
    m_ui->stackedWidgetPages->setCurrentWidget(m_pageGeneral);

    // Uncheck the "save enabled checkbox" when opening the program
    // enableUIComponents(false);
    // ui->cboxEnabled->setChecked(false);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    m_instance = nullptr;
    delete m_pageGeneral;
    delete m_pageItems;
    delete m_pageEventFlags;
}

/**
 * @brief Given a save data struct, fill all the UI components with the data from the save.
 */
void MainWindow::populateMainWindow(Save::Data* saveData) const
{
    if (saveData == nullptr) {
        return;
    }
    m_pageGeneral->populate(saveData);
    m_pageItems->populate(saveData);
    m_pageEventFlags->populate(saveData);
}

void MainWindow::openFile(const QString& filename)
{
    std::int32_t result = FileManager::getInstance()->openFile(filename);

    if (result == -1) {
        QMessageBox::critical(this, "Error", "Couldn't open file.");
        return;
    }

    // Populate with the currently-selected save slot.
    populateMainWindow(&SaveManager::getInstance()->getCurrentSave());

    /// Set default Slot option to the currently selected save.
    /// @note We must call this function after calling "populateMainWindow" in order to have the checkboxes
    /// ready. Otherwise the program will throw SIGSEV.
    updateSlotMenuCheckedState(SaveManager::getInstance()->m_currentSave, SaveManager::getInstance()->m_isMain);
}

void MainWindow::fileOpenMenu()
{
    // With these settings, we can obtain the last opened save directory
    QSettings settings("CV64SaveEditor", "Castlevania 64 Save Editor");

    // Retrieve the last opened file path
    const auto lastOpenedDir = settings.value("lastOpenedDir", QDir::homePath()).toString();

    // Open file menu in the last opened directory by default
    const auto filename = QFileDialog::getOpenFileName(
        this,
        "Open File",
        lastOpenedDir,
        "All accepted filetypes (*.mpk *.pak *.note *.eep *.n64 *.t64);;"
        "Individual note (*.note);;"
        "Controller Pak data (*.mpk *.pak);;"
        "Cartridge (Japanese version only) (*.eep);;"
        "DexDrive saves (*.n64 *.t64);;"
        "All Files (*)"
    );

    if (!filename.isEmpty()) {
        openFile(filename);

        /// Store the directory of the opened file
        /// @note If on Linux, the settings are saved at
        /// ~/.config/CV64SaveEditor/Castlevania 64 Save Editor.conf
        /// In Windows, the dir is stored at this registry:
        /// HKEY_CURRENT_USER\Software\CV64SaveEditor\Castlevania 64 Save Editor
        QFileInfo fileInfo(filename);
        settings.setValue("lastOpenedDir", fileInfo.absolutePath());
    }
}

void MainWindow::fileSaveMenu()
{
    if (!FileManager::getInstance()->wasFileOpened()) {
        QMessageBox::critical(this, "Error", "Open a file in local before trying to save.");
        return;
    }

    /// @note Scrapping this since we need to save empty saves in order to save New Game+ files.
    /*
    if (SaveManager::getInstance()->areAllSavesDisabled()) {
        QMessageBox::critical(this, "Error", "This save is empty, so it can't be saved.");
        return;
    }
*/

    std::int32_t result = FileManager::getInstance()->writeFile(FileManager::getInstance()->getFilepath(), false);

    switch (result) {
        case -1:
            QMessageBox::critical(this, "Error", "File could not be saved.\n"
                                                 "Make sure to save it as one of the accepted filetypes.");
            return;

        case -2:
            QMessageBox::critical(this, "Error", "Make sure that at least one save is enabled before saving.\n");
            return;
    }

    QMessageBox::information(this, "Save", "Saved successfully");
}

void MainWindow::fileSaveAsMenu()
{
    /// @note Scrapping this since we need to save empty saves in order to save New Game+ files.
    /*
    if (SaveManager::getInstance()->areAllSavesDisabled()) {
        QMessageBox::critical(this, "Error", "This save is empty, so it can't be saved.");
        return;
    }
*/

    // Retrieve the last "Save As..." directory
    QSettings settings("CV64SaveEditor", "Castlevania 64 Save Editor");
    const auto lastSaveAsDirectory = settings.value("lastSaveDir", QDir::homePath()).toString();

    const auto filepath = QFileDialog::getSaveFileName(
        this,
        "Save As...",
        lastSaveAsDirectory,
        "Individual note (*.note);;"
        "Cartridge (Japanese version only) (*.eep)"
    );

    if (!filepath.isEmpty()) {
        std::int32_t result = FileManager::getInstance()->writeFile(filepath, true);

        switch (result) {
            case -1:
                QMessageBox::critical(this, "Error", "File could not be saved.\n"
                                                     "Make sure to save it as one of the accepted filetypes.");
                return;

            case -2:
                QMessageBox::critical(this, "Error", "Make sure that at least one save is enabled before saving.\n");
                return;
        }
    }
    else {
        return;
    }

    /// Store the directory of the saved file
    /// @note If on Linux, the settings are saved at
    /// ~/.config/CV64SaveEditor/Castlevania 64 Save Editor.conf
    /// In Windows, the dir is stored at this registry:
    /// HKEY_CURRENT_USER\Software\CV64SaveEditor\Castlevania 64 Save Editor
    const QFileInfo fileInfo(filepath);
    settings.setValue("lastSaveDir", fileInfo.absolutePath());
    QMessageBox::information(this, "Save", "Saved successfully");
}

void MainWindow::setupFileMenu()
{
    // Setup the "Open" button
    connect(m_ui->actionOpenFile, &QAction::triggered, this, &MainWindow::fileOpenMenu);

    // Setup the "Save" button
    connect(m_ui->actionSave, &QAction::triggered, this, &MainWindow::fileSaveMenu);

    // Setup the "Save As..." button
    connect(m_ui->actionSave_As, &QAction::triggered, this, &MainWindow::fileSaveAsMenu);

    // Setup the "Exit" button
    connect(m_ui->actionExit, &QAction::triggered, this, []() {
        if (const auto reply = QMessageBox::question(nullptr, "Exit", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No); reply == QMessageBox::Yes) {
            QApplication::exit();
        }
    });
}

void MainWindow::setupSlotMenu()
{
    QMenu* menuSlot = menuBar()->addMenu("Slot");
    menuSlot->setObjectName("Slot");

    for (std::int32_t i = 0; i < Save::NUM_SAVES; ++i) {
        // Create a submenu for "Slot X"
        m_slotMenuOptions[i].slotOption = new QMenu(QString("Slot %1").arg(i + 1), this);
        menuSlot->addMenu(m_slotMenuOptions[i].slotOption);
        m_slotMenuOptions[i].slotOption->setObjectName(QString("Slot %1").arg(i + 1));

        // Create "Main" action inside the Slot X menu
        m_slotMenuOptions[i].mainSaveOption = new QAction("Main", this);
        m_slotMenuOptions[i].mainSaveOption->setCheckable(true);
        m_slotMenuOptions[i].slotOption->addAction(m_slotMenuOptions[i].mainSaveOption);
        connect(m_slotMenuOptions[i].mainSaveOption, &QAction::triggered, this, [this, i]() {
            m_selectedSlot = i;
            m_isMain = true;
            updateSlotMenuCheckedState(i, true);
            populateMainWindow(&SaveManager::getInstance()->getSaveSlot(i).mainSave);
            updateWindowVisibility(BITS_HAS(SaveManager::getInstance()->getCurrentSaveSlot().mainSave.flags, Save::SAVE_FLAG_ACTIVE));
        });

        // Create "Beginning of Stage" action inside the Slot X menu
        m_slotMenuOptions[i].beginningOfStageSaveOption = new QAction("Beginning of Stage", this);
        m_slotMenuOptions[i].beginningOfStageSaveOption->setCheckable(true);
        m_slotMenuOptions[i].slotOption->addAction(m_slotMenuOptions[i].beginningOfStageSaveOption);
        connect(m_slotMenuOptions[i].beginningOfStageSaveOption, &QAction::triggered, this, [this, i]() {
            m_selectedSlot = i;
            m_isMain = false;
            updateSlotMenuCheckedState(i, false);
            populateMainWindow(&SaveManager::getInstance()->getSaveSlot(i).beginningOfStage);
            /// @note For enabling / disabling the interface, we only look at the active flag from "mainSave", NOT the one in "beginningOfStage"
            updateWindowVisibility(BITS_HAS(SaveManager::getInstance()->getCurrentSaveSlot().mainSave.flags, Save::SAVE_FLAG_ACTIVE));
        });
    }

    /// Set default Slot option to Slot 1 -> Main.
    /// @note We must call this function after calling "populateMainWindow" in order to have the checkboxes
    /// ready. Otherwise the program will throw SIGSEV.
    updateSlotMenuCheckedState(0, true);
}

/// When clicking on a slot option, check it, and *also uncheck* any other unselected options
/// This is done for the "Main" and "Beginning of Stage" slot menu options
void MainWindow::updateSlotMenuCheckedState(std::int32_t selectedSlotIndex, bool isMainSave)
{
    SaveManager* saveManager = SaveManager::getInstance();

    for (std::uint32_t i = 0; i < Save::NUM_SAVES; ++i) {
        m_slotMenuOptions[i].mainSaveOption->setChecked(i == selectedSlotIndex && isMainSave);
        m_slotMenuOptions[i].beginningOfStageSaveOption->setChecked(i == selectedSlotIndex && !isMainSave);
    }

    saveManager->m_isMain = isMainSave;
    saveManager->m_currentSave = selectedSlotIndex;
}

void MainWindow::setupEditMenu()
{
    connect(m_ui->actionCopy, &QAction::triggered, this, [this]() {
        onCopy(this);
    });
    connect(m_ui->actionDelete, &QAction::triggered, this, &MainWindow::onDelete);
    connect(m_ui->actionDelete_All, &QAction::triggered, this, &MainWindow::onDeleteAll);
}

/// The player can only have a Mandragora *OR* a Magical Nitro at the same time.
/// This function checks if both Mandragora and Nitro have an amount larger than 0 at the same time.
/// If so, set the amount for both items back to 0
// void MainWindow::checkMandragoraAndNitroLineEdits() {
//     QLineEdit* mandragoraLineEdit = ui->leItemsMandragora;
//     QLineEdit* nitroLineEdit = ui->leItemsNitro;
//
//     bool okMandragora = false;
//     bool okNitro = false;
//
//     if (mandragoraLineEdit->text().toUInt(&okMandragora, 10) != 0 && nitroLineEdit->text().toUInt(&okNitro, 10) != 0) {
//         mandragoraLineEdit->setText(QString::number(0));
//         nitroLineEdit->setText(QString::number(0));
//     }
// }

void MainWindow::enableUIComponents(bool enable)
{
    // This function is now scrapped as it sometimes is necessary to edit a disabled save
    // (fo example, to activate New Game+)
    return;
/*
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    QMenu* menuSlot = menuBar()->findChild<QMenu*>("Slot");

    // Iterate over menuSlot's actions to find "Slot X" submenus.
    // We put these on a list so that later we can just enable them all at once (see the next loop)
    QList<QMenu*> slotSubMenus;
    for (QAction* action: menuSlot->actions()) {
        if (QMenu* submenu = action->menu()) {
            slotSubMenus.append(submenu);
        }
    }

    for (QWidget* widget: widgets) {
        // Skip essential components.
        // Also ensure that the language doesn't get enabled the first time a USA or JPN save is loaded
        if (widget == ui->cboxEnabled || widget == ui->menuBar || widget == ui->menuFile ||
            widget == menuSlot || slotSubMenus.contains(qobject_cast<QMenu*>(widget)) ||
            widget == ui->cbLanguage) {
            continue;
        }

        widget->setEnabled(enable);
    }
*/
}

/// This function ensures that the "Enabled" checkbox is only visible for "Main" saves
// void MainWindow::updateCheckboxEnabledVisibility() const
// {
//     if (!isMain) {
//         ui->cboxEnabled->hide();
//     }
//     else {
//         ui->cboxEnabled->show();
//     }
// }

/// Make sure to always have the "Beginning of Stage" save enabled only if the "Main" save is enabled
void MainWindow::updateWindowVisibility(bool enable)
{
//     if (BITS_HAS(SaveManager::getInstance()->getCurrentSaveSlot().mainSave.flags, Save::SAVE_FLAG_ACTIVE)
//         && !isMain) {
//         enableUIComponents(true);
//     }
//     else {
//         enableUIComponents(enable);
//     }
}

/**
 * @brief Copy the currently-opened save slot to another slot.
 */
void MainWindow::onCopy(QWidget* parent)
{
    SaveManager* saveManager = SaveManager::getInstance();
    // The save slot where the data will be copied over
    std::uint32_t destSaveSlot = 0;

    // Dynamically create the window
    QDialog dialog(parent);
    dialog.setWindowTitle("Copy");
    QVBoxLayout layout(&dialog);
    QLabel label("Select a save:", &dialog);
    layout.addWidget(&label);

    // Create the save slot ID selection spinbox
    QSpinBox spinBox(&dialog);
    spinBox.setRange(1, 4);
    layout.addWidget(&spinBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout.addWidget(&buttonBox);

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        destSaveSlot = spinBox.value() - 1;

        // If trying to copy the current save slot into an slot marked as "Enabled", then ask first if the user
        // wants to overwrite the data.
        if (BITS_HAS(saveManager->getSaveSlot(destSaveSlot).mainSave.flags, Save::SAVE_FLAG_ACTIVE)) {
            const auto reply = QMessageBox::question(nullptr, "Clear All", "An existing save exists on the destination slot\n"
                                                                                            "Do you want to replace it?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::No) {
                return;
            }
        }

        saveManager->setSaveSlot(saveManager->getCurrentSaveSlot(), destSaveSlot);
        populateMainWindow(&SaveManager::getInstance()->getCurrentSave());
    }
}

/**
 * @brief Clear a the currently opened save slot.
 */
void MainWindow::onDelete()
{
    if (const auto reply = QMessageBox::question(nullptr, "Clear", "Are you sure you want to clear the current save?", QMessageBox::Yes | QMessageBox::No); reply == QMessageBox::Yes) {
        SaveManager::getInstance()->getCurrentSaveSlot().clear();
        populateMainWindow(&SaveManager::getInstance()->getCurrentSave());
        updateWindowVisibility(BITS_HAS(SaveManager::getInstance()->getCurrentSaveSlot().mainSave.flags, Save::SAVE_FLAG_ACTIVE));
    }
}

/**
 * @brief Clear all save slots within the current save file.
 */
void MainWindow::onDeleteAll()
{
    if (const auto reply = QMessageBox::question(nullptr, "Clear All", "Are you sure you want to clear all saves?", QMessageBox::Yes | QMessageBox::No); reply == QMessageBox::Yes) {
        for (std::int32_t i = 0; i < Save::NUM_SAVES; i++) {
            SaveManager::getInstance()->getSaveSlot(i).clear();
            populateMainWindow(&SaveManager::getInstance()->getCurrentSave());
            updateWindowVisibility(BITS_HAS(SaveManager::getInstance()->getCurrentSaveSlot().mainSave.flags, Save::SAVE_FLAG_ACTIVE));
        }
    }
}
