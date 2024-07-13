
#include <iostream>
#include <list>

using std::list;
using std::string;

#ifndef NODO
#define NODO

struct archivo
{
  string name;
  string route;
  int peso = 0;
  int level = 0;
  int subelementos = 0;
  list<string> childs;
};

#endif // !DEBUG
