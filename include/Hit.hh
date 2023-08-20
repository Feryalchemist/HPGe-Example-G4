#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"

class DetectorHit : public G4VHit
{
  public:
    DetectorHit();
    ~DetectorHit();
  void Collect(G4double edep, G4ThreeVector pos, G4int eventID, G4int trackID, G4String Particle, G4int copyNo) 
  {
    G4String ref="None";
    fEdep += edep;
    fPos   = pos;
    fevID  = eventID;
    ftrID  = trackID;
    if (fpart == ref){
       fpart  = Particle;}
    fcopy  = copyNo;
  };
  
  G4ThreeVector GetPos() const{return fPos;};
  G4double GetEdep()     const{return fEdep;};
  G4int GetCopyNo()      const{return fcopy;};
  G4int GetEventID()     const{return fevID;};
  G4int GetTrackID()     const{return ftrID;};
  G4String GetParticle() const{return fpart;};
  
  private:
     G4int         fevID, ftrID, fcopy;
     G4double      fEdep;
     G4String      fpart;
     G4ThreeVector fPos;
};

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;

#endif
