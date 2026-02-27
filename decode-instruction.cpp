#include <stdio.h>
#include <iostream>
#include <vector>
#include "decode-instruction.h"

void decode(unsigned short opcode)
{
	// 1 is msb, 4 is lsb
	unsigned short digit1 = (opcode >> 12) & 0xf;
	unsigned short digit2 = (opcode >> 8) & 0xf;
	unsigned short digit3 = (opcode >> 4) & 0xf;
	unsigned short digit4 = opcode & 0xf;

	switch (digit1)
	{
	case 0x0:
		switch (opcode)
		{
		case 0x00e0:
			ins00E0();
			break;
		case 0x00ee:
			ins00EE();
			break;
		default:
			ins0NNN();
		}
		break;
	case 0x1:
		ins1NNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0x2:
		ins2NNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0x3:
		ins3XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x4:
		ins4XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x5:
		ins5XY0(digit2, digit3);
		break;
	case 0x6:
		ins6XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x7:
		ins7XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x8:
		switch (digit4)
		{
		case 0x0:
			ins8XY0(digit2, digit3);
			break;
		case 0x1:
			ins8XY1(digit2, digit3);
			break;
		case 0x2:
			ins8XY2(digit2, digit3);
			break;
		case 0x3:
			ins8XY3(digit2, digit3);
			break;
		case 0x4:
			ins8XY4(digit2, digit3);
			break;
		case 0x5:
			ins8XY5(digit2, digit3);
			break;
		case 0x6:
			ins8XY6(digit2 /*, digit3*/);
			break;
		case 0x7:
			ins8XY7(digit2, digit3);
			break;
		case 0xe:
			ins8XYE(digit2, digit3);
			break;
		default:
			std::cout << "unknown opcode starting with 8" << "\n";
		}
		break;
	case 0x9:
		ins9XY0(digit2, digit3);
		break;
	case 0xa:
		insANNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0xb:
		insBNNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0xc:
		insCXNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0xd:
		insDXYN(digit2, digit3, digit4);
		break;
	case 0xe:
		switch (digit4)
		{
		case 0xe:
			insEX9E(digit2);
			break;
		case 0x1:
			insEXA1(digit2);
			break;
		default:
			std::cout << "unknown opcode starting with E" << "\n";
		}
		break;
	case 0xf:
		switch (digit3)
		{
		case 0x0:
			switch (digit4)
			{
			case 0x7:
				insFX07(digit2);
				break;
			case 0xa:
				insFX0A(digit2);
				break;
			default:
				std::cout << "unknown opcode starting with FX0" << "\n";
			}
			break;
		case 0x1:
			switch (digit4)
			{
			case 0x5:
				insFX15(digit2);
				break;
			case 0x8:
				insFX18(digit2);
				break;
			case 0xe:
				insFX1E(digit2);
				break;
			default:
				std::cout << "unknown opcode starting with FX1" << "\n";
			}
			break;
		case 0x2:
			insFX29(digit2);
			break;
		case 0x3:
			insFX33(digit2);
			break;
		case 0x5:
			insFX55(digit2);
			break;
		case 0x6:
			insFX65(digit2);
			break;
		default:
			std::cout << "unknown opcode starting with F" << "\n";
		}
		break;
	default:
		std::cout << "unknown opcode" << "\n";
	}

	return;
}

void ins0NNN()
{
	std::cout << "0NNN call machine code subroutine (not used?)" << "\n";
}

void ins00E0()
{
	std::cout << "00E0 clear screen" << "\n";
}

void ins00EE()
{
	std::cout << "00EE return from subroutine" << "\n";
}

void ins1NNN(unsigned short address)
{
	std::cout << "1NNN goto address NNN" << "\n";
}

void ins2NNN(unsigned short address)
{
	std::cout << "2NNN call subroutine at address NNN" << "\n";
}

void ins3XNN(unsigned short registerX, unsigned short value)
{
	std::cout << "3XNN skip next instruction if Vx == NN" << "\n";
}

void ins4XNN(unsigned short registerX, unsigned short value)
{
	std::cout << "4XNN skip next instruction if Vx != NN" << "\n";
}

