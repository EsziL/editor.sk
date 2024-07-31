#include "highlighter.h"
#include "highlights.h"


SyntaxHighlighter::SyntaxHighlighter(GtkTextBuffer *buffer) : buffer(buffer) {
    GtkTextTagTable *tag_table = gtk_text_buffer_get_tag_table(buffer);

    auto highlight_rules = getSyntaxHighlight();

    for (const auto& rule : highlight_rules) {
        GtkTextTag *tag = gtk_text_tag_new(std::get<0>(rule).c_str());
        g_object_set(tag, "foreground", std::get<1>(rule).c_str(), NULL);
        gtk_text_tag_table_add(tag_table, tag);
        tags.push_back(tag);
        patterns.push_back(std::regex(std::get<2>(rule)));
    }
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