#ifndef __LRU_HPP
#define __LRU_HPP

#include <iostream>
#include <string>

#include "../TAD/tad.hpp"
#include "../HASH/TabelaHash.hpp"
#include "../estruturas.hpp"

class LRU {
 private:
  Fila<Matriz>* melhores_produtos_ordenados = new Fila<Matriz>();
  Fila<Produto>* usuario_entrada = new Fila<Produto>();
  Fila<Produto>* novos_produtos = new Fila<Produto>();
  Fila<Produto>* produtos_encontrados = new Fila<Produto>();
  TabelaHash *tabelaHash;

 public:
  LRU(Fila<Matriz>* melhores_produtos_ordenados,
      TabelaHash *tabelaHash, Fila<Produto> *usuario_entrada);

  void update_cache(Fila<Matriz>* melhores_produtos_ordenados,
                       TabelaHash* tabelaHash,
                       Fila<Produto>* usuario_entrada);

  Fila<Produto>* consulta_cache(Fila<Produto>* usuario_entrada);
  void imprimir();
  Matriz** recomendar();


  Matriz* getMax(Matriz** array, int n);
  void countingSort(Matriz** array, int size, int place);
  void radixsort(Matriz** array, int size);
  void printArray(Matriz** array, int size);
};

#endif
