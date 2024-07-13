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

Tree::Tree() {}

Tree::Tree(string root)
{
  archivo n = crearNodoArchivo(root);
  archivos[root] = n;
  raiz = root;
  keys.push_back(n.route);
}

string Tree::getRaiz() { return raiz; }

void Tree::agregarArchivo(string path)
{
  archivo n = crearNodoArchivo(path);
  string parent = getPadre(n.route);
  if (tienePadre(parent))
  {
    archivos[n.route] = n;
    distribuirPeso(n.route, n.peso);
    if (!esCarpeta(n.route))
      conteoElementos(n.route);
    archivos[parent].childs.push_back(n.route);
  }
}

void Tree::agregarKey(string path) { keys.push_back(path); }

bool Tree::tienePadre(string path)
{
  if (archivos.find(path) != archivos.end())
    return true;
  return false;
}

archivo Tree::getArchivo(string key) { return archivos[key]; }

archivo *Tree::getPunteroArchivo(string key) { return &archivos[key]; }

void Tree::auxiliarPreorden(archivo *raiz, list<archivo> &ans)
{
  if (!raiz)
    return;
  ans.push_back(*raiz);
  for (auto child : raiz->childs)
  {
    auxiliarPreorden(getPunteroArchivo(child), ans);
  }
}

list<archivo> Tree::preorden(string ruta)
{
  list<archivo> ans;
  archivo *root = &archivos[ruta];
  if (!root)
    return ans;
  auxiliarPreorden(root, ans);
  return ans;
}

// Retorna una lista de resultados que contienen el substring proporcionado
list<archivo> Tree::keySimilares(string key)
{
  list<archivo> resultados;

  for (string ruta : keys)
  {
    if (contieneSubstring(ruta, key))
      if (key != archivos[ruta].name)
        resultados.push_back(archivos[ruta]);
  }
  return resultados;
}

list<archivo> Tree::busquedaPorNombre(string objetivo)
{
  list<archivo> resultado;
  for (string archivo : keys)
  {
    string nombre = archivos[archivo].name;
    if (nombre == objetivo)
    {
      resultado.push_back(archivos[archivo]);
    }
  }
  return resultado;
}

list<archivo> Tree::busquedaPorExtension(string extension)
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

bool Tree::existeKey(string path)
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
void Tree::distribuirPeso(string ruta, int peso)
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
void Tree::conteoElementos(string ruta)
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

map<string, archivo> Tree::getArchivosMasPesados()
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
archivo Tree::obtenerArchivoMasPesado(string ruta)
{
  if (archivos[ruta].subelementos == 0)
  {
    archivo np;
    np.name = "No posee archivo";
    return np;
  }

  list<archivo> recorrido = preorden(ruta);
  archivo masPesado;
  for (archivo subRuta : recorrido)
  {
    if ((subRuta.peso > masPesado.peso) && (!esCarpeta(subRuta.route)))
    {
      masPesado = subRuta;
    }
  }
  return masPesado;
}