#include "dstring.h"
#include "mir.h"
#include "unity.h"

void
test_mir_init(void)
{
  mir_t mir;
  mir_init(&mir);

  TEST_ASSERT_EQUAL(0, mir.bitfields_length);
  TEST_ASSERT_EQUAL(0, mir.instructions_length);
  TEST_ASSERT_EQUAL(0, mir.registers_length);
  TEST_ASSERT_EQUAL(MIR_LIST_INITIAL_SIZE, mir._bitfields_size);
  TEST_ASSERT_EQUAL(MIR_LIST_INITIAL_SIZE, mir._instructions_size);
  TEST_ASSERT_EQUAL(MIR_LIST_INITIAL_SIZE, mir._registers_size);

  TEST_ASSERT_NOT_NULL(mir.bitfields);
  TEST_ASSERT_NOT_NULL(mir.instructions);
  TEST_ASSERT_NOT_NULL(mir.registers);

  TEST_ASSERT_EQUAL(MIR_BITFIELD_HASHTABLE_SIZE, mir._bitfields_index._size);
  TEST_ASSERT_EQUAL(MIR_INSTRUCTION_HASHTABLE_SIZE, mir._instructions_index._size);
  TEST_ASSERT_EQUAL(MIR_REGISTER_HASHTABLE_SIZE, mir._registers_index._size);
  TEST_ASSERT_EQUAL(MIR_VARIABLE_HASHTABLE_SIZE, mir.variables._size);

  TEST_ASSERT_NOT_NULL(mir._bitfields_index.items);
  TEST_ASSERT_NOT_NULL(mir._instructions_index.items);
  TEST_ASSERT_NOT_NULL(mir._registers_index.items);
  TEST_ASSERT_NOT_NULL(mir.variables.items);

  mir_close(&mir);
}

void
test_mir_add_and_get_bitfield(void)
{
  mir_t mir;
  mir_init(&mir);

  mir_bitfield_t* reg = mir_add_bitfield(&mir, "Reg", 4);
  TEST_ASSERT_NOT_NULL(reg);
  TEST_ASSERT_EQUAL_STRING("Reg", reg->name.data);
  TEST_ASSERT_EQUAL(4, reg->size);
  TEST_ASSERT_EQUAL(0, reg->fields_length);
  TEST_ASSERT_EQUAL(0, reg->_fields_size);
  TEST_ASSERT_NULL(reg->fields);

  mir_bitfield_t* opcode = mir_add_bitfield(&mir, "Opcode", 8);
  TEST_ASSERT_NOT_NULL(opcode);
  TEST_ASSERT_EQUAL_STRING("Opcode", opcode->name.data);
  TEST_ASSERT_EQUAL(8, opcode->size);
  TEST_ASSERT_EQUAL(0, opcode->fields_length);
  TEST_ASSERT_EQUAL(0, opcode->_fields_size);
  TEST_ASSERT_NULL(opcode->fields);

  TEST_ASSERT_EQUAL(2, mir.bitfields_length);
  TEST_ASSERT_GREATER_OR_EQUAL(mir.bitfields_length, mir._bitfields_size);
  TEST_ASSERT_EQUAL_PTR(reg, mir_get_bitfield(&mir, "Reg"));
  TEST_ASSERT_EQUAL_PTR(opcode, mir_get_bitfield(&mir, "Opcode"));
  TEST_ASSERT_NULL(mir_get_bitfield(&mir, "other"));


  mir_bitfield_field_t* f_op = mir_bitfield_add_field(opcode, "op", 5);
  TEST_ASSERT_NOT_NULL(f_op);
  TEST_ASSERT_EQUAL_STRING("op", f_op->name.data);
  TEST_ASSERT_EQUAL(5, f_op->size);

  mir_bitfield_field_t* f_reg = mir_bitfield_add_field(opcode, "reg", 3);
  TEST_ASSERT_NOT_NULL(f_reg);
  TEST_ASSERT_EQUAL_STRING("reg", f_reg->name.data);
  TEST_ASSERT_EQUAL(3, f_reg->size);

  TEST_ASSERT_EQUAL(2, opcode->fields_length);
  TEST_ASSERT_GREATER_OR_EQUAL(opcode->fields_length, opcode->_fields_size);
  TEST_ASSERT_EQUAL_PTR(f_op, mir_bitfield_get_field(opcode, "op"));
  TEST_ASSERT_EQUAL_PTR(f_reg, mir_bitfield_get_field(opcode, "reg"));
  TEST_ASSERT_NULL(mir_bitfield_get_field(opcode, "other"));

  mir_close(&mir);
}

