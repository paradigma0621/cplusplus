# Executar Comandos da Shell em C++ e obter Variáveis de Ambiente

## Obtendo variáveis de ambiente com C++

Para "pegar" variáveis de ambiente do sistema, basta incluir o cabeçalho `<cstdlib>` ou `<stdlib.h>`. No C++, as bibliotecas herdadas da linguagem C têm o mesmo nome, porém **com o `c` na frente e sem o `.h`**, e essa é a forma recomendada. Também é possível usar o nome original do C, com o `.h` no final.

Depois, use a função `getenv()`, informando o nome da variável como ela aparece no ambiente do sistema. A função retorna o valor da variável, ou `nullptr` se ela não existir.

Mostrar o nome de usuário:

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){

    const char* usuario = getenv("USER");

    if( usuario != nullptr ){
        cout << "USUÁRIO: " << usuario << endl;
    }else{
        cout << "A variável USER não está definida." << endl;
    }

    return 0;

}
```

## Executar comandos do Shell em C++

Para executar comandos do Shell, é muito simples: basta usar a função `system()`, também da biblioteca *cstdlib*. Não a use vazia (não irá compilar). Exemplo que mostra a resolução de tela do seu monitor:

Certifique-se de que o comando `xdpyinfo` está instalado.

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){

    system("echo -n 'SUA RESOLUÇÃO DE TELA É: '; xdpyinfo | grep 'dimensions:' | sed 's/.*://;s/pixels.*//;s/ //g;'");
    return 0;

}
```

# Forma fácil de obter as declarações das funções (para colocar nas libs `.h`)

```bash
grep -E '^[a-z].*\)\s*\{\s*$' project.cpp | grep -v '^int main' | sed -E 's/\s*\{\s*$/;/'

# Exemplo de saída:
#std::string returnBinaryString(int number);
#double returnDecimal(std::string binary_number);
```

O comando só encontra funções cujo `{` termina a linha. Funções de uma linha só, como `int soma(int a, int b){ return a + b; }`, ficam de fora.

# Comando para compilar programa que usa ncurses

```bash
g++ main.cpp -lncurses -ltinfo -o nome-do-app
```
