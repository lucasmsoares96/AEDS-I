#ifndef __ESTRUTURAS_HPP
#define __ESTRUTURAS_HPP

#include <string>
#include "TAD/tad.hpp"

using namespace std;

typedef struct Matriz {
  string *usuario;
  string *produto;
  float nota;
  Matriz *proxima_linha, *proxima_coluna;
} Matriz;

typedef struct Cache{
  string key;
  Fila<Matriz>* melhores_produtos_ordenados;
  int cont;
}Cache;

typedef struct Produto {
  string nome;
  float nota;
} Produto;

#endif
