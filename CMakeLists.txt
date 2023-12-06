cmake_policy(SET CMP0048 NEW)

project(
	fort-tags
	VERSION 1.4.1
	LANGUAGES C CXX
)

if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(FORT_TAGS_MAIN 1)
endif(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(VERSION_API ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
if(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${VERSION_API})
else(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${PROJECT_VERSION_MAJOR})
endif(${PROJECT_VERSION_MAJOR} EQUAL 0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(FetchApriltag)

fetch_apriltag(VERSION fort/3.1.3)

set(INCLUDE_INSTALL_DIR include/fort/tags)
set(LIB_INSTALL_DIR lib)

include(CMakePackageConfigHelpers)
configure_package_config_file(
	FortTagsConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfig.cmake
	INSTALL_DESTINATION ${LIB_INSTALL_DIR}/FortTags/cmake
	PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR
)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfig.cmake
			  ${CMAKE_CURRENT_BINARY_DIR}/FortTagsConfigVersion.cmake
		DESTINATION ${LIB_INSTALL_DIR}/FortTags/cmake
)

add_subdirectory(src/fort/tags)
