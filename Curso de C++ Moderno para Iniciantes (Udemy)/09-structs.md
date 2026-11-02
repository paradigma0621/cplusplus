# Structs

O uso de estruturas (`struct`) pode substituir o uso de classes, ou até mesmo ser combinado com elas. Apesar da semelhança entre os nomes, a programação estruturada não surgiu do `struct`: ela trata da organização do fluxo do programa, com sequências, decisões e repetições.

Iremos abordar o assunto bem por cima. Em C, a `struct` só agrupa dados. Já em C++, `struct` e `class` são praticamente iguais: as duas podem ter funções-membro, construtores e herança. A principal diferença é o acesso padrão, que é público na `struct` e privado na `class`.

## Sinopse

```cpp
struct nome_da_estrutura {
  // declaração dos membros
} variaveis;  // definir variáveis aqui é opcional, mas o ';' é obrigatório
```

## Exemplo

```cpp
#include <iostream>
#include <string>

// Em C++, `struct cliente { ... };` já permite declarar `cliente x;`, sem `typedef`.
// O `typedef` abaixo só cria o apelido `t_cliente`, um costume herdado do C.
// No C++ moderno, o apelido pode ser criado com: `using t_cliente = cliente;`
typedef struct cliente {
  std::string nome;
  std::string sobrenome;
  int matricula;
} t_cliente;

void show_data( t_cliente c ){   // poderia ter declarado como: `void show_data( cliente c ){`
  std::cout << "\n\033[5m:::: DADOS DO CLIENTE ::::" << "\033[m\n";
  std::cout << c.nome << " " << c.sobrenome << " - \033[33;1m" << c.matricula << "\033[m\n";
}

t_cliente get_data(){  // poderia ter declarado como: `cliente get_data(){`
  t_cliente c;
  std::cout << "Informe o nome do cliente: ";
  std::getline( std::cin , c.nome );

  std::cout << "Informe o sobrenome do cliente: ";
  std::getline( std::cin , c.sobrenome );

  std::cout << "Informe a matrícula do cliente: ";
  std::cin >> c.matricula;

  return c;
}

int main(){
  std::cout << ":::: CADASTRO DE CLIENTES ::::" << '\n';
  t_cliente dados_cliente;  // poderia ter declarado como: `cliente dados_cliente;`
  dados_cliente = get_data();
  show_data( dados_cliente );
  return 0;
}
```
