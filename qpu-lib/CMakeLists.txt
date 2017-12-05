# qpu-lib

file(GLOB sources
	*.cpp
	*.h
)

file(GLOB headers
	"${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h"
)

add_library(qpu ${sources} ${headers})

target_include_directories(qpu PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
