#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cassert>
#include "lacze_do_gnuplota.hh"
#include "Wektor3D.hh"
#include "MacierzRot3D.hh"
#include "prostopadloscian.hh"

//do time delay:
#include <chrono>
#include <thread>

using namespace std;

using namespace std::this_thread;
using namespace std::chrono;
//const std::string kModelCuboid("bryly/model2.dat");
const string kDroneFile("bryly/drone.dat");

/*class Prostopadloscian{
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
          points[i] = mac * points[i];
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
}*/

int main()
{
  Prostopadloscian cuboid; // To tylko przykladowe definicje zmiennej
  PzG::LaczeDoGNUPlota Lacze;

  Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.
  Lacze.DodajNazwePliku(kDroneFile.c_str(), PzG::RR_Ciagly, 1);
  Lacze.ZmienTrybRys(PzG::TR_3D);

  Lacze.UstawZakresX(-40, 100);
  Lacze.UstawZakresY(-100, 100);
  Lacze.UstawZakresZ(-100, 100);

  //Lacze.UstawRotacjeXZ(40, 60); // Tutaj ustawiany jest widok
  Lacze.UstawRotacjeXZ(76, 336); // Tutaj ustawiany jest widok

  cuboid.rysuj(kDroneFile);

  Lacze.DodajNazwePliku("bryly/pow_wody.dat");

  Lacze.Rysuj(); // Gnuplot rysuje to co jest w pliku

  cout << endl
       << endl
       << "#####################################\n";
  cout << "#               MENU:               #\n";
  cout << "#   r - Zadaj ruch na wprost        #\n"; /*przemieszcza drona o zadaną odległość, wznosząc go lub obniżając*/
  cout << "#   o - Zadaj zmianę orientacji     #\n"; /*obraca drona według osi Z*/
  cout << "#   m - wyświetl menu               #\n"; /*wyswietla ponownie menu opcji*/
  cout << "#                                   #\n";
  cout << "#   k - Zakoncz działanie programu  #\n"; /*koniec dzialania programu*/
  cout << "#####################################\n";

  char wybor;
  int a;
  int odlegloscX;

  do
  {
      cout << "Twoj wybor (m - menu):  ";
      cin >> wybor;
      switch (wybor)
      {
      case 'r':
      {
          cout << endl
               << "Podaj wartość kąta (wznoszenia/opadania) w stopniach" << endl;
          cout << "Wartość kąta:     //JESZCZE NIE DZIAŁA" << endl;
          cout << endl
               << "Podaj wartość odległości, na którą ma się przemiescić dron" << endl;
          cout << "Wartość odległości:   ";
          cin >> odlegloscX;
          cout << endl;

          Wektor3D change(odlegloscX, 0, 0);

          for (int i = 0; i < 20; i++)
          {
              cuboid.translate(change / 20);
              cuboid.rysuj(kDroneFile);
              Lacze.Rysuj();
              chrono::milliseconds timespan(50);
              this_thread::sleep_for(timespan);
          }
          break;
      }
      case 'o':
      {
          cout << "Podaj wartość kąta obrotu w stopniach" << endl;
          cout << "Wartość kąta:  ";
          cin >> a;
          /*for (int i = 0; i < 16; i++)
          {
              cuboid.rotateZ(90 / 16);
              cuboid.rysuj(kDroneFile);
              Lacze.Rysuj();
              chrono::milliseconds timespan(50);
              this_thread::sleep_for(timespan);
          }*/
          cuboid.rotateZ(a);
          cuboid.rysuj(kDroneFile);
          Lacze.Rysuj();
          break;
      }
      case 'm':
      {
          cout << endl
               << endl
               << "#####################################\n";
          cout << "#               MENU:               #\n";
          cout << "#   r - Zadaj ruch na wprost        #\n";
          cout << "#   o - Zadaj zmianę orientacji     #\n";
          cout << "#   m - wyświetl menu               #\n";
          cout << "#                                   #\n";
          cout << "#   k - Zakoncz działanie programu  #\n";
          cout << "#####################################\n";
          break;
      }
      case 'k':
      {
          cout << "Koniec działania programu" << endl;
          exit(0);
          break;
      }
      default:
      {
          cout << "Nie ma takiej opcji. Prosze sprobowac ponownie" << endl
               << endl;
          break;
      }
      } /*switch*/
  } while (true);
}