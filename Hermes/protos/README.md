## Usage
本目录存放所有 proto 文件，通过目录下的 generate.fish 可生成 cpp 文件和 python 文件，使用方式如下：
1. fish generate.fish search.proto
对单个文件进行生成

2. fish generate.fish search.proto newsOperation.proto ...
对多个文件进行生成

3. fish generate.fish $(ls | grep ".proto")
对匹配到的 protobuf 文件进行生成

4. fish generate.fish *.proto
> 等价于 3
目录下的所有 protobuf 文件进行生成

生成的文件根据类型存放在相关目录下，如 cpp 文件被存放于 cpp 目录下


## Generate other type files
参考 generate.fish 下的这类语句 
```fish
protoc --python_out=./python/ ./$file    
protoc --cpp_out=./include/Arachne ./$file
```
首先创建目录 <xxx>,随后添加
```fish
protoc --xxx_out=./xxx/ ./$file
```
> xxx 取决于生成的文件的类型
