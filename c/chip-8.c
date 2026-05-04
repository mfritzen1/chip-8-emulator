#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef INSTRUCTIONS
#define INSTRUCTIONS
#include "instructions.h"
#endif

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define MEMORY_SIZE 4096
#define FONT_START 0x50
#define PROGRAM_START 0x200
#define PROGRAM "../roms/IBM_Logo.ch8"

int main()
{
	unsigned char memory[MEMORY_SIZE];
	unsigned char dataRegister[16];
	unsigned short I;
	unsigned short pc;
	unsigned char delayTimer;
	unsigned char soundTimer;
	unsigned short stack[16];
	unsigned short sp;
	int byte = 0;

	const unsigned short FONT_0_LOCATION = FONT_START;
	const unsigned short FONT_1_LOCATION = FONT_START + 5;
	const unsigned short FONT_2_LOCATION = FONT_START + 10;
	const unsigned short FONT_3_LOCATION = FONT_START + 15;
	const unsigned short FONT_4_LOCATION = FONT_START + 20;
	const unsigned short FONT_5_LOCATION = FONT_START + 25;
	const unsigned short FONT_6_LOCATION = FONT_START + 30;
	const unsigned short FONT_7_LOCATION = FONT_START + 35;
	const unsigned short FONT_8_LOCATION = FONT_START + 40;
	const unsigned short FONT_9_LOCATION = FONT_START + 45;
	const unsigned short FONT_A_LOCATION = FONT_START + 50;
	const unsigned short FONT_B_LOCATION = FONT_START + 55;
	const unsigned short FONT_C_LOCATION = FONT_START + 60;
	const unsigned short FONT_D_LOCATION = FONT_START + 65;
	const unsigned short FONT_E_LOCATION = FONT_START + 70;
	const unsigned short FONT_F_LOCATION = FONT_START + 75;

	unsigned char font[80] = {
			0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
			0x20, 0x60, 0x20, 0x20, 0x70, // 1
			0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
			0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
			0x90, 0x90, 0xF0, 0x10, 0x10, // 4
			0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
			0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
			0xF0, 0x10, 0x20, 0x40, 0x40, // 7
			0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
			0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
			0xF0, 0x90, 0xF0, 0x90, 0x90, // A
			0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
			0xF0, 0x80, 0x80, 0x80, 0xF0, // C
			0xE0, 0x90, 0x90, 0x90, 0xE0, // D
			0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
			0xF0, 0x80, 0xF0, 0x80, 0x80	// F
	};

	// clear memory
	for (int i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = 0x0;
	}

	// load font data into memory
	for (int i = 0; i < 80; i++)
	{
		memory[FONT_START + i] = font[i];
	}

	// load program
	pc = PROGRAM_START;
	FILE *file = fopen(PROGRAM, "rb");
	if (file == NULL)
	{
		printf("Could not open file: %s\n", PROGRAM);
		return 1;
	}

	int maxProgramSize = MEMORY_SIZE - PROGRAM_START;
	while (byte != EOF)
	{
		// I don't know why it reads every two bytes in reverse order
		byte = fgetc(file);
		memory[pc + 1] = byte;
		byte = fgetc(file);
		memory[pc] = byte;
		pc += 2;
	}

	pc = PROGRAM_START;

	// emulation loop
	while (1)
	{
		// fetch next instruction
		unsigned char opcodePart1 = memory[pc];
		unsigned char opcodePart2 = memory[pc + 1];
		pc += 2;

		// decode instruction
		unsigned char nibble1 = (opcodePart1 & 0xF0) >> 4;
		unsigned char nibble2 = (opcodePart1 & 0xF);
		unsigned char nibble3 = (opcodePart2 & 0xF0) >> 4;
		unsigned char nibble4 = (opcodePart2 & 0xF);

		switch (nibble1)
		{
		case 0x0:
			switch (nibble2 << 8 | nibble3 << 4 | nibble4)
			{
			case 0x0E0:
				ins00E0();
				break;
			case 0x0EE:
				ins00EE(&pc, &stack, &sp);
				break;
			default:
				ins0NNN();
				break;
			}
			break;
		case 0x1:
			ins1NNN(nibble2 << 8 | nibble3 << 4 | nibble4, &pc);
			break;
		case 0x2:
			ins2NNN(nibble2 << 8 | nibble3 << 4 | nibble4, &pc, &stack, &sp);
			break;
		case 0x3:
			ins3XNN(nibble2, nibble3 << 4 | nibble4, &dataRegister, &pc);
			break;
		case 0x4:
			ins4XNN(nibble2, nibble3 << 4 | nibble4, &dataRegister, &pc);
			break;
		case 0x5:
			ins5XY0(nibble2, nibble3, &dataRegister, &pc);
			break;
		case 0x6:
			ins6XNN(nibble2, nibble3 << 4 | nibble4, &dataRegister);
			break;
		case 0x7:
			ins7XNN(nibble2, nibble3 << 4 | nibble4, &dataRegister);
			break;
		case 0x8:
			switch (nibble4)
			{
			case 0x0:
				ins8XY0(nibble2, nibble3, &dataRegister);
				break;
			case 0x1:
				ins8XY1(nibble2, nibble3, &dataRegister);
				break;
			case 0x2:
				ins8XY2(nibble2, nibble3, &dataRegister);
				break;
			case 0x3:
				ins8XY3(nibble2, nibble3, &dataRegister);
				break;
			case 0x4:
				ins8XY4(nibble2, nibble3, &dataRegister);
				break;
			case 0x5:
				ins8XY5(nibble2, nibble3, &dataRegister);
				break;
			case 0x6:
				ins8XY6(nibble2, &dataRegister);
				break;
			case 0x7:
				ins8XY7(nibble2, nibble3, &dataRegister);
				break;
			default:
				ins8XYE(nibble2, &dataRegister);
				break;
			}
			break;
		case 0x9:
			ins9XY0(nibble2, nibble3, &dataRegister, &pc);
			break;
		case 0xA:
			insANNN(nibble2 << 8 | nibble3 << 4 | nibble4, &I);
			break;
		case 0xB:
			insBNNN(nibble2 << 8 | nibble3 << 4 | nibble4, &dataRegister, &pc);
			break;
		case 0xC:
			insCXNN();
			break;
		case 0xD:
			insDXYN();
			break;
		case 0xE:
			switch (nibble3)
			{
			case 0x9:
				insEX9E();
				break;
			default:
				insEXA1();
				break;
			}
			break;
		case 0xF:
			switch (nibble3)
			{
			case 0x0:
				switch (nibble4)
				{
				case 0x7:
					insFX07(nibble2, &dataRegister, &delayTimer);
					break;
				default:
					insFX0A();
					break;
				}
				break;
			case 0x1:
				switch (nibble4)
				{
				case 0x5:
					insFX15(nibble2, &dataRegister, &delayTimer);
					break;
				case 0x8:
					insFX18(nibble2, &dataRegister, &soundTimer);
					break;
				default:
					insFX1E(nibble2, &dataRegister, &I);
					break;
				}
				break;
			case 0x2:
				insFX29(nibble2, FONT_START, &dataRegister, &I);
				break;
			case 0x3:
				insFX33(nibble2, &dataRegister, &I, &memory);
				break;
			case 0x5:
				insFX55(nibble2, &dataRegister, &I, &memory);
				break;
			default:
				insFX65(nibble2, &dataRegister, &I, &memory);
				break;
			}
			break;
		}
	}

	return 0;
}