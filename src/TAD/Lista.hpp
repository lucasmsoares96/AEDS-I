#ifndef LISTA_H_
#define LISTA_H_

#include <iostream>

using namespace std;

template <class T> class Lista {
private:
  class Celula {
    friend class Lista<T>;

  private:
    T *item;
    Celula *prox;
    Celula() {
      item = 0;
      prox = 0;
    }
    ~Celula() {
      if (item != 0)
        delete item;
    }
  };
  Celula *primeiro, *ultimo, *pos;
  int tam;

public:
  Lista();
  T *pesquisa(const T &chave) const;
  T *pesquisa_produto(string chave) const;
  void insere(const T &x);
  void inserePrimeiro(T &item);
  T *retira(const T &chave);
  T *retiraPrimeiro();
  T *_primeiro();
  T *proximo();
  T *pos_primeiro();
  T *get_ultimo();
  int tamanho();
  bool vazia() const;
  void imprime() const;
  void imprime_hash() const;
  ~Lista();
};
#endif
