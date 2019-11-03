#ifndef I_TYPE
#define I_TYPE

#include <vector>
#include <iostream>

void I_decoder(uint32_t instr, std::vector<uint32_t>& reg);
bool overflow(int a, int b);

void ADDI(std::vector<uint32_t>& reg, short rs, short rt, short immediate);
void ADDIU(std::vector<uint32_t>& reg, short rs, short rt, short immediate);
void ANDI(std::vector<uint32_t>& reg, short rs, short rt, short immediate);
void ORI(std::vector<uint32_t>& reg, short rs, short rt, short immediate);


#endif
