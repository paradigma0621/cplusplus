# Compilando um programa

```bash
g++ main.cpp -o a
```

As extensões do C++ são:

- **Código-fonte:** `.C`, `.cc`, `.cpp`, `.cxx`, `.c++`
- **Cabeçalhos:** `.h`, `.hh`, `.hpp`, `.hxx`, `.h++`

## Flags do g++

### `-v`

```bash
g++ -v main.cpp
```

Traz várias informações **importantes** sobre o compilador e as etapas da compilação, como a versão, os diretórios de busca e o modelo de threads. Ex.: `Thread model: posix`.

### `-Werror`

```bash
g++ -Werror programa.cpp -o programa
```

**O que faz a flag `-Werror` do g++?** Transforma todos os avisos (warnings) em erros, fazendo a compilação falhar se houver algum aviso.

### `-Wall`

```bash
g++ -Wall -Werror programa.cpp -o programa
```

> AP/Pro: o `-Wall` ativa um conjunto amplo de warnings, e o `-Werror` transforma em erro os warnings ativos. Juntas, qualquer warning do `-Wall` faz a compilação falhar.

O executável se chama `programa`, sem extensão, porque `.o` indica um arquivo objeto, gerado com a flag `-c`.

# Namespaces

Um `namespace` agrupa nomes para evitar conflitos entre eles. Ele lembra o `package` do Java, mas não é equivalente: não está ligado à estrutura de pastas nem controla o acesso aos nomes.

## Declarando um namespace

```cpp
namespace meu_app {
  int total = 0;
}

// Fora do namespace, o nome é acessado assim: meu_app::total
```

## Usando os nomes de um namespace

Podemos indicar o namespace em cada uso:

```cpp
#include <iostream>
// Comentário 1
int main(){ // função main obrigatória
  std::cout << "Olá, Mundo!" << '\n'; // Imprime o conteúdo
  return 0;
}
```

ou trazer todos os nomes dele para o arquivo com `using namespace`:

```cpp
#include <iostream>
using namespace std;

int main(){ // função main obrigatória
  cout << "Olá, Mundo!" << '\n'; // Imprime o conteúdo
  return 0;
}
```

# Variáveis

Tamanhos e valores de alguns tipos nas plataformas de 64 bits mais comuns (o programa `misc/tipos_de_dados_com_seus_tamanhos.cpp` mostra os tamanhos na sua máquina):

| Tipo | Tamanho | Valores |
|---|---|---|
| `char` | 1 byte | De -128 a 127 com sinal. Em algumas plataformas, como ARM, `char` é sem sinal por padrão e vai de 0 a 255. Se você precisa de uma faixa garantida, use `signed char` ou `unsigned char`. |
| `int` | 4 bytes | De -2.147.483.648 a 2.147.483.647. |
| `double` | 8 bytes | 15 dígitos significativos (na prática, de 15 a 17). |

## `::`

Em `std::cout << "Olá,..."`, o `::` é chamado de operador de resolução de escopo.

## Inicialização de variáveis

Inicializar é dar um valor à variável no momento em que ela é criada. Isso é diferente de atribuir, que é trocar o valor de uma variável que já existe.

Em muitos lugares você verá os termos **lvalue** e **rvalue**. Os nomes vêm de *left* e *right*, os lados de uma atribuição, mas a ideia é outra: um lvalue identifica um objeto na memória, como uma variável, enquanto um rvalue é um valor temporário, como `10` ou `x + 1`.

Existem 3 formas principais de inicializar uma variável:

| Forma | Exemplo |
|---|---|
| Inicialização de cópia | `int x = 10;` |
| Inicialização direta | `int x ( 10 );` |
| Inicialização uniforme | `int x { 10 };` |

Para tipos simples como `int`, as três têm o mesmo custo, e os compiladores atuais costumam eliminar a cópia também em objetos. A vantagem da inicialização uniforme não é o desempenho, e sim a segurança, pois ela rejeita conversões com perda de dados:

```cpp
int a = 3.9;    // compila, e a vale 3
int b ( 3.9 );  // compila, e b vale 3
int c { 3.9 };  // ERRO de compilação: conversão com perda de dados
```

