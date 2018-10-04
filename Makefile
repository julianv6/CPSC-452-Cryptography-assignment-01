all:	cipher

cipher:	cipher.o Playfair.o RowTransposition.o RailFence.o Vignere.o Ceasar.o
	g++ cipher.o Playfair.o RowTransposition.o RailFence.o Vignere.o Ceasar.o -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp 

Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
	g++ -g -c Playfair.cpp

RowTransposition.o:	RowTransposition.cpp RowTransposition.h
	g++ -g -c RowTransposition.cpp

RailFence.o: RailFence.cpp RailFence.h
	g++ -g -c RailFence.cpp

Vignere.o: Vignere.cpp Vignere.h
	g++ -g -c Vignere.cpp

Ceasar.o: Ceasar.cpp Ceasar.h
	g++ -g -c Ceasar.cpp

clean:
	rm -rf *.o cipher
