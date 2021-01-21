#include "Fila.hpp"

template <class T>
Fila<T>::Fila() {
  this->frente = new Celula();
  this->tras = this->frente;
  this->frente->prox = 0;
  this->tam = 0;
}

template <class T>
void Fila<T>::enfileira_ponteiro(T *x) {
  this->tras->prox = new Celula();
  this->tras = this->tras->prox;
  this->tras->item = x;
  this->tras->prox = 0;
  (this->tam)++;
}

template <class T>
void Fila<T>::enfileira(const T &x) {
  this->tras->prox = new Celula();
  this->tras = this->tras->prox;
  this->tras->item = new T(x);
  this->tras->prox = 0;
  (this->tam)++;
}

template <class T>
T *Fila<T>::desenfileira() {
  if (this->vazia()) {
    return NULL;
  } else {
    Celula *aux = this->frente;
    this->frente = this->frente->prox;
    T *item = this->frente->item;
    this->frente->item = 0;
    (this->tam)--;
    delete aux;
    return item;
  }
}

template <class T>
int Fila<T>::tamanho() const {
  return this->tam;
}

template <class T>
bool Fila<T>::vazia() const {
  return (this->frente == this->tras);
}

template <class T>
void Fila<T>::imprime_matriz() const {
  Celula *aux = this->frente->prox;
  while (aux != 0) {
    cout << "produto: " << left << setw(5) << *aux->item->produto;
    cout << " nota: " << left << setw(5) << aux->item->nota << endl;
    aux = aux->prox;
  }
}

template <class T>
void Fila<T>::imprime() const {
  Celula *aux = this->frente->prox;
  while (aux != 0) {
    cout << "produto: " << left << setw(5) << aux->item->nome;
    cout << " nota: " << left << setw(5) << aux->item->nota << endl;
    aux = aux->prox;
  }
}

template <class T>
Fila<T>::~Fila() {
  Celula *aux = this->frente;
  while (aux != 0) {
    this->frente = this->frente->prox;
    delete aux;
    aux = this->frente;
  }
}
