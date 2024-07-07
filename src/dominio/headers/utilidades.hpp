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

string getRepeatedString(char c, int i);

void levelPrint(node n);

vector<string> split(string texto, char caracter);

string joinVectorStrings(vector<string> segmentedText, char separator,
                         int partsToJoin);
node createNode(string path);
list<node> getEmptyList();

string getParent(string path);

void printDirectory(string pathToDirectory);

Tree getTreeFromPath(string pathToDirectory);

void printRawDirectory(string pathToDirectory);

bool esCarpeta(string ruta);

int getPeso(string ruta);

bool existeDirectorio(string ruta);

bool contieneSubstring(string texto, string caracteres);

#endif // UTILIDADES
