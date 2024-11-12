#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <thread>
#include <fstream>
#include <sstream>
#include "crow_all.h"  // Include Crow's single-header file

// Function to disable the ESC key
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Escape) {
        return TRUE;  // Ignore the ESC key
    }
    return FALSE;  // Allow other keys
}

// Function to read HTML file content
std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to run the Crow server
void run_crow_server() {
    crow::SimpleApp app;

    // Route to serve the HTML file
    CROW_ROUTE(app, "/")([]() {
        std::string html_content = read_file("index.html");  // Ensure index.html is in the same directory
        return crow::response(html_content);
    });

    app.port(8080).multithreaded().run();
}

// Function to create and display the GTK window
void run_gtk_window() {
    gtk_init(nullptr, nullptr);

    // Create a new GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);  // Remove window borders
    gtk_window_fullscreen(GTK_WINDOW(window));            // Make window fullscreen

    // Connect the destroy signal to quit the GTK loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Connect key-press event to disable ESC key
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Create a WebKit WebView to display web content
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Load the URL from the Crow server
    webkit_web_view_load_uri(web_view, "http://localhost:8080/");

    // Add the WebView to the GTK window
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));

    // Show the GTK window and all its contents
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

int main() {
    // Start the Crow server in a separate thread
    std::thread crow_thread(run_crow_server);

    // Run the GTK window in the main thread
    run_gtk_window();

    // Join the Crow server thread when the GTK window is closed
    crow_thread.join();

    return 0;
}

