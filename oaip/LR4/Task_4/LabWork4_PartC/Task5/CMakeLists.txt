add_library(Task5Lib minesweeper.cpp minesweeper.h)


add_executable(Task5 main.cpp minesweeper.cpp)
target_link_libraries(Task5 PRIVATE Task5Lib)


add_subdirectory(tests)
