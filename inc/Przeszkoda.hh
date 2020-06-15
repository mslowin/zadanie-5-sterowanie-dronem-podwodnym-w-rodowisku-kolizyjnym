#ifndef PRZESZKODA_HH
#define PRZESZKODA_HH
#include <iostream>
#include <iomanip>
#include "Bryla.hh"
#include "Wektor3D.hh"
#include "Zakres.hh"
#include "lacze_do_gnuplota.hh"

using namespace std;

/**
 * @brief Klasa tworząca przeszkodę (prostopadłościan)
 * 
 * @tparam rozmiar rozmiar przeszkody (ile linijek współżędnych jest w pliku)
 */
template<int rozmiar>
class Przeszkoda : public Bryla<rozmiar>
{
    Bryla<rozmiar> przeszkoda;
    vector<SWektor<double, 3>> wek_orient;
    string nazwa;

public:
    Bryla<rozmiar> getprzeszkoda() const { return przeszkoda; }
    Bryla<rozmiar> &getprzeszkoda() { return przeszkoda; }
    vector<SWektor<double, 3>> getwek_orient() const { return wek_orient; }
    vector<SWektor<double, 3>> &getwek_orient() { return wek_orient; }
    string getnazwa() const { return nazwa; }
    string &getnazwa() { return nazwa; }

    /**
     * @brief Construct a new Przeszkoda object
     * 
     */
    Przeszkoda()
    {
        Wektor3D obiekt;
        obiekt[0] = 0;
        obiekt[1] = 0;
        obiekt[2] = 0;
        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                przeszkoda.getbryla().push_back(obiekt); //funkcja std::vector
            }
        }
        for (int i = 0; i < 4; i++)
        {
            wek_orient.push_back(obiekt);
        }
    }

    /**
     * @brief Tworzy nową przeszkodę za pomocą podanych zakresów
     * 
     * @param x1 zakres "od" dla x
     * @param x2 zakres "do" dla x
     * @param y1 zakres "od" dla y
     * @param y2 zakres "do" dla y
     * @param z1 zakres "od" dla z
     * @param z2 zakres "do" dla z
     */
    void tworzprzeszkode(double x1, double x2, double y1, double y2, double z1, double z2)
    {
        przeszkoda.getbryla() [0].wektorXYZ(x1, y1, z1);
        przeszkoda.getbryla() [1].wektorXYZ(x2, y1, z1);
        przeszkoda.getbryla() [2].wektorXYZ(x2, y2, z1);
        przeszkoda.getbryla() [3].wektorXYZ(x1, y2, z1);
        przeszkoda.getbryla() [4].wektorXYZ(x1, y1, z1);
        przeszkoda.getbryla() [5].wektorXYZ(x1, y1, z2);
        przeszkoda.getbryla() [6].wektorXYZ(x2, y1, z2);
        przeszkoda.getbryla() [7].wektorXYZ(x2, y1, z1);
        przeszkoda.getbryla() [8].wektorXYZ(x2, y1, z2);
        przeszkoda.getbryla() [9].wektorXYZ(x2, y2, z2);
        przeszkoda.getbryla()[10].wektorXYZ(x2, y2, z1);
        przeszkoda.getbryla()[11].wektorXYZ(x2, y2, z2);
        przeszkoda.getbryla()[12].wektorXYZ(x1, y2, z2);
        przeszkoda.getbryla()[13].wektorXYZ(x1, y2, z1);
        przeszkoda.getbryla()[14].wektorXYZ(x1, y2, z2);
        przeszkoda.getbryla()[15].wektorXYZ(x1, y1, z2);
        przeszkoda.getbryla()[16].wektorXYZ(x2, y1, z2);
        przeszkoda.getbryla()[17].wektorXYZ(x2, y2, z1);
        przeszkoda.getbryla()[18].wektorXYZ(x2, y2, z2);
        przeszkoda.getbryla()[19].wektorXYZ(x2, y1, z1);

        wek_orient[0] = x2 - x1;
        wek_orient[1] = y2 - y1;
        wek_orient[2] = z2 - z1;
    }

    /**
     * @brief Sprawdza i zwraca zakres przeszkody
     * 
     * @return Zakres zakres przeszkody
     */
    virtual Zakres zakres()
    {
        Zakres tmp;
        tmp.getx_min() = przeszkoda.mini('X');
        tmp.getx_max() = przeszkoda.maxi('X');
        tmp.gety_min() = przeszkoda.mini('Y');
        tmp.gety_max() = przeszkoda.maxi('Y');
        tmp.getz_min() = przeszkoda.mini('Z');
        tmp.getz_max() = przeszkoda.maxi('Z');
        return tmp;
    }
};

#endif