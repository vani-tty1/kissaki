/* kissaki-application.c
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
#include <glib/gi18n.h>

#include "kissaki-application.h"
#include "kissaki-window.h"

struct _KissakiApplication
{
	AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (KissakiApplication, kissaki_application, ADW_TYPE_APPLICATION)

KissakiApplication *
kissaki_application_new (const char        *application_id,
                         GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (KISSAKI_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     "resource-base-path", "/io/github/vani_tty1/kissaki",
	                     NULL);
}

static void
kissaki_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (KISSAKI_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (KISSAKI_TYPE_WINDOW,
		                       "application", app,
		                       NULL);

	gtk_window_present (window);
}

static void
kissaki_application_class_init (KissakiApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = kissaki_application_activate;
}

static void
kissaki_application_about_action (GSimpleAction *action,
                                  GVariant      *parameter,
                                  gpointer       user_data)
{
    static const char *developers[] = {"Giovanni Rafanan", NULL};
    static const char *designers[] = {"Giovanni Rafanan", NULL};
    GtkWindow *window = NULL;
    AdwDialog *about;
	KissakiApplication *self = user_data;

	g_assert (KISSAKI_IS_APPLICATION (self));
    window = gtk_application_get_active_window (GTK_APPLICATION (self));

	 about = adw_about_dialog_new_from_appdata (
        "/io/github/vani_tty1/kissaki/io.github.vani_tty1.kissaki.metainfo.xml",
        PACKAGE_VERSION
    );

    adw_about_dialog_set_developers(ADW_ABOUT_DIALOG(about), developers);
    adw_about_dialog_set_version(ADW_ABOUT_DIALOG (about), PACKAGE_VERSION);
    adw_about_dialog_set_designers (ADW_ABOUT_DIALOG(about), designers);
    adw_dialog_present (about, GTK_WIDGET (window));

}

static void
kissaki_application_quit_action (GSimpleAction *action,
                                 GVariant      *parameter,
                                 gpointer       user_data)
{
	KissakiApplication *self = user_data;

	g_assert (KISSAKI_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", kissaki_application_quit_action },
	{ "about", kissaki_application_about_action },
};

static void
kissaki_application_init (KissakiApplication *self)
{
	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<control>q", NULL });
}
