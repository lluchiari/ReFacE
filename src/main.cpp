#include <ReFacE.h>

static void show_usage(std::string name) {
    std::cout << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help\t\t\t\t\tShow this help message\n"
              << "\t<MAIN_CONFIG_FILE>\t\t\t\tRun the program using the MAIN_CONFIG_FILE configuration file."
              << std::endl;
}

static void registryWallaroo(){
    try{
        // A catalog contains the objects used by our app
        Catalog catalog;
        // You can create the objects you need in this way
        catalog.Create("mainControl", "MainController");

    }
    catch(const WallarooError& error )
    {
        std::cerr << "ERROR: " << error.what() << std::endl;
    }

}

int main(int argc, char *argv[])
{
    //Files declaration
    std::string mainConfigFile;

    // Registring Wallaroo
    registryWallaroo();

//#############################################################################################
//      COMMAND LINE PARSER
//#############################################################################################
     // Checking Command Line Arguments //
    if (argc < 2) {
        std::cout << argv[0] << " invalid option!\nTry '"<< argv[0]
                             << " --help' for more information.\n";
        return -1;
    }

    mainConfigFile = argv[1];

    // Command HELP --> Without flags (it's a sovereign command) //
    if ((mainConfigFile == "-h") || (mainConfigFile == "--help")) {
        show_usage("ReFacE");
        return 0;
    }
//#############################################################################################
//      END OF PARSER
//#############################################################################################

    MainController *mainControl = new MainController();
    if(mainControl->config(mainConfigFile) != 0){
        cerr << "Something went wrong on MainController::config()! Please Check it!\n";
        delete mainControl;
        return -1;
    }
    if(mainControl->run() !=  0){
        cerr << "Something went wrong on MainController::run()! Please Check it!\n";
        delete mainControl;
        return -1;
    }
    delete mainControl;
    return 0;
}


