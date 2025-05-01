/**
 * @file main.cpp
 * @brief Main source code file
 *
 * This file contains the main entrypoint function of the program.
 *
 * @author 
 */

#include "windows/Main/MainWindow.h"
#include "save/SaveManager.h"
#include "file/FileManager.h"
#include <QApplication>
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>

/**
 * This program uses the Singleton pattern to handle different kind of tasks
 * from any part of the program.
 *
 * Since these are static, these will live for the entire lifetime of the application.
 */
SaveManager* SaveManager::instance = nullptr;
FileManager* FileManager::instance = nullptr;

void createSingletons() {
    SaveManager::createInstance();
    FileManager::createInstance();
}

void destroySingletons() {
    SaveManager::destroyInstance();
    FileManager::destroyInstance();
}

int main(int argc, char *argv[]) {
    using namespace Qt::StringLiterals;

    // Create the application and show the main window
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("k64ret"_L1);
    QCoreApplication::setApplicationName("CV64SaveEditor"_L1);
    QCoreApplication::setApplicationVersion("0.1.0"_L1);

    createSingletons();

    QTranslator translator;
    const auto uiLanguages = QLocale::system().uiLanguages();
    for (const auto &locale : uiLanguages) {
        const QString baseName = "CV64SaveEditor_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();

    auto result = a.exec();

    destroySingletons();

    return result;
}
