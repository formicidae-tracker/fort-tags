cmake_policy(SET CMP0048 NEW)

project(fort-tags VERSION 1.2.2
                  LANGUAGES C CXX)

cmake_minimum_required(VERSION 3.11)

set(VERSION_API ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
if(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${VERSION_API})
else(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${PROJECT_VERSION_MAJOR})
endif(${PROJECT_VERSION_MAJOR} EQUAL 0)


include(FetchContent)

FetchContent_Declare(apriltag
                     GIT_REPOSITORY https://github.com/AprilRobotics/apriltag.git
                     GIT_TAG        v3.0.0)

include(ExternalProject)
FetchContent_GetProperties(apriltag)
if(NOT apriltag_POPULATED)
	FetchContent_Populate(apriltag)
endif(NOT apriltag_POPULATED)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	ExternalProject_Add(apriltag-populated
	                    SOURCE_DIR ${apriltag_SOURCE_DIR}
	                    PATCH_COMMAND git reset --hard && git apply ${PROJECT_SOURCE_DIR}/patch/apriltag.patch && git apply ${PROJECT_SOURCE_DIR}/patch/noopt.patch
	                    CONFIGURE_COMMAND echo "configured"
	                    BUILD_COMMAND make
	                    BUILD_IN_SOURCE 1
	                    INSTALL_COMMAND make PREFIX=<INSTALL_DIR> install)
else(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	ExternalProject_Add(apriltag-populated
	                    SOURCE_DIR ${apriltag_SOURCE_DIR}
	                    PATCH_COMMAND git reset --hard && git clean -dxf && git apply ${PROJECT_SOURCE_DIR}/patch/noopt.patch
	                    CONFIGURE_COMMAND cmake -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_BUILD_TYPE=Release
	                    BUILD_IN_SOURCE 1
	                    )
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
ExternalProject_Get_Property(apriltag-populated INSTALL_DIR)

find_package(Threads REQUIRED)



set(INCLUDE_INSTALL_DIR include/fort/tags)
set(LIB_INSTALL_DIR lib )

include(CMakePackageConfigHelpers)
configure_package_config_file(FortTagsConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfig.cmake
	INSTALL_DESTINATION ${LIB_INSTALL_DIR}/FortTags/cmake
	PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfigVersion.cmake
        DESTINATION ${LIB_INSTALL_DIR}/FortTags/cmake )


set(APRILTAG_INCLUDE_DIR ${INSTALL_DIR}/include)
set(APRILTAG_INCLUDE_DIRS ${APRILTAG_INCLUDE_DIR})
set(APRILTAG_INCLUDE_DIRS ${APRILTAG_INCLUDE_DIR} PARENT_SCOPE)

set(APRILTAG_LIBRARIES ${INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}apriltag${CMAKE_SHARED_LIBRARY_SUFFIX})

install(FILES ${APRILTAG_LIBRARIES} ${APRILTAG_LIBRARIES}.3.0.0 ${APRILTAG_LIBRARIES}.3 DESTINATION lib)
install(DIRECTORY ${APRILTAG_INCLUDE_DIR}/apriltag DESTINATION include)


add_subdirectory(src/fort/tags)