Por isso, prefira a inicialização uniforme sempre que possível.

É possível (e preferível) inicializar uma variável sempre que a definirmos. Caso não haja um valor pré-definido, inicialize de forma vazia, exemplos:

```cpp
double z {};              // 0.0
char gun {};              // '\0'
int x {};                 // 0
std::string palavra {};   // texto vazio
```

> **Cuidado:** `int x();` não cria uma variável. O compilador entende como a declaração de uma função sem parâmetros que retorna `int`.

A inicialização uniforme também aceita o sinal de `=` e continua rejeitando conversões com perda: `double z = { 36.09 };`.

# Funções
## Protótipo

**Protótipo** é a declaração de uma função sem o corpo. Ele informa ao compilador o nome da função, o tipo de retorno e os tipos dos parâmetros, e termina com `;`.

```cpp
#include <iostream>

int soma(int a, int b);   // protótipo (declaração)

int main() {
    std::cout << soma(2, 3);  // o compilador já conhece soma
}

int soma(int a, int b) {  // definição (com o corpo)
    return a + b;
}
```

### Para que serve
O compilador lê o arquivo de cima para baixo e precisa conhecer uma função antes de ela ser chamada. Sem o protótipo acima, a chamada em `main` daria erro, porque `soma` só é definida depois. Ou seja: em C++, a ordem de declaração é relevante.

O protótipo permite:
- **Definir as funções em qualquer ordem:** `main` pode vir antes das outras funções, por exemplo.
- **Separar declaração e implementação:** os protótipos ficam no `.h`/`.hpp` e as definições no `.cpp`. Quem inclui o header pode chamar as funções sem ver o corpo delas.
- **Verificar as chamadas:** o compilador confere o número e os tipos dos argumentos, além do uso do retorno.

### Detalhes
Os nomes dos parâmetros são opcionais no protótipo, então estas duas formas são equivalentes:

```cpp
int soma(int a, int b);
int soma(int, int);
```

Mesmo assim, manter os nomes costuma ajudar na leitura.

# Compilando múltiplos arquivos
Quando usamos protótipos, geralmente colocamos o protótipo em um arquivo `.h` e a definição da função em um arquivo `.cpp` de mesmo nome. Ou seja, o nosso código ficaria assim, em resumo:

```cpp
// main.cpp
#include <iostream>
#include "produto.h"
int main(){
 std::cout << "O produto de 9 x 9 é: " << produto(9, 9) << '\n';
 return 0;
}
//----------------------------------------------------------------

// produto.h
#ifndef PRODUTO_H   // proteção explicada na seção "Diretivas"
#define PRODUTO_H

int produto( int x, int y );

#endif

//----------------------------------------------------------------

// produto.cpp
#include "produto.h"

int produto( int x, int y ){
 return x * y;
}
```

E compilamos somente os `.cpp`:
```bash
g++ main.cpp produto.cpp -o binario_final
```

## Obs: cabeçalhos da biblioteca padrão com `.h` são do C
A convenção atual é esta:

| Forma | Origem | Namespace |
|---|---|---|
| `<stdio.h>`, `<math.h>` | Cabeçalho do **C** | Nomes no escopo global (`printf`) |
| `<cstdio>`, `<cmath>` | Mesmo cabeçalho do C, **adaptado ao C++** (prefixo `c`, sem `.h`) | Nomes em `std` (`std::printf`) |
| `<iostream>`, `<vector>` | Biblioteca **própria do C++** | Nomes em `std` |

**Por que ficou assim:** O padrão C++98 definiu os cabeçalhos da biblioteca do C++ sem `.h`. Os cabeçalhos herdados do C ganharam uma versão com prefixo c (`<cstdio>`). As formas com `.h` continuaram existindo para manter compatibilidade com código C. 

Podemos usar as bibliotecas do C no C++. Além da forma original com `.h`, elas existem em versão C++: basta colocar `c` na frente do nome e tirar o `.h`, como `stdio.h` → `cstdio`, que é a forma recomendada.

**Na prática:**
- Se você vê `.h` num cabeçalho da biblioteca padrão, ele é do C.
- Em C++, prefira `<cstdio>` a `<stdio.h>`.
- `<iostream.h>` era do C++ de antes da padronização e não existe mais.

