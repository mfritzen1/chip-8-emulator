#ifndef INSTRUCTIONS
#define INSTRUCTIONS
#include "instructions.h"
#endif

/** 0NNN - execute machine code (probably won't be used) */
void ins0NNN() {}

/** 00E0 - clear the screen */
void ins00E0() {}

/** 00EE - return from subroutine */
void ins00EE(unsigned short *pc, unsigned short *stack, unsigned short *sp)
{
  *pc = stack[*sp];
  *sp--;
}

/** 1NNN - jump to address NNN */
// TODO: depending on implementation, might need to decrement pc after assignment here
void ins1NNN(unsigned short address, unsigned short *pc)
{
  *pc = address;
}

/** 2NNN - call subroutine at NNN */
void ins2NNN(unsigned short address, unsigned short *pc, unsigned short *stack, unsigned short *sp)
{
  stack[*sp + 1] = *pc;
  *sp++;
  *pc = address;
}

/** 3XNN - skip the next instruction if VX == NN */
void ins3XNN(unsigned char registerX, unsigned char value, unsigned char *dataRegister, unsigned short *pc)
{
  if (dataRegister[registerX] == value)
  {
    *pc += 2;
  }
}

/** 4XNN - skip the next instruction if VX != NN */
void ins4XNN(unsigned char registerX, unsigned char value, unsigned char *dataRegister, unsigned short *pc)
{
  if (dataRegister[registerX] != value)
  {
    *pc += 2;
  }
}

/** 5XY0 - skip the next instruction if VX == VY */
void ins5XY0(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister, unsigned short *pc)
{
  if (dataRegister[registerX] == dataRegister[registerY])
  {
    *pc += 2;
  }
}

/** 6XNN - set VX = NN */
void ins6XNN(unsigned char registerX, unsigned char value, unsigned char *dataRegister)
{
  dataRegister[registerX] = value;
}

/** 7XNN - set VX += NN, don't change carry flag */
void ins7XNN(unsigned char registerX, unsigned char value, unsigned char *dataRegister)
{
  dataRegister[registerX] += value;
}

/** 8XY0 - set VX = VY */
void ins8XY0(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister)
{
  dataRegister[registerX] = dataRegister[registerY];
}

/** 8XY1 - set VX |= VY */
void ins8XY1(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister)
{
  dataRegister[registerX] |= dataRegister[registerY];
}

/** 8XY2 - set VX &= VY */
void ins8XY2(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister)
{
  dataRegister[registerX] &= dataRegister[registerY];
}

/** 8XY3 - set VX ^= VY */
void ins8XY3(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister)
{
  dataRegister[registerX] ^= dataRegister[registerY];
}

/** 8XY4 - set VX += VY, set VF to 1 for overflow */
void ins8XY4(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister)
{
  int sum = dataRegister[registerX] + dataRegister[registerY];
  dataRegister[0xf] = sum > 255 ? 0x1 : 0x0;
  dataRegister[registerX] = sum;
}

/** 8XY5 - set VX -= VY, set VF to 0 for underflow */
void ins8XY5(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister)
{
  int difference = dataRegister[registerX] - dataRegister[registerY];
  dataRegister[0xf] = dataRegister[registerX] >= dataRegister[registerY] ? 1 : 0;
  dataRegister[registerX] = difference;
}

/** 8XY6 - set VX >>= 1 (right shift by 1), set VF to LSB of VX */
void ins8XY6(unsigned char registerX, unsigned char *dataRegister)
{
  unsigned char valueX = dataRegister[registerX];
  dataRegister[0xf] = valueX & 0x1;
  dataRegister[registerX] = valueX >> 1;
}

/** 8XY7 - set VX = VY - VX, set VF to 1 if VY > VX */
void ins8XY7(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister)
{
  int difference = dataRegister[registerY] - dataRegister[registerX];
  dataRegister[0xf] = dataRegister[registerY] >= dataRegister[registerX] ? 1 : 0;
  dataRegister[registerX] = difference;
}

/** 8XYE - set VX <<= 1 (left shift by 1), set VF to MSB of VX */
void ins8XYE(unsigned char registerX, unsigned char *dataRegister)
{
  unsigned char valueX = dataRegister[registerX];
  dataRegister[0xf] = (valueX & 0x80) >> 7;
  dataRegister[registerX] = valueX << 1;
}

