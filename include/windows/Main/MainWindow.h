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

#include <QMainWindow>
#include <QSettings>        // QSettings

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Main window
 *
 * The application's main window
 */
class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* instance;

    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    /**
     * @brief With this struct, we can keep track of the components inside the "Slot" menu option
     */
    struct SlotMenu {
        QMenu* slotOption;
        QAction* mainSaveOption;
        QAction* beginningOfStageSaveOption;
    };

    void populateMainWindow(SaveData* save);
    void updateSlotMenuCheckedState(std::int32_t selectedSlotIndex, bool isMainSave);

private slots:
    // Setup functions
    void setupPageMain();
    void setupPageItems();
    void setupPageEventFlags();
    void setupFileMenu();
    void setupSlotMenu();
    void setupEditMenu();
    void handleNumberOnlyInputUnsigned(std::function<void(std::uint32_t)> setter, QLineEdit* lineEdit);
    void setupLineEditNumberUnsigned(QLineEdit* lineEdit, const std::uint32_t minValue, const std::uint32_t maxValue, std::function<void(std::uint32_t)> setter);
    void setupComboBoxBitflag(QComboBox* comboBox, const Ui::ComboBoxData& array);
    void setupCheckBox(QCheckBox* checkBox, std::uint32_t value, std::function<void(std::uint32_t)> setter, std::function<void(std::uint32_t)> unsetter);
    QLineEdit* createGridFlag(QGridLayout* gridLayout, std::int32_t flagSet, std::uint32_t flags);

    // Interface event handling functions
    void fileOpenMenu();
    void fileSaveMenu();
    void fileSaveAsMenu();
    void onPageButtonClicked(QStackedWidget* stackedWidget, const QWidget* page);
    void openFile(const QString& filename);
    void onCopy(QWidget* parent);
    void onDelete();
    void onDeleteAll();
    void handleComboBoxSelection(QComboBox* comboBox, const Ui::ComboBoxData& array);

    // Helper functions
    void switchPage(QStackedWidget* stackedWidgetPages, const QWidget* page);
    void checkMandragoraAndNitroLineEdits();
    void selectComboBoxOption(QComboBox& comboBox, const QVariant data);
    void enableUIComponents(bool);
    void updateCheckboxEnabledVisibility();
    void updateWindowVisibility(bool);
    void convertFrameToTime(const std::uint32_t frameCount, QLabel* output);
    void updateBitSelection(std::uint32_t newValue, const Ui::ComboBoxData& comboBoxData);

    // Inline getters and setters
    inline void setSelectedSave(const std::int32_t slot) {
        selectedSlot = slot;
    }

    inline std::int32_t getSelectedSave() const {
        return selectedSlot;
    }

    inline void setIsMain(const bool isMain_) {
        isMain = isMain_;
    }

    inline bool getIsMain() const {
        return isMain;
    }

