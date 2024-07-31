#include "highlights.h"

std::vector<std::tuple<std::string, std::string, std::string>> getSyntaxHighlight() {
    return {
        {"keyword.control", "blue", R"((\t+|\s+)\b(if|else\s+if|else|while|loop(?!-)|return|continue\s+(loop)?)\b)"},
        {"entity.playerobjects", "orange", R"(game\s*mode|all\s*players?|victim|attacker|sender|loop-player|shooter|uuid\s+of\s*|'s\s+uuid|location\s+of\s*|'s\s+location|console)"},
        {"comment", "gray", R"(^(#.*)$)"},
        {"multiLineComment", "gray", R"(###\r?\n([\s\S]*?)\r?\n###(\r?\n|$))"},
        {"string", "red", R"("(\\"|[^"])*")"}
    };
}
