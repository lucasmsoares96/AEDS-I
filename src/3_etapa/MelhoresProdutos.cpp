#include "MelhoresProdutos.hpp"

MelhoresProdutos::MelhoresProdutos(Pilha<Matriz>* pilha_ordenada,
                                   Fila<Produto>* usuario_entrada) {
  encontrar_melhores_produtos(pilha_ordenada, usuario_entrada);
  ordenar_melhores_produtos();
}

Fila<Matriz>* MelhoresProdutos::get_fila_melhores_produtos() {
  return this->melhores_produtos_ordenados;
}

Matriz* MelhoresProdutos::getMax(Matriz** array, int n) {
  Matriz* max = array[0];
  for (int i = 1; i < n; i++) {
    if (array[i]->nota > max->nota) max = array[i];
  }
  return max;
}

void MelhoresProdutos::countingSort(Matriz** array, int size, int place) {
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

void MelhoresProdutos::radixsort(Matriz** array, int size) {
  Matriz* max = getMax(array, size);

  for (int place = 1; max->nota / place > 0; place *= 10) {
    countingSort(array, size, place);
  }
}

void MelhoresProdutos::printArray(Matriz** array, int size) {
  int i;
  for (i = 0; i < size; i++) {
    cout << "Produto:  " << left << setw(5) << *array[i]->produto << "\t";
    cout << "Media ponderada dos ratings:  " << left << setw(9)
         << array[i]->nota << endl;
  }
  cout << endl;
}

void MelhoresProdutos::ordenar_melhores_produtos() {
  Matriz** array = new Matriz*[this->tamanho_melhores_produtos];
  int n = this->tamanho_melhores_produtos;
  for (int i = 0; i < n; i++) {
    array[i] = this->vetor_melhores_produtos[i];
  }
  radixsort(array, n);
  cout << "\n\n >>>> Lista dos melhores produtos ordenada pelo RadixSort: "
          "\n\n";
  printArray(array, n);

  for (int i = n - 1; i >= n - 10; i--) {
    this->melhores_produtos_ordenados->enfileira_ponteiro(array[i]);
  }
}

void MelhoresProdutos::encontrar_melhores_produtos(
    Pilha<Matriz>* pilha_ordenada, Fila<Produto>* usuario_entrada) {
  int tamanho_usuario_entrada = usuario_entrada->tamanho();
  int tamanho_pilha_ordenada = pilha_ordenada->tamanho();

  int cont = 0;
  this->vetor_usuario_entrada = new Produto*[tamanho_usuario_entrada];

  Pilha<float>* prioridade = new Pilha<float>();
  for (int i = 0; i < tamanho_pilha_ordenada; i++) {
    prioridade->empilha(i + 1);
  }

  for (int i = 0; i < tamanho_usuario_entrada; i++) {
    this->vetor_usuario_entrada[i] = usuario_entrada->desenfileira();
  }
  Matriz* usuario_atual = pilha_ordenada->desempilha();
  float* prioridade_atual = prioridade->desempilha();

  while (usuario_atual != NULL) {
    while (usuario_atual != NULL) {
      for (int i = 0; i < tamanho_usuario_entrada; i++) {
        if (this->vetor_usuario_entrada[i]->nome !=
                *usuario_atual->produto &&
            usuario_atual->nota != -1) {
          cont++;
        } else {
          break;
        }
      }
      if (cont == tamanho_usuario_entrada) {
        Matriz* possivel_sugestao =
            this->melhores_produtos->pesquisa_produto(
                *usuario_atual->produto);
        if (possivel_sugestao == 0) {
          Matriz* formula = new Matriz(*usuario_atual);

          formula->nota =
              formula->nota * (*prioridade_atual / tamanho_pilha_ordenada);
          this->melhores_produtos->insere(*formula);
        } else {
          possivel_sugestao->nota =
              possivel_sugestao->nota + usuario_atual->nota;
        }
      }
      cont = 0;
      usuario_atual = usuario_atual->proxima_coluna;
    }
    usuario_atual = pilha_ordenada->desempilha();
    prioridade_atual = prioridade->desempilha();
  }

  cout << "\n\n >>>> Lista concatenada dos melhores produtos (media \n"
          "ponderada do ratings com a posicao do usuario na pilha dos \n"
          "usuarios mais semelhantes) nao avaliados pelo usuario de \n"
          "entrada\n"
       << endl;
  this->melhores_produtos->imprime();

  this->tamanho_melhores_produtos = this->melhores_produtos->tamanho();
  this->vetor_melhores_produtos = new Matriz*[tamanho_melhores_produtos];

  for (int i = 0; i < tamanho_melhores_produtos; i++) {
    this->vetor_melhores_produtos[i] = melhores_produtos->retiraPrimeiro();
  }
}
