cmake_minimum_required(VERSION 3.14)

#project name と使用言語
project(lossless VERSION 0.0.1 LANGUAGES CXX)
message("<<<<<<<<<build lossless version :${lossless_VERSION_MAJOR}.${lossless_VERSION_MINOR}.${lossless_VERSION_PATCH}>>>>>>>>>>")

# Version
# CMake の設定をソースコードに渡すための
# ヘッダファイルの構成
configure_file (
  "${PROJECT_SOURCE_DIR}/JaidsConfig.h.in"
  "${PROJECT_BINARY_DIR}/JaidsConfig.h"
  )
# インクルードファイルの探索パスにバイナリツリーを追加
include_directories("${PROJECT_BINARY_DIR}")

# enable_testing()
include(CTest)


##################################################################################
# VSビルド時にutf-8指定
##################################################################################
if(MSVC)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()


##################################################################################
# 3rd-party OSS library
##################################################################################
include(FetchContent)
#FetchContent_Declare(
#  ThreadPool
#  GIT_REPOSITORY        https://github.com/progschj/ThreadPool
#)
#FetchContent_MakeAvailable(ThreadPool)



##################################################################################
# Visual Studio Runtime Option
##################################################################################
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
# https://stackoverflow.com/questions/12540970/how-to-make-gtest-build-mdd-instead-of-mtd-by-default-using-cmake
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 次の行を追加するとMinSizeRelとRelWithDebInfoの選択肢を生成することが抑制
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited configs" FORCE)

##################################################################################
# Optimization
##################################################################################
if(UNIX)
set(CMAKE_CXX_FLAGS "-O3 -Wall")
endif()

add_definitions(-DINFO_PRINT)

##################################################################################
#sub-dir
##################################################################################
add_subdirectory(src)
add_subdirectory(test)
if(MSVC)
add_subdirectory(test_app)
endif()
# add_subdirectory(3rd-party)



