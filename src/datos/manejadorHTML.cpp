#include "manejadorHTML.hpp"
#include "../estructuras/nodo.hpp"
#include "../dominio/headers/utilidades.hpp"
#include <list>
#include <vector>
#include <iomanip>
#include <fstream>

using std::cout;
using std::endl;
using std::list;
using std::ofstream;
using std::string;
using std::vector;

manejadorHTML::manejadorHTML()
{
}
manejadorHTML::manejadorHTML(list<archivo> archivos, map<string, archivo> masPesados)
{
  elementos = archivos;
  elementosMasPesados = masPesados;
}

// Crea un string con el formato que
// Tendrá la carpeta en el HTML
string manejadorHTML::formatoCarpeta(archivo carpeta)
{
  float espacioTotalp = calcularEspacioTotal(elementos.begin()->peso, carpeta.peso);
  string nombre = getNombreArchivo(carpeta.nombre);
  int masPesado = elementosMasPesados[carpeta.ruta].peso;
  string masPesadoNombre = elementosMasPesados[carpeta.ruta].nombre;
  string carpetaFormateada = "<li><span class=\"caret\">" + nombre + "</span>\n" + "<ul class=\"nested\">\n"
                                                                                   "<li>Numero de archivos: " +
                             std::to_string(carpeta.subelementos) + "</li>\n" +
                             "<li>Espacio total: " +
                             std::to_string(carpeta.peso) + " Bytes</li>\n" +
                             "<li>Espacio total %: " +
                             std::to_string(espacioTotalp) + "</li>\n" +
                             "<li>Archivo mas pesado: " +
                             masPesadoNombre + " - " + std::to_string(masPesado) + " Bytes</li>\n";
  return carpetaFormateada;
}

string manejadorHTML::armarCuerpoHTML()
{
  agregarRaiz();
  int i = 0;
  for (archivo a : elementos)
  {
    if ((esCarpeta(a.ruta)) && (a.ruta != elementos.begin()->ruta))
    {
      agregarCarpeta(a);
    }
  }

  int size = htmlSegmentado.size();
  string cuerpo = unirVectorStrings(htmlSegmentado, '\n', size);
  return cuerpo;
}

void manejadorHTML::agregarRaiz()
{
  archivo raiz = *elementos.begin();
  string ruta = raiz.ruta;
  htmlSegmentado.push_back(formatoCarpeta(raiz));
  htmlSegmentado.push_back(crearComentario(ruta));
  htmlSegmentado.push_back("</ul>\n</li>\n");
}

// Inserta el fragmento HTML de la carpeta en  la posición correcta
void manejadorHTML::agregarCarpeta(archivo a)
{
  for (int i = 0; i < htmlSegmentado.size(); i++)
  {
    string ruta = getRutaDeComentario(htmlSegmentado[i]);
    string padre = getPadre(a.ruta);
    if (ruta == padre)
    {
      string carpeta = formatoCarpeta(a);
      htmlSegmentado.insert(htmlSegmentado.begin() + i, "</ul>\n</li>\n");
      htmlSegmentado.insert(htmlSegmentado.begin() + i, crearComentario(a.ruta));
      htmlSegmentado.insert(htmlSegmentado.begin() + i, carpeta);
      break;
    }
  }
}

string manejadorHTML::crearComentario(string comentario)
{
  comentario = "<!-- " + comentario + " -->";
  return comentario;
}

// Extrae el comentario con la ruta de la carpeta
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

string cabecera = "<!DOCTYPE html>\n"
                  "<html>\n<head>\n    <meta charset=\"UTF-8\">\n"
                  "    <meta name= \"directorio.html\" content= \"Directorio\">\n"
                  "    <title>Estadisticas del Directorio</title>\n</head>\n<body>\n"
                  "    <h1>Estadisticas del directorio </h1>\n"
                  "<style>\n"
                  "ul,"
                  "#myUL\n"
                  "{\n"
                  "list-style-type:none;\n"
                  "}\n"

                  "#myUL{\n"
                  "margin: 0;\n"
                  "padding: 0;\n"
                  "}\n"

                  ".caret\n"
                  "{\n"
                  "cursor: pointer;"
                  "-webkit-user-select: none; /* Safari 3.1+ */\n"
                  "-moz-user-select: none;    /* Firefox 2+ */\n"
                  "-ms-user-select: none;     /* IE 10+ */\n"
                  "user-select: none;\n"
                  "}\n"

                  ".caret::before\n"
                  "{\n"
                  "content: \"\\25B6\";\n"
                  "color: black;\n"
                  "display: inline-block;\n"
                  "margin-right: 6px;\n"
                  "}\n"

                  ".caret-down::before\n"
                  "{\n"
                  "-ms-transform: rotate(90deg);     /* IE 9 */\n"
                  "-webkit-transform: rotate(90deg); /* Safari */\n"
                  "transform: rotate(90deg);\n"
                  "}\n"

                  ".nested\n"
                  "{\n"
                  "display: none;\n"
                  "}\n"

                  ".active\n"
                  "{\n"
                  "display: block;\n"
                  "}\n"
                  "</style>\n</head>\n<body>"
                  "\n ";

string cierre =

    "<script>\n"
    "var toggler = document.getElementsByClassName(\"caret\");\n"
    "var i;\n"

    "for (i = 0; i < toggler.length; i++)\n"
    "{\n"
    "toggler[i].addEventListener(\"click\", function() {\n"
    "this.parentElement.querySelector(\".nested\").classList.toggle(\"active\");\n"
    "this.classList.toggle(\"caret-down\");\n});\n"
    "}\n"
    "</script>\n"
    "</body>\n</html>\n";

void manejadorHTML::generarHTML()
{
  string cuerpo = armarCuerpoHTML();
  HTML = cabecera + cuerpo + cierre;
  guardarHTML("estadisticas_directorio.html", HTML);
}

void manejadorHTML::guardarHTML(string nombre, string contenido)
{
  ofstream fichero(nombre);
  fichero << contenido;
  fichero.close();
}