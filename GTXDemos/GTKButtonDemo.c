#include <gtk/gtk.h>

/*Compile with:
gcc base.c -o base `pkg-config --cflags --libs gtk+-2.0`
*/

/* This callback quits the program */
static gboolean delete_event( GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_main_quit ();
    return FALSE;
}

/* Our callback.
 * The data passed to this function is printed to stdout */
static void callback(GtkWidget *widget, gpointer data) {
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

/*Creates a box with an icon and a label. Can be used to put into buttons*/
static GtkWidget *png_label_box(gchar *png_filename, gchar *label_text) {
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    box = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(box), 2);

    image = gtk_image_new_from_file(png_filename);

    label = gtk_label_new(label_text);

    gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 3);

    gtk_widget_show(image);
    gtk_widget_show(label);

    return box;
}

static void toggled(GtkWidget *widget, gpointer data) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        g_print("%s button was set to active.\n", (char *) data);
    } else {
        g_print("%s button was set to inactive.\n", (char *) data);
    }
}

int main(int argc, char *argv[]) {
    /*Passes GTK any arguments given - this is required.*/
    gtk_init (&argc, &argv);

    /*
    All widgets in GTK+ are of type GtkWidget. It is then typecast into the appropriate thing
    for any functions, seen below. For example, to use the GtkWidget window as a window, we
    cast it with GTK_WINDOW(window).
    */
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *iconButton;
    GtkWidget *box;
    GtkWidget *toggleButton;
    GtkWidget *checkButton;
    GtkWidget *seperator;
    GtkWidget *radioButton1;
    GtkWidget *radioButton2;
    GtkWidget *radioButton3;

    /*Creates a new window*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*Set title*/
    gtk_window_set_title(GTK_WINDOW(window), "GTK Playground");

    /*Set up a listener on the window, calls delete_event on 'delete-event' signal.*/
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);

    /*Sets the window border.*/
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    /*Create a grid, which will arrange some widgets for us.*/
    grid = gtk_grid_new();

    /*Puts the table into the window.*/
    gtk_container_add(GTK_CONTAINER(window), grid);

    /*Create a button with a label, connect it to the callback function.*/
    button = gtk_button_new_with_label("Button");
    g_signal_connect(button, "clicked", G_CALLBACK(callback), "button");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    /*Creating an iconed button.*/
    iconButton = gtk_button_new();
    g_signal_connect(iconButton, "clicked", G_CALLBACK(callback), "iconed button");
    box = png_label_box("folder-icon.png", "icon button");
    gtk_container_add(GTK_CONTAINER(iconButton), box);
    gtk_grid_attach(GTK_GRID(grid), iconButton, 1, 0, 1, 1);

    /*Creating a toggle button.*/
    toggleButton = gtk_toggle_button_new_with_label("Toggle");
    g_signal_connect(toggleButton, "toggled", G_CALLBACK(toggled), "toggle");
    gtk_grid_attach(GTK_GRID(grid), toggleButton, 0, 1, 2, 1);

    /*Creating a check button.*/
    checkButton = gtk_check_button_new_with_label("Check");
    g_signal_connect(checkButton, "toggled", G_CALLBACK(toggled), "check");
    gtk_grid_attach(GTK_GRID(grid), checkButton, 0, 2, 1, 1);

    /*Horizontal Seperator*/
    seperator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_grid_attach(GTK_GRID(grid), seperator, 0, 3, 2, 1);

    /*Creating a list of radio buttons. We create the first one, then make others from the
      previous one, in a chain. This ensures they're all in the same 'group' of buttons.*/
    radioButton1 = gtk_radio_button_new_with_label(NULL, "Radio 1");
    radioButton2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioButton1),
                                                               "Radio 2");
    radioButton3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioButton2),
                                                               "Radio 3");
    g_signal_connect(radioButton1, "toggled", G_CALLBACK(toggled), "radio 1");
    g_signal_connect(radioButton2, "toggled", G_CALLBACK(toggled), "radio 2");
    g_signal_connect(radioButton3, "toggled", G_CALLBACK(toggled), "radio 3");
    gtk_grid_attach(GTK_GRID(grid), radioButton1, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), radioButton2, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), radioButton3, 0, 6, 1, 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioButton2), TRUE);

    /*Show all created widgets. Do this after setting all their attributes, and
    show the window last.*/
    gtk_widget_show(button);
    gtk_widget_show(box);
    gtk_widget_show(iconButton);
    gtk_widget_show(toggleButton);
    gtk_widget_show(checkButton);
    gtk_widget_show(seperator);
    gtk_widget_show(radioButton1);
    gtk_widget_show(radioButton2);
    gtk_widget_show(radioButton3);
    gtk_widget_show(grid);
    gtk_widget_show(window);

    /*Starts GTK's main loop.*/
    gtk_main();

    return 0;
}