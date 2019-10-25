#include <iostream>
#include <bitset>
using namespace std;


int main(){
  string raymond = "11000001001011011001011010110101";
  uint32_t zhu = bitset<32>(raymond);
  cout << zhu;
}