void ins5XY0(unsigned short registerX, unsigned short registerY)
{
	std::cout << "5XY0 skip next instruction if Vx == Vy" << "\n";
}

void ins6XNN(unsigned short registerX, unsigned short value)
{
	std::cout << "6XNN set Vx = NN" << "\n";
}

void ins7XNN(unsigned short registerX, unsigned short value)
{
	std::cout << "7XNN set Vx += NN" << "\n";
}

void ins8XY0(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XY0 set Vx = Vy" << "\n";
}

void ins8XY1(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XY1 set Vx |= Vy" << "\n";
}

void ins8XY2(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XY2 set Vx &= Vy" << "\n";
}

void ins8XY3(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XY3 set Vx ^= Vy" << "\n";
}

void ins8XY4(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XY4 set Vx += Vy" << "\n";
}

void ins8XY5(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XY5 set Vx -= Vy" << "\n";
}

void ins8XY6(unsigned short registerX)
{
	std::cout << "8XY6 set Vx >>= 1" << "\n";
}

void ins8XY7(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XY7 set Vx = Vy - Vx" << "\n";
}

void ins8XYE(unsigned short registerX, unsigned short registerY)
{
	std::cout << "8XYE set Vx <<= 1" << "\n";
}

void ins9XY0(unsigned short registerX, unsigned short registerY)
{
	std::cout << "9XY0 skip next instruction if Vx != Vy" << "\n";
}

void insANNN(unsigned short address)
{
	std::cout << "ANNN set I = NNN" << "\n";
}

void insBNNN(unsigned short address)
{
	std::cout << "BNNN set PC = V0 + NNN" << "\n";
}

void insCXNN(unsigned short registerX, unsigned short value)
{
	std::cout << "CXNN set Vx = rand() & NN" << "\n";
}

void insDXYN(unsigned short registerX, unsigned short registerY, unsigned short spriteHeight)
{
	std::cout << "DXYN draw to screen" << "\n";
}

void insEX9E(unsigned short registerX)
{
	std::cout << "EX9E skip next instruction if keypress() == Vx" << "\n";
}

void insEXA1(unsigned short registerX)
{
	std::cout << "EXA1 skip next instruction if keypress() != Vx" << "\n";
}

void insFX07(unsigned short registerX)
{
	std::cout << "FX07 set Vx to value of delay timer" << "\n";
}

void insFX0A(unsigned short registerX)
{
	std::cout << "FX0A wait for keypress, store in Vx" << "\n";
}

void insFX15(unsigned short registerX)
{
	std::cout << "FX15 set delay timer = Vx" << "\n";
}

void insFX18(unsigned short registerX)
{
	std::cout << "FX18 set sound timer = Vx" << "\n";
}

void insFX1E(unsigned short registerX)
{
	std::cout << "FX1E set I += Vx" << "\n";
}

void insFX29(unsigned short registerX)
{
	std::cout << "FX29 set I = location of font character in Vx" << "\n";
}

void insFX33(unsigned short registerX)
{
	std::cout << "FX33 store BCD of Vx in I, I + 1 and I + 2" << "\n";
}

void insFX55(unsigned short registerX)
{
	std::cout << "FX55 store V0 through Vx in memory, starting at address I" << "\n";
}

void insFX65(unsigned short registerX)
{
	std::cout << "FX65 fill V0 through Vx from memory, starting at address I" << "\n";
}

int main()
{
	unsigned short opcode = 0x1234;

	std::vector opcodes{
			0x0111,
			0x00e0,
			0x00ee,
			0x1111,
			0x2111,
			0x3211,
			0x4211,
			0x5230,
			0x6211,
			0x7211,
			0x8230,
			0x8231,
			0x8232,
			0x8233,
			0x8234,
			0x8235,
			0x8236,
			0x8237,
			0x823e,
			0x9230,
			0xa111,
			0xb111,
			0xc211,
			0xd231,
			0xe29e,
			0xe2a1,
			0xf207,
			0xf20a,
			0xf215,
			0xf218,
			0xf21e,
			0xf229,
			0xf233,
			0xf255,
			0xf265};

	for (int i; i < 35; i++)
	{
		std::cout << i + 1 << ": ";
		decode(opcodes[i]);
	}

	return 0;
}