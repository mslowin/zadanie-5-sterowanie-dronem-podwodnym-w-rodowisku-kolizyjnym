#ifndef PROST_HH
#define PROST_HH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include "Wektor3D.hh"
#include "MacierzRot3D.hh"
#include "lacze_do_gnuplota.hh"
#include "SWektor.hh"
#include "Zakres.hh"

#include <vector>
#include <cmath>
using namespace std;

const std::string kModelCuboid("bryly/model2.dat");
//const std::string kModelWirnik1("bryly/modelwirnik11.dat");
//const std::string kModelWirnik2("bryly/modelwirnik22.dat");

/**
 * @brief klasa tworząca bryły (dron, przeszkody, itd.)
 * 
 * @tparam rozmiar bryły, czyli ile linijek współrzędnych zajmuje bryła
 */
template <int rozmiar>
class Bryla{
    std::vector<Wektor3D> points;
    Wektor3D translation;
    Wektor3D orientacja;
    MacierzRot3D rotation;    
    Wektor3D punktsymetrii;
    double angle;


public:
    Wektor3D operator[](int Ind) const { return points[Ind]; }
    Wektor3D &operator[](int Ind) { return points[Ind]; }
    vector<Wektor3D> getbryla() const { return points; }
    vector<Wektor3D> &getbryla() { return points; }
    Wektor3D getprzesuniecie() const { return translation; }
    Wektor3D &getprzesuniecie() { return translation; }
    Wektor3D getorientacja() const { return orientacja; }
    Wektor3D &getorientacja() { return orientacja; }
    MacierzRot3D getrotation() const { return rotation; }
    MacierzRot3D &getrotation() { return rotation; }
    double getkat() const { return angle; }
    double &getkat() { return angle; }

    /**
     * @brief Rysuje, czyli wpisuje do pliku współżędne punktów bryły w zależności od rozmiaru
     * 
     * @param filename nazwa pliku który będzie nadpisywany
     */
    void rysuj(std::string filename) const
    {
        ofstream outputFile;
        outputFile.open(filename);
        if (!outputFile.is_open())
        {
            cerr << "Unable to open drone file!" << endl;
            return;
        }
        for (unsigned i = 0; i < rozmiar /*points.size()*/; ++i)
        {
            outputFile << points[i] + translation << endl;
            if (i % 4 == 3) // triggers after every 4 points
            {
                outputFile << "#\n\n";
            }
        }
    }

