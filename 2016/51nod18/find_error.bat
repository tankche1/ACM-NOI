:again
make_number.exe > input.txt
G.exe < input.txt > output.a
G.exe < input.txt
duipai.exe < input.txt > output.b
fc output.a output.b > nul
if not errorlevel 1 goto again 