#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++11

TRGDIR=/tmp/rysowanie_3D

__start__: ./rysowanie_3D
	./rysowanie_3D

./rysowanie_3D: obj obj/main.o obj/lacze_do_gnuplota.o
	g++ -Wall -pedantic -std=c++11 -o ./rysowanie_3D obj/main.o\
                        obj/lacze_do_gnuplota.o


obj:
	mkdir -p obj

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -f obj/*.o ./rysowanie_3D
