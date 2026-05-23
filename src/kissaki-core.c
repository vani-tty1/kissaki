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
kissaki_core_setup_editor (GtkSourceView *source_view)
{
    GtkSourceBuffer *buffer;
    GtkSourceLanguageManager *lm;
    GtkSourceLanguage *lang;
    GtkSourceStyleSchemeManager *sm;
    GtkSourceStyleScheme *scheme;
    AdwStyleManager *style_manager;
    const char *scheme_name;

    buffer = GTK_SOURCE_BUFFER (
        gtk_text_view_get_buffer (GTK_TEXT_VIEW (source_view))
    );

    lm = gtk_source_language_manager_get_default ();
    lang = gtk_source_language_manager_get_language (lm, "c");
    gtk_source_buffer_set_language (buffer, lang);

    style_manager = adw_style_manager_get_default ();
    if (adw_style_manager_get_dark (style_manager))
        scheme_name = "Adwaita-dark";
    else
        scheme_name = "Adwaita";

    sm = gtk_source_style_scheme_manager_get_default ();
    scheme = gtk_source_style_scheme_manager_get_scheme (sm, scheme_name);
    gtk_source_buffer_set_style_scheme (buffer, scheme);
}


