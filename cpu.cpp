#include "cpu.h";

void CPU::initialize() 
{
	pc = 0x200;  // Program counter is initialized to 0x200 because 0x000 to 0x1FF is reserved for the interpreter itself.
	I = 0;
	sp = 0;
	dt = 0;
	st = 0;

	// Clear and initialize memory
	for (int i = 0; i < MEMORY_SIZE; i++) 
	{
		memory[i] = 0;
	}
	// Clear and initialize the general purpose registers
	for (int i = 0; i < NO_OF_REGISTER; i++)
	{
		registers[i] = 0;
	}
	// Clear and initialize the stack
	for (int i = 0; i < STACK_SIZE; i++)
	{
		s[i] = 0;
	}
}

uint8_t CPU::getMemory(uint16_t addr)
{
	return memory[addr];
}

void CPU::setMemory(uint16_t addr, uint8_t val)
{
	memory[addr] = val;
}

void CPU::I_0nnn(void)
{
	// TODO
}

void CPU::I_00E0(void)
{
	// Clears the display

}

void CPU::I_00EE(void)
{
}

void CPU::I_1nnn(void)
{
}

void CPU::I_2nnn(void)
{
}

void CPU::I_3xkk(void)
{
}

void CPU::I_4xkk(void)
{
}

void CPU::I_5xy0(void)
{
}

void CPU::I_6xkk(void)
{
}

void CPU::I_7xkk(void)
{
}

void CPU::I_8xy0(void)
{
}

void CPU::I_8xy1(void)
{
}

void CPU::I_8xy2(void)
{
}

void CPU::I_8xy3(void)
{
}

void CPU::I_8xy4(void)
{
}

void CPU::I_8xy5(void)
{
}

void CPU::I_8xy6(void)
{
}

void CPU::I_8xy7(void)
{
}

void CPU::I_8xyE(void)
{
}

void CPU::I_9xy0(void)
{
}

void CPU::I_Annn(void)
{
}

void CPU::I_Bnnn(void)
{
}

void CPU::I_Cxkk(void)
{
}

void CPU::I_Dxyn(void)
{
}

void CPU::I_Ex9E(void)
{
}

void CPU::I_ExA1(void)
{
}

void CPU::I_Fx07(void)
{
}

void CPU::I_Fx0A(void)
{
}

void CPU::I_Fx15(void)
{
}

void CPU::I_Fx18(void)
{
}

void CPU::I_Fx1E(void)
{
}

void CPU::I_Fx29(void)
{
}

void CPU::I_Fx33(void)
{
}

void CPU::I_Fx55(void)
{
}

void CPU::I_Fx65(void)
{
}
