add_library(Task4Lib array_utils.cpp array_utils.h)


add_executable(Task4 main.cpp array_utils.cpp)
target_link_libraries(Task4 PRIVATE Task4Lib)


add_subdirectory(tests)