#include <gtk/gtk.h>
#include "highlighter.h"


GtkTextBuffer *gBuffer = NULL;
GtkWidget *gHighlight = NULL;
GtkWidget *gOverlay = NULL;
GtkWidget *gWindow = NULL;
GtkWidget *gTextView = NULL;


static int textViewLines(GtkTextBuffer *buffer) {
    GtkTextIter iter;
    int line_count = 0;
    gtk_text_buffer_get_start_iter(buffer, &iter);
    if (gtk_text_iter_is_end(&iter)) {
        return 0;
    }
    do {
        line_count++;
    } while (gtk_text_iter_forward_line(&iter));
    return line_count;
}

static int getCursorLine(GtkTextBuffer *buffer) {
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, gtk_text_buffer_get_insert(buffer));
    return gtk_text_iter_get_line(&iter) + 1;
}

static void onEditorPositionChange(GtkTextBuffer *buffer, const GtkTextIter *location, GtkTextMark *mark, gpointer userData) {
    static int lastLine = -1;
    int currentLine = getCursorLine(buffer);
    if (currentLine != lastLine) {
        lastLine = currentLine;
        gtk_widget_set_margin_top(gHighlight, 25 * (currentLine - 1));

        int lines = textViewLines(gBuffer);

        gtk_widget_set_size_request(gOverlay, -1, (gtk_widget_get_height(gWindow)+(25*(lines-1))));
    }
}

static void onTextChanged(GtkTextBuffer *buffer, gpointer user_data) {
    SyntaxHighlighter *highlighter = static_cast<SyntaxHighlighter *>(user_data);
    highlighter->highlight_text();
}

GtkWidget* createTextEditor(GtkWidget *window) {
    GtkWidget *bgr = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(bgr, "bgr");
    gtk_widget_set_hexpand(bgr, TRUE);
    gtk_widget_set_vexpand(bgr, TRUE);

    GtkWidget *overlay = gtk_overlay_new();
    gtk_widget_set_hexpand(overlay, TRUE);
    gtk_widget_set_vexpand(overlay, TRUE);

    GtkWidget *textView = gtk_text_view_new();
    gtk_widget_add_css_class(textView, "textview");
    gtk_widget_set_hexpand(textView, TRUE);
    gtk_widget_set_vexpand(textView, TRUE);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    GtkWidget *highlight = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(highlight, -1, 28);
    gtk_widget_add_css_class(highlight, "highlight");
    gtk_widget_set_halign(highlight, GTK_ALIGN_FILL);
    gtk_widget_set_valign(highlight, GTK_ALIGN_START);

    gtk_overlay_set_child(GTK_OVERLAY(overlay), bgr);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), highlight);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), textView);

    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_hexpand(scrolledWindow, TRUE);
    gtk_widget_set_vexpand(scrolledWindow, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), overlay);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gBuffer = buffer;
    gHighlight = highlight;
    gOverlay = overlay;
    gWindow = window;
    gTextView = textView;

    g_signal_connect(buffer, "mark-set", G_CALLBACK(onEditorPositionChange), buffer);

    SyntaxHighlighter *highlighter = new SyntaxHighlighter(buffer);
    g_signal_connect(buffer, "changed", G_CALLBACK(onTextChanged), highlighter);

    return scrolledWindow;
}
