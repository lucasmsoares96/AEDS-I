#ifndef __USUARIOSSEMELHANTES_HPP
#define __USUARIOSSEMELHANTES_HPP

#include <fstream>
#include <iostream>
#include <string>

#include "../TAD/tad.hpp"
#include "../estruturas.hpp"

using namespace std;

class UsuariosSemelhantes {
 private:
  ifstream *inFile;
  char *delimiters;
  Matriz *primeira_celula;
  Fila<Produto> *usuario_entrada = new Fila<Produto>();
  Pilha<Matriz> *usuarios_semelhantes = new Pilha<Matriz>();
  Pilha<float> *pesos = new Pilha<float>();

  void abrir_arquivos(char *arquivo);
  void criar_fila_de_produtos();
  void imprimir_usuarios_pesos();
  void ordenar();

 public:
  UsuariosSemelhantes(char *arquivo, Matriz *primeira_celula,
                      char *delimiters);
  void encontrar_usuarios_semelhantes();
  void update_usuario(Fila<Produto>* novos_produtos);
  Pilha<Matriz> *get_pilha_usuarios();
  Fila<Produto> *get_usuario_entrada();
  void fechar_arquivos();
};
#endif
