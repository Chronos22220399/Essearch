file(
  GLOB_RECURSE
  srcs
  CONFIGURE_DEPENDS
  src/*.cpp
  include/*.h
  include/*.hpp
  datas/include/*.h)

project(
  Arachne
  LANGUAGES CXX
  VERSION 1.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake; ${CMAKE_MODULE_PATH}")

# 对 gumbo-query 的基本配置
find_package(SQLite3 REQUIRED)
if(APPLE)
  set(gumbo_query_INCLUDE_DIR /usr/local/include)
  set(gumbo_query_LIB /usr/local/lib/libgumbo_query.dylib)
else()
  include(GumboQueryConfig)
endif()

find_package(httplib REQUIRED)
find_package(fmt REQUIRED)
find_package(httplib REQUIRED)
find_package(Sqlpp11 REQUIRED)
find_package(ICU REQUIRED COMPONENTS uc i18n io)

add_executable(${PROJECT_NAME} ${srcs})

target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${gumbo_query_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE ${ICU_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC include
                                                  ${gumbo_query_INCLUDE_DIR})
target_include_directories(
  ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/datas
                          ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE sqlpp11::sqlpp11 sqlpp11::sqlite3)
