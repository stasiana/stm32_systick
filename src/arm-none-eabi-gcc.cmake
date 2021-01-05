set(CMAKE_SYSTEM_NAME generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)

# STATIC_LIBRARY Use add_library() with the STATIC option to name the source
# file in the generated project. This avoids running the linker and is intended
# for use with cross-compiling toolchains that cannot link without custom flags
# or linker scripts.

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
