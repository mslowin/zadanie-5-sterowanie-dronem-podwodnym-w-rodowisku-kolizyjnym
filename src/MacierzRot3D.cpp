#include <cmath>
#include <math.h>
#include "MacierzRot3D.hh"


inline
double Deg2Rad(double Ang_deg)
{
  return Ang_deg*M_PI/180;
}

/**
 * @brief Ustawia rotację obiektu wokół osi Z
 * 
 * @param Ang_deg kąt w stopniach 
 */
void MacierzRot3D::UstawRotZ_st(double  Ang_deg)
{
  double Ang_rad = Deg2Rad(Ang_deg);
  double sn = sin(Ang_rad), cs = cos(Ang_rad);

  (*this)(0,0) = cs;  (*this)(0,1) = -sn;  (*this)(0,2) = 0;
  (*this)(1,0) = sn;   (*this)(1,1) = cs;  (*this)(1,2) = 0;  
  (*this)(2,0) = 0;  (*this)(2,1) = 0;  (*this)(2,2) = 1;
}

/**
 * @brief Ustawia rotację obiektu wokół osi X
 * 
 * @param Ang_deg kąt w stopniach 
 */
void MacierzRot3D::UstawRotX_st(double  Ang_deg)
{
  double Ang_rad = Deg2Rad(Ang_deg);
  double sn = sin(Ang_rad), cs = cos(Ang_rad);

  (*this)(0,0) = 1; (*this)(0,1) = 0;  (*this)(0,2) = 0;
  (*this)(1,0) = 0; (*this)(1,1) = cs;  (*this)(1,2) = -sn;  
  (*this)(2,0) = 0; (*this)(2,1) = sn;  (*this)(2,2) = cs;
}


/**
 * @brief Ustawia rotację obiektu wokół osi Y
 * 
 * @param Ang_deg kąt w stopniach 
 */
void MacierzRot3D::UstawRotY_st(double  Ang_deg)
{
  double Ang_rad = Deg2Rad(Ang_deg);
  double sn = sin(Ang_rad), cs = cos(Ang_rad);

  (*this)(0,0) = cs;  (*this)(0,1) = 0;  (*this)(0,2) = sn;
  (*this)(1,0) = 0;   (*this)(1,1) = 1;  (*this)(1,2) = 0;  
  (*this)(2,0) = -sn; (*this)(2,1) = 0;  (*this)(2,2) = cs;
}
