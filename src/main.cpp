#include <ReFacE.h>

static void show_usage(std::string name) {
    std::cout << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h,--help\t\t\t\t\tShow this help message\n"
              << "\t-c,--calibrate <CONFIG_FILE>\t\t\tCalibrates single camera with CONFIG_FILE xml.\n"
              << "\t-cs,--calibrate-stereo [CONFIG_FILE]\t\tCalibrates both cameras with CONFIG_FILE if "
                 "specified, othrerwise configure with Default file in 'ReFacE/config/config_stereo.xml'.\n"
              << "\t-ms, --match-stereo [CALIB_FILE]\t\tComputes the Stero Matching and generates the "
                 "disparity map with CALIB_FILE specifications, otherwise uses Default file in "
                 "ReFacE/config/output/out_camera_stereo.xml\n"
              << std::endl;
}

int main(int argc, char *argv[])
{
//    cout << "Argc: " << argc << endl;
//    cout << "Argv: ";
//    for(int i=0; i<argc; i++)
//    {
//        cout << argv[i] << "\n";
//    }
//    return 0;


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
    for (int i = 1; i < argc; ++i)
    {
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
            if (i + 1 < argc) {
                // Increment 'i' so we don't get the argument as the next argv[i]. //
                configFile = argv[++i];
                if(configFile.empty()){
                    std::cerr << "Error: Wrong Config File! String is empty!\n";
                    return -1;
                }
                else{
                    flags[2] = true;
                }

            }
            else{
                // Default mode
                configFile = "../config/output/out_camera_stereo.xml";
            }
            #if DEBUG
                std::cout << "Runing Stereo-Matching with " << configFile << " camera file\n";
            #endif
        }
        else{
            show_usage(filename);
            return 0;
        }
    }

    if(flags[0] == true){
        #if DEBUG
            std::cout << "Calibration";
        #endif
        Calibration *calib = new Calibration();
        calib->config(configFile);
        calib->calibrate();
        delete calib;
    }
    if(flags[1] == true){
        #if DEBUG
            std::cout << "Stereo-Calibration\n";
        #endif

        SteroCalib calib;
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
    if(flags[2] == true){
        #if DEBUG
            std::cout << "Stereo-Matching\n";
        #endif

        SteroCalib calib;
        if(calib.load(configFile) != 0){
            cerr << "Error on Loading calibration file\n";
        }
    }

    return 0;
}


