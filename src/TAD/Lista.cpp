#include "Lista.hpp"

#include <iomanip>

template <class T>
Lista<T>::Lista() {
  this->primeiro = new Celula();
  this->pos = this->primeiro;
  this->ultimo = this->primeiro;
  this->primeiro->prox = 0;
  this->tam = 0;
}

template <class T>
void Lista<T>::insere(const T &x) {
  this->ultimo->prox = new Celula();
  this->ultimo = this->ultimo->prox;
  this->ultimo->item = new T(x);
  this->ultimo->prox = 0;
  (this->tam)++;
}

template <class T>
void Lista<T>::inserePrimeiro(T &item) {
  Celula *aux = this->primeiro->prox;
  this->primeiro->prox = new Celula();
  this->primeiro->prox->item = new T(item);
  this->primeiro->prox->prox = aux;
  (this->tam)++;
}

template <class T>
T *Lista<T>::pesquisa(const T &chave) const {
  if (this->vazia()) return 0;
  Celula *aux = this->primeiro;
  while (aux->prox != 0) {
    if (*(aux->prox->item) == chave) return aux->prox->item;
    aux = aux->prox;
  }
  return 0;
}

template <class T>
T *Lista<T>::pesquisa_produto(string chave) const {
  if (this->vazia()) return 0;
  Celula *aux = this->primeiro;
  while (aux->prox != 0) {
    if (*(aux->prox->item->produto) == chave) return aux->prox->item;
    aux = aux->prox;
  }
  return 0;
}

template <class T>
T *Lista<T>::retira(const T &chave) {
  if (this->vazia()) {
    cout << "lista vazia" << endl;
  }
  Celula *aux = this->primeiro;
  while (aux->prox != 0 && *(aux->prox->item) != chave) aux = aux->prox;
  if (aux->prox == 0) return 0;
  Celula *q = aux->prox;
  T *item = q->item;
  aux->prox = q->prox;
  q->item = 0;
  if (aux->prox == 0) this->ultimo = aux;
  (this->tam)--;
  delete q;
  return item;
}

template <class T>
T *Lista<T>::retiraPrimeiro() {
  if (this->vazia()) {
    cout << "lista vazia" << endl;
  }
  Celula *aux = this->primeiro;
  Celula *q = aux->prox;
  T *item = q->item;
  aux->prox = q->prox;
  q->item = 0;
  if (aux->prox == 0) this->ultimo = aux;
  delete q;
  return item;
}

template <class T>
T *Lista<T>::_primeiro() {
  this->pos = this->primeiro;
  return this->proximo();
}

template <class T>
T *Lista<T>::proximo() {
  if (this->pos == NULL || this->pos->prox == NULL)
    return NULL;
  else
    this->pos = this->pos->prox;
  return this->pos->item;
}

template <class T>
T *Lista<T>::pos_primeiro() {
  this->pos = this->primeiro;
  return this->proximo();
}

template <class T>
T *Lista<T>::get_ultimo() {
  return this->ultimo->item;
}

template <class T>
int Lista<T>::tamanho() {
  return this->tam;
}

template <class T>
bool Lista<T>::vazia() const {
  return (this->primeiro == this->ultimo);
}

template <class T>
void Lista<T>::imprime() const {
  Celula *aux = this->primeiro->prox;
  while (aux != 0) {
    cout << "Produto:  " << left << setw(5) << *(aux->item->produto)
         << "\t";
    cout << "Media ponderada dos ratings:  " << left << setw(9)
         << (aux->item->nota) << endl;
    aux = aux->prox;
  }
}

template <class T>
void Lista<T>::imprime_hash() const {
  Celula *aux = this->primeiro->prox;
  while (aux != 0) {
    cout << *(aux->item) << endl;
    aux = aux->prox;
  }
}

template <class T>
Lista<T>::~Lista() {
  Celula *aux = this->primeiro;
  while (aux != 0) {
    this->primeiro = this->primeiro->prox;
    delete aux;
    aux = this->primeiro;
  }
}
