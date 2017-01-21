#include "stdafx.h"
using namespace std;
void showHelpInfoAndExit();
int main(size_t arg_size, char **arg)
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
                        exit(0);
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

}