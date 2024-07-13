#include <iostream>
#include "manejadorHTML.hpp"
#include "../estructuras/nodo.hpp"
#include "../dominio/headers/utilidades.hpp"
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

string header = "<!DOCTYPE html>\n"
                "<html>\n<head>\n    <meta charset=\"UTF-8\">\n"
                "    <meta name= \"directorio.html\" content= \"Favoritos\">\n"
                "    <title>Vista del Directorio</title>\n</head>\n<body>\n"
                "    <h1>Favoritos</h1>\n";

/*  <li><span class="caret">Beverages</span>
    <ul class="nested">*/

manejadorHTML::manejadorHTML() {}
manejadorHTML::manejadorHTML(list<archivo> archivos) { elementos = archivos; }

string manejadorHTML::formatoCarpeta(archivo carpeta)
{
  string nombre = getNombreArchivo(carpeta.name);
  string carpetaFormateada = "<li><span class=\"caret\">" + nombre + "</span>\n" + "<ul class=\"nested\">\n";
  return carpetaFormateada;
}

string manejadorHTML::armarCuerpoHTML()
{
  agregarRaiz();
  int i = 0;
  for (archivo a : elementos)
  {
    if ((esCarpeta(a.route)) && (a.route != elementos.begin()->route))
    {
      agregarCarpeta(a);
    }
  }

  int size = htmlSegmentado.size();
  string cuerpo = unirVectorStrings(htmlSegmentado, '\n', size);
  cout << cuerpo << endl;
  return cuerpo;
}

void manejadorHTML::agregarRaiz()
{
  archivo raiz = *elementos.begin();
  string ruta = raiz.route;
  htmlSegmentado.push_back(formatoCarpeta(raiz));
  htmlSegmentado.push_back(crearComentario(ruta));
  htmlSegmentado.push_back("</ul>\n</li>\n");
}

void manejadorHTML::agregarCarpeta(archivo a)
{
  for (int i = 0; i < htmlSegmentado.size(); i++)
  {
    string ruta = getRutaDeComentario(htmlSegmentado[i]);
    string padre = getPadre(a.route);
    if (ruta == padre)
    {
      string carpeta = formatoCarpeta(a);
      htmlSegmentado.insert(htmlSegmentado.begin() + i, "</ul>\n</li>\n");
      htmlSegmentado.insert(htmlSegmentado.begin() + i, crearComentario(a.route));
      htmlSegmentado.insert(htmlSegmentado.begin() + i, carpeta);
      break;
    }
  }
}

void manejadorHTML::armarHTML() {}

string manejadorHTML::crearComentario(string comentario)
{
  comentario = "<!-- " + comentario + " -->";
  return comentario;
}

string manejadorHTML::getRutaDeComentario(string comentario)
{
  vector<string> vectorComentario = split(comentario, ' ');
  vectorComentario.pop_back();
  string ruta;

  for (int i = 1; i < vectorComentario.size(); i++)
  {
    ruta += vectorComentario[i];
    if (i != vectorComentario.size() - 1)
      ruta += " ";
  }
  return ruta;
}

bool manejadorHTML::esComentario(string linea)
{
  if (contieneSubstring(linea, "<!--"))
    return true;
  return false;
}
