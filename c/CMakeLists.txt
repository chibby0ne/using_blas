cmake_minimum_required(VERSION 3.0)
project(using_blas)

# Set sources
set(LIB_SRC matrix_support.c)
set(HEADERS matrix_support.h)
set(LIB_NAME matrix_support)
set(EXE_NAME main)
set(EXE_SRC main.c)

# Create Library
add_library(${LIB_NAME} STATIC ${LIB_SRC} ${HEADERS})

# Create executable
add_executable(${EXE_NAME} ${EXE_SRC})
target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME} cblas)
