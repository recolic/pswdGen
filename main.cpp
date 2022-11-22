#include "stdafx.h"
#include "pswdGener.h"
#include <fstream>
#include <streambuf>
#include <rlib/opt.hpp>
#include <rlib/sys/os.hpp>
using namespace std;
void showHelpInfoAndExit();
int main(int arg_size, char **arg)
{
    rlib::opt_parser opt(arg_size, arg);
     if(opt.getBoolArg("--help", "-h"))
        showHelpInfoAndExit();
    auto seedPath = opt.getValueArg("--seed", "-s");
    auto requestDomain = opt.getValueArg("--for", "-f");
    auto outputPath = opt.getValueArg("--output", "-o", false);
    auto forcedLength = opt.getValueArg("--length", "-l", false).as<unsigned int>();
    auto strongFlag = opt.getBoolArg("--strong", "-S");
    auto noconfirmFlag = opt.getBoolArg("--noconfirm", "-y");
    
    //Read seed file.
    string iBuffer;
    if(seedPath == "-")
    {
        if(!noconfirmFlag)
            throw invalid_argument("Argument Error: -y is needed while appointing - as seedPath.");
        //Read cin.
        while(!cin.eof())
        {
            string tmpBuf;
            getline(cin, tmpBuf);
            iBuffer += tmpBuf;
            iBuffer.push_back('\n');
        }
        iBuffer.pop_back();
    }
    else
    {
        ifstream iSeed(seedPath, ios::in);
        if(!iSeed)
        {
            DEBUG_PRINT((string("File:") + seedPath).c_str());
            throw runtime_error("Can't open seed file. Please check and try again. ");
        }

        iSeed.seekg(0, ios::end);

        iBuffer.reserve(static_cast<unsigned long>(iSeed.tellg()));
        iSeed.seekg(0, ios::beg);
        iBuffer.assign(istreambuf_iterator<char>(iSeed), istreambuf_iterator<char>());

        iSeed.close();
    }


    //Get result.
    pswdGener gen;
    string result = gen(iBuffer, requestDomain, strongFlag, forcedLength);
    if(outputPath.size() == 0)
    {
        gt_print_pswd:
        if(!noconfirmFlag)
        {
#if RLIB_OS_ID == OS_WINDOWS 
        toClipboard(result.c_str());
        cout << "Password is generated and copied to clipboard successfully. Print it out?(y/Any other key to deny) >";
#else
        cout << "Password is generated successfully. Print it out ?(y/Any other key to deny) >";
#endif
            string bPrint;
            cin >> bPrint;
            if(bPrint == "y" || bPrint == "Y")
                cout << "Your password is " << result << endl;
        }
        else
            cout << "Your password is " << result << endl;
        return 0;
    }
    else
    {
        ofstream oResult(outputPath, ios::out);
        if(!oResult)
        {
            cout << "Can't write to file." << endl;
            goto gt_print_pswd;
        }
        oResult << result;
        oResult.close();
        cout << "Done." << endl;
        return 0;
    }
}

void showHelpInfoAndExit()
{
    cout << R"RGEN(
********pswdGener v5****
---by Recolic Keghart---
---github.com/recolic---
---   GNU LICENSED   ---
************************
Usage: pswdGen [options]
Options:
-h --help:
    Show this message.
-o --output:
    Path to get output.
-S --strong:
    Generate stronger password.
-y --no-confirm:
    Directly output the result.
-l --length:
    Give max length of the pswd.(16 by default, 0 for INF)
-s --seed [REQUIRED]:
    Give path to seed file. '-' to read stdin.
-f --for [REQUIRED]:
    Identifier to where the pswd is used.

Example:
./pswdGen -h
./pswdGen -s ~/se.txt -f recolic.net -o out.txt
    )RGEN" << endl;
    exit(0);
}
