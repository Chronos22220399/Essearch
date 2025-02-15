file(
  GLOB_RECURSE
  srcs
  CONFIGURE_DEPENDS
  src/*.cpp
  include/*.h
  include/*.hpp
  protos/*.cc
  protos/*.h
  thirdparty/cppjieba/include/*.hpp
  thirdparty/cppjieba/deps/limonp/include/*.hpp)

project(
  Hephaestus
  LANGUAGES CXX
  VERSION 1.0)

find_package(leveldb REQUIRED)

find_package(fmt REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/protos)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/thirdparty/cppjieba/include
          ${CMAKE_CURRENT_LIST_DIR}/thirdparty/cppjieba/deps/limonp/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LEVELDB_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GRPC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::grpc++)
target_link_libraries(${PROJECT_NAME} PRIVATE leveldb::leveldb)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
