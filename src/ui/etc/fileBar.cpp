#include "fileBar.h"
#include "../editor/textEditor.h"
#include "../menu/menuBarActions.h"
#include "../../util/util.h"
#include <filesystem>

GtkWidget* gFileBar = NULL;
int fileCount = 0;
std::string currentPath = "";

std::map<std::string, GtkWidget*> fileBarMap;

void fileBarInit() {
    gFileBar = gtk_flow_box_new();
    gtk_widget_set_visible(gFileBar, FALSE);
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(gFileBar), 10);
    gtk_flow_box_set_column_spacing(GTK_FLOW_BOX(gFileBar), 1);
}


void fileBarShow() {
    gtk_widget_set_visible(gFileBar, TRUE);
    gtk_widget_set_size_request(gFileBar, -1, 30);
    gtk_widget_set_hexpand(gFileBar, TRUE);
    gtk_widget_set_halign(gFileBar, GTK_ALIGN_FILL);
    gtk_widget_set_valign(gFileBar, GTK_ALIGN_START);
    gtk_widget_add_css_class(gFileBar, "fileBar");
    gtk_widget_add_css_class(gWindow, "gWindowShift");
}

void fileBarClose() {
    gtk_widget_set_visible(gFileBar, FALSE);
    gtk_widget_remove_css_class(gWindow, "gWindowShift");
}

void fileBarOpenFile(std::string path) {
    fileCount++;
    GtkWidget *file = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_halign(file, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(file, GTK_ALIGN_FILL);
    std::filesystem::path filePath(path);
    GtkWidget *label = gtk_label_new(filePath.filename().string().c_str());
    gtk_widget_set_vexpand(label, TRUE);
    gtk_widget_set_hexpand(label, TRUE);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(file), label);
    gtk_flow_box_insert(GTK_FLOW_BOX(gFileBar), file, -1);
    
    GtkWidget *close = gtk_button_new();
    gtk_widget_set_halign(close, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(close, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(close, FALSE);
    gtk_widget_set_vexpand(close, TRUE);
    gtk_button_set_label(GTK_BUTTON(close), "×");
    gtk_widget_add_css_class(close, "fileBarClose");
    gtk_box_append(GTK_BOX(file), close);

    fileBarMap[path] = file;

    currentPath = path;

    g_signal_connect(close, "clicked", G_CALLBACK(fileBarCloseFile_byButton), g_strdup(path.c_str()));
}



void fileBarCloseFile_byButton(GtkButton *close, gpointer user_data) {
    std::string path = static_cast<const char*>(user_data);
    fileBarCloseFile(path);
}

void fileBarCloseFile(std::string path) {
    fileCount--;
    gtk_flow_box_remove(GTK_FLOW_BOX(gFileBar), fileBarMap[path]);
    fileBarMap.erase(path);
    if (fileCount <= 0) {
        fileBarClose();
        gtk_text_buffer_set_text(gBuffer, "", -1);
    } else {
        openFile(std::next(fileBarMap.begin(), 0)->first, false);
    }   
}