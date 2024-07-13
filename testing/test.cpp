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
  map<string, archivo> test2 = t.getArchivosMasPesados();
  for (auto i : test2)
  {
    cout << i.first << endl;
  }
  manejadorHTML h{test, test2};
  //  i.printStringList(test);
  h.generarHTML();
}
