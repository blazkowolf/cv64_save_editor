#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file MainWindow.h
 * @brief MainWindow header file
 *
 * @author 
 */

#include "ui_MainWindow.h"
#include "bit.h"
#include "save/Save.h"
#include "windows/ComboBoxData.h"
#include "windows/eventflags.h"
#include "windows/general.h"
#include "windows/items.h"

#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <QSettings>        // QSettings

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Main window
 *
 * The application's main window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* instance;

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    /**
     * @brief With this struct, we can keep track of the components inside the "Slot" menu option
     */
    struct SlotMenu {
        QMenu* slotOption;
        QAction* mainSaveOption;
        QAction* beginningOfStageSaveOption;
    };

    void populateMainWindow(SaveData* save) const;
    void updateSlotMenuCheckedState(std::int32_t selectedSlotIndex, bool isMainSave);

private slots:
    // Setup functions
    void setupFileMenu();
    void setupSlotMenu();
    void setupEditMenu();

    // Interface event handling functions
    void fileOpenMenu();
    void fileSaveMenu();
    void fileSaveAsMenu();
    void openFile(const QString& filename);
    void onCopy(QWidget* parent);
    void onDelete();
    void onDeleteAll();

    // Helper functions
    // void checkMandragoraAndNitroLineEdits();
    void enableUIComponents(bool);
    // void updateCheckboxEnabledVisibility() const;
    void updateWindowVisibility(bool);
    // void updateBitSelection(std::uint32_t newValue, const Ui::ComboBoxData& comboBoxData);

    // Inline getters and setters
    void setSelectedSave(const std::int32_t slot) {
        selectedSlot = slot;
    }

    [[nodiscard]] std::int32_t getSelectedSave() const {
        return selectedSlot;
    }

    void setIsMain(const bool isMain_) {
        isMain = isMain_;
    }

    [[nodiscard]] bool getIsMain() const {
        return isMain;
    }

private:
    Ui::MainWindow* ui;

    GeneralForm *pageGeneral;
    ItemsForm *pageItems;
    EventFlagsForm *pageEventFlags;

    /**< The currently-selected save slot */
    std::int32_t selectedSlot = 0;
    /**< If true, the "Main" save is selected. Otherwise, the "Beginning of Stage" save is selected. */
    bool isMain = true;

    /**< The options found in the "Slot" menu */
    SlotMenu slotMenuOptions[4] = {};

};

#endif // MAINWINDOW_H
