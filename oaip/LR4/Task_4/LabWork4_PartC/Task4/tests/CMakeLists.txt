add_executable(Task4Tests tests.cpp array_utils.h)


target_link_libraries(Task4Tests PRIVATE Task4Lib gtest_main)

include(GoogleTest)
gtest_discover_tests(Task4Tests)