# new e delete

Na linguagem de programação C++, `new` e `delete` são um par de operadores que realizam **alocação dinâmica de memória**, **construção** de objetos e **destruição** de objetos.

**No C++ moderno, eles são pouco usados diretamente**, pois os *smart pointers* fazem esse trabalho. O `new` sempre retorna um *ponteiro* para a memória alocada. Cada `new` precisa de um `delete`, e cada `new[]`, de um `delete[]`.

## Exemplo geral 1

Alocando um array:

```cpp
int* p = new int[4];
for (int i = 0; i < 4; ++i) {
  std::cout << "Digite um NÚMERO: ";
  std::cin >> p[i];
}

std::cout << "O primeiro número digitado foi: " << *p << '\n';
delete[] p;
p = nullptr;
```

## Exemplo geral 2

Alocando um único objeto:

```cpp
#include <iostream>
#include <string>

int main(){
  std::string * ponteiro = nullptr;
  ponteiro = new std::string;
  std::cout << "Digite algo: ";
  std::getline( std::cin, (*ponteiro) );
  std::cout << "Você digitou: \033[32;4m" << *ponteiro << "\033[m" << '\n';
  delete ponteiro;
  ponteiro = nullptr;
  return 0;
}
```
