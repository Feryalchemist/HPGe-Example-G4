cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(FissionDecay)

find_package(Geant4 REQUIRED  ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(Simulation Simulation.cc ${sources} ${headers} )
target_link_libraries(Simulation ${Geant4_LIBRARIES})

add_custom_target(FissionDecay DEPENDS Simulation)

set(SIMULATION_SCRIPTS
  vis.mac
  run.mac
  )

foreach(_script ${SIMULATION_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

