#include "../src/dominio/headers/arbol.hpp"
#include "../src/dominio/headers/utilidades.hpp"
#include "../src/presentacion/interfaz.hpp"
#include "../src/datos/manejadorHTML.hpp"
#include <iostream>

#include <list>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::string;
using std::vector;

int main()
{
  Tree t = getArbolDeRuta("..");
  Interfaz i;
  list<archivo> test = t.preorden("..");
  manejadorHTML h{test};

  h.armarCuerpoHTML();
}
