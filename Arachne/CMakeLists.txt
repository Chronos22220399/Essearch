file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h
     datas/include/*.h)

project(
  Arachne
  LANGUAGES CXX
  VERSION 1.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake; ${CMAKE_MODULE_PATH}")

# 对 gumbo-query 的基本配置
include(GumboQueryConfig)

find_package(httplib REQUIRED)
find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} ${srcs})

target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${gumbo_query_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

target_include_directories(${PROJECT_NAME} PUBLIC include
                                                  ${gumbo_query_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC datas/include)
