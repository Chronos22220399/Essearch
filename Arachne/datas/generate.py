from pathlib import Path
import sqlite3
import subprocess

db_dir = Path("db")
ddl_dir = Path("ddl")
include_dir = Path("include")
    
def generate_sqlite3_by_ddl(src_file_name: str):
    """ 根据 ddl 生成对应的 .sqlite3 文件和 .h 文件"""
    src_file = ddl_dir / f"{src_file_name}.ddl"
    des_db_file = db_dir / f"{src_file_name}.sqlite3"
    cap_file_name = src_file_name.capitalize()
    des_include_file = include_dir / f"{cap_file_name}"
    
    # 生成 sql
    with open(src_file, "r", encoding="utf-8") as file: 
        sqls = file.readlines()
        sql = ""
        for sentence in sqls:
            sql += sentence
            
        connect = sqlite3.connect(des_db_file)
        cursor = connect.cursor()

        cursor.execute(sql)

    # 生成头文件
    subprocess.run(["/usr/local/bin/sqlpp11-ddl2cpp", src_file, des_include_file, cap_file_name])
    
    

if __name__ == "__main__":
    db_dir.mkdir(parents=True, exist_ok=True)
    include_dir.mkdir(parents=True, exist_ok=True)
    generate_sqlite3_by_ddl("news")
