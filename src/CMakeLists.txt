include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(Timecode Timecode.cpp)

add_library(Subtitle Subtitle.cpp)
target_link_libraries(Subtitle Timecode)

# Tests
add_executable(test_Timecode Timecode.test.cpp)
target_link_libraries(test_Timecode Timecode GTest::gtest_main)
gtest_discover_tests(test_Timecode)

add_executable(test_Subtitle Subtitle.test.cpp)
target_link_libraries(test_Subtitle Subtitle GTest::gtest_main)
gtest_discover_tests(test_Subtitle)
