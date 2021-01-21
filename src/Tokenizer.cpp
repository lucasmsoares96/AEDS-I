#include "Tokenizer.hpp"

template <typename T>
Tokenizer<T>::Tokenizer() {
  tokens = NULL;
  delimiter = NULL;
}

template <typename T>
Tokenizer<T>::~Tokenizer() {
  delete tokens;
  delete delimiter;
}

template <typename T>
void Tokenizer<T>::set_delimiter(char *d) {
  this->delimiter = d;
}

template <typename T>
void Tokenizer<T>::tokenizer(char *line) {
  tokens = strtok(line, this->delimiter);
}

template <typename T>
T *Tokenizer<T>::get_token() {
  //	T v = stod(tokens, &sz);
  T *aux = this->tokens;
  tokens = strtok(NULL, delimiter);
  return aux;
}

