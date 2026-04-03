#include <stdio.h>
#include <iostream>
#include <vector>
#include "decode-instruction.h"
#include "chip-8.h"

void decode(unsigned short opcode)
{
	Chip8 chip8{};

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
			chip8.ins00E0();
			break;
		case 0x00ee:
			chip8.ins00EE();
			break;
		default:
			chip8.ins0NNN();
		}
		break;
	case 0x1:
		chip8.ins1NNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0x2:
		chip8.ins2NNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0x3:
		chip8.ins3XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x4:
		chip8.ins4XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x5:
		chip8.ins5XY0(digit2, digit3);
		break;
	case 0x6:
		chip8.ins6XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x7:
		chip8.ins7XNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0x8:
		switch (digit4)
		{
		case 0x0:
			chip8.ins8XY0(digit2, digit3);
			break;
		case 0x1:
			chip8.ins8XY1(digit2, digit3);
			break;
		case 0x2:
			chip8.ins8XY2(digit2, digit3);
			break;
		case 0x3:
			chip8.ins8XY3(digit2, digit3);
			break;
		case 0x4:
			chip8.ins8XY4(digit2, digit3);
			break;
		case 0x5:
			chip8.ins8XY5(digit2, digit3);
			break;
		case 0x6:
			chip8.ins8XY6(digit2 /*, digit3*/);
			break;
		case 0x7:
			chip8.ins8XY7(digit2, digit3);
			break;
		case 0xe:
			chip8.ins8XYE(digit2, digit3);
			break;
		default:
			std::cout << "unknown opcode starting with 8" << "\n";
		}
		break;
	case 0x9:
		chip8.ins9XY0(digit2, digit3);
		break;
	case 0xa:
		chip8.insANNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0xb:
		chip8.insBNNN((digit2 << 8) | (digit3 << 4) | digit4);
		break;
	case 0xc:
		chip8.insCXNN(digit2, (digit3 << 4) | digit4);
		break;
	case 0xd:
		chip8.insDXYN(digit2, digit3, digit4);
		break;
	case 0xe:
		switch (digit4)
		{
		case 0xe:
			chip8.insEX9E(digit2);
			break;
		case 0x1:
			chip8.insEXA1(digit2);
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
				chip8.insFX07(digit2);
				break;
			case 0xa:
				chip8.insFX0A(digit2);
				break;
			default:
				std::cout << "unknown opcode starting with FX0" << "\n";
			}
			break;
		case 0x1:
			switch (digit4)
			{
			case 0x5:
				chip8.insFX15(digit2);
				break;
			case 0x8:
				chip8.insFX18(digit2);
				break;
			case 0xe:
				chip8.insFX1E(digit2);
				break;
			default:
				std::cout << "unknown opcode starting with FX1" << "\n";
			}
			break;
		case 0x2:
			chip8.insFX29(digit2);
			break;
		case 0x3:
			chip8.insFX33(digit2);
			break;
		case 0x5:
			chip8.insFX55(digit2);
			break;
		case 0x6:
			chip8.insFX65(digit2);
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