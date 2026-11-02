# Caminho dos cabeçalhos do sistema
Os cabeçalhos das bibliotecas do sistema ficam no caminho: `/usr/include/`. Já o código compilado das bibliotecas fica em diretórios como `/usr/lib/`.

Ou seja, se quisermos encontrar o arquivo do cabeçalho `<iostream>`, basta pesquisarmos nesse diretório, exemplo:
`find /usr/include/ -name "iostream"`

Como esse cabeçalho é padrão do C++, ele também pode estar no diretório do compilador. O caminho exato muda conforme a distribuição e a versão do compilador. Para descobrir os diretórios em que o compilador procura os cabeçalhos, rode o comando abaixo e veja a lista depois de `#include <...> search starts here:`:
```bash
cpp -x c++ -v /dev/null -o /dev/null

# Ou, para procurar o arquivo diretamente:

find /usr/include/c++ /usr/lib/gcc -name "iostream"
```

No Ubuntu com g++ 15, o resultado é `/usr/include/c++/15/iostream`.

Para saber se o arquivo contém, por exemplo, a declaração do `cout` que usamos, rode:
```bash
find /usr/include/c++ /usr/lib/gcc -name "iostream" -exec grep 'cout' {} \;
```

O comando `c++` costuma ser um link simbólico que leva ao mesmo binário do `g++`. Já o `cpp` leva a outro binário, o do pré-processador. Para conferir para onde cada um aponta, rode:
```bash
readlink -f "$(command -v g++)"
readlink -f "$(command -v c++)"
readlink -f "$(command -v cpp)"
```

Você também pode descobrir quais bibliotecas o binário que você criou usa, exemplo de comando:
```bash
ldd nome_do_binario
```

# Executar no bash para ver lista de caracteres ASCII
```bash
man ascii
```

# Mostrando o valor retornado pelo programa
Para mostrar o número retornado pelo `main()` (`return x`), execute no bash:
```bash
./programa
echo $?
```

# Mostrando todas as variáveis de ambiente de um terminal
```bash
env
```
