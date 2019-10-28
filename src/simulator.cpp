#include <string>
#include <fstream>
#include <iostream>
#include <vector>
<<<<<<< HEAD
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
=======
//using namespace std;

#define ADDR_INSTR_OFFSET 0x100000
#define ADDR_DATA_OFFSET 0x20000000

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
    



    // //Simulator starts to run
>>>>>>> 2c18253d063379be1162dd45d498f7f5a83d52c6
    // while(1){
    //   uint32_t instruction;
    //   std::cerr << "Hello World" << std::endl;
    //   return(0);
    // }
<<<<<<< HEAD
    // std::cerr << "Hello" << std::endl;
=======

>>>>>>> 2c18253d063379be1162dd45d498f7f5a83d52c6
    return(0);

}
