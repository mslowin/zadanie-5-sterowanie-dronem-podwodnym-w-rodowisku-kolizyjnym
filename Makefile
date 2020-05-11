#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++11

TRGDIR=/tmp/rysowanie_3D

OBJECTS= obj/main.o obj/lacze_do_gnuplota.o obj/MacierzRot3D.o


__start__: ./rysowanie_3D
	./rysowanie_3D

./rysowanie_3D: obj ${OBJECTS}
	g++ -Wall -pedantic -std=c++11 -o ./rysowanie_3D ${OBJECTS}

obj:
	mkdir -p obj

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/MacierzRot3D.o: src/MacierzRot3D.cpp inc/MacierzRot3D.hh
	g++ -c ${CXXFLAGS} -o obj/MacierzRot3D.o src/MacierzRot3D.cpp



clear:
	rm -f obj/*.o ./rysowanie_3D
