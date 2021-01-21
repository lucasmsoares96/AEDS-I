#ifndef FILA_HPP_
#define FILA_HPP_

#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

template <class T>
class Fila {
 private:
  class Celula {
    friend class Fila<T>;

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
  Celula *frente, *tras;
  int tam;

 public:
  Fila();
  void enfileira(const T &x);
  void enfileira_ponteiro(T *x);
  T *desenfileira();
  int tamanho() const;
  bool vazia() const;
  void imprime() const;
  void imprime_matriz() const;
  void imprime_hash() const;
  ~Fila();
};
#endif
