include_directories(${CTKMM_INCLUDE_DIRS})

add_executable(mdialogo mdialogo.cpp)

target_link_libraries(mdialogo ${GTKMM_LIBRARIES})


