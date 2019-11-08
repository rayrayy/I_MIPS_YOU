#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "simulator.hpp"
#include "r_type.hpp"
#include "i_type/i_type.hpp"


#define ADDR_INSTR_OFFSET 0x10000000
#define ADDR_INSTR_LENGTH 0x1000000
#define ADDR_DATA_OFFSET 0x20000000
#define ADDR_DATA_LENGTH 0x4000000




int main(int argc, char *argv[]){

    (void)argc; //to stop the warning of not using this argument
    std::string binName = argv[1];

    //Opening the binary file
    std::ifstream binStream(binName, std::ios::in | std::ios::binary | std::ios::ate); //opens binary file for read with get pointer at the end
    std::streampos binStreamSize;
    char *memBlock;

    if (binStream.is_open()){
    binStreamSize = binStream.tellg();
    memBlock = new char[binStreamSize];
    binStream.seekg (0, std::ios::beg);
    binStream.read (memBlock, binStreamSize);
    binStream.close();
    }
    else{
      std::cerr << "Unable to open file" << std::endl;
      return(-1); //is this the right return value?
    }

    std::vector<uint32_t> instrMem(ADDR_INSTR_LENGTH, 0);
    std::vector<uint32_t> dataMem(ADDR_DATA_LENGTH, 0);
    std::vector<uint32_t> reg(32, 0);
    uint32_t hi, lo = 0;
    uint32_t pc = 0;

    load_instruction_memory(instrMem, memBlock, binStreamSize);
    delete[] memBlock;


    while(1){
      if (delay_slot(instrMem[pc])){
        if (delay_slot(instrMem[pc+1])){ //instruction in a delay slot cannot be a branch/jump
          std::cerr << "branch/jump instruction in a delay slot" << std::endl;
          give_error(-20);
        }
        execute_instruction(instrMem[pc+1], reg, pc, hi, lo, dataMem);
        execute_instruction(instrMem[pc], reg, pc, hi, lo, dataMem);
      }
      else {
        execute_instruction(instrMem[pc], reg, pc, hi, lo, dataMem);
        pc++;
      }

    }


}

bool delay_slot(uint32_t instr){
  uint32_t opcode = instr >> 26; //for now the only delay slot could come from JR
  uint32_t function = instr & 0x3F;

  if ((opcode == 0) && (function == 0b1000)) return true;

  return false;
}

void load_instruction_memory(std::vector<uint32_t>& instrMem, char *memBlock, std::streampos binStreamSize){
  uint32_t tempInst;
  for (int j = 0; j < binStreamSize/4; j++){
     tempInst = 0;
    for (int i = 0; i < 4; i++){
      tempInst += (unsigned char)memBlock[j*4+3-i] << 8*i;
    }
    instrMem[j] = tempInst;
  }
}

void execute_instruction(const uint32_t& inst, std::vector<uint32_t>& reg, uint32_t& pc, uint32_t& hi, uint32_t& lo, std::vector<uint32_t>& dataMem){
  uint32_t opcode = inst >> 26;

  if (opcode == 0x00){ // R-type
    r_type(inst, reg, pc, hi, lo);
  }
  else if (opcode == 0x02 || opcode == 0x03){ //J and JAL
    std::cerr << "J/JAL not implemented yet" << std::endl;
    give_error(-20);
  }
  else{
    I_decoder(inst, reg);
  }
}

void give_error(int error_code){
  std::cerr << "Exited with code "<< error_code << std::endl;
  std::exit(error_code);
}
