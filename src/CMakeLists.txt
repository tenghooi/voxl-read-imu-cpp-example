
SET(TARGET read-imu-cpp-example)

# Build from all source files
file(GLOB all_src_files *.c*)

add_executable(${TARGET}
	${all_src_files}
)

include_directories(
	../include
)

message(STATUS "included ../include")

find_library(MODAL_JSON  modal_json  HINTS /usr/lib /usr/lib64)
find_library(MODAL_PIPE  modal_pipe  HINTS /usr/lib /usr/lib64)
find_library(VOXL_CUTILS voxl_cutils HINTS /usr/lib /usr/lib64)

target_link_libraries(${TARGET}
	pthread
	${MODAL_JSON}
	${MODAL_PIPE}
	${VOXL_CUTILS}
)

# make sure everything is installed where we want
# LIB_INSTALL_DIR comes from the parent cmake file
install(
	TARGETS			${TARGET}
	LIBRARY			DESTINATION ${LIB_INSTALL_DIR}
	RUNTIME			DESTINATION /usr/bin
	PUBLIC_HEADER	DESTINATION /usr/include
)
