#include "headers/arbol.hpp"
#include "../estructuras/nodo.hpp"
#include "headers/utilidades.hpp"
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
  nodes[root];
  keys.push_back(n.name);
}

void Tree::addNode(string path) {
  node n = createNode(path);
  string parent = getParent(n.route);
  if (hasFather(parent)) {
    keys.push_back(n.route);
    nodes[n.route] = n;
    nodes[parent].childs.push_back(n.route);
  }
}

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
