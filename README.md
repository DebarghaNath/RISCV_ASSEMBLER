# RISC-V Assembler in C++

This project is a simple RISC-V assembler implemented in C++. The assembler translates RISC-V assembly instructions into machine code (binary format). It supports various instruction types including R-type, I-type, S-type, and others, making it a versatile tool for converting human-readable assembly code into the binary code that a RISC-V processor can execute.

## Features

- **Instruction Parsing**: Parses assembly instructions to identify opcodes, registers, and immediate values.
- **Binary Encoding**: Converts assembly instructions into binary format using the appropriate opcode, func3, and func7 fields.
- **Modular Design**: Uses a class-based structure with inheritance to handle different instruction types (e.g., R-type, I-type).
- **Extendable**: Easily extendable to support additional RISC-V instructions and formats by adding new subclasses.

## Structure

- **Register Class**: Converts register names (e.g., `x1`) into their corresponding binary representation.
- **Immediate Class**: Converts immediate integre values (e.g., `10`) into their corresponding binary representation.
- **Instruction Classes**: Handles specific instruction formats with subclasses for different types (e.g., `RTypeInstruction`).
- **InstructionConvert Class**: Main class that integrates all components, processes input assembly lines, and outputs the corresponding machine code.

## Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/DebarghaNath/RISCV_ASSEMBLER
