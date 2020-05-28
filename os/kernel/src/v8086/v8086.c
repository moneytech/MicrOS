#include "v8086.h"
#include "../memory/heap/heap.h"
#include <string.h>
#include "../assembly/io.h"
#include "./memory_operations.h"
#include "./stack.h"
#include "./mod_rm_parsing.h"
#include "./operations/internal_funcs.h"
#include "./operations/arithmetic_operations.h"
#include "./operations/opcodes.h"

int16_t parse_and_execute_instruction(v8086* machine);

void v8086_set_8086_instruction_set(v8086* machine)
{
    GROUP_OF_OPCODES(0x00u, 0x05u, add);
    ASSIGN_OPCODE(0x06, push_es);
    ASSIGN_OPCODE(0x07, pop_es);
    GROUP_OF_OPCODES(0x08u, 0x0du, or);
    ASSIGN_OPCODE(0x0eu, push_cs);
    //THERE IS NO 2-BYTES OPCODES
    ASSIGN_NULL(0x0fu);
    GROUP_OF_OPCODES(0x10u, 0x15u, adc);
    ASSIGN_OPCODE(0x16u, push_ss);
    ASSIGN_OPCODE(0x17u, pop_ss);
    GROUP_OF_OPCODES(0x18u, 0x1du, sbb);
    ASSIGN_OPCODE(0x1eu, push_ds);
    ASSIGN_OPCODE(0x1fu, pop_ds);
    GROUP_OF_OPCODES(0x20u, 0x25u, and);
    //RESERVED TO SEG=ES PREFIX
    ASSIGN_NULL(0x26u);
    ASSIGN_OPCODE(0x27u, daa);
    GROUP_OF_OPCODES(0x28u, 0x2du, sub);
    //RESERVED TO SEG=CS PREFIX
    ASSIGN_NULL(0x2eu);
    ASSIGN_OPCODE(0x2fu, das);
    GROUP_OF_OPCODES(0x30u, 0x35u, xor);
    //RESERVED TO SEG=SS PREFIX
    ASSIGN_NULL(0x36u);
    ASSIGN_OPCODE(0x37u, aaa);
    GROUP_OF_OPCODES(0x38u, 0x3du, cmp);
    //RESERVED TO SEG=DS PREFIX
    ASSIGN_NULL(0x3eu);
    ASSIGN_OPCODE(0x3fu, aas);
    GROUP_OF_OPCODES(0x40u, 0x47u, inc);
    GROUP_OF_OPCODES(0x48u, 0x4f, dec);
    GROUP_OF_OPCODES(0x50u, 0x57u, push_gpr);
    GROUP_OF_OPCODES(0x58u, 0x5fu, pop_gpr);
    //NOT DEFINED IN 8086 processor
    for(uint8_t i = 0x60u; i <= 0x6fu; i++) ASSIGN_NULL(i);
    GROUP_OF_OPCODES(0x70u, 0x7fu, jcc);
    GROUP_OF_OPCODES(0x80u, 0x83u, group1);
    GROUP_OF_OPCODES(0x84u, 0x85u, test);
    GROUP_OF_OPCODES(0x86u, 0x87u, xchg);
    GROUP_OF_OPCODES(0x88u, 0x8bu, mov_rm);
    ASSIGN_OPCODE(0x8cu, mov_segment);
    ASSIGN_OPCODE(0x8du, lea);
    ASSIGN_OPCODE(0x8eu, mov_segment);
    ASSIGN_OPCODE(0x8fu, pop_rm);
    GROUP_OF_OPCODES(0x90u, 0x97u, xchg_ax);
    ASSIGN_OPCODE(0x98u, cbw);
    ASSIGN_OPCODE(0x99u, cwd);
    ASSIGN_OPCODE(0x9au, far_call);
    //NO COPROCESSOR
    ASSIGN_NULL(0x9bu);
    ASSIGN_OPCODE(0x9cu, pushf);
    ASSIGN_OPCODE(0x9du, popf);
    ASSIGN_OPCODE(0x9eu, sahf);
    ASSIGN_OPCODE(0x9fu, lahf);
    GROUP_OF_OPCODES(0xa0u, 0xa3u, mov_moffset);
    ASSIGN_OPCODE(0xa4u, movsb);
    ASSIGN_OPCODE(0xa5u, movsw);
    ASSIGN_OPCODE(0xa6u, cmpsb);
    ASSIGN_OPCODE(0xa7u, cmpsw);
    GROUP_OF_OPCODES(0xa8u, 0xa9u, test_imm);
    ASSIGN_OPCODE(0xaau, stosb);
    ASSIGN_OPCODE(0xabu, stosw);
    ASSIGN_OPCODE(0xacu, lodsb);
    ASSIGN_OPCODE(0xadu, lodsw);
    ASSIGN_OPCODE(0xaeu, scasb);
    ASSIGN_OPCODE(0xafu, scasw);
    GROUP_OF_OPCODES(0xb0u, 0xbfu, mov_gpr_imm);
}

