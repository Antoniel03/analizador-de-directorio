#include "dominio/headers/arbol.hpp"
#include "dominio/headers/utilidades.hpp"
#include "presentacion/interfaz.hpp"
#include "datos/manejadorHTML.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::string;
using std::vector;

vector<string> opcionesMenu{"Establecer directorio.", "Salir."};

vector<string> opcionesMenu2{
    "Ver directorio completo.",
    "Ver Subcarpeta",
    "Busqueda de archivo por nombre.",
    "Busqueda de archivo por tipo.",
    "Generar HTML.",
    "Volver.",
};

void menuPrincipal(Interfaz *interfaz);

void menuDirectorio(Interfaz *i, string ruta);

void menuSubcarpeta(Interfaz *i, list<archivo> recorrido, Arbol *t);

int main()
{
  Interfaz interfaz;
  system("cls");
  menuPrincipal(&interfaz);
}

void menuPrincipal(Interfaz *i)
{
  int opt = 0;
  while (opt != 2)
  {
    opt = i->Menu(opcionesMenu, "ANALIZADOR DE DIRECTORIOS");
    if (opt == 1)
    {
      system("cls");
      string ruta = i->getText("Ingrese la ruta del directorio");
      string rutaWin = invertirFormato(ruta);
      if (existeDirectorio(ruta))
        menuDirectorio(i, rutaWin);
      else
        i->errorPersonalizado("No se ha encontrado el directorio.");
    }
    system("cls");
  }
}

void menuDirectorio(Interfaz *i, string ruta)
{
  system("cls");
  int opt = 0;
  string rutaFormateada = formatearRuta(ruta);
  Arbol directorio = getArbolDeRuta(ruta);
  while (opt != 6)
  {
    opt = i->Menu(opcionesMenu2, "DIRECTORIO: " + rutaFormateada);
    system("cls");
    switch (opt)
    {
    case 1:
    {
      list<archivo> recorrido = directorio.preorden(ruta);
      i->printStringList(recorrido);
      i->pause();
      break;
    }
    case 2:
    {
      menuSubcarpeta(i, directorio.preorden(ruta), &directorio);
      break;
    }

    case 3:
    {
      i->printTitulo("BUSQUEDA POR NOMBRE");
      string nombre = i->getText("Ingrese el nombre del archivo a buscar");
      list<archivo> resultados = directorio.busquedaPorNombre(nombre);
      list<archivo> resultadosSimilares = directorio.keySimilares(nombre);
      cout << endl;
      i->printBusqueda(resultados);
      i->printColorString(
          1, "\n-----------------------------------------------------");
      i->printColorString(1, "\n--> Resultados Similares\n\n");

      i->printBusqueda(resultadosSimilares);
      i->pause();
      break;
    }
    case 4:
    {
      i->printTitulo("BUSQUEDA POR EXTENSION");
      string nombre = i->getText("Escriba la extension");
      list<archivo> resultados = directorio.busquedaPorExtension(nombre);
      cout << endl;
      i->printBusqueda(resultados);
      i->pause();
      break;
    }
    case 5:
    {
      i->printTitulo("GENERADO DE HTML");
      list<archivo> recorrido = directorio.preorden(directorio.getRaiz());
      map<string, archivo> masPesados = directorio.getArchivosMasPesados();
      manejadorHTML html{recorrido, masPesados};
      html.generarHTML();
      cout << "Se ha generado el archivo HTML con las estadisticas del "
              "directorio."
           << endl;
      i->pause();
      break;
    }
    }
    system("cls");
  }
}

void menuSubcarpeta(Interfaz *i, list<archivo> recorrido, Arbol *t)
{
  vector<string> opcionesMenu3 = listaAVector(recorrido);
  opcionesMenu3.push_back("Volver");
  int opcion = 0;
  while (opcion != opcionesMenu3.size())
  {
    system("cls");
    opcion = i->Menu(opcionesMenu3, "VER CARPETA");

    if (opcion != opcionesMenu3.size())
    {
      system("cls");
      cout << opcionesMenu3[opcion - 1] << endl;
      list<archivo> elementosSubcarpeta = t->preorden(opcionesMenu3[opcion - 1]);
      i->printTitulo("SUBCARPETA: " + opcionesMenu3[opcion - 1]);
      i->printStringList(elementosSubcarpeta);
      i->pause();
    }
    else
      break;
  }
}
