cmake_minimum_required(VERSION 3.16)

project(ServerKach LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_DIR "C:/Qt/6.10.2/mingw_64/lib/cmake/Qt6")

# Поиск необходимых компонентов Qt
find_package(Qt6 REQUIRED COMPONENTS Core Sql Network Widgets)

# Создание исполнимого файла
add_executable(ServerKach
  main.cpp
  UserManager.h UserManager.cpp
  Server.h Server.cpp
)

# Связываем проект с необходимыми модулями Qt
target_link_libraries(ServerKach PRIVATE Qt6::Core Qt6::Sql Qt6::Network Qt6::Widgets)

# Настройки установки (для возможности последующего развёртывания)
include(GNUInstallDirs)
install(TARGETS ServerKach
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
