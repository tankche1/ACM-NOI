:again
make.exe > input.txt
B.exe < input.txt > output.a
std.exe < input.txt > output.b
fc output.a output.b > nul
if not errorlevel 1 goto again 