void
test_mir_add_and_get_register(void)
{
  mir_t mir;
  mir_init(&mir);

  mir_register_t* r2 = mir_add_register(&mir, "r2", 32);
  TEST_ASSERT_NOT_NULL(r2);
  TEST_ASSERT_EQUAL_STRING("r2", r2->name.data);
  TEST_ASSERT_EQUAL(32, r2->size);
  TEST_ASSERT_NULL(r2->spec.spec);
  TEST_ASSERT_EQUAL(0, r2->spec.spec_length);
  TEST_ASSERT_EQUAL(0, r2->spec._spec_size);

  TEST_ASSERT_EQUAL_PTR(r2, mir_get_register(&mir, "r2"));
  TEST_ASSERT_NULL(mir_get_register(&mir, "r5"));
  TEST_ASSERT_EQUAL(1, mir.registers_length);
  TEST_ASSERT_GREATER_OR_EQUAL(mir.registers_length, mir._registers_size);

  r2->spec.type = FT_FIELDS;
  mir_bitfield_spec_t* f_size = mir_bitfield_spec_add_field(&r2->spec, "size", FT_LITERAL);
  TEST_ASSERT_NOT_NULL(f_size);
  TEST_ASSERT_EQUAL_STRING("size", f_size->name.data);
  TEST_ASSERT_EQUAL(FT_LITERAL, f_size->type);
  TEST_ASSERT_NULL(f_size->spec);
  TEST_ASSERT_EQUAL(0, f_size->spec_length);
  TEST_ASSERT_EQUAL(0, f_size->_spec_size);

  mir_bitfield_spec_t* f_code = mir_bitfield_spec_add_field(&r2->spec, "code", FT_LITERAL);
  TEST_ASSERT_NOT_NULL(f_code);
  TEST_ASSERT_EQUAL_STRING("code", f_code->name.data);
  TEST_ASSERT_EQUAL(FT_LITERAL, f_code->type);
  TEST_ASSERT_NULL(f_code->spec);
  TEST_ASSERT_EQUAL(0, f_code->spec_length);
  TEST_ASSERT_EQUAL(0, f_code->_spec_size);

  TEST_ASSERT_EQUAL(2, r2->spec.spec_length);
  TEST_ASSERT_GREATER_OR_EQUAL(r2->spec.spec_length, r2->spec._spec_size);

  TEST_ASSERT_EQUAL_PTR(f_size, mir_bitfield_spec_get_field(&r2->spec, "size"));
  TEST_ASSERT_EQUAL_PTR(f_code, mir_bitfield_spec_get_field(&r2->spec, "code"));
  TEST_ASSERT_NULL(mir_bitfield_spec_get_field(&r2->spec, "invalid"));

  mir_close(&mir);
}

