#include <iostream>
#include <string>
#include <utility>
#include <vector>

/**
 * Available token classes.
 */
enum TokenType {
    type_lpar = 0,
    type_rpar = 1,
    type_lcurly_brace = 2,
    type_rcurly_brace = 3,
    type_keyword = 4,
    type_identifier = 5,
    type_number = 6,
    type_string = 7,
    type_comment = 8,
    type_error = 9
};

std::string get_token_type_string(TokenType _type) {
    switch (_type) {
    case type_keyword:
        return "KEYWORD";
    case type_lpar:
        return "LPAR";
    case type_rpar:
        return "RPAR";
    case type_lcurly_brace:
        return "L-CURLY-BRACE";
    case type_rcurly_brace:
        return "R-CURLY-BRACE";
    case type_identifier:
        return "ID";
    case type_number:
        return "NUMBER";
    case type_string:
        return "STRING";
    case type_comment:
        return "COMMENT";
    case type_error:
        return "ERROR";
    }
}

/**
 * Data structure for tokens.
 * Whenever a token is found, an object (with appropriate token type/class and lexeme)
 * from this class has to be created.
 */
class Token {

private:
    TokenType type;
    std::string lexeme;

public:
    Token(TokenType _type, std::string _lexeme) {
        this->type = _type;
        this->lexeme = std::move(_lexeme);
    }

    std::string get_repr()
    {
        std::string return_str = "<" + get_token_type_string(this->type) + ", " + this->lexeme + ">";
        return return_str;
    }
};

/*
 * We simulate the state transitions with a DFA here.
 * The next state should be constructed based on the current state and the input character.
 * Gotcha note!
 *      Be careful about whitespaces.
 *      Whitespaces usually finish a token, except for strings and comments.
 *      For example, `hello world ` contains 2 identifier tokens, each terminated with a whitespace.
 *      However, `"Hello world "` contains 1 string token, and both spaces are included in the token lexeme.
 */
std::string stateTransition(std::string current_state, char ch) {
    if (current_state.empty()) {
        // When the state is empty, the input character will represent the current state.
        current_state.push_back(ch);
        return current_state;
    }
    else if (current_state == "i" && ch == 'f') {
        return "if";
    }

    // TODO: implement the rest of the state transitions.
    
    else {
        return "Not implemented error!";
    }
}

/***
 * The main function for lexical analysis/tokenization.
 *
 * @param   _character_stream of type std::string
 * @return  std::vector of type Token (declared above)
 *
 */
std::vector<Token> tokenizeCode(std::string _character_stream) {
    std::vector<Token> tokens;
    std::string state_buffer; // Initially, we start with a null or empty state.
    // We scan character by character.
    for (std::string::iterator string_iter = _character_stream.begin();
         string_iter != _character_stream.end();
         string_iter++) {
        char current_character = *string_iter;
        state_buffer = stateTransition(state_buffer, current_character);
        if (state_buffer == "(") {
            tokens.emplace_back(TokenType::type_lpar, "(");
            // Clear out the state buffer once a token is read.
            state_buffer.clear();
        }
        else if (state_buffer == ")") {
            tokens.emplace_back(TokenType::type_rpar, ")");
            // Clear out the state buffer once a token is read.
            state_buffer.clear();
        }
        else if (state_buffer == "{") {
            tokens.emplace_back(TokenType::type_lcurly_brace, "{");
            // Clear out the state buffer once a token is read.
            state_buffer.clear();
        }
        else if (state_buffer == "}") {
            tokens.emplace_back(TokenType::type_rcurly_brace, "}");
            // Clear out the state buffer once a token is read.
            state_buffer.clear();
        }
        else if (state_buffer == "if") {
            tokens.emplace_back(TokenType::type_keyword, "if");
            // Clear out the state buffer once a token is read.
            state_buffer.clear();
        }
        else {
            // TODO: add the rest of the tokens.
            // TODO (extra credit): in case of an error, the cause of the error should go to the lexeme.
        }
    }
    return tokens;
}

void printTokenStream(std::vector<Token> tokens) {
    for (auto& token : tokens) {
        std::cout << token.get_repr() << " ";
    }
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::vector<Token> tokens = tokenizeCode(input);
    printTokenStream(tokens);
    return 0;
}
