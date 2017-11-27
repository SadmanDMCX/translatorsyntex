#include <iostream>
#include <fstream>

namespace super {

    // Class
    class FileManupulator {

    public:
        void GetFile(std::fstream &file, int key) {
            std::string filePathIn = "input.txt", filePathOut = "input.txt";
            if (key == 0) {
                file.open(filePathIn.c_str(), std::ios::in);
                if (file == NULL) {
                    std::cout << "No file found" << std::endl;
                }
            }
            if (key == 1) {
                file.open(filePathOut.c_str(), std::ios::out);
                if (file == NULL) {
                    std::cout << "Output file not found" << std::endl;
                }
            }
        }
    } fman;

    // Post Methods
    // Read File
    std::string readFile() {

        // variables
        std::string lines, totalLine = "";
        std::fstream infile, outfile;

        // Call Function
        fman.GetFile(infile, 0);

        while (!infile.eof()) {
            getline(infile, lines);
            totalLine += lines + "\n";
        }

        return totalLine;
    }
}

