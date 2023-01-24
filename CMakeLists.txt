cmake_minimum_required(VERSION 3.5)

project(motiv VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# configure qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

set(PROJECT_SOURCES
        resources.qrc
        src/main.cpp
        src/readercallbacks.cpp
        src/utils.cpp
        src/models/slot.cpp
        src/models/subtrace.cpp
        src/models/filetrace.cpp
        src/models/uitrace.cpp
        src/models/communication/blockingp2pcommunicationevent.cpp
        src/models/communication/nonblockingp2pcommunicationevent.cpp
        src/models/communication/blockingsendevent.cpp
        src/models/communication/blockingreceiveevent.cpp
        src/models/communication/communication.cpp
        src/models/communication/nonblockingsendevent.cpp
        src/models/communication/nonblockingreceiveevent.cpp
        src/models/communication/requestcancelledevent.cpp
        src/models/communication/collectivecommunicationevent.cpp
        src/ui/CommunicationIndicator.cpp
        src/ui/MainWindow.cpp
        src/ui/TimeInputField.cpp
        src/ui/TraceDataProxy.cpp
        src/ui/Timeline.cpp
        src/ui/TimelineHeader.cpp
        src/ui/TimelineLabelList.cpp
        src/ui/TimelineView.cpp
        src/ui/TimeUnit.cpp
        src/ui/TimeUnitLabel.cpp
        src/ui/ScrollSynchronizer.cpp
        src/ui/SlotInformationDock.cpp
        src/ui/SlotIndicator.cpp
        )

# XXX this would require qt version 6
#qt_add_resources(${PROJECT_NAME} resources.qrc)

# configure OTF2xx submodule
set(OTF2XX_CHRONO_DURATION_TYPE nanoseconds CACHE INTERNAL "")
add_subdirectory(lib/otf2xx)
mark_as_advanced(OTF2XX_WITH_MPI OTF2_CONFIG OTF2_PRINT)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
    -DQT_NO_KEYWORDS
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        otf2xx::Reader
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER de.ovgu.parcio.motiv
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
