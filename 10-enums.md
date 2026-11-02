# Enum Types

C++ contém alguns tipos de dados integrados. Mas esses tipos nem sempre são suficientes para os tipos de coisas que queremos fazer. Portanto, C++ contém recursos que **permitem aos programadores criar seus próprios tipos de dados**. Esses tipos de dados são chamados de tipos de dados definidos pelo usuário.

Talvez o tipo de dados mais simples definido pelo usuário seja o tipo enumerado. Um tipo enumerado (também chamado de *enumeração* ou `enum`) é um tipo de dados em que cada valor possível é definido como uma constante simbólica (chamada de **enumerador**). Enumerações são definidas por meio da palavra-chave `enum`. Vejamos um exemplo:

```cpp
enum Animals {  // Por convenção, o nome do tipo começa com letra maiúscula
    gato,
    cachorro,
    papagaio
};
```

As enumerações são úteis para criar dados fáceis de lembrar.

## Exemplo
```cpp
#include <iostream>

enum Cores {
  red,          // 0
  green = 84,
  yellow        // 85: sem valor definido, vale o anterior + 1
};

enum Saidas {         // Por padrão, os enumeradores recebem valores inteiros:
  sucesso,            // se não definirmos o número (como feito no `green = 84` ali em cima), o primeiro é 0, o segundo 1, o terceiro 2...
  erro_ao_abrir,
  erro_de_leitura,
  erro_de_permissao
};

void mostra( Cores cor ){
  std::cout << "O valor da cor recebida é: " << cor << '\n';
}

int main(){
  Cores cor = yellow;
  std::cout << "O valor da cor red é: " << red << '\n';                // Saída: O valor da cor red é: 0
  std::cout << "O valor de erro_ao_abrir é: " << erro_ao_abrir << '\n'; // Saída: O valor de erro_ao_abrir é: 1
  mostra( cor ); // Saída: O valor da cor recebida é: 85
  return sucesso;  // Clean code!!! (pois equivale a `return 0`)
}
```
