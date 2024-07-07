#include "../dominio/headers/arbol.hpp"
#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

#ifndef INTERFAZ
#define INTERFAZ

class Interfaz {
public:
  void printOpciones(vector<string> opciones, bool numeracion);
  int getInput(int range);
  bool validarInput(string input);
  string getText(string mensaje);
  void printTitulo(string title);
  void pause();
  void inputIncorrecto();
  int Menu(vector<string> opciones, string titulo);
  void errorPersonalizado(string mensaje);
  void printStringList(list<string> elements);
  void auxiliarPreorden(node *raiz, list<string> &ans, Tree t);
  list<string> preorden(node *root, Tree *t);
  void printArchivo(node n);
  void printBusqueda(list<node> elementos);
  void printSeparador();
  void printColorString(int numeroColor, string mensaje);
  string getColor(int numeroColor);
};

#endif // !INTERFAZ
