#include "highlighter.h"
#include "highlights.h"
#include <sstream>


SyntaxHighlighter::SyntaxHighlighter(GtkTextBuffer *buffer) : buffer(buffer) {
    GtkTextTagTable *tag_table = gtk_text_buffer_get_tag_table(buffer);

    auto highlight_rules = getSyntaxHighlight();

    for (const auto& rule : highlight_rules) {
        GtkTextTag *tag = gtk_text_tag_new(std::get<0>(rule).c_str());

        std::string color_str = std::get<1>(rule);
        std::string foreground_color;
        std::string background_color;

        std::istringstream color_stream(color_str);
        if (color_stream >> foreground_color >> background_color) {
            g_object_set(tag, 
                         "foreground", foreground_color.c_str(), 
                         "background", background_color.c_str(), 
                         "style", parseFontStyle(std::get<2>(rule)).first, 
                         "weight", parseFontStyle(std::get<2>(rule)).second,
                         NULL);
        } else {
            g_object_set(tag, 
                         "foreground", color_str.c_str(), 
                         "style", parseFontStyle(std::get<2>(rule)).first, 
                         "weight", parseFontStyle(std::get<2>(rule)).second,
                         NULL);
        }

        gtk_text_tag_table_add(tag_table, tag);
        tags.push_back(tag);
        patterns.push_back(std::regex(std::get<3>(rule)));
    }
}

std::pair<int, int> SyntaxHighlighter::parseFontStyle(const std::string &style) {
    int fontStyle = PANGO_STYLE_NORMAL;
    int fontWeight = PANGO_WEIGHT_NORMAL;

    if (style.find("italic") != std::string::npos) {
        fontStyle = PANGO_STYLE_ITALIC;
    }
    if (style.find("bold") != std::string::npos) {
        fontWeight = PANGO_WEIGHT_BOLD;
    }

    return std::make_pair(fontStyle, fontWeight);
}

void SyntaxHighlighter::highlight_text() {
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);
    
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    std::string str_text(text);
    g_free(text);

    for (size_t i = 0; i < patterns.size(); ++i) {
        highlight_pattern(str_text, patterns[i], tags[i]);
    }
}

void SyntaxHighlighter::highlight_pattern(const std::string &text, const std::regex &pattern, GtkTextTag *tag) {
    std::sregex_iterator iter(text.begin(), text.end(), pattern);
    std::sregex_iterator end;

    while (iter != end) {
        std::smatch match = *iter;
        int start_offset = match.position();
        int end_offset = start_offset + match.length();

        GtkTextIter start_iter, end_iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &start_iter, start_offset);
        gtk_text_buffer_get_iter_at_offset(buffer, &end_iter, end_offset);

        gtk_text_buffer_apply_tag(buffer, tag, &start_iter, &end_iter);

        ++iter;
    }
}