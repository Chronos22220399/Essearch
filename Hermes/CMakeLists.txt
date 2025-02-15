file(
  GLOB_RECURSE
  srcs
  CONFIGURE_DEPENDS
  include/*.h
  include/*.hpp
  src/*.cpp
  protos/include/*.h
  protos/include/*.cc
  datas/include/*.h)

project(
  Hermes
  LANGUAGES CXX
  VERSION 1.0)

find_package(fmt REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Sodium REQUIRED)
find_package(gRPC REQUIRED)
find_package(Sqlpp11 REQUIRED)
# find_package(Sqlpp11SQLite3 REQUIRED CONFIG)
find_package(Boost REQUIRED CONFIG)
find_package(Crow REQUIRED)
# # 查找 SQLite3 库 include_directories(/usr/local/include)
find_package(SQLite3 REQUIRED)

# 分别处理 macos 和 archlinux
if(APPLE)
  # 手动设置 macOS SQLite3 安装路径（例如通过 Homebrew） 这个有用
  include_directories("/opt/homebrew/Cellar/sqlite/3.48.0/include")
  link_directories("/opt/homebrew/Cellar/sqlite/3.48.0/lib")
  # 手动设置 macOS spdlog 安装路径
  include_directories("/opt/homebrew/Cellar/spdlog/1.15.0_1/include")
  link_directories("/opt/homebrew/Cellar/spdlog/1.15.0_1/lib")
  # ${LEVELDB_LIBRARIES}/libleveldb.dylib ${LEVELDB_LIBRARIES} leveldb
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # 手动设置 Arch Linux 路径（例如通过系统安装） include_directories("/usr/include/sqlite3")
  # link_directories("/usr/lib")
endif()

add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(${PROJECT_NAME} PRIVATE ${sodium_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/protos)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/datas)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test/)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLite3_LIBRARIES} # 手动找到的库路径
                                              sqlpp11::sqlpp11 sqlpp11::sqlite3)
target_link_libraries(${PROJECT_NAME} PRIVATE ${sodium_LIBRARY_DEBUG})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::grpc++ gRPC::grpc)
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)

# CMAKE_OPTIONS 定义于根目录的 CMakeLists.txt
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS}
                                               -DCROW_ENABLE_SSL)
