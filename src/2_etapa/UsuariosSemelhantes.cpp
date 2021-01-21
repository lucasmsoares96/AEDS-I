#include "UsuariosSemelhantes.hpp"

#include "../Tokenizer.cpp"

UsuariosSemelhantes::UsuariosSemelhantes(char *arquivo,
                                         Matriz *primeira_celula,
                                         char *delimiters) {
  this->primeira_celula = primeira_celula;
  this->delimiters = delimiters;
  abrir_arquivos(arquivo);
  criar_fila_de_produtos();
}

void UsuariosSemelhantes::update_usuario(Fila<Produto> *novos_produtos){
  this->usuario_entrada = novos_produtos;
}

Fila<Produto> *UsuariosSemelhantes::get_usuario_entrada() {
  Fila<Produto> *usuario_entrada = new Fila<Produto>();
  Produto *produto = new Produto();
  int n = this->usuario_entrada->tamanho();

  for (int i = 0; i < n; i++) {
    produto = this->usuario_entrada->desenfileira();
    this->usuario_entrada->enfileira(*produto);
    usuario_entrada->enfileira(*produto);
  }

  return usuario_entrada;
}

Pilha<Matriz> *UsuariosSemelhantes::get_pilha_usuarios() {
  return this->usuarios_semelhantes;
}

void UsuariosSemelhantes::abrir_arquivos(char *arquivo) {
  this->inFile = new ifstream(arquivo);
  if (!inFile) {
    cout << "nao foi possivel abrir o arquivo do usuario" << *arquivo
         << endl;
  }
}

void UsuariosSemelhantes::criar_fila_de_produtos() {
  string linha;
  Tokenizer<char> *toks = new Tokenizer<char>();
  toks->set_delimiter(this->delimiters);
  while (*(this->inFile) >> linha) {
    toks->tokenizer(&linha[0]);
    Produto produto;
    produto.nome = toks->get_token();
    produto.nota = stof(toks->get_token());
    this->usuario_entrada->enfileira(produto);
  }

  this->usuario_entrada->imprime();
  cout << "\n";
}

void UsuariosSemelhantes::encontrar_usuarios_semelhantes() {
  Matriz *produto_atual = this->primeira_celula;
  Matriz *usuario_atual = this->primeira_celula;
  Produto *produto;
  Fila<Produto> *aux_usuario = new Fila<Produto>();
  produto = this->usuario_entrada->desenfileira();
  aux_usuario->enfileira(*produto);
  while (produto != NULL) {
    while (produto != NULL && produto_atual != NULL &&
           *(produto_atual->produto) != produto->nome) {
      produto_atual = produto_atual->proxima_coluna;
    }
    if (produto_atual != NULL) {
      while (usuario_atual != NULL) {
        if (produto_atual->nota != -1) {
          Matriz *aux_semelhante = new Matriz();
          Pilha<Matriz> *pilha_aux_semelhante = new Pilha<Matriz>();
          aux_semelhante = this->usuarios_semelhantes->desempilha();
          float *aux_peso = new float();
          Pilha<float> *pilha_aux_peso = new Pilha<float>();
          aux_peso = this->pesos->desempilha();
          while (aux_semelhante != NULL) {
            pilha_aux_semelhante->empilha_ponteiro(aux_semelhante);
            if (aux_semelhante->usuario == produto_atual->usuario &&
                produto_atual->nota != -1) {
              float soma = produto_atual->nota + *aux_peso;
              pilha_aux_peso->empilha(soma);
              break;
            } else {
              pilha_aux_peso->empilha_ponteiro(aux_peso);
            }
            aux_semelhante = this->usuarios_semelhantes->desempilha();
            aux_peso = this->pesos->desempilha();
          }
          Matriz *aux_semelhante2 = new Matriz();
          aux_semelhante2 = pilha_aux_semelhante->desempilha();
          float *aux_peso2 = new float();
          aux_peso2 = pilha_aux_peso->desempilha();
          if (aux_semelhante == NULL) {  // não é repetido
            this->usuarios_semelhantes->empilha_ponteiro(usuario_atual);
            this->pesos->empilha(produto_atual->nota);
            while (aux_semelhante2 != NULL) {
              this->usuarios_semelhantes->empilha_ponteiro(
                  aux_semelhante2);
              aux_semelhante2 = pilha_aux_semelhante->desempilha();
              this->pesos->empilha_ponteiro(aux_peso2);
              aux_peso2 = pilha_aux_peso->desempilha();
            }
          } else {
            while (aux_semelhante2 != NULL) {
              this->usuarios_semelhantes->empilha_ponteiro(
                  aux_semelhante2);
              aux_semelhante2 = pilha_aux_semelhante->desempilha();
              this->pesos->empilha_ponteiro(aux_peso2);
              aux_peso2 = pilha_aux_peso->desempilha();
            }
          }
        }
        usuario_atual = usuario_atual->proxima_linha;
        produto_atual = produto_atual->proxima_linha;
      }
    }
    produto = this->usuario_entrada->desenfileira();
    if (produto != NULL) aux_usuario->enfileira(*produto);
    produto_atual = primeira_celula;
    usuario_atual = primeira_celula;
  }
  this->usuario_entrada = aux_usuario;

  cout << "\n\n >>>> Usuarios semelhantes com seus respectivos \n"
          "pesos(desordenados)\n"
       << endl;

  imprimir_usuarios_pesos();

  ordenar();

  cout << "\n\n >>>> Usuarios semelhantes com seus respectivos "
          "pesos(ordenados\n"
          "pelo metodo da bolha)\n"
       << endl;

  imprimir_usuarios_pesos();
  cout << endl;
}

