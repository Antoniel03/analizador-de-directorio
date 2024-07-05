#include "../dominio/headers/arbol.hpp"
#include "../estructuras/nodo.hpp"
#include <filesystem>
#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

string getRepeatedString(char c, int i) {
  string result;
  for (int j = 0; j < i; j++) {
    result += c;
  }
  return result;
}

void levelPrint(node n) {
  string identated = getRepeatedString(' ', n.level) + n.route;
  cout << identated << endl;
}

vector<string> split(string texto, char caracter) {

  vector<string> resultado;
  string palabra = "";

  for (auto i : texto) {
    if (i != caracter)
      palabra += i;

    else if (i == caracter) {
      resultado.push_back(palabra);
      palabra = "";
    }
  }

  resultado.push_back(palabra);
  return resultado;
}

string joinVectorStrings(vector<string> segmentedText, char separator,
                         int partsToJoin) {
  string result;
  int size = segmentedText.size();
  for (int i = 0; i < partsToJoin; i++) {
    result += segmentedText[i];
    if (i != partsToJoin - 1)
      result += separator;
  }
  return result;
}

node createNode(string path) {
  vector<string> segmentedPath = split(path, '/');
  int size = segmentedPath.size();
  node n;
  n.name = segmentedPath[size - 1];
  n.route = path;
  n.level = size;
  return n;
}

list<node> getEmptyList() {
  list<node> l;
  return l;
}

string getParent(string path) {
  vector<string> segmentedPath = split(path, '/');
  int size = segmentedPath.size();
  string parent = joinVectorStrings(segmentedPath, '/', size - 1);
  return parent;
}

void printDirectory(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    string path = entry.path();
    vector<string> segmentedPath = split(path, '/');
    int size = segmentedPath.size();
    string filename = segmentedPath[size - 1];
    cout << filename << " - " << path << endl;
  }
}

Tree getTreeFromPath(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;
  Tree t{pathToDirectory};

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    string path = entry.path();
    t.addNode(path);
  }
  return t;
}

void printRawDirectory(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    cout << entry.path() << endl;
  }
}

void printStringList(list<string> elements) {
  for (string i : elements) {
    cout << i << endl;
  }
}

void helper(node *root, list<string> &ans, Tree t) {
  if (!root)
    return;
  ans.push_back(root->route);
  for (auto child : root->childs) {
    helper(t.getAddressToNode(child), ans, t);
  }
}

list<string> preorder(node *root, Tree *t) {
  list<string> ans;
  if (!root)
    return ans;
  helper(root, ans, *t);
  return ans;
}
