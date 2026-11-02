# Vetores em C++ (`std::vector`)

## 1. O que é um `std::vector`

O `std::vector` é a alternativa moderna ao array primitivo do C++. Ele guarda uma sequência de elementos do mesmo tipo, mas, ao contrário do array, **cresce e diminui conforme a necessidade** e sabe o próprio tamanho.

| Array primitivo | `std::vector` |
|---|---|
| `int a[5];` com tamanho fixo, definido na compilação | `std::vector<int> v;` com tamanho variável |
| não sabe o próprio tamanho | `v.size()` |
| não pode crescer | `v.push_back(...)` |
| acesso fora dos limites passa despercebido | `v.at(i)` verifica os limites |

Para usar, inclua o cabeçalho `<vector>` e informe o **tipo dos elementos** entre `< >`:

```cpp
#include <vector>
#include <string>

std::vector<int> numeros;                     // vazio
std::vector<int> zeros(5);                    // 5 elementos com valor 0
std::vector<int> setes(3, 7);                 // {7, 7, 7}
std::vector<std::string> v = {"Shell Script", "Web", "C++", "Linux", "BSD"};
```

> **Por baixo dos panos:** os elementos ficam **lado a lado** na memória, como num array (veja a aula de ponteiros), só que alocados na **heap**. O objeto `vector` em si, que pode estar na pilha, guarda apenas um ponteiro para esses dados, o tamanho e a capacidade. Quando você o destrói, a memória da heap é liberada automaticamente.

Nos exemplos a seguir, vamos usar este vetor:

```cpp
std::vector<std::string> v = {"Shell Script", "Web", "C++", "Linux", "BSD"};
//  índice:                       0           1      2       3       4
```

---

## 2. Acessando elementos

| Função | Retorna | Observação |
|---|---|---|
| `v[i]` | o elemento no índice `i` | **sem** verificação: índice inválido é comportamento indefinido |
| `v.at(i)` | o elemento no índice `i` | **com** verificação: índice inválido lança `std::out_of_range` |
| `v.front()` | o primeiro elemento | o vetor não pode estar vazio |
| `v.back()` | o último elemento | o vetor não pode estar vazio |

```cpp
std::cout << v[2]      << '\n';   // C++
std::cout << v.at(3)   << '\n';   // Linux
std::cout << v.front() << '\n';   // Shell Script
std::cout << v.back()  << '\n';   // BSD

v.at(10);   // lança std::out_of_range
v[10];      // compila e roda, mas é comportamento indefinido!
```

Todas essas funções retornam uma **referência**, então também servem para alterar o elemento:

```cpp
v[1] = "Web Dev";   // v agora é {"Shell Script", "Web Dev", "C++", "Linux", "BSD"}
```

---

## 3. Tamanho e capacidade

| Função | O que faz |
|---|---|
| `v.size()` | quantidade de elementos atual |
| `v.empty()` | `true` se não houver elementos |
| `v.capacity()` | quantos elementos cabem **sem realocar** memória |
| `v.reserve(n)` | garante capacidade para pelo menos `n` elementos |
| `v.resize(n)` | muda o **tamanho** para `n`, cortando ou criando elementos |
| `v.max_size()` | limite teórico de elementos (enorme, raramente útil) |

```cpp
std::cout << v.size()  << '\n';   // 5
std::cout << v.empty() << '\n';   // 0 (false)
```

### Tamanho × capacidade

O `size()` é quantos elementos **existem**. O `capacity()` é quanto espaço **já está reservado**. Quando um `push_back` estoura a capacidade, o vector aloca um bloco maior (em geral o dobro), copia ou move tudo para lá e libera o antigo:

```cpp
std::vector<int> n;
for (int i = 0; i < 9; ++i) {
    n.push_back(i);
    std::cout << "size=" << n.size() << " capacity=" << n.capacity() << '\n';
}
// size=1 capacity=1
// size=2 capacity=2
// size=3 capacity=4    ← realocou
// size=4 capacity=4
// size=5 capacity=8    ← realocou
// size=6 capacity=8
// size=7 capacity=8
// size=8 capacity=8
// size=9 capacity=16   ← realocou   (saída do g++; outros compiladores podem crescer diferente)
```

Se você sabe de antemão quantos elementos terá, `reserve` evita essas realocações:

```cpp
std::vector<int> n;
n.reserve(1000);   // capacity >= 1000, size continua 0
```

---

## 4. Adicionando e removendo elementos

