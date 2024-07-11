#include "headers/arbol.hpp"
#include "../estructuras/nodo.hpp"
#include "headers/utilidades.hpp"
#include <filesystem>
#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::string;

Tree::Tree() {}

Tree::Tree(string root) {
  node n = createNode(root);
  nodes[root] = n;
  keys.push_back(n.route);
}

void Tree::addNode(string path) {
  node n = createNode(path);
  string parent = getParent(n.route);
  if (hasFather(parent)) {
    nodes[n.route] = n;
    /*nodes[parent].peso += n.peso;*/
    nodes[parent].childs.push_back(n.route);
  }
}

void Tree::addKey(string path) { keys.push_back(path); }

void Tree::printKeys() {
  for (auto i : keys) {
    node n = nodes[i];
    levelPrint(n);
  }
}

bool Tree::hasFather(string path) {
  if (nodes.find(path) != nodes.end())
    return true;
  return false;
}

void Tree::printChilds(string key) {
  list<string> childs = nodes[key].childs;
  cout << "Elements in -> " << key << endl;
  for (auto i : childs) {
    cout << i << endl;
  }
}
node Tree::getNode(string key) { return nodes[key]; }

node *Tree::getAddressToNode(string key) { return &nodes[key]; }

void Tree::auxiliarPreorden(node *raiz, list<node> &ans) {
  if (!raiz)
    return;
  ans.push_back(*raiz);
  for (auto child : raiz->childs) {
    auxiliarPreorden(getAddressToNode(child), ans);
  }
}

list<node> Tree::preorden(string ruta) {
  list<node> ans;
  node *root = &nodes[ruta];
  if (!root)
    return ans;
  auxiliarPreorden(root, ans);
  return ans;
}

list<node> Tree::keySimilares(string key) {
  list<node> resultados;

  for (string ruta : keys) {
    if (contieneSubstring(ruta, key))
      if (key != nodes[ruta].name)
        resultados.push_back(nodes[ruta]);
  }
  return resultados;
}

list<node> Tree::busquedaPorNombre(string objetivo) {
  list<node> resultado;
  for (string archivo : keys) {
    string nombre = nodes[archivo].name;
    if (nombre == objetivo) {
      resultado.push_back(nodes[archivo]);
    }
  }
  return resultado;
}

list<node> Tree::busquedaPorExtension(string extension) {
  list<node> resultados;
  for (string archivo : keys) {
    std::filesystem::path rutaArchivo{archivo};
    if ("." + extension == rutaArchivo.extension())
      resultados.push_back(nodes[archivo]);
  }
  return resultados;
}

void Tree::cargarPesoDeCarpetas() {
  for (string key : keys) {
    if (esCarpeta(key)) {
      for (string hijo : nodes[key].childs) {
        nodes[key].peso += nodes[hijo].peso;
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
