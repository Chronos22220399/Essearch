cmake_minimum_required(VERSION 3.0.0)

# set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SUPPRESS_REGENERATION FALSE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
# set(Gumbo)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake; ${CMAKE_MODULE_PATH}")
set(COMPILE_OPTIONS
    -O0 -g -Wall # 打开所有警告
    # -Wextra      # 打开额外的警告 -Werror # 将警告视为错误
    -pedantic # 启用严格的 C++ 标准
)

project(
  Essearch
  LANGUAGES CXX
  VERSION 1.0)

# 对 gumbo-query 的基本配置
find_package(SQLite3 REQUIRED)
if(APPLE)
  set(gumbo_query_INCLUDE_DIR /usr/local/include)
  set(gumbo_query_LIB /usr/local/lib/libgumbo_query.dylib)
else()
  include(GumboQueryConfig)
endif()
include(FindSodium)

add_subdirectory(Arachne)
add_subdirectory(Hermes)
