#include <iostream>
#include <cmath>
#include <climits>
#include "r_type_instructions.hpp"
#define MSB 0x8000000

using namespace std;

int main(){

  uint32_t rs = 0x7fffffff;
  uint32_t rt = 0x80000000;

  int64_t hilo = (int64_t)(int32_t)rs*(int64_t)(int32_t)rt;

  uint32_t lo = hilo;
  uint32_t hi = hilo >> 32;
  std::cerr << hex << hi <<  " "<< hex << lo << std::endl;


  /*int b = SIGNED(rs) & 0xFFFF;
  int d = SIGNED(rt) & 0xFFFF;
  int a = (SIGNED(rs) >> 16) & 0xFFFF;
  int c = (SIGNED(rt) >> 16) & 0xFFFF;



  int bit_31_0 = b * d;
  int bit_63_32 = a * c;

  int bit_47_16_a = a*d;
  int bit_47_16_b = b*c;

  int bit_47_16 = bit_47_16_a + bit_47_16_b;
  int carry_48 = addition_overflow(bit_47_16_a, bit_47_16_b, bit_47_16);

  int bit_31_16 = bit_47_16 << 16;
  int lo = bit_31_0 + bit_31_16;
  int carry_32 = addition_overflow(bit_31_0, bit_31_16, lo);

  int bit_47_32 = (bit_47_16 >> 16) + carry_32;
  int hi = bit_47_32 + bit_63_32 + (carry_48 << 16);

  cout << hi << lo;

*/







  // if (x <= INT_MAX){
  //     cout << static_cast<int>(x);
  // }
  //
  // if (x >= INT_MIN){
  //     cout << static_cast<int>(x - INT_MIN) + INT_MIN;
  // }

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
