# dll name
set(TARGET_NAME "liblossless")
set(CMAKE_DEBUG_POSTFIX _d)

# C++17利用
set(CMAKE_CXX_STANDARD 17)

##################################################################################
# target
##################################################################################
add_library(${TARGET_NAME} STATIC)
target_sources(
    ${TARGET_NAME}
    PRIVATE
    bitstream.cpp
    bitstream.hpp
    compressed_bitstream.cpp
    compressed_bitstream.hpp
    compressed_block_bpp8.cpp
    compressed_block_bpp8.hpp
    compressed_block_bpp8d.cpp
    compressed_block_bpp8d.hpp
    compressed_block_bayerbpp8.cpp
    compressed_block_bayerbpp8.hpp
    compressed_buffer_bpp8.cpp
    compressed_buffer_bpp8d.cpp
    compressed_line_bpp8.cpp
    compressed_line_bpp8.hpp
    compressed_line_bpp8d.cpp
    compressed_line_bpp8d.hpp
    threadpool_mgr.cpp
    twos_complement_bitwidth0.cpp
    twos_complement_bitwidth0.hpp
    twos_complement_bitwidth1.cpp
    twos_complement_bitwidth1.hpp
    twos_complement_bitwidth2.cpp
    twos_complement_bitwidth2.hpp
    twos_complement_bitwidth3.cpp
    twos_complement_bitwidth3.hpp
    twos_complement_bitwidth4.cpp
    twos_complement_bitwidth4.hpp
    twos_complement_bitwidth5.cpp
    twos_complement_bitwidth5.hpp
    twos_complement_bitwidth6.cpp
    twos_complement_bitwidth6.hpp
    twos_complement_bitwidth7.cpp
    twos_complement_bitwidth7.hpp
    twos_complement_bitwidth8.cpp
    twos_complement_bitwidth8.hpp
    ${PROJECT_SOURCE_DIR}/include/compressed_buffer_bpp8.hpp
    ${PROJECT_SOURCE_DIR}/include/compressed_buffer_bpp8d.hpp
    ${PROJECT_SOURCE_DIR}/include/threadpool_mgr.hpp
)
target_include_directories(${TARGET_NAME} INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:${toml11_install_include_dir}>
)
add_library(${TARGET_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME} PRIVATE 
  jaids::util
)

if (UNIX)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage") # 追加
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage") # 追加
target_link_libraries(
     ${TARGET_NAME}
    gcov
)
endif()

##################################################################################
# 3rd-party OSS library
##################################################################################
include(FetchContent)
FetchContent_Declare(
   	jaids-util
   	GIT_REPOSITORY        https://github.com/jai-rd/jaids-utils
   	GIT_TAG        v0.0.5
)
FetchContent_GetProperties(jaids-util)
message("Cloning jaids-util")
FetchContent_Populate(jaids-util)
message("Cloning jaids-util:${jaids-util_SOURCE_DIR}")
add_subdirectory(
	${jaids-util_SOURCE_DIR}
	${jaids-util_BINARY_DIR}
)

add_definitions(-DJaids_VERSION_MAJOR=1)