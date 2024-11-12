#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

// Callback to disable the ESC key
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Escape) {
        return TRUE;  // Ignore the ESC key
    }
    return FALSE;  // Allow other keys
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create a new GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);   // Remove window borders
    gtk_window_fullscreen(GTK_WINDOW(window));             // Make window fullscreen

    // Connect the destroy signal to quit the GTK loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Connect key-press event to disable ESC key
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Create a WebKit WebView to display web content
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Load a local HTML file or a URL served by your C++ backend
    // Uncomment the option that you prefer:

    // Load local HTML file
    webkit_web_view_load_uri(web_view, "file:index.html");

    // Load HTML from a local C++ server running at http://localhost:8080
    // webkit_web_view_load_uri(web_view, "http://localhost:8080/");

    // Add the WebView to the GTK window
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));

    // Show the GTK window and all its contents
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
