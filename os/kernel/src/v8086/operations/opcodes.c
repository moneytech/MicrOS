#include <stdint.h>
#include <v8086/stack.h>
#include <stdbool.h>
#include "opcodes.h"
#include "arithmetic_operations.h"
#include "ascii_adjustments_operations.h"
#include "stack_operations.h"
#include "jump_operations.h"
#include "internal_funcs.h"
#include "exchange_operations.h"
#include "mov_operations.h"
#include "procedure_operations.h"
#include "string_operations.h"
#include "io_operations.h"
#include "misc_operations.h"

#define NO_CARRY 0
#define CARRY_FLAG_AS_NUMBER bit_get(machine->regs.d.eflags, 1u <<CARRY_FLAG_BIT) >> CARRY_FLAG_BIT

OPCODE_PROTO(add)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode, NO_CARRY, perform_adding);
}

OPCODE_PROTO(push_es)
{
    push_word(machine, machine->sregs.es);
    return OK;
}

OPCODE_PROTO(pop_es)
{
    machine->sregs.es = pop_word(machine);
    return OK;
}

OPCODE_PROTO(or)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode - 0x08, NO_CARRY, perform_or);
}

OPCODE_PROTO(push_cs)
{
    push_word(machine, machine->sregs.cs);
    return OK;
}

OPCODE_PROTO(adc)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode - 0x10, CARRY_FLAG_AS_NUMBER, perform_adding);
}

OPCODE_PROTO(push_ss)
{
    push_word(machine, machine->sregs.ss);
    return OK;
}

OPCODE_PROTO(pop_ss)
{
    machine->sregs.ss = pop_word(machine);
    return OK;
}

OPCODE_PROTO(sbb)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode - 0x18, CARRY_FLAG_AS_NUMBER, perform_subtracting);
}

OPCODE_PROTO(push_ds)
{
    push_word(machine, machine->sregs.ds);
    return OK;
}

OPCODE_PROTO(pop_ds)
{
    machine->sregs.ds = pop_word(machine);
    return OK;
}

OPCODE_PROTO(and)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode - 0x20, 0, perform_and);
}

OPCODE_PROTO(daa)
{
    return adjust_after_add_sub_packed(machine, false);
}

OPCODE_PROTO(sub)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode - 0x28, NO_CARRY, perform_subtracting);
}

OPCODE_PROTO(das)
{
    return adjust_after_add_sub_packed(machine, true);
}

OPCODE_PROTO(xor)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode - 0x30, NO_CARRY, perform_xor);
}

OPCODE_PROTO(aaa)
{
    return adjust_after_add_sub(machine, false);
}

OPCODE_PROTO(cmp)
{
    return perform_artihmetic_or_logical_instruction(machine, opcode - 0x30, NO_CARRY, perform_cmp);
}

OPCODE_PROTO(aas)
{
    return adjust_after_add_sub(machine, true);
}

OPCODE_PROTO(inc)
{
    return perform_inc_dec(machine, opcode, false);
}

OPCODE_PROTO(dec)
{
    return perform_inc_dec(machine, opcode, true);
}

OPCODE_PROTO(push_gpr)
{
    return push_gpr(machine, opcode);
}

OPCODE_PROTO(pop_gpr)
{
    return pop_gpr(machine, opcode);
}

OPCODE_PROTO(jcc)
{
    return jump_short_relative_on_condition(machine, opcode);
}

OPCODE_PROTO(group1)
{
    uint8_t mod_rm = read_byte_from_pointer(machine->Memory, get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset));
    machine->internal_state.IPOffset += 1;
    uint8_t recalculated_opcode = opcode - 0x80;
    switch(get_reg(mod_rm))
    {
        case 0: //ADD
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm, NO_CARRY,
                                                                     perform_adding);
        case 1: //OR
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm, NO_CARRY, perform_or);
        case 2: //ADC
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm,
                                                                     CARRY_FLAG_AS_NUMBER, perform_adding);
        case 3: //SBB
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm,
                                                                     CARRY_FLAG_AS_NUMBER, perform_subtracting);
        case 4: //AND
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm, NO_CARRY, perform_and);
        case 5: //SUB
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm, NO_CARRY,
                                                                     perform_subtracting);
        case 6: //XOR
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm, NO_CARRY, perform_xor);
        case 7: //CMP
            return perform_arithmetic_or_logical_instruction_group(machine, recalculated_opcode, mod_rm, NO_CARRY, perform_cmp);
        default:
            return BAD_REG;
    }
}

