//
// Created by recolic on 21/01/17.
//

#ifndef PSWDGEN_STDAFX_H
#define PSWDGEN_STDAFX_H

//Includes
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

#include "recolic_alias.h"

//Simple functions
#define cstreql(stra, strb) (strlen(stra) == strlen(strb) && strcmp(stra, strb) == 0)

//Debug tools
#define RECOLIC_DEBUG
#ifdef RECOLIC_DEBUG
#define PRINT_DEBUG_HEAD printf("RECOLIC_DEBUG >")
#define DEBUG_PRINTF(msg, ...) PRINT_DEBUG_HEAD; printf(msg, __VA_ARGS__); printf("\n")
#define DEBUG_PRINT(msg) PRINT_DEBUG_HEAD; printf(msg); printf("\n")
#else
#define DEBUG_PRINTF(msg, ...)
#define DEBUG_PRINT(msg)
#endif

#endif //PSWDGEN_STDAFX_H
