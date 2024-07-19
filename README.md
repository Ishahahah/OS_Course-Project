# MULTIPROGRAMMING OPERATING SYSTEM
This repository contains the implementation of a virtual multiprogramming operating system as part of an Operating System course project. The project consists of three phases, with Phase 3 being the final phase. The goal of the project is to understand the general concepts of multiprogramming operating systems and to write assembly programs that can be executed within this environment.


## PROJECT PHASES
1. Phase 1:  Understand Single Programming Concept.
2. Phase 2: Implementation of paging mechanisms in an operating system
            Address translation and page tables
3. Phase 3: The final phase of the project.

   The main objectives of this phase are:
   - Implementing process management routines, such as process creation, termination, and scheduling.
   - Developing memory management routines, including memory allocation and deallocation.
   - Implementing input/output (I/O) routines for device management.
   - Writing assembly programs that can be executed within the multiprogramming operating system.


  
## MACHINE SPECIFICATIONS
  The MOS computer is described from two points of view: the “virtual” machine seen by the
  typical user and the “real” machine used by the MOS designer/implementer.


## THE VIRTUAL MACHINE
- Storage: The storage consists of a maximum of 100 words, addressed from 00 to 99. Each word is divided into four one-byte units, allowing for a wide range of characters acceptable by the host machine.
- CPU: The CPU has three registers of interest:
  - General Register (R): A four-byte register used for general-purpose operations.
  - Boolean Toggle (C): A one-byte register that can hold either 'T' (true) or 'F' (false).
  - Instruction Counter (IC): A two-byte register that keeps track of the current instruction's address.
    
   ![Virtual user machine](https://github.com/poojaindulkar/MULTIPROGRAMMING-OPERATING-SYSTEM/blob/main/Virtual%20user%20machine.png?raw=true)
    
- Instruction: Instructions are divided into two parts:
  - Operation Code (Opcode): The two high-order bytes of the word represent the operation code of an instruction.
  - Operand Address: The two low-order bytes of the word indicate the address of the operand in the storage.
    
  ### INSTRUCTION SET

  
    
           Instruction                                          
     |   Opcode    |    Operand      |            Description                  |
     |-------------|-----------------|-----------------------------------------|
     | GD          |       -         | Read the first 40 columns of a card     |
     | PD          |       -         | Print a new line of 40 characters       |
     | LR          |    Address      | Load a word from storage into R         |
     | SR          |    Address      | Store the content of R into storage     |
     | CR          |    Address      | Compare the content of R with storage   |
     | BT          |    Address      | Branch to the specified address if C=T  |
     | H           |      -          | Halt the program execution              |
    

   

## Tools used
- Gcc compiler
- Gdb

