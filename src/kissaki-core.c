/* kissaki-core.c
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


#include "kissaki-core.h"
#include <adwaita.h>


void
on_dark_changed (AdwStyleManager *style_manager,
                 GParamSpec      *pspec,
                 GtkSourceView   *source_view)
{
    GtkSourceBuffer *buffer;
    GtkSourceStyleSchemeManager *sm;
    GtkSourceStyleScheme *scheme;
    const char *scheme_name;

    buffer = GTK_SOURCE_BUFFER (
        gtk_text_view_get_buffer (GTK_TEXT_VIEW (source_view))
    );

    if (adw_style_manager_get_dark (style_manager))
        scheme_name = "Adwaita-dark";
    else
        scheme_name = "Adwaita";

    sm = gtk_source_style_scheme_manager_get_default ();
    scheme = gtk_source_style_scheme_manager_get_scheme (sm, scheme_name);
    gtk_source_buffer_set_style_scheme (buffer, scheme);
}


void
kissaki_core_setup_editor (GtkSourceView *source_view, const char *filename)
{
    GtkSourceBuffer *buffer;
    GtkSourceLanguageManager *langmgr;
    GtkSourceLanguage *lang;
    GtkSourceStyleSchemeManager *schemamgr;
    GtkSourceStyleScheme *scheme;
    AdwStyleManager *style_manager;
    const char *scheme_name;

    buffer = GTK_SOURCE_BUFFER (
        gtk_text_view_get_buffer (GTK_TEXT_VIEW (source_view))
    );

    langmgr = gtk_source_language_manager_get_default ();
    lang = gtk_source_language_manager_guess_language (langmgr, filename, NULL);
    gtk_source_buffer_set_language (buffer, lang);

    style_manager = adw_style_manager_get_default ();
    if (adw_style_manager_get_dark (style_manager))
        scheme_name = "Adwaita-dark";
    else
        scheme_name = "Adwaita";

    schemamgr = gtk_source_style_scheme_manager_get_default ();
    scheme = gtk_source_style_scheme_manager_get_scheme (schemamgr, scheme_name);
    gtk_source_buffer_set_style_scheme (buffer, scheme);
}


