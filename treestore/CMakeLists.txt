include_directories(${CTKMM_INCLUDE_DIRS})

add_executable(gtkmm_password main.cpp ventana_main.cpp
    ../textview/textview.cpp ../mdialogo/mdialogo.cpp
    ../dconfirma/dconfirma.cpp)

target_link_libraries(gtkmm_password ${GTKMM_LIBRARIES} fsys gpgme)

install(TARGETS gtkmm_password DESTINATION bin)
# install(TARGETS ../dconfirma/g1.png DESTINATION pixmap/gtkmm_password)
# install(TARGETS fsys DESTINATION lib)
# install(TARGETS ../gtkmm_password.desktop DESTINATION applications)
# install(TARGETS ../gtkmm_password.svg DESTINATION icons/gtkmm_password)
 
