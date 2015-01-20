enigma: rotor.cpp reflector.cpp generator.cpp enigma.cpp main.cpp
	g++ rotor.cpp -c -std=c++0x
	g++ reflector.cpp -c -std=c++0x
	g++ generator.cpp -c -std=c++0x
	g++ enigma.cpp -c -std=c++0x
	g++ rotor.o reflector.o generator.o enigma.o main.cpp -o enigma -std=c++0x
