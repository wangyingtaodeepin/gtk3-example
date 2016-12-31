#include <gtk/gtk.h>
#include <glib/gprintf.h>       // g_sprintf
#include <stdlib.h>             // system (web link)
#include <openssl/md5.h>        // MD5 hash
#include <gdk/gdkkeysyms-compat.h>     // GDK_Escape

/* Well, by golly, this program uses widgets */
typedef struct {
    GtkWidget *window1;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *label1;
} AppWidgets;

/* Make the copy, cut, paste, delete menu items work */
#if 1
#define UNUSED gpointer _x_ G_GNUC_UNUSED
#define FOCUSED GTK_EDITABLE( \
    (gtk_widget_has_focus(app->entry2))?app->entry2:app->entry1)
#define EDIT(copy,clipboard) \
void edit_##copy(UNUSED, AppWidgets *app){ \
    gtk_editable_##copy##_##clipboard(FOCUSED); }

EDIT(copy,clipboard)
EDIT(cut,clipboard)
EDIT(paste,clipboard)

#undef EDIT
#endif

void file_save_as(GtkWidget *widget)
{

}

void file_save(GtkWidget *widget)
{

}

void file_open(GtkWidget *widget)
{

}

void file_new(GtkWidget *widget)
{

}

/* show the about box */
void help_about(GtkWidget *widget)
{
    GtkBuilder *builder;
    GObject *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "hasher.glade", NULL);
    window = gtk_builder_get_object(builder, "demo_about");
    gtk_widget_show(GTK_WIDGET(window));

}

/* Serve up 32 hex digits, Must be freed */
gchar *make_hash(const gchar *input)
{
    int i;
    unsigned char bytes[16];
    gchar hexdigits[2];
    gchar *hexstring = g_malloc(32);
    hexstring[0] = '\0';
    MD5((unsigned char*)input, g_utf8_strlen(input, 99), bytes);
    for(i=0; i<16; i++)
    {
        g_sprintf(hexdigits, "%02x", bytes[i]);
        g_strlcat(hexstring, hexdigits, 32);
    }
    return hexstring;
}

/* Somebody pressed the check hash button */
void check_hash(UNUSED, AppWidgets *app)
{
    gchar *hash = make_hash(gtk_entry_get_text(GTK_ENTRY(app->entry1)));
    if(!g_strcmp0(hash, gtk_entry_get_text(GTK_ENTRY(app->entry2))))
    {
        gtk_label_set_text(GTK_LABEL(app->label1), "valid");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(app->label1), "fail");
    }
    g_free(hash);
}

/* Somebody pressed the Generate Hash button */
void generate_hash(UNUSED, AppWidgets *app)
{
    gchar *hash = make_hash(gtk_entry_get_text(GTK_ENTRY(app->entry1)));
    gtk_entry_set_text(GTK_ENTRY(app->entry2), hash);
    g_free(hash);
}

/* Somebody pressed the ESC key */
void key_event(UNUSED, GdkEventKey *event)
{
    if (event->keyval == GDK_Escape)
    {
        gtk_main_quit();
    }
}

/* Somebody ran our program */
int main(int argc, char  **argv)
{
    GtkBuilder *builder;
    AppWidgets *app = g_slice_new(AppWidgets);
    GError *err = NULL;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "hasher.glade", &err);

    if (err)
    {
        g_error(err->message);
        g_error_free(err);
        g_slice_free(AppWidgets, app);
        return 1;
    }

    // Get handlers to our app widgets.
    #define appGET(xx) \
    app->xx=GTK_WIDGET(gtk_builder_get_object(builder,#xx))
    appGET(entry1);
    appGET(entry2);
    appGET(label1);
    appGET(window1);
    gtk_builder_connect_signals(builder, app);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(GTK_WIDGET(app->window1));
    gtk_main();
    g_slice_free(AppWidgets, app);
}
