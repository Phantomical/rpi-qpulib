
add_executable(qpu-dis main.cpp)

target_include_directories(qpu-dis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libdis)
target_link_libraries(qpu-dis PRIVATE disasm)

