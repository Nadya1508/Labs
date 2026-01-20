cmake_minimum_required(VERSION 3.14)
project(LabWork4_PartC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

enable_testing()  


add_subdirectory(Task4)
add_subdirectory(Task5)
add_subdirectory(Task6)