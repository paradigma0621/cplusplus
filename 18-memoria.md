# O que acontece na memória quando um programa C++ roda

*Um passeio do `codigo.cpp` até a memória RAM, mostrando o que fica em cada região e como os ponteiros se encaixam nessa história.*

---

## 1. Do `codigo.cpp` ao programa em execução

Um arquivo `.cpp` não roda diretamente. Ele passa por várias etapas até virar um processo na memória:

```
codigo.cpp
   │
   ▼  1. Pré-processador   → resolve #include, #define, #ifdef... (texto puro)
   │
   ▼  2. Compilador        → traduz C++ para código de máquina (arquivo objeto .o)
   │
   ▼  3. Linker            → junta os .o com as bibliotecas (ex.: iostream) → executável
   │
   ▼  4. Loader (sistema)  → ao executar ./programa, o SO copia o executável para a RAM
   │                         e organiza a memória do processo
   ▼
processo em execução
```

Na prática, um único comando faz as três primeiras etapas:

```bash
g++ codigo.cpp -o programa   # pré-processa, compila e linka
./programa                   # o sistema operacional carrega e executa
```

É na **etapa 4** que a memória é organizada nas regiões que veremos a seguir.

---

## 2. O mapa da memória de um processo

No curso, a memória foi dividida em quatro áreas: **código, global, pilha e heap**. Na realidade, a área "global" ainda se subdivide. O mapa mais completo fica assim:

```
 endereços altos
┌─────────────────────────────┐
│           PILHA             │  variáveis locais, parâmetros, endereços de retorno
│           ▼ ▼ ▼             │  (cresce para baixo)
├─────────────────────────────┤
│                             │
│        MEMÓRIA LIVRE        │
│                             │
├─────────────────────────────┤
│           ▲ ▲ ▲             │  tudo que é criado com new
│           HEAP              │  (cresce para cima)
├─────────────────────────────┤
│  .bss    globais/estáticas  │  sem valor inicial ou iniciadas com zero   ┐
├─────────────────────────────┤                                            │ "GLOBAL"
│  .data   globais/estáticas  │  iniciadas com valor diferente de zero     ┘
├─────────────────────────────┤
│  .rodata constantes         │  literais de texto ("Oi"), constantes      ┐
├─────────────────────────────┤                                            │ "CÓDIGO"
│  .text   código             │  as instruções das funções (main, soma...) ┘
└─────────────────────────────┘
 endereços baixos
```

| Região | O que guarda | Quando é criada | Quando é destruída | Quem gerencia |
|---|---|---|---|---|
| **.text** (código) | instruções de máquina das funções | ao carregar o programa | ao fim do programa | sistema operacional |
| **.rodata** | literais de texto, constantes | ao carregar o programa | ao fim do programa | sistema operacional (somente leitura) |
| **.data** | globais e estáticas com valor inicial | ao carregar o programa | ao fim do programa | sistema operacional |
| **.bss** | globais e estáticas zeradas ou sem valor | ao carregar o programa (zeradas) | ao fim do programa | sistema operacional |
| **Heap** | objetos criados com `new` | quando você executa `new` | quando você executa `delete` | **você** (ou um *smart pointer*) |
| **Pilha** | variáveis locais e parâmetros | quando a função é chamada | quando a função retorna | o compilador, automaticamente |

---

## 3. Um `codigo.cpp` genérico

Este programa tem um pouco de tudo: globais, estática, locais, ponteiros, literal de texto, alocação dinâmica e chamada de função. Os comentários indicam onde cada coisa vai parar.

```cpp
#include <iostream>

int contador = 0;            // global iniciada com zero      → .bss
int limite = 100;            // global com valor inicial      → .data
const char* saudacao = "Oi"; // o ponteiro está em .data;
                             // o texto "Oi" está em .rodata

int soma(int a, int b){      // as instruções de soma          → .text
    int resultado = a + b;   // a, b e resultado               → pilha (frame de soma)
    return resultado;
}

int main(){                  // as instruções de main          → .text
    static int chamadas = 0; // estática local                 → .bss (vive o programa todo)
    int x = 3;               // local                          → pilha (frame de main)
    int *p = &x;             // p está na pilha e aponta para a pilha
    int *h = new int(42);    // h está na pilha e aponta para a HEAP

    contador = soma(x, *h);  // cria e destrói o frame de soma na pilha
    std::cout << contador << '\n';   // 45

    delete h;                // libera o int da heap
    h = nullptr;
    return 0;
}
```

---

## 4. A execução, passo a passo

### Passo 1: o programa é carregado (antes da `main`)

O sistema operacional copia o executável para a RAM. Antes de qualquer linha da `main` rodar, **as regiões fixas já estão prontas**:

```
.text    → instruções de soma() e main()
.rodata  → "Oi"
.data    → limite = 100,  saudacao = (endereço de "Oi")
.bss     → contador = 0,  chamadas = 0
heap     → (vazia)
pilha    → (vazia)
```

