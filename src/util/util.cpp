#include "util.h"

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
            return child; // Return the nth child
        }
        count++;
        child = gtk_widget_get_next_sibling(child);
    }

    return NULL; // Return NULL if n is out of bounds
}