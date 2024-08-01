#include "highlights.h"

std::vector<std::tuple<std::string, std::string, std::string, std::string>> getSyntaxHighlight() {
    const std::string CONTROL = "#D885FCD9";
    const std::string PLAYEROBJECTS = "#F9FF8F";

    return {
        {"keyword.control", CONTROL, "bold italic", R"((\t+|\s+)\b(if|else\s+if|else|while|loop(?!-)|return|continue\s+(loop)?)\b)"},
        {"entity.playerobjects", PLAYEROBJECTS, "", R"(game\s*mode|all\s*players?|victim|attacker|sender|loop-player|shooter|uuid\s+of\s*|'s\s+uuid|location\s+of\s*|'s\s+location|console)"},
        {"comment", "gray", "italic", R"(^(#.*)$)"},
        {"multiLineComment", "gray", "italic", R"(###\r?\n([\s\S]*?)\r?\n###(\r?\n|$))"},
        {"string", "red", "italic", R"("(\\"|[^"])*")"}
    };
}
