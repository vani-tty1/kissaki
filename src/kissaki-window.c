/* kissaki-window.c
 *
 * Copyright 2026 Giovanni
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"

#include "kissaki-window.h"
#include "kissaki-window-private.h"
#include "kissaki-core.h"
#include "kissaki-core.h"



G_DEFINE_FINAL_TYPE (KissakiWindow, kissaki_window, ADW_TYPE_APPLICATION_WINDOW)

static void
kissaki_window_class_init (KissakiWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/io/github/vani_tty1/kissaki/kissaki-window.ui");
	//gtk_widget_class_bind_template_child (widget_class, KissakiWindow, label);
    gtk_widget_class_bind_template_child (widget_class, KissakiWindow, source_view);
}

static void
kissaki_window_init (KissakiWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
    kissaki_core_setup_editor (self->source_view);
    g_signal_connect (adw_style_manager_get_default (),
                  "notify::dark",
                  G_CALLBACK (on_dark_changed),
                  self->source_view);
}
