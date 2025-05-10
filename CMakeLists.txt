cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET CV64SaveEditor)

project(${TARGET} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(${TARGET}
  WIN32 MACOSX_BUNDLE
  src/file/FileManager.cpp
  src/file/FileLoader.cpp
  src/save/SaveManager.cpp
  src/main.cpp
  include/windows/Main/MainWindow.h
  src/windows/MainWindow.cpp
  include/windows/ControllerPakSelection/ControllerPakSelectionWindow.h
  src/windows/ControllerPakSelectionWindow.cpp
  include/windows/general.h
  src/windows/general.cpp
  include/windows/items.h
  src/windows/items.cpp
  include/windows/eventflags.h
  src/windows/eventflags.cpp)

qt_add_ui(${TARGET}
  SOURCES
    ui/MainWindow.ui
    ui/general.ui
    ui/items.ui
    ui/eventflags.ui
    ui/ControllerPakSelectionWindow.ui)

target_link_libraries(${TARGET}
  PRIVATE
    Qt::Core
    Qt::Widgets)

target_include_directories(${TARGET}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include)

include(GNUInstallDirs)

install(TARGETS ${TARGET}
  BUNDLE  DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_generate_deploy_app_script(
  TARGET ${TARGET}
  OUTPUT_SCRIPT deploy_script
  NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
