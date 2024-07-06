#include<random>
#include <cstdint>
#include<iostream>

#include "cpu.h"

uint8_t generateRandomByte() {
	// Create a random device and seed the random number engine
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a distribution that produces values in the range [0, 255]
	std::uniform_int_distribution<uint16_t> dis(0, 255);

	// Generate and return a random byte
	return static_cast<uint8_t>(dis(gen));
}

CPU::CPU(Audio* audio, Display* display, Keyboard* keyboard)
{
	pc = 0x200;  // Program counter is initialized to 0x200 because 0x000 to 0x1FF is reserved for the interpreter itself.
	I = 0;
	sp = -1;
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

	// Initialize peripherals
	this->audio = audio;
	this->keyboard = keyboard;
	this->display = display;
}

CPU::~CPU(void)
{
	delete[] memory;
	delete[] registers;
	delete[] s;
	delete audio;
	delete keyboard;
	delete display;

	audio = nullptr;
	keyboard = nullptr;
	display = nullptr;
}

uint8_t CPU::getMemory(uint16_t addr)
{
	return memory[addr];
}

void CPU::setMemory(uint16_t addr, uint8_t val)
{
	memory[addr] = val;
}

void CPU::decodeAndExecute(uint16_t opcode)
{
	uint8_t firstNibble = (opcode & 0xF000) >> 12;

	switch (firstNibble)
	{
	case 0x0:
		switch (opcode & 0x00FFu)
		{
		case 0xE0:
			I_00E0();
			break;
		case 0xEE:
			I_00EE();
			break;
		default:
			break;
		}
		break;
	case 0x1:
		I_1nnn(opcode);
		break;
	case 0x2:
		I_2nnn(opcode);
		break;
	case 0x3:
		I_3xkk(opcode);
		break;
	case 0x4:
		I_4xkk(opcode);
		break;
	case 0x5:
		I_5xy0(opcode);
		break;
	case 0x6:
		I_6xkk(opcode);
		break;
	case 0x7:
		I_7xkk(opcode);
		break;
	case 0x8:
		switch(opcode & 0x000Fu) 
		{
		case 0x0:
			I_8xy0(opcode);
			break;
		case 0x1:
			I_8xy1(opcode);
			break;
		case 0x2:
			I_8xy2(opcode);
			break;
		case 0x3:
			I_8xy3(opcode);
			break;
		case 0x4:
			I_8xy4(opcode);
			break;
		case 0x5:
			I_8xy5(opcode);
			break;
		case 0x6:
			I_8xy6(opcode);
			break;
		case 0x7:
			I_8xy7(opcode);
			break;
		case 0xE:
			I_8xyE(opcode);
			break;
		default:
			break;
		}
		break;
	case 0x9:
		I_9xy0(opcode);
		break;
	case 0xA:
		I_Annn(opcode);
		break;
	case 0xB:
		I_Bnnn(opcode);
		break;
	case 0xC:
		I_Cxkk(opcode);
		break;
	case 0xD:
		I_Dxyn(opcode);
		break;
	case 0xE:
		switch (opcode & 0x00FFu)
		{
		case 0x9E:
			I_Ex9E(opcode);
			break;
		case 0xA1:
			I_ExA1(opcode);
			break;
		default:
			break;
		}
		break;
	case 0xF:
		switch (opcode & 0x00FFu)
		{
		case 0x07:
			I_Fx07(opcode);
			break;
		case 0x0A:
			I_Fx0A(opcode);
			break;
		case 0x15:
			I_Fx15(opcode);
			break;
		case 0x18:
			I_Fx18(opcode);
			break;
		case 0x1E:
			I_Fx1E(opcode);
			break;
		case 0x29:
			I_Fx29(opcode);
			break;
		case 0x33:
			I_Fx33(opcode);
			break;
		case 0x55:
			I_Fx55(opcode);
			break;
		case 0x65:
			I_Fx65(opcode);
			break;
		}
		break;
	default:
		break;
	}
}

