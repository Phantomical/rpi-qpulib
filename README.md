# rpi-qpulib

### This library is a WIP

A library for running programs on the Raspberry PI QPUs. The QPUs on the Raspberry PI are similar
to GPUs on other computers and are used to run OpenGLES programs on the Raspberry PI. 
While using the proprietary driver on the raspberry pi these are normally driven by the
the second processor on the RPI. It is however possible to control them from userland code
and this library aims to do that. Since shaders running on the QPUs can access the entirety of 
the system memory, any programs using this library must be run as root.

## Usage
To initialize the library first call the `init_qpu` method with a number of QPUs. On all current RPI 
systems the total number of QPUs is 12. Then create a program by calling `create_program` with a 
program binary. Use `create_buffer` to create buffers and `buffer_map` to set their data. Use 
`run_program` to execute the program and wait on the resulting semaphore until the program has 
finished executing.

## Compiling QPU Programs
QPU programs can be compiled from QPU assembly by using [vc4asm](https://github.com/maazl/vc4asm).
The resulting binary should be able to be loaded directly using `create_program`.

## Caveats
There are a some caveats to using the RPI QPU.

1. At this point there is no way to debug code run on the QPU
2. Invalid programs can crash the entire PI
3. It doesn't seem to be any faster than using ARM NEON intrinsics on the newer models of PIs

## Building 
QPULib uses CMake to compile. It can be built as follows
```
cmake /path/to/qpulib
cmake --build .
```
Currently, installing the library is not supported.
