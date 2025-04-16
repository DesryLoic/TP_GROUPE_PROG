# CMakeList.txt : projet CMake pour TP_GROUPE, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_executable (TP_GROUPE "TP_GROUPE.cpp")
add_executable (TP_GROUPE_EX8 "TP_GROUPE_EX8.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TP_GROUPE PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
