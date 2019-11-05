#ifndef R_TYPE
#define R_TYPE

#include <cmath>
#include <climits>
#include <vector>

void give_error(int error_code);
char type_decoder(uint32_t inst);
int addition_overflow(const int& a, const int& b, const int& c);
int SIGNED(uint32_t val);
void r_type(const uint32_t& inst, std::vector<uint32_t>& reg, uint32_t& pc, uint32_t& hi, uint32_t& lo);

void ADD(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void ADDU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void AND(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void DIV(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo);
void DIVU(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo);
void JR(const uint32_t& rs, uint32_t& pc);
void MFHI(const uint32_t& hi, uint32_t& rd);
void MFLO(const uint32_t& lo, uint32_t& rd);
void MTHI(const uint32_t& rs, uint32_t& hi);
void MTLO(const uint32_t& rs, uint32_t& lo);
void MULT(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo);
void MULTU(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo);
void OR(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void XOR(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void SLT(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void SLTU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void SLL(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt);
void SLLV(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void SRL(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt);
void SRLV(const uint32_t& rt, uint32_t&rd, const uint32_t& rs);
void SRA(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt);
void SRAV(const uint32_t& rt, uint32_t&rd, const uint32_t& rs);
void SUB(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);
void SUBU(const uint32_t& rs, const uint32_t& rt, uint32_t& rd);

#endif