private:
    Ui::MainWindow* ui;

    /**< The array of line edits that appear in the "Event Flags" page */
    QLineEdit* hexBitflagLineEdits[NUM_EVENT_FLAGS] = {};

    /**< The currently-selected save slot */
    std::int32_t selectedSlot = 0;
    /**< If true, the "Main" save is selected. Otherwise, the "Beginning of Stage" save is selected. */
    bool isMain = true;

    /**< The options found in the "Slot" menu */
    SlotMenu slotMenuOptions[4] = {};

    // Data for this window's combo boxes
    const Ui::ComboBoxData comboBoxDataMap = {
        {{"Forest of Silence", SaveData::MORI}},
        {{"Castle Wall (Towers)", SaveData::TOU}},
        {{"Castle Wall (Main)", SaveData::TOUOKUJI}},
        {{"Villa (Yard)", SaveData::NAKANIWA}},
        {{"Villa (Foyer)", SaveData::BEKKAN_1F}},
        {{"Villa (Hallway)", SaveData::BEKKAN_2F}},
        {{"Villa (Maze Garden)", SaveData::MEIRO_TEIEN}},
        {{"Tunnel", SaveData::CHIKA_KODO}},
        {{"Underground Waterway", SaveData::CHIKA_SUIRO}},
        {{"Castle Center (Main)", SaveData::HONMARU_B1F}},
        {{"Castle Center (Bottom Elevator)", SaveData::HONMARU_1F}},
        {{"Castle Center (Gears)", SaveData::HONMARU_2F}},
        {{"Castle Center (Friendly Lizard-man)", SaveData::HONMARU_3F_MINAMI}},
        {{"Castle Center (Library)", SaveData::HONMARU_4F_MINAMI}},
        {{"Castle Center (Nitro Room)", SaveData::HONMARU_3F_KITA}},
        {{"Castle Center (Top Elevator)", SaveData::HONMARU_5F}},
        {{"Tower of Execution", SaveData::SHOKEI_TOU}},
        {{"Tower of Sorcery", SaveData::MAHOU_TOU}},
        {{"Tower of Science", SaveData::KAGAKU_TOU}},
        {{"Duel Tower", SaveData::KETTOU_TOU}},
        {{"Castle Keep Stairs", SaveData::TURO_TOKEITOU}},
        {{"Castle Keep", SaveData::TENSHU}},
        {{"Intro Cutscene Map", SaveData::ENDING_DUMMY}},
        {{"Clock Tower", SaveData::TOKEITOU_NAI}},
        {{"Dracula Desert", SaveData::DRACULA}},
        {{"Rose / Actrice Fan Room", SaveData::ROSE}},
        {{"Villa (Vampire Crypt)", SaveData::BEKKAN_BOSS}},
        {{"Room of Clocks", SaveData::TOU_TURO}},
        {{"Ending Map", SaveData::ENDING}},
        {{"Test Grid", SaveData::TEST_GRID}}
    };

    const Ui::ComboBoxData comboBoxDataCharacter = {
        {{"Reinhardt", SaveData::REINHARDT}},
        {{"Carrie", SaveData::CARRIE}}
    };

    const Ui::ComboBoxData comboBoxDataButtonConfig = {
        {{"Type A", 0}},
        {{"Type B", 1}},
        {{"Type C", 2}}
    };

    const Ui::ComboBoxData comboBoxDataSoundMode = {
        {{"Stereo", 0}},
        {{"Monoaural", 1}}
    };

    const Ui::ComboBoxData comboBoxDataSubweapon = {
        {{"None", SaveData::SUBWEAPON_NONE}},
        {{"Knife", SaveData::SUBWEAPON_KNIFE}},
        {{"Holy Water", SaveData::SUBWEAPON_HOLY_WATER}},
        {{"Cross", SaveData::SUBWEAPON_CROSS}},
        {{"Axe", SaveData::SUBWEAPON_AXE}},
        {{"Wooden Stake", SaveData::SUBWEAPON_WOODEN_STAKE}},
        {{"Rose", SaveData::SUBWEAPON_ROSE}}
    };

    const Ui::ComboBoxData comboBoxDataDifficulty = {
        {{"Easy", SaveData::SAVE_FLAG_EASY}},
        {{"Normal", SaveData::SAVE_FLAG_NORMAL}},
        {{"Hard", SaveData::SAVE_FLAG_HARD}},
    };

    const Ui::ComboBoxData comboBoxDataEndingReinhardt = {
        {{"-", 0}},
        {{"Good", SaveData::SAVE_FLAG_REINDHART_GOOD_ENDING}},
        {{"Bad", SaveData::SAVE_FLAG_REINDHART_BAD_ENDING}}
    };

    const Ui::ComboBoxData comboBoxDataEndingCarrie = {
        {{"-", 0}},
        {{"Good", SaveData::SAVE_FLAG_CARRIE_GOOD_ENDING}},
        {{"Bad", SaveData::SAVE_FLAG_CARRIE_BAD_ENDING}}
    };

    const Ui::ComboBoxData comboBoxDataRegion = {
        {{"USA", SaveData::USA}},
        {{"JPN", SaveData::JPN}},
        {{"PAL", SaveData::PAL}}
    };

    const Ui::ComboBoxData comboBoxDataLanguage = {
        {{"English", SaveData::ENGLISH}},
        {{"German", SaveData::GERMAN}},
        {{"French", SaveData::FRENCH}}
    };
};
#endif // MAINWINDOW_H
