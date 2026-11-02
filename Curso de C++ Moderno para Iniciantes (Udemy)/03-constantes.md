# Constantes em C++

Em C++, além de variáveis, também podemos usar valores que não mudam, chamados de **constantes**. Assim como as variáveis, as constantes têm tipos: podem ser `int`, `char`, etc.

É importante diferenciar:

- **Literal:** o valor escrito diretamente no código, como `42`, `'a'` ou `"Oi"`.
- **Constante com `const`:** uma variável cujo valor não pode ser alterado depois de inicializado. Ela pode ocupar memória e ter endereço, como qualquer outro objeto.
- **Macro:** um nome que o pré-processador troca por um texto antes da compilação.

## Utilizando a palavra-chave `const`

```cpp
const std::string hello = "Hello, const!";
```

## Como macros

Em C, as constantes costumam ser declaradas com a diretiva `#define`, geralmente logo depois dos `#include` e fora das funções. Por convenção, o nome usa letras MAIÚSCULAS, sem acentos, cedilha ou hifens.

Exemplo de macro em C++ (note que não há `;` no final):

```cpp
#define HELLO "Hello, macro constant!"
```

> Declarar constantes como macros é uma prática herdada da linguagem C. Em C++, prefira `const`: a macro é só uma substituição de texto, não respeita escopo e não tem um tipo próprio, o que dificulta encontrar erros.

## Exemplo com as duas formas

Vejamos agora um exemplo que engloba as duas formas:

Analise o código e compile: `g++ constant-hello.cpp -o constant-hello`

```cpp
#include <iostream>
#include <string>
#define HELLO "Hello, constant!"
using namespace std;

int main(){
        const string hello = "Hello constant, again!";
        cout << "Constant Macro HELLO: " << HELLO << endl;
        cout << "Constant const hello: " << hello << endl;
        return 0;
}
```

## Códigos de escape

Os códigos de escape representam caracteres especiais dentro de um literal. Os principais são:

| Código de Escape | Descrição |
|---|---|
| `\n` | nova linha |
| `\r` | retorno de carro |
| `\t` | tab |
| `\v` | vertical tab |
| `\b` | backspace |
| `\f` | form feed (page feed) |
| `\a` | alert (beep) |
| `\'` | aspas simples (`'`) |
| `\"` | aspas duplas (`"`) |
| `\?` | interrogação (`?`) |
| `\\` | barra invertida (`\`) |
| `\0` | caractere nulo (terminador de textos no estilo C) |
| `\ooo` | caractere pelo código em octal (ex.: `\033`) |
| `\xhh` | caractere pelo código em hexadecimal (ex.: `\x1b`) |

> `\e`, muito usado para colorir a saída no terminal, é uma extensão do GCC e não faz parte do padrão. A forma portável é `\033`, como em `"\033[32m"`.

Exemplo incluindo o código de escape `\n`:

```cpp
#include <iostream>
#include <string>
#define HELLO "Hello, constant!"
using namespace std;

int main(){
    const string hello = "Hello constant, again!";

    // Sem código de escape
    cout << "Constant Macro HELLO: " << HELLO << endl;
    cout << "Constant const hello: " << hello << endl;

    // Com o código de escape \n
    cout << "Constant Macro HELLO: \n" << HELLO << endl;
    cout << "Constant const hello: \n" << hello << endl;

    // Se atribuirmos um valor para hello ou HELLO, o código não compilará
    // Exemplo: hello = "new hello" , ou HELLO = "New Hello"

    return 0;
}
```
