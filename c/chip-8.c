#include <stdio.h>
#include "instructions.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define MEMORY_SIZE 4096
#define FONT_START 0x50

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

	return 0;
}