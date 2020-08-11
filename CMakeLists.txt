cmake_policy(SET CMP0048 NEW)

project(fort-tags VERSION 1.3.0
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
                     GIT_REPOSITORY https://github.com/formicidae-tracker/apriltag.git
                     GIT_TAG        fort/3.1.2)

include(ExternalProject)
FetchContent_GetProperties(apriltag)
if(NOT apriltag_POPULATED)
	FetchContent_Populate(apriltag)
endif(NOT apriltag_POPULATED)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	ExternalProject_Add(apriltag-populated
	                    SOURCE_DIR ${apriltag_SOURCE_DIR}
	                    PATCH_COMMAND git reset --hard
	                    CONFIGURE_COMMAND echo "configured"
	                    BUILD_COMMAND make
	                    BUILD_IN_SOURCE 1
	                    INSTALL_COMMAND make PREFIX=<INSTALL_DIR> install)
else(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	ExternalProject_Add(apriltag-populated
	                    SOURCE_DIR ${apriltag_SOURCE_DIR}
	                    PATCH_COMMAND git reset --hard
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
get_directory_property(PARENT_DIR PARENT_DIRECTORY)
if(PARENT_DIR)
	set(APRILTAG_INCLUDE_DIRS ${APRILTAG_INCLUDE_DIR} PARENT_SCOPE)
endif(PARENT_DIR)
set(APRILTAG_STATIC_LIBRARY ${INSTALL_DIR}/lib/libapriltag.a)
add_custom_target(apriltag-static-lib ALL
                                      COMMAND "true"
                                      BYPRODUCTS ${APRILTAG_STATIC_LIBRARY})

install(DIRECTORY ${APRILTAG_INCLUDE_DIR}/apriltag DESTINATION include)


add_subdirectory(src/fort/tags)
