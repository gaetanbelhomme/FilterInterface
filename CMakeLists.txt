# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 3.0)

# This project is designed to be built outside the Insight source tree.
project(SmothingFilter)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
# Find ITK.
find_package(ITK REQUIRED)

include(${ITK_USE_FILE})

#SmoothingFilter.cxx SmoothingFilter.hxx
add_executable(SmoothingFilter main.cxx Window.h Window.cpp SmoothingFilter.hxx SmoothingFilter.h)

target_link_libraries(SmoothingFilter ${ITK_LIBRARIES})
target_link_libraries(SmoothingFilter Qt5::Widgets)