A regra vale só para a biblioteca padrão. Cabeçalhos de projetos e de bibliotecas de terceiros escritos em C++ costumam usar `.h` ou `.hpp`, como `#include "minha_classe.h"`.

**Vendo o código completo de um arquivo após o pré-processamento**

O comando `cpp` (C PreProcessor) executa só a primeira etapa da compilação, o **pré-processamento**:

```bash
cpp main.cpp
```

Equivale a:

```bash
g++ -E main.cpp
```

Ele mostra o arquivo como o compilador vai recebê-lo. Todas as diretivas `#` são resolvidas:

- cada `#include` é substituído pelo conteúdo do cabeçalho correspondente, de forma recursiva;
- as macros (`#define`) são expandidas;
- os comentários são removidos.

O resultado é um único arquivo, a *unidade de tradução*, com o seu código e o de todos os cabeçalhos incluídos. No g++ 15, só incluir `<iostream>` já gera cerca de 37 mil linhas.

Como a saída é grande, vale salvá-la num arquivo:

```bash
cpp main.cpp > main.ii      # .ii é a extensão usual de C++ pré-processado
cpp -P main.cpp > main.ii   # -P remove as linhas de marcação "# 1 ..."
```

Atenção: aparecem os **cabeçalhos** (declarações, templates, funções inline), não o código compilado das bibliotecas. Esse código já está pronto em arquivos como `libstdc++.so` e só entra em cena na etapa de *linkagem*.

# Declaração da `main()` com argumentos de linha de comando

## Formas equivalentes
```cpp
int main(int argc, char** argv)   // Modo 1: ponteiro para ponteiro
int main(int argc, char* argv[])  // Modo 2: array de ponteiros
```
As duas são **idênticas** para o compilador. Quando um array é passado como parâmetro de função, ele vira um ponteiro, então `char* argv[]` é o mesmo que `char** argv`.

- `argc` (*argument count*): quantidade de argumentos, **contando o nome do programa**.
- `argv` (*argument vector*): os argumentos, cada um como string no estilo C (`char*`).
  - `argv[0]` → normalmente, o nome do programa
  - `argv[1]` até `argv[argc - 1]` → argumentos passados pelo usuário
  - `argv[argc]` → sempre `nullptr`

## Obs: converta `argv[i]` para `std::string`
`argv[i]` é um `char*` e **não** um `std::string`. Por isso ele não tem métodos como `.begin()`, `.end()`, `.erase()` e `.size()`, e usar esses métodos direto nele **não compila**.

A solução é copiar o argumento para um `std::string`:
```cpp
#include <algorithm>  // std::remove
#include <string>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {        // começa em 1 para pular o nome do programa
        std::string cpf = argv[i];          // char* → std::string
        cpf.erase(std::remove(cpf.begin(), cpf.end(), '.'), cpf.end()); // remove os '.'
    }
}
```

# Coletando dados informados pelo usuário

## Inputs

Em determinadas ocasiões, deseja-se coletar dados. Para isso, usamos o `std::cin`, redirecionando para uma variável:

```cpp
char letra {};
std::cout << "Informe uma letra: ";
std::cin >> letra;
std::cout << "A letra que você digitou foi: " << letra << "\n";
```

No entanto, o operador `>>` ignora os espaços em branco iniciais e para de ler no primeiro espaço, tabulação ou quebra de linha, então ele lê uma palavra de cada vez. Para ler uma frase inteira, o C++ oferece a `getline`.

A `getline` lê até encontrar o delimitador (por padrão, a quebra de linha) e guarda o texto lido em uma variável. O delimitador é retirado do stream e descartado, sem ser armazenado.

Ela existe em 2 formas, como detalhado abaixo:

- `std::cin.getline(...)`: função-membro de `std::cin`, usada com array de `char`;
- `std::getline(...)`: função livre, usada com `std::string`.

### Capturando conjunto de caracteres em array de char
```cpp
#include <iostream>

int main(){
    char frase[99];
    std::cout << "Digite uma frase: ";
    std::cin.getline( frase , sizeof(frase) );
    std::cout << "A frase que você digitou foi: " << frase << '\n';
    return 0;
}
```

