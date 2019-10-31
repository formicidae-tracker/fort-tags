include_directories(${APRILTAG_INCLUDE_DIRS})

set(SRC_FILES tag36ARTag.c
              tag36h10.c)

set(HDR_FILES tag36ARTag.h
              tag36h10.h)

add_library(fort-tags SHARED ${SRC_FILES} ${HDR_FILES})

target_link_libraries(fort-tags ${APRILTAG_LIBRARIES} Threads::Threads)

set_target_properties(fort-tags PROPERTIES VERSION ${PROJECT_VERSION}
                                           SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS fort-tags DESTINATION lib)

install(FILES ${HDR_FILES} DESTINATION include/fort-tags)
