#include <gtk/gtk.h>
#include <string.h>   // for css

int main (int argc, char *argv[])
{
GtkWidget *window;

/*---- CSS ------------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*---------------------------*/

gtk_init(&argc, &argv);

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_widget_set_size_request(window, 400, 300);
gtk_window_set_title(GTK_WINDOW(window), "wikistack");
g_signal_connect(G_OBJECT (window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

/* ----------------- CSS ----------------------------------------------------------------------------------------------*/
provider = gtk_css_provider_new ();
display = gdk_display_get_default ();
screen = gdk_display_get_default_screen (display);
gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

const gchar* home = "./mystyle.css";

GError *error = 0;

gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
g_object_unref (provider);
/* --------------------------------------------------------------------------------------------------------------------*/

gtk_widget_show_all(window);
gtk_main ();
return 0;
}
