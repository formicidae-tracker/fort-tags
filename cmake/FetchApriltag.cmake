include(FetchContent)
include(CMakeParseArguments)

function(fetch_apriltag)
	cmake_parse_arguments(OPTS "" "VERSION" "" ${ARGN})
	FetchContent_Declare(apriltag
	                     GIT_REPOSITORY https://github.com/formicidae-tracker/apriltag
	                     GIT_TAG ${OPTS_VERSION}
	                     SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/src/apriltag
	                     )

	FetchContent_GetProperties(apriltag)
	if(NOT apriltag_POPULATED)
		FetchContent_Populate(apriltag)
		add_subdirectory(${apriltag_SOURCE_DIR} ${apriltag_BINARY_DIR})
	endif(NOT apriltag_POPULATED)
	set(APRILTAG_INCLUDE_DIRS ${FETCHCONTENT_BASE_DIR}/src PARENT_SCOPE)

endfunction(fetch_apriltag)
