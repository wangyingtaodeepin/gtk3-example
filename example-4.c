#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget,
                        gpointer   data)
{
    g_print("Hello World\n");
}

static void dialog_page(GtkWidget *widget,
                        gpointer   data)
{
    GtkBuilder *builder;
    GObject *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "dialog.glade", NULL);
    //window = gtk_builder_get_object(builder, "window_main");
    g_object_unref(builder);
    //gtk_widget_show(GTK_WIDGET(window));

}

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    AtkObject *obj;

    gtk_init(&argc, &argv);

    /* Construct a GtkBuilder instance and load our UI description  */
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "builder.ui", NULL);

    /* connect signal handlers to the constructed widgets.  */
    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    button = gtk_builder_get_object(builder, "button1");
    g_signal_connect (button, "clicked", G_CALLBACK(print_hello), NULL);
    obj = gtk_widget_get_accessible(GTK_WIDGET(button));
    // atk_object_set_name(obj, "wangyingtao");

    button = gtk_builder_get_object(builder, "button2");
    g_signal_connect (button, "clicked", G_CALLBACK(dialog_page), NULL);
    obj = gtk_widget_get_accessible(GTK_WIDGET(button));
    // atk_object_set_name(obj, "wangyingtao2");

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect (button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main ();

    return 0;
}

