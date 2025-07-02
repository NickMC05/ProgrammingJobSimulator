#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 1. Execute Python script (which presumably generates output.txt)
    system("python test.py");
    
    // 2. Read the output file in C++
    std::ifstream inputFile("samples/jfk.mp3.txt");
    std::string line;
    
    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            std::cout << line << '\n';  // Process each line
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file\n";
        return 1;
    }
    
    return 0;
}