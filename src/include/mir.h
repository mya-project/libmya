#pragma once

#include "types/mir.h"

/**
 * Initializes a MIR struct.
 *
 * @param mir  The struct to be initialized.
 */
void
mir_init(mir_t* mir);

/**
 * Closes the given MIR instruction.
 *
 * @param mir  The struct to be closed.
 */
void
mir_close(mir_t* mir);

/**
 * Add a new bitfield declaration.
 *
 * @param mir   The MIR where the bitfield will be added.
 * @param name  The name of the bitfield.
 * @param size  The size in bits of the bitfield.
 *
 * @return  Pointer for the new bitfield declaration.
 */
mir_bitfield_t*
mir_add_bitfield(mir_t* mir, const char* name, uint32_t size);

/**
 * Get the bitfield declaration with the given name.
 *
 * @param mir   The MIR where to get the bitfield.
 * @param name  Name of the bitifield.
 *
 * @return  Pointer fot the bitfield declaration.
 * @return  NULL when the bitfield doesn't exists.
 */
mir_bitfield_t*
mir_get_bitfield(mir_t* mir, const char* name);

/**
 * Add a new field to a bitfield declaration.
 *
 * @param bitfield  The bitfield declaration.
 * @param name      Name of the field.
 * @param size      Size in bits of the field.
 *
 * @return  Pointer for the new field.
 */
mir_bitfield_field_t*
mir_bitfield_add_field(mir_bitfield_t* bitfield, const char* name, uint32_t size);

/**
 * Get the field with the given name from the bitfield declaration.
 *
 * @param bitfield  The bitfield declaration.
 * @param name      Name of the field.
 *
 * @return  Pointer for the field.
 * @return  NULL when the field doesn't exists.
 */
mir_bitfield_field_t*
mir_bitfield_get_field(mir_bitfield_t* bitfield, const char* name);

/**
 * Closes the given bitfield.
 *
 * @param bitfield  The bitfield to be closed.
 */
void
mir_bitfield_close(mir_bitfield_t* bitfield);

/**
 * Add a new register declaration for the specified MIR.
 *
 * @param mir   The MIR where do add the register declaration.
 * @param name  The name of the register.
 * @param size  The size in bits of the register.
 *
 * @return  Pointer for the new register declaration.
 */
mir_register_t*
mir_add_register(mir_t* mir, const char* name, uint32_t size);

/**
 * Get a register declaration from the specified MIR.
 *
 * @param mir   The MIR where to get the register declaration.
 * @param name  The name of the register.
 *
 * @return  Pointer for the register.
 * @return  NULL when the register doesn't exists.
 */
mir_register_t*
mir_get_register(mir_t* mir, const char* name);

/**
 * Closes the given register.
 *
 * @param reg  The register to be closed.
 */
void
mir_register_close(mir_register_t* reg);

/**
 * Add a new instruction declaration to MIR.
 *
 * @param mir   The MIR where to add the instruction.
 * @param name  Name of the instruction.
 * @param size  The size in bits of the instruction.
 *
 * @return  Pointer to new added instruction.
 */
mir_inst_t*
mir_add_instruction(mir_t* mir, const char* name, uint32_t size);

/**
 * Get an instruction declaration.
 *
 * @param mir   The MIR where to get the instruction.
 * @param name  Name of the instruction.
 *
 * @return  Pointer for the instruction.
 * @return  NULL when the instruction doesn't exists.
 */
mir_inst_t*
mir_get_instruction(mir_t* mir, const char* name);

/**
 * Add a new parameter specification to an instruction.
 *
 * @param inst  The instruction where to add the parameter.
 * @param name  Name of the paramameter.
 * @param type  Type of the parameter.
 * @param size  Size in bits of the parameter.
 *
 * @return  Pointer to new added parameter.
 */
mir_inst_param_t*
mir_instruction_add_param(mir_inst_t* inst, const char* name, mir_type_t type, uint32_t size);

/**
 * Get a parameter from an instruction declaration.
 *
 * @param inst  The instruction where to get the parameter.
 * @param name  The parameter name.
 *
 * @return  Pointer for the parameter.
 * @return  NULL when the parameter doesn't exists.
 */
mir_inst_param_t*
mir_instruction_get_param(mir_inst_t* inst, const char* name);

/**
 * Add a new body field to the given instruction.
 *
 * @param inst  The instruction where to add the field.
 * @param name  Name of the field.
 * @param type  Type of the field.
 *
 * @return  Pointer to new added body field.
 */
mir_bitfield_spec_t*
mir_instruction_add_field(mir_inst_t* inst, const char* name, mir_bitfield_spec_type_t type);

/**
 * Get the body field from the instruction.
 *
 * @param inst  The instruction where to get the field.
 * @param name  Name of the field.
 *
 * @return  Pointer for the field.
 * @return  NULL when the field doesn't exists.
 */
mir_bitfield_spec_t*
mir_instruction_get_field(mir_inst_t* inst, const char* name);

/**
 * Closes the given instruction.
 *
 * @param inst  Instruction to be closed.
 */
void
mir_instruction_close(mir_inst_t* inst);

/**
 * Add a new bitfield spec's field to the given bitfield spec. It's used on bitfield specs with fields.
 * Example:
 *   Opcode {
 *     a = 1,
 *     b = 2,
 *   }
 *
 * Where `Opcode { ... }` itself is a bitfield spec, and `a = 1` and `b = 2` are bitfield specs too.
 *
 * @param spec  The bitfield spec where to add the field spec.
 * @param name  Name of the field.
 * @param type  Type of the field.
 *
 * @return  Pointer for the new bitfield spec's field.
 */
mir_bitfield_spec_t*
mir_bitfield_spec_add_field(mir_bitfield_spec_t* spec, const char* name, mir_bitfield_spec_type_t type);

/**
 * Get a bitfield spec's field from the given bitfield spec.
 *
 * @param spec  The bitfield spec where to get the field.
 * @param name  Name of the field.
 *
 * @return  Pointer for the field.
 * @return  NULL when the field doesn't exists.
 */
mir_bitfield_spec_t*
mir_bitfield_spec_get_field(mir_bitfield_spec_t* spec, const char* name);

/**
 * Closes the given bitfield spec.
 *
 * @param spec  The bitfield spec to be closed.
 */
void
mir_bitfield_spec_close(mir_bitfield_spec_t* spec);
