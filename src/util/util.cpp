#include "util.h"
#include "../ui/etc/error.h"
#include <filesystem>
#include <fstream>
#include <string>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(str);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

GtkWidget* get_nth_child(GtkWidget *box, int n) {
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(box));
    int count = 0;

    while (child != NULL) {
        if (count == n) {
            return child;
        }
        count++;
        child = gtk_widget_get_next_sibling(child);
    }

    return NULL;
}


std::string read_file_contents(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        std::string contents((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
        file.close();
        return contents;
    } else {
        // Handle file opening error
        return "";
    }
}


void save_text_to_file(GtkTextBuffer* buffer, const std::string& path) {
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    std::string text = gtk_text_buffer_get_text(buffer, &start, &end, false);

    std::ofstream file(path, std::ios::out);
    if (file.is_open()) {
        file << text;
        file.close();
    } else {
        showError("Could not cache file to disk, if you close it, it will be lost.");
    }
}