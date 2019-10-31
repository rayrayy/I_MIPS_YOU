#include <iostream>
#include <climits>

#include "r_type_instructions.hpp"
using namespace std;

#define MSB 0x80000000

int main(){

  vector<uint32_t> reg;
  reg.resize(32);

  reg[0] = 1;
  reg[1] = 0;

  // std::cout << SIGNED(reg[0]) + SIGNED(reg[1]) << std::endl;


  uint32_t hi;
  uint32_t lo;
  uint32_t pc;


  uint32_t instruction = 0b00000000000000010001000000100000;
  char type = type_decoder(instruction);

  if (type=='r'){
    r_type(instruction, reg, pc, hi, lo);
  }


  std::cout << reg[2];


  // if (x <= INT_MAX){
  //     cout << static_cast<int>(x);
  // }
  //
  // if (x >= INT_MIN){
  //     cout << static_cast<int>(x - INT_MIN) + INT_MIN;
  // }

}


char type_decoder(uint32_t inst){

  uint32_t r = 0x00;
  uint32_t j = 0x02;
  uint32_t jal = 0x03;

  inst = inst >> 26;
  if (inst == r){
    return 'r';
  }
  else if (inst == j || inst == jal){
    return 'j';
  }
  else{
    return 'i';
  }
}

int SIGNED(uint32_t val){
  int twos_complement = -(~val+1);
  return twos_complement;
}

void r_type(const uint32_t& inst, std::vector<uint32_t>& reg, uint32_t& pc, uint32_t& hi, uint32_t& lo){

  short rs = inst >> 21; // extracting register source
  rs = rs & 0b11111;

  short rt = inst >> 16; // extracting register target
  rt = rt & 0b11111;

  short rd = inst >> 11; //extracting register destination
  rd = rd & 0b11111;

  short shamt = inst >> 6; //extracting shift amount
  shamt = shamt & 0b11111;

  short function = inst & 0b111111; //extracting function code

  if (function == 0b100000){
    ADD(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100001){
    ADDU(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100100){
    AND(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b001000){
    JR(reg[rs], reg[rt]);
  }
  else if (function == 0b100101){
    OR(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100110){
    XOR(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b101010){
    SLT(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b101011){
    SLTU(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b000000){
    SLL(reg[rt], reg[rd], shamt);
  }
  else if (function == 0b000010){
    SRL(reg[rt], reg[rd], shamt);
  }
  else if (function == 0b000011){
    SRA(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100010){
    SUB(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100011){
    SUBU(reg[rs], reg[rt], reg[rd]);
  }
}


void ADD(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = SIGNED(rs) + SIGNED(rt);

  if ((((rs & MSB) == MSB) && ((rt & MSB) == MSB) && ((rd & MSB) == 0))
  || (((rs & MSB) == 0) && ((rt & MSB) == 0) && ((rd & MSB) == MSB))){
   exit(-10); //need to check on this -- currently not giving an exit message
  }

}

void ADDU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs & 0x7FFFFFFF + rt & 0x7FFFFFFF;
}

void AND(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs & rt;
}

void DIV(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){
  if(rt!=0){
    lo = SIGNED(rs) / SIGNED(rt);
    hi = SIGNED(rs) % SIGNED(rt);
  }
}
void JR(const uint32_t& rs, uint32_t& pc){
  pc = rs;
}

void MFHI(const uint32_t& hi, uint32_t& rd){
  rd = hi;
}

void MFLO(const uint32_t& lo, uint32_t& rd){
  rd = lo;
}

void MTHI(const uint32_t& rs, uint32_t& hi){
  hi = rs;
}

void MTLO(const uint32_t& rs, uint32_t& lo){
  lo = rs;
}

//mult

//multu

void MULT(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ //NOT COMPLETE

  int rs_lo = SIGNED(rs) & 0xFFFF;
  int rt_lo = SIGNED(rt) & 0xFFFF;
  int rs_hi = (SIGNED(rs) >> 16) & 0xFFFF;
  int rt_hi = (SIGNED(rt) >> 16) & 0xFFFF;

  lo = rs_lo * rt_lo;
  hi = rs_hi * rt_hi;



}

void OR(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs | rd;
}

void XOR(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs ^ rd;
}

void SLT(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){

  if (SIGNED(rs) < SIGNED(rt)){
    rd = 1;
  }
  else{
    rd = 0;
  }
}

void SLTU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
    if (rs < rt){
      rd = 1;
    }

    else{
      rd = 0;
    }
}

void SLL(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){ //need to double check regarding sign extensions.
  rd = rt << shamt;
}

void SRL(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){ //
  rd = rt >> shamt;
}

void SRA(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){ //need to check if loop is correct
  int tmp = rt & 0x80000000;
  rd = rt >> shamt;
  for (int i = shamt; i > -1; i--){ //loop used to copy first bit to empty bits after shift
    rd = (rd + tmp) >> i;
  }
}

void SUB(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){ //INCORRECT OVERFLOW CALCULATIONS - lets think of a way to calculate overflow first!
  rd = SIGNED(rs) - SIGNED(rt);
  if (rd < rs || rd < rt){
    exit(-10);
  }

}

void SUBU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs - rt;
}