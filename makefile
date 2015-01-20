enigma: rotor.cpp reflector.cpp generator.cpp enigma.cpp
	g++ rotor.cpp -c -std=c++0x
	g++ reflector.cpp -c -std=c++0x
	g++ enigma.cpp -c -std=c++0x
	g++ generator.cpp -c -std=c++0x
	g++ rotor.cpp reflector.o generator.o enigma.o -o enigma -std=c++0x