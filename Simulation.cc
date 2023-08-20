#include <iostream>

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "Action.hh"
#include "ParticleGenerator.hh"

#include "G4RunManager.hh"
#include "G4ScoringManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{    
   string Line = "EventID,TrackID,fx,fy,fz,CopyNo,Particle,Edep,Volume";
   ofstream file("HistData.dat");
   file << Line << endl;

   G4RunManager *runManager = new G4RunManager();
   runManager->SetUserInitialization(new DetectorConstruction());
   runManager->SetUserInitialization(new PhysicsList());
   runManager->SetUserInitialization(new ActionInitialization());
   runManager->Initialize();
   
   G4UIExecutive* ui = 0;
   if ( argc == 1 ) 
   {
     ui = new G4UIExecutive(argc, argv);
   }
   
   G4VisManager *visManager = new G4VisExecutive();
   visManager->Initialize();
   
   G4ScoringManager* ScoringManager = G4ScoringManager::GetScoringManager();
   G4UImanager *UImanager           = G4UImanager::GetUIpointer();
   
   if ( ! ui ) 
   {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UImanager->ApplyCommand(command+fileName);
   }
   else 
   {
     ui->SessionStart();
   }
   return 0;
}
