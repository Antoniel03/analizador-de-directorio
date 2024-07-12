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
  map<string, archivo> archivos;
  list<string> keys;

public:
  Tree();
  Tree(string path);
  void agregarArchivo(string path);
  void printKeys(); // Remover
  bool tienePadre(string path);
  void printChilds(string key); // Remover
  archivo getArchivo(string key);
  archivo *getPunteroArchivo(string key);
  list<archivo> preorden(string ruta);
  void auxiliarPreorden(archivo *raiz, list<archivo> &ans);
  list<archivo> busquedaPorNombre(string objetivo);
  list<archivo> keySimilares(string key);
  list<archivo> busquedaPorExtension(string extension);
  void agregarKey(string path);
  void cargarPesoDeCarpetas();
  bool existeKey(string path);
};
#endif // !ARBOL
