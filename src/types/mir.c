#include <stdlib.h>
#include <string.h>

#include "dstring.h"
#include "hashtable.h"
#include "mir.h"

void
mir_init(mir_t* mir)
{
  mir->bitfields = malloc(sizeof(mir_bitfield_t) * MIR_LIST_INITIAL_SIZE);
  mir->bitfields_length = 0;
  mir->_bitfields_size = MIR_LIST_INITIAL_SIZE;

  mir->registers = malloc(sizeof(mir_register_t) * MIR_LIST_INITIAL_SIZE);
  mir->registers_length = 0;
  mir->_registers_size = MIR_LIST_INITIAL_SIZE;

  mir->instructions = malloc(sizeof(mir_inst_t) * MIR_LIST_INITIAL_SIZE);
  mir->instructions_length = 0;
  mir->_instructions_size = MIR_LIST_INITIAL_SIZE;

  hashtable_init(&mir->variables, MIR_VARIABLE_HASHTABLE_SIZE);
  hashtable_init(&mir->_bitfields_index, MIR_BITFIELD_HASHTABLE_SIZE);
  hashtable_init(&mir->_instructions_index, MIR_INSTRUCTION_HASHTABLE_SIZE);
  hashtable_init(&mir->_registers_index, MIR_REGISTER_HASHTABLE_SIZE);
}

void
mir_close(mir_t* mir)
{
  for (int i = 0; i < mir->bitfields_length; i++) {
    mir_bitfield_close(&mir->bitfields[i]);
  }

  for (int i = 0; i < mir->registers_length; i++) {
    mir_register_close(&mir->registers[i]);
  }

  for (int i = 0; i < mir->instructions_length; i++) {
    mir_instruction_close(&mir->instructions[i]);
  }

  free(mir->bitfields);
  free(mir->registers);
  free(mir->instructions);
  mir->bitfields = NULL;
  mir->registers = NULL;
  mir->instructions = NULL;

  hashtable_close(&mir->variables);
  hashtable_close(&mir->_bitfields_index);
  hashtable_close(&mir->_registers_index);
  hashtable_close(&mir->_instructions_index);
}

mir_bitfield_t*
mir_add_bitfield(mir_t* mir, const char* name, uint32_t size)
{
  mir_bitfield_t* bitfield;

  if (mir->_bitfields_size < mir->bitfields_length + 1) {
    mir->_bitfields_size += MIR_LIST_INCREMENT_SIZE;
    mir->bitfields = realloc(mir->bitfields, sizeof(mir_bitfield_t) * mir->_bitfields_size);
  }

  bitfield = &mir->bitfields[mir->bitfields_length];
  bitfield->fields = NULL;
  bitfield->fields_length = 0;
  bitfield->_fields_size = 0;
  bitfield->size = size;
  dstring_init(&bitfield->name, 0);
  dstring_copy(&bitfield->name, name);

  hashtable_set(&mir->_bitfields_index, name, mir->bitfields_length);

  mir->bitfields_length++;
  return bitfield;
}

mir_bitfield_t*
mir_get_bitfield(mir_t* mir, const char* name)
{
  int64_t index;

  if (hashtable_get(&mir->_bitfields_index, name, &index) != ERR_OK) {
    return NULL;
  }

  return &mir->bitfields[index];
}

mir_bitfield_field_t*
mir_bitfield_add_field(mir_bitfield_t* bitfield, const char* name, uint32_t size)
{
  mir_bitfield_field_t* field;

  if (bitfield->_fields_size < bitfield->fields_length + 1) {
    bitfield->_fields_size += MIR_LIST_INCREMENT_SIZE;
    bitfield->fields = realloc(bitfield->fields, sizeof(mir_bitfield_field_t) * bitfield->_fields_size);
  }

  field = &bitfield->fields[bitfield->fields_length++];
  field->size = size;
  dstring_init(&field->name, 0);
  dstring_copy(&field->name, name);

  return field;
}

mir_bitfield_field_t*
mir_bitfield_get_field(mir_bitfield_t* bitfield, const char* name)
{
  for (int i = 0; i < bitfield->fields_length; i++) {
    if (strcmp(bitfield->fields[i].name.data, name) == 0) {
      return &bitfield->fields[i];
    }
  }

  return NULL;
}

void
mir_bitfield_close(mir_bitfield_t* bitfield)
{
  for (int i = 0; i < bitfield->fields_length; i++) {
    dstring_close(&bitfield->fields[i].name);
  }

  dstring_close(&bitfield->name);
  free(bitfield->fields);
  bitfield->fields = NULL;
}

mir_register_t*
mir_add_register(mir_t* mir, const char* name, uint32_t size)
{
  mir_register_t* reg;

  if (mir->_registers_size < mir->registers_length + 1) {
    mir->_registers_size += MIR_LIST_INCREMENT_SIZE;
    mir->registers = realloc(mir->registers, sizeof(mir_register_t) * mir->_registers_size);
  }

  reg = &mir->registers[mir->registers_length];
  reg->size = size;
  reg->spec.spec = NULL;
  reg->spec.spec_length = 0;
  reg->spec._spec_size = 0;
  dstring_init(&reg->name, 0);
  dstring_copy(&reg->name, name);

  hashtable_set(&mir->_registers_index, name, mir->registers_length);

  mir->registers_length++;
  return reg;
}

