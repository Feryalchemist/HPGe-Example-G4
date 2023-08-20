#include "Detector.hh"

SensitiveDetector::SensitiveDetector(G4String name, G4int noReplica)
  : G4VSensitiveDetector(name),
    fnoReplica(noReplica)
{
   collectionName.insert(name);
}

SensitiveDetector::~SensitiveDetector()
{}

void SensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{ 
  hitCollection = new DetectorHitsCollection(GetName(), collectionName[0]); 
  G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  HCE->AddHitsCollection(HCID, hitCollection);
  
  for (G4int i=0; i<fnoReplica; i++){
    hitCollection->insert(new DetectorHit());
  }
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{  
  // ==== Access Emission Track
  G4StepPoint *preStepPoint  = aStep->GetPreStepPoint();
  G4ThreeVector pos          = preStepPoint->GetPosition();
  
  G4int copyNo      = preStepPoint->GetTouchable()->GetCopyNumber();  
  G4double edep     = aStep->GetTotalEnergyDeposit();
  G4int eventID     = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4int trackID     = aStep->GetTrack()->GetTrackID();
  G4String Particle = aStep->GetTrack()->GetDefinition()->GetParticleName();
  
  // ==== Storing Hits
  auto hit = (*hitCollection)[copyNo-1];
  hit -> Collect(edep, pos, eventID, trackID, Particle, copyNo);
  return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitCollection)
{}