Com `std::cin >> frase`, a entrada "duas palavras" guardaria só "duas".

### Capturando conjunto de caracteres em string
```cpp
#include <iostream>
#include <string>

int main(){

  std::string frase;

  std::cout << "Digite uma frase: ";
  std::getline( std::cin , frase );
  std::cout << "A frase que você digitou foi: " << frase << '\n';
  return 0;
}
```

Nas duas formas, a leitura pega a linha inteira, com os espaços, até o Enter.

# Usando Range em switch

O `case 1 ... 8` é uma **extensão do GNU**, aceita pelo g++, e não faz parte do C++ padrão. Por isso, pode não compilar em outros compiladores, e o g++ avisa se você usar a flag `-pedantic`.

```cpp
#include <iostream>

int main(){
  int num = 9;

  switch( num ){
    // Não se usam parênteses aqui, e os espaços ao redor de "..." são obrigatórios
    case 1 ... 8:
      std::cout << "SWITCH: 'num' está entre 1 e 8." << '\n';
      break;

    case 9:
      std::cout << "SWITCH: 'num' é IGUAL a nove." << '\n';
      break;

    // Este intervalo não pode se sobrepor aos anteriores
    case 10 ... 1000:
      std::cout << "SWITCH: 'num' está entre 10 e 1000." << '\n';
      break;

    default:
      std::cout << "SWITCH: 'num' está fora dos intervalos." << '\n';
      break;
  }

  std::cout << ( num > 9 ? "TERNARY: É maior que 9!" : "TERNARY: É MENOR ou IGUAL a nove." ) << '\n';

  return 0;
}
```

# O `for` de intervalo (*range-based for*)

Se você vem do Java, já conhece esta forma de laço. É o *enhanced for*, ou *for-each*:

```java
// Java
String[] nomes = {"Ana", "Bruno", "Carla"};
for (String nome : nomes) {
    System.out.println(nome);
}
```

Em C++ (desde o C++11) a sintaxe é praticamente a mesma:

```cpp
// C++
std::string nomes[] = {"Ana", "Bruno", "Carla"};
for (std::string nome : nomes) {
    std::cout << nome << '\n';
}
```

Lê-se "para cada `nome` em `nomes`". Você não precisa de índice nem de condição de parada, e não corre o risco de errar o tamanho do array.

## `auto`: deixe o compilador deduzir o tipo

Como no `var` do Java 10+, você pode deixar o compilador descobrir o tipo:

```cpp
for (auto nome : nomes) { ... }   // nome é deduzido como std::string
```

## A grande diferença: cópia vs. referência

Este é o ponto em que quem vem do Java mais tropeça.

Em Java, uma variável de objeto é sempre uma **referência**. No `for (String nome : nomes)`, `nome` aponta para o mesmo objeto que está no array e nada é copiado.

Em C++, variáveis guardam o **valor**. No `for (auto nome : nomes)`, cada elemento é **copiado** para `nome`. Com `std::string`, `std::vector` ou objetos grandes, isso custa memória e tempo à toa.

Para controlar esse comportamento, você escolhe a forma da variável do laço:

| Forma           | O que acontece                        | Quando usar                              |
| --------------- | ------------------------------------- | ---------------------------------------- |
| `auto x`        | copia cada elemento                   | tipos pequenos (`int`, `char`, `double`) |
| `const auto& x` | referência somente leitura, sem cópia | **padrão para objetos**: só ler          |
| `auto& x`       | referência que permite alterar        | modificar os elementos no lugar          |

```cpp
std::string nomes[] = {"Ana", "Bruno", "Carla"};

// Só ler, sem cópias (o jeito idiomático)
for (const auto& nome : nomes) {
    std::cout << nome << '\n';
}

// Modificar os elementos do próprio array
for (auto& nome : nomes) {
    nome += "!";            // altera o array original
}
// nomes agora é {"Ana!", "Bruno!", "Carla!"}
```

> **Comparação com Java:** em Java, `for (int n : numeros) { n = 0; }` não altera o array, porque `n` é uma cópia. Em C++ também não altera **se** você usar `auto n`. Mas com `auto& n` a atribuição muda o array de verdade. O Java não tem nada equivalente no for-each.

