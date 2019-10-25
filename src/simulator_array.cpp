#include <string>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]){



    std::string binName = argv[1];

    std::cout << binName;

    // Initializing array and offset for instruction memory
    uint32_t imem[0x1000000] = {0};
    uint32_t IMEM_OFFSET = 0x10000000;

    //Initializing array and offset for data memory
    uint32_t dmem[0x4000000] = {0};
    uint32_t DMEM_OFFSET = 0x20000000;

    //Initializing all registers at 0x00000000
    uint32_t registers[32]={0};

    //Initializing pc at IMEM_OFFSET
    uint32_t pc=IMEM_OFFSET;


    // Opening the binary file
    // std::ifstream binStream;
    // binStream.open(binName, std::ios::binary);

    // if (binStream.is_open()){
    //   std::cout << "Binary opened successfully." << std::endl;
    //   std::string line;
    //   while (getline(binStream, line)) {
    //       std::cout << line.c_str() << std::endl;
    //   }
    //   binStream.close();
    // }

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
