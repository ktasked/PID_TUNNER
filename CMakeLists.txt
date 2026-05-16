cmake_minimum_required(VERSION 3.16)
project(PIDAutoTunerOilGas VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

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

set(RESOURCE_FILES
    resources/resources.qrc
)

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

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Widgets
    Qt5::Core
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_CHARTS_LIB
    APP_VERSION="${PROJECT_VERSION}"
)

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY resources DESTINATION share/${PROJECT_NAME})
