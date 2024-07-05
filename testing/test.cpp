#include "../src/dominio/headers/arbol.hpp"
#include "../src/dominio/headers/utilidades.hpp"
#include <iostream>
#include <list>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::string;
using std::vector;

int main() {
  Tree t = getTreeFromPath("..");
  /*t.printKeys();*/

  list<string> test = preorder(t.getAddressToNode(".."), &t);
  printStringList(test);

  cout << "----" << endl;
  /*t.printKeys();*/
  /*t.printChilds("../src");*/
}
