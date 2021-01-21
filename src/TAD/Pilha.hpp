#ifndef PILHA_HPP_
#define PILHA_HPP_

#include <stdexcept>
#include <iostream>

using namespace std;

template <class T>
class Pilha {
 private:
  class Celula {
    friend class Pilha<T>;

   private:
    T *item;
    Celula *prox;
    Celula() {
      item = 0;
      prox = 0;
    }
    ~Celula() {
      if (item != 0) delete item;
    }
  };
  Celula *topo;
  int tam;

 public:
  Pilha();
  ~Pilha();
  void empilha_ponteiro(T *x);
  void empilha(const T &x);
  T *desempilha();
  bool vazia() const;
  int tamanho() const;
  void imprime();
  void imprime_ponteiro();
};
#endif
