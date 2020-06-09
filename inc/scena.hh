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

template <int rozmiar1, int rozmiar2, int rozmiar3, int rozmiar4>
class Scena : public Bryla<rozmiar1 || rozmiar2 || rozmiar3 || rozmiar4>
{
    Dron<rozmiar1, rozmiar4> dron;
    //Powierzchnia<rozmiar2> woda;    //bryla wody (statyczna)
    //Powierzchnia<rozmiar3> podloze; //bryla podloze (statyczna)
    vector<Przeszkoda<rozmiar1>> przeszkoda;
    PzG::LaczeDoGNUPlota Lacze; //gnuplot

public:
    //metody pozwalajace dostac sie do pliku
    Dron<rozmiar1, rozmiar4> getdron() const { return dron; }
    Dron<rozmiar1, rozmiar4> &getdron() { return dron; }
    //Powierzchnia<rozmiar2> getwoda() const { return woda; }
    //Powierzchnia<rozmiar2> &getwoda() { return woda; }
    //Powierzchnia<rozmiar3> getpodloze() const { return podloze; }
    //Powierzchnia<rozmiar3> &getpodloze() { return podloze; }
    vector<Przeszkoda<rozmiar1>> getprzeszkoda() const { return przeszkoda; }
    vector<Przeszkoda<rozmiar1>> &getprzeszkoda() { return przeszkoda; }
    //metoda rysujaca z plikow w gnuplocie
    /*void rysuj()
    {
        Lacze.Rysuj();
    }*/

    //konstruktor wywolywany na poczatku programu
    Scena()
    {
        Lacze.ZmienTrybRys(PzG::TR_3D); // Tutaj ustawiany jest tryb 3D
        Lacze.UstawZakresX(-100, 100);  // Tutaj ustawiany jest zakres X
        Lacze.UstawZakresY(-100, 100);  // Tutaj ustawiany jest zakres Y
        Lacze.UstawZakresZ(-50, 100);   // Tutaj ustawiany jest zakres Z
        Lacze.UstawRotacjeXZ(60, 40);    // Tutaj ustawiany jest widok
        Lacze.UsunWszystkieNazwyPlikow();
        Lacze.DodajNazwePliku("bryly/wirnik11.dat");
        Lacze.DodajNazwePliku("bryly/wirnik22.dat");
        Lacze.DodajNazwePliku("bryly/ziemia.dat");
        Lacze.DodajNazwePliku("bryly/pow_wody.dat");
        Lacze.DodajNazwePliku("bryly/drone.dat");
    }

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

    int czykolizja()
    {
        /*int czykolizja = 0;
        czykolizja = porownajzakresy(podloze.zakres(), dron.zakres());
        if (czykolizja == 1)
            return 1;
        czykolizja = porownajzakresy(woda.zakres(), dron.zakres());
        if (czykolizja == 1)
            return 2;*/
        for (int i = 0; i < przeszkoda.size(); i++)
        {
            czykolizja = porownajzakresy(przeszkoda[i].zakres(), dron.zakres());
            if (czykolizja == 1)
                return 3;
        }
        return 0;
    }

    void co_sie_stalo(int tmp)
    {
        if (tmp == 1)
            cout << " zderzenie z podlozem " << endl;
        if (tmp == 2)
            cout << " wynurzenie drona " << endl;
        if (tmp == 3)
            cout << " zderzenie z przeszkoda " << endl;
    }

