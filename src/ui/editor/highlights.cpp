#include "highlights.h"

std::vector<std::tuple<std::string, std::string, std::string>> getSyntaxHighlight() {
    // couple of examples just for testing
    return {
        {"keyword", "blue", "\\b(if|else|while|for|return)\\b"},
        {"comment", "gray", "#[^\n]*"},
        {"string", "red", "\"(\\\\.|[^\"\\\\])*\""},
    };
}
