:again
make_number.exe > input.txt
hdu5048.exe < input.txt > output.a
duipai.exe < input.txt > output.b
fc output.a output.b > nul
if not errorlevel 1 goto again 