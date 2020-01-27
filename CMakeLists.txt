cmake_policy(SET CMP0048 NEW)

project(fort-tags VERSION 1.1.0
                  LANGUAGES C CXX)

cmake_minimum_required(VERSION 3.11)

include(FetchContent)

FetchContent_Declare(apriltag
                     GIT_REPOSITORY https://github.com/AprilRobotics/apriltag.git
                     GIT_TAG        v3.0.0)

include(ExternalProject)
FetchContent_GetProperties(apriltag)
if(NOT apriltag_POPULATED)
	FetchContent_Populate(apriltag)
endif(NOT apriltag_POPULATED)

ExternalProject_Add(apriltag-populated
	SOURCE_DIR ${apriltag_SOURCE_DIR}
	PATCH_COMMAND git reset --hard
	CONFIGURE_COMMAND git apply ${PROJECT_SOURCE_DIR}/patch/apriltag.patch
	BUILD_COMMAND make
	BUILD_IN_SOURCE 1
	INSTALL_COMMAND PREFIX=<INSTALL_DIR> make install)

ExternalProject_Get_Property(apriltag-populated INSTALL_DIR)

find_package(Threads REQUIRED)

set(APRILTAG_INCLUDE_DIR ${INSTALL_DIR}/include)
set(APRILTAG_INCLUDE_DIRS ${APRILTAG_INCLUDE_DIR})
set(APRILTAG_INCLUDE_DIRS ${APRILTAG_INCLUDE_DIR} PARENT_SCOPE)

set(APRILTAG_LIBRARIES ${INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}apriltag${CMAKE_SHARED_LIBRARY_SUFFIX})

install(FILES ${APRILTAG_LIBRARIES} ${APRILTAG_LIBRARIES}.3.0.0 ${APRILTAG_LIBRARIES}.3 DESTINATION lib)
install(DIRECTORY ${APRILTAG_INCLUDE_DIR} DESTINATION include)

add_subdirectory(src/fort-tags)
