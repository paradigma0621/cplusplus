# Notas de cursos sobre C++

Anotações de estudo sobre C++, com explicações e exemplos de código. As notas de cada curso ficam em um diretório próprio.

## Cursos

| Data | Curso | Plataforma | Notas |
|---|---|---|---|
| 2026-11-02 | [Curso de C++ Moderno para Iniciantes](https://www.udemy.com/course/curso-de-cpp-moderno-para-iniciantes/) | Udemy | [Diretório](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/) |

## Conteúdo do Curso de C++ Moderno para Iniciantes

### Fundamentos

- [Notas gerais](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/01-notas.md): compilação, namespaces, variáveis, funções, entrada de dados, laços e diretivas
- [Operadores](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/02-operadores.md)
- [Constantes](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/03-constantes.md)
- [Conversão de tipos](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/04-conversao-de-tipos.md)
- [Variáveis estáticas](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/13-variaveis-static.md)
- [Versões do C++](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/14-diferencas-cpp-versoes.md)

### Estruturas de dados e tipos

- [Arrays](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/05-arrays.md)
- [Vetores (`std::vector`)](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/07-vetores.md)
- [Structs](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/09-structs.md)
- [Enums](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/10-enums.md)

### Ponteiros e memória

- [Ponteiros](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/06-ponteiros.md)
- [`new` e `delete`](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/08-new-delete.md)
- [Smart pointers](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/15-smart-pointers.md)
- [Memória de um programa em execução](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/18-memoria.md)
- [Resumo: ponteiros e arrays](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/17-infos-importantes.md)

### Arquivos e sistema

- [Trabalhando com arquivos](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/11-trabalhando-com-arquivos.md)
- [Comandos do shell e variáveis de ambiente](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/12-comandos-shell.md)
- [Dicas do Linux](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/16-dicas-do-linux.md)

### Materiais extras

- [`misc/`](Curso%20de%20C%2B%2B%20Moderno%20para%20Iniciantes%20%28Udemy%29/misc/): programas de exemplo e links úteis

## Como compilar os exemplos

```bash
g++ -std=c++20 -Wall -Wextra main.cpp -o programa
./programa
```

Alguns exemplos usam recursos do C++20, por isso o comando inclui `-std=c++20`.
