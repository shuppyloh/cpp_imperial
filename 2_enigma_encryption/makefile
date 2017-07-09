enigma: main.o MachinePart.o Rotor.o Reflector.o Plugboard.o
	g++ -Wall -g main.o MachinePart.o Rotor.o Reflector.o Plugboard.o -o enigma
main.o: main.cpp MachinePart.h Plugboard.h Rotor.h Reflector.h errors.h
	g++ -Wall -g main.cpp -c
MachinePart.o: MachinePart.cpp MachinePart.h errors.h
	g++ -Wall -g MachinePart.cpp -c
Rotor.o: Rotor.cpp Rotor.h MachinePart.h errors.h 
	g++ -Wall -g Rotor.cpp -c
Reflector.o: Reflector.cpp Reflector.h MachinePart.h errors.h 
	g++ -Wall -g Reflector.cpp -c
Plugboard.o: Plugboard.cpp Plugboard.h MachinePart.h errors.h 
	g++ -Wall -g Plugboard.cpp -c