### Onde funciona

O `for` de intervalo funciona com arrays e com qualquer tipo que tenha começo e fim (`begin()` e `end()`). É o equivalente da interface `Iterable` do Java.

```cpp
// Arrays estilo C
int numeros[] = {11, 2, 9, 17};
for (int n : numeros) { ... }

// std::vector (equivalente ao ArrayList)
std::vector<int> v = {1, 2, 3};
for (int n : v) { ... }

// std::string, caractere por caractere
std::string palavra = "C++";
for (char c : palavra) { ... }

// Lista literal direto no laço
for (int n : {10, 20, 30}) { ... }

// std::map (equivalente ao TreeMap), com structured bindings (C++17)
std::map<std::string, int> idades = {{"Ana", 30}, {"Bruno", 25}};
for (const auto& [nome, idade] : idades) {
    std::cout << nome << " tem " << idade << " anos\n";
}
```

O último exemplo substitui o `for (Map.Entry<String, Integer> e : mapa.entrySet())` do Java, com bem menos texto.

### Cuidados

1. **Array passado para função perde o tamanho.** Um array estilo C passado como parâmetro vira um ponteiro, e o `for` de intervalo deixa de funcionar com ele. Use `std::vector` ou `std::array`, que sempre sabem o próprio tamanho.

   ```cpp
   void imprime(int arr[]) {
       for (int n : arr) { }   // ERRO de compilação: arr é só um ponteiro
   }
   ```

2. **Não adicione nem remova elementos durante o laço.** Em Java isso lança `ConcurrentModificationException`. Em C++ nada avisa: se a operação invalidar os iteradores, como ocorre em um `std::vector`, é *comportamento indefinido*, e o programa pode funcionar, travar ou produzir lixo.

3. **Não há índice.** Se precisar da posição, use o `for` clássico, que é igual ao do Java:

   ```cpp
   for (int i = 0; i < 4; ++i) {
       std::cout << i << ": " << numeros[i] << '\n';
   }
   ```

   No C++20 também dá para declarar um contador dentro do próprio `for` de intervalo:

   ```cpp
   for (int i = 0; const auto& nome : nomes) {
       std::cout << i++ << ": " << nome << '\n';
   }
   ```

### Resumo para quem vem do Java

- A sintaxe `for (tipo x : colecao)` é a mesma.
- `auto` faz o papel do `var`.
- **Use `const auto&` por padrão** com objetos, para evitar cópias.
- Use `auto&` quando quiser alterar os elementos, algo que o Java não permite no for-each.
- Use `auto` (cópia) só com tipos pequenos, como `int` e `char`.

---

# Diretivas

Elas são processadas pelo pré-processador, antes da compilação do código propriamente dita. De uma maneira geral, elas indicam ações que devem ser feitas com o código antes de ele ser compilado.

Exemplos de diretivas:

`#include`, `#define`, `#ifdef`, `#ifndef`, `#else`, `#endif`, `#if`, `#elif`, `#pragma`, `#line`, `#error`, `#undef` ...

É comum ver `#ifndef`/`#define`/`#endif` juntos e concluir que essas diretivas só servem para controlar declarações de `#define`. **Isso não é verdade.**

