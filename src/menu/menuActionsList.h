#ifndef MENUACTIONSLIST_H
#define MENUACTIONSLIST_H

#include <gtk/gtk.h>
#include <vector>
#include <tuple>

std::vector<std::tuple<GSimpleAction **, const gchar *, GCallback>> getActions();

#endif // MENUACTIONSLIST_H