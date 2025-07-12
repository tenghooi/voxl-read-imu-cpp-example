cmake_minimum_required(VERSION 3.22)

project(read-imu-cpp-example)

# Strawson's list of standard list of default gcc flags. Yes, I treat
# warnings as errors. Warnings exist to point out sloppy code and potential
# failure points for good reason. We do not approve of sloppy code.
set(CMAKE_C_FLAGS "-std=gnu99 -O3 -Werror -Wall -Wextra -Wuninitialized \
	-Wunused-variable -Wdouble-promotion -Wmissing-prototypes \
	-Wmissing-declarations -Werror=undef -Wno-unused-function \
	-Wno-address-of-packed-member ${CMAKE_C_FLAGS}")

set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Werror -Wall -Wextra -Wuninitialized \
	-Wunused-variable -Wdouble-promotion \
	-Wmissing-declarations -Werror=undef -Wno-unused-function \
	-Wno-address-of-packed-member ${CMAKE_CXX_FLAGS}")

# tell the linker not to worry about missing symbols in libraries
# core Modal AI libraries often have a lot of dependencies and this prevents
# higher level projects from needing to install so many dependencies at compile time
set(CMAKE_C_FLAGS   "-Wl,--unresolved-symbols=ignore-in-shared-libs ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wl,--unresolved-symbols=ignore-in-shared-libs ${CMAKE_CXX_FLAGS}")

# ordering matters in this check since QRB5165 is a substring of QRB5165_2
if(PLATFORM STREQUAL QRB5165_2)
	message(STATUS "Building for platform QRB5165 2.X system images")
	add_definitions(-DPLATFORM_QRB5165_2)
elseif(PLATFORM STREQUAL QRB5165)
	message(STATUS "Building for platform QRB5165 1.X system images")
	add_definitions(-DPLATFORM_QRB5165)
endif()


# for VOXL, install 64-bit libraries to lib64, 32-bit libs go in /usr/lib
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch64")
	set(LIB_INSTALL_DIR /usr/lib64)
else()
	set(LIB_INSTALL_DIR /usr/lib)
endif()

# ignore some warnings when building 32-bit applications for VOXL 2
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
	string(REPLACE "-Wmissing-declarations" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()
 
# include each subdirectory, may have others in example/ or lib/ etc
add_subdirectory (src)
