#include "I_type.hpp"
#define MSB 0x80000000

int main(){
  std::vector<uint32_t> reg(32, 0);
  reg[0] = 0xffff0000;

  uint32_t instr = 0b00110100000000011000000000000001;
  I_decoder(instr, reg);

  std::cerr << "kanec: "<< std::hex<< (int)reg[1] << std::endl;
  return 0;
}

void ADDI(std::vector<uint32_t>& reg, short rs, short rt, short immediate){
    if (overflow(reg[rs], immediate)) std::exit(-10);
    reg[rt] = reg[rs] + immediate;
}

void ADDIU(std::vector<uint32_t>& reg, short rs, short rt, short immediate){
    reg[rt] = reg[rs] + immediate;
}

void ANDI(std::vector<uint32_t>& reg, short rs, short rt, short immediate){
  reg[rt] = reg[rs] & (unsigned short)immediate;
}

void ORI(std::vector<uint32_t>& reg, short rs, short rt, short immediate){
  reg[rt] = reg[rs] | (unsigned short)immediate;
}

void XORI(std::vector<uint32_t>& reg, short rs, short rt, short immediate){
  reg[rt] = reg[rs] | (unsigned short)immediate;
}

bool overflow(int a, int b){
  int result = a+b;
  return ((((a & MSB) == MSB) && ((b & MSB) == MSB) && ((result & MSB) == 0)) || (((a & MSB) == 0) && ((b & MSB) == 0) && ((result & MSB) == MSB)));
}

void I_decoder(uint32_t instr, std::vector<uint32_t>& reg){

  short opcode = instr >> 26;
  short rs = (instr >> 21) & 0x1F;
  short rt = (instr >> 16) & 0x1F;
  short immediate = instr & 0xFFFF;

  switch(opcode){
    case 0b001000: //ADDI
      ADDI(reg, rs, rt, immediate);
      break;

    case 0b001001: //ADDIU
      ADDIU(reg, rs, rt, immediate);
      break;

    case 0b001100: //ANDI
      ANDI(reg, rs, rt, immediate);
      break;

    case 0b000100:
      //BEQ
      break;

    case 0b000001:
      switch(rt){
        case 0b00001: //BGEZ
          break;

        case 0b10001: //BGEZAL
          break;

        case 0b00000: //BLTZ
          break;

        case 0b10000: std::cerr << "BLTZAL"<< std::endl; // BLTZAL
          break;
      }
      break;

    case 0b000111:
      //BGTZ
      break;

    case 0b000110:
      //BLEZ
      break;

    case 0b000101:
      //BNE
      break;

    case 0b100000:
      //LB
      break;

    case 0b100100:
      //LBU
      break;

    case 0b100001:
      //LH
      break;

    case 0b100101:
      //LHU
      break;

    case 0b001111:
      //LUI
      break;

    case 0b100011:
      //LW
      break;

    case 0b100010:
      //LWL
      break;

    case 0b100110:
      //LWR
      break;

    case 0b001101: //ORI
      ORI(reg, rs, rt, immediate);
      break;

    case 0b101000:
      //SB
      break;

    case 0b101001:
      //SH
      break;

    case 0b001010:
      //SLTI
      break;

    case 0b001011:
      //SLTIU
      break;

    case 0b101011: std::cerr << "SW" << std::endl;
      //SW
      break;

    case 0b001110: //XORI

      break;
  }
}
