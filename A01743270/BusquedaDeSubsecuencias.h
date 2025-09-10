/*
Verifica si un string (patron) es subsecuencia de otro (texto). 
Es decir, si puedes encontrar todos los caracteres del patrón en 
el texto en orden, pero no necesariamente consecutivos.
*/

#ifndef BUSQUEDADESUBSECUENCIAS_H
#define BUSQUEDADESUBSECUENCIAS_H

#include <iostream>
#include <string>

bool esSubsecuencia(const std::string& mcode, const std::string& transmission);

#endif // BUSQUEDADESUBSECUENCIAS_H