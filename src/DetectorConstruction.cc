#include "DetectorConstruction.hh"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // Material definition 
  G4NistManager *nistManager = G4NistManager::Instance(); 
  
  G4double a, z, abundance;
  G4double density, fractionmass;
  G4int ncomp;
    
  // Air defined using NIST Manager
  G4Material* air  = nistManager->FindOrBuildMaterial("G4_AIR");
  
  // Polyethylene defined using NIST Manager
  G4Material* Lucite = nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");
  
  // Copper defined using NIST Manager
  G4Material* Cu   = nistManager->FindOrBuildMaterial("G4_Cu");

  // Lead defined using NIST Manager
  G4Material* Pb   = nistManager->FindOrBuildMaterial("G4_Pb");

  // Aluminum defined using NIST Manager
  G4Material* Al   = nistManager->FindOrBuildMaterial("G4_Al");
  
  // Berylium defined using NIST Manager
  G4Material* Be   = nistManager->FindOrBuildMaterial("G4_Be");
  
  // Magnesium defined using NIST Manager
  G4Material* Mg   = nistManager->FindOrBuildMaterial("G4_Be"); //G4_MAGNESIUM_OXIDE
  
  // Sodium Iodide defined using NIST Manager
  G4Material* Detector = nistManager->FindOrBuildMaterial("G4_Ge");
  
  // Polypropylene defined using NIST Manager
  G4Material* PP = nistManager->FindOrBuildMaterial("G4_POLYPROPYLENE");
  
  // Neoprene Rubber defined using NIST Manager
  G4Material* ORing_Rubber = nistManager->FindOrBuildMaterial("G4_RUBBER_NEOPRENE");
  
  // Mylar defined using NIST Manager
  G4Material* Mylar = nistManager->FindOrBuildMaterial("G4_MYLAR");
  
  // ICRU Soft Tissue Equivalent Material defined using NIST Manager
  G4Material* ICRU_Tissue = nistManager->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRU-4");
  
  // Default Material
  G4Material* defaultMaterial  = nistManager->FindOrBuildMaterial("G4_Galactic");

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // Volume Definition
  G4double worldLength  = 400;  
  G4RotationMatrix rotm = G4RotationMatrix();
  
  // ==== World
  G4Box* worldS
    = new G4Box("worldS",worldLength/2*cm,worldLength/2*cm,worldLength/2*cm);
  G4LogicalVolume* worldLV  
    = new G4LogicalVolume(worldS,air,"World");
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,
                        G4ThreeVector(),
                        worldLV,"World",
                        0, false, 1, true);
  
  // ======================================================================================================
  //                                        DETECTOR CONSTRUCTION
  // ======================================================================================================
  G4double Cap_T = 1.51;
  G4double Cap_D = 70;
  G4double Cap_L = 134;
  G4double Window_T  = 0.5;
  G4double Crystal_L = 64.0;
  G4double Crystal_D = 56.6;
  G4double Top_Gap   = 3;
  G4double Bottom_Gap= 20;
  G4double Mylar_T   = 0.05;
  G4double Holder_T  = 1.8;
  G4double Holder_B  = 3.2;
  G4double Chamfer_R = 4;
  G4double Hole_D    = 8;
  G4double Hole_L    = -4.5 -Hole_D/2 + Crystal_L + Holder_B + Bottom_Gap;
  G4double Detector_O= 0;
  G4double DeadLyr_S = 0.7;
  G4double DeadLyr_T = 1.3;
  G4double DeadLyr_I = 1.0;
      
  // ==== Detector Aluminum Outer Cap
  G4Tubs* Outer_CapS
    = new G4Tubs("Outer_Cap", 0*cm, (Cap_D/2)*mm ,
                                    (Cap_L/2)*mm,0.*deg,360.*deg);
  G4LogicalVolume* Outer_CapLV  
    = new G4LogicalVolume(Outer_CapS,Al,"Outer_Cap");
  G4VPhysicalVolume* Outer_CapPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0,-Outer_CapS->GetZHalfLength()+Detector_O),
                        Outer_CapLV,"Outer_Cap",
                        worldLV, false, 0, true);
                        
  // ==== Detector Berylium Window Cap
  G4Tubs* Window_CapS
    = new G4Tubs("Window_Cap", 0*cm, (Crystal_D/2)*mm,
                                     (Window_T/2 )*mm,0.*deg,360.*deg);
  G4LogicalVolume* Window_CapLV  
    = new G4LogicalVolume(Window_CapS,Be,"Window_Cap");
  G4VPhysicalVolume* Window_CapPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0,(Outer_CapS->GetZHalfLength() - 
                                           Window_CapS->GetZHalfLength())),
                        Window_CapLV,"Window_Cap",
                        Outer_CapLV, false, 0, true);
  
  // ==== Detector Vacuum Window Cap Gap
  G4Tubs* Window_Cap_GapS
    = new G4Tubs("Window_Cap_Gap", 0*cm, (Crystal_D/2)*mm,
                                         (Cap_T - Window_T)/2*mm,0.*deg,360.*deg);
  G4LogicalVolume* Window_Cap_GapLV  
    = new G4LogicalVolume(Window_Cap_GapS,defaultMaterial,"Window_Cap_Gap");
  G4VPhysicalVolume* Window_Cap_GapPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0,(Outer_CapS->GetZHalfLength() - 
                                           2*Window_CapS->GetZHalfLength()-
                                           Window_Cap_GapS->GetZHalfLength())),
                        Window_Cap_GapLV,"Window_Cap_Gap",
                        Outer_CapLV, false, 0, true);

  // ==== Detector Vacuum Gap
  G4Tubs* Vaccum_GapS
    = new G4Tubs("Vaccum_Gap", 0*cm, ((Cap_D/2 - Cap_T))*mm, 
                                     ((Cap_L - Cap_T)/2)*mm,0.*deg,360.*deg);
  G4LogicalVolume* Vaccum_GapLV  
    = new G4LogicalVolume(Vaccum_GapS,defaultMaterial,"Vaccum_Gap");
  G4VPhysicalVolume* Vaccum_GapPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0,-Cap_T/2*mm),
                        Vaccum_GapLV,"Vaccum_Gap",
                        Outer_CapLV, false, 0, true); 
               
  // ==== Detector Aluminum Insulator
  G4Tubs* InsulatorS
    = new G4Tubs("Insulator", 0*cm, (Crystal_D/2+Holder_T)*mm, 
                                    (Mylar_T/2)*mm,0.*deg,360.*deg);
  G4LogicalVolume* InsulatorLV  
    = new G4LogicalVolume(InsulatorS,Mylar,"Insulator");
  G4VPhysicalVolume* InsulatorPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0, (Vaccum_GapS->GetZHalfLength() - Mylar_T - Top_Gap)),
                        InsulatorLV,"Insulator",
                        Vaccum_GapLV, false, 0, true);                   

  // ==== Detector Center Hole
  G4Tubs* CenterHole_TubeS
    = new G4Tubs("CenterHole_Tube", 0*cm, Hole_D/2*mm, (Hole_L-Hole_D/2)/2*mm,0.*deg,360.*deg);
  G4Ellipsoid* CenterHole_BallS
    = new G4Ellipsoid("CenterHole_Ball", Hole_D/2*mm, Hole_D/2*mm, Hole_D/2*mm);
  G4VSolid* CenterHoleS
    = new G4UnionSolid("CenterHole", CenterHole_TubeS, CenterHole_BallS, 0, 
                       G4ThreeVector(0*mm,0*mm, (CenterHole_TubeS->GetZHalfLength())));
  //***
  G4Tubs* CenterHole_Tube_InS
    = new G4Tubs("CenterHole_Tube", 0*cm, Hole_D/2*0.5*mm, (Hole_L-Hole_D/2)/2*mm,0.*deg,360.*deg);
  G4Ellipsoid* CenterHole_Ball_InS
    = new G4Ellipsoid("CenterHole_Ball", Hole_D/2*0.5*mm, Hole_D/2*0.5*mm, Hole_D/2*0.5*mm);
  G4VSolid* CenterHole_InS
    = new G4UnionSolid("CenterHole", CenterHole_Tube_InS, CenterHole_Ball_InS, 0, 
                       G4ThreeVector(0*mm,0*mm, (CenterHole_Tube_InS->GetZHalfLength())));
  //***
  G4Tubs* CenterHole_Tube_offS
    = new G4Tubs("CenterHole_Tube_off", 0*cm, (Hole_D+DeadLyr_I)/2*mm, 
                                              (Hole_L-Hole_D/2+DeadLyr_I)/2*mm,0.*deg,360.*deg);
  G4Ellipsoid* CenterHole_Ball_offS
    = new G4Ellipsoid("CenterHole_Ball_off", (Hole_D+DeadLyr_I)/2*mm, 
                                             (Hole_D+DeadLyr_I)/2*mm, (Hole_D+DeadLyr_I)/2*mm);
  G4VSolid* CenterHole_offS
    = new G4UnionSolid("CenterHole_off", CenterHole_Tube_offS, CenterHole_Ball_offS, 0, 
                       G4ThreeVector(0*mm,0*mm, (CenterHole_Tube_offS->GetZHalfLength())));                   
 
  // ==== Crystal Copper Holder
  G4Tubs* CrystalHolder_TubeS
    = new G4Tubs("CrystalHolder_Tube", 0*cm, (Crystal_D/2+Holder_T)*mm, 
                                        (Crystal_L+Holder_B+Bottom_Gap)/2*mm,0.*deg,360.*deg);
  G4VSolid* CrystalHolderS
    = new G4SubtractionSolid("CrystalHolder", CrystalHolder_TubeS, CenterHoleS, 0, 
                             G4ThreeVector(0*mm,0*mm, (-CrystalHolder_TubeS->GetZHalfLength() +
                                                        CenterHole_TubeS->GetZHalfLength())));
  G4LogicalVolume* CrystalHolderLV  
    = new G4LogicalVolume(CrystalHolderS,Cu,"CrystalHolder");
  G4VPhysicalVolume* CrystalHolderPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0, (Vaccum_GapS->GetZHalfLength() - 
                                            CrystalHolder_TubeS->GetZHalfLength() - 
                                            1.5*Mylar_T - Top_Gap)),
                        CrystalHolderLV,"CrystalHolder",
                        Vaccum_GapLV, false, 0, true); 
                        
  // ==== Copper Center Hole
  /*
  G4LogicalVolume* CenterHoleLV  
    = new G4LogicalVolume(CenterHole_InS,Cu,"CenterHole");
  G4VPhysicalVolume* CenterHolePV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0, (Vaccum_GapS->GetZHalfLength() - CenterHole_TubeS->GetZHalfLength() - Top_Gap - Mylar_T + 
                                            (Hole_L - Crystal_L - Holder_B - Bottom_Gap) - Hole_D/2)),
                        CenterHoleLV,"CenterHole",
                        Vaccum_GapLV, false, 0, true);                  
  */
  // ==== Detector Vacuum Housing
  G4Tubs* Housing_TubeS
    = new G4Tubs("Housing_Tube", 0*cm, (Crystal_D/2)*mm, 
                                        CrystalHolder_TubeS->GetZHalfLength()-(Holder_B/2)*mm,0.*deg,360.*deg);
  G4VSolid* HousingS
    = new G4SubtractionSolid("Housing", Housing_TubeS, CenterHoleS, 0, 
                             G4ThreeVector(0*mm,0*mm, (-Housing_TubeS->GetZHalfLength() +
                                                        CenterHole_TubeS->GetZHalfLength() - Holder_B)));  
  G4LogicalVolume* HousingLV  
    = new G4LogicalVolume(HousingS,defaultMaterial,"Housing");
  G4VPhysicalVolume* HousingPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0, (CrystalHolder_TubeS->GetZHalfLength()-
                                            Housing_TubeS->GetZHalfLength())*mm),
                        HousingLV,"Housing",
                        CrystalHolderLV, false, 0, true);
  
  // ==== Detector Dead Layer 
  G4Tubs* Detector_BodyS
    = new G4Tubs("Detector_Body", 0*cm, (Crystal_D/2)*mm, 
                                        (Crystal_L-Chamfer_R)/2*mm,0.*deg,360.*deg);
  G4Tubs* Detector_TopS
    = new G4Tubs("Detector_Top", 0*cm, (Crystal_D/2 - Chamfer_R)*mm, 
                                       (Chamfer_R)*mm,0.*deg,360.*deg);
  G4Torus* Detector_ChamferS
    = new G4Torus("Detector_Chamfer", 0*cm, Chamfer_R*mm, (Crystal_D/2 - Chamfer_R)*mm,0.*deg,360.*deg); 
  G4MultiUnion* Detector_UnchamferS
    = new G4MultiUnion("Detector_Unchamfer");
  G4ThreeVector pos_D1 = G4ThreeVector();
  G4Transform3D tr_D1  = G4Transform3D(rotm,pos_D1);
  Detector_UnchamferS->AddNode(*Detector_TopS,    tr_D1);
  Detector_UnchamferS->AddNode(*Detector_ChamferS,tr_D1);
  Detector_UnchamferS->Voxelize();
  
  G4UnionSolid* Dead_Layer_UnionS
    = new G4UnionSolid("Dead_Layer_Union", Detector_BodyS, Detector_UnchamferS, 0, 
                       G4ThreeVector(0*mm,0*mm, (Detector_BodyS->GetZHalfLength())));
  G4VSolid* Dead_LayerS
    = new G4SubtractionSolid("Dead_Layer", Dead_Layer_UnionS, CenterHoleS, 0, 
                             G4ThreeVector(0*mm,0*mm, (-Detector_BodyS->GetZHalfLength() +
                                                        CenterHole_TubeS->GetZHalfLength()-Bottom_Gap-Holder_B)));
  G4LogicalVolume* Dead_LayerLV  
    = new G4LogicalVolume(Dead_LayerS,Detector,"Dead_Layer");
  G4VPhysicalVolume* Dead_LayerPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0, (Housing_TubeS->GetZHalfLength()-
                                            Detector_BodyS->GetZHalfLength()-
                                            Detector_TopS->GetZHalfLength())*mm),
                        Dead_LayerLV,"Dead_Layer",
                        HousingLV, false, 0, true);
  // ==== Detector Active Layer
  G4Tubs* Active_BodyS
    = new G4Tubs("Active_Body", 0*cm, (Crystal_D/2-DeadLyr_S-DeadLyr_T)*mm, 
                                      (Crystal_L-Chamfer_R-DeadLyr_T)/2*mm,0.*deg,360.*deg);
  G4Tubs* Active_TopS
    = new G4Tubs("Active_Top", 0*cm, (Crystal_D/2-Chamfer_R-DeadLyr_S)*mm, 
                                     (Chamfer_R-DeadLyr_T)*mm,0.*deg,360.*deg);
  G4Torus* Active_ChamferS
    = new G4Torus("Detector_Chamfer", 0*cm, (Chamfer_R-DeadLyr_T)*mm, 
                                            (Crystal_D/2-Chamfer_R-DeadLyr_S)*mm,0.*deg,360.*deg);
  G4MultiUnion* Active_UnchamferS
    = new G4MultiUnion("Active_Unchamfer");
  G4ThreeVector pos_DI1 = G4ThreeVector();
  G4Transform3D tr_DI1  = G4Transform3D(rotm,pos_DI1);
  Active_UnchamferS->AddNode(*Active_TopS,    tr_DI1);
  Active_UnchamferS->AddNode(*Active_ChamferS,tr_DI1);
  Active_UnchamferS->Voxelize();
  
  G4UnionSolid* Scintillator_UnionS
    = new G4UnionSolid("Scintillator_Union", Active_BodyS, Active_UnchamferS, 0, 
                       G4ThreeVector(0*mm,0*mm, (Active_BodyS->GetZHalfLength())));
  G4VSolid* ScintillatorS
    = new G4SubtractionSolid("Scintillator", Scintillator_UnionS, CenterHole_offS, 0, 
                             G4ThreeVector(0*mm,0*mm, (-Active_BodyS->GetZHalfLength() +
                                                        CenterHole_Tube_offS->GetZHalfLength()-
                                                        Bottom_Gap-Holder_B-DeadLyr_I)));
  G4LogicalVolume* ScintillatorLV  
    = new G4LogicalVolume(ScintillatorS,Detector,"Scintillator");
  G4VPhysicalVolume* ScintillatorPV
    = new G4PVPlacement(0,
                        G4ThreeVector(0,0, -DeadLyr_T/2*mm),
                        ScintillatorLV,"Scintillator",
                        Dead_LayerLV, false, 1, true);
  
  // ======================================================================================================
  //                                        SHIELDING CONSTRUCTION
  // ======================================================================================================
  
  G4double Lead_Opening_lo = 10.5;
  G4double Lead_Opening_hi = 23;
  G4double Lead_Opening_l  = 9.6;
  G4double Sample_space_h  = 16.5;
  G4double Lead_Tank_w     = 55.5;
  G4double Lead_Tank_h     = 92;
  G4double Sample_space_u  = 15.5;
  G4double Lead_Head_h     = 13;
  G4double Secondary_Lead_t= 0.3;
  G4double Secondary_Lead_i= 0.1;
  
  G4double Lead_Head_u     = 
  (Lead_Tank_h-Sample_space_h-Lead_Opening_l-Lead_Head_h-Sample_space_u);
  
  // ==== Lead Tank
  G4Tubs* LeadTankWallS
    = new G4Tubs("LeadTankWall", 0*cm, Lead_Tank_w/2*cm, Lead_Tank_h/2*cm,0.*deg,360.*deg);
  G4Cons* LeadTankOpeningS
    = new G4Cons("LeadTankOpening", 0,(Lead_Tank_w/2 - Lead_Opening_lo)*cm, 
                                    0,(Lead_Tank_w/2 - Lead_Opening_hi)*cm, 
                                    (Lead_Opening_l/2)*cm,0.*deg,360.*deg);
  G4Tubs* LeadTankSpaceS
    = new G4Tubs("LeadTankSpace", 0*cm, (Lead_Tank_w/2 - Lead_Opening_hi)*cm, 
                                        (Lead_Opening_l+Sample_space_h+Sample_space_u)/2*cm,
                                        0.*deg,360.*deg);
  G4VSolid* LowerLeadTankS
    = new G4SubtractionSolid("LowerLeadTank", LeadTankWallS, LeadTankOpeningS, 0, 
                             G4ThreeVector(0*cm,0*cm,(LeadTankOpeningS->GetZHalfLength() - 
                                                      LeadTankWallS->GetZHalfLength())));
  G4VSolid* LeadTankS
    = new G4SubtractionSolid("LeadTank", LowerLeadTankS, LeadTankSpaceS, 0, 
                             G4ThreeVector(0*cm,0*cm,(LeadTankSpaceS->GetZHalfLength() - 
                                                      LeadTankWallS->GetZHalfLength())));
  G4LogicalVolume* LeadTankLV
    = new G4LogicalVolume(LeadTankS, Pb, "LeadTank");
  G4VPhysicalVolume* LeadTankPV  
    = new G4PVPlacement(0, G4ThreeVector(0, 0, LeadTankWallS->GetZHalfLength() - 
                                               LeadTankOpeningS->GetZHalfLength()*2),
                        LeadTankLV,"LeadTank", worldLV,false,0,true);
  
  // ==== Steel Tank Wall
  G4Tubs* SteelTankWallS
    = new G4Tubs("SteelTankWall", (Lead_Tank_w/2-Lead_Opening_hi)*cm, 
                                  (Lead_Tank_w/2-Lead_Opening_lo)*cm, 
                                  (Sample_space_u)/2*cm,0.*deg,360.*deg);  
  G4LogicalVolume* SteelTankWallLV
    = new G4LogicalVolume(SteelTankWallS, Al, "SteelTankWall");
  G4VPhysicalVolume* SteelTankWallPV  
    = new G4PVPlacement(0, G4ThreeVector(0, 0, (SteelTankWallS->GetZHalfLength() - 
                                                LeadTankWallS->GetZHalfLength()+
                                                LeadTankOpeningS->GetZHalfLength()*2+
                                                Sample_space_h*cm)),
                        SteelTankWallLV,"SteelTankWall", LeadTankLV,false,0,true);
  
  // ==== Secondary Lead
  G4Tubs* SecondaryLeadS
    = new G4Tubs("SecondaryLead", (Lead_Tank_w/2-Lead_Opening_hi+Secondary_Lead_i)*cm, 
                                  (Lead_Tank_w/2-Lead_Opening_lo-Secondary_Lead_t)*cm, 
                                  (Sample_space_u-Secondary_Lead_t)/2*cm,0.*deg,360.*deg);  
  G4LogicalVolume* SecondaryLeadLV
    = new G4LogicalVolume(SecondaryLeadS, Pb, "SecondaryLead");
  G4VPhysicalVolume* SecondaryLeadPV  
    = new G4PVPlacement(0, G4ThreeVector(0, 0, Secondary_Lead_t/2*cm),
                        SecondaryLeadLV,"SecondaryLead", SteelTankWallLV,false,0,true);
  // ==== Primary Lead Wall
  G4Tubs* PrimaryLeadWallS
    = new G4Tubs("PrimaryLeadWall", 0*cm, 
                                    (Lead_Tank_w/2-Lead_Opening_lo)*cm, 
                                    (Lead_Head_u+Secondary_Lead_i+Secondary_Lead_t)/2*cm,0.*deg,360.*deg);  
  G4LogicalVolume* PrimaryLeadWallLV
    = new G4LogicalVolume(PrimaryLeadWallS, Al, "PrimaryLeadWall");
  G4VPhysicalVolume* PrimaryLeadWallPV  
    = new G4PVPlacement(0, G4ThreeVector(0, 0, (LeadTankWallS->GetZHalfLength() - 
                                                PrimaryLeadWallS->GetZHalfLength()-
                                                (Lead_Head_h-Secondary_Lead_t-Secondary_Lead_i)*cm)),
                        PrimaryLeadWallLV,"PrimaryLeadWall", LeadTankLV,false,0,true);  
  
  // ==== Primary Lead Wall Cu Lining
  G4Tubs* PrimaryLeadWall_CuS
    = new G4Tubs("PrimaryLeadWall_Cu", 0*cm, 
                                     (Lead_Tank_w/2-Lead_Opening_lo-Secondary_Lead_t)*cm, 
                                     PrimaryLeadWallS->GetZHalfLength()-(Secondary_Lead_t)*cm,0.*deg,360.*deg);  
  G4LogicalVolume* PrimaryLeadWall_CuLV
    = new G4LogicalVolume(PrimaryLeadWall_CuS, Cu, "PrimaryLeadWall_Cu");
  G4VPhysicalVolume* PrimaryLeadWall_CuPV  
    = new G4PVPlacement(0, G4ThreeVector(),
                        PrimaryLeadWall_CuLV,"PrimaryLeadWall_Cu", PrimaryLeadWallLV,false,0,true);
  
  // ==== Primary Lead Room
  G4Tubs* PrimaryLeadRoomS
    = new G4Tubs("PrimaryLeadRoom", 0*cm, 
                                    (Lead_Tank_w/2-Lead_Opening_lo-Secondary_Lead_t-Secondary_Lead_i)*cm, 
                                    PrimaryLeadWallS->GetZHalfLength()-(Secondary_Lead_i/2+Secondary_Lead_t)*cm,
                                    0.*deg,360.*deg);  
  G4LogicalVolume* PrimaryLeadRoomLV
    = new G4LogicalVolume(PrimaryLeadRoomS, air, "PrimaryLeadRoom");
  G4VPhysicalVolume* PrimaryLeadRoomPV  
    = new G4PVPlacement(0, G4ThreeVector(0,0,-Secondary_Lead_i/2*cm),
                        PrimaryLeadRoomLV,"PrimaryLeadRoom", PrimaryLeadWall_CuLV,false,0,true);
  
  LogicDetector.push_back(ScintillatorLV);
  noReplica.push_back(1);
  //LogicDetector.push_back(worldLV);
  //noReplica.push_back(1);
  return worldPV; 
}

void DetectorConstruction::ConstructSDandField()
{ 
  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  for (G4int i = 0; i < LogicDetector.size(); i++)
  {
    G4LogicalVolume *SD = LogicDetector[i];  
    G4int copyNo        = noReplica[i];
    
    SensitiveDetector *SDetector = new SensitiveDetector(SD->GetName(),copyNo);
    SDName.push_back(SD->GetName());
    
    SD    -> SetSensitiveDetector(SDetector);
    SDMan -> AddNewDetector(SDetector);
  }
}
