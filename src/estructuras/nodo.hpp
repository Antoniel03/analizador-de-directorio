
#include <iostream>
#include <list>

using std::list;
using std::string;

#ifndef NODO
#define NODO

struct node {
  string name;
  string route;
  int level = 0;
  list<string> childs;
};

#endif // !DEBUG
