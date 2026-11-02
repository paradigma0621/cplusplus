# Operadores em C++

## Precedência e associatividade

Os grupos estão em ordem de precedência, da maior (grupo 1) para a menor (grupo 6). No grupo 4, as linhas também seguem essa ordem (ex.: `*` tem precedência sobre `+`). Nos demais grupos, todos os operadores têm a mesma precedência.

- **Esquerda → direita:** `a - b - c` é avaliado como `(a - b) - c`
- **Direita → esquerda:** `a = b = c` é avaliado como `a = (b = c)`

### 1. Esquerda → direita

| Operadores | Descrição |
|---|---|
| `::` | Resolução de escopo |

### 2. Esquerda → direita

| Operadores | Descrição |
|---|---|
| `++` `--` | Incremento e decremento pós-fixados |
| `tipo()` `tipo{}` | Conversão de tipo na notação funcional |
| `()` | Parênteses (chamada de função) |
| `[]` | Elemento de arranjo |
| `.` | Seleção de elemento por identificador |
| `->` | Seleção de elemento por ponteiro |

### 3. Direita → esquerda

| Operadores | Descrição |
|---|---|
| `++` `--` | Incremento e decremento pré-fixados |
| `+` `-` | Mais e menos unários |
| `!` `~` | *Não* lógico e complemento |
| `(tipo)` | Conversão de tipo de dado |
| `*` | Desreferência |
| `&` | Endereço de |
| `sizeof` | Tamanho de elemento |
| `new` `new[]` | Alocação dinâmica de memória |
| `delete` `delete[]` | Desalocação dinâmica de memória |

### 4. Esquerda → direita

| Operadores | Descrição |
|---|---|
| `.*` `->*` | Ponteiro para membro |
| `*` `/` `%` | Multiplicação, divisão e módulo (resto) |
| `+` `-` | Adição e subtração |
| `<<` `>>` | Deslocamento de bits à esquerda e à direita |
| `<=>` | Comparação de três vias (C++20) |
| `<` `<=` `>` `>=` | "Menor que", "menor ou igual a", "maior que" e "maior ou igual a" |
| `==` `!=` | "Igual a" e "diferente de" |
| `&` | *E* para bits |
| `^` | *Ou exclusivo* para bits |
| `\|` | *Ou* para bits |
| `&&` | *E* lógico |
| `\|\|` | *Ou* lógico |

### 5. Direita → esquerda

| Operadores | Descrição |
|---|---|
| `c?t:f` | Condição ternária |
| `throw` | Lançamento de exceção |
| `=` | Atribuição |
| `+=` `-=` | Atribuição por adição ou subtração |
| `*=` `/=` `%=` | Atribuição por multiplicação, divisão ou módulo (resto) |
| `<<=` `>>=` | Atribuição por deslocamento de bits |
| `&=` `^=` `\|=` | Atribuição por operações sobre bits |

### 6. Esquerda → direita

| Operadores | Descrição |
|---|---|
| `,` | Vírgula |

## Operadores aritméticos

| Operador | Sintaxe |
|---|---|
| Mais unário | `+a` |
| Adição | `a + b` |
| Incremento pré-fixado | `++a` |
| Incremento pós-fixado | `a++` |
| Atribuição por adição | `a += b` |
| Menos unário | `-a` |
| Subtração | `a - b` |
| Decremento pré-fixado | `--a` |
| Decremento pós-fixado | `a--` |
| Atribuição por subtração | `a -= b` |
| Multiplicação | `a * b` |
| Atribuição por multiplicação | `a *= b` |
| Divisão | `a / b` |
| Atribuição por divisão | `a /= b` |
| Módulo (resto) | `a % b` |
| Atribuição por módulo (resto) | `a %= b` |

## Operadores comparativos

| Operador | Sintaxe |
|---|---|
| Menor que | `a < b` |
| Menor ou igual a | `a <= b` |
| Maior que | `a > b` |
| Maior ou igual a | `a >= b` |
| Diferente de | `a != b` |
| Igual a | `a == b` |
| Comparação de três vias (C++20) | `a <=> b` |

## Operadores lógicos

| Operador | Sintaxe |
|---|---|
| *Não* lógico | `!a` |
| *E* lógico | `a && b` |
| *Ou* lógico | `a \|\| b` |

## Operadores sobre bits

| Operador | Sintaxe |
|---|---|
| Complemento | `~a` |
| *E* | `a & b` |
| Atribuição por *e* | `a &= b` |
| *Ou* | `a \| b` |
| Atribuição por *ou* | `a \|= b` |
| *Ou exclusivo* | `a ^ b` |
| Atribuição por *ou exclusivo* | `a ^= b` |
| Deslocamento à esquerda | `a << b` |
| Atribuição de deslocamento à esquerda | `a <<= b` |
| Deslocamento à direita | `a >> b` |
| Atribuição de deslocamento à direita | `a >>= b` |

## Outros operadores

| Operador | Sintaxe |
|---|---|
| Atribuição | `a = b` |
| Chamada de função | `a()` |
| Elemento de arranjo | `a[b]` |
| Desreferência | `*a` |
| Endereço de | `&a` |
| Membro por ponteiro | `a->b` |
| Membro por identificador | `a.b` |
| Ponteiro para membro, por identificador | `a.*b` |
| Ponteiro para membro, por ponteiro | `a->*b` |
| Conversão de tipo de dados | `(tipo) a` |
| Vírgula | `a , b` |
| Condição ternária | `a ? b : c` |
| Resolução de escopo | `a::b` |
| Tamanho de | `sizeof a` |
| Identificador de tipo | `typeid(tipo)` |