    /**
     * @brief Construct a new Bryla object
     * 
     */
    Bryla()
    {
        Wektor3D obiekt;
        obiekt[0] = 0;
        obiekt[1] = 0;
        obiekt[2] = 0;
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                points.push_back(obiekt); //funkcja std::vector
            }
        }
    }

    /**
     * @brief metoda sluzaca zapisowi wierzcholkow do pliku (właściwie niepotrzebna bo robi to samo0 co rysuj())
     * 
     * @param sciezka nazwa pliku w którym będą zapisywane wierzchołki
     */
    void Importdopliku(string sciezka) //wpisuje sciezke
    {
        ofstream zapis(sciezka); //tworze plik
        for (unsigned i = 0; i < rozmiar; i++)
        {
            for (unsigned j = 0; j < 3; j++)
            {
                zapis << points[i][j] << " "; //zapisuje w pliku
            }
            zapis << endl;
        }
        zapis.close(); //zamykam plik
    }
    /**
     * @brief metoda sluzaca pobraniu wierzcholkow z pliku
     * 
     * @param plik nazwa pliku z którego będą zczytywane dane
     */
    void Eksportzpliku(string plik) //wpisuje sciezke
    {
        ifstream file;
        file.open(plik.c_str()); //otwieram plik
        for (unsigned i = 0; i < rozmiar; i++)
        {
            for (unsigned j = 0; j < 3; j++)
            {
                file >> points[i][j]; //zczytuje z pliku do programu
            }
        }
    }

    /**
     * @brief Pozwala na ruch drona, ustawia orientację bryły
     * 
     */
    void zorientowanie()
    {
        orientacja = points[1] - points[0];
        orientacja = orientacja / 10;       //bok ma 10
        orientacja[2] = 0;
    }

    /**
     * @brief Zwraca minimalną wartość współżędnej X, Y lub Z
     * 
     * @param tmp nazwa współżędnej ('X', 'Y' lub 'Z')
     * @return double 
     */
    double mini(char tmp)
    {
        double a = 100;
        if (tmp == 'X')
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = min(points[i][0], a);
            }
        }
        if (tmp == 'Y')
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = min(points[i][1], a);
            }
        }

        if (tmp == 'Z')
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = min(points[i][2], a);
            }
        }
        return a;
    }

    /**
     * @brief Zwraca maksymalną wartość współżędnej X, Y lub Z
     * 
     * @param tmp nazwa współżędnej ('X', 'Y' lub 'Z')
     * @return double 
     */
    double maxi(char tmp)
    {
        double a = -100;
        if (tmp == 'X')
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = max(points[i][0], a);
            }
        }
        if (tmp == 'Y')
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = max(points[i][1], a);
            }
        }
        if (tmp == 'Z')
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = max(points[i][2], a);
            }
        }
        return a;
    }

    /**
     * @brief obraca bryłę według osi Z
     * 
     * @param kat kąt obrotu w stopniach
     */
    void rotateZ(double kat)
    {
        MacierzRot3D mac;
        mac.UstawRotX_st(0);
        mac.UstawRotY_st(0);
        mac.UstawRotZ_st(kat);
        rotation = mac;
        for (unsigned i = 0; i < points.size(); ++i)
        {
          points[i] = rotation * points[i];
        }
        zorientowanie();
    }

    /**
     * @brief obraca bryłę według osi X
     * 
     * @param kat kąt obrotu w stopniach
     */
    void rotateX(double kat)
    {
        MacierzRot3D mac;
        mac.UstawRotX_st(kat);
        mac.UstawRotY_st(0);
        mac.UstawRotZ_st(0);
        rotation = mac;
        for (unsigned i = 0; i < points.size(); ++i)
        {
          points[i] = rotation * points[i];
        }
        zorientowanie();
    }

    /**
     * @brief Metoda wyznaczająca punkt symetrii bryły
     * 
     */
    void wyznaczenie_punktu_symetrii()
    {
        punktsymetrii[0] = (mini('X') + maxi('X')) / 2;
        punktsymetrii[1] = (mini('Y') + maxi('Y')) / 2;
        punktsymetrii[2] = (mini('Z') + maxi('Z')) / 2;
        //cout << punktsymetrii[0] << " " << punktsymetrii[1] << " " << punktsymetrii[2] << endl; jest dobrze
    }

    /**
     * @brief obraca bryłę według osi X (dla wirników)
     * 
     * @param radian kąt obrotu w radianach
     * @return SMacierz<double, 3> 
     */
    SMacierz<double, 3> os_obrotuX(double radian)
    {
        /*MacierzRot3D mac;
        mac.UstawRotX_st(radian);
        mac.UstawRotY_st(0);
        mac.UstawRotZ_st(0);
        //mac = rotation;
        for (unsigned i = 0; i < points.size(); ++i)
        {
          points[i] = mac * points[i];
        }
        return mac;*/

        SMacierz<double, 3> pom;
        pom[0][0] = 1;
        pom[0][1] = 0;
        pom[0][2] = 0;
        pom[1][0] = 0;
        pom[1][1] = cos(radian);
        pom[1][2] = -1 * sin(radian);
        pom[2][0] = 0;
        pom[2][1] = sin(radian);
        pom[2][2] = cos(radian);

        return pom;
    }

    /**
     * @brief obraca bryłę według osi Y (dla wirników)
     * 
     * @param radian kąt obrotu w radianach
     * @return SMacierz<double, 3> 
     */
    SMacierz<double, 3> os_obrotuY(double radian)
    {
        SMacierz<double, 3> pom;
        pom[0][0] = cos(radian);
        pom[1][1] = 1;
        pom[0][2] = sin(radian);
        pom[2][0] = -1 * sin(radian);
        pom[2][2] = pom[0][0];

        return pom;
    }

    /**
     * @brief obraca bryłę według osi Z (dla wirników)
     * 
     * @param radian kąt obrotu w radianach
     * @return SMacierz<double, 3> 
     */
    SMacierz<double, 3> os_obrotuZ(double radian)
    {
        SMacierz<double, 3> pom;
        pom[0][1] = -1 * sin(radian);
        pom[1][0] = sin(radian);
        pom[1][1] = cos(radian);
        pom[0][0] = pom[1][1];
        pom[2][2] = 1;

        return pom;
    }

    /**
     * @brief Metoda służąca obracaniu wirników
     * 
     * @param radian kąt obrotu w radianach
     */
    void obrotwir(double radian)
    {
        //w tym miejscu dla kąta 0 jest 0 radianów
        MacierzRot3D pom;
        for (int i = 0; i < 3; i++)
        {
            punktsymetrii[i] = -1 * punktsymetrii[i]; //zmiana okrientacji wektora przesuniecia
        }

        translate(punktsymetrii); //powrot do (0,0,0)
        pom = os_obrotuY(-1 * radian);
        for (int i = 0; i < rozmiar; i++)
        {
            points[i] = pom * points[i]; //zmiana kata
        }

        pom = os_obrotuX(radian + 0.1);
        for (int i = 0; i < rozmiar; i++)
        {
            points[i] = pom * points[i]; //zmiana kata
        }
        pom = os_obrotuZ(radian);
        for (int i = 0; i < rozmiar; i++)
        {
            points[i] = pom * points[i]; //zmiana kata
        }
        for (int i = 0; i < 3; i++)
        {
            punktsymetrii[i] = -1 * punktsymetrii[i]; //zmiana okrientacji wektora przesuniecia
        }
        translate(punktsymetrii); //powrot do wczesniejszej lokalizacji
        // przesun(przesuniecie);
        zorientowanie(); //aktualizacja orientacji
        //cout << orientacja << endl;  chyba jest dobrze
    }

    /**
     * @brief przesuwa bryłę o wektor
     * 
     * @param change wektor przesunięcia [x,y,z]
     */
    void translate(const Wektor3D& change)
    {   

        translation = translation + change;
    }

    /**
     * @brief oblicza wektor ruchu, żeby potem za pomocą metody translate() przesunąć bryłę
     * 
     * @param poY odległość wzdłóż osi Y
     * @param poZ odległość wzdłóż osi Z 
     * @return Wektor3D 
     */
    Wektor3D ruch(double poY, double poZ)
    {
        Wektor3D wek_ruchu;       //wektor ruchu, glowny wektor
        Wektor3D osZ, osY;        //wektor pomocnik, wektor osi Z i XY
        osZ[0] = 0;
        osZ[1] = 0;
        osZ[2] = 1;
        //cout << endl << orientacja << endl;  //wyświetla wektor orientacji
        osY = orientacja;       //ustawienie doberj orientacji XY

        osZ = osZ * poZ;       //aktualizacja osi Z , pomnozenie razy dlugosc wzniosu
        osY = osY * poY;       //aktualizacja osi XY , pomnozenie razy dlugosc ruchu
        wek_ruchu = osZ + osY; //skladowa osi Z i XY

        return wek_ruchu;
    }

    /**
     * @brief Metoda poprawia położenie bryły po zderzeniu z przeszkodą
     * 
     */
    void popraw()
    {
        cout << "######" << endl;
        Bryla<rozmiar> tmp = Bryla<rozmiar>();
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tmp[i][j] = round(points[i][j]);
                points[i][j] =tmp[i][j];
            }
        }
    }

};

#endif
