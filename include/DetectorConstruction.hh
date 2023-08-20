#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Ellipsoid.hh"
#include "G4EllipticalTube.hh"
#include "G4VSolid.hh"
#include "G4MultiUnion.hh"

#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include "Detector.hh"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
     DetectorConstruction();
     ~DetectorConstruction();
     virtual G4VPhysicalVolume *Construct();
     
    vector<G4String> GetSDName() const {return SDName;}; 

  private:
    vector<G4int>            noReplica;
    vector<G4String>         SDName;
    vector<G4LogicalVolume*> LogicDetector;
    virtual void ConstructSDandField();
};
#endif
