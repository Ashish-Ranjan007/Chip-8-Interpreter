#pragma once

#include <cstdint>

#include "audio.h"
#include "display.h"
#include "keyboard.h"

const int MEMORY_SIZE = 4096;
const int NO_OF_REGISTER = 16;
const int STACK_SIZE = 16;

class CPU
{

public:

	uint8_t memory[MEMORY_SIZE];
	uint8_t registers[NO_OF_REGISTER];		// General purpose registers
	uint16_t pc;							// Program counter is said to be a pseudo-register
	uint16_t I;								// Index register
	uint16_t s[STACK_SIZE];					// Stack
	uint8_t sp;								// Stack pointer is said to be a pseudo-register
	uint8_t dt;								// Delay timer is controlled by the delay timer register
	uint8_t st;								// Sound timer is controlled by the sound timer register
	Audio* audio;
	Display* display;
	Keyboard* keyboard;

	CPU(Audio* audio, Display* display, Keyboard* keyboard);
	~CPU(void);
	uint8_t getMemory(uint16_t addr);
	void setMemory(uint16_t addr, uint8_t val);
	void decodeAndExecute(uint16_t opcode);
	void emulateCycle();
	void I_0nnn(uint16_t opcode);
	void I_00E0(void);
	void I_00EE(void);
	void I_1nnn(uint16_t opcode);
	void I_2nnn(uint16_t opcode);
	void I_3xkk(uint16_t opcode);
	void I_4xkk(uint16_t opcode);
	void I_5xy0(uint16_t opcode);
	void I_6xkk(uint16_t opcode);
	void I_7xkk(uint16_t opcode);
	void I_8xy0(uint16_t opcode);
	void I_8xy1(uint16_t opcode);
	void I_8xy2(uint16_t opcode);
	void I_8xy3(uint16_t opcode);
	void I_8xy4(uint16_t opcode);
	void I_8xy5(uint16_t opcode);
	void I_8xy6(uint16_t opcode);
	void I_8xy7(uint16_t opcode);
	void I_8xyE(uint16_t opcode);
	void I_9xy0(uint16_t opcode);
	void I_Annn(uint16_t opcode);
	void I_Bnnn(uint16_t opcode);
	void I_Cxkk(uint16_t opcode);
	void I_Dxyn(uint16_t opcode);
	void I_Ex9E(uint16_t opcode);
	void I_ExA1(uint16_t opcode);
	void I_Fx07(uint16_t opcode);
	void I_Fx0A(uint16_t opcode);
	void I_Fx15(uint16_t opcode);
	void I_Fx18(uint16_t opcode);
	void I_Fx1E(uint16_t opcode);
	void I_Fx29(uint16_t opcode);
	void I_Fx33(uint16_t opcode);
	void I_Fx55(uint16_t opcode);
	void I_Fx65(uint16_t opcode);

};
