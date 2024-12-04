#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Parser {
   private:
    std::ifstream file;
    char current_char;
    std::string current;

   public:
    Parser(const std::string &filename) : file(filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        advance();  // Read first character
    }

    char peek() const { return current_char; }

    void advance() {
        if (file.get(current_char)) {
            // Character successfully read
            current += current_char;
        } else {
            current_char = '\0';  // EOF marker
        }
    }

    void reset() {
        current = "";
        current += current_char;
    }

    bool is_at_end() const { return file.eof() || current_char == '\0'; }

    std::string currentString(int offset) {
        return current.substr(0, current.size() - offset);
    }
};

bool isdigit(char c) { return c >= '0' && c <= '9'; }

int number(Parser &parser) {
    while (isdigit(parser.peek())) parser.advance();
    // skip the last char.
    std::string left = parser.currentString(1);
    parser.reset();
    return std::stoi(left);
}

std::string identifier(Parser &parser) {
    // allow ' as part of identifier name to allow "don't" as identifier...
    while (isalpha(parser.peek()) || parser.peek() == '\'') parser.advance();
    std::string name = parser.currentString(1);
    parser.reset();
    return name;
}

bool isEmptyParen(Parser &parser) {
    if (parser.peek() != '(') return false;
    parser.advance();
    if (parser.peek() != ')') return false;
    parser.advance();
    parser.reset();
    return true;
}

int mulCall(Parser &parser) {
    if (parser.peek() != '(') return 0;
    // Now can safely advance and reset. We don't care about keeping the prefix
    // `mul(`
    parser.advance();
    parser.reset();
    int left = number(parser);
    if (parser.peek() != ',') return 0;
    parser.advance();
    parser.reset();
    int right = number(parser);
    if (parser.peek() != ')') return 0;
    parser.advance();
    parser.reset();
    return left * right;
}

int main() {
    Parser parser("input.txt");

    bool lastDo = true;
    int total = 0;
    while (!parser.is_at_end()) {
        while (!isalpha(parser.peek()) && !parser.is_at_end()) parser.advance();

        parser.reset();
        std::string ident = identifier(parser);
        if (ident == "mul") {
            std::cout << ident << '\n';
            int res = mulCall(parser);
            if (lastDo) {
                std::cout << "res: " << res << '\n';
                total += res;
            }
        } else if (ident == "do" && isEmptyParen(parser)) {
            std::cout << ident << '\n';
            lastDo = true;
        } else if (ident == "don't" && isEmptyParen(parser)) {
            std::cout << ident << '\n';
            lastDo = false;
        } else {
            parser.advance();
        }
        parser.reset();
    }
    std::cout << "total: " << total << '\n';
}