v8086* v8086_create_machine()
{
    v8086* machine = (v8086*) heap_kernel_alloc(sizeof(v8086), 0);
    if(machine == NULL) return NULL;
    memset(machine, 0, sizeof(v8086));
    machine->regs.x.flags = 0x2;
    machine->sregs.cs = 0xf000;
    machine->IP.w.ip = 0xfff0;
	memcpy(machine->Memory, (void*)0xc0000000, 0x100000);
    v8086_set_8086_instruction_set(machine);
    return machine;
}

int16_t v8086_call_function(v8086* machine)
{
    while(!(machine->IP.w.ip == 0xFFFF && machine->sregs.cs == 0xFFFF))
    {
        int16_t status = parse_and_execute_instruction(machine);
        if(status != OK) return status;
    }
    return OK;
}

int16_t v8086_call_int(v8086* machine, int16_t num)
{
    if ((num < 0) || (num > 0xFF)) return BAD_INT_NUMBER;
    machine -> IP.w.ip = read_word_from_pointer(machine->Memory, get_absolute_address(0, num * 4));
    machine -> sregs.cs = read_word_from_pointer(machine->Memory, get_absolute_address(0, num * 4 + 2));
    push_word(machine, machine->regs.w.flags);
    push_word(machine, 0xFFFF);
    push_word(machine, 0xFFFF);
    int16_t x = v8086_call_function(machine);
    if(x != OK) return x;
    return num;
}

