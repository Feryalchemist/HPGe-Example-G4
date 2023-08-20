#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

#include "DetectorConstruction.hh"
#include "Run.hh"
#include "Randomize.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction*);
    ~EventAction();
    
  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);
};
#endif
