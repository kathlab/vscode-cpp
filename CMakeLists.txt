cmake_minimum_required(VERSION 3.16)

## set project name
project(vscode_cpp)

## set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## cmake includes
include(FetchContent)

## arguments

# doctest
set(DOCTEST_URL "https://github.com/onqtam/doctest")
set(DOCTEST_TAG "v2.4.9")

# sfml
set(SFML_URL "https://github.com/SFML/SFML.git")
# set(SFML_TAG "2.5.1")  # does not support c++17 nor macOS M1/M2
set(SFML_TAG "e82d20c29140c8631bfb4d0a28db8918931dd7df") # 2.6.x dev branch

# fltk
set(FLTK_URL "https://github.com/fltk/fltk")
# set(FLTK_TAG "release-1.3.8") # DWORD type error in this release on windows
set(FLTK_TAG "b5b88d5f0dcb682df1ad80ac8939fcfc1f6671da") # 1.4.x dev branch

## fetch external libraries

# doctest

FetchContent_Declare(
    doctest
    GIT_REPOSITORY ${DOCTEST_URL}
    GIT_TAG ${DOCTEST_TAG}
)
FetchContent_MakeAvailable(doctest)

# sfml

# build SFML static library on windows to fix run issue in VS Code
if(WIN32)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(SFML_USE_STATIC_LIBS ON CACHE BOOL "" FORCE)
endif()

# sfml build is NOT compatible with MinGW UCRT compiler
# MSVCRT compiler is mandatory
# @see https://github.com/SFML/SFML/issues/2289

FetchContent_Declare(
    SFML
    GIT_REPOSITORY ${SFML_URL}
    GIT_TAG ${SFML_TAG}
)
FetchContent_MakeAvailable(SFML)

# fltk

# 1.3.x has compilation errors on windows (fixed for upcoming 1.4 version)
# @see https://github.com/fltk/fltk/issues/445

set(FLTK_BUILD_TEST OFF CACHE BOOL "" FORCE)
if(UNIX AND NOT APPLE) 
    set(OPTION_USE_PANGO ON CACHE BOOL "" FORCE)
endif()

FetchContent_Declare(
    FLTK
    GIT_REPOSITORY ${FLTK_URL}
    GIT_TAG ${FLTK_TAG}
)

FetchContent_MakeAvailable(FLTK)

if(WIN32)
    set(GUI_TYPE WIN32)
elseif(APPLE)
    set(GUI_TYPE MACOSX_BUNDLE)
else()
    set(GUI_TYPE)
endif()


## platform setup
if (APPLE)
    set(PLATFORM_LIBS "-framework cocoa")
else()
    set(PLATFORM_LIBS "")
endif (APPLE)

###############################################################
### CLI app

# app executable
add_executable(${CMAKE_PROJECT_NAME}_cli)
target_sources(${CMAKE_PROJECT_NAME}_cli
    PRIVATE
    src/cli_app.cpp
    src/app.cpp
)

# link libraries
target_link_libraries(${CMAKE_PROJECT_NAME}_cli
    PRIVATE
    # add libs here
    ${PLATFORM_LIBS}
)

# ###############################################################
# ### FLTK app

# app executable
add_executable(${CMAKE_PROJECT_NAME}_fltk)
target_sources(${CMAKE_PROJECT_NAME}_fltk
    PRIVATE
    src/fltk_app.cpp
)

# add include targets
target_include_directories(${CMAKE_PROJECT_NAME}_fltk
    PRIVATE
    ${fltk_BINARY_DIR} # abi-version.h
    ${fltk_SOURCE_DIR}
)

# link libraries
target_link_libraries(${CMAKE_PROJECT_NAME}_fltk
    PRIVATE
    fltk
    ${PLATFORM_LIBS}
)

###############################################################
### SFML app

# app executable
add_executable(${CMAKE_PROJECT_NAME}_sfml)
target_sources(${CMAKE_PROJECT_NAME}_sfml
    PRIVATE
    src/sfml_app.cpp
)

# add include targets
target_include_directories(${CMAKE_PROJECT_NAME}_sfml
    PRIVATE
    ${sfml_SOURCE_DIR}/include
)

# link libraries
target_link_libraries(${CMAKE_PROJECT_NAME}_sfml
    PRIVATE
    sfml-audio
    sfml-graphics
    sfml-system
    sfml-window
    ${PLATFORM_LIBS}
)

###############################################################
### automated tests

# test executable
add_executable(${CMAKE_PROJECT_NAME}_test)
target_sources(${CMAKE_PROJECT_NAME}_test
    PRIVATE
    src/test/base_config_main_test.cpp
    src/test/app_test.cpp
    src/app.cpp
)

# add include targets
target_include_directories(${CMAKE_PROJECT_NAME}_test
    PRIVATE
    ${doctest_SOURCE_DIR}/doctest
)

# link libraries
target_link_libraries(${CMAKE_PROJECT_NAME}_test
    doctest
    ${PLATFORM_LIBS}
)