include_directories(${apriltag_SOURCE_DIR}/include)

set(SRC_FILES tag36ARTag.c
              tag36h10.c
              options.cpp
              fort-tags.cpp)

set(HDR_FILES tag36ARTag.h
              tag36h10.h
              fort-tags.h
              fort-tags.hpp
              options.hpp)


add_library(fort-tags SHARED ${SRC_FILES} ${HDR_FILES})

add_dependencies(fort-tags apriltag)

set(APRILTAG_LINK_FLAGS )
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(APRILTAG_LINK_FLAGS "-L${apriltag_BINARY_DIR} -Wl,--whole-archive -lapriltag -Wl,--no-whole-archive")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	set(APRILTAG_LINK_FLAGS "-Wl,-force_load,${apriltag_BINARY_DIR}/libapriltag.a")
else(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(FATAL_ERROR "Unsupported OS ${CMAKE_SYSTEM_NAME}")
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")


target_link_libraries(fort-tags ${APRILTAG_LINK_FLAGS}
                                )

set_target_properties(fort-tags PROPERTIES VERSION ${VERSION_API}
                                           SOVERSION ${VERSION_ABI})

install(TARGETS fort-tags DESTINATION ${LIB_INSTALL_DIR})

install(FILES ${HDR_FILES} DESTINATION ${INCLUDE_INSTALL_DIR})
