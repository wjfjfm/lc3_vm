/* lc3.c */
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
/* unix */
#include <unistd.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>


/* Registers */
enum
{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /* program counter */
    R_COND, /* condition flags */
    R_COUNT,
};

/* Opcodes */
enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP,    /* execute trap */
};

/* Condition Flags */
enum
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};

/* Memory Mapped Registers */
enum
{
    MR_KBSR = 0xFE00, /*keyboard status */
    MR_KBDR = 0xFE02, /*keyboard data */
};

/* TRAP Codes */
enum
{
    TRAP_GETC = 0x20,  /* get character from keyboard, not echoed onto the terminal */
    TRAP_OUT = 0x21,   /* output a character */
    TRAP_PUTS = 0x22,  /* output a word string */
    TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
    TRAP_PUTSP = 0x24, /* output a byte string */
    TRAP_HALT = 0x25   /* halt the program */
};


/* Memory Storage */
/* 65536 locations */
uint16_t memory[UINT16_MAX];

/* Register Storage */
uint16_t reg[R_COUNT];


/* Sign Extend */
uint16_t sign_extend(uint16_t x, int bit_count)
{
    // TODO
}


int main(int argc, const char* argv[]) {
    /* Load Arguments */
    if (argc < 2)
    {
        /* show usage string */
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j=1; j<argc; ++j)
    {
        if (!read_image(argv[j]))
        {
            printf("failed to lead image: %s\n", argv[j]);
            exit(1);
        }
    }

    /* Setup */
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    /* since exactly one condition flag should be set at any give time, set the Z flag*/
    reg[R_COND] = FL_ZRO;

    /* set the PC to starting position */
    /* 0x3000 is the default */
    enum { PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    int running = 1;
    while (running) {
        /* FETCH */
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op)
        {
            case OP_ADD:
                /* ADD */
                {
                    /* destination register (DR) */
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6)
                }
                break;
            case OP_AND:
                /* AND */
                {
                }
                break;
            case OP_NOT:
                /* NOT */
                {
                }
                break;
            case OP_BR:
                /* BR */
                {
                }
                break;
            case OP_JMP:
                /* JMP */
                {
                }
                break;
            case OP_JSR:
                /* JSR */
                {
                }
                break;
            case OP_LD:
                /* LD */
                {
                }
                break;
            case OP_LDI:
                /* LDI */
                {
                }
                break;
            case OP_LDR:
                /* LDR */
                {
                }
                break;
            case OP_LEA:
                /* LEA */
                {
                }
                break;
            case OP_ST:
                /* ST */
                {
                }
                break;
            case OP_STI:
                /* STI */
                {
                }
                break;
            case OP_STR:
                /* STR */
                {
                }
                break;
            case OP_TRAP:
                /* TRAP */
                {
                }
                break;
            case OP_RES:
            case OP_RTI:
            default:
                /* BAD OPCODE */
                abort();
                break;

        }
    }
    /* Shutdown */
    restore_input_buffering();

}