| Função | O que faz |
|---|---|
| `v.push_back(x)` | adiciona `x` no **final** |
| `v.pop_back()` | remove o **último** elemento |
| `v.insert(pos, x)` | insere `x` antes da posição `pos` (um iterador) |
| `v.erase(pos)` | remove o elemento na posição `pos` |
| `v.erase(ini, fim)` | remove o intervalo `[ini, fim)` |
| `v.clear()` | remove todos os elementos (`size()` vira 0) |
| `v.assign(n, x)` / `v.assign({...})` | substitui todo o conteúdo |
| `v.swap(outro)` | troca o conteúdo com outro vector |

```cpp
std::vector<std::string> v = {"Shell Script", "Web", "C++", "Linux", "BSD"};

v.push_back("GNU");             // {"Shell Script", "Web", "C++", "Linux", "BSD", "GNU"}
v.pop_back();                   // remove "GNU" → volta ao original
v.pop_back();                   // remove "BSD" → {"Shell Script", "Web", "C++", "Linux"}

v.insert(v.begin(), "Unix");    // {"Unix", "Shell Script", "Web", "C++", "Linux"}
v.erase(v.begin() + 2);         // remove "Web" → {"Unix", "Shell Script", "C++", "Linux"}

v.clear();                      // {}
std::cout << v.empty() << '\n'; // 1 (true)
```

> **Não existe `'\0'` no final de um vector.** Esse terminador é exclusivo dos textos no estilo C (`char[]`). O `pop_back()` sempre remove o último elemento **de verdade**.

> **Desempenho:** `push_back` e `pop_back` no final são rápidos. `insert` e `erase` no meio ou no início precisam **deslocar** todos os elementos seguintes, o que fica caro em vetores grandes.

---

## 5. Iteradores

### 5.1 O que é um iterador

Um **iterador** é um objeto que aponta para um elemento de um contêiner e sabe "andar" para o próximo. Ele se comporta como um ponteiro:

| Operação | Significado |
|---|---|
| `*it` | acessa o elemento apontado |
| `++it` | avança para o próximo elemento |
| `it + n` | avança `n` posições (no vector) |
| `it1 == it2` | compara posições |

Por isso, para ler o valor é preciso usar o `*` (**desreferência**), exatamente como na aula de ponteiros. Sem ele, você teria o iterador, e não o elemento, e o `std::cout` não saberia imprimi-lo, dando erro de compilação.

### 5.2 `begin()` e `end()`

- `v.begin()` aponta para o **primeiro** elemento.
- `v.end()` aponta para a posição **logo após o último** elemento. Lá **não existe elemento**; ela serve só para marcar o fim.

```
   v.begin()                                      v.end()
      │                                              │
      ▼                                              ▼
┌──────────────┬───────┬───────┬─────────┬───────┐ ─ ─ ─ ┐
│ Shell Script │  Web  │  C++  │  Linux  │  BSD  │       │  ← nada aqui
└──────────────┴───────┴───────┴─────────┴───────┘ ─ ─ ─ ┘
```

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> v = {"Shell Script", "Web", "C++", "Linux", "BSD"};

    std::vector<std::string>::iterator primeiro = v.begin();
    std::cout << *primeiro << '\n';         // Shell Script

    auto ultimo = v.end() - 1;              // um passo antes do end()
    std::cout << *ultimo << '\n';           // BSD
    return 0;
}
```

> ⚠️ **Nunca desreferencie `v.end()`.** `*v.end()` é comportamento indefinido: pode imprimir lixo, travar ou parecer funcionar. Para obter o último elemento, use `v.back()`, `*(v.end() - 1)` ou `*v.rbegin()`.

> **Dica:** o tipo `std::vector<std::string>::iterator` é longo. Use `auto`, como em `auto it = v.begin();`.

### 5.3 Percorrendo o vector

As três formas abaixo imprimem todos os elementos:

```cpp
// 1. Com índice
for (std::size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << '\n';
}

// 2. Com iterador: anda de begin() até chegar em end()
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << '\n';
}

