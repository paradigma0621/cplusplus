#include <iostream>

int main(){
  for( int i = 30; i < 40 ; i++ ){
    for( int k = 0 ; k < 6; k++ ){
      std::cout << "\033[" << i << ";" << k << "m CORRR" << "\033[m ";
    }
  }
  return 0;
}

