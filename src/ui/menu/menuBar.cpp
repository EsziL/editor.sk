#include "menuBar.h"
#include "menuActionsList.h"
#include <vector>
#include <tuple>
#include <string>
#include <cctype>

std::string camelToTitle(std::string camelCase) {
    std::string titleCase;
    bool isFirstChar = true;

    for (char c : camelCase) {
        if (isFirstChar || std::isupper(c)) {
            titleCase += std::toupper(c);
            isFirstChar = false;
        } else {
            titleCase += std::tolower(c);
        }
    }

    return titleCase;
}

GMenu* createMenuBar(GtkApplication* app) {
    
    std::vector<std::tuple<GSimpleAction **, const gchar *, GCallback>> actions = getActions();

    std::vector<std::string> fileMenuNames;
    std::vector<std::string> editMenuNames;
    

    for (auto &action : actions) {
        GSimpleAction **actionPtr = std::get<0>(action);
        const gchar *actionName = std::get<1>(action);
        GCallback actionCallback = std::get<2>(action);

        std::string actionNameStr = std::get<1>(action);
        std::size_t dot = actionNameStr.find(".");
        std::string type = actionNameStr.substr(0, dot);
        if (type == "file") {
            fileMenuNames.push_back(actionNameStr);
        } else if (type == "edit") {
            editMenuNames.push_back(actionNameStr);
        }
        *actionPtr = g_simple_action_new(actionName, NULL);
        g_signal_connect(*actionPtr, "activate", actionCallback, NULL);
        g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(*actionPtr));
    }

    GMenu *menuBar = g_menu_new();
    GMenuItem *menuItem;

    // file menu

    menuItem = g_menu_item_new("File", NULL);
    GMenu *fileMenu = g_menu_new();
    for (const auto &name : fileMenuNames) {
        std::size_t dotPos = name.find('.');
        std::string fileName = (dotPos != std::string::npos) ? name.substr(dotPos + 1) : name;

        GMenuItem *fileItem = g_menu_item_new(camelToTitle(fileName).c_str(), ("app." + name).c_str());
        g_menu_append_item(fileMenu, fileItem);
        g_object_unref(fileItem);
    }


    g_menu_item_set_submenu(menuItem, G_MENU_MODEL(fileMenu));
    g_menu_append_item(menuBar, menuItem);
    g_object_unref(fileMenu);
    g_object_unref(menuItem);

    // edit menu

    menuItem = g_menu_item_new("Edit", NULL);
    GMenu *editMenu = g_menu_new();

    for (const auto &name : editMenuNames) {
        std::size_t dotPos = name.find('.');
        std::string editName = (dotPos != std::string::npos) ? name.substr(dotPos + 1) : name;

        GMenuItem *editItem = g_menu_item_new(camelToTitle(editName).c_str(), ("app." + name).c_str());
        g_menu_append_item(editMenu, editItem);
        g_object_unref(editItem);
    }
    g_menu_item_set_submenu(menuItem, G_MENU_MODEL(editMenu));
    g_menu_append_item(menuBar, menuItem);
    g_object_unref(editMenu);
    g_object_unref(menuItem);

    return menuBar;
}