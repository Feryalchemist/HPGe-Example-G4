#include "Run.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4RunManager::GetRunManager()->SetPrintProgress(0);
  G4RunManager::GetRunManager()->SetVerboseLevel(0);
  G4AnalysisManager * manager = G4AnalysisManager::Instance();
  manager->OpenFile("Simulation.root");

  auto detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());  
  auto SDs = detectorConstruction->GetSDName();
    
  for (G4int j = 0; j < SDs.size(); j++)
  {  
     manager->CreateNtuple(SDs[j],SDs[j]);
     manager->CreateNtupleIColumn("TrackID");
     manager->CreateNtupleDColumn("fX");
     manager->CreateNtupleDColumn("fY");
     manager->CreateNtupleDColumn("fZ");
     manager->CreateNtupleDColumn("Edep");
     manager->CreateNtupleIColumn("CopyNo");
     manager->FinishNtuple();
   }
}

void RunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager * manager = G4AnalysisManager::Instance();
  manager->Write();
  manager->CloseFile();
}


