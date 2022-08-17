#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstring>

class Obfuscate {
public:
    Obfuscate(const std::string &filePath) {
        std::ifstream file(filePath);
        if (!file) {
            throw std::runtime_error("Error occurred while trying to open file!");
        }
        std::string line;
        while (getline(file, line)) {
            m_content.append(line);
            m_content.append("\n");
        }
        //std::cout << "file content:\n" << m_content << std::endl;
    }

    Obfuscate obfuscate() {
        for (int i = 0; i < m_content.size(); i++) {
            char currentChar = m_content[i];
            
            // obfuscate vars
            if ((i+2 < m_content.size()) && (currentChar == 'l' || currentChar == 'v')) {
                std::cout << "current char: " << currentChar << std::endl;
                std::string word;
                for (int j = i; j < i+3; j++) {
                    word.push_back(m_content[j]);
                }
                std::cout << "word: " << word << std::endl;
                if (word == "var" || word == "let") {
                    std::string varName;
                    for (int j = i+4; j < m_content.size(); j++) {
                        char currentJChar = m_content[j]; 
                        if (j+1 < m_content.size()) {
                            if (m_content[j+1] == '=') break;
                        }
                        varName.push_back(currentJChar);
                    }
                    std::cout << "found var: '" << varName << "'" << std::endl;

                    replaceVar(varName, varName.append("yeyeye"), i+4);
                }

            }
        }
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

    // replaces varName with newName
    // variableStartPointer is the index to the start of the var name inside m_content
    // let x = 10
    void replaceVar(const std::string &varName, const std::string &newName, int variableStartPointer) {
    

    }

private:
    std::string m_content;
    
};

int main(int argc, char **argv) {
    if (argc > 1) {
        try {
            std::string filePath = argv[1];
            Obfuscate obfuscate(filePath);
            obfuscate.obfuscate();
        } 
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }
    return 0;
}