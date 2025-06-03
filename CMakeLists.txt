cmake_minimum_required(VERSION 3.31)
project(SystemMonitorApp)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)


find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)


include_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/include")
link_directories("/opt/homebrew/Cellar/libpqxx/7.10.1/lib")
include_directories(${Qt6Charts_INCLUDE_DIRS})

include_directories("/opt/homebrew/include" "/usr/local/include")
link_directories("/opt/homebrew/lib" "/usr/local/lib")


set(SOURCES
        main.cpp


        FrontEnd/LogInWindow/LogInWindow.cpp
        FrontEnd/RegisterWindow/RegisterWindow.cpp
        FrontEnd/MainWindowUser/MainWindow.cpp
        FrontEnd/MainWindowUser/CpuUsageWidget/CpuUsage.cpp


        BackEnd/Tables/ReadSqlTables.cpp
        BackEnd/Auth/User.cpp
        BackEnd/Auth/Register/Register.cpp
        BackEnd/Auth/Login/Login.cpp
        BackEnd/GetSystemResources/UsageProvider.cpp
        BackEnd/GetSystemResources/GetCpuUsage/GetCpuUsage.cpp
        BackEnd/GetSystemResources/GetGpuUsage/GetGpuUsage.cpp
        BackEnd/GetSystemResources/GetInternetUsage/GetInternetUsage.cpp
        BackEnd/GetSystemResources/GetRamUsage/GetRamUsage.cpp
)

set(HEADERS

        FrontEnd/LogInWindow/LogInWindow.h
        FrontEnd/RegisterWindow/RegisterWindow.h
        FrontEnd/MainWindowUser/MainWindow.h
        FrontEnd/MainWindowUser/CpuUsageWidget/CpuUsage.h


        BackEnd/Tables/ReadSqlTables.h
        BackEnd/PQXXConnection/ReadEnvFile/ReadEnvFile.h
        BackEnd/PQXXConnection/PQXXSingleton/PQXXSingletonConnection.h
        BackEnd/Auth/User.h
        BackEnd/Auth/Register/Register.h
        BackEnd/Auth/Register/BCrypt.hpp
        BackEnd/Auth/Register/bcrypt.h
        BackEnd/Auth/Login/Login.h
        BackEnd/Auth/Login/BCrypt.hpp
        BackEnd/Auth/Login/bcrypt.h
        BackEnd/GetSystemResources/UsageProvider.h
        BackEnd/GetSystemResources/GetCpuUsage/GetCpuUsage.h
        BackEnd/GetSystemResources/GetGpuUsage/GetGpuUsage.h
        BackEnd/GetSystemResources/GetInternetUsage/GetInternetUsage.h
        BackEnd/GetSystemResources/GetRamUsage/GetRamUsage.h
)


add_executable(SystemMonitorApp ${SOURCES} ${HEADERS})


target_link_libraries(SystemMonitorApp
        PRIVATE
        Qt6::Widgets
        pq
        pqxx
        OpenSSL::Crypto
        spdlog::spdlog
        bcrypt
        Qt6::Charts
)


set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH
        "/opt/homebrew/Cellar/libpqxx/7.10.1/lib;/opt/homebrew/opt/libpq/lib;/opt/homebrew/opt/openssl@3/lib"
)