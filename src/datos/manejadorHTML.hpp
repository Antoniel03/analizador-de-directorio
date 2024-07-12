#include "../estructuras/nodo.hpp"
#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::string;

#ifndef MANEJADORHTML
#define MANEJADORHTML

class manejadorHTML {
private:
  list<archivo> elementos;
  string HTML;

public:
  string formatearCarpeta(archivo carpeta);
  string formatearArchivo(archivo a);
  string armarCuerpoHTML();
  void armarHTML();
};

#endif // !MANEJADORHTML
