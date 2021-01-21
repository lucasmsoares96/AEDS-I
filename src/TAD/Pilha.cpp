#include "Pilha.hpp"

template <class T>
Pilha<T>::Pilha() {
  this->topo = 0;
  this->tam = 0;
}

template <class T>
Pilha<T>::~Pilha() {
  Celula *aux = topo;
  while (aux != 0) {
    topo = topo->prox;
    delete aux;
    aux = topo;
  }
}

template <class T>
void Pilha<T>::empilha_ponteiro(T *x) {
  Celula *aux = this->topo;
  this->topo = new Celula();
  this->topo->item = x;
  this->topo->prox = aux;
  (this->tam)++;
}

template <class T>
void Pilha<T>::empilha(const T &x) {
  Celula *aux = this->topo;
  this->topo = new Celula();
  this->topo->item = new T(x);
  this->topo->prox = aux;
  (this->tam)++;
}

template <class T>
T *Pilha<T>::desempilha() {
  if (this->vazia()) {
    return NULL;
  } else {
    Celula *aux = this->topo;
    T *item = this->topo->item;
    this->topo->item = 0;
    this->topo = this->topo->prox;
    (this->tam)--;
    delete aux;
    return item;
  }
}

template <class T>
bool Pilha<T>::vazia() const {
  return (this->topo == 0);
}

template <class T>
int Pilha<T>::tamanho() const {
  return this->tam;
}

template <class T>
void Pilha<T>::imprime_ponteiro() {
  Celula *aux = this->topo;
  while (aux != 0) {
    cout << *(aux->item->usuario) << endl;
    aux = aux->prox;
  }
}

template <class T>
void Pilha<T>::imprime() {
  Celula *aux = this->topo;
  while (aux != 0) {
    cout << *(aux->item) << endl;
    aux = aux->prox;
  }
}
