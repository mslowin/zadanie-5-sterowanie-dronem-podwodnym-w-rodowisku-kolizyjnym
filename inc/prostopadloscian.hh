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
    MacierzRot3D rotation;
    double angle;

public:
    Prostopadloscian();
    void rysuj(std::string filename) const;
    void translate(const Wektor3D& change)
    {
        translation = translation + change;
    }
    void rotateZ(int kat)
    {
        MacierzRot3D mac;
        mac.UstawRotX_st(0);
        mac.UstawRotY_st(0);
        mac.UstawRotZ_st(kat);
        //rotation = mac;
        for (unsigned i = 0; i < points.size(); ++i)
        {
          points[i] = /*rotation*/ mac * points[i];
        }
    }
};

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
