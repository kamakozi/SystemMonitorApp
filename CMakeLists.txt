cmake_minimum_required(VERSION 3.31)
project(SystemMonitorApp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(SystemMonitorApp main.cpp
                FrontEnd/LogInWindow/LogInWindow.cpp
                FrontEnd/LogInWindow/LogInWindow.h)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
target_link_libraries(SystemMonitorApp
        PRIVATE
        Qt6::Widgets)
