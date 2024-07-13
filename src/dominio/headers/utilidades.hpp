#include "../../estructuras/nodo.hpp"
#include "arbol.hpp"
#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#ifndef UTILIDADES
#define UTILIDADES

string getStringRepetido(char c, int i);

void levelPrint(archivo n);

vector<string> split(string texto, char caracter);

string unirVectorStrings(vector<string> segmentedText, char separator,
                         int partsToJoin);
archivo crearNodoArchivo(string path);

list<archivo> getListaVacia();

string getPadre(string path);

void printDirectorio(string pathToDirectory);

Tree getArbolDeRuta(string pathToDirectory);

void printRawDirectory(string pathToDirectory);

bool esCarpeta(string ruta);

int getPeso(string ruta);

bool existeDirectorio(string ruta);

bool contieneSubstring(string texto, string caracteres);

string formatearRuta(string ruta);

string getNombreArchivo(string ruta);

string invertirFormato(string ruta);

bool esPadre(string padre, string hijo);

float calcularEspacioTotal(int raiz, int carpeta);

#endif // UTILIDADES
