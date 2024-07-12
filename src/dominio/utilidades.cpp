#include "../dominio/headers/arbol.hpp"
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
using std::vector;

int getPeso(string ruta) {
  string rutaWin = invertirFormato(ruta);
  std::filesystem::path elemento(rutaWin);
  int peso;
  try {
    peso = std::filesystem::file_size(elemento);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return peso;
}

bool esCarpeta(string ruta) { 
  std::filesystem::path elemento(ruta);
  if (std::filesystem::is_directory(elemento))
    return true;
  return false;
}

string getStringRepetido(char c, int i) {
  string result;
  for (int j = 0; j < i; j++) {
    result += c;
    result += c;
    result += c;
    result += c;
  }
  return result;
}
void levelPrint(archivo n) {
  string identated = getStringRepetido(' ', n.level) + n.route;
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

string unirVectorStrings(vector<string> segmentedText, char separator,
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

archivo crearNodoArchivo(string path) {
  vector<string> segmentedPath = split(path, '\\');
  int size = segmentedPath.size();
  archivo n;
  n.name = segmentedPath[size - 1];
  //cout<<n.name<<endl;
  n.route = path;
  n.level = size;
  if (!esCarpeta(path)) {
    n.peso = getPeso(path);
  }
  return n;
}

list<archivo> getEmptyList() {
  list<archivo> l;
  return l;
}

string getPadre(string path) {
  vector<string> segmentedPath = split(path, '\\');
  int size = segmentedPath.size();
  string parent = unirVectorStrings(segmentedPath, '\\', size - 1);
  return parent;
}

void printDirectorio(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    string path = entry.path().string();
    vector<string> segmentedPath = split(path, '\\');
    int size = segmentedPath.size();
    string filename = segmentedPath[size - 1];
    cout << filename << " - " << path << endl;
  }
}

Tree getArbolDeRuta(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;
  //string rutaFormateada = formatearRuta(p.string());
  Tree t{pathToDirectory};

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    string entrada = entry.path().string();

    //string path = formatearRuta(entrada);    
    //cout<<path<<endl;
    t.agregarArchivo(entrada);
    if (entrada != pathToDirectory){
      t.agregarKey(entrada);
    }
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

string formatearRuta(string ruta){
  vector<string> rutaSegmentada= split(ruta, '\\');
  int size = rutaSegmentada.size();
  string resultado= unirVectorStrings(rutaSegmentada, '/', size);
  return resultado;
}


string invertirFormato(string ruta){
  vector<string> rutaSegmentada= split(ruta, '/');
  int size = rutaSegmentada.size();
  string resultado= unirVectorStrings(rutaSegmentada, '\\', size);
  return resultado;
}