void CPU::emulateCycle()
{
	// Fetch opcode from program loaded into memory
	uint16_t opcode = (memory[pc] << 8) | (memory[pc + 1]);

	std::cout<<"Opcode: 0x" << std::hex << opcode << std::endl;
	std::cout<<"PC: 0x" << std::hex << pc << std::endl;

	// Increment program counter to the address of next instruction
	pc += 2;

	// Decode and Execute the instruction
	decodeAndExecute(opcode);

	// Decrement the delay timer if it is greater than 0
	if (dt) dt--;

	// Decrement the sound timer if it is greater than 0
	if (st) {
		st--;

		if (st > 0)
		{
			audio->playSound();
		}
	}
}

void CPU::I_0nnn(uint16_t opcode)
{
	/*
		Instruction: 0nnn - SYS addr
		Function: Jump to a machine code routine at nnn.
	*/

	uint8_t addr = opcode & 0x0FFFu;
	pc = addr;
}

void CPU::I_00E0(void)
{
	/*
		Instruction: 00E0 - CLS
		Function: Clears the display
	*/
	display->clearDisplay();
}

void CPU::I_00EE(void)
{
	/*
		Instruction: 00EE - RET
		Function: Return from a subroutine.

	*/

	pc = s[sp];
	sp--;
}

void CPU::I_1nnn(uint16_t opcode)
{
	/*
		Instruction: 1nnn - JP addr
		Function: Jump to location nnn.
	*/

	uint16_t addr = opcode & 0x0FFFu;
	pc = addr;
}

void CPU::I_2nnn(uint16_t opcode)
{
	/*
		Instruction: 2nnn - CALL addr
		Function: Call subroutine at nnn.
	*/
	uint16_t addr = opcode & 0x0FFFu;

	sp++;
	s[sp] = pc;
	pc = addr;
}

void CPU::I_3xkk(uint16_t opcode)
{
	/*
		Instruction: 3xkk - SE Vx, byte
		Function: Skip next instruction if Vx = kk.
	*/
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	if (registers[x] == byte)
	{
		pc += 2;
	}
}

void CPU::I_4xkk(uint16_t opcode)
{
	/*
		Instruction: 4xkk - SNE Vx, byte
		Function: Skip next instruction if Vx != kk.
	*/
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	if (registers[x] != byte)
	{
		pc += 2;
	}
}

void CPU::I_5xy0(uint16_t opcode)
{
	/*
		Instruction: 5xy0 - SE Vx, Vy
		Function: Skip next instruction if Vx = Vy.
	*/
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	if (registers[x] == registers[y])
	{
		pc += 2;
	}
}

void CPU::I_6xkk(uint16_t opcode)
{
	/*
		Instruction: 6xkk - LD Vx, byte
		Function: Set Vx = kk.
	*/
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	registers[x] = byte;
}

void CPU::I_7xkk(uint16_t opcode)
{
	/*
		Instruction: 7xkk - ADD Vx, byte
		Function: Set Vx = Vx + kk.
	*/
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	registers[x] += byte;
}

void CPU::I_8xy0(uint16_t opcode)
{
	/*
		Instruction: 8xy0 - LD Vx, Vy
		Function: Set Vx = Vy.
	*/
	 
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	registers[x] = registers[y];
}

void CPU::I_8xy1(uint16_t opcode)
{
	/*
		Instruction: 8xy1 - OR Vx, Vy
		Function: Set Vx = Vx OR Vy.
	*/
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	registers[x] = registers[x] | registers[y];
}