int16_t parse_and_execute_instruction(v8086* machine)
{
    machine->internal_state.IPOffset = 0;
    machine->internal_state.operand_32_bit = 0;
    machine->internal_state.segment_reg_select = DEFAULT;
    machine->internal_state.rep_prefix = NONE;

    int16_t status = OK;

    //Maybe opcode, an be also prefix
    uint8_t opcode;
    decode: opcode = read_byte_from_pointer(machine->Memory, get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset));
    uint32_t temp = get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset);
    uint8_t* ptr_to_opcode = get_byte_pointer(machine->Memory, get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset));
    machine->internal_state.IPOffset += 1;
    
    //PREFIXES
    //Segment Prefix CS DS ES SS
    if((opcode & 0x7u) == 0x6 && ((opcode >> 5u) & 0x7u) == 0x1u) //001XX110 pattern where XX is number of segment
    {
        machine->internal_state.segment_reg_select = (opcode >> 3u) & 0x3u;
        goto decode; //continue parsing opcode;
    }
    //Segment Prefix FS
    else if(opcode == 0x64)
    {
        machine->internal_state.segment_reg_select = FS;
        goto decode; //continue parsing opcode;
    }
    //Segment Prefix GS
    else if(opcode == 0x65)
    {
        machine->internal_state.segment_reg_select = GS;
        goto decode; //continue parsing opcode;
    }
    //Operand Size Prefix
    else if(opcode == 0x66)
    {
        machine->internal_state.operand_32_bit = 1;
        goto decode; //continue parsing opcode;
    }
    //REPNE Prefix
    else if(opcode == 0xF2)
    {
        machine->internal_state.rep_prefix = REPNE;
        goto decode; //continue parsing opcode;
    }
    //REP/REPE Prefix
    else if(opcode == 0xF3)
    {
        machine->internal_state.rep_prefix = REP_REPE;
        goto decode; //continue parsing opcode;
    }
    //LOCK Prefix
    else if(opcode == 0xF0)
    {
        goto decode; //ommit prefix, contniue parsinf opcode; 
    }

    //LOAD Operations group
    //LDS or LES
    else if(opcode >= 0xc4 && opcode <= 0xc5)
    {
        uint8_t mod_rm = read_byte_from_pointer(machine->Memory, get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset));
        machine->internal_state.IPOffset += 1;

        uint16_t* segment_register;
        if(opcode == 0xc4) segment_register = select_segment_register(machine, ES);
        else segment_register = select_segment_register(machine, DS);
        if(segment_register == NULL) return UNDEFINED_SEGMENT_REGISTER;
        uint16_t* source = get_memory_from_mode(machine, mod_rm, 16);
        if(source == NULL) return UNABLE_GET_MEMORY;

        if(machine->internal_state.operand_32_bit)
        {
            uint32_t* dest = get_dword_register(machine, get_reg(mod_rm));
            *dest = *((uint32_t*) source);
            *segment_register = *(source+2);
        }
        else
        {
            uint16_t* dest = get_word_register(machine, get_reg(mod_rm));
            *dest = *source;
            *segment_register = *(source+1);
        }
        
    }
    //FLAG Setting and clearing Group
    //CMC
    else if(opcode == 0xf5)
        bit_flip(machine->regs.w.flags, 1u <<CARRY_FLAG_BIT);
    //CLC
    else if(opcode == 0xf8)
        bit_clear(machine->regs.w.flags, 1u <<CARRY_FLAG_BIT);
    //STC
    else if(opcode == 0xf9)
        bit_set(machine->regs.w.flags, 1u <<CARRY_FLAG_BIT);
    //CLI
    else if(opcode == 0xfa)
        bit_clear(machine->regs.w.flags, 1u <<INTERRUPT_FLAG_BIT);
    //STI
    else if(opcode == 0xfb)
        bit_set(machine->regs.w.flags, 1u <<INTERRUPT_FLAG_BIT);
    //CLD
    else if(opcode == 0xfc)
        bit_clear(machine->regs.w.flags, 1u <<DIRECTION_FLAG_BIT);
    //STD
    else if(opcode == 0xfd)
        bit_set(machine->regs.w.flags, 1u <<DIRECTION_FLAG_BIT);
    //MISC group
    //XLAT/XLATB
    else if(opcode == 0xd7)
    {
        uint8_t tempAL = machine->regs.h.al;
        uint16_t* segment;
        if(machine->internal_state.segment_reg_select != DEFAULT)
            segment = select_segment_register(machine, machine->internal_state.segment_reg_select);
        else
            segment = select_segment_register(machine, DS);
        if(segment == NULL) return UNDEFINED_SEGMENT_REGISTER;
        machine->regs.h.al = read_byte_from_pointer(machine->Memory, get_absolute_address(*segment, machine->regs.w.bx + tempAL));
    }
    //GROUP 4
    else if(opcode == 0xfe)
    {
        uint8_t mod_rm = read_byte_from_pointer(machine->Memory, get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset));
        machine->internal_state.IPOffset += 1;
        uint8_t width = 8;

        void* dest = get_memory_from_mode(machine, mod_rm, width);
        if(dest == NULL) return UNABLE_GET_MEMORY;
        switch(get_reg(mod_rm))
        {
            case 0: //INC rm8
                status = perform_inc(machine, dest, width);
                break;
            case 1: //DEC rm8
                status = perform_dec(machine, dest, width);
                break;
            default:
                return UNDEFINED_OPCODE;
        }
    }
    //GROUP 5
    else if(opcode == 0xff)
    {
        uint8_t mod_rm = read_byte_from_pointer(machine->Memory, get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset));
        machine->internal_state.IPOffset += 1;
        uint8_t width = 16;
        if(machine->internal_state.operand_32_bit) width = 32;

        void* dest = get_memory_from_mode(machine, mod_rm, width);
        if(dest == NULL) return UNABLE_GET_MEMORY;
        switch(get_reg(mod_rm))
        {
            case 0: //INC rm8
                status = perform_inc(machine, dest, width);
                break;
            case 1: //DEC rm8
                status = perform_dec(machine, dest, width);
                break;
            case 2: //Near absolute indirect call
                machine->IP.w.ip += machine->internal_state.IPOffset;
                push_word(machine, machine->IP.w.ip);
                if(width == 16)
                    machine->IP.w.ip += *((uint16_t*) dest);
                else return BAD_WIDTH;
                machine->internal_state.IPOffset = 0;
                break;
            case 3: // Far absolute indirect call
                machine->IP.w.ip += machine->internal_state.IPOffset;
                push_word(machine, machine->sregs.cs);
                push_word(machine, machine->IP.w.ip);
                machine->IP.w.ip = *((uint16_t*) dest);
                machine->sregs.cs = *(((uint16_t*)dest)+1);
                machine->internal_state.IPOffset = 0;
                break;
            case 4: //Near absolute indirect jmp
                if(width == 16)
                    machine->IP.w.ip += *((uint16_t*) dest);
                else return BAD_WIDTH;
                machine->internal_state.IPOffset = 0;
                break;
            case 5: //Far absolute indirect jmp
                machine->IP.w.ip = *((uint16_t*) dest);
                machine->sregs.cs = *(((uint16_t*)dest)+1);
                machine->internal_state.IPOffset = 0;
                break;
            case 6:
                if(width == 16) push_word(machine, *((uint16_t*)dest));
                else if(width == 32) push_dword(machine, *((uint32_t*)dest));
                else return BAD_WIDTH;
                break;
            default:
                return UNDEFINED_OPCODE;
        }
    }
    else return UNDEFINED_OPCODE;
    recalculate_ip: machine->IP.w.ip += machine->internal_state.IPOffset;

    return status;
}