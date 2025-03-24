# Enable testing
enable_testing()

# Collect all test source files
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# Define the test executable
add_executable(optichess_tests ${TEST_SOURCES})

# Link the main library and any required libraries
target_link_libraries(optichess_tests optichess m)

# Add a test
add_test(NAME RunOptichessTests COMMAND optichess_tests)
