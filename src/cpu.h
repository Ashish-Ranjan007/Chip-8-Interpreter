#pragma once

#include <cstdint>

const int MEMORY_SIZE = 4096;
const int NO_OF_REGISTER = 16;
const int STACK_SIZE = 16;

class CPU
{

private:
	uint8_t memory[MEMORY_SIZE];
	uint8_t registers[NO_OF_REGISTER];		// General purpose registers
	uint16_t pc;							// Program counter is said to be a pseudo-register
	uint16_t I;								// Index register
	uint16_t s[STACK_SIZE];					// Stack
	uint8_t sp;								// Stack pointer is said to be a pseudo-register
	uint8_t dt;								// Delay timer is controlled by the delay timer register
	uint8_t st;								// Sound timer is controlled by the sound timer register

public:
	void initialize(void);  // Initializes all the components of the CPU 
	uint8_t getMemory(uint16_t addr);
	void setMemory(uint16_t addr, uint8_t val);
	void I_0nnn(void);
	void I_00E0(void);
	void I_00EE(void);
	void I_1nnn(void);
	void I_2nnn(void);
	void I_3xkk(void);
	void I_4xkk(void);
	void I_5xy0(void);
	void I_6xkk(void);
	void I_7xkk(void);
	void I_8xy0(void);
	void I_8xy1(void);
	void I_8xy2(void);
	void I_8xy3(void);
	void I_8xy4(void);
	void I_8xy5(void);
	void I_8xy6(void);
	void I_8xy7(void);
	void I_8xyE(void);
	void I_9xy0(void);
	void I_Annn(void);
	void I_Bnnn(void);
	void I_Cxkk(void);
	void I_Dxyn(void);
	void I_Ex9E(void);
	void I_ExA1(void);
	void I_Fx07(void);
	void I_Fx0A(void);
	void I_Fx15(void);
	void I_Fx18(void);
	void I_Fx1E(void);
	void I_Fx29(void);
	void I_Fx33(void);
	void I_Fx55(void);
	void I_Fx65(void);

};
