#include "ParticleGenerator.hh"

PrimaryGenerator::PrimaryGenerator()
  : G4VUserPrimaryGeneratorAction(),
    fParticleGun(0)
{
  fParticleGun = new G4GeneralParticleSource();
}

PrimaryGenerator::~PrimaryGenerator()
{
  delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
    
