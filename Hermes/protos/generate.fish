#!/usr/bin/fish

# 检查是否传入参数
if test (count $argv) -eq 0
    echo "Usage: ./generate.fish <args...> [or <*.proto>]"
    exit 1  
end

set valid_files 

# 处理每个参数，扩展通配符并验
for arg in $argv
    for file in $arg
        if test -f "$file"
            set valid_files $valid_files "$file"
        else
            echo "Error: '$file' does not exists."
            exit 1
        end
    end
end

echo "Generating code for files: $valid_files"

if not test -d "./python"
    echo "No such directory python"
    mkdir python
    echo "Directory python created"
end

if not test -d "./cpp"
    echo "No such directory cpp"
    mkdir cpp
    echo "Directory cpp created"
end

# 生产 cpp 和 python 文件
for file in $valid_files
    protoc --python_out=./python/ ./$file    
    protoc --cpp_out=./include/ ./$file
    protoc --grpc_out=./include/ --plugin=protoc-gen-grpc=(which grpc_cpp_plugin) ./$file
    if test $status -ne 0
        echo "Error: Failed to generate code for $file"
        exit 1
    end
    echo "Generated code for $file"
end
