# Ponteiros em C++

## 1. O que é um ponteiro

Um **ponteiro** é uma variável que guarda um **endereço de memória** em vez de um valor comum.

- Uma variável `int` guarda um número, por exemplo `3`.
- Um ponteiro para `int` guarda **onde** esse número está na memória, por exemplo `1000`.

Usamos ponteiros quando precisamos acessar ou manipular a memória diretamente: evitar cópias de dados grandes, alterar uma variável a partir de outra função, trabalhar com memória dinâmica etc.

> **Analogia:** um ponteiro funciona como um **link simbólico** no Linux. O link não é o arquivo, mas leva até ele. Se você editar o arquivo pelo link, o original é que muda.

---

## 2. Como a memória de um programa é organizada

A memória que um programa usa é dividida, de forma simplificada, em quatro áreas:

| Área | O que guarda |
|---|---|
| **Código** | as instruções do programa compilado |
| **Global** | as variáveis globais (e estáticas) |
| **Pilha** (*stack*) | os parâmetros e as variáveis locais das funções |
| **Heap** | as variáveis alocadas dinamicamente (com `new`) |

```
┌──────────────────────┐
│        PILHA         │  ← cresce para baixo
│        ▼ ▼ ▼         │
├──────────────────────┤
│    MEMÓRIA LIVRE     │
├──────────────────────┤
│        ▲ ▲ ▲         │
│         HEAP         │  ← cresce para cima
├──────────────────────┤
│        GLOBAL        │
├──────────────────────┤
│        CÓDIGO        │
└──────────────────────┘
```

A pilha e a heap crescem uma em direção à outra, usando a memória livre entre elas.

Cada vez que uma função é chamada (inclusive a `main()`), suas variáveis locais são criadas **na pilha** e destruídas quando ela termina. O **espaço** que cada variável ocupa depende do seu tipo: em geral, `char` ocupa 1 byte e `int` ocupa 4 bytes.

---

## 3. Variáveis na memória

Considere este programa:

```cpp
#include <iostream>

int main(){
    int x = 3;
    char c = 'a';
    int y[3] = {1, 2, 3};
    return 0;
}
```

Cada variável recebe um endereço na pilha. Para fins didáticos, podemos imaginar assim:

| identificador | endereço | valor | tamanho |
|---|---|---|---|
| `x` | 1000 | 3 | 4 bytes |
| `c` | 1004 | 'a' | 1 byte |
| `y[0]` | 1008 | 1 | 4 bytes |
| `y[1]` | 1012 | 2 | 4 bytes |
| `y[2]` | 1016 | 3 | 4 bytes |

Note que os elementos de um array ficam **lado a lado** na memória, cada um a 4 bytes do anterior (o tamanho de um `int`). Isso vai ser importante na seção 6.

> Os endereços acima são ilustrativos. Endereços reais são números grandes, exibidos em hexadecimal (algo como `0x7ffd5c3a1b2c`), e mudam a cada execução.

---

## 4. Os operadores `&` e `*`

Para trabalhar com ponteiros, você precisa conhecer dois operadores:

| Operador | Nome | Significado |
|---|---|---|
| `&variavel` | **endereço de** | "qual é o endereço desta variável?" |
| `*ponteiro` | **desreferência** | "qual é o valor que está no endereço guardado aqui?" |

```cpp
int myvar = 25;

int *foo = &myvar;   // foo guarda o ENDEREÇO de myvar
int bar = myvar;     // bar guarda uma CÓPIA do valor de myvar (25)

int baz = *foo;      // baz recebe o VALOR apontado por foo (25)
```

- `foo` aponta para `myvar`. Se `myvar` mudar, `*foo` reflete a mudança.
- `bar` é uma cópia independente. Mudar `myvar` depois não afeta `bar`.

> **Atenção à dupla função do `*`:** na **declaração** (`int *foo`), o `*` indica que `foo` é um ponteiro. Fora da declaração (`*foo`), ele **desreferencia**, ou seja, acessa o valor apontado.

---

## 5. Declarando e usando um ponteiro

Voltando ao programa da seção 3, vamos acrescentar um ponteiro `p` que aponta para `x`:

```cpp
#include <iostream>

int main(){
    int x = 3;
    char c = 'a';
    int y[3] = {1, 2, 3};
    int *p = &x;               // p recebe o endereço de x

    std::cout << p  << '\n';   // endereço guardado em p (ex.: 0x7ffd...)
    std::cout << *p << '\n';   // valor de x → 3

    *p = 10;                   // altera x através do ponteiro
    std::cout << x  << '\n';   // → 10
    return 0;
}
```

Na tabela de memória, `p` aparece como mais uma variável:

| identificador | endereço | valor |
|---|---|---|
| `x` | 1000 | 3 |
| `c` | 1004 | 'a' |
| `y[0]` | 1008 | 1 |
| `y[1]` | 1012 | 2 |
| `y[2]` | 1016 | 3 |
| **`p`** | **1020** | **1000** |

Lendo a linha do `p`:

- **endereço `1020`**: onde o próprio `p` está. Um ponteiro também é uma variável e ocupa seu próprio espaço na memória.
- **valor `1000`**: o conteúdo de `p`, que é o endereço de `x`. Por isso se diz que **"`p` aponta para `x`"**.

---

## 6. Regras importantes

### 6.1 O tipo do ponteiro deve ser o tipo da variável apontada

```cpp
int x = 3;
int  *p1 = &x;   // OK
char *p2 = &x;   // ERRO: um char* não pode apontar para um int
```

