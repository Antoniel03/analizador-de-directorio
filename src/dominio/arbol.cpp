#include "headers/arbol.hpp"
#include "../estructuras/nodo.hpp"
#include "headers/utilidades.hpp"
#include <filesystem>
#include <iostream>
#include <list>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::list;
using std::string;
using std::stack;

Tree::Tree() {}

Tree::Tree(string root) {
  archivo n = crearNodoArchivo(root);
  archivos[root] = n;
  raiz=root;
  keys.push_back(n.route);
}

string Tree::getRaiz(){return raiz;}

void Tree::agregarArchivo(string path) {
  archivo n = crearNodoArchivo(path);
  string parent = getPadre(n.route);
  if (tienePadre(parent)) {
    archivos[n.route] = n;
    distribuirPeso(n.route, n.peso);
    /*archivos[parent].peso += n.peso;*/
    archivos[parent].childs.push_back(n.route);
  }
}

void Tree::agregarKey(string path) { keys.push_back(path); }

void Tree::printKeys() {
  for (auto i : keys) {
    archivo n = archivos[i];
    levelPrint(n);
  }
}

bool Tree::tienePadre(string path) {
  if (archivos.find(path) != archivos.end())
    return true;
  return false;
}

void Tree::printChilds(string key) {
  list<string> childs = archivos[key].childs;
  cout << "Elements in -> " << key << endl;
  for (auto i : childs) {
    cout << i << endl;
  }
}
archivo Tree::getArchivo(string key) { return archivos[key]; }

archivo *Tree::getPunteroArchivo(string key) { return &archivos[key]; }

void Tree::auxiliarPreorden(archivo *raiz, list<archivo> &ans) {
  if (!raiz)
    return;
  ans.push_back(*raiz);
  for (auto child : raiz->childs) {
    auxiliarPreorden(getPunteroArchivo(child), ans);
  }
}

list<archivo> Tree::preorden(string ruta) {
  list<archivo> ans;
  archivo *root = &archivos[ruta];
  if (!root)
    return ans;
  auxiliarPreorden(root, ans);
  return ans;
}

list<archivo> Tree::keySimilares(string key) {
  list<archivo> resultados;

  for (string ruta : keys) {
    if (contieneSubstring(ruta, key))
      if (key != archivos[ruta].name)
        resultados.push_back(archivos[ruta]);
  }
  return resultados;
}

list<archivo> Tree::busquedaPorNombre(string objetivo) {
  list<archivo> resultado;
  for (string archivo : keys) {
    string nombre = archivos[archivo].name;
    if (nombre == objetivo) {
      resultado.push_back(archivos[archivo]);
    }
  }
  return resultado;
}

list<archivo> Tree::busquedaPorExtension(string extension) {
  list<archivo> resultados;
  for (string elemento : keys) {
    string formatoWin= invertirFormato(elemento);
    std::filesystem::path rutaArchivo{formatoWin};
    cout<<formatoWin<<endl;
    if ("." + extension == rutaArchivo.extension())
      resultados.push_back(archivos[elemento]);
  }
  return resultados;
}

void Tree::cargarPesoDeCarpetas() {
  for (string key : keys) {
    if (esCarpeta(key)) {
      for (string hijo : archivos[key].childs) {
        archivos[key].peso += archivos[hijo].peso;
      }
    }
  }
}

bool Tree::existeKey(string path) {
  for (string key : keys) {
    if (key == path)
      return true;
  }
  return false;
}

list<archivo> Tree::postorder(string root)
{
  list<archivo> resultado;
  stack<archivo *> nodosVisitados;

  nodosVisitados.push(&archivos[root]);

  while (!nodosVisitados.empty())
  {
    archivo *nodo = nodosVisitados.top();
    nodosVisitados.pop();

    if (nodo == NULL)
      continue;

    for (string child : nodo->childs)
    {
      nodosVisitados.push(&archivos[child]);
    }

    resultado.push_back(archivos[nodo->name]);
    cout<<"added: "<<nodo->name<<endl;
  }
  return resultado;
}

void Tree::distribuirPeso(string ruta, int peso){
  int size= split(ruta,'\\').size();
  if(size==1)
    return;
  else{ 
   string padre = getPadre(ruta);
    archivos[padre].peso+=peso;
   distribuirPeso(padre, peso);
  }
}