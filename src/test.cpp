#include <iostream>
#include <cmath>
#include <climits>
#include "r_type_instructions.hpp"
#define MSB 0x8000000

using namespace std;

int main(){

  uint32_t a = 0xFFFFFFFF;

  a = a << (31 & 0x1F);

  cout << hex << a;


}

int addition_overflow(const int& a, const int& b, const int& c){
  int overflow = 0;
  if((((a & MSB) == MSB) && ((b & MSB) == MSB) && ((c & MSB) == 0)) || (((a & MSB) == 0) && ((b & MSB) == 0) && ((c & MSB) == MSB))){
    overflow = 1;
  }
  return overflow;
}

int SIGNED(uint32_t val){
  int twos_complement = -(~val+1);
  return twos_complement;
}
