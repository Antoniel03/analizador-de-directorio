#include "../../estructuras/nodo.hpp"
#include <iostream>
#include <list>
#include <map>
#include <vector>

using std::endl;
using std::list;
using std::map;
using std::string;

#ifndef ARBOL
#define ARBOL

class Tree {
private:
  map<string, node> nodes;
  list<string> keys;

public:
  Tree();
  Tree(string path);
  void addNode(string path);
  void printKeys(); // Remover
  bool hasFather(string path);
  void printChilds(string key);
  node getNode(string key);
  node *getAddressToNode(string key);
  list<node> preorden(string ruta);
  void auxiliarPreorden(node *raiz, list<node> &ans);
  list<node> busquedaPorNombre(string objetivo);
  list<node> keySimilares(string key);
  list<node> busquedaPorExtension(string extension);
  void addKey(string path);
  void cargarPesoDeCarpetas();
  bool existeKey(string path);
};
#endif // !ARBOL
