# Gather all source files in the src directory (including subfolders, if any)
file(GLOB_RECURSE APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# Define the executable target. This will compile all .c files in src.
add_executable(optichess ${APP_SOURCES})

