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
//const string kDroneFile("bryly/drone.dat");

int main()
{
  Dron<20, 33> dron = Dron<20, 33>();
  //Przeszkoda<20> przeszkoda = Przeszkoda<20>();

  PzG::LaczeDoGNUPlota Lacze;
  Lacze.Inicjalizuj();                                               // Tutaj startuje gnuplot.
  Scena<20, 43, 25, 33> scena = Scena<20, 43, 25, 33>();             //inicjalizowanie sceny (dron, podloze, woda)
  Wektor3D wek_przesuniecia;   

  //###################
  /*
  Lacze.DodajNazwePliku(kDroneFile.c_str(), PzG::RR_Ciagly, 1);    //dron 
  Lacze.ZmienTrybRys(PzG::TR_3D);
 */
 
  //Lacze.DodajNazwePliku("bryly/pow_wody.dat");        //powierzchnia wody   
  //Lacze.DodajNazwePliku("bryly/ziemia.dat");          //powierzchnia ziemi
  //Lacze.DodajNazwePliku("bryly/wirnik11.dat");        //prawy wirnik
  //Lacze.DodajNazwePliku("bryly/wirnik22.dat");        //lewy wirnik

/*
  Lacze.UstawZakresX(-100, 100);
  Lacze.UstawZakresY(-100, 100);
  Lacze.UstawZakresZ(-50, 100);
  Lacze.UstawRotacjeXZ(76, 336); // Tutaj ustawiany jest widok
  */
  
  //Lacze.UstawRotacjeXZ(40, 60); // Tutaj ustawiany jest widok
  //###################

  scena.getpodloze().Eksportzpliku("bryly/ziemia.dat");
  scena.getpodloze().getpowierzchnia().Eksportzpliku("bryly/ziemia.dat");
  scena.getwoda().getpowierzchnia().Eksportzpliku("bryly/pow_wody.dat");

  scena.getdron().getdron().Eksportzpliku("bryly/model2.dat");
  scena.getdron().getdron().Importdopliku("bryly/drone.dat");
  scena.getdron().getdron().rysuj("bryly/drone.dat");
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

  scena.getdron().getwirnik1().wyznaczenie_punktu_symetrii();
  scena.rysuj();

  // WCZYTYWANIE PRZESZK??D ##################
      Przeszkoda<20> obiekt = Przeszkoda<20>();
      obiekt.tworzprzeszkode(80, 85, -90, 10, 0, 40);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(70, 90, 70, 90, -15, 65);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-90, -40, -90, -40, -20, -10);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-80, 0, 80, 87, 70, 77);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-80, 0, 80, 87, 30, 37);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-80, 0, 80, 87, -10, -3);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-90, -80, -90, -20, 20, 70);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      scena.rysuj();
      cout << "\n\nprzeszkody zostaly wczytane" << endl;
  //######################################## 

  //Lacze.Rysuj(); // Gnuplot rysuje to co jest w pliku
  

  cout << endl
       << endl
       << "#####################################\n";
  cout << "#               MENU:               #\n";
  cout << "#   r - Zadaj ruch na wprost        #\n"; /*przemieszcza drona o zadan?? odleg??o????, wznosz??c go lub obni??aj??c*/
  cout << "#   o - Zadaj zmian?? orientacji     #\n"; /*obraca drona wed??ug osi Z*/
  cout << "#   d - dodaj przeszkode            #\n"; /*dodaje przeszkod??*/
  cout << "#   m - wy??wietl menu               #\n"; /*wyswietla ponownie menu opcji*/
  cout << "#                                   #\n";
  cout << "#   k - Zakoncz dzia??anie programu  #\n"; /*koniec dzialania programu*/
  cout << "#####################################\n";

  char wybor;              //wybor w menu
  double a;                //k??t obrotu
  double b;                //k??t opadania/wznoszenia
  double odlegloscZ;       //odleg??o???? opadania/wznoszenia (zmienna z - wertykalna)
  double odlegloscY;       //zmienna x odleg??o??i przesuni??cia 
  double odlegloscR;       //odleg??o???? przesuni??cia

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
               << "Podaj warto???? k??ta (wznoszenia/opadania) w stopniach" << endl;
          cout << "Warto???? k??ta:   ";
          cin >> b;
          scena.getdron().getkat() = scena.getdron().getkat() + b;
          cout << endl
               << "Podaj warto???? odleg??o??ci, na kt??r?? ma si????przemiesci?? dron" << endl;
          cout << "Warto???? odleg??o??ci:   ";
          cin >> odlegloscR;
          //cin >> odl;
          cout << endl;

         // scena.poruszanie(odl, scena.getdron().getkat());

          odlegloscZ = odlegloscR * sin((b*M_PI)/180);
          odlegloscY = odlegloscR * cos((b*M_PI)/180);

          wek_ruchu = scena.getdron().getdron().ruch(odlegloscY, odlegloscZ);  //liczy si?? dobrze !
          cout << "wektor ruchu: " << wek_ruchu << endl;
          //scena.getdron().getdron().getprzesuniecie() = scena.getdron().getdron().getprzesuniecie() + wek_ruchu;
            //double kaat = dron.getkat();
            //cout << "###" << kaat << endl;

          //double radian = (3.14 * dron.getkat()) / (180);
            //cout << "radiany licz?? si?? dobrze: " << radian << endl;

          for (int i = 0; i < 200; i++)
          {
              scena.getdron().getdron().translate(wek_ruchu / 200);

              scena.getdron().getwirnik1().translate(wek_ruchu / 200);
              //obr??t wirnika 1 !!!!!!!!!!!!!                                      //Co?? mo??e z k??tem obrotu wirnik??w ???
              //dron.getwirnik1().wyznaczenie_punktu_symetrii();
              //dron.getwirnik1().obrotwir(radian);
              
              scena.getdron().getwirnik2().translate(wek_ruchu / 200);
              //obr??t wirnika 1 !!!!!!!!!!!!!
              //dron.getwirnik2().wyznaczenie_punktu_symetrii();
              //dron.getwirnik2().obrotwir(radian);

              scena.getdron().getdron().rysuj("bryly/drone.dat"); //importowanie nowych danych do pliku
              scena.getdron().getwirnik1().rysuj("bryly/wirnik11.dat"); 
              scena.getdron().getwirnik2().rysuj("bryly/wirnik22.dat");

              //Lacze.Rysuj();
              scena.rysuj();

              double czyblad;
              czyblad = scena.czykolizja();                  //TU COS NIE TAK BO OD RAZU PRZED RUCHEM WYKRYWA KOLIZJ?? I NIE POZWALA DRONOWI RUSZY??
              cout << "czy kolizja: " << czyblad << endl;    //czyblad powinien by?? wi??kszy od 0 dopiero w momencie zetkni??cia powierzchnik drona i przeszkody
              if (czyblad > 0)
              {
                  scena.co_sie_stalo(czyblad);
                  scena.getdron().getdron().popraw();
                  scena.getdron().getwirnik1().popraw();
                  scena.getdron().getwirnik2().popraw();
                  break;
              }
              chrono::milliseconds timespan(10);
              this_thread::sleep_for(timespan);
          }//for
          cout << "Przesuni??cie" << scena.getdron().getdron().getprzesuniecie() << endl;
          break; 
      }
      case 'o':
      {
          cout << "Podaj warto???? k??ta obrotu w stopniach" << endl;
          cout << "Warto???? k??ta:  ";
          cin >> a;
          for (int i = 0; i < 30; i++)
          {
              scena.getdron().getdron().rotateZ(a / 30);
              scena.getdron().getwirnik1().rotateZ(a / 30);
              scena.getdron().getwirnik2().rotateZ(a / 30);
              scena.getdron().getdron().rysuj("bryly/drone.dat");
              scena.getdron().getwirnik1().rysuj("bryly/wirnik11.dat");
              scena.getdron().getwirnik2().rysuj("bryly/wirnik22.dat");
              //Lacze.Rysuj();
              scena.rysuj();
              /*int czyblad = 0;
              czyblad = scena.czykolizja();
              if (czyblad > 0)
              {
                  scena.getdron().getdron().popraw();
                  scena.getdron().getwirnik1().popraw();
                  scena.getdron().getwirnik2().popraw();
                  scena.co_sie_stalo(czyblad);
                  break;
              }*/
              chrono::milliseconds timespan(50);
              this_thread::sleep_for(timespan);
          }
          break;
      }
      case 'd':
      {
          scena.dodaj_przeszkode();
          scena.rysuj();
          //Lacze.Rysuj();
          break;
      }
      case 'm':
      {
          cout << endl
               << endl
               << "#####################################\n";
          cout << "#               MENU:               #\n";
          cout << "#   r - Zadaj ruch na wprost        #\n";
          cout << "#   o - Zadaj zmian?? orientacji     #\n";
          cout << "#   d - dodaj przeszkode            #\n";
          cout << "#   m - wy??wietl menu               #\n";         
          cout << "#                                   #\n";
          cout << "#   k - Zakoncz dzia??anie programu  #\n";
          cout << "#####################################\n";
          break;
      }
      case 'k':
      {
          cout << "Koniec dzia??ania programu" << endl;
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
  } while (true); /*do while*/
}