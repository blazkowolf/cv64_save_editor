cmake_minimum_required(VERSION 3.28)

set(TARGET CV64SaveEditor)

project(${TARGET} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

qt_standard_project_setup()
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

qt_add_executable(${TARGET}
  # ui/MainWindow.ui
  # ui/ControllerPakSelectionWindow.ui
  src/file/FileManager.cpp
  src/file/FileLoader.cpp
  src/save/SaveManager.cpp
  src/main.cpp
  include/windows/Main/MainWindow.h
  src/windows/MainWindow.cpp
  include/windows/ControllerPakSelection/ControllerPakSelectionWindow.h
  src/windows/ControllerPakSelectionWindow.cpp)

# qt_wrap_cpp(${TARGET}
#   src/windows/MainWindow.cpp
#   src/windows/ControllerPakSelectionWindow.cpp)

qt_add_ui(${TARGET}
  SOURCES
    ui/MainWindow.ui
    ui/ControllerPakSelectionWindow.ui)

target_link_libraries(${TARGET} PRIVATE Qt6::Widgets)

target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR})

set_target_properties(${TARGET}
  PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON)
