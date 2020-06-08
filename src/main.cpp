#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cassert>
#include "lacze_do_gnuplota.hh"
#include "Wektor3D.hh"
#include "MacierzRot3D.hh"
#include "Bryla.hh"

//do time delay:
#include <chrono>
#include <thread>

//do funkcji trygonometrycznych:
#include <cmath>

using namespace std;

using namespace std::this_thread;
using namespace std::chrono;
//const std::string kModelCuboid("bryly/model2.dat");
const string kDroneFile("bryly/drone.dat");

int main()
{
  Bryla<20> cuboid;      // dron, jeszcze jako prostopadłościan bez wirników 
  PzG::LaczeDoGNUPlota Lacze;
  Wektor3D wek_przesuniecia;   

  Lacze.Inicjalizuj();          // Tutaj startuje gnuplot.
  
  Lacze.DodajNazwePliku(kDroneFile.c_str(), PzG::RR_Ciagly, 1);    //dron 
  Lacze.ZmienTrybRys(PzG::TR_3D);

  Lacze.DodajNazwePliku("bryly/pow_wody.dat");        //powierzchnia wody   
  Lacze.DodajNazwePliku("bryly/ziemia.dat");          //powierzchnia ziemi
  Lacze.DodajNazwePliku("bryly/wirnik11.dat");        //prawy wirnik
  Lacze.DodajNazwePliku("bryly/wirnik22.dat");        //lewy wirnik


  Lacze.UstawZakresX(-100, 100);
  Lacze.UstawZakresY(-100, 100);
  Lacze.UstawZakresZ(-100, 150);

  //Lacze.UstawRotacjeXZ(40, 60); // Tutaj ustawiany jest widok
  Lacze.UstawRotacjeXZ(76, 336); // Tutaj ustawiany jest widok

  cuboid.Eksportzpliku("bryly/model2.dat");
  cuboid.Importdopliku(kDroneFile);
  cuboid.rysuj(kDroneFile);

  cuboid.zorientowanie();;


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

  char wybor;              //wybor w menu
  double a;                //kąt obrotu
  double b;                //kąt opadania/wznoszenia
  double odlegloscZ;       //odległość opadania/wznoszenia (zmienna z - wertykalna)
  double odlegloscY;       //zmienna x odległośi przesunięcia 
  double odlegloscR;       //odległość przesunięcia 

  do
  {
      cout << "Twoj wybor (m - menu):  ";
      cin >> wybor;
      switch (wybor)
      {
      case 'r':
      {
          Wektor3D wek_ruchu;
          cout << endl
               << "Podaj wartość kąta (wznoszenia/opadania) w stopniach" << endl;
          cout << "Wartość kąta:   ";
          cin >> b;
          cout << endl
               << "Podaj wartość odległości, na którą ma się przemiescić dron" << endl;
          cout << "Wartość odległości:   ";
          cin >> odlegloscR;
          cout << endl;

          odlegloscZ = odlegloscR * sin((b*M_PI)/180);
          odlegloscY = odlegloscR * cos((b*M_PI)/180);

          wek_ruchu = cuboid.ruch(odlegloscY, odlegloscZ);

          for (int i = 0; i < 20; i++)
          {
              cuboid.translate(wek_ruchu / 20);
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
          //a = a / 30;
          for (int i = 0; i < 30; i++)
          {
              cuboid.rotateZ(a/30);
              cuboid.rysuj(kDroneFile);
              Lacze.Rysuj();
              chrono::milliseconds timespan(50);
              this_thread::sleep_for(timespan);
          }
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