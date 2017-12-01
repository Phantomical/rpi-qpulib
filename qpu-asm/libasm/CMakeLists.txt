#libasm CMake file

file (GLOB sources
	*.cpp
	*.h
)

add_library(asm ${sources}) 
