:again
make_number.exe > input.txt
D.exe < input.txt > output.a
duipai.exe < input.txt > output.b
fc output.a output.b > nul
if not errorlevel 1 goto again 