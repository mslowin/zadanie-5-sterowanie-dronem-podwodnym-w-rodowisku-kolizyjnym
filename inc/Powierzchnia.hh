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
};

#endif
