add_library(Task6Lib magic_square.cpp magic_square.h)


add_executable(Task6 main.cpp magic_square.cpp)
target_link_libraries(Task6 PRIVATE Task6Lib)


add_subdirectory(tests)
