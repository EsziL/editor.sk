#include "menuBarActions.h"
#include "../editor/textEditor.h"
#include "../etc/error.h"
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>



std::tuple<std::string, int> getFileContent(GFile *file) {
    char *path = g_file_get_path(file);
    std::string strPath(path);
    std::ifstream f(path);
    if (strPath.substr(strPath.length()-3) != ".sk") {
        std::cout << "Not a skript file" << std::endl;
        showError("Not a skript file");
        return {"", 1};
    }
    if (!f.is_open()) {
        std::cout << "Failed to open file" << std::endl;
        return {"", 1};
    }
    std::string content;
    std::string line;
    while(std::getline(f, line)) {
        content += line + "\n";
    }

    f.close();
    return {content, 0};
}

// this was hell to figure out, but it works
static void
openFileCallback(GObject *source_object, GAsyncResult *result, gpointer user_data)
{
    GTask *task = static_cast<GTask*>(user_data);
    GtkFileDialog *dialog = GTK_FILE_DIALOG(g_task_get_source_object(task));
    GFile *file = gtk_file_dialog_open_finish(dialog, result, NULL);
    std::tuple<std::string, int> content = getFileContent(file);
    if (std::get<1>(content) == 0) { 
        gtk_text_buffer_set_text(gBuffer, std::get<0>(content).c_str(), -1);
    }
}


static void open_file_dialog(GtkWindow *parent)
{
    GtkFileDialog *dialog = gtk_file_dialog_new();
    GTask *task = g_task_new(dialog, NULL, NULL, NULL);
    gtk_file_dialog_open(dialog, parent, NULL, (GAsyncReadyCallback)openFileCallback, task);
}

void aRedo(GApplication* app, gpointer data) {
    std::cout << "Undo" << std::endl;
}
void aUndo(GApplication* app, gpointer data) {
    std::cout << "Redo" << std::endl;
}
void aCut(GApplication* app, gpointer data) {
    std::cout << "Cut" << std::endl;
}
void aOpenFile(GApplication* app, gpointer data) {
    std::cout << "OpenFile" << std::endl;

    open_file_dialog(GTK_WINDOW(data));
}