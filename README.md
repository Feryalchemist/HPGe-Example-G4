# HPGe-Example-G4

This is an example of Geant4 implementation for simulating HPGe detector. The detector is modelled with a dead layer and lead shielding. The emission source could be changed in run.mac file since it uses General Particle Source (GPS). The result consists of the energy deposition for each simulated particle, compiled inside a tabulated 'HistData.dat' file and the '.root' file. In current settings, the simulation could not run in Multithreade due to the needs of continously read/write file to HistData (ASCII) after each simulated event.


<p align="center">
  <img src="https://github.com/Feryalchemist/HPGe-Example-G4/blob/main/Geom.png?raw=true" alt="HPGe Geometry"/>
</p>

The column of 'HistData.dat' comprises of:

EventID,TrackID,fx,fy,fz,CopyNo,Particle,Edep,Volume
- `EventID`; the particle eventID where its energy deposited in HPGe
- `TrackID`; the last trackID of the particle when it fully absorbed
- `fx,fy,fz`; last coordinate of the particle
- `CopyNo`; The copy number of the geometry (1 if it is not copied)
- `Particle`; The particle type of the absorbed emission
- `Edep`; Total Energy deposition of the event
- `Volume`; Name of the PhysicalVolume where the particle absorbed  
