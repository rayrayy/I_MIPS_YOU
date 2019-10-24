#include <string>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]){

    std::string binName = argv[1];

    std::cerr << binName;


    std::ifstream binStream(argv[1], std::ios::binary);

    // binStream.seek(seek_end);
    // sizeBin=binStream.tell();

    std::vector<uint32_t> imem;
    imem.resize(0x1000000);

    std::vector<uint32_t> dmem;
    dmem.resize(0x4000000);

    // binStream.read(&tmp[0], sizeBin);

    uint32_t IMEM_OFFSET = 0x1000000;
    uint32_t registers[32]={0};
    uint32_t pc=IMEM_OFFSET;

    while(1){
      uint32_t instruction;
    }

    return(0);

}
