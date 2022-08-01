for /f "tokens=* delims=" %%i in ('dir /b/s *.mdtxt') do (
rem 查找目标文件夹及子文件夹内的所有zip后缀的文件
rename "%%i" "*.txt"
rem 将所有zip后缀的文件更改为exe后缀
)
rem 退出
