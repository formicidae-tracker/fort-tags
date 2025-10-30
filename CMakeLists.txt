# Copyright (c) 2018-2023, Universitée de Lausanne.
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# 1. Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.11)

project(
	fort-tags
	VERSION 1.4.3
	LANGUAGES C CXX
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-Wall -Wpedantic -Werror)
endif()

if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(FORT_TAGS_MAIN 1)
endif(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(VERSION_API ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
if(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${VERSION_API})
else(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${PROJECT_VERSION_MAJOR})
endif(${PROJECT_VERSION_MAJOR} EQUAL 0)

include(FetchContent)
FetchContent_Declare(
	apriltag
	GIT_REPOSITORY https://github.com/formicidae-tracker/apriltag
	GIT_TAG fort/3.1.3-1
	SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/src/apriltag
)
FetchContent_MakeAvailable(apriltag)

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
