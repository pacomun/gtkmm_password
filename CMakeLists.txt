
CMAKE_MINIMUM_REQUIRED(VERSION  3.31)
project(gtkmm_password LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

# Adicionar directorios
# ---------------------
 add_subdirectory(treestore)

# Adicionar ejecutables
# ---------------------
# add_executable(mta ${SRC_DIR}/main.cpp)

# target_link_libraries(mta ${GTKMM_LIBRARIES} gui
#     funciones sqlite3 registro)

# Activar test
# ------------
# enable_testing()
# add_test(NAME test1 COMMAND test1)
