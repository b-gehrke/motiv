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
        src/ReaderCallbacks.cpp
        src/main.cpp
        src/models/Filetrace.cpp
        src/models/Filter.cpp
        src/models/Slot.cpp
        src/models/SubTrace.cpp
        src/models/UITrace.cpp
        src/models/ViewSettings.cpp
        src/models/communication/BlockingP2PCommunicationEvent.cpp
        src/models/communication/BlockingReceivEevent.cpp
        src/models/communication/BlockingSendEvent.cpp
        src/models/communication/CollectiveCommunicationEvent.cpp
        src/models/communication/Communication.cpp
        src/models/communication/NonBlockingP2PCommunicationEvent.cpp
        src/models/communication/NonBlockingReceiveEvent.cpp
        src/models/communication/NonBlockingSendEvent.cpp
        src/models/communication/RequestCancelledEvent.cpp
        src/ui/ScrollSynchronizer.cpp
        src/ui/TimeUnit.cpp
        src/ui/TraceDataProxy.cpp
        src/ui/views/CommunicationIndicator.cpp
        src/ui/views/SlotIndicator.cpp
        src/ui/views/TimelineView.cpp
        src/ui/widgets/SlotInformationDock.cpp
        src/ui/widgets/TimeInputField.cpp
        src/ui/widgets/TimeUnitLabel.cpp
        src/ui/widgets/Timeline.cpp
        src/ui/widgets/TimelineHeader.cpp
        src/ui/widgets/TimelineLabelList.cpp
        src/ui/windows/FilterPopup.cpp
        src/ui/windows/MainWindow.cpp
        src/utils.cpp
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
