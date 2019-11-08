#include "i_type.hpp"
//#include "../r_type.hpp"
//#include "../simulator.hpp"
//delete later:
void give_error(int error_code){
  std::cerr << "Exited with code "<< error_code << std::endl;
  std::exit(error_code);
}

#define MSB 0x80000000
#define ADDR_INSTR_OFFSET 0x10000000
#define ADDR_INSTR_LENGTH 0x1000000
#define ADDR_DATA_OFFSET 0x20000000
#define ADDR_DATA_LENGTH 0x4000000

int main(){
  uint32_t pc = 10;
  std::vector<uint32_t> reg(32, 0);
  reg[2] = 0x80000000;
  uint32_t instr = 0x04410FF7;

  I_decoder(instr, reg, pc);

  std::cerr << pc << std::endl;

}

void ADDI(const uint32_t& rs, uint32_t& rt, short immediate){
    if (overflow(rs, immediate)) std::exit(-10);
    rt = rs + immediate;
}

void ADDIU(const uint32_t& rs, uint32_t& rt, short immediate){
    rt = rs + immediate;
}

void ANDI(const uint32_t& rs, uint32_t& rt, short immediate){
  rt = rs & (unsigned short)immediate;
}

void ORI(const uint32_t& rs, uint32_t& rt, short immediate){
  rt = rs | (unsigned short)immediate;
}

void XORI(const uint32_t& rs, uint32_t& rt, short immediate){
  rt = rs | (unsigned short)immediate;
}

void BGEZ(const uint32_t& rs, short immediate, uint32_t& pc){
  if ((rs & MSB) == 0){ //branch if rs >= 0
    if ((pc + 1 + immediate < 0) || ((pc + 1 + immediate)*4 >= ADDR_INSTR_LENGTH)){
      std::cerr << "BGEZ to invalid address" << std::endl;
      give_error(-11);
    }
    pc = pc + 1 + immediate;
  }

}

void I_decoder(uint32_t instr, std::vector<uint32_t>& reg, uint32_t& pc){

  short opcode = instr >> 26;
  short rs = (instr >> 21) & 0x1F;
  short rt = (instr >> 16) & 0x1F;
  short immediate = instr & 0xFFFF;

  switch(opcode){
    //ADDI
    case 0b001000: ADDI(reg[rs], reg[rt], immediate); break;
    //ADDIU
    case 0b001001: ADDIU(reg[rs], reg[rt], immediate); break;
    //ANDI
    case 0b001100: ANDI(reg[rs], reg[rt], immediate); break;
    //BEQ
    case 0b000100: give_error(-20); break;
    //BGEZ //BGEZAL //BLTZ // BLTZAL
    case 0b000001:
      switch(rt){
        //BGEZ
        case 0b00001: BGEZ(reg[rs], immediate, pc); break;
        //BGEZAL
        case 0b10001: give_error(-20); break;
        //BLTZ
        case 0b00000: give_error(-20); break;
        // BLTZAL
        case 0b10000: give_error(-20); break;
      }
      break;
    //BGTZ
    case 0b000111: give_error(-20); break;
    //BLEZ
    case 0b000110: give_error(-20); break;
    //BNE
    case 0b000101: give_error(-20); break;
    //LB
    case 0b100000: give_error(-20); break;
    //LBU
    case 0b100100: give_error(-20); break;
    //LH
    case 0b100001: give_error(-20); break;
    //LHU
    case 0b100101: give_error(-20); break;
    //LUI
    case 0b001111: give_error(-20); break;
    //LW
    case 0b100011: give_error(-20); break;
    //LWL
    case 0b100010: give_error(-20); break;
    //LWR
    case 0b100110: give_error(-20); break;
    //ORI
    case 0b001101: ORI(reg[rs], reg[rt], immediate); break;
    //SB
    case 0b101000: give_error(-20); break;
    //SH
    case 0b101001: give_error(-20); break;
    //SLTI
    case 0b001010: give_error(-20); break;
    //SLTIU
    case 0b001011: give_error(-20); break;
    //SW
    case 0b101011: give_error(-20); break;
    //XORI
    case 0b001110: give_error(-20); break;
  }
}

bool overflow(int a, int b){
  int result = a+b;
  return ((((a & MSB) == MSB) && ((b & MSB) == MSB) && ((result & MSB) == 0)) || (((a & MSB) == 0) && ((b & MSB) == 0) && ((result & MSB) == MSB)));
}
