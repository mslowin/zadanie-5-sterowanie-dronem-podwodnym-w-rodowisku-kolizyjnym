#ifndef ZAKR_HH
#define ZAKR_HH

#include <iostream>
#include <iomanip>
#include "Bryla.hh"
#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"
//#include "Przeszkoda.hh"

using namespace std;

class Zakres
{
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    double z_min;
    double z_max;

public:
    double getx_min() const { return x_min; }
    double &getx_min() { return x_min; }
    double getx_max() const { return x_max; }
    double &getx_max() { return x_max; }
    double gety_min() const { return y_min; }
    double &gety_min() { return y_min; }
    double gety_max() const { return y_max; }
    double &gety_max() { return y_max; }
    double getz_min() const { return z_min; }
    double &getz_min() { return z_min; }
    double getz_max() const { return z_max; }
    double &getz_max() { return z_max; }

    /**
     * @brief Construct a new Zakres object
     * 
     */
    Zakres()
    {
        double x_min = 0;
        double x_max = 0;
        double y_min = 0;
        double y_max = 0;
        double z_min = 0;
        double z_max = 0;
    }

    /*void wyswietl()
    {
        cout << x_min << " x " << x_max << endl;
        cout << y_min << " y " << y_max << endl;
        cout << z_min << " z " << z_max << endl;
    }*/
    // ~Zakres();
    // virtual Zakres zakres() =0;
};

#endif