cmake_minimum_required(VERSION 3.10)

project(SFML_Schedule_visualizer VERSION 0.1)

# make variables with paths
set(INC_DIR             ${CMAKE_SOURCE_DIR}/inc)
set(SRC_DIR             ${CMAKE_SOURCE_DIR}/src)
set(SRC_SIMPLEGUI_DIR   ${CMAKE_SOURCE_DIR}/src/SimpleGUI)
set(RES_DIR             ${CMAKE_SOURCE_DIR}/data/res)

# include headers to project
include_directories(${INC_DIR})

# compile each single source file
file(GLOB SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.rc)
file(GLOB SOURCES_SIMPLEGUI ${SRC_SIMPLEGUI_DIR}/*.cpp)

# copy resource files to bin/ 
file(COPY ${RES_DIR} DESTINATION ${CMAKE_BINARY_DIR})

# link compiled files to main
add_executable(main ${SOURCES} ${SOURCES_SIMPLEGUI} )

# find SFML package
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# link SFML package
target_link_libraries(main sfml-graphics sfml-window sfml-system) # comdlg32

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(main comdlg32)
endif()