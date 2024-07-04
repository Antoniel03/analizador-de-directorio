#include <filesystem>
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

struct node {
  string name;
  string route;
  int level = 0;
};

vector<string> split(string texto, char caracter) {

  vector<string> resultado;
  string palabra = "";

  for (auto i : texto) {
    if (i != caracter)
      palabra += i;

    else if (i == caracter) {
      resultado.push_back(palabra);
      palabra = "";
    }
  }

  resultado.push_back(palabra);
  return resultado;
}

node createNode(string path) {
  vector<string> segmentedPath = split(path, '/');
  int size = segmentedPath.size();
  node n;
  n.name = segmentedPath[size - 1];
  n.route = path;
  n.level = size;
  return n;
}

list<node> getEmptyList() {
  list<node> l;
  return l;
}

string getParent(string path) {
  vector<string> segmentedPath = split(path, '/');
  int size = segmentedPath.size();
  return segmentedPath[size - 2];
}

class Tree {
private:
  map<string, list<node>> nodes;
  list<string> keys;

public:
  Tree() {}

  Tree(string root) {
    node n = createNode(root);
    nodes[root];
    keys.push_back(n.name);
  }

  void addNode(string path) {
    node n = createNode(path);
    string parent = getParent(n.route);
    if (hasFather(parent)) {
      keys.push_back(n.name);
      nodes[n.name];
      nodes[parent].push_back(n);
    }
  }

  void printTree() {
    for (auto i : keys) {
      cout << i << endl;
    }
  }

  bool hasFather(string path) {
    if (nodes.find(path) != nodes.end())
      return true;
    return false;
  }

  void printChilds(string key) {
    list<node> childs = nodes[key];
    cout << "Elements in -> " << key << endl;
    for (auto i : childs) {
      cout << i.route << endl;
    }
  }
};

void printDirectory(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    string path = entry.path();
    vector<string> segmentedPath = split(path, '/');
    int size = segmentedPath.size();
    string filename = segmentedPath[size - 1];
    cout << filename << " - " << path << endl;
  }
}

Tree getTreeFromPath(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;
  Tree t{pathToDirectory};

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    string path = entry.path();
    t.addNode(path);
  }
  return t;
}

void printRawDirectory(string pathToDirectory) {
  std::filesystem::path p = pathToDirectory;

  for (const auto &entry : std::filesystem::recursive_directory_iterator(p)) {
    cout << entry.path() << endl;
  }
}

int main() {
  Tree t = getTreeFromPath("..");
  cout << "----" << endl;
  t.printTree();
}
