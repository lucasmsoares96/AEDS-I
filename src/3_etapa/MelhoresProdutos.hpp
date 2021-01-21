#ifndef __MELHORESPRODUTOS_HPP
#define __MELHORESPRODUTOS_HPP

#include <iostream>
#include <string>
#include <iomanip>

#include "../TAD/tad.hpp"
#include "../estruturas.hpp"

class MelhoresProdutos {
 private:
  Lista<Matriz>* melhores_produtos = new Lista<Matriz>();
  Fila<Matriz>* melhores_produtos_ordenados = new Fila<Matriz>();
  Produto** vetor_usuario_entrada;
  Matriz** vetor_melhores_produtos;
  int tamanho_melhores_produtos;

  void encontrar_melhores_produtos(Pilha<Matriz>* pilha_ordenada,
                                   Fila<Produto>* usuario_entrada);
  void ordenar_melhores_produtos();

  Matriz* getMax(Matriz** array, int n);
  void countingSort(Matriz** array, int size, int place);
  void radixsort(Matriz** array, int size);
  void printArray(Matriz** array, int size);

 public:
  MelhoresProdutos(Pilha<Matriz>* pilha_ordenada,
                   Fila<Produto>* usuario_entrada);
  Fila<Matriz>* get_fila_melhores_produtos();
};

#endif
