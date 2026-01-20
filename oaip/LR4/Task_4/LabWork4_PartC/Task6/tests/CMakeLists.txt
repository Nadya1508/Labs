add_executable(Task6Tests tests.cpp magic_square.h)


target_link_libraries(Task6Tests PRIVATE Task6Lib gtest_main)

include(GoogleTest)
gtest_discover_tests(Task6Tests)