// 3. Com for de intervalo (o mais simples; usa iteradores por baixo)
for (const auto& s : v) {
    std::cout << s << '\n';
}
```

### 5.4 Iteradores reversos: `rbegin()` e `rend()`

`rbegin()` aponta para o **último** elemento e `rend()` para a posição **antes do primeiro**. O `++` anda de trás para frente:

```cpp
for (auto it = v.rbegin(); it != v.rend(); ++it) {
    std::cout << *it << ' ';
}
// BSD Linux C++ Web Shell Script
```

### 5.5 Cuidado: iteradores invalidados

Quando o vector **realoca** a memória (por exemplo, num `push_back` que estoura a capacidade), os elementos mudam de endereço. Iteradores, ponteiros e referências antigos passam a apontar para memória liberada:

```cpp
auto it = v.begin();
v.push_back("GNU");        // pode realocar
std::cout << *it << '\n';  // comportamento indefinido se houve realocação
```

Depois de inserir ou remover elementos, obtenha os iteradores de novo.

---

## 6. Exemplo prático: limpando um CPF

Os mesmos conceitos (`begin()`, `end()`, `erase()`) também valem para `std::string`, que se comporta como um vetor de caracteres. Para remover pontos e traço de um CPF:

```cpp
#include <iostream>
#include <string>
#include <algorithm>   // std::remove

int main() {
    std::string cpf = "987.568.214-54";

    cpf.erase( std::remove(cpf.begin(), cpf.end(), '.'), cpf.end() );
    cpf.erase( std::remove(cpf.begin(), cpf.end(), '-'), cpf.end() );

    std::cout << cpf << '\n';   // 98756821454
    return 0;
}
```

### Como funciona o *erase-remove*

Este padrão é tão comum que tem nome: **erase-remove idiom**. Ele acontece em dois passos:

1. **`std::remove(begin, end, '.')`** não apaga nada de fato. Ele **move para a frente** todos os caracteres que **não** são `'.'` e devolve um iterador para o início da "sobra" no final:

   ```
   antes:   9 8 7 . 5 6 8 . 2 1 4 - 5 4
   depois:  9 8 7 5 6 8 2 1 4 - 5 4 5 4
                                    ▲
                                    iterador devolvido (início da sobra)
   ```

2. **`cpf.erase(iterador, cpf.end())`** apaga de fato esse trecho final, e o tamanho diminui.

O mesmo vale para um `std::vector`:

```cpp
std::vector<int> n = {1, 0, 2, 0, 3};
n.erase( std::remove(n.begin(), n.end(), 0), n.end() );   // {1, 2, 3}
```

> **C++20:** existe um atalho que faz os dois passos de uma vez: `std::erase(cpf, '.');` ou `std::erase(n, 0);`.

---

## 7. Referência rápida

| Categoria | Função | O que faz |
|---|---|---|
| **Acesso** | `v[i]` | elemento no índice `i` (sem verificação) |
| | `at(i)` | elemento no índice `i` (com verificação) |
| | `front()` | referência ao primeiro elemento |
| | `back()` | referência ao último elemento |
| **Iteradores** | `begin()` | iterador para o primeiro elemento |
| | `end()` | iterador para logo após o último (não desreferenciar!) |
| | `rbegin()` | iterador reverso para o último elemento |
| | `rend()` | iterador reverso para antes do primeiro |
| **Tamanho** | `size()` | quantidade de elementos |
| | `empty()` | `true` se estiver vazio |
| | `capacity()` | espaço reservado sem realocar |
| | `reserve(n)` | reserva espaço para pelo menos `n` elementos |
| | `resize(n)` | muda a quantidade de elementos para `n` |
| | `max_size()` | quantidade máxima teórica de elementos |
| **Modificação** | `push_back(x)` | adiciona no final |
| | `pop_back()` | remove o último |
| | `insert(pos, x)` | insere antes de `pos` |
| | `erase(pos)` / `erase(ini, fim)` | remove um elemento / intervalo |
| | `clear()` | remove todos os elementos |
| | `assign(...)` | substitui todo o conteúdo |
| | `swap(outro)` | troca o conteúdo com outro vector |

---

## Resumo

- `std::vector<T>` é um array dinâmico: cresce, diminui e sabe o próprio tamanho. Inclua `<vector>`.
- Elementos são acessados com `v[i]` (rápido, sem verificação) ou `v.at(i)` (seguro).
- `push_back` / `pop_back` adicionam e removem **no final**; não existe `'\0'` em vector.
- `size()` é quantos elementos existem; `capacity()` é quanto espaço já está reservado.
- Iteradores se comportam como ponteiros: `*it` lê o elemento e `++it` avança.
- `end()` marca o fim e **nunca** deve ser desreferenciado. Para o último elemento, use `back()`.
- Para remover valores específicos, use o padrão *erase-remove* (ou `std::erase` no C++20).
