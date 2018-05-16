#include <ReFacE.h>

static void show_usage(std::string name) {
    std::cout << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help\t\t\t\t\tShow this help message\n"
              << "\t-c,--calibrate CONFIG_FILE\t\t\tCalibrates the camera with CONFIG_FILE xml.\n"
              << std::endl;
}

int main(int argc, char *argv[])
{

//    const string keys =
//            "{h help ? ||}"
//            "{c calibrate |<none>| Calibrate config file}";

//    CommandLineParser parser(argc, argv, keys);
//    parser.about("ReFacE v0.1");

//    // Help Option
//    if(parser.has("help"))
//    {
//        show_usage(argv[0]);
//        return 0;
//    }

//    if (!parser.check())
//    {
//        parser.printErrors();
//        return 0;
//    }

    //Files declaration
    std::string configFile;

     // Checking Command Line Arguments //
    if (argc < 2) {
        std::cout << argv[0] << " invalid option!\nTry '"<< argv[0]
                             << " --help' for more information.\n";
        return -1;
    }

    // Create the vector of flags. It is usefull for more than one command in the same line//
    bool flags[PROGRAM_OPTIONS];
    for(int i=0; i< PROGRAM_OPTIONS; i++){flags[i] = false;}

    // Loop Case to Evaluate all the commands //
    for (int i = 1; i < argc; ++i) {
        // Auxiliar Variable storing the argument //
        std::string arg = argv[i];

        // Command HELP --> Without flags (it's a sovereign command) //
        if ((arg == "-h") || (arg == "--help")) {
            std::string aux = argv[0];
            std::string filename = aux.substr(aux.find("/")+1, aux.find(" "));
            show_usage(filename);
            return 0;
        }
        /* Command CALIBRATE --> flags[0] */
        else if((arg == "-c")|| (arg == "--calibrate")) {
            if (i + 1 < argc) {
            // Increment 'i' so we don't get the argument as the next argv[i]. //
                configFile = argv[++i];
                if(configFile.empty()){
                    std::cerr << "Error: Missing Config File!\n";
                    return -1;
                }
                else{
                    if(DEBUG) {std::cout << "Runing Calibration with " << configFile << " confg file";}
                    flags[0] = true;
                }
            }
            else{
                std::cerr << "Error: Missing Config and/or output files!\n";
                return -1;
            }
        }


//        // Command ENCRYPT --> flags[1] //
//        else if((arg == "-e")|| (arg == "--encrypt")) {
//            // Make sure we aren't at the end of argv! //
//            if (i + 2 < argc) {
//                /* Increment 'i' so we don't get the argument as the next argv[i]. */
//                source.push_back(argv[++i]);                    // public key file
//                source.push_back(argv[++i]);                   // message file
//            }
//            /* Uh-oh, there was no argument to the destination option. */
//            else {
//                std::cerr << "--encrypt option requires two argument. See --help for more information" << std::endl;
//                return -1;
//            }
//            flags[1] = true;
//        }
//        /* Command DECRYPT --> flags[2] */
//        else if((arg == "-d")|| (arg == "--decrypt")) {
//            /* Make sure we aren't at the end of argv! */
//            if (i + 2 < argc) {
//                /* Increment 'i' so we don't get the argument as the next argv[i]. */
//                source.push_back(argv[++i]);                    // private key file
//                source.push_back(argv[++i]);                   // cryptogram file
//            }
//            /* Uh-oh, there was no argument to the destination option. */
//            else {
//                std::cerr << "--decrypt option requires two argument. See --help for more information" << std::endl;
//                return -1;
//            }
//            flags[2] = true;
//        }
//        /* Command ENCRYPT GENERATE KEY --> flags[2] */
//        else if((arg == "-eak")|| (arg == "--encrypt-assimetric-key")) {

//        }
//        /* Command GUI --> flags[2] */
//        else if((arg == "-gui")|| (arg == "--graphical")) {

//        else {
//            show_usage(argv[0]);
//            std::cerr << "No options selected!"<< std::endl;
//            return -1;
//        }
//    }

    if(flags[0] == true){
        std::cout << "Calibration";
        Calibration *calib = new Calibration();
        calib->config(configFile);
        calib->calibrate();
        delete calib;
    }

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();

    return 0;
}