Por isso globais e estáticas **existem durante o programa inteiro** e começam zeradas quando não recebem valor.

### Passo 2: a `main` começa

Ao chamar a `main`, um **frame** (bloco de memória da função) é empilhado na pilha com as variáveis locais:

```
PILHA
┌─────────────────────────────────┐
│ frame de main                   │
│   x = 3  ◄──────────┐           │
│   p = &x  ──────────┘           │
│   h = (lixo)                    │
└─────────────────────────────────┘
```

`p` é uma variável **na pilha** cujo valor é o endereço de outra variável **na pilha** (`x`).

### Passo 3: `new int(42)`

O `new` reserva espaço na **heap** e devolve o endereço. Esse endereço é guardado em `h`, que continua na pilha:

```
PILHA                                 HEAP
┌──────────────────────┐             ┌──────────────┐
│ frame de main        │             │              │
│   x = 3              │             │   42         │ ◄─┐
│   p = &x             │             │              │   │
│   h = 0x...5320  ────┼─────────────┼──────────────┼───┘
└──────────────────────┘             └──────────────┘
```

> **Este é o ponto central da relação entre ponteiros e memória:** o **ponteiro** e o **dado apontado** podem estar em regiões diferentes. Aqui, `h` vive na pilha, mas o `int` vive na heap.

### Passo 4: chamada de `soma(x, *h)`

Um novo frame é empilhado **em cima** do frame da `main`. Os argumentos são **copiados** para os parâmetros `a` e `b`:

```
PILHA
┌───────────────────────────────────┐
│ frame de soma                     │  ← topo da pilha
│   a = 3     (cópia de x)          │
│   b = 42    (cópia de *h)         │
│   resultado = 45                  │
│   (endereço de retorno para main) │
├───────────────────────────────────┤
│ frame de main                     │
│   x = 3                           │
│   p = &x                          │
│   h = 0x...5320                   │
└───────────────────────────────────┘
```

As **instruções** de `soma` não são copiadas para a pilha. Elas continuam no `.text`. Na pilha ficam apenas os **dados** dessa chamada.

### Passo 5: `soma` retorna

O valor `45` é devolvido e o frame de `soma` é **desempilhado**. `a`, `b` e `resultado` deixam de existir. O valor é então gravado em `contador`, no `.bss`.

```
PILHA                          .bss
┌──────────────────────┐      ┌──────────────────┐
│ frame de main        │      │ contador = 45    │
│   x = 3              │      │ chamadas = 0     │
│   p = &x             │      └──────────────────┘
│   h = 0x...5320      │
└──────────────────────┘
```

### Passo 6: `delete h;` e `h = nullptr;`

O `int` da heap é liberado. O ponteiro `h` **continua existindo** na pilha, mas agora com `nullptr`, para deixar claro que não aponta para nada válido.

### Passo 7: a `main` retorna

O frame da `main` é desempilhado, o processo termina e o sistema operacional recupera **toda** a memória do processo.

---

## 5. Ponteiros atravessando regiões

Um ponteiro é só uma variável que guarda um endereço. Ele mora numa região e pode apontar para qualquer outra:

| Ponteiro | Onde o ponteiro mora | Para onde aponta |
|---|---|---|
| `p = &x` | pilha | pilha |
| `h = new int(42)` | pilha | heap |
| `saudacao = "Oi"` | .data | .rodata |
| `&soma` | (é um valor, não uma variável) | .text |

É justamente essa liberdade que gera os erros clássicos com ponteiros.

### 5.1 Ponteiro pendente (*dangling pointer*): apontar para a pilha de quem já saiu

```cpp
int* errado(){
    int local = 7;      // vive no frame de errado()
    return &local;      // devolve o endereço de algo que vai sumir
}

int main(){
    int *q = errado();  // o frame de errado() já foi desempilhado
    std::cout << *q;    // COMPORTAMENTO INDEFINIDO
}
```

`q` aponta para um pedaço da pilha que **já foi liberado** e pode ser reaproveitado pela próxima chamada de função. O g++ avisa, mesmo sem `-Wall`, mas compila.

### 5.2 Vazamento de memória (*memory leak*): esquecer a heap

```cpp
void vaza(){
    int *h = new int(42);   // o int está na heap
}                           // h (na pilha) some aqui, mas o int continua na heap!
```

Quando `vaza()` termina, o ponteiro `h` desaparece com o frame. O `int` na heap fica lá, **sem ninguém que saiba o endereço dele**, e não pode mais ser liberado. Chamada em loop, essa função consome memória até o fim do programa.

### 5.3 A solução moderna: deixar a pilha cuidar da heap

```cpp
#include <memory>

void nao_vaza(){
    auto h = std::make_unique<int>(42);   // o int está na heap
}                                         // h sai da pilha e libera a heap sozinho
```

