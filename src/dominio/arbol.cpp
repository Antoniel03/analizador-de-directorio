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
using std::stack;
using std::string;

Arbol::Arbol() {}

Arbol::Arbol(string root)
{
  archivo n = crearNodoArchivo(root);
  archivos[root] = n;
  raiz = root;
  keys.push_back(n.ruta);
}

string Arbol::getRaiz() { return raiz; }

void Arbol::agregarArchivo(string path)
{
  archivo n = crearNodoArchivo(path);
  string parent = getPadre(n.ruta);
  if (tienePadre(parent))
  {
    archivos[n.ruta] = n;
    distribuirPeso(n.ruta, n.peso);
    if (!esCarpeta(n.ruta))
      conteoElementos(n.ruta);
    archivos[parent].hijos.push_back(n.ruta);
  }
}

void Arbol::agregarKey(string path) { keys.push_back(path); }

bool Arbol::tienePadre(string path)
{
  if (archivos.find(path) != archivos.end())
    return true;
  return false;
}

archivo Arbol::getArchivo(string key) { return archivos[key]; }

archivo *Arbol::getPunteroArchivo(string key) { return &archivos[key]; }

void Arbol::auxiliarPreorden(archivo *raiz, list<archivo> &ans)
{
  if (!raiz)
    return;
  ans.push_back(*raiz);
  for (auto child : raiz->hijos)
  {
    auxiliarPreorden(getPunteroArchivo(child), ans);
  }
}

list<archivo> Arbol::preorden(string ruta)
{
  list<archivo> ans;
  archivo *root = &archivos[ruta];
  if (!root)
    return ans;
  auxiliarPreorden(root, ans);
  return ans;
}

// Retorna una lista de resultados que contienen el substring proporcionado
list<archivo> Arbol::keySimilares(string key)
{
  list<archivo> resultados;

  for (string ruta : keys)
  {
    if (contieneSubstring(ruta, key))
      if (key != archivos[ruta].nombre)
        resultados.push_back(archivos[ruta]);
  }
  return resultados;
}

list<archivo> Arbol::busquedaPorNombre(string objetivo)
{
  list<archivo> resultado;
  for (string archivo : keys)
  {
    string nombre = archivos[archivo].nombre;
    if (nombre == objetivo)
    {
      resultado.push_back(archivos[archivo]);
    }
  }
  return resultado;
}

list<archivo> Arbol::busquedaPorExtension(string extension)
{
  list<archivo> resultados;
  for (string elemento : keys)
  {
    string formatoWin = invertirFormato(elemento);
    std::filesystem::path rutaArchivo{formatoWin};
    if ("." + extension == rutaArchivo.extension())
      resultados.push_back(archivos[elemento]);
  }
  return resultados;
}

bool Arbol::existeKey(string path)
{
  for (string key : keys)
  {
    if (key == path)
      return true;
  }
  return false;
}

// Agrega el tamaño al archivo dado y a
//  las carpetas contenedoras de forma recursiva
void Arbol::distribuirPeso(string ruta, int peso)
{
  int size = split(ruta, '\\').size();
  if (size == 1)
    return;
  else
  {
    string padre = getPadre(ruta);
    archivos[padre].peso += peso;
    distribuirPeso(padre, peso);
  }
}

// Incrementa la cantidad de elementos registrados en
// las carpetas contenedoras de forma recursiva
void Arbol::conteoElementos(string ruta)
{
  int size = split(ruta, '\\').size();
  if (size == 1)
    return;
  else
  {
    string padre = getPadre(ruta);
    archivos[padre].subelementos++;
    conteoElementos(padre);
  }
}

// Retorna un hashmap con los archivos más pesados
// De cada carpeta
// Se accede al archivo del hashmap con la ruta de la carpeta

map<string, archivo> Arbol::getArchivosMasPesados()
{
  map<string, archivo> resultado;
  for (string ruta : keys)
  {
    if (esCarpeta(ruta))
    {
      resultado[ruta] = obtenerArchivoMasPesado(ruta);
    }
  }
  return resultado;
}

// Realiza un recorrido preorden a partir de la ruta especificada
// En busqueda del archivo más pesado de la misma
archivo Arbol::obtenerArchivoMasPesado(string ruta)
{
  if (archivos[ruta].subelementos == 0)
  {
    archivo np;
    np.nombre = "No posee archivo";
    return np;
  }

  list<archivo> recorrido = preorden(ruta);
  archivo masPesado;
  for (archivo subRuta : recorrido)
  {
    if ((subRuta.peso > masPesado.peso) && (!esCarpeta(subRuta.ruta)))
    {
      masPesado = subRuta;
    }
  }
  return masPesado;
}