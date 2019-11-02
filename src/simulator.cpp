#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#define ADDR_INSTR_OFFSET 0x10000000
#define ADDR_INSTR_LENGTH 0x1000000

#define ADDR_DATA_OFFSET 0x20000000
#define ADDR_DATA_LENGTH 0x4000000


void load_instruction_memory(std::vector<uint32_t>& instrMem, char *memBlock, std::streampos binStreamSize);

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

    std::vector<uint32_t> instrMem;
    std::vector<uint32_t> dataMem;

    load_instruction_memory(instrMem, memBlock, binStreamSize);

    delete[] memBlock;

    std::cerr << std::hex << instrMem[0] << std::endl;
    std::cerr << std::hex << instrMem[1] << std::endl;


    return(0);

}

void load_instruction_memory(std::vector<uint32_t>& instrMem, char *memBlock, std::streampos binStreamSize){
  uint32_t tempInst;
  for (int j = 0; j < binStreamSize/4; j++){
     tempInst = 0;
    for (int i = 0; i < 4; i++){
      tempInst += (unsigned char)memBlock[j*4+3-i] << 8*i;
    }
    instrMem.push_back(tempInst);
  }
}
