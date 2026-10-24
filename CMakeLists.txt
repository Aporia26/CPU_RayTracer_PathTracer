cmake_minimum_required(VERSION 3.22)

# 1. 🌟 PROJECT NAME
project(RayTracerInOneWeekend LANGUAGES CXX)

# Enforce ultra-high performance modern standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crucial line that sends auto-complete tracking data directly to VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ===========================================================================
# 🚀 ULTRA-PERFORMANCE RAY TRACING OPTIMIZATIONS
# ===========================================================================
# Force Release mode optimizations if no build type is specified.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' for maximum rendering speed.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# ===========================================================================
# 2. 🌟 AUTOMATED PROJECT SEARCHING (FIXED)
# ===========================================================================
# Explicitly grab your source files from code directories to avoid scanning 
# the 'build' artifacts folder.
file(GLOB_RECURSE SOURCE_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

# Fallback: If you have files directly in the root folder, explicitly add them,
# but safely skip anything hidden inside the build cache.
file(GLOB ROOT_SOURCE_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
list(APPEND SOURCE_FILES ${ROOT_SOURCE_FILES})

# Compile the final executable binary
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include directories so you can use clean headers
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Apply aggressive architecture-specific compiler optimization flags
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /O2 /Oi /Ot /FP:fast)
else()
    # For MSYS2 UCRT64 GCC: Enable O3, fast-math, and native CPU vectorization
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -ffast-math -march=native)
endif()

# ===========================================================================
# 3. 🚀 ZERO ASSET COPY-PASTE CONFIGURATION
# ===========================================================================
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    ENGINE_WORKSPACE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)





# use this to get ppm file output->
#./build/RayTracerInOneWeekend.exe | Out-File -Encoding ascii image.ppm
