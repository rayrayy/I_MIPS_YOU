#include <iostream>
#include <climits>

#include "r_type_instructions.hpp"
using namespace std;

#define MSB 0x80000000

int main(){

  vector<uint32_t> reg;
  reg.resize(32);

  reg[0] = 1;
  reg[1] = 2;

  std::cout << std::hex << reg[1] << std::endl ; //std::hex prints in hex :)


  uint32_t hi = 0;
  uint32_t lo = 0;
  uint32_t pc = 0;


  uint32_t instruction = 0b0000000000000010000000000011000;
  char type = type_decoder(instruction);

  if (type=='r'){
    r_type(instruction, reg, pc, hi, lo);
  }


  std::cout << std::hex << reg[1] ; //std::hex prints in hex :)


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
  if((((a & MSB) == MSB) && ((b & MSB) == MSB) && ((c & MSB) == 0)) || (((a & MSB) == 0) && ((b & MSB) == 0) && ((c & MSB) == MSB))){
    int overflow = 1;
  }
  else{
    int overflow = 0;
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
  else if (function == 0b001000){
    JR(reg[rs], pc);
  }
  else if (function == 0b010000){
    MFHI(hi, reg[rd]);
  }
  else if (function == 0b010010){
    MFHI(lo, reg[rd]);
  }
  else if (function == 0b010001){
    MTHI(reg[rs], hi);
  }
  else if (function == 0b010011){
    MTLO(reg[rs], lo);
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

void DIV(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ //incomplete - will finish later
  if(rt!=0){
    lo = SIGNED(rs) / SIGNED(rt);
    hi = SIGNED(rs) % SIGNED(rt);
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





void MULT(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ //NOT COMPLETE

  // int rs_lo = SIGNED(rs) & 0xFFFF;
  // int rt_lo = SIGNED(rt) & 0xFFFF;
  // int rs_hi = (SIGNED(rs) >> 16) & 0xFFFF;
  // int rt_hi = (SIGNED(rt) >> 16) & 0xFFFF;
  //
  //
  //
  // lo = rs_lo * rt_lo;
  // hi = rs_hi * rt_hi;

  long long product = SIGNED(rs) * SIGNED(rt);

  product = -(~product+1); //since SIGNED() is only for 32 bits

  lo = product & 0xFFFFFFFF;
  hi = product >> 32;
}

//multu

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

void SRL(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){
  rd = rt >> shamt;
} // tested

void SRA(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){ //need to check if loop is correct
  int tmp = rt & 0x80000000;
  rd = rt >> shamt;
  for (int i = shamt; i > -1; i--){ //loop used to copy first bit to empty bits after shift
    rd = (rd + tmp) >> i;
  }
}  // NOT WORKING -- did you make this? I dont recall but if it was you probably best if you finish it?

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
