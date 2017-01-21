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

#include "recolic_alias.h"

//Simple functions
#define cstreql(stra, strb) (strlen(stra) == strlen(strb) && strcmp(stra, strb) == 0)

//OS judge
#define OS_LINUX 1
#define OS_WINDOWS 2
#define OS_UNIX_LIKE 3
#if defined(linux)
#define ros OS_LINUX
#endif
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(_MSC_VER)
#define ros OS_WINDOWS
#endif
#if defined(_UNIX)
#ifndef ros
#define ros OS_UNIX_LIKE
#endif
#endif

#ifdef ros
#if ros == OS_WINDOWS
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
#else

#endif
#endif

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
