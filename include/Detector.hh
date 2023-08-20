#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "Hit.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
  public:
    SensitiveDetector(G4String, G4int);
    ~SensitiveDetector();
    
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);
    
  private:
    G4int fnoReplica;
    DetectorHitsCollection* hitCollection;
};
#endif

