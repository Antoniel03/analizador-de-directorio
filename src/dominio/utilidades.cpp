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

int getPeso(string ruta) {
  std::filesystem::path archivo(ruta);
  int peso;
  try {
    peso = std::filesystem::file_size(archivo);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return peso;
}

bool esCarpeta(string ruta) {
  std::filesystem::path archivo(ruta);
  if (std::filesystem::is_directory(archivo))
    return true;
  return false;
}

string getRepeatedString(char c, int i) {
  string result;
  for (int j = 0; j < i; j++) {
    result += c;
    result += c;
    result += c;
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
  if (!esCarpeta(path)) {
    n.peso = getPeso(path);
  }
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
    if (path != pathToDirectory)
      t.addKey(path);
  }
  t.cargarPesoDeCarpetas();
  return t;
}

void printRawDirectory(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    cout << entry.path() << endl;
  }
}

bool existeDirectorio(string ruta) {
  if (std::filesystem::exists(ruta))
    return true;

  return false;
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
