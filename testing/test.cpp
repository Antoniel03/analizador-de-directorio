#include <filesystem>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

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

int main() { printDirectory(".."); }
