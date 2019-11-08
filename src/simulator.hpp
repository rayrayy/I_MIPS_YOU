#ifndef SIMULATOR
#define SIMULATOR

bool delay_slot(uint32_t instr);

void give_error(int error_code);
void load_instruction_memory(std::vector<uint32_t>& instrMem, char *memBlock, std::streampos binStreamSize);
void execute_instruction(const uint32_t& inst, std::vector<uint32_t>& reg, uint32_t& pc, uint32_t& hi, uint32_t& lo, std::vector<uint32_t>& dataMem);

#endif
