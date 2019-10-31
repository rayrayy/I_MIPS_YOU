#include <iostream>
#include <cmath>
#include <climits>
#include "r_type_instructions.hpp"

using namespace std;

int main(){

  string ins = "11111111111111101111111111111111";

  

  uint32_t inst = stoi(ins);

  cout << std::hex << inst;


  // if (x <= INT_MAX){
  //     cout << static_cast<int>(x);
  // }
  //
  // if (x >= INT_MIN){
  //     cout << static_cast<int>(x - INT_MIN) + INT_MIN;
  // }

}
