#ifndef SWEKTOR_HH
#define SWEKTOR_HH

#include <iostream>
#include <math.h>

/*!
 *  Klasa modelująca wektor
 *  Tab[ROZMIAR] - tablica będąca wektorem o rozmiarze 1 x ROZMIAR
 */
template <typename STyp, int SWymiar>
class SWektor {
    STyp _Tab[SWymiar];

public:
    SWektor() { for (STyp &Tab: _Tab) Tab = 0; }
    STyp  operator[] (unsigned int l) const {return _Tab[l];};
    STyp &operator[] (unsigned int l)       {return _Tab[l];};
    SWektor<STyp,SWymiar> operator +(const SWektor<STyp,SWymiar> &W2)const    /*Przeciążenie dodawania dwóch wektorów*/
    {
        SWektor<STyp, SWymiar> Wynik;
        for (unsigned int i = 0; i < SWymiar; ++i)
        {
            Wynik[i] = (*this)[i] + W2[i];
        }
        return Wynik;
    }
    SWektor<STyp,SWymiar> operator -(const SWektor<STyp,SWymiar> &W2)const    /*Przeciążenie odejmowania dwóch wektorów*/
    {
        SWektor<STyp, SWymiar> Wynik;

        for (unsigned int Ind = 0; Ind < SWymiar; ++Ind)
        {
            Wynik[Ind] = (*this)[Ind] - W2[Ind];
        }
        return Wynik;
    }
    SWektor<STyp,SWymiar> operator *(STyp Mnoznik) const   /*Przeciążenie mnożenia wektor x liczba*/
    {
        SWektor<STyp, SWymiar> Wynik;

        for (unsigned int Ind = 0; Ind < SWymiar; ++Ind)
        {
            Wynik[Ind] = (*this)[Ind] * Mnoznik;
        }
        return Wynik;
    }
    SWektor<STyp,SWymiar> operator /(STyp liczba) const   /*Przeciążenie dzielenia wektor / liczba*/
    {
        SWektor<STyp, SWymiar> Wynik;
        if (liczba == 0)
        {
            std::cout << "DZIELENIE PRZEZ ZERO" << std::endl;
            exit(0);
        }
        for (unsigned int i = 0; i < SWymiar; ++i)
        {
            Wynik[i] = (*this)[i] / liczba;
        }
        return Wynik;
    }
};

template <typename STyp, int SWymiar>
STyp operator *(SWektor<STyp,SWymiar> W1, SWektor<STyp,SWymiar> W2)    /*Przeciążenie mnożenia dwóch wektorów (iloczyn skalarny)*/
{
    STyp wynik, j;
    wynik = 0; 
    j = 0;
    for (int i = 0; i < SWymiar; ++i)
    {
        j = W1[i] * W2[i];
        wynik = wynik + j;
    }
     return wynik;
}

/*!
 * Przeciążenie ściśle związane z klasą Wektor
 * Służy do wczytywania liczb do wektora
 */
template <typename STyp, int SWymiar>
std::istream& operator >> (std::istream &in, SWektor<STyp,SWymiar> &Wek)
{
    for(unsigned int i=0; i < SWymiar; ++i)
    {
        std::cout << "Podaj " << i+1 << ". liczbę wektora" << std::endl;
        in >> Wek[i];
    }
    return in;
}

/*!
 * Przeciążenie ściśle związane z klasą Wektor
 * Służy do wyświetlania wektora
 */
template <typename STyp, int SWymiar>
std::ostream& operator << (std::ostream &out, const SWektor<STyp,SWymiar> &Wek)
{
    for (unsigned int Ind = 0; Ind < SWymiar; ++Ind) {
        out << Wek[Ind] << "   ";
    }
    return out;
}


#endif
