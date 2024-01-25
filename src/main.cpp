#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <algorithm>

#define SEMICOLON 59
#define SPACE 32
#define TAB 9
#define ENDLINE 10

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
        /* remove comments */
        // positions of comments (start index of comment, int index of comment)
        std::vector<std::pair<int, int>> comments;
        char lastChar = 0;
        for (int i = 0; i < m_content.size(); i++) {
            char currentChar = m_content[i];
            int start = i;
            int end = -1;
            if (currentChar == '/' && lastChar == '/') {
                start = i - 1;
                for (int j = start; j < m_content.size(); j++) {
                    if (m_content[j] == '\n') {
                        end = j;
                        break;
                    }
                }
            }
            else if (currentChar == '*' && lastChar == '/') {
                start = i - 1;
                for (int j = start; j+1 < m_content.size(); j++) {
                    if (m_content[j] == '*') {
                        if (m_content[j+1] == '/') {
                            end = j; 
                        }
                    }
                }
            
            }
            if (end != -1) {
                std::pair<int, int> startEnd = {start, end};
                comments.push_back(startEnd);
            }
            lastChar = currentChar;
            
        }

        std::string obfuscated_content = "";
        for (int i = 0; i < m_content.size(); i++) {
            bool isComment = false;
            for (auto& startEnd : comments) {
                if (i >= startEnd.first && i <= startEnd.second) { isComment = true; }
            }
            if (isComment) continue;

            obfuscated_content.push_back(m_content[i]);
        }
        m_obfuscated = obfuscated_content;
        for (int i = 1; i - 1 < m_obfuscated.size(); i++) {
            if (m_obfuscated[i] == '\n') {
                char lastVisibleChar = Obfuscate::getLastVisibleChar(m_obfuscated, i);
                char nextVisibleChar = Obfuscate::getNextVisibleChar(m_obfuscated, i);
                if (nextVisibleChar != SEMICOLON && 
                    nextVisibleChar != ENDLINE &&
                    nextVisibleChar != SPACE &&
                    lastVisibleChar != SEMICOLON &&
                    lastVisibleChar != ENDLINE) {
                    m_obfuscated[i] = SEMICOLON; 
                }
            }
        }
        // remove invisible chars
        m_obfuscated.erase(std::remove(m_obfuscated.begin(), m_obfuscated.end(), ENDLINE), m_obfuscated.end()); 
        m_obfuscated.erase(std::remove(m_obfuscated.begin(), m_obfuscated.end(), TAB), m_obfuscated.end()); 
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

    const std::string& getObfuscated() {
        return m_obfuscated;
    }


private:
    std::string m_content;
    std::string m_obfuscated;
    
    /* 
        returns the next char in a string after startingIndex that isn't tab/endline/space 
        if the file ends before a visible char was found it returns 32 (SPACE)
    */
    static char getNextVisibleChar(const std::string& str, int startingIndex) {
        for (int i = startingIndex + 1; i < str.size(); i++) {
            if (str[i] != SPACE && 
                str[i] != TAB && 
                str[i] != ENDLINE) {
                return str[i];
            } 
        }
        return SPACE;
    }

    /*
        returns the last char in a string before startingIndex that isn't tab/endline/space
        if the function reaches the beginning of the string before finding a visible char
        it returns 32 (SPACE)
    */
    static char getLastVisibleChar(const std::string& str, int startingIndex) {
        for (int i = startingIndex - 1; i > 0; i--) {
            if (str[i] != SPACE && 
                str[i] != TAB && 
                str[i] != ENDLINE) {
                return str[i];
            } 
        }
        return SPACE;
    }

    /*
        removes spaces that are unnessessary 
        eg.: 'var x = 0;    var y = 10;' -> 'var x=0;var y=10;
        TODO:
    */
    static void removeRedundantSpaces(const std::string str) {

    } 
};

int main(int argc, char **argv) {
    if (argc > 1) {
        try {
            std::string filePath = argv[1];
            Obfuscate obfuscate(filePath);
            obfuscate.obfuscate();
            std::cout << obfuscate.getObfuscated() << std::endl;
        } 
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }
    return 0;
}