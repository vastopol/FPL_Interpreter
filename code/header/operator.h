#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "object.h"
#include "memory.h"
#include "func.h"
#include "utils.h"

#include <string>

Object* operate(Object* fun, Object* arg, Memory* m);

#endif // __OPERATOR_H__
