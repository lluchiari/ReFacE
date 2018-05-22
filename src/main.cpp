#include <ReFacE.h>

static void show_usage(std::string name) {
    std::cout << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help\t\t\t\t\tShow this help message\n"
              << "\t-c,--calibrate <CONFIG_FILE>\t\t\tCalibrates single camera with CONFIG_FILE xml.\n"
              << "\t-cs,--calibrate-stereo [CONFIG_FILE]\t\tCalibrates both cameras with CONFIG_FILE if "
                 "specified, othrerwise configure with Default file in 'ReFacE/config/config_stereo.xml'.\n"
              << "\t-ms, --match-stereo [CALIB_FILE] [--algorithm=bm|sgbm|hh|sgbm3way]\t\tComputes the Stero Matching and generates the "
                 "disparity map with CALIB_FILE specifications, otherwise uses Default file in "
                 "ReFacE/config/output/out_camera_stereo.xml\n"
              << std::endl;
}

int main(int argc, char *argv[])
{
    //Files declaration
    std::string configFile;
    std::string param;


//#############################################################################################
//      COMMAND LINE PARSER
//#############################################################################################
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
    for (int i = 1; i < argc; ++i)
    {
        // Auxiliar Variabl e storing the argument //
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
                    flags[0] = true;
                }
            }
            else {
                std::cerr << "Error: Missing Config and/or output files!\n";
                return -1;
            }
            #if DEBUG
                std::cout << "Runing Calibration with " << configFile << " confg file.\n";
            #endif
        }
        /* Command CALIBRATE STEREO --> flags[1] */
        else if((arg == "-cs") || (arg == "--calibrate-stereo")){
            if (i + 1 < argc) {
                // Increment 'i' so we don't get the argument as the next argv[i]. //
                configFile = argv[++i];
                if(configFile.empty()){
                    std::cerr << "Error: Wrong Config File! String is empty!\n";
                    return -1;
                }
                else{
                    flags[1] = true;
                }

            }
            else{
                // Default mode
                configFile = "../config/config_stereo.xml";
            }
            #if DEBUG
                std::cout << "Runing Stereo-Calibration with " << configFile << " confg file\n";
            #endif
        }
        /* Command MATCHING STEREO --> flags[2] */
        else if((arg == "-ms") || (arg == "--match-stereo")){
            // Case where the two options were indicated //
            if(i+2 < argc)
            {
                param = argv[++i];

                // if param is has not a algorithm option //
                if(param.find("--algorithm") == string::npos){
                    configFile = param;
                    param = argv[++i];
                }
                else{
                    configFile = argv[++i];
                }
            }
            // Case where only one option was indicated //
            else if (i+1 < argc)
            {
                param = argv[++i];
                if(param.find("--algorithm") == string::npos){
                    configFile = param;
                    param = DEFAULT_MATCH_PARAM;
                }
                else {
                    configFile = DEFAULT_MATCH;
                }
            }
            // Default case //
            else {
                param = DEFAULT_MATCH_PARAM;
                configFile = DEFAULT_MATCH;
            }
            if(configFile.empty()){
                std::cerr << "Error: Wrong Config File! String is empty!\n";
                return -1;
            }
            flags[2] = true;
            #if DEBUG
                std::cout << "Runing Stereo-Matching with " << configFile << " camera file\n";
            #endif
        }
        else{
            show_usage("ReFacE");
            return 0;
        }
    }

//#############################################################################################
//      END OF PARSER
//#############################################################################################

    // Normal Calibration
    if(flags[0] == true){
        #if DEBUG
            std::cout << "Calibration";
        #endif
        Calibration *calib = new Calibration();
        calib->config(configFile);
        calib->calibrate();
        delete calib;
    }

    // Stereo Calibration
    if(flags[1] == true){
        #if DEBUG
            std::cout << "Stereo-Calibration\n";
        #endif

        StereoCalib calib;
        calib.config(configFile);

        // Run the calibration process based on config file //
        if(calib.calibrate() != 0)
        {
            cerr << "Error on Calibration!\n";
        }

        // Run the rectification process based on config file //
        if(calib.rectificate() != 0){
            cerr << "Error on Rectification!\n";
        }
    }

    // Stereo Matching
    if(flags[2] == true){
        StereoMatching *method;
        if(param == "--algorithm=bm")
        {
            method = new BlockMatching();
        }
        else if(param == "--algorithm=sgbm")
        {
            method = new SGBM();
        }
        else
        {
            std::cerr << "Not recognize parameter: " << param;
            return -1;
        }
        #if DEBUG
            cout << method->nameToString();
        #endif

        if(method->config(configFile) != 0){
            std::cerr << "Error on Matching Configuration!\n";
            delete method;
            return -1;
        }

        if(method->match() != 0){
            std::cerr << "Error on Matching Method '" << method->nameToString() << "'\n";
            delete method;
            return -1;
        }
        delete method;
    }

    return 0;
}


