#ifndef ZAKR_HH
#define ZAKR_HH

#include <iostream>
#include <iomanip>
#include "Bryla.hh"
#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"
using namespace std;

class Zakres
{
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;

public:
    float getx_min() const { return x_min; }
    float &getx_min() { return x_min; }
    float getx_max() const { return x_max; }
    float &getx_max() { return x_max; }
    float gety_min() const { return y_min; }
    float &gety_min() { return y_min; }
    float gety_max() const { return y_max; }
    float &gety_max() { return y_max; }
    float getz_min() const { return z_min; }
    float &getz_min() { return z_min; }
    float getz_max() const { return z_max; }
    float &getz_max() { return z_max; }

    Zakres()
    {
        float x_min = 0;
        float x_max = 0;
        float y_min = 0;
        float y_max = 0;
        float z_min = 0;
        float z_max = 0;
    }

    /* void wyswietl()
    {
        cout << x_min << " x " << x_max << endl;
        cout << y_min << " y " << y_max << endl;
        cout << z_min << " z " << z_max << endl;
    }*/
    // ~Zakres();
    // virtual Zakres zakres() =0;
};

#endif