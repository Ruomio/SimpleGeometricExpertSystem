cmake_minimum_required(VERSION 3.5)

project(Simple_geometric_expert_system VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# opencv
set(OpenCV_DIR /usr/lib/cmake/opencv4/)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)

# end

MESSAGE(STATUS "----------------Current path : ${OpenCV_DIR}")
# MESSAGE(STATUS "----------------Current path : ${OpenCV_LIBS}")

find_package(QT NAMES Qt5 Qt6 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets )

MESSAGE(STATUS "----------------Current path : Qt${QT_VERSION_MAJOR}")



set(PROJECT_SOURCES
    # include
    code/include/MainWindow.h
    code/include/Rule.h
    code/include/Engine.h
    code/include/Handler.h
    code/include/Frame.h
    code/include/RuleEdit.h
    
    
    # source
    code/source/MainWindow.cpp
    code/source/Rule.cpp
    code/source/Engine.cpp
    code/source/Handler.cpp
    code/source/Frame.cpp
    code/source/RuleEdit.cpp
    code/source/main.cpp
)


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
        add_library(${PROJECT_NAME} SHAREDS
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

# opencv
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
# Qt
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
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
