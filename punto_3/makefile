all:
	c++ caos.cpp -o caos.x
	./caos.x > salida.txt
	tail -n +5 salida.txt > datos.txt
	python caos.py
