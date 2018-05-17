#ifndef __INPUT_PARSER__
#define __INPUT_PARSER__

namespace inParser {
 class ImputParser;
 class InputObject;
}

class inParser::ImputParser {
public:
    ImputParser();
    ~ImputParser();

public:
    inParser::InputObject parse(int, char**);

};

class inParser::InputObject{

};

#endif
