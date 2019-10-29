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

void r_type(const uint32_t& inst, std::vector<uint32_t>& reg, uint32_t& pc, uint32_t& hi, uint32_t& lo){

  short rs = inst >> 21; // extracting register source
  rs = rs & 0b11111;

  short rt = ins >> 16; // extracting register target
  rt = rt & 0b11111;

  short rd = ins >> 11; //extracting register destination
  rd = rd & 0b11111;

  short shamt = ins >> 6; //extracting shift amount
  shamt = shamt & 0b11111;

  short function = ins & 0b111111; //extracting function code

  if (function == 0b100000){
    if(add(reg[rs], reg[rt], reg[rd])){
      std::cerr << "Overflow" << std::endl;
    }
  }
  else if (function == 0b100001){
    addu(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100100){
    and(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b001000){
    jr(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100101){
    or(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 0b100110){
    xor(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 101010){
    slt(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 101011){
    sltu(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 000000){
    sll(reg[rt], reg[rd], shamt);
  }
  else if (function == 000010){
    srl(reg[rt], reg[rd], shamt);
  }
  else if (function == 000011){
    sra(reg[rs], reg[rt], reg[rd]);
  }
  else if (function == 100010){
    if(sub(reg[rs], reg[rt], reg[rd])){
      std::cerr << "Overflow" << std::endl;
    }
  }
  else if (function == 100011){
    subu(reg[rs], reg[rt], reg[rd]);
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

void addu(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs + rt;
}

void and(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs & rt;
}

void div(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){
  if(rt!=0){
    lo = signed(rs) / signed(rt);
    hi = signed(rs) % signed(rt);
  }
}
void jr(const uint32_t& rs, uint32_t& pc){
  pc = rs;
}

void mfhi(const uint32_t& hi, uint32_t& rd){
  rd = hi;
}

void mflo(const uint32_t& lo, uint32_t& rd){
  rd = lo;
}

void mthi(const uint32_t& rs, uint32_t& hi){
  hi = rs;
}

void mtlo(const uint32_t& rs, uint32_t& lo){
  lo = rs;
}

//mult

//multu

void or(const uint32_t& rs, const uint32_t& rt, uint32_t& hi, uint32_t& lo){ //NOT COMPLETE

  int rs_lo = signed(rs) & 0xFFFF;
  int rt_lo = signed(rt) & 0xFFFF;
  int rs_hi = (signed(rs) >> 16) & 0xFFFF;
  int rt_hi = (signed(rt) >> 16) & 0xFFFF;

  lo = rs_lo * rt_lo;
  hi = rs_hi * rt_hi;

  int tmp = rs_hi*rt_lo + rs_lo*rt*hi;

}

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

void sll(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){ //need to double check regarding sign extensions.
  rd = rt << shamt;
}

void srl(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){ //
  rd = rt >> shamt;
}

void sra(const uint32_t& rt, uint32_t&rd, const uint32_t& shamt){ //need to check if loop is correct
  int tmp = rt & 0x80000000;
  rd = rt >> shamt;
  for (int i = shamt; i > -1; i--){ //loop used to copy first bit to empty bits after shift
    rd = rd + tmp >> i;
  }
}

bool sub(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){ //INCORRECT OVERFLOW CALCULATIONS - lets think of a way to calculate overflow first!
  bool overflow = 0;
  rd = signed(rs) - signed(rt);
  if (rd < rs || rd < rt){
    overflow = 1;
    return overflow;
  }
  else{
    return overflow;
  }
}

void subu(const uint32_t& rs, const uint32_t& rt, uint32_t& rd){
  rd = rs - rt;
}
