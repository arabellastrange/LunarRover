#include <stdio.h>
#include <gtk/gtk.h>

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_main_quit ();
    return FALSE;
}

static void testCallback(GtkWidget *widget, gpointer data) {
    g_print ("%s was pressed\n", (char *) data);
}

int main(int argc, char *argv[]) {

    gtk_init (&argc, &argv);

    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*Create the menu containers - these are the popup menus that appear when you click things.
     * and they hold menu items.*/
    GtkWidget *fileMenu;
    GtkWidget *editMenu;
    GtkWidget *viewMenu;
    fileMenu = gtk_menu_new();
    editMenu = gtk_menu_new();
    viewMenu = gtk_menu_new();

    /*Create the menu items that will go in the containers.*/
    GtkWidget *fileMenuItem1;
    GtkWidget *editMenuItem1;
    GtkWidget *viewMenuItem1;
    fileMenuItem1 = gtk_menu_item_new_with_label("Save");
    editMenuItem1 = gtk_menu_item_new_with_label("Undo");
    viewMenuItem1 = gtk_menu_item_new_with_label("Show Grid");

    /*Add them to the internal menu items to their respective menu containers*/
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), fileMenuItem1);
    gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), editMenuItem1);
    gtk_menu_shell_append(GTK_MENU_SHELL(viewMenu), viewMenuItem1);

    /*Attach callback functions, if there are any*/

    /*Show menu items. Menu containers don't need to be shown.*/
    gtk_widget_show(fileMenuItem1);
    gtk_widget_show(editMenuItem1);
    gtk_widget_show(viewMenuItem1);

    /*Create and show Menu Bar, add it to window*/
    GtkWidget *menuBar;
    menuBar = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window), menuBar);
    gtk_widget_show(menuBar);

    /*Create menu items for menu bar entries and show them - these will be the one that show on top, and
     * when clicked open their respective menu containers, containing the rest of the menu items.*/
    GtkWidget *fileItem;
    GtkWidget *editItem;
    GtkWidget *viewItem;
    fileItem = gtk_menu_item_new_with_label("File");
    editItem = gtk_menu_item_new_with_label("Edit");
    viewItem = gtk_menu_item_new_with_label("View");
    gtk_widget_show(fileItem);
    gtk_widget_show(editItem);
    gtk_widget_show(viewItem);

    /*Associate the menu containers to menu items*/
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileItem), fileMenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(editItem), editMenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(viewItem), viewMenu);

    /*Add Menu items to menu bar*/
    gtk_container_add(GTK_CONTAINER(menuBar), fileItem);
    gtk_container_add(GTK_CONTAINER(menuBar), editItem);
    gtk_container_add(GTK_CONTAINER(menuBar), viewItem);

    /*All done! Show the window.*/
    gtk_widget_show(window);

    gtk_main();
    return 0;
}