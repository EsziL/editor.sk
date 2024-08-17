#include "menuBarActions.h"
#include "../editor/textEditor.h"
#include "../etc/error.h"
#include "../etc/fileBar.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>



std::tuple<std::string, int> getFileContent(std::string path) {
    std::ifstream f(path);
    if (path.substr(path.length()-3) != ".sk") {
        showError("Not a skript file");
        return {"", 1};
    }
    if (!f.is_open()) {
        showError("Failed to open file");
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
    GError *error = NULL;
    GFile *file = gtk_file_dialog_open_finish(dialog, result, &error);

    if (error != NULL) {
        if (error->domain != 1887 && error->code != 2) showError(error->message);
        g_error_free(error);
        g_object_unref(task);
        return;
    }
    if (file == NULL) {
        g_object_unref(task);
        return;
    }

    std::filesystem::path filePath(g_file_get_path(file));
    openFile(filePath.string(), true);
    
}


void openFile(std::string path, bool isNew) {
    std::tuple<std::string, int> content = getFileContent(path);
    if (std::get<1>(content) == 0) { 
        if (fileCount == 0) {
            fileBarShow();
        } if (isNew) {
            fileBarOpenFile(path);
        }
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