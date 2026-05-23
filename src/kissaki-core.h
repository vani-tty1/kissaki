#pragma once

#include <gtksourceview/gtksource.h>
#include <adwaita.h>

void kissaki_core_setup_editor (GtkSourceView *source_view);
void on_dark_changed (AdwStyleManager *style_manager,
                      GParamSpec      *pspec,
                      GtkSourceView   *source_view);
