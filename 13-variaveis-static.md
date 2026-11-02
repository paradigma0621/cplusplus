# Variáveis locais estáticas

O termo `static` é um dos termos mais confusos na linguagem C++, em grande parte porque `static` tem significados diferentes em contextos diferentes.

Usar a palavra-chave `static` em uma variável local muda seu tempo de vida. A variável estática manterá seu valor mesmo depois de sair do escopo! Um dos usos mais comuns para variáveis locais de duração estática é para geradores de ID exclusivos.

```cpp
#include <iostream>

void increment_e_print(){
    static int value{ 1 }; // inicializada uma única vez: como uma variável global que nunca tem seu valor resetado, mas visível só nesta função
    // int value{ 1 }; // duração automática - mostraria sempre `1` apenas nos prints da main()
    
    std::cout << value << '\n';
    ++value;
} // value sai de escopo aqui, mas não é destruída: continua existindo até o fim do programa


int main(){
    // Cada vez que increment_e_print() é chamada, imprime o valor atual e, em seguida, o incrementa. Saída: 1, 2 e 3.
    increment_e_print();
    increment_e_print();
    increment_e_print();

    return 0;
}
```