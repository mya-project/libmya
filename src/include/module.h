#pragma once

#include "err.h"
#include "types/module.h"

error_code_t
module_init(module_t* module, const char* filepath);
