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
                        continue;
                    }
                    else if(cstreql(arg[cter], "-h") || cstreql(arg[cter], "--help"))
                    {
                        showHelpInfoAndExit();
                    }
                    else if(cstreql(arg[cter], "-s") || cstreql(arg[cter], "--seed"))
                    {
                        current_config = RECOLIC_ARG_SEED_PATH;
                        continue;
                    }
                    else if(cstreql(arg[cter], "-f") || cstreql(arg[cter], "--for"))
                    {
                        current_config = RECOLIC_ARG_REQUEST_DOMAIN;
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
                    break;
                case RECOLIC_ARG_SEED_PATH:
                    seedPath = arg[cter];
                    break;
                case RECOLIC_ARG_REQUEST_DOMAIN:
                    requestDomain = arg[cter];
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
    string result = gen(iBuffer, requestDomain);
    if(outputPath.size() == 0)
    {
        gt_print_pswd:
        cout << "Password is generated successfully. Print it out ?(y/Any other key to deny) >";
        string bPrint;
        cin >> bPrint;
        if(bPrint == "y" || bPrint == "Y")
            cout << "Your password is " << result << " and it's automatically copied to clipboard. " << endl;
        else
            cout << "Result copied to clipboard." << endl;
#if ros==OS_WINDOWS
        toClipboard(result.c_str());
#else
        cout << "Can't visit clipboard.System limit." << endl;
#endif
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
    cout << "********pswdGener*******\\n---by Recolic Keghart---\\n---github.com/recolic---\\n---   GNU LICENSED   ---\\n************************\\nUsage: pswdGen [options]\\nOptions: \\n-h --help:\\n    Show this message.\\n-o --output:\\n    Path to get output.\\n-s --seed:\\n[NEED]Give path to seed file.\\n-f --for:\\n[NEED]Identifyer to where the pswd is used.\\n\\nExample:\\n.\\/pswdGen -h\\n.\\/pswdGen -s ~\\/se.txt -f recolic.net -o out.txt" << endl;
    exit(0);
}