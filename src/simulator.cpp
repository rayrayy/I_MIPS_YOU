#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[]){



    std::string binName = argv[1];

    // std::cout << binName;

    // Initializing array and offset for instruction memory
    std::vector<uint32_t> imem;
    imem.resize(0x1000000);
    uint32_t IMEM_OFFSET = 0x10000000;

    //Initializing array and offset for data memory
    std::vector<uint32_t> dmem;
    dmem.resize(0x4000000);
    uint32_t DMEM_OFFSET = 0x20000000;

    //Initializing all registers at 0x00000000
    uint32_t registers[32]={0};

    //Initializing pc at IMEM_OFFSET
    uint32_t pc=IMEM_OFFSET;


    // Opening the binary file
    std::ifstream binStream;
    binStream.open(binName, std::ios::binary);

    if (binStream.is_open()){
      std::cout << "Binary opened successfully." << std::endl;
      std::string line;
      while (getline(binStream, line)) {
        std::cout << typeid(line).name() << std::endl; //this line needs to change to one which loads the binary value into the instruction memory.
      }
      binStream.close();
    }

    // else{
    //   std::cout << "Error" << std::endl;
    //   return(0);
    // }
    //
    // // Simulator starts to run
    // while(1){
    //   uint32_t instruction;
    //   std::cerr << "Hello World" << std::endl;
    //   return(0);
    // }
    // std::cerr << "Hello" << std::endl;
    return(0);

}
