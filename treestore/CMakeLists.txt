include_directories(${CTKMM_INCLUDE_DIRS})

add_executable(gtkmm_password main.cpp ventana_main.cpp
    ../textview/textview.cpp ../mdialogo/mdialogo.cpp
    ../dconfirma/dconfirma.cpp)

target_link_libraries(gtkmm_password ${GTKMM_LIBRARIES} fsys gpgme)


