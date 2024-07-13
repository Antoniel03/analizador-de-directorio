
#include <iostream>
#include <list>

using std::list;
using std::string;

#ifndef NODO
#define NODO

struct archivo
{
  string nombre;
  string ruta;
  int peso = 0;
  int level = 0;
  int subelementos = 0;
  list<string> hijos;
};

#endif // !DEBUG
