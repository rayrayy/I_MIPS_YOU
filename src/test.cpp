#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

int main(){

  uint32_t x = 0XFFFFFFFF;
  uint32_t y = 0X00000002;

  cout << x+y;


  // if (x <= INT_MAX){
  //     cout << static_cast<int>(x);
  // }
  //
  // if (x >= INT_MIN){
  //     cout << static_cast<int>(x - INT_MIN) + INT_MIN;
  // }

}
