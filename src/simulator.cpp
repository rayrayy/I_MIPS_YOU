#include <string>
#include <fstream>
#include <iostream>
#include <vector>
//using namespace std;

#define IMEM_OFFSET 0x100000
#define DMEM_OFFSET 0x20000000

int main(int argc, char *argv[]){

    (void)argc; //to stop the warning of not using this argument
    std::string binName = argv[1];

    //Initializing array and offset for instruction memory
    // uint32_t imem[0x1000000] = {0};
    // uint32_t IMEM_OFFSET = 0x10000000;
    //
    // //Initializing array and offset for data memory
    // uint32_t dmem[0x4000000] = {0};
    // uint32_t DMEM_OFFSET = 0x20000000;
    //
    // //Initializing all registers at 0x00000000
    // uint32_t registers[32]={0};
    //
    // //Initializing pc at IMEM_OFFSET
    // uint32_t pc=IMEM_OFFSET;


    //Opening the binary file
    std::ifstream binStream(binName.c_str(), std::ios::in | std::ios::binary | std::ios::ate); //opens binary file for read with get pointer at the end

    std::streampos binStream_size;
    char *memBlock;

    if (binStream.is_open()){
    binStream_size = binStream.tellg();
    memBlock = new char[binStream_size];
    binStream.seekg (0, std::ios::beg);
    binStream.read (memBlock, binStream_size);
    binStream.close();
    }
    else{
      std::cerr << "Unable to open file" << std::endl;
      return(-1);
    }

    std::cerr << memBlock[34] << std::endl;



    // //Simulator starts to run
    // while(1){
    //   uint32_t instruction;
    //   std::cerr << "Hello World" << std::endl;
    //   return(0);
    // }

    return(0);

}