mir_register_t*
mir_get_register(mir_t* mir, const char* name)
{
  int64_t index;

  if (hashtable_get(&mir->_registers_index, name, &index) != ERR_OK) {
    return NULL;
  }

  return &mir->registers[index];
}

void
mir_register_close(mir_register_t* reg)
{
  dstring_close(&reg->name);
  mir_bitfield_spec_close(&reg->spec);
}

mir_inst_t*
mir_add_instruction(mir_t* mir, const char* name, uint32_t size)
{
  mir_inst_t* inst;

  if (mir->_instructions_size < mir->instructions_length + 1) {
    mir->_instructions_size += MIR_LIST_INCREMENT_SIZE;
    mir->instructions = realloc(mir->instructions, sizeof(mir_inst_t) * mir->_instructions_size);
  }

  inst = &mir->instructions[mir->instructions_length];
  inst->size = size;
  inst->fields = NULL;
  inst->fields_length = 0;
  inst->_fields_size = 0;
  inst->parameters = NULL;
  inst->parameters_length = 0;
  inst->_parameters_size = 0;
  dstring_init(&inst->name, 0);
  dstring_copy(&inst->name, name);

  hashtable_set(&mir->_instructions_index, name, mir->instructions_length);

  mir->instructions_length++;
  return inst;
}

mir_inst_t*
mir_get_instruction(mir_t* mir, const char* name)
{
  int64_t index;

  if (hashtable_get(&mir->_instructions_index, name, &index) != ERR_OK) {
    return NULL;
  }

  return &mir->instructions[index];
}

mir_inst_param_t*
mir_instruction_add_param(mir_inst_t* inst, const char* name, mir_type_t type, uint32_t size)
{
  mir_inst_param_t* param;

  if (inst->_parameters_size < inst->parameters_length + 1) {
    inst->_parameters_size += MIR_LIST_INCREMENT_SIZE;
    inst->parameters = realloc(inst->parameters, sizeof(mir_inst_param_t) * inst->_parameters_size);
  }

  param = &inst->parameters[inst->parameters_length++];
  param->size = size;
  param->type = type;
  dstring_init(&param->name, 0);
  dstring_copy(&param->name, name);

  return param;
}

mir_inst_param_t*
mir_instruction_get_param(mir_inst_t* inst, const char* name)
{
  for (int i = 0; i < inst->parameters_length; i++) {
    if (strcmp(inst->parameters[i].name.data, name) == 0) {
      return &inst->parameters[i];
    }
  }

  return NULL;
}

mir_bitfield_spec_t*
mir_instruction_add_field(mir_inst_t* inst, const char* name, mir_bitfield_spec_type_t type)
{
  mir_bitfield_spec_t* field;

  if (inst->_fields_size < inst->fields_length + 1) {
    inst->_fields_size += MIR_LIST_INCREMENT_SIZE;
    inst->fields = realloc(inst->fields, sizeof(mir_bitfield_spec_t) * inst->_fields_size);
  }

  field = &inst->fields[inst->fields_length++];
  field->type = type;
  field->spec = NULL;
  field->spec_length = 0;
  field->_spec_size = 0;
  dstring_init(&field->name, 0);
  dstring_copy(&field->name, name);

  return field;
}

mir_bitfield_spec_t*
mir_instruction_get_field(mir_inst_t* inst, const char* name)
{
  for (int i = 0; i < inst->fields_length; i++) {
    if (strcmp(inst->fields[i].name.data, name) == 0) {
      return &inst->fields[i];
    }
  }

  return NULL;
}

void
mir_instruction_close(mir_inst_t* inst)
{
  dstring_close(&inst->name);

  for (int i = 0; i < inst->parameters_length; i++) {
    dstring_close(&inst->parameters[i].name);
  }

  for (int i = 0; i < inst->fields_length; i++) {
    mir_bitfield_spec_close(&inst->fields[i]);
  }
}

mir_bitfield_spec_t*
mir_bitfield_spec_add_field(mir_bitfield_spec_t* spec, const char* name, mir_bitfield_spec_type_t type)
{
  mir_bitfield_spec_t* field;

  if (spec->_spec_size < spec->spec_length + 1) {
    spec->_spec_size += MIR_LIST_INCREMENT_SIZE;
    spec->spec = realloc(spec->spec, sizeof(mir_bitfield_spec_t) * spec->_spec_size);
  }

  field = &spec->spec[spec->spec_length++];
  field->type = type;
  dstring_init(&field->name, 0);
  dstring_copy(&field->name, name);

  return field;
}

mir_bitfield_spec_t*
mir_bitfield_spec_get_field(mir_bitfield_spec_t* spec, const char* name)
{
  for (int i = 0; i < spec->spec_length; i++) {
    if (strcmp(spec->spec[i].name.data, name) == 0) {
      return &spec->spec[i];
    }
  }

  return NULL;
}

void
mir_bitfield_spec_close(mir_bitfield_spec_t* spec)
{
  dstring_close(&spec->name);
  dstring_close(&spec->identifier);

  for (int i = 0; i < spec->spec_length; i++) {
    mir_bitfield_spec_close(&spec->spec[i]);
  }

  if (spec->spec_length > 0 && spec->spec != NULL) {
    free(spec->spec);
    spec->spec = NULL;
  }
}
