#include "fileBar.h"
#include "glibconfig.h"
#include "../editor/textEditor.h"
#include "gtk/gtk.h"
#include "pango/pango-layout.h"
#include <filesystem>

GtkWidget* gFileBar = NULL;
int fileCount = 0;

void fileBarInit() {
    gFileBar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_visible(gFileBar, FALSE);
    gtk_widget_add_css_class(gWindow, "fileBarOpen");
}

void fileBarShow() {
    gtk_widget_set_visible(gFileBar, TRUE);
    gtk_widget_set_size_request(gFileBar, -1, 30);
    gtk_widget_set_hexpand(gFileBar, TRUE);
    gtk_widget_set_halign(gFileBar, GTK_ALIGN_FILL);
    gtk_widget_set_valign(gFileBar, GTK_ALIGN_START);
    gtk_widget_add_css_class(gFileBar, "fileBar");
}

void fileBarClose() {
    gtk_widget_remove_css_class(gWindow, "fileBarOpen");
    fileBarInit();   
}

void fileBarOpenFile(std::string path) {
    fileCount++;
    GtkWidget *file = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    int width;
    gtk_widget_set_halign(file, GTK_ALIGN_START);
    gtk_widget_set_valign(file, GTK_ALIGN_FILL);
    std::filesystem::path filePath(path);
    GtkWidget *label = gtk_label_new(filePath.filename().string().c_str());
    gtk_widget_set_vexpand(label, TRUE);
    gtk_widget_set_hexpand(label, TRUE);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(file), label);
    gtk_box_append(GTK_BOX(gFileBar), file);
    pango_layout_get_size(gtk_label_get_layout(GTK_LABEL(label)), &width, NULL);
    gtk_widget_set_size_request(file, (width/PANGO_SCALE)*1.5, 30);
    
}