O tipo diz ao compilador **quantos bytes ler** e **como interpretá-los** ao desreferenciar.

### 6.2 Ponteiros e arrays

Um ponteiro para array aponta, na verdade, para **um elemento** do array, normalmente o primeiro. O nome do array, quando usado como valor, já se converte em um ponteiro para o primeiro elemento:

```cpp
int y[3] = {1, 2, 3};

int *p = y;        // o mesmo que: int *p = &y[0];

std::cout << *p       << '\n';   // 1 (primeiro elemento)
std::cout << *(p + 2) << '\n';   // 3 (terceiro elemento)
std::cout << p[2]     << '\n';   // 3 (mesma coisa, sintaxe de índice)
```

`p + 2` não soma 2 bytes. Soma **2 elementos**, ou seja, `2 × sizeof(int)` bytes. Isso só funciona porque os elementos ficam lado a lado na memória (seção 3).

### 6.3 O caso especial dos arrays de `char`

Com textos no estilo C (arrays de `char`), o `std::cout` se comporta de um jeito diferente:

```cpp
char letra[] = "Ola";
char *pletra = letra;   // aponta para o primeiro caractere

std::cout << *pletra       << '\n';   // O   → COM asterisco: só o primeiro caractere
std::cout << pletra        << '\n';   // Ola → SEM asterisco: o texto inteiro
std::cout << *(pletra + 2) << '\n';   // a   → o terceiro caractere (índice 2)
std::cout << pletra[2]     << '\n';   // a   → mesma coisa
```

- **Com asterisco** (`*pletra`), você obtém um único `char`: o primeiro.
- **Sem asterisco** (`pletra`), o `std::cout` entende um `char*` como **texto** e imprime caractere por caractere até encontrar o terminador `'\0'`.

Com um `int*`, imprimir o ponteiro sem asterisco mostra o **endereço**. O comportamento de "imprimir tudo" é exclusivo do `char*`.

---

## 7. Por que ponteiros importam: evitando cópias

Entender ponteiros é fundamental para o desempenho de programas em C/C++. Compare:

**Cópia:**

```cpp
std::string var1 = "Meu conteúdo";
std::string var2 = var1;      // duplica todo o texto
```

```
┌───────────────────────────────┐
│ var1 = "Meu conteúdo"         │
└───────────────────────────────┘
┌───────────────────────────────┐
│ var2 = "Meu conteúdo"         │   ← uma segunda cópia, independente
└───────────────────────────────┘
```

**Ponteiro:**

```cpp
std::string var1 = "Meu conteúdo";
std::string *var2 = &var1;    // guarda apenas o endereço de var1
```

```
┌───────────────────────────────┐
│ var1 = "Meu conteúdo"         │ ◄──┐
└───────────────────────────────┘    │
┌───────────────────────────────┐    │
│ var2 = 0x7ffd5c3a1b20         │ ───┘  ← só um endereço
└───────────────────────────────┘
```

Com a cópia, existem dois textos na memória e alterar um não altera o outro. Com o ponteiro, existe **um único** texto. `var2` só sabe onde ele está, e `*var2` dá acesso a ele. Para dados grandes, guardar um endereço é muito mais barato do que copiar tudo.

---

## 8. Ponteiros no C++ moderno

Ponteiros são essenciais para entender como o C++ funciona por baixo dos panos. No C++ moderno, porém, **ponteiros "crus" não são a primeira escolha**. Algumas boas práticas:

- **Use `nullptr`** para indicar um ponteiro que não aponta para nada (nunca `0` ou `NULL`):

  ```cpp
  int *p = nullptr;
  if (p != nullptr) { /* só desreferencie se for válido */ }
  ```

- **Para evitar cópias em funções, prefira referências** (`&` na declaração). Elas têm o mesmo ganho de desempenho, com sintaxe mais simples e sem risco de serem nulas:

  ```cpp
  void imprime(const std::string& texto){   // não copia o texto
      std::cout << texto << '\n';
  }
  ```

- **Para memória dinâmica, prefira *smart pointers***, como `std::unique_ptr` e `std::shared_ptr` (em `<memory>`). Eles liberam a memória sozinhos e evitam vazamentos:

  ```cpp
  auto p = std::make_unique<int>(42);   // liberado automaticamente
  ```

- **Nunca desreferencie** um ponteiro nulo, não inicializado ou que aponte para uma variável que já deixou de existir. Isso é *comportamento indefinido* e pode travar o programa.

> Note que `&` também tem dois papéis: em uma **expressão** (`&x`), significa "endereço de". Em uma **declaração** (`std::string& texto`), cria uma *referência*. São coisas diferentes.

---

## Resumo

| Código | Significado |
|---|---|
| `int *p;` | declara `p` como ponteiro para `int` |
| `p = &x;` | `p` recebe o endereço de `x` |
| `*p` | o valor que está no endereço guardado em `p` |
| `*p = 10;` | altera a variável apontada |
| `p + n` / `p[n]` | avança `n` **elementos** (em arrays) |
| `nullptr` | ponteiro que não aponta para nada |

- Um ponteiro é uma variável que guarda um **endereço**.
- `&` obtém o endereço; `*` acessa o valor apontado.
- O tipo do ponteiro deve corresponder ao tipo da variável apontada.
- O nome de um array se converte em ponteiro para o seu primeiro elemento.
- Ponteiros evitam cópias, mas no C++ moderno prefira **referências** e **smart pointers** sempre que possível.
