#ifndef PROST_HH
#define PROST_HH

#include "Wektor3D.hh"
#include "MacierzRot3D.hh"
#include "lacze_do_gnuplota.hh"

#include <vector>
using namespace std;

const std::string kModelCuboid("bryly/model2.dat");

class Prostopadloscian{
    std::vector<Wektor3D> points;
    Wektor3D translation;
    Wektor3D orientacja;
    MacierzRot3D rotation;
    double angle;

public:
    Prostopadloscian();
    Wektor3D getprzesuniecie() const { return translation; }
    Wektor3D &getprzesuniecie() { return translation; }
    Wektor3D getorientacja() const { return orientacja; }
    Wektor3D &getorientacja() { return orientacja; }
    void rysuj(std::string filename) const;

    /**
     * @brief obraca prostopadłościan według osi Z
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

    void zorientowanie()
    {
        orientacja = points[1] - points[0];
        orientacja = orientacja / 10;       //bok ma 10
    }

    /**
     * @brief przesuwa prostopadłościan o wektor
     * 
     * @param change wektor przesunięcia [x,y,z]
     */
    void translate(const Wektor3D& change)
    {
        
        translation = translation + change;
    }


};

/**
 * @brief konstruuje nowy Prostopadloscian:: Prostopadloscian object
 * 
 */
Prostopadloscian::Prostopadloscian(): angle{0}
{
    ifstream inputFile;
    inputFile.open(kModelCuboid);
    if(!inputFile.is_open())
    {
        cerr << "Unable to load model Cuboid file!" 
             << endl;
        return;
    }

    Wektor3D point;
    while(inputFile >> point)
    {
        points.push_back(point);
    }
    inputFile.close();
}

/**
 * @brief rysuje prostopadłościan do pliku
 * 
 * @param filename nazwa pliku w którym zapisuje
 */
void Prostopadloscian::rysuj(std::string filename) const
{
    ofstream outputFile;
    outputFile.open(filename);
    if(!outputFile.is_open())
    {
        cerr << "Unable to open drone file!" << endl;
        return;
    }
    for(unsigned i = 0; i < points.size(); ++i)
    {
      
      //sleep_until(system_clock::now() + seconds(1));
        outputFile << points[i] + translation << endl;
        //sleep_for(nanoseconds(10000));
        if(i % 4 == 3) // triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
    }
}

#endif
