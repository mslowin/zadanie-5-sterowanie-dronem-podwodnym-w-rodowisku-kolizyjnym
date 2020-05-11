#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cassert>
#include "lacze_do_gnuplota.hh"
#include "Wektor3D.hh"
//#include "MacierzRot3D.hh"


using namespace std;
const std::string kModelCuboid("bryly/model.dat");
const string kDroneFile("bryly/drone.dat");

class Prostopadloscian{
    std::vector<Wektor3D> points;
    Wektor3D translation;
    double angle;

public:
    Prostopadloscian();
    void rysuj(std::string filename) const;
    void translate(const Wektor3D& change)
    {
        translation = translation + change;
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
        outputFile << points[i] + translation << endl;
        if(i % 4 == 3) // triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
    }
}

int main()
{
  Prostopadloscian cuboid; // To tylko przykladowe definicje zmiennej
  PzG::LaczeDoGNUPlota Lacze;
  char c;

  Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.
  Lacze.DodajNazwePliku(kDroneFile.c_str(), PzG::RR_Ciagly, 1);
  Lacze.ZmienTrybRys(PzG::TR_3D);

  Lacze.UstawZakresX(-40, 100);
  Lacze.UstawZakresY(-90, 90);
  Lacze.UstawZakresZ(-80, 150);

  Lacze.UstawRotacjeXZ(40, 60); // Tutaj ustawiany jest widok

  cuboid.rysuj(kDroneFile);

  Lacze.Rysuj(); // Gnuplot rysuje to co jest w pliku
  cout << "Nacisnij ENTER, aby kontynuowac ... " << flush;
  cin >> noskipws >> c;


  Wektor3D translation(50,50,50);

  cuboid.translate(translation);
  cuboid.rysuj(kDroneFile);

  Lacze.Rysuj(); // Gnuplot rysuje to co jest w pliku
  cout << "Nacisnij ENTER, aby kontynuowac ... " << flush;
  cin >> noskipws >> c;
}