void CPU::I_8xy2(uint16_t opcode)
{
	/*
		Instruction: 8xy2 - AND Vx, Vy
		Function: Set Vx = Vx AND Vy.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	registers[x] = registers[x] & registers[y];
}

void CPU::I_8xy3(uint16_t opcode)
{
	/*
		Instruction: 8xy3 - XOR Vx, Vy
		Function: Set Vx = Vx XOR Vy.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	registers[x] = registers[x] ^ registers[y];
}

void CPU::I_8xy4(uint16_t opcode)
{
	/*
		Instruction: 8xy4 - ADD Vx, Vy
		Function: Set Vx = Vx + Vy, set VF = carry.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	uint16_t sum = registers[x] + registers[y];
	registers[x] = sum & 0x00FFu;
	registers[0x000Fu] = (sum & 0x0F00) >> 8u;
}

void CPU::I_8xy5(uint16_t opcode)
{
	/*
		Instruction: 8xy5 - SUB Vx, Vy
		Function: Set Vx = Vx - Vy, set VF = NOT borrow.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	if (registers[x] > registers[y])
	{
		registers[0x000Fu] = 1;
	}
	else
	{
		registers[0x000Fu] = 0;
	}

	registers[x] = registers[x] - registers[y];
}

void CPU::I_8xy6(uint16_t opcode)
{
	/*
		Instruction: 8xy6 - SHR Vx {, Vy}
		Function: Set Vx = Vx SHR 1.
	*/
	
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	registers[0xFu] = (registers[x] & 0x1u);
	registers[x] = registers[x] >> 1u;
}

void CPU::I_8xy7(uint16_t opcode)
{
	/*
		Instruction: 8xy7 - SUBN Vx, Vy
		Function: Set Vx = Vy - Vx, set VF = NOT borrow.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	if (registers[x] < registers[y])
	{
		registers[0x000Fu] = 1u;
	}
	else
	{
		registers[0x000Fu] = 0u;
	}

	registers[0x000Fu] = registers[y] - registers[x];
}

void CPU::I_8xyE(uint16_t opcode)
{
	/*
		Instruction: 8xyE - SHL Vx {, Vy}
		Function: Set Vx = Vx SHL 1.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	registers[0x000Fu] = (registers[x] & 0x8000u) >> 15u;
	registers[x] = registers[x] << 1u;
}

void CPU::I_9xy0(uint16_t opcode)
{
	/*
		Instruction: 9xy0 - SNE Vx, Vy
		Function: Skip next instruction if Vx != Vy.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	if (registers[x] != registers[y])
	{
		pc += 2;
	}
}

void CPU::I_Annn(uint16_t opcode)
{
	/*
		Instruction: Annn - LD I, addr
		Function: Set I = nnn.
	*/

	I = opcode & 0x0FFFu;
}

void CPU::I_Bnnn(uint16_t opcode)
{
	/*
		Instruction: Bnnn - JP V0, addr
		Function: Jump to location nnn + V0.
	*/

	pc = (opcode & 0x0FFFu) + registers[0];
}

void CPU::I_Cxkk(uint16_t opcode)
{
	/*
		Instruction: Cxkk - RND Vx, byte
		Function: Set Vx = random byte AND kk.
	*/
	
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;
	uint8_t randomNum = generateRandomByte();
	registers[x] = byte & randomNum;
}

void CPU::I_Dxyn(uint16_t opcode)
{
	/*
		Instruction: Dxyn - DRW Vx, Vy, nibble
		Function: Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
	*/

	// Extract operands from opcode
	uint8_t x = (opcode & 0x0F00u) >> 8;
	uint8_t y = (opcode & 0x00F0u) >> 4;
	uint8_t n = opcode & 0x000F;

	// Fetch values from register
	uint8_t Vx = registers[x] % 64;  // Module with 64 ensures out of width values are not drawn out of the screen
	uint8_t Vy = registers[y] % 32;  // Module with 32 ensures out of height values are not drawn out of the screen

	registers[0xF] = 0;  // Carry register is initially set to 0, implying no collision has been detected

	for (int i = 0; i < n; i++) // Loop over all the rows of the sprite
	{
		uint8_t spriteByte = memory[I + i];  // Fetch the sprite row from memory

		for (int j = 0; j < 8; j++) // Loop over all the bits of each row in the sprite
		{
			if (spriteByte & (0x80u >> j)) // If `jth` bit is set to 1
			{
				uint8_t screenPixel = display->getPixel((Vy + i) * 64 + (Vx + j)); // Fetch the pixel from display->vram
				if (screenPixel) // If the pixel is already set to 1, A collision is deteted. Hence, the carry bit is set to 1.
				{
					registers[0xF] = 1;  // Carry/Collision bit is set to 1
				}
				display->setPixel((Vy + i) * 64 + (Vx + j), screenPixel ^ 0xFFFFFFFF); // The value of XOR'ed into the screen
				display->setDrawFlag(true);
			}
		}
	}
}

