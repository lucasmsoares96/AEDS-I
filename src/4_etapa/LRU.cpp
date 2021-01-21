#include "LRU.hpp"

#include <string>

LRU::LRU(Fila<Matriz>* melhores_produtos_ordenados, TabelaHash* tabelaHash,
         Fila<Produto>* usuario_entrada) {
  update_cache(melhores_produtos_ordenados, tabelaHash, usuario_entrada);
}

Matriz** LRU::recomendar() {
  Produto* produto1 = this->novos_produtos->desenfileira();
  Fila<Matriz>* cache1 = this->tabelaHash->Find(stoi(produto1->nome))
                             ->melhores_produtos_ordenados;
  Produto* produto2 = this->produtos_encontrados->desenfileira();
  Fila<Matriz>* cache2 = this->tabelaHash->Find(stoi(produto2->nome))
                             ->melhores_produtos_ordenados;

  int n = cache1->tamanho();
  int m = cache2->tamanho();

  Matriz** array = new Matriz*[n + m];
  Matriz* aux1 = cache1->desenfileira();
  Matriz* aux2 = cache2->desenfileira();

  int i = 0;
  while (aux1 != NULL) {
    array[i] = aux1;
    aux1 = cache1->desenfileira();
    i++;
  }
  while (aux2 != NULL) {
    array[i] = aux2;
    aux2 = cache2->desenfileira();
    i++;
  }
  radixsort(array, n + m);
  printArray(array, n + m);
  return array;
}

Matriz* LRU::getMax(Matriz** array, int n) {
  Matriz* max = array[0];
  for (int i = 1; i < n; i++) {
    if (array[i]->nota > max->nota) max = array[i];
  }
  return max;
}

void LRU::countingSort(Matriz** array, int size, int place) {
  const int max = 10;
  Matriz* output[size];
  int count[max];

  for (int i = 0; i < max; ++i) {
    count[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    count[(int)(array[i]->nota / place) % 10]++;
  }

  for (int i = 1; i < max; i++) {
    count[i] += count[i - 1];
  }

  for (int i = size - 1; i >= 0; i--) {
    output[count[(int)(array[i]->nota / place) % 10] - 1] = array[i];
    count[(int)(array[i]->nota / place) % 10]--;
  }

  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }
}

void LRU::radixsort(Matriz** array, int size) {
  Matriz* max = getMax(array, size);

  for (int place = 1; max->nota / place > 0; place *= 10) {
    countingSort(array, size, place);
  }
}

void LRU::printArray(Matriz** array, int size) {
  int i;
  for (i = 0; i < size; i++) {
    cout << "Produto:  " << left << setw(5) << *array[i]->produto << "\t";
    cout << "Media ponderada dos ratings:  " << left << setw(9)
         << array[i]->nota << endl;
  }
  cout << endl;
}

void LRU::update_cache(Fila<Matriz>* melhores_produtos_ordenados,
                       TabelaHash* tabelaHash,
                       Fila<Produto>* usuario_entrada) {
  this->melhores_produtos_ordenados = melhores_produtos_ordenados;
  this->tabelaHash = tabelaHash;
  this->usuario_entrada = usuario_entrada;

  Cache* recomendados;
  Matriz* aux_produto;
  Fila<Matriz>* aux_fila_produto;

  int n = this->usuario_entrada->tamanho();
  int m = this->melhores_produtos_ordenados->tamanho();
  for (int i = 0; i < n; i++) {
    recomendados = new Cache();
    aux_fila_produto = new Fila<Matriz>();
    recomendados->cont = 0;
    for (int j = 0; j < m; j++) {
      aux_produto = this->melhores_produtos_ordenados->desenfileira();
      this->melhores_produtos_ordenados->enfileira(*aux_produto);
      aux_fila_produto->enfileira(*aux_produto);
    }
    recomendados->melhores_produtos_ordenados = aux_fila_produto;
    string nome = this->usuario_entrada->desenfileira()->nome;
    recomendados->key = nome;
    this->tabelaHash->Insert(stoi(nome), recomendados);
  }
}

void LRU::imprimir() {
  this->tabelaHash->Imprime();
  cout << "\n";
}

Fila<Produto>* LRU::consulta_cache(Fila<Produto>* usuario_entrada) {

  Produto* produto;
  Cache* cache;

  int n = usuario_entrada->tamanho();
  for (int i = 0; i < n; i++) {
    produto = usuario_entrada->desenfileira();

    cache = this->tabelaHash->Find(stoi(produto->nome));
    if (cache != NULL) {
      cout << "Encontrado: " << cache->key << endl;
      this->produtos_encontrados->enfileira_ponteiro(produto);

    } else {
      this->novos_produtos->enfileira_ponteiro(produto);
    }
  }
  cout << "\n";

  Fila<Produto>* aux = new Fila<Produto>();
  n = this->novos_produtos->tamanho();

  for (int i = 0; i < n; i++) {
    produto = this->novos_produtos->desenfileira();
    this->usuario_entrada->enfileira(*produto);
    this->novos_produtos->enfileira(*produto);
  }
  return this->usuario_entrada;
}