void UsuariosSemelhantes::imprimir_usuarios_pesos() {
  Pilha<Matriz> *usuarios_semelhantes = new Pilha<Matriz>();
  Pilha<float> *pesos = new Pilha<float>();
  Matriz *aux_usuarios_semelhantes;
  float *aux_pesos;

  aux_usuarios_semelhantes = this->usuarios_semelhantes->desempilha();
  aux_pesos = this->pesos->desempilha();

  while (aux_pesos != NULL) {
    cout << "Nome usuario:  " << *aux_usuarios_semelhantes->usuario
         << "\tPeso respectivo: " << *aux_pesos << endl;

    usuarios_semelhantes->empilha_ponteiro(aux_usuarios_semelhantes);
    pesos->empilha_ponteiro(aux_pesos);

    aux_usuarios_semelhantes = this->usuarios_semelhantes->desempilha();
    aux_pesos = this->pesos->desempilha();
  }

  aux_usuarios_semelhantes = usuarios_semelhantes->desempilha();
  aux_pesos = pesos->desempilha();

  while (aux_pesos != NULL) {
    this->usuarios_semelhantes->empilha_ponteiro(aux_usuarios_semelhantes);
    this->pesos->empilha_ponteiro(aux_pesos);
    aux_usuarios_semelhantes = usuarios_semelhantes->desempilha();
    aux_pesos = pesos->desempilha();
  }
}

void UsuariosSemelhantes::ordenar() {
  Matriz **vetor_usuarios;
  float **vetor_peso;
  int tam = this->pesos->tamanho();

  Pilha<Matriz> *usuarios_semelhantes = new Pilha<Matriz>();
  Pilha<float> *pesos = new Pilha<float>();

  vetor_usuarios = (Matriz **)malloc(
      this->usuarios_semelhantes->tamanho() * sizeof(Matriz **));
  vetor_peso = (float **)malloc(this->pesos->tamanho() * sizeof(float **));
  for (int i = 0; i < tam; i++) {
    vetor_peso[i] = this->pesos->desempilha();
    vetor_usuarios[i] = this->usuarios_semelhantes->desempilha();
  }

  for (int j = 1; j < tam; j++) {
    for (int i = 0; i < tam - 1; i++) {
      if (*vetor_peso[i] > *vetor_peso[i + 1]) {
        float *aux_float = vetor_peso[i];
        vetor_peso[i] = vetor_peso[i + 1];
        vetor_peso[i + 1] = aux_float;
        Matriz *aux_matriz = vetor_usuarios[i];
        vetor_usuarios[i] = vetor_usuarios[i + 1];
        vetor_usuarios[i + 1] = aux_matriz;
      }
    }
  }

  for (int i = 0; i < tam; i++) {
    usuarios_semelhantes->empilha_ponteiro(vetor_usuarios[i]);
    pesos->empilha_ponteiro(vetor_peso[i]);
  }

  this->usuarios_semelhantes = usuarios_semelhantes;
  this->pesos = pesos;
}

void UsuariosSemelhantes::fechar_arquivos() { this->inFile->close(); }