As diretivas condicionais (`#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, `#endif`) trabalham sobre o **texto do código-fonte**, antes da compilação. O pré-processador avalia a condição e:

- se ela for verdadeira, **mantém** todas as linhas entre a diretiva e o `#endif`;
- se for falsa, **apaga** essas linhas. O compilador nem chega a vê-las.

A **condição** depende de uma macro estar ou não definida. Já o **bloco** controlado pode conter **qualquer coisa**: `#include`, variáveis, funções, classes inteiras, comandos dentro do `main`, outras diretivas e até o arquivo inteiro.

## Exemplos de escopo

**1. Incluir um arquivo condicionalmente**

```cpp
#ifndef TEST
#include "fdir.h"      // só é incluído se TEST não estiver definido
#endif
```

**2. Trechos dentro de uma função**

```cpp
int main(){
#ifdef TEST
  std::cout << "TESTE DEFINIDO" << '\n';
#else
  std::cout << "Não definido" << '\n';
#endif
  return 0;
}
```

**3. Funções ou classes inteiras**

```cpp
#ifdef DEBUG
void log(const std::string& msg){
  std::cerr << "[DEBUG] " << msg << '\n';
}
#else
void log(const std::string&){}   // versão vazia em produção
#endif
```

**4. Código específico de cada sistema operacional**

```cpp
#include <cstdlib>   // std::system

#ifdef _WIN32
  #include <windows.h>
  void limpar_tela(){ system("cls"); }
#elif defined(__linux__)
  void limpar_tela(){ system("clear"); }
#endif
```

**5. Um arquivo inteiro (include guard)**

O clássico `#ifndef`/`#define`/`#endif` de um header é um caso particular disso. O "bloco" é o arquivo todo, e o `#define` é só o mecanismo que evita que o arquivo seja incluído duas vezes:

```cpp
// fdir.h
#ifndef FDIR_H
#define FDIR_H

void fdir();     // todo o conteúdo do header fica protegido

#endif
```

**6. Desativar um bloco grande de código**

```cpp
#if 0
  // tudo aqui é ignorado, inclusive outros comentários /* ... */
#endif
```

## De onde vem a definição da macro?

A macro testada não precisa ser criada com `#define` no próprio código. Você pode defini-la **na hora de compilar**:

```bash
g++ -DTEST main.cpp -o main     # equivale a ter "#define TEST 1" no topo
g++ main.cpp -o main            # TEST não definido
```

Assim, você gera versões diferentes do programa (teste, debug, produção) **a partir do mesmo código-fonte, sem editá-lo**.

Algumas macros já vêm predefinidas pelo compilador, como `_WIN32`, `__linux__` e `__cplusplus`. Com `#if` dá até para comparar valores:

```cpp
#if __cplusplus >= 201703L
  // código que usa recursos do C++17
#endif
```

## Resumo

> As diretivas condicionais funcionam como um **filtro de texto** aplicado antes da compilação. A condição testa macros, mas o que fica entre `#if...` e `#endif` pode ser qualquer trecho de código, de uma única linha até um arquivo inteiro.

# Conversões de tipos
## De char para int
### 1. Obter o código ASCII do caractere
```cpp
char c = 'A';
int codigo = static_cast<int>(c);  // 65
int codigo2 = c;                   // 65 (conversão implícita, também funciona)
```
`static_cast<int>` é a forma recomendada no C++ moderno, porque deixa explícito que a conversão é intencional. Evite o cast no estilo C, `(int)c`.

### 2. Obter o valor numérico de um dígito ('7' → 7)
```cpp
char c = '7';
int n = c - '0';  // 7
```
Funciona porque os dígitos `'0'` a `'9'` são consecutivos na tabela ASCII (`'0'` = 48, `'7'` = 55, e 55 − 48 = 7).

⚠️ Sem conferir antes, `'A' - '0'` dá 17, um valor sem sentido. Valide o caractere primeiro:
```cpp
#include <cctype>  // std::isdigit

if (std::isdigit(static_cast<unsigned char>(c))) {
    int n = c - '0';
}
```
O `static_cast<unsigned char>` é necessário porque passar um `char` negativo (acentos, por exemplo) para `std::isdigit` é comportamento indefinido.

### 3. De string (ou char*) para int
```cpp
#include <string>

std::string s = "123";
int n = std::stoi(s);        // 123

int m = std::stoi(argv[1]);  // também aceita char*, ex.: argumentos da main
```
`std::stoi` lança exceção se a conversão falhar:
- `std::invalid_argument`: o texto não é um número (ex.: `"abc"`)
- `std::out_of_range`: o número não cabe em um `int`

```cpp
try {
    int n = std::stoi(s);
} catch (const std::exception& e) {
    std::cerr << "Conversão inválida: " << e.what() << '\n';
}
```

### 4. Usando `atoi` (herança do C)
```cpp
#include <cstdlib>  // std::atoi

int n = std::atoi("123");      // 123
int m = std::atoi(argv[1]);    // direto do char*, ex.: argumentos da main

std::string s = "456";
int k = std::atoi(s.c_str());  // com std::string precisa do .c_str()
```
`atoi` (*ASCII to integer*) recebe um `const char*`. Por isso uma `std::string` precisa passar pelo `.c_str()`.

#### Comportamento em casos problemáticos
| Entrada | `std::atoi` | `std::stoi` |
|---|---|---|
| `"123"` | 123 | 123 |
| `"  42"` | 42 (ignora espaços no início) | 42 |
| `"12abc"` | 12 (para no primeiro caractere inválido) | 12 |
| `"abc"` | **0** (sem nenhum aviso) | lança `std::invalid_argument` |
| `"0"` | 0 | 0 |
| `"99999999999"` | **comportamento indefinido** | lança `std::out_of_range` |

⚠️ **O problema do `atoi`:** ele **não tem como indicar erro**. Com `"abc"` ele devolve `0`, e com `"0"` também devolve `0`, então não dá para saber se a entrada era inválida ou se era zero mesmo. Com um número grande demais (overflow), o comportamento é indefinido.

#### Quando usar?
- `atoi`: só quando você tem **certeza** de que a entrada é válida (testes rápidos, código legado).
- `std::stoi`: quando a entrada vem do usuário e você quer tratar erros com exceções.
- `std::from_chars` (C++17): a opção mais rápida e segura. Não lança exceção e não aloca memória:

```cpp
#include <charconv>

std::string s = "123";
int n{};
auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), n);

if (ec == std::errc{}) {
    // conversão OK: n == 123
} else if (ec == std::errc::invalid_argument) {
    // não era um número
} else if (ec == std::errc::result_out_of_range) {
    // número grande demais para int
}
```

Resumindo: `atoi` é prático, mas falha em silêncio. Em C++ moderno, prefira `std::stoi` ou `std::from_chars`.

# Sobrecarga e ponteiros de funções

**Sobrecarga de funções:** ocorre quando o código possui funções com o mesmo nome, mas com tipos ou quantidade de parâmetros diferentes. O compilador escolhe a versão certa pelos argumentos da chamada.

```cpp
int dobro(int x)       { return x * 2; }
double dobro(double x) { return x * 2; }
```

**Ponteiro de função:** é um ponteiro que guarda o endereço de uma função, o que permite chamá-la depois ou passá-la como argumento.

```cpp
int soma(int a, int b){ return a + b; }

int (*operacao)(int, int) = soma;   // operacao aponta para soma
int resultado = operacao(2, 3);     // 5
```

**Função que retorna ponteiro:** é outra coisa. Nesse caso, o ponteiro é o valor retornado, e basta indicá-lo no tipo de retorno: `int* cria_numero();`.

# Texto de várias linhas em um único `cout`

Textos literais separados apenas por espaços ou quebras de linha são unidos pelo compilador. Assim, não é preciso repetir o `<<` em cada linha:

```cpp
void help(){
  std::cout << "Uso: ./a.out [--parametros] [numero]\n"
               " --dec2bin Para converter decimal para binário\n"
               " --bin2dec Para converter binário para decimal\n";
}
```

# Anjuta e a geração de arquivos do Autotools

O **Anjuta** cria automaticamente os arquivos de um projeto baseado em **Autotools**, sem que eles precisem ser escritos à mão. Ao iniciar um projeto pelo assistente, a IDE gera a estrutura inicial, com arquivos como:

- **`configure.ac`:** define o nome e a versão do projeto, além das verificações do sistema, como compilador e bibliotecas.
- **`Makefile.am`:** descreve em alto nível o que deve ser compilado e quais arquivos fazem parte do programa.
- **`autogen.sh`:** executa as ferramentas do Autotools para gerar os arquivos seguintes.

## Como esses arquivos viram o `configure` e o `Makefile`

```text
configure.ac --(autoconf)--> configure
Makefile.am  --(automake)--> Makefile.in
Makefile.in  --(configure)-> Makefile
```

Depois, o `make` usa o `Makefile` para compilar o projeto. O Anjuta permite executar essas etapas pela própria interface.

## Manutenção

Ao adicionar arquivos-fonte ou alvos pelo gerenciador de projetos, o Anjuta atualiza o `Makefile.am`, o que evita editar essas listas manualmente.
