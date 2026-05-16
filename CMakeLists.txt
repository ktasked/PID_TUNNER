cmake_minimum_required(VERSION 3.16)
project(PIDAutoTunerOilGas VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Поиск Qt с поддержкой Charts
find_package(Qt6 COMPONENTS Core Gui Widgets Charts QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Charts)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/pidcontroller.cpp
    src/processmodel.cpp
    src/tuningmethod.cpp
    src/zeiglernichols.cpp
    src/cohencoon.cpp
    src/internalmodelcontrol.cpp
)

set(HEADERS
    include/mainwindow.h
    include/pidcontroller.h
    include/processmodel.h
    include/tuningmethod.h
    include/zeiglernichols.h
    include/cohencoon.h
    include/internalmodelcontrol.h
)

set(UI_FILES
    src/mainwindow.ui
)

if(EXISTS "${CMAKE_SOURCE_DIR}/resources/resources.qrc")
    set(RESOURCE_FILES resources/resources.qrc)
else()
    set(RESOURCE_FILES "")
endif()

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
    )
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_CHARTS_LIB
    APP_VERSION="${PROJECT_VERSION}"
)

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
    install(DIRECTORY resources DESTINATION share/${PROJECT_NAME})
endif()
