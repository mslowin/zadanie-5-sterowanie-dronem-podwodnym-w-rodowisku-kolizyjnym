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
#include "Dron.hh"
#include "Zakres.hh"
#include "Przeszkoda.hh"
#include "scena.hh"
#include "Powierzchnia.hh"

//do time delay:
#include <chrono>
#include <thread>

//do funkcji trygonometrycznych:
#include <cmath>

using namespace std;

using namespace std::this_thread;
using namespace std::chrono;
const string kDroneFile("bryly/drone.dat");

int main()
{
  //Bryla<20> cuboid;      // dron, jeszcze jako prostopadłościan bez wirników 
  //Bryla<33> wirnik1;
  Dron<20, 33> dron = Dron<20, 33>();
  //Przeszkoda<20> przeszkoda = Przeszkoda<20>();

  PzG::LaczeDoGNUPlota Lacze;
  Lacze.Inicjalizuj();          // Tutaj startuje gnuplot.
  Scena<20, 43, 25, 33> scena = Scena<20, 43, 25, 33>();             //inicjalizowanie sceny (dron, podloze, woda)
  Wektor3D wek_przesuniecia;   

  
  
  //###################
  Lacze.DodajNazwePliku(kDroneFile.c_str(), PzG::RR_Ciagly, 1);    //dron 
  Lacze.ZmienTrybRys(PzG::TR_3D);
  //Lacze.DodajNazwePliku("bryly/pow_wody.dat");        //powierzchnia wody   
  //Lacze.DodajNazwePliku("bryly/ziemia.dat");          //powierzchnia ziemi
  //Lacze.DodajNazwePliku("bryly/wirnik11.dat");        //prawy wirnik
  //Lacze.DodajNazwePliku("bryly/wirnik22.dat");        //lewy wirnik


  Lacze.UstawZakresX(-100, 100);
  Lacze.UstawZakresY(-100, 100);
  Lacze.UstawZakresZ(-50, 100);

  //Lacze.UstawRotacjeXZ(40, 60); // Tutaj ustawiany jest widok
  Lacze.UstawRotacjeXZ(76, 336); // Tutaj ustawiany jest widok
  //###################
  
  //cuboid.Eksportzpliku("bryly/model2.dat");
  //cuboid.Importdopliku(kDroneFile);
  //cuboid.rysuj(kDroneFile);

  scena.getdron().getdron().Eksportzpliku("bryly/model2.dat");
  scena.getdron().getdron().Importdopliku("bryly/drone.dat");
  scena.getdron().getdron().rysuj(kDroneFile);
  scena.getdron().getwirnik1().Eksportzpliku("bryly/modelwirnik11.dat");
  scena.getdron().getwirnik1().Importdopliku("bryly/wirnik11.dat");
  scena.getdron().getwirnik1().rysuj("bryly/wirnik11.dat");
  scena.getdron().getwirnik2().Eksportzpliku("bryly/modelwirnik22.dat");
  scena.getdron().getwirnik2().Importdopliku("bryly/wirnik22.dat");
  scena.getdron().getwirnik2().rysuj("bryly/wirnik22.dat");

  //dron.getwirnik1().wyznaczenie_punktu_symetrii();
  //dron.getwirnik2().wyznaczenie_punktu_symetrii();

  //wirnik1.Eksportzpliku("bryly/modelwirnik11.dat");
  //wirnik1.Importdopliku("bryly/wirnik11.dat");
  //wirnik1.rysuj("bryly/wirnik11.dat");

  scena.getdron().getdron().zorientowanie();
  scena.getdron().getwirnik1().zorientowanie();
  scena.getdron().getwirnik2().zorientowanie();

  Lacze.Rysuj(); // Gnuplot rysuje to co jest w pliku

  cout << endl
       << endl
       << "#####################################\n";
  cout << "#               MENU:               #\n";
  cout << "#   r - Zadaj ruch na wprost        #\n"; /*przemieszcza drona o zadaną odległość, wznosząc go lub obniżając*/
  cout << "#   o - Zadaj zmianę orientacji     #\n"; /*obraca drona według osi Z*/
  cout << "#   d - dodaj przeszkode            #\n"; /*dodaje przeszkodę*/
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
          dron.getkat() = dron.getkat() + b;
          cout << endl
               << "Podaj wartość odległości, na którą ma się przemiescić dron" << endl;
          cout << "Wartość odległości:   ";
          cin >> odlegloscR;
          cout << endl;

          odlegloscZ = odlegloscR * sin((b*M_PI)/180);
          odlegloscY = odlegloscR * cos((b*M_PI)/180);

          wek_ruchu = scena.getdron().getdron().ruch(odlegloscY, odlegloscZ);  //liczy się dobrze !
          cout << "wektor ruchu: " << wek_ruchu << endl;
            //double kaat = dron.getkat();
            //cout << "###" << kaat << endl;

          //double radian = (3.14 * dron.getkat()) / (180);
            //cout << "radiany liczą się dobrze: " << radian << endl;

          for (int i = 0; i < 200; i++)
          {
              scena.getdron().getdron().translate(wek_ruchu / 200);

              scena.getdron().getwirnik1().translate(wek_ruchu / 200);
              /*obrót wirnika 1 !!!!!!!!!!!!!*/                                        /*Coś może z kątem obrotu wirników ???*/
              //dron.getwirnik1().wyznaczenie_punktu_symetrii();
              //dron.getwirnik1().obrotwir(radian);
              
              scena.getdron().getwirnik2().translate(wek_ruchu / 200);
              /*obrót wirnika 1 !!!!!!!!!!!!!*/
              //dron.getwirnik2().wyznaczenie_punktu_symetrii();
              //dron.getwirnik2().obrotwir(radian);

              scena.getdron().getdron().rysuj(kDroneFile); //importowanie nowych danych do pliku
              scena.getdron().getwirnik1().rysuj("bryly/wirnik11.dat"); 
              scena.getdron().getwirnik2().rysuj("bryly/wirnik22.dat");

              Lacze.Rysuj();
              chrono::milliseconds timespan(10);
              this_thread::sleep_for(timespan);
          }
          break; 
      }
      case 'o':
      {
          cout << "Podaj wartość kąta obrotu w stopniach" << endl;
          cout << "Wartość kąta:  ";
          cin >> a;
          for (int i = 0; i < 30; i++)
          {
              scena.getdron().getdron().rotateZ(a / 30);
              scena.getdron().getwirnik1().rotateZ(a / 30);
              scena.getdron().getwirnik2().rotateZ(a / 30);
              scena.getdron().getdron().rysuj(kDroneFile);
              scena.getdron().getwirnik1().rysuj("bryly/wirnik11.dat");
              scena.getdron().getwirnik2().rysuj("bryly/wirnik22.dat");
              Lacze.Rysuj();
              chrono::milliseconds timespan(50);
              this_thread::sleep_for(timespan);
          }
          break;
      }
      case 'd':
      {
          scena.dodaj_przeszkode();
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
          cout << "#   d - dodaj przeszkode            #\n";
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