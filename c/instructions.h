void ins0NNN();                                                 // 0NNN - execute machine code (probably won't be used)
void ins00E0();                                                 // 00E0 - clear the screen
void ins00EE();                                                 // 00EE - return from subroutine
void ins1NNN(unsigned short address);                           // 1NNN - jump to address NNN, TODO: depending on implementation, might need to decrement pc after assignment here
void ins2NNN(unsigned short address);                           // 2NNN - call subroutine at NNN
void ins3XNN(unsigned char registerX, unsigned char value);     // 3XNN - skip the next instruction if VX == NN
void ins4XNN(unsigned char registerX, unsigned char value);     // 4XNN - skip the next instruction if VX != NN
void ins5XY0(unsigned char registerX, unsigned char registerY); // 5XY0 - skip the next instruction if VX == VY
void ins6XNN(unsigned char registerX, unsigned char value);     // 6XNN - set VX = NN
void ins7XNN(unsigned char registerX, unsigned char value);     // 7XNN - set VX += NN, don't change carry flag
void ins8XY0(unsigned char registerX, unsigned char registerY); // 8XY0 - set VX = VY
void ins8XY1(unsigned char registerX, unsigned char registerY); // 8XY1 - set VX |= VY
void ins8XY2(unsigned char registerX, unsigned char registerY); // 8XY2 - set VX &= VY
void ins8XY3(unsigned char registerX, unsigned char registerY); // 8XY3 - set VX ^= VY
void ins8XY4(unsigned char registerX, unsigned char registerY); // 8XY4 - set VX += VY, set VF to 1 for overflow
void ins8XY5(unsigned char registerX, unsigned char registerY); // 8XY5 - set VX -= VY, set VF to 0 for underflow
void ins8XY6(unsigned char registerX);                          // 8XY6 - set VX >>= 1 (right shift by 1), set VF to LSB of VX
void ins8XY7(unsigned char registerX, unsigned char registerY); // 8XY7 - set VX = VY - VX, set VF to 1 if VY > VX
void ins8XYE(unsigned char registerX);                          // 8XYE - set VX <<= 1 (left shift by 1), set VF to MSB of VX
void ins9XY0(unsigned char registerX, unsigned char registerY); // 9XY0 - skip the next instruction if VX != VY
void insANNN(unsigned short address);                           // ANNN - set I = NNN
void insBNNN(unsigned short address);                           // BNNN - set PC = V0 + NNN
void insCXNN();                                                 // CXNN - set VX = rand() & NN
void insDXYN();                                                 // DXYN - draw to screen
void insEX9E();                                                 // EX9E - skip the next instruction if the key stored in VX is pressed
void insEXA1();                                                 // EXA1 - skip the next instruction if the key stored in VX is not pressed
void insFX07(unsigned char registerX);                          // FX07 - set VX to value of delay timer
void insFX0A();                                                 // FX0A - wait for key press, then store value in VX
void insFX15(unsigned char registerX);                          // FX15 - set delay timer to VX
void insFX18(unsigned char registerX);                          // FX18 - set sound timer to VX
void insFX1E(unsigned char registerX);                          // FX1E - set I += VX
void insFX29(unsigned char registerX);                          // FX29 - set I to memory location of font character in VX
void insFX33(unsigned char registerX);                          // FX33 - store BCD of VX in memory locations I, I + 1, and I + 2
void insFX55(unsigned char registerX);                          // FX55 - stores V0 through VX in memory, starting at location I
void insFX65(unsigned char registerX);                          // FX65 - fills V0 through VX with data from memory, starting at location I