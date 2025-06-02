cmake_minimum_required(VERSION 3.31)
project(SystemMonitorApp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(spdlog REQUIRED)
include_directories("/usr/local/include")




set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3")
set(OPENSSL_INCLUDE_DIR "/opt/homebrew/opt/openssl@3/include")
set(OPENSSL_LIBRARIES "/opt/homebrew/opt/openssl@3/lib")
find_package(OpenSSL REQUIRED)



include_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/include")
link_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/lib")
include_directories("/opt/homebrew/include")
link_directories("/opt/homebrew/lib")
link_directories("/usr/local/lib")

include_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/include")
link_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/lib")
include_directories("/opt/homebrew/include")
link_directories("/opt/homebrew/lib")


add_executable(SystemMonitorApp main.cpp
                FrontEnd/LogInWindow/LogInWindow.cpp
                FrontEnd/LogInWindow/LogInWindow.h
                FrontEnd/RegisterWindow/RegisterWindow.cpp
                FrontEnd/RegisterWindow/RegisterWindow.h
                BackEnd/Tables/ReadSqlTables.cpp
                BackEnd/Tables/ReadSqlTables.h
                BackEnd/PQXXConnection/ReadEnvFile/ReadEnvFile.h
                BackEnd/PQXXConnection/PQXXSingleton/PQXXSingletonConnection.h
                BackEnd/Auth/User.cpp
                BackEnd/Auth/User.h
                BackEnd/Auth/Register/Register.cpp
                BackEnd/Auth/Register/Register.h
                BackEnd/Auth/Register/BCrypt.hpp
                BackEnd/Auth/Register/bcrypt.h)



target_include_directories(SystemMonitorApp PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(SystemMonitorApp
        PRIVATE
        Qt6::Widgets
        pq
        pqxx
        OpenSSL::Crypto
        spdlog::spdlog
        bcrypt
)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "/opt/homebrew/Cellar/libpqxx/7.10.1/lib;/opt/homebrew/opt/libpq/lib;/opt/homebrew/opt/openssl@3/lib")