void
test_mir_add_and_get_instruction(void)
{
  mir_t mir;
  mir_init(&mir);

  mir_inst_t* inst = mir_add_instruction(&mir, "mov", 16);
  TEST_ASSERT_NOT_NULL(inst);
  TEST_ASSERT_EQUAL_STRING("mov", inst->name.data);
  TEST_ASSERT_EQUAL(16, inst->size);
  TEST_ASSERT_NULL(inst->fields);
  TEST_ASSERT_EQUAL(0, inst->fields_length);
  TEST_ASSERT_EQUAL(0, inst->_fields_size);
  TEST_ASSERT_NULL(inst->parameters);
  TEST_ASSERT_EQUAL(0, inst->parameters_length);
  TEST_ASSERT_EQUAL(0, inst->_parameters_size);

  TEST_ASSERT_EQUAL(1, mir.instructions_length);
  TEST_ASSERT_GREATER_OR_EQUAL(mir.instructions_length, mir._instructions_size);
  TEST_ASSERT_EQUAL_PTR(inst, mir_get_instruction(&mir, "mov"));
  TEST_ASSERT_NULL(mir_get_instruction(&mir, "move"));

  mir_inst_param_t* arg1 = mir_instruction_add_param(inst, "arg1", TYPE_REGISTER, 32);
  TEST_ASSERT_EQUAL_STRING("arg1", arg1->name.data);
  TEST_ASSERT_EQUAL(TYPE_REGISTER, arg1->type);
  TEST_ASSERT_EQUAL(32, arg1->size);

  mir_inst_param_t* arg2 = mir_instruction_add_param(inst, "arg2", TYPE_IMMEDIATE, 32);
  TEST_ASSERT_EQUAL_STRING("arg2", arg2->name.data);
  TEST_ASSERT_EQUAL(TYPE_IMMEDIATE, arg2->type);
  TEST_ASSERT_EQUAL(32, arg2->size);

  TEST_ASSERT_EQUAL(2, inst->parameters_length);
  TEST_ASSERT_GREATER_OR_EQUAL(inst->parameters_length, inst->_parameters_size);
  TEST_ASSERT_EQUAL_PTR(arg1, mir_instruction_get_param(inst, "arg1"));
  TEST_ASSERT_EQUAL_PTR(arg2, mir_instruction_get_param(inst, "arg2"));
  TEST_ASSERT_NULL(mir_instruction_get_param(inst, "arg3"));

  mir_bitfield_spec_t* field1 = mir_instruction_add_field(inst, "opcode", FT_LITERAL);
  field1->value = 0x12;
  TEST_ASSERT_EQUAL_STRING("opcode", field1->name.data);
  TEST_ASSERT_EQUAL(FT_LITERAL, field1->type);
  TEST_ASSERT_NULL(field1->spec);
  TEST_ASSERT_EQUAL(0, field1->spec_length);
  TEST_ASSERT_EQUAL(0, field1->_spec_size);

  mir_bitfield_spec_t* field2 = mir_instruction_add_field(inst, "regdst", FT_IDENTIFIER);
  dstring_copy(&field2->identifier, "arg1");
  TEST_ASSERT_EQUAL_STRING("regdst", field2->name.data);
  TEST_ASSERT_EQUAL(FT_IDENTIFIER, field2->type);
  TEST_ASSERT_NULL(field2->spec);
  TEST_ASSERT_EQUAL(0, field2->spec_length);
  TEST_ASSERT_EQUAL(0, field2->_spec_size);

  mir_bitfield_spec_t* field3 = mir_instruction_add_field(inst, "regsrc", FT_SPEC);
  TEST_ASSERT_EQUAL_STRING("regsrc", field3->name.data);
  TEST_ASSERT_EQUAL(FT_SPEC, field3->type);
  TEST_ASSERT_NULL(field3->spec);
  TEST_ASSERT_EQUAL(0, field3->spec_length);
  TEST_ASSERT_EQUAL(0, field3->_spec_size);

  mir_bitfield_spec_t* reg_spec = mir_bitfield_spec_set_spec(field3, "Reg", FT_IDENTIFIER);
  dstring_copy(&reg_spec->identifier, "arg2");
  TEST_ASSERT_EQUAL_STRING("Reg", reg_spec->name.data);
  TEST_ASSERT_EQUAL(FT_IDENTIFIER, reg_spec->type);
  TEST_ASSERT_NULL(reg_spec->spec);
  TEST_ASSERT_EQUAL(0, reg_spec->spec_length);
  TEST_ASSERT_EQUAL(0, reg_spec->_spec_size);

  TEST_ASSERT_EQUAL_PTR(field1, mir_instruction_get_field(inst, "opcode"));
  TEST_ASSERT_EQUAL_PTR(field2, mir_instruction_get_field(inst, "regdst"));
  TEST_ASSERT_EQUAL_PTR(field3, mir_instruction_get_field(inst, "regsrc"));
  TEST_ASSERT_NULL(mir_instruction_get_field(inst, "nop"));

  TEST_ASSERT_EQUAL_PTR(reg_spec, mir_bitfield_spec_get_field(field3, "Reg"));
  TEST_ASSERT_NULL(mir_bitfield_spec_get_field(field3, "a"));

  mir_close(&mir);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_mir_init);
  RUN_TEST(test_mir_add_and_get_bitfield);
  RUN_TEST(test_mir_add_and_get_register);
  RUN_TEST(test_mir_add_and_get_instruction);

  return UNITY_END();
}

void
setUp(void)
{
  //
}

void
tearDown(void)
{
  //
}
