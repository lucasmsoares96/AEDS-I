#ifndef __TABELAHASH_HPP
#define __TABELAHASH_HPP

#include <iostream>
#include <map>

#include "../estruturas.hpp"

using namespace std;


class TabelaHash {
 private:
  typedef struct HashTable {
    map<int, Cache*> hash;
  } HashTable;

  HashTable *h = new HashTable();

 public:
  TabelaHash();
  void Imprime();
  void Insert(int key, Cache *value);
  void Remove_LRU();
  Cache *Find(int key);
};

#endif
