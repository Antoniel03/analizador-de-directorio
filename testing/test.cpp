#include "../src/dominio/headers/arbol.hpp"
#include "../src/dominio/headers/utilidades.hpp"
#include "../src/presentacion/interfaz.hpp"
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

int main() {
  Tree t = getTreeFromPath("..");
  Interfaz i;

  list<node> test = t.preorden("..");
  i.printStringList(test);

  cout << "----" << endl;
}
