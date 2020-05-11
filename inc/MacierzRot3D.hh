#ifndef MACIERZROT3D_HH
#define MACIERZROT3D_HH


#include <SMacierz.hh>



#define ROZM_MAC   3
class MacierzRot3D: public SMacierz<double,ROZM_MAC> {
  public:
   MacierzRot3D() = default;
   MacierzRot3D(const SMacierz<double,ROZM_MAC>& Mac):
                         SMacierz<double,ROZM_MAC>(Mac) {}
  
   /*void UstawRotX_st(double  Ang_deg);
   void UstawRotY_st(double  Ang_deg);
   void UstawRotZ_st(double  Ang_deg);*/
};



#endif
