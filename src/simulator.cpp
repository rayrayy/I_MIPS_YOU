#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#define ADDR_INSTR_OFFSET 0x10000000
#define ADDR_INSTR_LENGTH 0x1000000

#define ADDR_DATA_OFFSET 0x20000000
#define ADDR_DATA_LENGTH 0x4000000



int main(int argc, char *argv[]){

    (void)argc; //to stop the warning of not using this argument
    std::string binName = argv[1];

    //Opening the binary file
    std::ifstream binStream(binName, std::ios::in | std::ios::binary | std::ios::ate); //opens binary file for read with get pointer at the end
    std::streampos binStream_size;
    char *memBlock;

    if (binStream.is_open()){
    binStream_size = binStream.tellg();
    memBlock = new char[binStream_size];
    binStream.seekg (0, std::ios::beg);
    binStream.read (memBlock, binStream_size);
    binStream.close();
    delete[] memBlock;
    }
    else{
      std::cerr << "Unable to open file" << std::endl;
      return(-1); //is this the right return value?
    }

    std::vector<uint32_t> instrMem;
    std::vector<uint32_t> dataMem;


    return(0);

}
