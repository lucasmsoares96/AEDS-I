#ifndef __MATRIZDEFATORACAO_HPP
#define __MATRIZDEFATORACAO_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "../TAD/tad.hpp"
#include "../estruturas.hpp"

using namespace std;

class MatrizDeFatoracao {
 private:
  Lista<string> *lista_usuarios = new Lista<string>();
  Lista<string> *lista_produtos = new Lista<string>();

  Matriz *primeira_celula, *celula_atual, *ultima_linha,
      *linha_atual, *ultima_coluna, *coluna_atual;

  char *delimiters;
  ifstream *inFile;

  void abrir_arquivos(char *arquivo);
  void criar_matriz();
  void novo_usuario(string usuario, string produto, float nota);
  void novo_produto(string usuario, string produto, float nota);
  void imprimir_matriz();

 public:
  MatrizDeFatoracao(char *delimiters, char *arquivo);
  Matriz *get_primeira_celula();
  int get_tamanho_lista_de_produtos();
  int get_tamanho_lista_de_usuarios();
  void fechar_arquivos();
};
#endif
