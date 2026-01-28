cmake_minimum_required(VERSION 3.20)

project(ase-alloc
    VERSION 1.0.0
    DESCRIPTION "ASE Memory Allocation - Arena, Pool, Stack Allocators"
    LANGUAGES CXX
)

# Library (header-only)
add_library(ase-alloc INTERFACE)
add_library(ase::alloc ALIAS ase-alloc)

target_include_directories(ase-alloc
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(ase-alloc INTERFACE cxx_std_20)

# Install
install(TARGETS ase-alloc
    EXPORT ase-alloc-targets
)

install(DIRECTORY include/ase
    DESTINATION include
)
