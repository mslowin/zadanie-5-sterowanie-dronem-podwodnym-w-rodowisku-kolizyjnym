#ifndef MACIERZROT3D_HH
#define MACIERZROT3D_HH


#include <SMacierz.hh>



class MacierzRot3D: public SMacierz<double,3> {
public:
  MacierzRot3D() = default;
  MacierzRot3D(const SMacierz<double, 3> &Mac) : SMacierz<double, 3>(Mac) {}

  void UstawRotX_st(double Ang_deg);
  void UstawRotY_st(double Ang_deg);
  void UstawRotZ_st(double Ang_deg);
};



#endif
