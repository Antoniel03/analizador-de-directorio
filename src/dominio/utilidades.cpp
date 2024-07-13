#include "../dominio/headers/arbol.hpp"
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
using std::stack;
using std::string;
using std::vector;

// Recibe la ruta del archivo y retorna su tamaño
int getPeso(string ruta)
{
  string rutaWin = invertirFormato(ruta);
  std::filesystem::path elemento(rutaWin);
  int peso;
  try
  {
    peso = std::filesystem::file_size(elemento);
  }
  catch (const std::filesystem::filesystem_error &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return peso;
}

// Verifica si la ruta especificada es una carpeta
// Verdadero: es una carpeta
// Falso: No lo es
bool esCarpeta(string ruta)
{
  std::filesystem::path elemento(ruta);
  if (std::filesystem::is_directory(elemento))
    return true;
  return false;
}

// Repite un caracter n cantidad de veces y retorna el resultado de ello
string getStringRepetido(char c, int i)
{
  string result;
  for (int j = 0; j < i; j++)
  {
    result += c;
    result += c;
    result += c;
    result += c;
  }
  return result;
}
// Imprime un elemento de tipo archivo emulando su identacion
void levelPrint(archivo n)
{
  string identated = getStringRepetido(' ', n.level) + n.route;
  cout << identated << endl;
}

// Retorna un arreglo de strings, elemento siendo un fragmento del
// Arreglo original particionado a partir del caracter especificado.
vector<string> split(string texto, char caracter)
{
  vector<string> resultado;
  string palabra = "";

  for (auto i : texto)
  {
    if (i != caracter)
      palabra += i;

    else if (i == caracter)
    {
      resultado.push_back(palabra);
      palabra = "";
    }
  }
  resultado.push_back(palabra);
  return resultado;
}

// Une un vector de strings mediante un caracter y rango especificado
string unirVectorStrings(vector<string> segmentedText, char separator,
                         int partsToJoin)
{
  string result;
  int size = segmentedText.size();
  for (int i = 0; i < partsToJoin; i++)
  {
    result += segmentedText[i];
    if (i != partsToJoin - 1)
      result += separator;
  }
  return result;
}

// Rellena los campos del struct archivo a partir de una ruta
archivo crearNodoArchivo(string path)
{
  vector<string> segmentedPath = split(path, '\\');
  int size = segmentedPath.size();
  archivo n;
  n.name = segmentedPath[size - 1];
  // cout<<n.name<<endl;
  n.route = path;
  n.level = size;
  if (!esCarpeta(path))
  {
    n.peso = getPeso(path);
  }
  return n;
}

// Retorna una lista vacía
list<archivo> getEmptyList()
{
  list<archivo> l;
  return l;
}

// Retorna el contenedor de la ruta especificada
string getPadre(string path)
{
  vector<string> segmentedPath = split(path, '\\');
  int size = segmentedPath.size();
  string parent = unirVectorStrings(segmentedPath, '\\', size - 1);
  return parent;
}

// Verifica si la ruta proporcionada es contenedor del segundo parámetro
bool esPadre(string padre, string hijo)
{
  if (getPadre(hijo) == padre)
    return true;
  return false;
}

// Retorna un arbol con todos los elementos de un directorio especificado y sus relaciones
Tree getArbolDeRuta(string pathToDirectory)
{
  std::filesystem::path p = pathToDirectory;
  Tree t{pathToDirectory};

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p))
  {
    string entrada = entry.path().string();

    t.agregarArchivo(entrada);
    if (entrada != pathToDirectory)
    {
      t.agregarKey(entrada);
    }
  }
  return t;
}

// Verifica si existe la ruta especificada
// Verdadero: Sí, existe
// Verdadero: No existe
bool existeDirectorio(string ruta)
{
  if (std::filesystem::exists(ruta))
    return true;

  return false;
}

// Verifica si un string contiene el substring especificado
bool contieneSubstring(string texto, string caracteres)
{
  int check = 0;
  int letras = caracteres.length();

  for (char c : texto)
  {
    if (c == caracteres[check])
    {
      check++;
      if (check == letras)
        return true;
    }
    else
      check = 0;
  }

  return false;
}

// Cambia el formato de la ruta de \\ a /
string formatearRuta(string ruta)
{
  vector<string> rutaSegmentada = split(ruta, '\\');
  int size = rutaSegmentada.size();
  string resultado = unirVectorStrings(rutaSegmentada, '/', size);
  return resultado;
}

// Invierte el formateo anterior
string invertirFormato(string ruta)
{
  vector<string> rutaSegmentada = split(ruta, '/');
  int size = rutaSegmentada.size();
  string resultado = unirVectorStrings(rutaSegmentada, '\\', size);
  return resultado;
}

string getNombreArchivo(string ruta)
{
  vector<string> rutaSegmentada = split(ruta, '\\');
  int size = rutaSegmentada.size();
  return rutaSegmentada[size - 1];
}

float calcularEspacioTotal(int raiz, int carpeta)
{
  return ((carpeta * 1.00) / (raiz * 1.00)) * 100;
}