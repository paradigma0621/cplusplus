# Qual a verdadeira origem dos ponteiros inteligentes?

Embora o C++ tenha popularizado o conceito de ponteiros inteligentes, a ideia já aparecia antes dele: a linguagem **Simula I**, antecessora da Simula 67, que inspirou o C++, já tinha referências com contagem embutidas.

# Como utilizar smart pointers?

Para usar os smart pointers, primeiramente, é necessário incluir o cabeçalho `<memory>`. Existem _4 tipos deles_, todos templates de classes. Os três primeiros foram introduzidos no C++11:

- `unique_ptr`: possui semântica para objetos exclusivos;
- `shared_ptr`: ponteiros com semântica para objetos compartilhados;
- `weak_ptr`: referência fraca a um objeto gerenciado por `std::shared_ptr`;
- `auto_ptr`: introduzido no C++98, obsoleto desde o C++11 e removido no C++17.

Para construir objetos gerenciados por esses ponteiros, usam-se as funções livres (não são funções-membro) `std::make_unique` (C++14, para `unique_ptr`) ou `std::make_shared` (C++11, para `shared_ptr`). Esses dois ponteiros são os mais utilizados. O `unique_ptr` é mais leve e mais rápido, pois não mantém contagem de referências, então deve ser a primeira escolha. Use o `shared_ptr` quando o objeto precisar ter mais de um dono.

# Exemplo
```cpp
#include <iostream>
#include <memory>
#include <string>

struct Content {
  private:
    std::string info;

  public:
    Content( std::string l_info ) : info(l_info){}
    void getInfo(){
      std::cout << info << '\n';
    }
};

int main(){
  /* 01 - STACK
  Content c("Olá, amigo?!");
  c.getInfo();
  */

  // Content * c = new Content("Olá, Mundo!");     // *****************************
  // c->getInfo();                                 // *   NÃO É MAIS USADO ASSIM  *
  // delete c;                                     // *****************************

  std::shared_ptr<Content> c = std::make_shared<Content>("Beleza, amigo!"); 
  // Poderia também ter usado `auto c = std::make_shared<Content>("Beleza, amigo!");`
  c->getInfo();

  return 0;
}
```
