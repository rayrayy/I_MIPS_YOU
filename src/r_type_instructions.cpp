#include <iostream>
#include <climits>

#include "r_type_instructions.hpp"
using namespace std;

#define MSB 0x80000000

int main(){

  vector<uint32_t> reg;
  reg.resize(32);

  reg[0] = 11;
  reg[1] = 0x7FFFFFFF;


  // std::cout << std::hex << reg[1] << std::endl ; //std::hex prints in hex :)


  uint32_t hi = 0;
  uint32_t lo = 0;
  uint32_t pc = 0;


  uint32_t instruction = 0b00000000000000010001000000000111;
  char type = type_decoder(instruction);

  if (type=='r'){
    r_type(instruction, reg, pc, hi, lo);
  }

  std::cout << hex << reg[2];

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

int addition_overflow(const int& a, const int& b, const int& c){
  int overflow = 0;
  if((((a & MSB) == MSB) && ((b & MSB) == MSB) && ((c & MSB) == 0)) || (((a & MSB) == 0) && ((b & MSB) == 0) && ((c & MSB) == MSB))){
    overflow = 1;
  }
  return overflow;
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
  else if (function == 0b011010){
    DIV(reg[rs], reg[rt], hi, lo);
  }
  else if (function == 0b011011){
    DIVU(reg[rs], reg[rt], hi, lo);
  }
  else if (function == 0b001000){
    JR(reg[rs], pc);
  }
  else if (function == 0b010000){
    MFHI(hi, reg[rd]);
  }
  else if (function == 0b010010){
    MFLO(lo, reg[rd]);
  }
  else if (function == 0b010001){
    MTHI(reg[rs], hi);
  }
  else if (function == 0b010011){
    MTLO(reg[rs], lo);
  }
  else if (function == 0b011000){
    MULT(reg[rs], reg[rt], hi, lo);
  }
  else if (function == 0b011001){
    MULTU(reg[rs], reg[rt], hi, lo);
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
  else if (function == 0b000100){
    SLLV(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b000010){
    SRL(reg[rt], reg[rd], shamt);
  }
  else if (function == 0b000110){
    SRLV(reg[rt], reg[rd], reg[rs]);
  }
  else if (function == 0b000011){
    SRA(reg[rt], reg[rd], shamt);
  }
  else if (function == 0b000111){
    SRAV(reg[rt], reg[rd], reg[rs]);
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
  //
  // if((((rs >> 31) == 1) && ((rt >> 31) == 1) && ((rd >> 31) == 0))
  // || (((rs >> 31) == 0) && ((rt >> 31) == 0) && ((rd >> 31) == 1))){
  if(addition_overflow(SIGNED(rs), SIGNED(rt), rd)){
   give_error(-10); //need to check on this -- currently not giving an exit message
  }

} // tested

void ADDU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs + rt;
} // tested

void AND(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs & rt;
} // tested

void DIV(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ //tested
  if(rt!=0){
    lo = SIGNED(rs) / SIGNED(rt);
    hi = SIGNED(rs) % SIGNED(rt);
  }
}

void DIVU(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ //tested
  if(rt!=0){
    lo = rs / rt;
    hi = rs % rt;
  }
}

void JR(const uint32_t& rs, uint32_t& pc){
  pc = rs;
} // tested

void MFHI(const uint32_t& hi, uint32_t& rd){
  rd = hi;
} // tested

void MFLO(const uint32_t& lo, uint32_t& rd){
  rd = lo;
} // tested

void MTHI(const uint32_t& rs, uint32_t& hi){
  hi = rs;

} // tested

void MTLO(const uint32_t& rs, uint32_t& lo){
  lo = rs;
} // tested

void MULT(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ // tested

  long long product = SIGNED(rs) * SIGNED(rt);

  lo = product & 0xFFFFFFFF;
  hi = product >> 32;
}

void MULTU(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ //NOT COMPLETE

  uint64_t product = (uint64_t)rs * (uint64_t)rt;

  lo = product & 0xFFFFFFFF;
  hi = product >> 32;

  cout << hex << product << endl;
}

void OR(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs | rd;
} // tested

void XOR(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs ^ rt;
} // tested

void SLT(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){

  if (SIGNED(rs) < SIGNED(rt)){
    rd = 1;
  }
  else{
    rd = 0;
  }
} // tested

void SLTU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
    if (rs < rt){
      rd = 1;
    }

    else{
      rd = 0;
    }
} //tested

void SLL(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){
  rd = rt << shamt;
} // tested

void SLLV(const uint32_t& rs, const uint32_t&rt, uint32_t& rd){
  rd = rt << (rs & 0x1F);
} // tested

void SRL(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){
  rd = rt >> shamt;
} // tested

void SRLV(const uint32_t& rt, uint32_t&rd, const uint32_t& rs){
  rd = rt >> (rs & 0x1F);
} // tested

void SRA(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){
  //int tmp = rt & 0x80000000;
  rd = (int)rt >> shamt;
}  // tested

void SRAV(const uint32_t& rt, uint32_t&rd, const uint32_t& rs){
  //int tmp = rt & 0x80000000;
  rd = (int)rt >> (rs&0x1F);
}  // tested

void SUB(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){ // test
  rd = SIGNED(rs) - SIGNED(rt);
  if((((rs & MSB) == MSB) && ((rt & MSB) == 0) && ((rd & MSB) == 0))
  || (((rs & MSB) == 0) && ((rt & MSB) == MSB) && ((rd & MSB) == MSB))){
   give_error(-10);
 }

}

void SUBU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs - rt;
}

void give_error(int error_code){
  std::cerr << "Exited with error code "<<error_code;
  exit(error_code);
}
