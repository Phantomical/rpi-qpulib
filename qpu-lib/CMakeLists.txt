# qpu-lib

file(GLOB sources
	*.cpp
	*.h
)

file(GLOB headers
	"${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h"
)

include (CheckIncludeFiles)
check_include_files("fcntl.h;unistd.h;sys/mman.h;sys/ioctl.h;linux/ioctl.h" HAVE_MAILBOX_HEADERS)
check_include_files("dlfcn.h" HAVE_DLFCN_H)

if (HAVE_MAILBOX_HEADERS)
	add_definitions(-DHAVE_MAILBOX_HEADERS)
endif()
if (HAVE_DLFCN_H)
	add_definitions(-DHAVE_DLFCN_H)
endif()

add_library(qpu ${sources} ${headers})

target_include_directories(qpu PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
