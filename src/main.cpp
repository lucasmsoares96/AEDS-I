#include <iostream>

#include "1_etapa/MatrizDeFatoracao.hpp"
#include "2_etapa/UsuariosSemelhantes.hpp"
#include "3_etapa/MelhoresProdutos.hpp"
#include "4_etapa/LRU.hpp"
#include "TAD/tad.hpp"

int main() {
  char arquivo_matriz[] = "shuf_netflix.csv";
  char arquivo_usuario[] = "shuf_user1.csv";
  char arquivo_usuario2[] = "shuf_user2.csv";

  // 1ª etapa
  cout << endl
       << "==============================================================="
       << endl;
  cout << "                           1a ETAPA                            "
       << endl
       << "==============================================================="
       << endl
       << endl;

  cout
      << "Nesta etapa foi gerada uma matriz de fatoracao dinamicamente \n"
         "alocada, na qual cada linha corresponde a um usuario, cada \n"
         "coluna corresponde a um produto e na intercessao de ambos foi \n"
         "armazenado o valor da nota que o usuario correspondente deu \n"
         "para o filme correspondente. O arquivo foi salvo no diretorio \n"
         "raiz do projeto com o nome de \"matriz_de_fatoracao.txt\""
      << endl
      << endl;

  char delimiters[] = ",";
  MatrizDeFatoracao* matrizDeFatoracao =
      new class MatrizDeFatoracao(delimiters, arquivo_matriz);

  // 2ª etapa
  cout << endl
       << "==============================================================="
       << endl;
  cout << "                           2a ETAPA                            "
       << endl
       << "==============================================================="
       << endl
       << endl;
  cout
      << "Nesta etapa um usuario a ser analizado foi lido de um arquivo\n"
         " e armazenado em uma fila. Em seguida foram encontrados na\n"
         "matriz de fatoracao os usuarios mais semelhantes ao usuario\n "
         "informado pelo arquivo. Quando um usuario da matriz de\n "
         "fatoracao avaliou um filme igual a algum dos filmes assistidos\n"
         "pelo usuario do arquivo, essa nota era adicionado a um \n "
         "somador e adicionado em uma pilha. Em seguida esses usuarios \n"
         "foram ordenados de acordo como somador.\n"
      << endl
      << endl;
  Matriz* primeira_celula = matrizDeFatoracao->get_primeira_celula();
  UsuariosSemelhantes* usuario_1 = new class UsuariosSemelhantes(
      arquivo_usuario, primeira_celula, delimiters);
  usuario_1->encontrar_usuarios_semelhantes();
  matrizDeFatoracao->fechar_arquivos();
  usuario_1->fechar_arquivos();

  // 3ª etapa
  cout << endl
       << "==============================================================="
       << endl;
  cout << "                           3a ETAPA                            "
       << endl
       << "==============================================================="
       << endl
       << endl;
  cout
      << "Agora, com todos os usuarios semelhantes separados em um \n"
         "pilha, cada um dos filmes de cada usuario foi comparado com a \n"
         "fila de filmes do usuario que foi informado pelo arquivo, \n"
         "aqueles filmes que não foram assistidos pelo usuario em \n"
         "análise foi concatenado em uma lista. No momento da \n"
         "concatenacao o filme receberu um rating ponderado, que era a \n"
         "media ponderada dos ratins usando como pelo a posição do \n"
         "usuario na pilha dos usuarios mais semelhantes. Em seguida \n"
         "essa lista foi ordenada pelo metodo de ordenacao RadixSort\n"
      << endl;
  Pilha<Matriz>* pilha_ordenada = usuario_1->get_pilha_usuarios();
  Fila<Produto>* usuario_entrada = usuario_1->get_usuario_entrada();
  MelhoresProdutos* melhores_produtos =
      new class MelhoresProdutos(pilha_ordenada, usuario_entrada);

  cout << endl
       << "==============================================================="
       << endl
       << "                           4a ETAPA                            "
       << endl
       << "==============================================================="
       << endl
       << endl;

  cout << "O objetivo dessa etapa era desenvolver um sistema de chache\n"
          "para recomendar filmes para um segundo usuário com base nas\n"
          "recomendações para o usuário anterior. Por isso, foi usado\n"
          "uma tabela hash para reduzir o tempo de acesso aos melhores \n"
          "melhores filmes a serem sugeridos e processar apenas aqueles\n"
          "filmes que ainda não estavam armazenados na cache."
       << endl
       << endl;
  Fila<Matriz>* melhores_produtos_ordenados =
      melhores_produtos->get_fila_melhores_produtos();
  usuario_entrada = usuario_1->get_usuario_entrada();
  TabelaHash* tabelaHash = new TabelaHash;

  cout << "==============================================================="
       << endl
       << "                Tabela Hash do Primeiro Usuário                "
       << endl
       << "==============================================================="
       << endl
       << endl;
  LRU* lru = new class LRU(melhores_produtos_ordenados, tabelaHash,
                           usuario_entrada);
  lru->imprimir();

  cout << "==============================================================="
       << endl
       << "          Fila do Segundo Usuário Lido do Arquivo:            "
       << endl
       << "==============================================================="
       << endl
       << endl;
  UsuariosSemelhantes* usuario_2 = new class UsuariosSemelhantes(
      arquivo_usuario2, primeira_celula, delimiters);
  usuario_2->fechar_arquivos();

  usuario_entrada = usuario_2->get_usuario_entrada();
  Fila<Produto>* usuario_2_bkp = usuario_2->get_usuario_entrada();
  cout << "==============================================================="
       << endl
       << "                  Filmes Encontrados na Hash                   "
       << endl
       << "==============================================================="
       << endl
       << endl;
  Fila<Produto>* novos_produtos = lru->consulta_cache(usuario_entrada);
  cout << "==============================================================="
       << endl
       << "               Filmes NÃO Encontrados na Hash                  "
       << endl
       << "==============================================================="
       << endl
       << endl;
  novos_produtos->imprime();
  usuario_2->update_usuario(novos_produtos);
  usuario_2->encontrar_usuarios_semelhantes();

  pilha_ordenada = usuario_2->get_pilha_usuarios();

  usuario_entrada = usuario_2->get_usuario_entrada();
  melhores_produtos =
      new class MelhoresProdutos(pilha_ordenada, usuario_entrada);
  melhores_produtos_ordenados =
      melhores_produtos->get_fila_melhores_produtos();

  cout << "==============================================================="
       << endl
       << "            Melhores Produtos para o Segundo Usuario           "
       << endl
       << "==============================================================="
       << endl
       << endl;
  melhores_produtos_ordenados->imprime_matriz();
  cout << "\n";

  usuario_entrada = usuario_2->get_usuario_entrada();

  cout << "                                                               "
       << endl
       << "                Removidos por LRU:" << endl
       << "                                                               "
       << endl
       << endl;
  lru->update_cache(melhores_produtos_ordenados, tabelaHash,
                    usuario_entrada);

  cout << "==============================================================="
       << endl
       << "                Tabela Hash do Segundo Usuário                 "
       << endl
       << "==============================================================="
       << endl
       << endl;
  lru->imprimir();

  cout << "==============================================================="
       << endl
       << "               Recomendação de Fimles para o Usuário2          "
       << endl
       << "                   dado_da_tabela+dado_computado               "
       << endl
       << "                             ordenado                          "
       << endl
       << "==============================================================="
       << endl
       << endl;
  lru->recomendar();

  return 0;
}
