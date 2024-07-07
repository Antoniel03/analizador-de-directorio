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

list<string> busquedaPorNombre(string objetivo, list<string> nombres) {
  list<string> resultado;
  for (string nombre : nombres) {

    if (nombre == objetivo) {
      resultado.push_back(objetivo);
    }
  }
  return resultado;
}

bool contieneSubstring(string texto, string caracteres) {
  int check = 0;
  int letras = caracteres.length();

  for (char c : texto) {
    if (c == caracteres[check]) {
      check++;
      if (check == letras)
        return true;
    } else
      check = 0;
  }

  return false;
}

/*list<string> busquedaPorSubstring(string objetivo, list<string> nombres) {}*/

int main() {
  Tree t = getTreeFromPath("..");
  Interfaz i;

  list<string> test = t.preorden("..");
  i.printStringList(test);

  cout << "----" << endl;
}
