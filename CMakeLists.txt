cmake_minimum_required(VERSION 3.19)

project(motiv VERSION 0.1 LANGUAGES CXX)

set(PROJECT_SOURCE_URL https://github.com/parcio/motiv)
set(PROJECT_ISSUES_URL ${PROJECT_SOURCE_URL}/issues)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Configure OTF2xx submodule
set(OTF2XX_CHRONO_DURATION_TYPE nanoseconds CACHE INTERNAL "")
add_subdirectory(lib/otf2xx)
mark_as_advanced(OTF2XX_WITH_MPI OTF2_CONFIG OTF2_PRINT)

set(PROJECT_SOURCES
        resources.qrc
        src/ReaderCallbacks.cpp
        src/main.cpp
        src/models/AppSettings.cpp
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
        src/ui/views/CollectiveCommunicationIndicator.cpp
        src/ui/views/CommunicationIndicator.cpp
        src/ui/views/GenericIndicator.cpp
        src/ui/views/SlotIndicator.cpp
        src/ui/views/TimelineView.cpp
        src/ui/views/TraceOverviewTimelineView.cpp
        src/ui/widgets/InformationDock.cpp
        src/ui/widgets/TimeInputField.cpp
        src/ui/widgets/TimeUnitLabel.cpp
        src/ui/widgets/Timeline.cpp
        src/ui/widgets/TimelineHeader.cpp
        src/ui/widgets/TimelineLabelList.cpp
        src/ui/widgets/TraceOverviewDock.cpp
        src/ui/widgets/infostrategies/InformationDockCollectiveCommunicationStrategy.cpp
        src/ui/widgets/infostrategies/InformationDockCommunicationStrategy.cpp
        src/ui/widgets/infostrategies/InformationDockElementBaseStrategy.cpp
        src/ui/widgets/infostrategies/InformationDockSlotStrategy.cpp
        src/ui/widgets/infostrategies/InformationDockTraceStrategy.cpp
        src/ui/windows/FilterPopup.cpp
        src/ui/windows/MainWindow.cpp
        src/ui/windows/Otf2FileDialog.cpp
        src/ui/windows/RecentFilesDialog.cpp
        src/utils.cpp
        )

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE
        -DQT_NO_KEYWORDS
        -Wall
        -Wextra
        -Wpedantic
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE
        MOTIV_VERSION_STRING="${PROJECT_VERSION}"
        MOTIV_SOURCE_URL="${PROJECT_SOURCE_URL}"
        MOTIV_ISSUES_URL="${PROJECT_ISSUES_URL}"
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Qt6::Widgets
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
        BUNDLE DESTINATION .)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/motiv.desktop DESTINATION share/icons)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/res/motiv.png DESTINATION share/applications)