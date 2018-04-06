#include <stdio.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    /*Create all widget variables first*/
    GtkWidget *window;

    /*Create the window and set it up.*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rover Mission Control");
    gtk_window_resize(GTK_WINDOW(window), 1200, 800);

    /*Add the menu bar to the window.*/
    create_menu_bar(window);

    /*Show everything!*/
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

/**
 * Creates the initial window and sets it up. This is mostly where the window will be sized and given a title.
 * @param window the GtkWidget pointer for the created window
 * @return 0
 */
int create_window(GtkWidget *window) {

    return 0;
}

/**
 * Creates the menu bar and adds it to the window given. This sets up the whole menu, attaching any callback
 * functions needed as well.
 * @param window the GtkWidget window to add the menubar to
 * @return 0
 */
int create_menu_bar(GtkWidget *window) {
    /*Create the menu containers - these are the popup menus that appear when you click things.
     * and they hold menu items.*/
    GtkWidget *appMenu;
    GtkWidget *sensorMenu;
    appMenu = gtk_menu_new();
    sensorMenu = gtk_menu_new();

    /*Create the menu items that will go in the containers.*/
    GtkWidget *appMenuItemExit;
    GtkWidget *sensorMenuItemLoad;
    GtkWidget *sensorMenuItemGyro;
    GtkWidget *sensorMenuItemDistance;
    appMenuItemExit = gtk_menu_item_new_with_label("Quit");
    sensorMenuItemLoad = gtk_menu_item_new_with_label("Load");
    sensorMenuItemGyro = gtk_menu_item_new_with_label("Gyro");
    sensorMenuItemDistance = gtk_menu_item_new_with_label("Distance");

    /*Add them to the internal menu items to their respective menu containers*/
    gtk_menu_shell_append(GTK_MENU_SHELL(appMenu), appMenuItemExit);
    gtk_menu_shell_append(GTK_MENU_SHELL(sensorMenu), sensorMenuItemLoad);
    gtk_menu_shell_append(GTK_MENU_SHELL(sensorMenu), sensorMenuItemGyro);
    gtk_menu_shell_append(GTK_MENU_SHELL(sensorMenu), sensorMenuItemDistance);

    /*Attach callback functions, if there are any*/


    /*Show menu items. Menu containers don't need to be shown.*/
    gtk_widget_show(appMenuItemExit);
    gtk_widget_show(sensorMenuItemLoad);
    gtk_widget_show(sensorMenuItemGyro);
    gtk_widget_show(sensorMenuItemDistance);

    /*Create and show Menu Bar, add it to window*/
    GtkWidget *menuBar;
    menuBar = gtk_menu_bar_new();
    gtk_container_add(GTK_CONTAINER(window), menuBar);
    gtk_widget_show(menuBar);

    /*Create menu items for menu bar entries and show them - these will be the one that show on top, and
     * when clicked open their respective menu containers, containing the rest of the menu items.*/
    GtkWidget *appItem;
    GtkWidget *sensorItem;
    appItem = gtk_menu_item_new_with_label("App");
    sensorItem = gtk_menu_item_new_with_label("Sensors");
    gtk_widget_show(appItem);
    gtk_widget_show(sensorItem);

    /*Associate the menu containers to menu items*/
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(appItem), appMenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(sensorItem), sensorMenu);

    /*Add Menu items to menu bar*/
    gtk_container_add(GTK_CONTAINER(menuBar), appItem);
    gtk_container_add(GTK_CONTAINER(menuBar), sensorItem);

    return 0;
}