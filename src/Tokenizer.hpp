#ifndef __TOKENIZER_HPP
#define __TOKENIZER_HPP

#include <string.h>

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Tokenizer {
 public:
  Tokenizer();
  ~Tokenizer();

  void tokenizer(char line[]);
  void set_delimiter(char *d);
  T *get_token();

 private:
  char *tokens;
  char *delimiter;       // delimiter in "," and ' '
  string::size_type sz;  // alias of size_t
};
#endif