OPCODE_PROTO(test)
{
    return execute_test(machine, opcode);
}

OPCODE_PROTO(xchg)
{
    return perform_exchange_rm(machine, opcode);
}

OPCODE_PROTO(mov_rm)
{
    return perform_mov_rm(machine, opcode);
}

OPCODE_PROTO(mov_segment)
{
    return perform_mov_segment(machine, opcode);
}

OPCODE_PROTO(lea)
{
    return perform_lea(machine);
}

OPCODE_PROTO(pop_rm)
{
    return pop_rm(machine);
}

OPCODE_PROTO(xchg_ax)
{
    return perform_exchange_ax_register(machine, opcode);
}

OPCODE_PROTO(cbw)
{
    return convert_byte_to_word(machine);
}

OPCODE_PROTO(cwd)
{
    return convert_word_to_double(machine);
}

OPCODE_PROTO(far_call)
{
    return far_call(machine);
}

OPCODE_PROTO(pushf)
{
    push_word(machine, machine->regs.w.flags);
    return OK;
}

OPCODE_PROTO(popf)
{
    machine->regs.w.flags = pop_word(machine);
    return OK;
}

OPCODE_PROTO(sahf)
{
    return store_flags(machine);
}

OPCODE_PROTO(lahf)
{
    return load_flags(machine);
}

OPCODE_PROTO(mov_moffset)
{
    return perform_mov_moffset(machine, opcode);
}
OPCODE_PROTO(movsb)
{
    return perform_movs(machine, 8);
}
OPCODE_PROTO(movsw)
{
    return perform_movs(machine, machine->internal_state.operand_32_bit ? 32: 16);
}
OPCODE_PROTO(cmpsb)
{
    return perform_cmps(machine, 8);
}
OPCODE_PROTO(cmpsw)
{
    return perform_cmps(machine, machine->internal_state.operand_32_bit ? 32: 16);
}
OPCODE_PROTO(test_imm)
{
    return execute_test_immediate(machine, opcode);
}
OPCODE_PROTO(stosb)
{
    return perform_stos(machine, 8);
}
OPCODE_PROTO(stosw)
{
    return perform_stos(machine, machine->internal_state.operand_32_bit ? 32: 16);
}
OPCODE_PROTO(lodsb)
{
    return perform_lods(machine, 8);
}
OPCODE_PROTO(lodsw)
{
    return perform_lods(machine, machine->internal_state.operand_32_bit ? 32: 16);
}
OPCODE_PROTO(scasb)
{
    return perform_scas(machine, 8);
}
OPCODE_PROTO(scasw)
{
    return perform_scas(machine, machine->internal_state.operand_32_bit ? 32: 16);
}
OPCODE_PROTO(mov_gpr_imm)
{
    return perform_mov_gpr_imm(machine, opcode);
}


/*
 *     //INT, imm and INT 3 and INTO
    else if(opcode >= 0xcc && opcode <= 0xce)
    {
        uint8_t interrupt_number = 3;
        if(opcode == 0xcd) //INT, imm
        {
            interrupt_number = read_byte_from_pointer(machine->Memory, get_absolute_address(machine->sregs.cs, machine->IP.w.ip + machine->internal_state.IPOffset));
            machine->internal_state.IPOffset += 1;
        }
        else if(opcode == 0xce) //INTO
        {
            if(!bit_get(machine->regs.w.flags, 1u << OVERFLOW_FLAG_BIT)) goto recalculate_ip;
            interrupt_number = 4;
        }
    }
 */