#include "interfaz.hpp"
#include "../dominio/headers/utilidades.hpp"
#include <iostream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define GREEN "\x1B[32m"

void Interfaz::pause()
{
  cout << "\nPresione enter para continuar.";
  getchar();
}

bool Interfaz::validarInput(string input)
{ // Valida entra de datos numéricas
  if (input == "")
    return false; // verdadero: solo hay números en el string dado
  for (auto i : input)
  { // falso:hay otros caracteres
    if (isalpha(i))
      return false;
  }
  return true;
}

int Interfaz::getInput(int range)
{ // Entrada de datos numérica
  string input;
  cout << GREEN << ">>: " << RESET;
  getline(std::cin, input);
  if (!validarInput(input))
    return 0;

  int inputOpcion = stoi(input);

  if ((inputOpcion) > 0 && (inputOpcion <= range))
  {
    return stoi(input);
  }

  else
    return 0;
}

string Interfaz::getText(string mensaje)
{
  string text;
  cout << "\n" + mensaje << GREEN << " >>: " << RESET;
  getline(cin, text);
  return text;
}

void Interfaz::inputIncorrecto()
{
  printf(RED "\nOpcion invalida.\n" RESET);
  pause();
}

void Interfaz::errorPersonalizado(string mensaje)
{
  cout << RED << mensaje << RESET;
  pause();
}

void Interfaz::printOpciones(vector<string> opciones, bool numeracion)
{
  for (int i = 0; i < opciones.size(); i++)
  {
    if (numeracion)
      cout << GREEN << i + 1 << ") " << RESET;
    cout << opciones[i];
    cout << endl;
  }
}

void Interfaz::printTitulo(string title)
{
  cout << " -------------- " << GREEN + title + RESET + " -------------- \n\n";
}

int Interfaz::Menu(vector<string> opciones, string titulo)
{

  int rango = opciones.size();
  int seleccion = 0;
  while (true)
  {
    printTitulo(titulo);
    printOpciones(opciones, true);
    seleccion = getInput(rango);
    if (seleccion != 0)
      break;
    else
      inputIncorrecto();
    system("cls");
  }
  return seleccion;
}

// Imprime un elemento de tipo archivo resaltando sus caracteristicas
void Interfaz::printArchivo(archivo n)
{
  string archivoFormateado = getStringRepetido(' ', n.level) + n.ruta;
  if (esCarpeta(n.ruta))
  {
    cout << GREEN;
    cout << archivoFormateado;
    cout << RESET;
    cout << " " << YELLOW << n.peso << " Bytes" << RESET;
    cout << " n = " << n.subelementos;
  }
  else
  {
    cout << archivoFormateado << YELLOW << " " << n.peso << " Bytes" << RESET;
  }
  cout << endl;
}

void Interfaz::printStringList(list<archivo> elements)
{
  for (archivo i : elements)
  {
    printArchivo(i);
  }
}

void Interfaz::printBusqueda(list<archivo> elementos)
{
  for (archivo n : elementos)
  {
    cout << GREEN << n.nombre << RESET << " --> " << n.ruta << endl;
  }
}

void Interfaz::printColorString(int numeroColor, string mensaje)
{
  string color = getColor(numeroColor);
  cout << color << mensaje << RESET;
}

string Interfaz::getColor(int numeroColor)
{
  switch (numeroColor)
  {
  case 1:
    return YELLOW;
  case 2:
    return BLUE;
  case 3:
    return RED;
  case 4:
    return GREEN;
  }
  return "";
}
