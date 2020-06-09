#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include <iostream>
#include <iomanip>
#include "Bryla.hh"
#include "Przeszkoda.hh"
#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"

using namespace std;

template <int rozmiar>
class Powierzchnia : public Bryla<rozmiar>
{
private:
    Bryla<rozmiar> powierzchnia;

public:
    Bryla<rozmiar> getpowierzchnia() const { return powierzchnia; }
    Bryla<rozmiar> &getpowierzchnia() { return powierzchnia; }
    Powierzchnia() : Bryla<rozmiar>(){};

    virtual Zakres zakres()//shared_ptr<Zakres> tmp)
    {
        Zakres tmp;
        tmp.getx_min() = powierzchnia.mini('X');
        tmp.getx_max() = powierzchnia.maxi('X');
        tmp.gety_min() = powierzchnia.mini('Y');
        tmp.gety_max() = powierzchnia.maxi('Y');
        tmp.getz_min() = powierzchnia.mini('Z');
        tmp.getz_max() = powierzchnia.maxi('Z');
        return tmp;
    }
};

#endif
