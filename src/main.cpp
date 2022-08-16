#include <iostream>
#include <fstream>
#include <string>

class Obfuscate {
public:
    Obfuscate(const std::string &filePath) {
        std::ifstream file(filePath);
        m_content = "";
        std::string line;
        while (getline(file, line)) {
            m_content.append(line);
            m_content.append("\n");
        }
        std::cout << "file content:\n" << m_content << std::endl;
    }

    // TODO: Implement this
    Obfuscate obfuscate() {
        return *this;
    }

    // TODO: Implement this
    Obfuscate uglify() {
       
        return *this;
    }

    // TODO: Implement this
    Obfuscate prettify() {

        return *this;
    }

private:
    std::string m_content;
    
};

int main(int argc, char **argv) {
    if (argc > 1) {
        std::string filePath = argv[1];
        Obfuscate obfuscate(filePath);
    }
    return 0;
}