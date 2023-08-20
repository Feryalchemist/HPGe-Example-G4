#include "Event.hh"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

EventAction::EventAction(RunAction*)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{}

void EventAction::EndOfEventAction(const G4Event* event)
{ 
  auto detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  auto manager = G4AnalysisManager::Instance();
  auto SDs     = detectorConstruction->GetSDName();
  
  string Line = "";
  for (G4int j = 0; j < SDs.size(); j++)
  {
     G4String HCName = SDs[j];
     G4int    HCID   = G4SDManager::GetSDMpointer()->GetCollectionID(HCName);
     auto     HC     = static_cast<const DetectorHitsCollection*>(event->GetHCofThisEvent()->GetHC(HCID));
     for (G4int i=0; i < HC->entries(); i++)
     {
        G4double SDEdep = (*HC)[i]->GetEdep();
        G4double ref    = 0;
        if (SDEdep > ref)
          { 
            //G4double E1    = 0.122;
            //G4double E2    = 1.332;
            //G4double F1    = 0.85e-3;
            //G4double F2    = 1.85e-3;
            //G4double FWHM  = (F2-F1)/(E2-E1)*(SDEdep-E1) + F1;
            //G4double FWHM  = 1.85e-3;
            //G4double FWHM  = 7.36242e-7*SDEdep + 1.25768e-3;
            //G4double FWHM  = 2.81187e-7*SDEdep + 1.40257e-3;
            //G4double FWHM  = 3.63439e-7*SDEdep + 1.63495e-3;
            //G4double FWHM  = 5.66828e-7*SDEdep + 1.51352e-3;
            //G4double FWHM  = (exp(4.08348e-4*SDEdep*1.0e3 + 2.04927e-1))*1e-3;
            //G4double FWHM  = 6.66899e-7*SDEdep + 1.40768e-3;
            
            G4double FWHM  = 6.07827e-7*SDEdep + 1.28546e-3;
            G4double sigma = FWHM/(2*sqrt(2*log(2)));
            G4String det   = "Scintillator";
            if (HCName == det){
              SDEdep = G4RandGauss::shoot(SDEdep,sigma);
            };
            Line += to_string((*HC)[i]->GetEventID())+",";
            Line += to_string((*HC)[i]->GetTrackID())+",";
            Line += to_string((*HC)[i]->GetPos()[0])+",";
            Line += to_string((*HC)[i]->GetPos()[1])+",";
            Line += to_string((*HC)[i]->GetPos()[2])+",";
            Line += to_string((*HC)[i]->GetCopyNo())+",";
            Line += (*HC)[i]->GetParticle()+",";
            Line += to_string(SDEdep)+",";
            Line += HCName+"\n";
      
            manager->FillNtupleIColumn(j,0,(*HC)[i]->GetTrackID());
            manager->FillNtupleDColumn(j,1,(*HC)[i]->GetPos()[0]);
            manager->FillNtupleDColumn(j,2,(*HC)[i]->GetPos()[1]);
            manager->FillNtupleDColumn(j,3,(*HC)[i]->GetPos()[2]);
            manager->FillNtupleDColumn(j,4,SDEdep);
            manager->FillNtupleIColumn(j,5,(*HC)[i]->GetCopyNo());
            manager->AddNtupleRow(j);
          }}}
          
  ofstream foutput;
  ifstream finput;
  finput.open("HistData.dat");
  foutput.open("HistData.dat",ios::app);
  if(finput.is_open())
    foutput<<Line;
  finput.close();
  foutput.close();
}

