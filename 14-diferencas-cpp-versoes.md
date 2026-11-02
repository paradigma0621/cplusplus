# Versões do C++

Existem **várias versões** da linguagem de programação C++. Cada versão é um padrão, isto é, uma especificação publicada pela ISO e desenvolvida pelo comitê ISO C++. Os compiladores, como o g++, implementam esses padrões.

- C++ 98 - primeira edição, lançada em 1998.
- C++ 03 - segunda edição, lançada em 2003.
- C++ 11 - terceira edição, lançada em 2011.
- C++ 14 - quarta edição, lançada em 2014.
- C++ 17 - quinta edição, lançada em 2017.
- C++ 20 - sexta edição, lançada em 2020.
- C++ 23 - sétima edição, publicada em 2024 como ISO/IEC 14882:2024.
- C++ 26 - concluída pelo comitê em março de 2026, sem publicação confirmada pela ISO na última verificação (novembro de 2026).

Todas essas versões têm muitas diferenças, principalmente adições à biblioteca padrão e expansão de *APIs*. Os padrões são publicados pela **ISO** (<https://www.iso.org/>), e o site da Standard C++ Foundation reúne informações sobre eles: <https://isocpp.org/>.

---

Para descobrir qual versão você está usando, imprima a macro `__cplusplus`. Os valores são:

- Antes do C++98: `__cplusplus` é `1`.
- C++98 e C++03: `__cplusplus` é `199711L`.
- C++11: `__cplusplus` é `201103L`.
- C++14: `__cplusplus` é `201402L`.
- C++17: `__cplusplus` é `201703L`.
- C++20: `__cplusplus` é `202002L`.
- C++23: `__cplusplus` é `202302L`.

Sem nenhum parâmetro, o g++ 15 usa o C++17 (`201703L`).

Para compilar em outra versão, use o parâmetro `-std=c++XX`, exemplo para compilar em C++17: `-std=c++17`. Para ver a diferença, crie um código com recursos de uma versão e tente compilar numa versão inferior. Por exemplo, `std::make_unique` existe desde o C++14 e não compila com `-std=c++11`. Para mais informações, rode: `man g++ | grep '\-std='`

> Inclua sempre os cabeçalhos do que você usa. No g++, `std::string` compila incluindo apenas `<iostream>`, mas isso é um detalhe da implementação, não uma garantia do padrão. Por isso, inclua também `<string>`.
