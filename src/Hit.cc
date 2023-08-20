#include "Hit.hh"

DetectorHit::DetectorHit()
{
  fEdep  = 0;
  fPos   = G4ThreeVector();
  fevID  = 0;
  ftrID  = 0;
  fpart  = "None";
  fcopy  = 0;
}

DetectorHit::~DetectorHit()
{}
