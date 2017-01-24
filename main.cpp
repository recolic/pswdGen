#include "stdafx.h"
#include "pswdGener.h"
#include <fstream>
#include <streambuf>
using namespace std;
void showHelpInfoAndExit();
int main(int arg_size, char **arg)
{
    //Init env variables
    string outputPath, seedPath, requestDomain;
    bool bStrongerPassword = false;
    bool bNoConfirm = false;
    size_t forcedLength = 16;
    //Read command line
    if(arg_size == 1)
        showHelpInfoAndExit();
    else
    {
        int current_config = RECOLIC_ARG_NULL;
        for(size_t cter = 1; cter < arg_size; ++cter)
        {
            switch(current_config)
            {
                case RECOLIC_ARG_NULL:
                    if(cstreql(arg[cter], "-o") || cstreql(arg[cter], "--output"))
                    {
                        current_config = RECOLIC_ARG_OUTPUT_PATH;
                        DEBUG_PRINT("-o detected.");
                        continue;
                    }
                    else if(cstreql(arg[cter], "-h") || cstreql(arg[cter], "--help"))
                    {
                        DEBUG_PRINT("-h detected.");
                        showHelpInfoAndExit();
                    }
                    else if(cstreql(arg[cter], "-s") || cstreql(arg[cter], "--seed"))
                    {
                        current_config = RECOLIC_ARG_SEED_PATH;
                        DEBUG_PRINT("-s detected.");
                        continue;
                    }
                    else if(cstreql(arg[cter], "-l") || cstreql(arg[cter], "--length"))
                    {
                        current_config = RECOLIC_ARG_PSWD_LENGTH;
                        DEBUG_PRINT("-l detected.");
                        continue;
                    }
                    else if(cstreql(arg[cter], "-f") || cstreql(arg[cter], "--for"))
                    {
                        current_config = RECOLIC_ARG_REQUEST_DOMAIN;
                        DEBUG_PRINT("-f detected.");
                        continue;
                    }
                    else if(cstreql(arg[cter], "-S") || cstreql(arg[cter], "--strong"))
                    {
                        bStrongerPassword = true;
                        DEBUG_PRINT("-S detected.");
                        continue;
                    }
                    else if(cstreql(arg[cter], "-y") || cstreql(arg[cter], "--no-confirm"))
                    {
                        bNoConfirm = true;
                        DEBUG_PRINT("-y detected.");
                        continue;
                    }
                    else
                    {
                        cout << "Incorrect arguments. Use \"pswdgen --help\" to get help. " << endl;
                        return 0;
                    }
                    break;
                case RECOLIC_ARG_OUTPUT_PATH:
                    outputPath = arg[cter];
                    current_config = RECOLIC_ARG_NULL;
                    break;
                case RECOLIC_ARG_PSWD_LENGTH:
                    forcedLength = stoul(string(arg[cter]));
                    current_config = RECOLIC_ARG_NULL;
                    break;
                case RECOLIC_ARG_SEED_PATH:
                    seedPath = arg[cter];
                    current_config = RECOLIC_ARG_NULL;
                    break;
                case RECOLIC_ARG_REQUEST_DOMAIN:
                    requestDomain = arg[cter];
                    current_config = RECOLIC_ARG_NULL;
                    break;
                default:
                    throw logic_error("At main.cpp, line 54, invalid argument analyser(bug1001).");
            }
        }
    }
    if(seedPath.size() == 0 || requestDomain.size() == 0)
    {
        cout << "Please provide enough arguments. try \"pswdGen -h\" for more infomation. " << endl;
        return 0;
    }
    //Read seed file.
    ifstream iSeed(seedPath, ios::in);
    if(!iSeed)
    {
        cout << "Can't open seed file. Please check and try again. " << endl;
        DEBUG_PRINT((string("File:") + seedPath).c_str());
        return 0;
    }
    iSeed.seekg(0, ios::end);
    string iBuffer;
    iBuffer.reserve(static_cast<unsigned long>(iSeed.tellg()));
    iSeed.seekg(0, ios::beg);
    iBuffer.assign(istreambuf_iterator<char>(iSeed), istreambuf_iterator<char>());
    iSeed.close();
    //Get result.
    pswdGener gen;
    string result = gen(iBuffer, requestDomain, bStrongerPassword, forcedLength);
    if(outputPath.size() == 0)
    {
        gt_print_pswd:
        if(!bNoConfirm)
        {
#if ros==OS_WINDOWS
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
    cout << HELP_INFO << endl;
    exit(0);
}
