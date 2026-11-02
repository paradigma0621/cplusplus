(Obs: o que está aqui já está contido nos outros arquivos dessa pasta. Deixei aqui também pois considero bastante relevantes)
# Ponteiros e arrays

Um ponteiro para array aponta, na verdade, para **um elemento** do array, normalmente o primeiro. O nome do array, quando usado como valor, já se converte em um ponteiro para o primeiro elemento:

```cpp
int y[3] = {1, 2, 3};

int *p = y;        // o mesmo que: int *p = &y[0];

std::cout << *p       << '\n';   // 1 (primeiro elemento)
std::cout << *(p + 2) << '\n';   // 3 (terceiro elemento)
std::cout << p[2]     << '\n';   // 3 (mesma coisa, sintaxe de índice)
```

`p + 2` não soma 2 bytes. Soma **2 elementos**, ou seja, `2 × sizeof(int)` bytes. Isso só funciona porque os elementos ficam lado a lado na memória (veja a seção 3 de `06-ponteiros.md`).

## Dupla função do `*`

```cpp
int myvar = 25;

int *foo = &myvar;   // foo guarda o ENDEREÇO de myvar
```
> **Atenção à dupla função do `*`:** na **declaração** (`int *foo`), o `*` indica que `foo` é um ponteiro. Fora da declaração (`*foo`), ele **desreferencia**, ou seja, acessa o valor apontado.

> Note que `&` também tem dois papéis: em uma **expressão** (`&x`), significa "endereço de". Em uma **declaração** (`std::string& texto`), cria uma *referência*. São coisas diferentes.


## O caso especial dos arrays de `char`

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
