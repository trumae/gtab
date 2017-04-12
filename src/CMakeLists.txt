include_directories(${CPPSMD_SOURCE_DIR}/src/widgets)
link_directories(${CPPSMD_SOURCE_DIR}/src/widgets)

include_directories(${CPPSMD_SOURCE_DIR}/src/logic)
link_directories(${CPPSMD_SOURCE_DIR}/src/logic)

include_directories(${CPPSMD_SOURCE_DIR}/src/utils)
link_directories(${CPPSMD_SOURCE_DIR}/src/utils)

add_executable (gtab 
  application.cpp
  db.cpp
  main.cpp)

#geral
target_link_libraries(gtab m)
target_link_libraries(gtab wt)
target_link_libraries(gtab wthttp)
target_link_libraries(gtab boost_signals)
target_link_libraries(gtab boost_system)
target_link_libraries(gtab Widgets)
target_link_libraries(gtab Logic)
target_link_libraries(gtab Utils)
target_link_libraries(gtab cppdb)

add_subdirectory(logic)
add_subdirectory(widgets)
add_subdirectory(utils)

