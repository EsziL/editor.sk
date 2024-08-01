#include "highlights.h"

std::vector<std::tuple<std::string, std::string, std::string, std::string>> getSyntaxHighlight() {
    const std::string CONTROL = "#D885FCD9";
    const std::string PLAYEROBJECTS = "#F9FF8F";
    const std::string COMMENT = "gray";
    const std::string STRING = "#C3E88D";
    const std::string EVENT = "#E3E3E3";
    const std::string STOP = "#DD5855 #FF8C8C1F";

    return {
        {"control", CONTROL, "bold italic", R"((\t+|\s+)\b(if|else\s+if|else|while|loop(?!-)|return|continue(\s+loop|)?)\b)"},
        {"playerobjects", PLAYEROBJECTS, "italic bold", R"(game\s*mode|all\s*players?|victim|attacker|sender|(loop-|)player|shooter|uuid\s+of\s*|'s\s+uuid|location\s+of\s*|'s\s+location|console)"},
        {"comment", COMMENT, "italic", R"(^(#.*)$)"},
        {"multiLineComment", COMMENT, "italic", R"(###\r?\n([\s\S]*?)\r?\n###(\r?\n|$))"},
        {"string", STRING, "italic", R"("(\\"|[^"])*")"},
        {"event", EVENT, "bold", R"(^on\s+[^:]+:)"},
        {"stop", STOP, "", R"(\b(((un|)cancel(\s+|\s+the\s+)event|break|shutdown))\b)"}
    };
}
