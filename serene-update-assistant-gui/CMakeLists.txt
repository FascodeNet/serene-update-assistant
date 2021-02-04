cmake_minimum_required(VERSION 3.5)

project(serene-update-assistant-gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

    set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network LinguistTools RemoteObjects REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network LinguistTools RemoteObjects REQUIRED)

set(TS_FILES serene-update-assistant-gui_ja_JP.ts)
set(QT_QMAKE_EXECUTABLE /usr/bin/qmake-qt5)
qt5_generate_repc(REPCS IPC_Serene.rep SOURCE)
QT5_ADD_RESOURCES(RESOURCES resources.qrc)
set(SOURCESKUN
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    updatertray.cpp
    updatertray.h
    updatercore.cpp
    updatercore.h
    ansiescapecodehandler.cpp
    ansiescapecodehandler.h
    qtcassert.cpp
    qtcassert.h)

qt5_create_translation(_qmFiles ${SOURCESKUN} ${TS_FILES})
qt5_add_translation(_qmFiles ${TS_FILES})
add_executable(serene-update-assistant-gui
    ${SOURCESKUN}
    ${RESOURCES}
    ${_qmFiles}
    ${REPCS}
  )


target_link_libraries(serene-update-assistant-gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets curl Qt${QT_VERSION_MAJOR}::RemoteObjects )
