CMAKE_MINIMUM_REQUIRED(VERSION  3.31)
project(gtkmm_password LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE RELEASE)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GPGME REQUIRED gpgme)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_library(fsys STATIC fsys.cpp auxiliar.cpp genera.cpp)

# Adicionar directorios
# ---------------------
 add_subdirectory(treestore)
 add_executable(test_01 test_01.cpp fsys.cpp auxiliar.cpp)
 target_link_libraries(test_01 gpgme)
 


# Instalación.
#-------------
# install(TARGETS gtkmm_password DETINATION bin)
install(TARGETS fsys DESTINATION lib)
install(FILES gtkmm_password.desktop DESTINATION share/applications)
install(FILES gtkmm_password.svg DESTINATION share/icons/gtkmm_password)
install(TARGETS gtkmm_password DESTINATION bin)
install(FILES dconfirma/g1.png DESTINATION share/pixmaps/gtkmm_password)
install(FILES README.md LICENSE DESTINATION share/doc/gtkmm_password)
