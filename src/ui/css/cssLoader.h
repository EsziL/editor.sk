#ifndef CSSLOADER_H
#define CSSLOADER_H

#include <gtk/gtk.h>
#include <string>

void initCSS();
static std::string get_config_path();
extern std::string config_path;

#endif // CSSLOADER_H