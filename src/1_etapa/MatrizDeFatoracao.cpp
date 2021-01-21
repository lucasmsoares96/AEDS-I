#include "MatrizDeFatoracao.hpp"

#include "../Tokenizer.cpp"

MatrizDeFatoracao::MatrizDeFatoracao(char *delimiters, char *arquivo) {
  this->primeira_celula = new Matriz();
  this->linha_atual = this->primeira_celula;
  this->coluna_atual = this->primeira_celula;
  this->ultima_coluna = this->primeira_celula;
  this->ultima_linha = this->primeira_celula;
  this->ultima_linha->proxima_linha = NULL;
  this->ultima_coluna->proxima_coluna = NULL;

  this->celula_atual = this->primeira_celula;
  abrir_arquivos(arquivo);
  this->delimiters = delimiters;
  criar_matriz();
}

Matriz *MatrizDeFatoracao::get_primeira_celula() {
  return this->primeira_celula;
}

int MatrizDeFatoracao::get_tamanho_lista_de_produtos(){
  return lista_produtos->tamanho();
}

int MatrizDeFatoracao::get_tamanho_lista_de_usuarios(){
  return lista_usuarios->tamanho();
}

void MatrizDeFatoracao::imprimir_matriz() {
  Matriz *usuario = this->primeira_celula;
  Matriz *produto = this->primeira_celula;
  Matriz *atual = this->primeira_celula;
  cout << "      ";
  do {
    cout << " " << *produto->produto;
    produto = produto->proxima_coluna;
  } while (produto != NULL);
  do {
    cout << endl << *usuario->usuario;
    do {
      cout << "   " << atual->nota;
      atual = atual->proxima_coluna;
    } while (atual != NULL);
    usuario = usuario->proxima_linha;
    atual = usuario;
  } while (usuario != NULL);
  cout << endl;
}

void MatrizDeFatoracao::criar_matriz() {
  string linha;
  Tokenizer<char> *toks = new Tokenizer<char>();
  toks->set_delimiter(this->delimiters);
  while (*inFile >> linha) {
    toks->tokenizer(&linha[0]);
    string usuarios = toks->get_token();
    string produtos = toks->get_token();
    float nota = stof(toks->get_token());
    toks->get_token();
    novo_usuario(usuarios, produtos, nota);
  }
}

void MatrizDeFatoracao::novo_usuario(string usuario, string produto,
                                     float nota) {
  this->linha_atual = this->primeira_celula;

  if (this->linha_atual->usuario != NULL) {
    while (usuario != *this->linha_atual->usuario &&
           this->linha_atual->proxima_linha != NULL) {
      this->linha_atual = this->linha_atual->proxima_linha;
    }
    if (usuario != *this->linha_atual->usuario &&
        this->linha_atual->proxima_linha == NULL) {
      this->lista_usuarios->insere(usuario);

      string *aux = this->lista_produtos->pos_primeiro();

      this->linha_atual->proxima_linha = new Matriz();
      this->ultima_linha = this->linha_atual->proxima_linha;
      this->ultima_linha->usuario = this->lista_usuarios->get_ultimo();
      this->ultima_linha->produto = aux;
      this->ultima_linha->nota = -1;
      this->celula_atual = this->ultima_linha;

      if (aux != NULL) {
        string *prox = this->lista_produtos->proximo();
        while (prox != NULL) {
          this->ultima_linha->produto = aux;
          aux = prox;
          this->ultima_linha->proxima_coluna = new Matriz();
          this->ultima_linha->proxima_coluna->nota = -1;
          this->ultima_linha->proxima_coluna->usuario =
              this->lista_usuarios->get_ultimo();
          this->ultima_linha->proxima_coluna->produto = aux;
          this->ultima_linha = this->ultima_linha->proxima_coluna;
          this->linha_atual = this->linha_atual->proxima_coluna;
          this->linha_atual->proxima_linha = this->ultima_linha;
          prox = this->lista_produtos->proximo();
        }
      }
    } else
      this->celula_atual = this->linha_atual;
  } else {
    this->lista_usuarios->insere(usuario);

    this->ultima_linha->usuario = this->lista_usuarios->get_ultimo();
    this->celula_atual = this->ultima_linha;
  }
  novo_produto(usuario, produto, nota);
}

void MatrizDeFatoracao::novo_produto(string usuario, string produto,
                                     float nota) {
  this->coluna_atual = this->primeira_celula;
  string *aux = this->lista_usuarios->pos_primeiro();

  if (this->coluna_atual->produto != NULL) {
    while (produto != *coluna_atual->produto &&
           this->coluna_atual->proxima_coluna != NULL) {
      this->coluna_atual = this->coluna_atual->proxima_coluna;
      this->celula_atual = this->celula_atual->proxima_coluna;
    }
    if (produto != *coluna_atual->produto &&
        coluna_atual->proxima_coluna == NULL) {
      this->lista_produtos->insere(produto);

      this->coluna_atual->proxima_coluna = new Matriz();
      this->ultima_coluna = this->coluna_atual->proxima_coluna;
      this->ultima_coluna->produto = this->lista_produtos->get_ultimo();
      this->ultima_coluna->usuario = aux;
      if (usuario == *aux)
        this->ultima_coluna->nota = nota;
      else
        this->ultima_coluna->nota = -1;
      aux = this->lista_usuarios->proximo();

      if (aux != NULL) {
        while (aux != NULL) {
          this->ultima_coluna->proxima_linha = new Matriz();
          this->ultima_coluna->proxima_linha->nota = -1;
          this->ultima_coluna->proxima_linha->usuario = aux;
          this->ultima_coluna->proxima_linha->produto =
              this->lista_produtos->get_ultimo();
          this->ultima_coluna = this->ultima_coluna->proxima_linha;
          this->coluna_atual = this->coluna_atual->proxima_linha;
          this->coluna_atual->proxima_coluna = this->ultima_coluna;
          if (usuario == *aux)
            this->ultima_coluna->nota = nota;
          else
            this->ultima_coluna->nota = -1;
          aux = this->lista_usuarios->proximo();
        }
      }
    } else {
      this->celula_atual->nota = nota;
    }
  } else {
    this->lista_produtos->insere(produto);

    this->ultima_coluna->produto = this->lista_produtos->get_ultimo();
    if (aux != NULL && usuario == *aux)
      this->ultima_coluna->nota = nota;
    else
      this->ultima_coluna->nota = -1;
    this->celula_atual = this->ultima_coluna;
  }
}

void MatrizDeFatoracao::abrir_arquivos(char *arquivo) {
  this->inFile = new ifstream(arquivo);

  if (!inFile) {
    cout << "nao foi possivel abrir o arquivo de entrada da matriz" << *arquivo
         << endl;
  }
}

void MatrizDeFatoracao::fechar_arquivos() {
  ofstream outFile("matriz_de_fatoracao.txt");

  if (!outFile) {
    cout << "nao foi possivel abrir o arquivo de saida da matriz" << endl;
  }

  Matriz *usuario = this->primeira_celula;
  Matriz *produto = this->primeira_celula;
  Matriz *atual = this->primeira_celula;
  outFile << right << setw(22) << " ";
  do {
    outFile << right << setw(11) << *produto->produto;
    produto = produto->proxima_coluna;
  } while (produto != NULL);
  do {
    outFile << endl << right << setw(22) << *usuario->usuario;
    do {
      outFile << right << setw(11) << atual->nota;
      atual = atual->proxima_coluna;
    } while (atual != NULL);
    usuario = usuario->proxima_linha;
    atual = usuario;
  } while (usuario != NULL);

  outFile.close();
  this->inFile->close();
}
