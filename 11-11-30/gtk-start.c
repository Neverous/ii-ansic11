#include <gtk/gtk.h>

int main(int argc,char *argv[])
{
    gtk_init (&argc, &argv);

    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Hello");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 30);

    GtkWidget *button=gtk_button_new_with_label("Hello World");
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show(button);

    gtk_widget_show(window);

    gtk_main ();

    return 0;
}
