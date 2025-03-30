
include_directories(${CTKMM_INCLUDE_DIRS})
add_executable(exec_dconfirma dconfirma.cpp)

target_link_libraries(exec_dconfirma ${GTKMM_LIBRARIES})


