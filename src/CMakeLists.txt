cmake_minimum_required(VERSION 3.19)

enable_language(C CXX ASM)

project(main)

set(EXE_FILE ${PROJECT_NAME}.out)
add_executable(${EXE_FILE}
    main.c
    )

target_compile_definitions(${EXE_FILE} PRIVATE
    -DSTM32F1 # libopencm3
    )

target_compile_options(${EXE_FILE} PRIVATE
    -mcpu=cortex-m3 # target
    -mthumb # target
    -ffunction-sections # dead code elimination
    -fdata-sections # dead code elimination
    )

target_include_directories(${EXE_FILE} PRIVATE
    ${PROJECT_SOURCE_DIR}/../opt/libopencm3/include # libopencm3
    )

target_link_options(${EXE_FILE} PRIVATE
    -mcpu=cortex-m3 # target
    -mthumb # target
    -T${PROJECT_SOURCE_DIR}/STM32F103C8T6.ld # target
    -Wl,--gc-sections # dead code elimination
    # -Wl,--print-gc-sections # dead code elimination
    -nostartfiles # bare metal
    # -specs=nosys.specs # bare metal, C++
    )

target_link_libraries(${EXE_FILE}
    -L${PROJECT_SOURCE_DIR}/../opt/libopencm3/lib # libopencm3
    -lopencm3_stm32f1 # libopencm3
    )

add_custom_command(TARGET ${EXE_FILE}
    PRE_BUILD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../opt/libopencm3
    COMMAND make
    )

add_custom_command(TARGET ${EXE_FILE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${EXE_FILE} ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${EXE_FILE} ${PROJECT_NAME}.bin
    COMMAND arm-none-eabi-size ${EXE_FILE}
    )

add_custom_target(flash
    COMMAND st-flash --reset write ${PROJECT_NAME}.bin 0x08000000
    VERBATIM
)
