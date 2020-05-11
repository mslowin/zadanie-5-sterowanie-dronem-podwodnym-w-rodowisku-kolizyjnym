#ifndef WEKTOR3D_HH
#define WEKTOR3D_HH


#include "SWektor.hh"


//typedef  SWektor<double,3>  Wektor3D;

class Wektor3D: public SWektor<double,3> {
  public:
   Wektor3D() = default;
   Wektor3D(double x, double y, double z)
              { (*this)[0] = x;  (*this)[1] = y;  (*this)[2] = z; }
   Wektor3D(const SWektor<double,3>& W):
                      SWektor<double,3>(W) {}
};


#endif
