#ifndef I_TYPE
#define I_TYPE

#include <vector>
#include <iostream>




void give_error(int error_code);

void I_decoder(uint32_t instr, std::vector<uint32_t>& reg, uint32_t& pc);
bool overflow(int a, int b);

void ADDI(const uint32_t& rs, uint32_t& rt, short immediate);
void ADDIU(const uint32_t& rs, uint32_t& rt, short immediate);
void ANDI(const uint32_t& rs, uint32_t& rt, short immediate);
void ORI(const uint32_t& rs, uint32_t& rt, short immediate);
void BGEZ(const uint32_t& rs, short immediate, uint32_t& pc);



#endif
