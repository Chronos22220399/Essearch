## Record
### gumbo-query
gumbo-query 的安装和使用非常麻烦，我的 gumbo-parser 通过 pacman 安装，后续的运行会通过 docker 创建 archlinux 容器进行，因此不考虑其他系统了

1. 首先安装 gumbo-parser
`sudo pacman -S gumbo-parser`

2. 接着安装 gumbo-query
```fish
git clone https://github.com/Falven/gumbo-query
ccd gumbo-query/build
make -DGumbo_static_LIBRARY=/usr/lib/libgumbo.so ..
make && make test
sudo make install
```

> 安装成图示样子可以直接照抄第 3 步中的配置
```fish
Install the project...
/usr/bin/cmake -P cmake_install.cmake
-- Install configuration: "Debug"
-- Installing: /usr/local/lib/libgq.so
-- Installing: /usr/local/lib/libgq.a
-- Installing: /usr/local/include/gq/Document.h
-- Installing: /usr/local/include/gq/Node.h
-- Installing: /usr/local/include/gq/Object.h
-- Installing: /usr/local/include/gq/Parser.h
-- Installing: /usr/local/include/gq/QueryUtil.h
-- Installing: /usr/local/include/gq/Selection.h
-- Installing: /usr/local/include/gq/Selector.h
```

3. 在 CMakeLists.txt 中进行配置
首先将 gumbo-query 项目中的 cmake 目录下的三个cmake文件放到自己的项目的cmake目录下。
然后在自己的 CMakeLists.txt 中添加如下内容:
```cmake
...
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake; ${CMAKE_MODULE_PATH}")
set(gumbo_query_INCLUDE_DIR /usr/local/include/gq)
set(gumbo_query_LIB /usr/local/lib/libgq.so)
...
include(FindGumbo)
...
target_include_directories(${PROJECT_NAME} PUBLIC include
                                                  ${gumbo_query_INCLUDE_DIR})
...
target_link_libraries(${PROJECT_NAME} PRIVATE ${gumbo_query_LIB})
```

4. 通过以上配置就能使用 gumbo-query 了


## sqlite3 数据库 ddl
### news
```sqlite3
CREATE TABLE New (
  new_id INTEGER PRIMARY KEY,  -- uint32 对应 INTEGER 类型
  title TEXT NOT NULL,         -- string 对应 TEXT 类型
  author_photor TEXT,          -- string 对应 TEXT 类型
  referring TEXT,              -- string 对应 TEXT 类型
  source TEXT,                 -- string 对应 TEXT 类型
  clicked_cnt INTEGER,         -- uint32 对应 INTEGER 类型
  editor TEXT,                 -- string 对应 TEXT 类型
  content TEXT                 -- string 对应 TEXT 类型
);
```
