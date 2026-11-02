# Arrays em C++

O *array* é uma estrutura de dados indexada, que pode armazenar uma determinada quantidade de valores do mesmo tipo. Os dados armazenados em um *array* são chamados de itens do *array*.

Em outras palavras, um **array** pode ser definido como um conjunto de variáveis do mesmo tipo. Veja o diagrama abaixo:

```
         0       1       2       3       4
     +-------+-------+-------+-------+-------+
foo  |       |       |       |       |       |
     +-------+-------+-------+-------+-------+
     |--int--|
```

Ou seja, `foo` é o nome do array, e ele possui 5 variáveis, acessadas pelo número da posição, a partir da posição 0 (zero).

No diagrama, cada posição guarda um `int`, mas poderia ser `char`, `std::string`... Neste exemplo de código, vamos usar `std::string`:

```cpp
// Esse array de nome 'foo' é do tipo 'std::string' e possui 5 posições
std::string foo[5];
```

## Exemplo básico

Um exemplo básico de um array seria:

```cpp
#include <iostream>
#include <string>

int main(){
  std::string meuarray[3] = {"Elis", "Tim", "James"};
  // poderia ter omitido o tamanho, que o compilador deduz, sem perda de desempenho:
  // std::string meuarray[] = {"Elis", "Tim", "James"};

  std::cout << meuarray[1 + 1] << '\n';  // James
  return 0;
}
```

## Array multidimensional

Exemplo de array bidimensional (um tipo de multidimensional):

```cpp
int multiarray[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};
std::cout << multiarray[1][2] << '\n';  // 6

// forma simplificada, mas mais difícil de ler
int x[3][4] = {0, 1 ,2 ,3 ,4 , 5 , 6 , 7 , 8 , 9 , 10 , 11};
```

## Passando Arrays para função em C++

Um array não é um ponteiro, mas seu nome, quando usado como valor, se converte em um ponteiro para o primeiro elemento, assunto que veremos mais à frente. Por isso, se imprimirmos um array sem informar o elemento, será exibida a localização dele na memória (arrays de `char` são a exceção, pois são impressos como texto):

```cpp
int arr[] = {1, 22, 33 , 44, 55, 66};
std::cout << "Imprimindo o array: " << arr << '\n';
```

Podemos alterar um elemento de um array após declará-lo. Só não podemos adicionar posições, pois o tamanho do array é fixo:

```cpp
int arr[] = {1, 22, 33 , 44, 55, 66};
arr[2] = 99;
std::cout << "Imprimindo o elemento de posição 2: " << arr[2] << '\n';
```

Passando um array para uma função:

```cpp
#include <iostream>

void recebe_array( int array_param[] ){ // Aqui, em "int array_param[]": pode-se tanto colocar o tamanho esperado quanto deixar vazio
  array_param[2] = 88;
}

int main(){
  int arr[] = {1, 11, 22 , 33, 44, 55};
  std::cout << "O elemento de posição 2 ANTES de chamar função é: " << arr[2] << '\n';
  recebe_array( arr );
  std::cout << "O elemento de posição 2 DEPOIS de chamar função é: " << arr[2] << '\n';

  // poderia ter especificado também um número maior de elementos, mesmo que não ocupe todos inicialmente
  int other_arr[1000] = {1, 11, 22 , 33, 44, 55};
  std::cout << "O elemento de posição 999 de other_arr é: " << other_arr[999] << '\n';  // Mostra 0

  // poderia também ter especificado o número de elementos, sem atribuir valores inicialmente
  int another[20];
  another[1] = 5;
  std::cout << "O elemento de posição 1 de another é: " << another[1] << '\n';  // Mostra 5
    // OBS (AP): em arrays locais declarados sem inicializador (ex.: int another[20];),
    // os elementos não atribuídos têm valor indeterminado ("lixo" de memória), e lê-los é
    // comportamento indefinido. Com inicialização parcial ({1, 2, ...}) ou vazia ({}),
    // os elementos restantes valem 0.
  return 0;
}
```

Para medir o tamanho de um array em bytes, utilizamos o operador `sizeof`. Para obter a quantidade de elementos, dividimos pelo tamanho de um elemento: `sizeof(arr) / sizeof(arr[0])`. Isso só funciona onde o array foi declarado: em uma função que o recebe como parâmetro, `sizeof` mede o ponteiro. Para imprimir todos os elementos, veremos quando falarmos sobre loops.
