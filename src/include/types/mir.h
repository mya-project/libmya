#pragma once

#include <stdint.h>

#include "types/dstring.h"
#include "types/hashtable.h"

#define MIR_LIST_INITIAL_SIZE          50
#define MIR_LIST_INCREMENT_SIZE        100
#define MIR_BITFIELD_HASHTABLE_SIZE    1000
#define MIR_INSTRUCTION_HASHTABLE_SIZE 1000
#define MIR_REGISTER_HASHTABLE_SIZE    1000
#define MIR_VARIABLE_HASHTABLE_SIZE    1000

extern const char* mya_types[];

typedef enum mir_type
{
  TYPE_IMMEDIATE,
  TYPE_REGISTER,
} mir_type_t;

/**
 * A bitfield spec type. It's specify the type of the specification for bitfield's value.
 */
typedef enum mir_bitfield_spec_type
{
  FT_FIELDS,      ///< Bitfied spec value has a body with a list of fields. Example: Opcode{ opcode = 0x1, reg = arg1 }
                  ///< On this type, `spec` is the used value with a list of bitfield spec's fields.
  FT_IDENTIFIER,  ///< Bitfield spec value is a identifier. Example: Reg{arg2}
                  ///< On this type, `identifier` is the used value.
  FT_LITERAL,     ///< Bitfield spec value is a literal value. Example: Reg{4}
                  ///< On this type, `value` is the used value.
  FT_SPEC,        ///< Bitfield spec value is a bitfield spec. Example: reg = Reg{2}
                  ///< On this type, `spec` is the used value with an unique bitfield spec.
} mir_bitfield_spec_type_t;

/**
 * A bitfield's field declaration.
 */
typedef struct mir_bitfield_field
{
  dstring_t name;  ///< Name of the field.
  uint32_t size;   ///< Size in bits of the field.
} mir_bitfield_field_t;

/**
 * A bitfield declaration.
 */
typedef struct mir_bitfield
{
  dstring_t name;                ///< Name of the bitfield.
  uint32_t size;                 ///< Size in bits of the bitfield.
  mir_bitfield_field_t* fields;  ///< Array of fields.
  unsigned int fields_length;    ///< Number of elements on the `fields` array.
  unsigned int _fields_size;     ///< Size of the allocated memory for `fields` array.
} mir_bitfield_t;

/**
 * A bitfield or bitfield's field declaration. Examples:
 *   1. Reg{arg1}
 *   2. Opcode { opcode = 0x11, reg = arg1 }
 *
 * In the second example, the `opcode = 0x11` and `reg = arg1` are represented with this struct too, in the `spec` list
 * of the `Opcode{}` specification.
 */
typedef struct mir_bitfield_spec
{
  dstring_t name;                  ///< Name of the bitfield.
  mir_bitfield_spec_type_t type;   ///< Specify the type of this bitfield specification.
  dstring_t identifier;            ///< Bitfield's value identifier.
  int64_t value;                   ///< Bitfield's literal value.
  struct mir_bitfield_spec* spec;  ///< Bitfield's list of field specifications.
  unsigned int spec_length;        ///< Number of elements on the `spec` array.
  unsigned int _spec_size;         ///< Size of the allocated memory for `spec` array.
} mir_bitfield_spec_t;

/**
 * Register declaration.
 */
typedef struct mir_register
{
  dstring_t name;            ///< Register name.
  uint32_t size;             ///< Register size in bits.
  mir_bitfield_spec_t spec;  ///< Register's bitfield specification.
} mir_register_t;

/**
 * An instruction's parameter. Example: inst not[32](arg: register[32])
 */
typedef struct mir_inst_param
{
  dstring_t name;   ///< Name of the parameter.
  mir_type_t type;  ///< Type of the parameter.
  uint32_t size;    ///< Size in bits of the parameter.
} mir_inst_param_t;

/**
 * Instruction declaration.
 */
typedef struct mir_inst
{
  dstring_t name;                  ///< Instruction name.
  uint32_t size;                   ///< Instruction size in bits.
  mir_inst_param_t* parameters;    ///< List of instruction's parameters.
  mir_bitfield_spec_t* fields;     ///< Instruction field's specification list.
  unsigned int fields_length;      ///< Number of elements on the `fields` array.
  unsigned int parameters_length;  ///< Number of paramenters on the `parameters` array.
  unsigned int _fields_size;       ///< Size of the allocated memory for `fields` array.
  unsigned int _parameters_size;   ///< Size of the allocated memory for `parameters` array.
} mir_inst_t;

/**
 * Mya in-memory intermediate representation.
 */
typedef struct mir
{
  mir_bitfield_t* bitfields;  ///< List of bitfields.
  mir_register_t* registers;  ///< List of registers.
  mir_inst_t* instructions;   ///< List of instructions.
  hashtable_t variables;      ///< Hashtable of variables.

  unsigned int bitfields_length;     ///< The number of declared bitfields.
  unsigned int registers_length;     ///< The number of declared registers.
  unsigned int instructions_length;  ///< The number of declared instructions.
  unsigned int _bitfields_size;      ///< The size of the allocated memory for bitfields list.
  unsigned int _registers_size;      ///< The size of the allocated memory for registers list.
  unsigned int _instructions_size;   ///< The size of the allocated memory for instructions list.

  hashtable_t _bitfields_index;     ///< Bitfields indexes.
  hashtable_t _registers_index;     ///< Registers indexes.
  hashtable_t _instructions_index;  ///< Instructions indexes.
} mir_t;
