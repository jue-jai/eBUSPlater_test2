
set(TARGET_NAME "Test")
# C++17利用
set(CMAKE_CXX_STANDARD 17)

##################################################################################
# target
##################################################################################
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PRIVATE
	bitstream_test.cpp
	compressed_bitstream_test.cpp
#	line_header_v1_test.cpp
#	compressed_block_test.cpp
	two_complement_test.cpp
	testmain.cpp
#	a.cpp
)

# dependent internal modules
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PRIVATE
     liblossless
	 gtest_main
)

##################################################################################
# 3rd-party OSS library
##################################################################################
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# https://stackoverflow.com/questions/12540970/how-to-make-gtest-build-mdd-instead-of-mtd-by-default-using-cmake
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include(GoogleTest)
#add_test(NAME run_test COMMAND ${TARGET_NAME})
#gtest_add_tests(TARGET ${TARGET_NAME})
gtest_discover_tests(${TARGET_NAME})