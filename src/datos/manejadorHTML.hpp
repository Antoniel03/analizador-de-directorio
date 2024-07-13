#include "../estructuras/nodo.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <map>

using std::list;
using std::map;
using std::string;
using std::vector;

#ifndef MANEJADORHTML
#define MANEJADORHTML
class manejadorHTML
{
private:
  list<archivo> elementos;
  vector<string> htmlSegmentado;
  map<string, archivo> elementosMasPesados;
  string HTML;

public:
  manejadorHTML();
  manejadorHTML(list<archivo> archivos, map<string, archivo> masPesados);
  string formatoCarpeta(archivo carpeta);
  string armarCuerpoHTML();
  void armarHTML();
  string crearComentario(string comentario);
  string getRutaDeComentario(string comentario);
  bool esComentario(string linea);
  void agregarRaiz();
  void agregarCarpeta(archivo a);
  void generarHTML();
  void guardarHTML(string nombre, string contenido);
};

#endif // !MANEJADORHTML
