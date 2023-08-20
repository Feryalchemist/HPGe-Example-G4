#include "PhysicsList.hh"

PhysicsList::PhysicsList()
{
  RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP());
  RegisterPhysics(new G4EmStandardPhysics_option4());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  //RegisterPhysics(new G4EmQExtraPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4OpticalPhysics());
}

PhysicsList::~PhysicsList()
{}