/** 9XY0 - skip the next instruction if VX != VY */
void ins9XY0(unsigned char registerX, unsigned char registerY, unsigned char *dataRegister, unsigned short *pc)
{
  if (dataRegister[registerX] != dataRegister[registerY])
  {
    *pc += 2;
  }
}

/** ANNN - set I = NNN */
void insANNN(unsigned short address, unsigned short *I)
{
  *I = address;
}

/** BNNN - set PC = V0 + NNN */
void insBNNN(unsigned short address, unsigned char *dataRegister, unsigned short *pc)
{
  *pc = dataRegister[0x0] + address;
}

/** CXNN - set VX = rand() & NN */
void insCXNN() {}

/** DXYN - draw to screen */
void insDXYN() {}

/** EX9E - skip the next instruction if the key stored in VX is pressed */
void insEX9E() {}

/** EXA1 - skip the next instruction if the key stored in VX is not pressed */
void insEXA1() {}

/** FX07 - set VX to value of delay timer */
void insFX07(unsigned char registerX, unsigned char *dataRegister, unsigned char *delayTimer)
{
  dataRegister[registerX] = *delayTimer;
}

/** FX0A - wait for key press, then store value in VX */
void insFX0A() {}

/** FX15 - set delay timer to VX */
void insFX15(unsigned char registerX, unsigned char *dataRegister, unsigned char *delayTimer)
{
  *delayTimer = dataRegister[registerX];
}

/** FX18 - set sound timer to VX */
void insFX18(unsigned char registerX, unsigned char *dataRegister, unsigned char *soundTimer)
{
  *soundTimer = dataRegister[registerX];
}

/** FX1E - set I += VX */
void insFX1E(unsigned char registerX, unsigned char *dataRegister, unsigned short *I)
{
  *I += dataRegister[registerX];
}

/** FX29 - set I to memory location of font character in VX */
void insFX29(unsigned char registerX, unsigned short fontStartLocation, unsigned char *dataRegister, unsigned short *I)
{
  unsigned char fontCharacter = dataRegister[registerX];
  switch (fontCharacter)
  {
  case 0x0:
    *I = fontStartLocation;
    break;
  case 0x1:
    *I = fontStartLocation + 5;
    break;
  case 0x2:
    *I = fontStartLocation + 10;
    break;
  case 0x3:
    *I = fontStartLocation + 15;
    break;
  case 0x4:
    *I = fontStartLocation + 20;
    break;
  case 0x5:
    *I = fontStartLocation + 25;
    break;
  case 0x6:
    *I = fontStartLocation + 30;
    break;
  case 0x7:
    *I = fontStartLocation + 35;
    break;
  case 0x8:
    *I = fontStartLocation + 40;
    break;
  case 0x9:
    *I = fontStartLocation + 45;
    break;
  case 0xA:
    *I = fontStartLocation + 50;
    break;
  case 0xB:
    *I = fontStartLocation + 55;
    break;
  case 0xC:
    *I = fontStartLocation + 60;
    break;
  case 0xD:
    *I = fontStartLocation + 65;
    break;
  case 0xE:
    *I = fontStartLocation + 70;
    break;
  default:
    *I = fontStartLocation + 75;
    break;
  }
}

/** FX33 - store BCD of VX in memory locations I, I + 1, and I + 2 */
void insFX33(unsigned char registerX, unsigned char *dataRegister, unsigned short *I, unsigned char *memory)
{
  unsigned char dataX = dataRegister[registerX];
  memory[*I] = dataX / 100;
  memory[*I + 1] = (dataX % 100) / 10;
  memory[*I + 2] = dataX % 10;
}

/** FX55 - stores V0 through VX in memory, starting at location I */
void insFX55(unsigned char registerX, unsigned char *dataRegister, unsigned short *I, unsigned char *memory)
{
  for (unsigned char i = 0x0; i <= registerX; i++)
  {
    memory[*I + i] = dataRegister[i];
  }
}

/** FX65 - fills V0 through VX with data from memory, starting at location I */
void insFX65(unsigned char registerX, unsigned char *dataRegister, unsigned short *I, unsigned char *memory)
{
  for (unsigned char i = 0x0; i <= registerX; i++)
  {
    dataRegister[i] = memory[*I + i];
  }
}
