#include "../estructuras/nodo.hpp"
#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::string;
using std::vector;

#ifndef MANEJADORHTML
#define MANEJADORHTML

class manejadorHTML
{
private:
  list<archivo> elementos;
  vector<string> htmlSegmentado;
  string HTML;

public:
  manejadorHTML();
  manejadorHTML(list<archivo> archivos);
  string formatoCarpeta(archivo carpeta);
  string armarCuerpoHTML();
  void armarHTML();
  string crearComentario(string comentario);
  string getRutaDeComentario(string comentario);
  bool esComentario(string linea);
  void agregarRaiz();
  void agregarCarpeta(archivo a);
};

#endif // !MANEJADORHTML
