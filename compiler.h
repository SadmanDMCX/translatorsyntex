#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

namespace ChargeSentence {
    int spaceFlag = 0;

    void charge(std::string &sentence) {
        spaceFlag = 0;
        for (int i = 0; i < sentence.length(); i++) {
            if (sentence[i] == ' ') {
                if (spaceFlag == 0) {
                    sentence[i] = '+';
                }
                spaceFlag++;
            }
        }
    }

    void escapeNewLine(std::string &data) {
        bool f1 = false, f2 = false;
        for (int i = 0; i < data.length(); i++) {
            if (data[i] == '\n' && f1 == false) {
                f1 = true;
            }
            else if (data[i] == '\n' && f2 == false) {
                f2 = true;
            }
            if (f1 == true && f2 == true) {
                f1 = false;
                f2 = false;
                data[i] = '!';
            }
        }
    }

    std::vector<std::string> tokenizer(std::string data) {
        int flag = 0;
        int len = data.length();
        std::string tokens[1000];
        std::vector<std::string> vectorTokens;
        int i = -1, k = 0;
        while (data[i] != '\0'){
            i++;
            if (data[i] == ' ' || data[i] == '!') {
                data[i] = '\n';
                k++;
            } else {
                if (data[i] != '\n') {
                    tokens[k] += data[i];
                }
            }
        }

        for (int i = 0; i < k; i++) {
            if (tokens[i] != "") {
                vectorTokens.push_back(tokens[i]);
            }
        }

        return vectorTokens;
    }

    void surf(std::string &finalProgram, std::string mainProgram) {
        finalProgram = "\nclass program\n{\n    static void Main(string[] args)\n    {\n        // Program\n        " + mainProgram + "\n    }\n}";
    }

    int returnSpaceFlag() {
        return spaceFlag;
    }
}

namespace generator {

    void generateData(std::string data) {

        std::string finalData = "", finalMain = "", quoteLine = "";

        int flagUsing1 = 1, flagUsing2 = 2;
        int flagMain1 = 1, flagMain2 = 2;
        int flagCWriteLine1 = 1, flagCWriteLine2 = 2;
        int flagLine = 0;

        ChargeSentence::escapeNewLine(data);
        std::vector<std::string> tokens = ChargeSentence::tokenizer(data);
        for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {

            if (*it == "#include") {
                flagUsing1 = 0;
            }

            if (*it == "<iostream>") {
                flagUsing2 = 0;
            }

            if (flagUsing1 == flagUsing2) {
                flagUsing1 = 1; flagUsing2 = 2;
                finalData += "using System;";
            }

            if (*it == "int") {
                flagMain1 = 0;
            }

            if (*it == "main()") {
                flagMain2 = 0;
            }

            if (flagMain1 == flagMain2) {
                flagMain1 = 1; flagMain2 = 2;
                ChargeSentence::surf(finalMain, "");
            }

            if (*it == "cout") {
                flagCWriteLine1 = 0;
            }

            std::string s = *it;
            if (s.find("\"") < 100 && flagCWriteLine1 == 0) {
                quoteLine += *it;
                quoteLine += " ";
            }

            if (*it == "endl;") {
                flagCWriteLine2 = 0;
            }

            if (flagCWriteLine1 == flagCWriteLine2) {
                flagCWriteLine1 = 1; flagCWriteLine2 = 2;
                ChargeSentence::surf(finalMain, "Console.WriteLine("+quoteLine+")");
                quoteLine = "";
            }
        }

        for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {

        }

        std::cout << finalData << std::endl << finalMain << std::endl;
    }

}
