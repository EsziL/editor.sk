#include "fileBar.h"
#include "../editor/textEditor.h"
#include <iostream>
#include <string>

GtkWidget* gFileBar = NULL;

void fileBarInit() {
    gFileBar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
}

void fileBarShow() {
    gtk_widget_set_size_request(gFileBar, -1, 30);
    gtk_widget_set_hexpand(gFileBar, TRUE);
    gtk_widget_set_halign(gFileBar, GTK_ALIGN_FILL);
    gtk_widget_set_valign(gFileBar, GTK_ALIGN_START);
    gtk_widget_add_css_class(gFileBar, "fileBar");
    gtk_widget_add_css_class(gOverlay, "overlayFileBarEnabled");
}

void fileBarClose() {
    fileBarInit();
    gtk_widget_remove_css_class(gOverlay, "overlayFileBarEnabled");
}

void fileBarOpenFile(std::string path) {
    std::cout << "Opening file: " << path << std::endl;
}