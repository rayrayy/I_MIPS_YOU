#include <climits>

char type_decoder(uint32_t inst){

  uint32_t r = 0x00;
  uint32_t j = 0x02;
  uint32_t jal = 0x03;

  inst = inst >> 26;
  if (inst == 0){
    return 'r';
  }
  else if (inst == j || inst == jal){
    return 'j';
  }
  else{
    return 'i';
  }
}

int signed(uint32_t val){
  if (val <= INT_MAX){
        return static_cast<int>(x);
  }

  if (val >= INT_MIN){
    return static_cast<int>(x - INT_MIN) + INT_MIN;
  }
}

void r_type(const uint32_t& inst, std::vector<uint32_t>& reg, uint32_t& pc){

  short rs = inst >> 21; // extracting register source
  rs = rs & 0b11111;

  short rt = ins >> 16; // extracting register target
  rt = rt & 0b11111;

  short rd = ins >> 11; //extracting register destination
  rd = rd & 0b11111;

  short shift = ins >> 6; //extracting shift amount
  shift = shift & 0b11111;

  short function = ins & 0b111111; //extracting function code

  if (function == 0b1000000){
    add(reg[rs], reg[rt], reg[rd]);
  }

}


bool add(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){ //INCORRECT OVERFLOW CALCULATIONS - lets think of a way to calculate overflow first!
  bool overflow = 0;
  rd = signed(rs) + signed(rt);
  if (rd < rs || rd < rt){
    overflow = 1;
    return overflow;
  }
  else{
    return overflow;
  }
}

void add(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs + rt;
}

void and(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs & rt;
}

//div

void jr(const uint32_t& rs, uint32_t& pc){
  pc = rs;
}

//mfhi

//mflo

//mthi

//mtlo

//mult

//multu

void or(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs | rd;
}

void xor(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs ^ rd;
}

void slt(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){

  if (signed(rs) < signed(rt){
    rd = 1;
  }
  else{
    rd = 0;
  }
}

void sltu(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
    if (rs < rt{
      rd = 1;
    }

    else{
      rd = 0;
    }
}

void sll(const uint32_t& rt, uint32_t&rd, const uint32_t& shift){ //need to double check regarding sign extensions.
  rd = rt << shift;
}

void slr(const uint32_t& rt, uint32_t&rd, const uint32_t& shift){ //
  rd = rt >> shift;
}

void sra(const uint32_t& rt, uint32_t&rd, const uint32_t& shift){ //need to check if loop is correct
  int tmp = rt & 0x80000000;
  rd = rt >> shift;
  for (int i = shift; i > -1; i--){ //loop used to copy first bit to empty bits after shift
    rd = rd + tmp >> i;
  }
}

//sub

//subu
