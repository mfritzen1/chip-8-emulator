#include <iostream>

struct Chip8
{
  unsigned char memory[4096];
  unsigned char dataRegisters[16];
  unsigned short I;
  unsigned short pc;
  unsigned char screen[64 * 32];
  unsigned char delayTimer;
  unsigned char soundTimer;
  unsigned short stack[16];
  unsigned short sp;
  unsigned char key;

  /* 0NNN call machine code subroutine (not used?) */
  void ins0NNN()
  {
    std::cout << "0NNN call machine code subroutine (not used?)" << "\n";
  }

  /* 00E0 clear screen" */
  void ins00E0()
  {
    std::cout << "00E0 clear screen" << "\n";
  }

  /* 00EE return from subroutine*/
  void ins00EE()
  {
    pc = stack.pop();
  }

  /* 1NNN goto address NNN */
  void ins1NNN(unsigned short address)
  {
    pc = address;
  }

  /* 2NNN call subroutine at address NNN */
  void ins2NNN(unsigned short address)
  {
    stack.push(pc);
    pc = address;
  }

  /* 3XNN skip next instruction if Vx == NN */
  void ins3XNN(unsigned short registerX, unsigned short value)
  {
    if (dataRegisters[registerX] == value)
    {
      pc += 2;
    }
  }

  /* 4XNN skip next instruction if Vx != NN */
  void ins4XNN(unsigned short registerX, unsigned short value)
  {
    if (dataRegisters[registerX] != value)
    {
      pc += 2;
    }
  }

  /* 5XY0 skip next instruction if Vx == Vy */
  void ins5XY0(unsigned short registerX, unsigned short registerY)
  {
    if (dataRegisters[registerX] == dataRegisters[registerY])
    {
      pc += 2;
    }
  }

  /* 6XNN set Vx = NN */
  void ins6XNN(unsigned short registerX, unsigned short value)
  {
    dataRegisters[registerX] = value;
  }

  /* 7XNN set Vx += NN */
  void ins7XNN(unsigned short registerX, unsigned short value)
  {
    dataRegisters[registerX] += value;
  }

  /* 8XY0 set Vx = Vy */
  void ins8XY0(unsigned short registerX, unsigned short registerY)
  {
    dataRegisters[registerX] = dataRegisters[registerY];
  }

  /* 8XY1 set Vx |= Vy */
  void ins8XY1(unsigned short registerX, unsigned short registerY)
  {
    dataRegisters[registerX] |= dataRegisters[registerY];
  }

  /* 8XY2 set Vx &= Vy */
  void ins8XY2(unsigned short registerX, unsigned short registerY)
  {
    dataRegisters[registerX] &= dataRegisters[registerY];
  }

  /* 8XY3 set Vx ^= Vy */
  void ins8XY3(unsigned short registerX, unsigned short registerY)
  {
    dataRegisters[registerX] ^= dataRegisters[registerY];
  }

  /* 8XY4 set Vx += Vy */
  void ins8XY4(unsigned short registerX, unsigned short registerY)
  {
    int sum = dataRegisters[registerX] + dataRegisters[registerY];
    if (sum > 255)
    {
      dataRegisters[0xf] = 1;
    }
    else
    {
      dataRegisters[0xf] = 0;
    }
    dataRegisters[registerX] = sum & 0xff;
  }

  /* 8XY5 set Vx -= Vy */
  void ins8XY5(unsigned short registerX, unsigned short registerY)
  {
    int difference = dataRegisters[registerX] - dataRegisters[registerY];
    if (difference < 0)
    {
      dataRegisters[0xf] = 0;
    }
    else
    {
      dataRegisters[0xf] = 1;
    }
    dataRegisters[registerX] = difference;
  }

  /* 8XY6 set Vx >>= 1 */
  void ins8XY6(unsigned short registerX)
  {
    std::cout << "8XY6 set Vx >>= 1" << "\n";
  }

  /* 8XY7 set Vx = Vy - Vx */
  void ins8XY7(unsigned short registerX, unsigned short registerY)
  {
    int difference = dataRegisters[registerY] - dataRegisters[registerX];
    if (difference < 0)
    {
      dataRegisters[0xf] = 0;
    }
    else
    {
      dataRegisters[0xf] = 1;
    }
    dataRegisters[registerX] = difference;
  }

  /* 8XYE set Vx <<= 1 */
  void ins8XYE(unsigned short registerX, unsigned short registerY)
  {
    std::cout << "8XYE set Vx <<= 1" << "\n";
  }

  /* 9XY0 skip next instruction if Vx != Vy */
  void ins9XY0(unsigned short registerX, unsigned short registerY)
  {
    if (dataRegisters[registerX] != dataRegisters[registerY])
    {
      pc += 2;
    }
  }

  /* ANNN set I = NNN */
  void insANNN(unsigned short address)
  {
    std::cout << "ANNN set I = NNN" << "\n";
  }

  /* BNNN set PC = V0 + NNN */
  void insBNNN(unsigned short address)
  {
    std::cout << "BNNN set PC = V0 + NNN" << "\n";
  }

  /* CXNN set Vx = rand() & NN */
  void insCXNN(unsigned short registerX, unsigned short value)
  {
    std::cout << "CXNN set Vx = rand() & NN" << "\n";
  }

  /* DXYN draw to screen */
  void insDXYN(unsigned short registerX, unsigned short registerY, unsigned short spriteHeight)
  {
    std::cout << "DXYN draw to screen" << "\n";
  }

  /* EX9E skip next instruction if keypress() == Vx */
  void insEX9E(unsigned short registerX)
  {
    std::cout << "EX9E skip next instruction if keypress() == Vx" << "\n";
  }

  /* EXA1 skip next instruction if keypress() != Vx */
  void insEXA1(unsigned short registerX)
  {
    std::cout << "EXA1 skip next instruction if keypress() != Vx" << "\n";
  }

  /* FX07 set Vx to value of delay timer */
  void insFX07(unsigned short registerX)
  {
    std::cout << "FX07 set Vx to value of delay timer" << "\n";
  }

  /* FX0A wait for keypress, store in Vx */
  void insFX0A(unsigned short registerX)
  {
    std::cout << "FX0A wait for keypress, store in Vx" << "\n";
  }

  /* FX15 set delay timer = Vx */
  void insFX15(unsigned short registerX)
  {
    std::cout << "FX15 set delay timer = Vx" << "\n";
  }

  /* FX18 set sound timer = Vx */
  void insFX18(unsigned short registerX)
  {
    std::cout << "FX18 set sound timer = Vx" << "\n";
  }

  /* FX1E set I += Vx */
  void insFX1E(unsigned short registerX)
  {
    std::cout << "FX1E set I += Vx" << "\n";
  }

  /* FX29 set I = location of font character in Vx */
  void insFX29(unsigned short registerX)
  {
    std::cout << "FX29 set I = location of font character in Vx" << "\n";
  }

  /* FX33 store BCD of Vx in I, I + 1 and I + 2 */
  void insFX33(unsigned short registerX)
  {
    std::cout << "FX33 store BCD of Vx in I, I + 1 and I + 2" << "\n";
  }

  /* FX55 store V0 through Vx in memory, starting at address I */
  void insFX55(unsigned short registerX)
  {
    std::cout << "FX55 store V0 through Vx in memory, starting at address I" << "\n";
  }

  /* FX65 fill V0 through Vx from memory, starting at address I */
  void insFX65(unsigned short registerX)
  {
    std::cout << "FX65 fill V0 through Vx from memory, starting at address I" << "\n";
  }
};