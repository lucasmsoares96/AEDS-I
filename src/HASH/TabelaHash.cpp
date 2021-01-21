#include "TabelaHash.hpp"

TabelaHash::TabelaHash() {}

Cache *TabelaHash::Find(int key) {
  map<int, Cache *>::iterator it;
  Cache *encontrado;
  it = this->h->hash.find(key);
  if (it != this->h->hash.end()) {
    it->second->cont++;
    encontrado = it->second;
    return encontrado;
  } else {
    return NULL;
  }
}

void TabelaHash::Remove_LRU() {
  map<int, Cache *>::iterator it;
  int lru;
  int menor = 99999;

  for (it = this->h->hash.begin(); it != this->h->hash.end(); ++it) {
    if (it->second->cont < menor) {
      menor = it->second->cont;
      lru = stoi(it->second->key);
    }
  }
  this->h->hash.erase(lru);
  cout << "Removendo: \t" << lru << endl;
}

void TabelaHash::Imprime() {
  map<int, Cache *>::iterator it;
  for (it = this->h->hash.begin(); it != this->h->hash.end(); ++it) {
    cout << "Chave:\t" << it->first << endl;
    cout << "Contador:\t" << it->second->cont << endl;
    it->second->melhores_produtos_ordenados->imprime_matriz();
    cout << endl;
  }
}

void TabelaHash::Insert(int key, Cache *value) {
  map<int, Cache *>::iterator it;
  it = this->h->hash.find(key);
  if (it != this->h->hash.end()) {
    this->h->hash[key] = value;
  } else {
    if (this->h->hash.size() > 75) {
      Remove_LRU();
      this->h->hash[key] = value;
    } else {
      this->h->hash[key] = value;
    }
  }
}
