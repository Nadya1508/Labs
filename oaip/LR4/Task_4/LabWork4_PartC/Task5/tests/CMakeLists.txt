add_executable(Task5Tests tests.cpp minesweeper.h)


target_link_libraries(Task5Tests PRIVATE Task5Lib gtest_main)

include(GoogleTest)
gtest_discover_tests(Task5Tests)
