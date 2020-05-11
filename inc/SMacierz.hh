#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "SWektor.hh"

#include <iostream>
#include <math.h>

/*!
 *  Klasa modelująca Macierz
 *  _Tab[3][3] - tablica będąca macierzą o 3ach 3 x 3
 */
 /*template <class STyp>
class SMacierz {
    SWektor<STyp> macierz[3];*/
template <typename STyp, int SWymiar>
class SMacierz {
    SWektor<STyp,SWymiar> _Tab[3];
  public:
    int size = SWymiar;
    SWektor<STyp,SWymiar>  operator[](unsigned int Ind) const {return _Tab[Ind];};
    SWektor<STyp,SWymiar> &operator[](unsigned int Ind)       {return _Tab[Ind];};
    STyp  operator ()(unsigned int Wiersz, unsigned int Kolumna) const {return _Tab[Wiersz][Kolumna];}
    STyp& operator ()(unsigned int Wiersz, unsigned int Kolumna)       { return _Tab[Wiersz][Kolumna]; }
    /*!
    *  metoda wypełniająca macierz zerami
    */
    SMacierz()
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                _Tab[i][j] = 0;
            }
        }
    }

    SMacierz<STyp,SWymiar> operator*(double liczba) const
    {
        SMacierz<STyp, SWymiar> wynik;
        for (unsigned int i = 0; i < SWymiar; ++i)
        {
            for (unsigned int j = 0; j < SWymiar; ++j)
            {
                wynik[i][j] = (*this)[i][j] * liczba;
            }
        }
        return wynik;
    }

    SMacierz<STyp,SWymiar> operator-(const SMacierz<STyp,SWymiar> &M) const
    {
        SMacierz<STyp, SWymiar> Wynik;

        for (unsigned int Ind = 0; Ind < SWymiar; ++Ind)
        {
            for (unsigned int I = 0; I < SWymiar; ++I)
            {
                Wynik[Ind][I] = (*this)[Ind][I] - M[Ind][I];
            }
        }
        return Wynik;
    }
/*!
 * Funkcja kopiująca wyrazy z macierzy do nowej macierzy
 *  macierzpocz - macierz początkowa
 */
    void copy(SMacierz<STyp,SWymiar> from)
    {
        for (int i = 0; i < SWymiar; ++i)
        {
            for (int j = 0; j < SWymiar; ++j)
            {
                _Tab[i][j] = from[i][j];
            }
        }
    }
};
/*!
 * Metoda wyliczająca wyznacznik macierzy
 */
template <typename STyp, int SWymiar>
STyp wyznacznik(SMacierz<STyp, SWymiar> &macierz)
{
    SWektor<STyp, SWymiar> ab = SWektor<STyp, SWymiar>();
    int i = 0, j = 0, k = 0, n = 0;
    for (k = 0; k < 3; ++k)
    {
        for (i = 1 + k; i < 3; ++i)
        {
            for (j = 3 - 1; j >= 0 + k; --j)
            {
                while (macierz[k][k] == 0 && n <= 3 - k)
                {
                    ab = macierz[k + n];
                    macierz[k + n] = macierz[k];
                    macierz[k] = ab;
                    n++;
                }
                macierz[i][j] = macierz[i][j] - (macierz[i][k] * macierz[k][j]) / macierz[k][k];

                if (fabs(macierz[i][j]) < 0.0000001)
                    macierz[i][j] = 0;
                if (fabs(macierz[i][j]) > 100000)
                    macierz[i][j] = 100000;
            }
        }
    }
    STyp a;
    a = 1;
    for (int i = 0; i < 3; i++)
    {
        a = a * macierz[i][i];
    }
    return a;
}
/*!
 * Funkcja do mnożenia macierzy przez wektor
 * wynik     - wynik mnożenia
 * macierz1  - macierz
 * wektor1   - wektor
 */
template <typename STyp, int SWymiar>
SWektor<STyp,SWymiar> operator*(SMacierz<STyp,SWymiar> macierz1, SWektor<STyp,SWymiar> wektor1)
{
    SWektor<STyp,SWymiar> wynik;
    for (unsigned int i = 0; i < SWymiar; ++i)
    {
            wynik[i] = macierz1[i] * wektor1;
    }
    return wynik;
}
/*!
 * Funkcja do mnożenia dwóch macierzy
 * wynik   - wynik mnożenia
 * ma1     - macierz pierwsza
 * ma2     - macierz druga
 */
template <typename STyp, int SWymiar>
SMacierz<STyp,SWymiar> operator*(SMacierz<STyp,SWymiar> m1, SMacierz<STyp,SWymiar> m2)
{
    SMacierz<STyp,SWymiar> wynik;
    for(unsigned int i = 0; i < SWymiar; ++i)
        for(unsigned int j = 0; j < SWymiar; ++j)
        {
            wynik[i][j]=0;
        }
    for (unsigned int i = 0; i < SWymiar; ++i)
    {
        for(unsigned int j = 0; j < SWymiar; ++j) {
            for (unsigned int k = 0; k < SWymiar; ++k)
            {
                wynik[i][j] += (m1[i][k] * m2[k][j]);
            }
        }
    }
    return wynik;
}


/*!
 * Funkcja zmiany kolejnosci wierszy w macierzy, w celu wyliczenia wyznaczników pomocniczych
 * macierz1 -   macierz ktorej zmieniamy kolumny
 * int i    -   zmienna pomocnicza do okreslenia zmienianej kolumny
 * wektor1  -   wektor wyrazow wolnych (nowa kolumna)
*/
template <typename STyp, int SWymiar>
SMacierz<STyp,SWymiar> zmianakolejnosci(SMacierz<STyp,SWymiar> macierz1, SWektor<STyp,SWymiar> wektor1, int i)
{
    for (unsigned int j = 0; j < SWymiar; j++)
    {
        macierz1[i][j] = wektor1[j];
    }
    return macierz1;
}

//transponowanie macierzy
template <typename STyp, int SWymiar>
SMacierz<STyp,SWymiar> transponowanie(SMacierz<STyp,SWymiar> macierz1)
{
    STyp t;
    for(unsigned int i = 0; i < SWymiar - 1; ++i)
        for(unsigned int j = i + 1; j < SWymiar; ++j)
        {
            t = macierz1[i][j];
            macierz1[i][j] = macierz1[j][i];
            macierz1[j][i] = t;
        }
    return macierz1;
}

/*!
 * Przeciążenie ściśle związane z klasą Macierz
 * Służy do wyświetlania macierzy
 */
template <typename STyp, int SWymiar>
std::ostream& operator << (std::ostream &out, const SMacierz<STyp,SWymiar> &Mac)
{
    for (unsigned int i = 0; i < SWymiar; ++i) {
        for (int j = 0; j < SWymiar; ++j) {
            out << Mac[i][j] << "   ";
        }
        out << std::endl;
    }
    return out;
}

/*!
 * Przeciążenie ściśle związane z klasą Macierz
 * Służy do wczytywania liczb do macierzy
 */
template <typename STyp, int SWymiar>
std::istream& operator >> (std::istream &in, SMacierz<STyp,SWymiar> &Mac)
{
    int l=1;
    for(unsigned int i=0; i < SWymiar; ++i)
    {
        for(unsigned int j=0; j < SWymiar; ++j)
        {
            in >> Mac[i][j];
        }
        l++;
    }
    return in;
}

#endif
