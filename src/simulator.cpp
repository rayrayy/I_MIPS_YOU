#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "r_type_instructions.hpp"
#include <unordered_set>

#define ADDR_INSTR_OFFSET 0x10000000
#define ADDR_INSTR_LENGTH 0x1000000

#define ADDR_DATA_OFFSET 0x20000000
#define ADDR_DATA_LENGTH 0x4000000


void load_instruction_memory(std::vector<uint32_t>& instrMem, char *memBlock, std::streampos binStreamSize);

int main(int argc, char *argv[]){

    (void)argc; //to stop the warning of not using this argument
    std::string binName = argv[1];

    std::unordered_set<uint8_t> delay_slot_opcodes;


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

    char kanec = 3;
    std::cout << "kanec je: "<< kanec << std::endl;

    while(1){

      if (type_decoder(instrMem[pc]) == 'r'){
        r_type(instrMem[pc], reg, pc, hi, lo);
        pc++;

      }
      else if ((instrMem[pc] >> 26 == 0) && (instrMem[pc] & 0x3F == 0b1000)){ //ugly way of implememting JR, will change later

        if (type_decoder(instrMem[pc+1]) == 'r') r_type(instrMem[pc+1], reg, pc, hi, lo);
        else std::exit(-20);

        int rs = (instrMem[pc] >> 21) & 0x1F;
        if (reg[rs] == 0) exit(reg[2] & 0xFF);
        if ((reg[rs] < ADDR_INSTR_OFFSET)  || (reg[rs] >= ADDR_INSTR_OFFSET+ADDR_INSTR_LENGTH) || (reg[rs] & 0b11) != 0) std::exit(-11);
        pc = reg[rs]/4;
      }
      else std::exit(-20);




    }

    return(0);

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
