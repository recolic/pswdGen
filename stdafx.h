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
#include <memory>
#include <rlib/sys/os.hpp>

#include "recolic_alias.h"

#if RLIB_OS_ID == OS_WINDOWS
#include <windows.h>
void toClipboard(const std::string &s){
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size());
    if (!hg){
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg),s.c_str(),s.size());
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT,hg);
    CloseClipboard();
    GlobalFree(hg);
}
#endif

//Debug tools
//#define RECOLIC_DEBUG
#ifdef RECOLIC_DEBUG
#define PRINT_DEBUG_HEAD printf("RECOLIC_DEBUG >")
#define DEBUG_PRINTF(msg, ...) PRINT_DEBUG_HEAD; printf(msg, __VA_ARGS__); printf("\n")
#define DEBUG_PRINT(msg) PRINT_DEBUG_HEAD; printf(msg); printf("\n")
#else
#define DEBUG_PRINTF(msg, ...)
#define DEBUG_PRINT(msg)
#endif

//other info
#define HELP_INFO "********pswdGener*******\n---by Recolic Keghart---\n---github.com/recolic---\n---   GNU LICENSED   ---\n************************\nUsage: pswdGen [options]\nOptions: \n-h --help:\n    Show this message.\n-o --output:\n    Path to get output.\n-S --strong:\n    Generate stronger password.\n-y --no-confirm:\n    Directly output the result.\n-l --length:\n    Give max length of the pswd.(16 by default, 0 for INF)\n-s --seed [REQUIRED]:\n    Give path to seed file. '-' to read stdin.\n-f --for [REQUIRED]:\n    Identifyer to where the pswd is used.\n\nExample:\n./pswdGen -h\n./pswdGen -s ~/se.txt -f recolic.net -o out.txt"

#endif //PSWDGEN_STDAFX_H
