cmake_minimum_required(VERSION 3.31)

project(SRT_time_shifter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

include(FetchContent)

# Download googletest & add to project
FetchContent_Declare(GoogleTest
GIT_REPOSITORY  https://github.com/google/googletest.git
GIT_TAG         main
GIT_SHALLOW     TRUE
UPDATE_DISCONNECTED TRUE
EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(GoogleTest)

# Add googletest targets
include(GoogleTest)

add_subdirectory(src)

configure_file(sample/sample.srt sample.srt COPYONLY)

add_executable(main main.cc)
target_link_libraries(main process_input)
target_include_directories(main PRIVATE include)