void CPU::I_Ex9E(uint16_t opcode)
{
	/*
		Instruction: Ex9E - SKP Vx
		Function: Skip next instruction if key with the value of Vx is pressed.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;

	if (keyboard->getKey(registers[x]))
	{
		pc += 2;
	}
}

void CPU::I_ExA1(uint16_t opcode)
{
	/*
		Instruction: ExA1 - SKNP Vx
		Function: Skip next instruction if key with the value of Vx is not pressed.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;

	if (keyboard->getKey(registers[x]) == 0u)
	{
		pc += 2;
	}
}

void CPU::I_Fx07(uint16_t opcode)
{
	/*
		Instruction: Fx07 - LD Vx, DT
		Function: Set Vx = delay timer value.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	registers[x] = dt;
}

void CPU::I_Fx0A(uint16_t opcode)
{
	/*
		Instruction: Fx0A - LD Vx, K
		Function: Wait for a key press, store the value of the key in Vx.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	
	for (int i = 0; i < 16; i++)
	{
		if (keyboard->getKey(i))
		{
			registers[x] = keyboard->getKey(i);
		}
	}

	pc -= 2;
}

void CPU::I_Fx15(uint16_t opcode)
{
	/*
		Instruction: Fx15 - LD DT, Vx
		Function: Set delay timer = Vx.
	*/
	
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	dt = registers[x];
}

void CPU::I_Fx18(uint16_t opcode)
{
	/*
		Instruction: Fx18 - LD ST, Vx
		Function: Set sound timer = Vx.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	st = registers[x];
}

void CPU::I_Fx1E(uint16_t opcode)
{
	/*
		Instruction: Fx1E - ADD I, Vx
		Function: Set I = I + Vx.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	I = I + registers[x];
}

void CPU::I_Fx29(uint16_t opcode)
{
	/*
		Instruction: Fx29 - LD F, Vx
		Function: Set I = location of sprite for digit Vx.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t digit = registers[x];

	I = 0x50u + (5u * digit);
}

void CPU::I_Fx33(uint16_t opcode)
{
	/*
		Instruction: Fx33 - LD B, Vx
		Function: Store BCD representation of Vx in memory locations I, I+1, and I+2.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t val = registers[x];

	memory[I + 2] = val % 10;
	val /= 10;
	memory[I + 1] = val % 10;
	val /= 10;
	memory[I] = val % 10;
}

void CPU::I_Fx55(uint16_t opcode)
{
	/*
		Instruction: Fx55 - LD [I], Vx
		Function: Store registers V0 through Vx in memory starting at location I.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8;
	for (uint8_t i = 0; i <= x; i++)
	{
		memory[I + i] = registers[i];
	}
}

void CPU::I_Fx65(uint16_t opcode)
{
	/*
		Instruction: Fx65 - LD Vx, [I]
		Function: Read registers V0 through Vx from memory starting at location I.
	*/

	uint8_t x = (opcode & 0x0F00u) >> 8;
	for (uint8_t i = 0u; i <= x; i++)
	{
		registers[i] = memory[I + i];
	}
}

