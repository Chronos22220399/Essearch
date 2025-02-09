from pathlib import Path
import subprocess
    
def find_sqlite3_file(path: Path) -> list[Path]:
    """ 获取 db 下的所有 sqlite3 文件"""
    return [item for item in path.iterdir() if item.is_file() and item.suffix == ".sqlite3"]
    
def get_sqlite3_ddl(path: Path):
    """ 获取 db 下所有 sqlite3 文件的 ddl 并存入 db/ddl 下"""
    sqlite3_files = find_sqlite3_file(path)
    
    # 创建 ./db/ddl
    ddl_dir = path/"ddl"
    ddl_dir.mkdir(parents=True, exist_ok=True)
    
    for file in sqlite3_files:
        file_name = file.stem
        ddl_file = ddl_dir / f"{file_name}.ddl"

        with open(ddl_file, "w", encoding="utf-8") as f:
            subprocess.run(["sqlite3", file, ".schema"], stdout=f, check=True)
            print(f"已解析完 {file} 并生成 {ddl_file}")

def get_sqlite3_cppcode(path: Path):
    """获取 db/ddl 下所有的 ddl 文件，根据 ddl 生成 cpp 文件存入 ./include 下"""
    ddl_dir = path/"ddl"
    ddl_files = [file for file in ddl_dir.iterdir() if file.is_file() and file.suffix == ".ddl"]
    
    # 创建 ./include
    include_dir = path / ".." / "include"
    include_dir.mkdir(parents=True, exist_ok=True)
    
    # 生成 cpp 文件
    for ddl_file in ddl_files:
        file_name = ddl_file.stem
        cap_file_name = file_name.capitalize()
        result = subprocess.run(["/usr/local/bin/sqlpp11-ddl2cpp", ddl_file, include_dir/cap_file_name, cap_file_name])

if __name__ == "__main__":
    dir = Path("db")
    get_sqlite3_ddl(dir)
    get_sqlite3_cppcode(dir)
    
