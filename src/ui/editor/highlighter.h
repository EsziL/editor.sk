#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <gtk/gtk.h>
#include <vector>
#include <regex>
#include <string>

class SyntaxHighlighter {
public:
    SyntaxHighlighter(GtkTextBuffer *buffer);
    void highlight_text();

private:
    GtkTextBuffer *buffer;
    std::vector<GtkTextTag*> tags;
    std::vector<std::regex> patterns;
    std::pair<int, int> parseFontStyle(const std::string &style);

    void highlight_pattern(const std::string &text, const std::regex &pattern, GtkTextTag *tag);
};

#endif // HIGHLIGHTER_H
