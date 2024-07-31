cmake_minimum_required(VERSION 3.5)

project(CalcCPP VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}PrintSupport)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter -Wextra -Werror -Wall -Wreorder -Wa,-mbig-obj -O4")

set(PROJECT_SOURCES
        main.cc
        qcustomplot.cc
        qcustomplot.h
        mainwindow.cc
        mainwindow.h
        mainwindow.ui
        annuietet.ui
        credit.cc
        credit.h
        credit.ui
        differ.ui
        form.ui
        graph.cc
        graph.h
        graph.ui
        my_smartcalc.cc
        my_smartcalc.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CalcCPP
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CalcCPP APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CalcCPP SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CalcCPP
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CalcCPP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CalcCPP PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(CalcCPP PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CalcCPP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CalcCPP)
endif()
