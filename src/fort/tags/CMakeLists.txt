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

include_directories(${apriltag_SOURCE_DIR}/include)

set(SRC_FILES tag36ARTag.c tag36h10.c options.cpp fort-tags.cpp)

set(HDR_FILES tag36ARTag.h tag36h10.h fort-tags.h fort-tags.hpp options.hpp)

add_library(fort-tags SHARED ${SRC_FILES} ${HDR_FILES})

add_dependencies(fort-tags apriltag)

set(APRILTAG_LINK_FLAGS)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(APRILTAG_LINK_FLAGS
		"-L${apriltag_BINARY_DIR} -Wl,--whole-archive -lapriltag -Wl,--no-whole-archive"
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	set(APRILTAG_LINK_FLAGS
		"-Wl,-force_load,${apriltag_BINARY_DIR}/libapriltag.a"
	)
else(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(FATAL_ERROR "Unsupported OS ${CMAKE_SYSTEM_NAME}")
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

target_link_libraries(fort-tags ${APRILTAG_LINK_FLAGS})

set_target_properties(
	fort-tags PROPERTIES VERSION ${VERSION_API} SOVERSION ${VERSION_ABI}
)

install(TARGETS fort-tags DESTINATION ${LIB_INSTALL_DIR})

install(FILES ${HDR_FILES} DESTINATION ${INCLUDE_INSTALL_DIR})

if(NOT FORT_TAGS_MAIN)
	add_library(fort-tags::libfort-tags INTERFACE IMPORTED GLOBAL)
	target_link_libraries(fort-tags::libfort-tags INTERFACE fort-tags)
	target_include_directories(
		fort-tags::libfort-tags INTERFACE ${PROJECT_SOURCE_DIR}/src
										  ${apriltag_SOURCE_DIR}/include
	)
endif(NOT FORT_TAGS_MAIN)
