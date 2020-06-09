#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include <iomanip>
#include "Wektor3D.hh"
#include "MacierzRot3D.hh"
#include "lacze_do_gnuplota.hh"
#include "Bryla.hh"
#include "Zakres.hh"
#include "Przeszkoda.hh"

#include <vector>
#include <cmath>
using namespace std;

// tu będzie klasa składająca się z 3 części: prostopadłościan, śruba1, śruba2
// coś na wzór układu równań liniowych

template <int rozmiar1, int rozmiar2>
class Dron : public Bryla<rozmiar1>
{
    Bryla<rozmiar1> dron;
    Bryla<rozmiar2> wirnik1;
    Bryla<rozmiar2> wirnik2;
    Wektor3D lok_w1;
    Wektor3D lok_w2;

    public:
    Bryla<rozmiar1> getdron() const { return dron; }
    Bryla<rozmiar1> &getdron() { return dron; }
    Bryla<rozmiar2> getwirnik1() const { return wirnik1; }
    Bryla<rozmiar2> &getwirnik1() { return wirnik1; }
    Bryla<rozmiar2> getwirnik2() const { return wirnik2; }
    Bryla<rozmiar2> &getwirnik2() { return wirnik2; }
    Wektor3D getlok_w1() const { return lok_w1; }
    Wektor3D &getlok_w1() { return lok_w1; }
    Wektor3D getlok_w2() const { return lok_w2; }
    Wektor3D &getlok_w2() { return lok_w2; }

    Dron()
    {
        Wektor3D obiekt;
        obiekt[0] = 0;
        obiekt[1] = 0;
        obiekt[2] = 0;
        for (int i = 0; i < rozmiar1; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                dron.getbryla().push_back(obiekt); //funkcja std::vector
            }
        }
        for (int i = 0; i < rozmiar2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                wirnik1.getbryla().push_back(obiekt); //funkcja std::vector
                wirnik2.getbryla().push_back(obiekt);
            }
        }
        dron.getkat() = 0;
        wirnik1.getkat() = 0;
        wirnik2.getkat() = 0;
    }

    virtual Zakres zakres()
    {
        Zakres tmp;
        tmp.getx_min() = dron.mini('X') + (dron.mini('X') - wirnik1.mini('X'));
        tmp.getx_max() = dron.maxi('X'); //+ (dron.maxi('X')-wirnik1.maxi('X');
        tmp.gety_min() = dron.mini('Y');
        tmp.gety_max() = dron.maxi('Y');
        tmp.getz_min() = dron.mini('Z');
        tmp.getz_max() = dron.maxi('Z');
        return tmp;
    }
};

#endif