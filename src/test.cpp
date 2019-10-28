#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

int main(){

  uint32_t x = 0xFFFFFFFF;
//Decoder values
  // uint32_t r = 0x00;
  // uint32_t j = 0x02;
  // uint32_t jal = 0x03;
  // //General decoder
  //
  //   inst = inst >> 26;
  //   if (inst == 0){
  //     cout << 'r';
  //   }
  //   else if (inst == j || inst == jal){
  //     cout << 'j';
  //   }
  //   else{
  //     cout << 'i';
  //   }
  // short rs = inst >> 21; // extracting register source
  // rs = rs & 0b11111;
  //
  // short rt = inst >> 16; // extracting register target
  // rt = rt & 0b11111;
  //
  // short rd = inst >> 11; //extracting register destination
  // rd = rd & 0b11111;
  //
  // short shift = inst >> 6; //extracting shift amount
  // shift = shift & 0b11111;
  //
  // short function = inst & 0b111111; //extracting function code
  // cout <<function;
  uint32_t m = x >> 1;
  cout << x << endl;
  cout << m;
  // if (x <= INT_MAX){
  //     cout << static_cast<int>(x);
  // }
  //
  // if (x >= INT_MIN){
  //     cout << static_cast<int>(x - INT_MIN) + INT_MIN;
  // }

}
