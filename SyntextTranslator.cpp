#include <iostream>
#include <fstream>

#include "fileio.h"
#include "compiler.h"

using namespace std;
using namespace super;

int main() {
    int read;

    string data = super::readFile();
    generator::generateData(data);

    cin >> read;
}
