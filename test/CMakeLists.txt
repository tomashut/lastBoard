###########################################################################################
###################### Unit tests are defined as an isolated project ######################
cmake_minimum_required( VERSION 3.5 )
project(project_unit_tests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

enable_language(C)
enable_language(CXX)

###################### WINDOWS FIX ->
# Set the target platform explicitly to Windows
#set(CMAKE_SYSTEM_NAME Windows)
#set(CMAKE_SYSTEM_NAME Linux)

# Add additional compiler flags for the runtime library
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

###########################################################################
###################### Google Test framework include ######################
### This content gets fetched only once after doing the first "make setup xxx"
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG		release-1.11.0
)

message(STATUS "FETCHING GTest REPOSITORY CONTENT... --")
FetchContent_MakeAvailable(googletest)
message(STATUS "GTest CONTENT FETCHED SUCCESSFULLY! --")

add_library(
	GTest::GTest 
	INTERFACE 
	IMPORTED
)

target_link_libraries(
	GTest::GTest 
	INTERFACE 
	gtest_main
)

enable_testing()
add_subdirectory(utilities)
message(STATUS "UNIT TESTING -- ENABLED!")

message(STATUS "HERE")
##############################################################################################################
################## AUTOMATICALLY SETS ALL DIRECTORIES INSIDE "unit_tests" as CMAKE SUBDIR's ##################
# Set the base directory to search for subdirectories
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Find all subdirectories in the base directory
file(GLOB SUBDIRS LIST_DIRECTORIES true ${BASE_DIR}/*)
# Loop through each found subdirectory and adds it, excepting for the build directory
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${SUBDIR} AND NOT SUBDIR STREQUAL "${BASE_DIR}/build")
        add_subdirectory(${SUBDIR})
    endif()
endforeach()
