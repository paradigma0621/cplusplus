# Trabalhando com arquivos em C++

Existem 3 classes no C++ que manipulam arquivos, todas no cabeçalho `<fstream>`:

- `ifstream`: **lê** dados de um arquivo;
- `ofstream`: **escreve** dados em um arquivo;
- `fstream`: **lê e escreve** dados em um arquivo.

## Para ler um arquivo com C++:

1. Incluir `<fstream>`, que já disponibiliza as três classes: `#include <fstream>`
2. Declarar uma variável para a linha, exemplo: `std::string linha;`
3. Abrir o arquivo (*input file*), exemplo: `std::ifstream arquivo("file.txt");`
4. Verificar se o arquivo foi aberto: `if( arquivo.is_open() ){}`
5. Gerar um loop por linha, exemplo: `while( std::getline( arquivo , linha ) ){}`
6. Fechar o arquivo: `arquivo.close();` (se você não fechar, o destrutor fecha ao sair do escopo)

### Exemplo

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main( int argc , char **argv ){

  std::string linha;
  bool numero {false};
  std::string param;
  int i = {1};

  if( argc > 1 ){
    param = argv[1];
    if( param == "--numero" || param == "-n" ){
      numero = true;
    }
  }

  std::ifstream arquivo("arquivo.txt");

  if( arquivo.is_open() ){

    while( std::getline( arquivo , linha ) ){
      if( numero ){
        std::cout << i << " │ " << linha << '\n';
        i++;
      }else{
        std::cout << linha << '\n';
      }
    }

    arquivo.close();

  }else{
    std::cout << "Não foi possível abrir o arquivo." << '\n';
  }

  return 0;
}
```

## Para gravar em um arquivo com C++:

1. Usar `std::ofstream` (*output file*);
2. Direcionar o conteúdo para o arquivo: `arquivo << conteudo << '\n';`
3. Fechar o arquivo: `arquivo.close();`
4. Para anexar ao final do arquivo, em vez de sobrescrevê-lo, usar o parâmetro: `std::ios_base::app`

### Exemplo

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main(){

  std::string conteudo, outro;

  std::ofstream arquivo;

  arquivo.open("arquivo.txt", std::ios_base::app);

  if( !arquivo.is_open() ){
    std::cout << "Não foi possível abrir o arquivo." << '\n';
    return 1;
  }

  std::cout << "Informe uma linha: ";
  std::getline( std::cin, conteudo );
  std::cout << "Informe uma nova linha: ";
  std::getline( std::cin, outro );

  arquivo << conteudo << '\n';
  arquivo << outro << '\n';

  arquivo.close();

  std::cout << "Dados gravados com sucesso!" << '\n';
  return 0;
}
```
