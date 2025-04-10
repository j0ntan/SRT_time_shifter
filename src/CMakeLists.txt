include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(Timecode Timecode.cpp)

add_library(timecode_str_identifier INTERFACE timecode_str_identifier.hpp)

add_library(process_input process_input.cpp)
target_link_libraries(process_input Timecode)

# Tests
add_executable(test_Timecode Timecode.test.cpp)
target_link_libraries(test_Timecode Timecode GTest::gtest_main)
gtest_discover_tests(test_Timecode)

add_executable(test_timecode_str_identifier timecode_str_identifier.test.cpp)
target_link_libraries(test_timecode_str_identifier timecode_str_identifier
    GTest::gtest_main)
gtest_discover_tests(test_timecode_str_identifier)

add_executable(test_process_input process_input.test.cpp)
target_link_libraries(test_process_input process_input GTest::gtest_main)
gtest_discover_tests(test_process_input)
