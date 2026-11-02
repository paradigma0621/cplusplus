#include<iostream>
using namespace std;
 
int main(){
    cout << "Tamanho de char : " << sizeof(char) 
      << " byte" << endl;
    cout << "Tamanho de int : " << sizeof(int)
      << " bytes" << endl;
    cout << "Tamanho de short int : " << sizeof(short int) 
      << " bytes" << endl;
    cout << "Tamanho de long int : " << sizeof(long int) 
       << " bytes" << endl;
    cout << "Tamanho de signed long int : " << sizeof(signed long int)
       << " bytes" << endl;
    cout << "Tamanho de unsigned long int : " << sizeof(unsigned long int) 
       << " bytes" << endl;
    cout << "Tamanho de float : " << sizeof(float) 
       << " bytes" <<endl;
    cout << "Tamanho de double : " << sizeof(double) 
       << " bytes" << endl;
    cout << "Tamanho de wchar_t : " << sizeof(wchar_t) 
       << " bytes" <<endl;
     
    return 0;
}