O `std::unique_ptr` é um objeto **na pilha** que é dono de um dado **na heap**. Quando ele é destruído junto com o frame, o destrutor executa o `delete` por você. É a ideia do RAII: amarrar a vida de um recurso da heap à vida de uma variável da pilha.

---

## 6. Vendo os endereços de verdade

Dá para confirmar tudo isso imprimindo os endereços. Acrescente à `main` do programa da seção 3, antes do `delete h;`:

```cpp
std::cout << "codigo   (soma)     : " << (void*)&soma    << '\n';
std::cout << "rodata   (\"Oi\")     : " << (void*)saudacao << '\n';
std::cout << "data     (limite)   : " << &limite         << '\n';
std::cout << "bss      (contador) : " << &contador       << '\n';
std::cout << "bss      (chamadas) : " << &chamadas       << '\n';
std::cout << "heap     (*h)       : " << h               << '\n';
std::cout << "pilha    (x)        : " << &x              << '\n';
std::cout << "pilha    (p)        : " << &p              << '\n';
std::cout << "pilha    (h)        : " << &h              << '\n';
```

> O `(void*)` é necessário em dois casos. Sem ele, um `const char*` seria impresso como **texto** ("Oi") em vez de endereço. E o endereço de uma função não seria impresso como endereço: o `std::cout` mostraria `1`.

> Usamos `&soma`, e não `&main`, porque o padrão do C++ proíbe obter o endereço da `main`.

Uma execução real no Linux (g++, 64 bits) produziu:

```
codigo   (soma)     : 0x5831bacad209
rodata   ("Oi")     : 0x5831bacae004
data     (limite)   : 0x5831bacb0010
bss      (contador) : 0x5831bacb0154
bss      (chamadas) : 0x5831bacb0158
heap     (*h)       : 0x5831e0185320
pilha    (x)        : 0x7fff2c0e6634
pilha    (p)        : 0x7fff2c0e6638
pilha    (h)        : 0x7fff2c0e6640
```

Repare que a saída confirma o mapa da seção 2:

- **.text → .rodata → .data → .bss** aparecem em ordem crescente e próximos entre si (`0x5831bac...`). São as regiões fixas, carregadas do executável.
- A **heap** (`0x5831e018...`) vem logo acima delas.
- A **pilha** (`0x7fff...`) fica lá no alto, muito longe de tudo, com a memória livre no meio.
- `chamadas`, mesmo declarada **dentro** da `main`, está no `.bss`, ao lado de `contador`, e não na pilha. É o efeito do `static`.

Rodando de novo, os números mudam (`0x5d2102dd...`), mas a **ordem** se mantém. Isso acontece por causa do **ASLR**, uma proteção do sistema operacional que sorteia a posição das regiões a cada execução. Além disso, esses endereços são **virtuais**: cada processo tem seu próprio "mapa" e o sistema traduz para a RAM física por baixo dos panos.

---

## 7. Resumo

| Você escreve... | Vai para... | Vive até... |
|---|---|---|
| uma função (`int soma(...) {...}`) | `.text` | o fim do programa |
| `"um texto literal"` | `.rodata` | o fim do programa |
| `int g = 100;` (global) | `.data` | o fim do programa |
| `int g;` ou `int g = 0;` (global) | `.bss` | o fim do programa |
| `static int s;` (dentro de função) | `.bss` / `.data` | o fim do programa |
| `int x = 3;` (dentro de função) | pilha | o fim da função (ou do bloco `{}`) |
| parâmetros (`int a, int b`) | pilha | o fim da função |
| `new int(42)` | heap | o `delete` (ou o fim do *smart pointer*) |
| `int *p = ...;` (local) | o **ponteiro** na pilha | o fim da função. O **dado apontado** vive onde estiver! |

**Regras de ouro:**

1. A **pilha** se cuida sozinha, mas tudo nela morre quando a função retorna. Nunca guarde o endereço de uma local para usar depois.
2. A **heap** sobrevive às funções, mas é responsabilidade sua. Cada `new` precisa de um `delete`. Melhor ainda: use `std::unique_ptr` ou `std::shared_ptr`.
3. **Globais e estáticas** existem do início ao fim do programa.
4. Um ponteiro mora numa região e pode apontar para outra. Sempre se pergunte: **"o dado para onde estou apontando ainda existe?"**

## AP - referente à `vector`
```cpp
std::vector<int> setes(3, 7);                 // {7, 7, 7}
std::vector<std::string> v = {"Shell Script", "Web", "C++", "Linux", "BSD"};
```

> **Por baixo dos panos:** os elementos ficam **lado a lado** na memória, como num array (veja a aula de ponteiros), só que alocados na **heap**. O objeto `vector` em si, que pode estar na pilha, guarda apenas um ponteiro para esses dados, o tamanho e a capacidade. Quando você o destrói, a memória da heap é liberada automaticamente.
