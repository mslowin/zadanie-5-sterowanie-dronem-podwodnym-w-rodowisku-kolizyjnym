#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "Bryla.hh"
#include "Zakres.hh"
#include "Przeszkoda.hh"
#include "Dron.hh"
#include "lacze_do_gnuplota.hh"
#include "Powierzchnia.hh"

/**
 * @brief Klasa Scena zawierająca w sobie drona, powierzchnie wody, podloże i przeszkody
 * 
 * @tparam rozmiar1 rozmiar dla prostopadłościanu (dron, przeszkody)
 * @tparam rozmiar2 rozmiar dla pow wody
 * @tparam rozmiar3 rozmiar dla podłoża
 * @tparam rozmiar4 rozmiar dla wirnika
 */
template <int rozmiar1, int rozmiar2, int rozmiar3, int rozmiar4>
class Scena : public Bryla<rozmiar1 || rozmiar2 || rozmiar3 || rozmiar4>
{
    Dron<rozmiar1, rozmiar4> dron;
    Powierzchnia<rozmiar2> woda;    //bryla wody (statyczna)
    Powierzchnia<rozmiar3> podloze; //bryla podloze (statyczna)
    vector<Przeszkoda<rozmiar1>> przeszkoda;
    PzG::LaczeDoGNUPlota Lacze; //gnuplot

public:
    //metody pozwalajace dostac sie do pliku
    Dron<rozmiar1, rozmiar4> getdron() const { return dron; }
    Dron<rozmiar1, rozmiar4> &getdron() { return dron; }
    Powierzchnia<rozmiar2> getwoda() const { return woda; }
    Powierzchnia<rozmiar2> &getwoda() { return woda; }
    Powierzchnia<rozmiar3> getpodloze() const { return podloze; }
    Powierzchnia<rozmiar3> &getpodloze() { return podloze; }
    vector<Przeszkoda<rozmiar1>> getprzeszkoda() const { return przeszkoda; }
    vector<Przeszkoda<rozmiar1>> &getprzeszkoda() { return przeszkoda; }

    /**
    * @brief Construct a new Scena object
    * 
    */
    Scena()
    {
        Lacze.ZmienTrybRys(PzG::TR_3D); // Tutaj ustawiany jest tryb 3D
        Lacze.UstawZakresX(-100, 100);  // Tutaj ustawiany jest zakres X
        Lacze.UstawZakresY(-100, 100);  // Tutaj ustawiany jest zakres Y
        Lacze.UstawZakresZ(-50, 100);   // Tutaj ustawiany jest zakres Z
        Lacze.UstawRotacjeXZ(76, 336);  // Tutaj ustawiany jest widok
        Lacze.UsunWszystkieNazwyPlikow();
        Lacze.DodajNazwePliku("bryly/wirnik11.dat");
        Lacze.DodajNazwePliku("bryly/wirnik22.dat");
        Lacze.DodajNazwePliku("bryly/ziemia.dat");
        Lacze.DodajNazwePliku("bryly/pow_wody.dat");
        Lacze.DodajNazwePliku("bryly/drone.dat");
    }

    /**
     * @brief rysuje wczytane pliki (części sceny)
     * 
     */
    void rysuj()
    {
        Lacze.Rysuj();
    }

    /**
     * @brief Porównuje zakresy, aby sprawdzić, czy dochodzi do kolizji
     * 
     * @param tmp zakres pierwszego obiektu
     * @param pom zakres drugiego obiektu
     * @return int 
     */
    int porownajzakresy(Zakres tmp, Zakres pom)
    {
        int a = 0;
        if (((tmp.getx_min() <= pom.getx_min()) &&
             (tmp.getx_max() >= pom.getx_min())) ||
            ((tmp.getx_min() <= pom.getx_max()) &&
             (tmp.getx_max() >= pom.getx_max())))
        {
            a++;
        }

        if (((tmp.gety_min() <= pom.gety_min()) &&
             (tmp.gety_max() >= pom.gety_min())) ||
            ((tmp.gety_min() <= pom.gety_max()) &&
             (tmp.gety_max() >= pom.gety_max())))
        {
            a++;
        }
        if (((tmp.getz_min() <= pom.getz_min()) &&
             (tmp.getz_max() >= pom.getz_min())) ||
            ((tmp.getz_min() <= pom.getz_max()) &&
             (tmp.getz_max() >= pom.getz_max())))
        {
            a++;
        }
        if (a == 3)
            return 1;
        return 0;
    }

    /**
     * @brief Sprawdza czy doszło do kolizji i jeśli tak, to zwraca numer odpowiedzniego zderzenia
     * 1 - zderzenie z podłożem
     * 2 - zderzenie z pow. wody 
     * 3 - zderzenie z przeszkodą
     * 
     * @return double 
     */
    double czykolizja()
    {
        double czykolizja = 0;
        czykolizja = porownajzakresy(podloze.zakres(), dron.zakres());
        if (czykolizja == 1)
            return 1;
        czykolizja = porownajzakresy(woda.zakres(), dron.zakres());
        if (czykolizja == 1)
            return 2;
        for (int i = 0; i < przeszkoda.size(); i++)
        {
            czykolizja = porownajzakresy(przeszkoda[i].zakres(), dron.zakres());
            if (czykolizja == 1)
                return 3;
        }
        return 0;
    }

    /**
     * @brief Mówi z jaką przeszkodą nastąpiło zderzenie poprzez cyfrę zwróconą przez czykolizja()
     * 
     * @param tmp 
     */
    void co_sie_stalo(int tmp)
    {
        if (tmp == 1)
            cout << " zderzenie z podlozem " << endl;
        if (tmp == 2)
            cout << " wynurzenie drona " << endl;
        if (tmp == 3)
            cout << " zderzenie z przeszkoda " << endl;
    }

    /**
     * @brief Nadaje nazwę nowej, stworzonej przeszkodzie
     * 
     */
    void nazwa_przeszkody()
    {
        char *nazwa = nullptr;
        string napis = "bryly/przeszkoda";
        string liczba_porz = to_string(przeszkoda.size());
        napis += liczba_porz;
        napis += ".dat";

        cout << napis << endl;

        przeszkoda[przeszkoda.size() - 1].getnazwa() = napis;
        przeszkoda[przeszkoda.size() - 1].getprzeszkoda().Importdopliku(napis);
        int chars_to_reserve = napis.size() + 1;
        nazwa = new char[chars_to_reserve];
        strcpy(nazwa, napis.c_str());
        Lacze.DodajNazwePliku(nazwa);
    }

    /**
     * @brief metoda tworząca nową przeszkodę na scenie i zapisująca ją w nowym pliku
     * 
     */
    void dodaj_przeszkode()
    {
        // przeszkoda[0].getlp() = liczba;
        double x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0, x = 0, y = 0, z = 0;
        cout << endl << "Podaj dlugosc boków x ,y ,z >  ";
        cin >> x >> y >> z;
        cout << "Podaj wspolrzedne miejsca początku rysowania przeszkody >  ";
        cin >> x1 >> y1 >> z1;
        
        x2 = x1 + x;
        y2 = y1 + y;
        z2 = z1 + z;

        Przeszkoda<rozmiar1> obiekt = Przeszkoda<rozmiar1>();
        obiekt.tworzprzeszkode(x1, x2, y1, y2, z1, z2);
        przeszkoda.push_back(obiekt);
        nazwa_przeszkody();

        //Lacze.Rysuj();
    }
};

#endif