    /*void obracanie(double kat, char a)
    {
        cout << "podany kat:  " << kat << endl;
        double obr, radian;
        radian = (3.14 * kat) / (180);
        radian = radian / 200;
        cout << "o ktory sie obraca:  " << radian << endl;
        for (int i = 0; i < 200 - 1; i++)
        {
            obr = (3.14 * dron.getdron().getkat()) / 180 + radian * i;

            dron.getdron().obrot(dron.getdron().getprzesuniecie(), radian, a); //obracanie drona (inc/bryla.hh)

            dron.getwirnik1().obrot(dron.getdron().getprzesuniecie(), radian, a);
            dron.getwirnik1().wyznaczenie_punktu_symetrii();
            dron.getwirnik1().obrotwir(obr);

            dron.getwirnik2().obrot(dron.getdron().getprzesuniecie(), radian, a);
            dron.getwirnik2().wyznaczenie_punktu_symetrii();
            dron.getwirnik2().obrotwir(obr);

            dron.getdron().Importdopliku("bryly/dron1.dat"); //importowanie nowych danych do pliku
            dron.getwirnik1().Importdopliku("bryly/wirnikk1.dat");
            dron.getwirnik2().Importdopliku("bryly/wirnikk2.dat");
            rysuj(); //wyrysowanie nowej sceny
            int czyblad = 0;
            czyblad = czykolizja();

            // czyblad = czy_nastapilo_zderzenie();
            if (czyblad > 0)
            {
                dron.getdron().napraw();
                dron.getwirnik1().napraw();
                dron.getwirnik2().napraw();
                co_sie_stalo(czyblad);
                break;
            }
            // funkcje z biblioteki "chrono" sluzace do opoznienia programu (plynnego przejscia drona)
            chrono::milliseconds timespan(10); //"100" 100 ms to 0,1sek.
            this_thread::sleep_for(timespan);
        }
        dron.getdron().getkat() = dron.getdron().getkat() + kat;
        dron.getwirnik1().getkat() = dron.getwirnik1().getkat() + kat;
        dron.getwirnik2().getkat() = dron.getwirnik2().getkat() + kat;
    }*/

    /*void poruszanie(float odl, double kat)
    {
        Wektor wek_ruchu;
        Wektor wek_przesuniecia;

        wek_ruchu = dron.getdron().ruch(odl, kat); //funkcja do utrzymania porzadku (inc/bryla.hh)
        dron.getdron().getprzesuniecie() = dron.getdron().getprzesuniecie() + wek_ruchu;

        
        double radian = (3.14 * dron.getdron().getkat()) / (180);
        cout << "###" << radian << endl;
        for (int i = 0; i < 200; i++)
        {
            dron.getdron().przesun(wek_ruchu / 200); //przesuwanie drona (inc/bryla.hh)

            dron.getwirnik1().przesun(wek_ruchu / 200);
            dron.getwirnik1().wyznaczenie_punktu_symetrii();
            dron.getwirnik1().obrotwir(radian);

            dron.getwirnik2().przesun(wek_ruchu / 200);
            dron.getwirnik2().wyznaczenie_punktu_symetrii();
            dron.getwirnik2().obrotwir(radian);

            dron.getdron().Importdopliku("bryly/dron1.dat"); //importowanie nowych danych do pliku
            dron.getwirnik1().Importdopliku("bryly/wirnikk1.dat");
            dron.getwirnik2().Importdopliku("bryly/wirnikk2.dat");
            rysuj();
            int czyblad = 0; //wyrysowanie nowej sceny
            czyblad = czykolizja();
            // czyblad = czy_nastapilo_zderzenie();
            if (czyblad > 0)
            {
                co_sie_stalo(czyblad);
                dron.getdron().napraw();
                dron.getwirnik1().napraw();
                dron.getwirnik2().napraw();
                break;
            }

            // funkcje z biblioteki "chrono" sluzace do opoznienia programu (plynnego przejscia drona)
            chrono::milliseconds timespan(10); //"100" 100 ms to 0,1sek.
            this_thread::sleep_for(timespan);
        }
    }*/

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

    void dodaj_przeszkode()
    {
        // przeszkoda[0].getlp() = liczba;
        float x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0, x = 0, y = 0, z = 0;
        cout << "wpisz dlugosc boku x ,y ,z" << endl;
        cin >> x >> y >> z;
        cout << " wpisz wspolrzedne miejsca rozpoczecia przeszkody " << endl;
        cin >> x1 >> y1 >> z1;
        x2 = x1 + x;
        y2 = y1 + y;
        z2 = z1 + z;

        Przeszkoda<rozmiar1> obiekt = Przeszkoda<rozmiar1>();
        obiekt.tworzprzeszkode(x1, x2, y1, y2, z1, z2);
        przeszkoda.push_back(obiekt);
        nazwa_przeszkody();

        Lacze.Rysuj();
    }
};

#endif
