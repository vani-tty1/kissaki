#pragma once
#include <adwaita.h>
#include <gtksourceview/gtksource.h>
#include "kissaki-window.h"

struct _KissakiWindow
{
	AdwApplicationWindow  parent_instance;
        GtkSourceView *source_view;

	// TODO: add widgets
};
