
cmake_minimum_required(VERSION 3.20)

project(embedded-simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(embedded-simulator
  src/main.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(embedded-simulator PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
  )

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(embedded-simulator PRIVATE
      -O0
      -g
      -fsanitize=address,undefined
    )

    target_link_options(embedded-simulator PRIVATE
      -fsanitize=address,undefined
    )
  endif()
endif()

