#include <stdio.h>
#include <iostream>
#include <vector>

void decode(unsigned short opcode)
{
	// 1 is msb, 4 is lsb
	// also, I don't know the correct hex term, so I'm using digit
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
			std::cout << "00E0 clear screen" << "\n";
			break;
		case 0x00ee:
			std::cout << "00EE return from subroutine" << "\n";
			break;
		default:
			std::cout << "0NNN call machine code subroutine (not used?)" << "\n";
		}
		break;
	case 0x1:
		std::cout << "1NNN goto address NNN" << "\n";
		break;
	case 0x2:
		std::cout << "2NNN call subroutine at address NNN" << "\n";
		break;
	case 0x3:
		std::cout << "3XNN skip next instruction if Vx == NN" << "\n";
		break;
	case 0x4:
		std::cout << "4XNN skip next instruction if Vx != NN" << "\n";
		break;
	case 0x5:
		std::cout << "5XY0 skip next instruction if Vx == Vy" << "\n";
		break;
	case 0x6:
		std::cout << "6XNN set Vx = NN" << "\n";
		break;
	case 0x7:
		std::cout << "7XNN set Vx += NN" << "\n";
		break;
	case 0x8:
		switch (digit4)
		{
		case 0x0:
			std::cout << "8XY0 set Vx = Vy" << "\n";
			break;
		case 0x1:
			std::cout << "8XY1 set Vx |= Vy" << "\n";
			break;
		case 0x2:
			std::cout << "8XY2 set Vx &= Vy" << "\n";
			break;
		case 0x3:
			std::cout << "8XY3 set Vx ^= Vy" << "\n";
			break;
		case 0x4:
			std::cout << "8XY4 set Vx += Vy" << "\n";
			break;
		case 0x5:
			std::cout << "8XY5 set Vx -= Vy" << "\n";
			break;
		case 0x6:
			std::cout << "8XY6 set Vx >>= 1" << "\n";
			break;
		case 0x7:
			std::cout << "8XY7 set Vx = Vy - Vx" << "\n";
			break;
		case 0xe:
			std::cout << "8XYE set Vx <<= 1" << "\n";
			break;
		default:
			std::cout << "unknown opcode starting with 8" << "\n";
		}
		break;
	case 0x9:
		std::cout << "9XY0 skip next instruction if Vx != Vy" << "\n";
		break;
	case 0xa:
		std::cout << "ANNN set I = NNN" << "\n";
		break;
	case 0xb:
		std::cout << "BNNN set PC = V0 + NNN" << "\n";
		break;
	case 0xc:
		std::cout << "CXNN set Vx = rand() & NN" << "\n";
		break;
	case 0xd:
		std::cout << "DXYN draw to screen" << "\n";
		break;
	case 0xe:
		switch (digit4)
		{
		case 0xe:
			std::cout << "EX9E skip next instruction if keypress() == Vx" << "\n";
			break;
		case 0x1:
			std::cout << "EXA1 skip next instruction if keypress() != Vx" << "\n";
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
				std::cout << "FX07 set Vx to value of delay timer" << "\n";
				break;
			case 0xa:
				std::cout << "FX0A wait for keypress, store in Vx" << "\n";
				break;
			default:
				std::cout << "unknown opcode starting with FX0" << "\n";
			}
			break;
		case 0x1:
			switch (digit4)
			{
			case 0x5:
				std::cout << "FX15 set delay timer = Vx" << "\n";
				break;
			case 0x8:
				std::cout << "FX18 set sound timer = Vx" << "\n";
				break;
			case 0xe:
				std::cout << "FX1E set I += Vx" << "\n";
				break;
			default:
				std::cout << "unknown opcode starting with FX1" << "\n";
			}
			break;
		case 0x2:
			std::cout << "FX29 set I = location of font character in Vx" << "\n";
			break;
		case 0x3:
			std::cout << "FX33 store BCD of Vx in I, I + 1 and I + 2" << "\n";
			break;
		case 0x5:
			std::cout << "FX55 store V0 through Vx in memory, starting at address I" << "\n";
			break;
		case 0x6:
			std::cout << "FX65 fill V0 through Vx from memory, starting at address I" << "\n";
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
		decode(opcodes[i]);
	}

	return 0;
}