# Notas de cursos sobre C++

Anotações de estudo sobre C++, com explicações e exemplos de código.

## Cursos

| Data | Curso | Plataforma |
|---|---|---|
| 2026-11-02 | [Curso de C++ Moderno para Iniciantes](https://www.udemy.com/course/curso-de-cpp-moderno-para-iniciantes/) | Udemy |

## Conteúdo

### Fundamentos

- [Notas gerais](01-notas.md): compilação, namespaces, variáveis, funções, entrada de dados, laços e diretivas
- [Operadores](02-operadores.md)
- [Constantes](03-constantes.md)
- [Conversão de tipos](04-conversao-de-tipos.md)
- [Variáveis estáticas](13-variaveis-static.md)
- [Versões do C++](14-diferencas-cpp-versoes.md)

### Estruturas de dados e tipos

- [Arrays](05-arrays.md)
- [Vetores (`std::vector`)](07-vetores.md)
- [Structs](09-structs.md)
- [Enums](10-enums.md)

### Ponteiros e memória

- [Ponteiros](06-ponteiros.md)
- [`new` e `delete`](08-new-delete.md)
- [Smart pointers](15-smart-pointers.md)
- [Memória de um programa em execução](18-memoria.md)
- [Resumo: ponteiros e arrays](17-infos-importantes.md)

### Arquivos e sistema

- [Trabalhando com arquivos](11-trabalhando-com-arquivos.md)
- [Comandos do shell e variáveis de ambiente](12-comandos-shell.md)
- [Dicas do Linux](16-dicas-do-linux.md)

### Materiais extras

- [`misc/`](misc/): programas de exemplo e links úteis

## Como compilar os exemplos

```bash
g++ -std=c++20 -Wall -Wextra main.cpp -o programa
./programa
```

Alguns exemplos usam recursos do C++20, por isso o comando inclui `-std=c++20`.
