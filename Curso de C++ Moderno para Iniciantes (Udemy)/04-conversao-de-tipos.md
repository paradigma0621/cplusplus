# Conversão de tipos em C++

É possível converter dados de um tipo em outro. Isso é conhecido como conversão de tipo. Existem dois tipos de conversão de tipo em C++.

1. Conversão implícita
2. Conversão explícita (também conhecida como *Type Casting*)

## Conversão implícita

A conversão de tipo feita automaticamente pelo compilador é conhecida como conversão de tipo implícita. Esse tipo de conversão também é conhecido como conversão automática. Exemplo de conversão implícita:

```cpp
double d = 3.96;
int i = d;
char a = 'a';
std::cout << "Valor de d: " << d << '\n'; // Saída: Valor de d: 3.96
std::cout << "Valor de i: " << i << '\n'; // Saída: Valor de i: 3
i = a + i;
std::cout << "Valor de a + i: " << i << '\n'; // Saída: Valor de a + i: 100
```

> Como vimos no exemplo acima, a conversão de um tipo de dados para outro está sujeita à perda de dados. Isso acontece quando o tipo de destino não consegue representar o valor original, como na conversão de `double` para `int`.

## Conversão explícita de C++

Quando o programador converte manualmente os dados de um tipo para outro, isso é conhecido como conversão explícita. Existem 2 formas principais de usar a conversão explícita em C++: o cast no estilo C e os operadores de conversão de tipo.

### Cast no estilo C

Como o nome sugere, esta forma de conversão foi herdada da linguagem C. Exemplos:

```cpp
int i, j;
double d = 9.87;
i = (int)d; // notação "cast"
j = int(d); // notação funcional
```

### Operadores de conversão de tipo

Além dessas duas notações, há também quatro operadores para conversão de tipo. São eles:

- `static_cast`: usado nas conversões comuns, verificadas na compilação, como entre tipos numéricos.
- `dynamic_cast`: geralmente usado para conversões com ponteiros de classes polimórficas, verificadas durante a execução.
- `const_cast`: usado para adicionar ou remover o qualificador `const`.
- `reinterpret_cast`: reinterpreta os bits de um valor como se fossem de outro tipo, por exemplo, um ponteiro como outro tipo de ponteiro. Faz parte do padrão desde o C++98, mas é perigoso, pois o compilador quase não verifica a conversão. Por isso, é restrito a código de baixo nível.

A sintaxe de uso deles consiste em: `nome_cast<novo_tipo>(expressão)`

Exemplo de `static_cast`:

```cpp
double d = 3.14;
int i = static_cast<int>(d);
d = static_cast<double>(i);
```

Exemplo de `const_cast`:

```cpp
int valor = 10;
const int* leitura = &valor;               // ponteiro que só permite ler

int* escrita = const_cast<int*>(leitura);  // remove o const do ponteiro
*escrita = 20;                             // OK: valor agora é 20
```

> A alteração acima só é válida porque `valor` não foi declarado como `const`. Alterar um objeto declarado como `const` é comportamento indefinido.

Para os exemplos de uso de `dynamic_cast` e `reinterpret_cast`, precisaríamos abordar classes e ponteiros, que veremos mais à frente.

Nem todos os tipos podem ser convertidos com esses operadores. `static_cast` de `string` para `double`, por exemplo, gera erro de compilação. Nesse caso, use uma função como `std::stod`.

Para saber o tipo de uma variável, usa-se `typeid(variavel).name()`, do cabeçalho `<typeinfo>`. O nome exibido depende do compilador: no g++, `int` aparece como `i`.
