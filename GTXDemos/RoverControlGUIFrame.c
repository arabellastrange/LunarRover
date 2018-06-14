#include <stdio.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    /*Create all widget variables first*/
    GtkWidget *window;
    GtkWidget *windowBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    /*Create the window and set it up.*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rover Mission Control");
    gtk_window_resize(GTK_WINDOW(window), 1200, 800);

    /*Add the menu bar to the window.*/
    create_menu_bar(windowBox);

    create_inner_content_alt(windowBox);

    gtk_container_add(GTK_CONTAINER(window), windowBox);

    /*Show everything!*/
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

static gboolean delete_event( GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_main_quit ();
    return FALSE;
}

static void testCallback(GtkWidget *widget, gpointer data) {
    g_print ("%s was pressed\n", (char *) data);
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

    /*Attach callback functions. Menu items emit 'activate' signals when clicked.*/
    g_signal_connect(appMenuItemExit, "activate", G_CALLBACK(delete_event), NULL);
    g_signal_connect(sensorMenuItemLoad, "activate", G_CALLBACK(testCallback), "load-sensor");
    g_signal_connect(sensorMenuItemGyro, "activate", G_CALLBACK(testCallback), "gyro-sensor");
    g_signal_connect(sensorMenuItemDistance, "activate", G_CALLBACK(testCallback), "distance-sensor");

    /*Show menu items. Menu containers don't need to be shown.*/
    gtk_widget_show(appMenuItemExit);
    gtk_widget_show(sensorMenuItemLoad);
    gtk_widget_show(sensorMenuItemGyro);
    gtk_widget_show(sensorMenuItemDistance);

    /*Create and show Menu Bar, add it to window*/
    GtkWidget *menuBar;
    menuBar = gtk_menu_bar_new();
    gtk_box_pack_start (GTK_BOX(window), menuBar, FALSE, FALSE, 2);
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

int create_inner_content(GtkWidget *window) {
    GtkWidget *outerGrid = gtk_grid_new();
    GtkWidget *cameraOuterGrid = gtk_grid_new();
    GtkWidget *statusOuterGrid = gtk_grid_new();

    GtkWidget *button1 = gtk_button_new_with_label("Button");
    GtkWidget *button2 = gtk_button_new_with_label("Button");

    gtk_grid_attach(GTK_GRID(outerGrid), cameraOuterGrid, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(outerGrid), statusOuterGrid, 0, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(cameraOuterGrid), button1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(statusOuterGrid), button2, 0, 0, 1, 1);

    gtk_box_pack_start(GTK_BOX(window), outerGrid, FALSE, FALSE, 2);

    return 0;
}

int create_inner_content_alt(GtkWidget *window) {
    /*Create and pack the outer box, and the two boxes inside it, the camera box and status box.*/
    GtkWidget *outerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *cameraOuterBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *statusOuterBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_box_pack_start(GTK_BOX(outerBox), cameraOuterBox, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(outerBox), statusOuterBox, FALSE, FALSE, 2);

    /*Create two boxes for the camera feeds, and add these to the camera outer box.*/
    GtkWidget *cameraInnerLeftBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *cameraInnerRightBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_box_pack_start(GTK_BOX(cameraOuterBox), cameraInnerLeftBox, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(cameraOuterBox), cameraInnerRightBox, TRUE, TRUE, 2);

    /*TODO: At this point, we have the two boxes for the cameras, so we can add the video feed to them, somehow.*/

    /*TODO: Change the statuses into picture icons instead of text labels.*/
    /*Create the Motor Status box, which has a label and four boxes for each motor, which further have a label and a status symbol.*/
    GtkWidget *motorStatusBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *motorStatusLabelBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *motorStatusLabel = gtk_label_new("Motor Status");
    GtkWidget *motorStatusInnerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *motor1StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *motor1Label = gtk_label_new("Motor 1");
    GtkWidget *motor1Status = gtk_label_new("OK");
    GtkWidget *motor2StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *motor2Label = gtk_label_new("Motor 2");
    GtkWidget *motor2Status = gtk_label_new("OK");
    GtkWidget *motor3StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *motor3Label = gtk_label_new("Motor 3");
    GtkWidget *motor3Status = gtk_label_new("OK");
    GtkWidget *motor4StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *motor4Label = gtk_label_new("Motor 4");
    GtkWidget *motor4Status = gtk_label_new("OK");

    /*Pack all the boxes inside each other. It's boxes all the way down.*/
    gtk_box_pack_start(GTK_BOX(statusOuterBox), motorStatusBox, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(motorStatusBox), motorStatusLabelBox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(motorStatusLabelBox), motorStatusLabel, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motorStatusBox), motorStatusInnerBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(motorStatusInnerBox), motor1StatusBox, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor1StatusBox), motor1Label, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor1StatusBox), motor1Status, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motorStatusInnerBox), motor2StatusBox, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor2StatusBox), motor2Label, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor2StatusBox), motor2Status, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motorStatusInnerBox), motor3StatusBox, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor3StatusBox), motor3Label, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor3StatusBox), motor3Status, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motorStatusInnerBox), motor4StatusBox, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor4StatusBox), motor4Label, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(motor4StatusBox), motor4Status, TRUE, TRUE, 1);

    /*Create the network status box, which has a label, and four networks. Each network has a label,
     *a status, and a button to refresh the connection.*/
    GtkWidget *networkStatusBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *networkLabelBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *networkLabel = gtk_label_new("Network Status");
    GtkWidget *networkStatusInnerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *network1StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *network1Label = gtk_label_new("WiFi");
    GtkWidget *network1Status = gtk_label_new("OK");
    GtkWidget *network1RefreshButton = gtk_button_new_with_label("R");
    GtkWidget *network2StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *network2Label = gtk_label_new("RF");
    GtkWidget *network2Status = gtk_label_new("OK");
    GtkWidget *network2RefreshButton = gtk_button_new_with_label("R");
    GtkWidget *network3StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *network3Label = gtk_label_new("Bluetooth");
    GtkWidget *network3Status = gtk_label_new("OK");
    GtkWidget *network3RefreshButton = gtk_button_new_with_label("R");
    GtkWidget *network4StatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *network4Label = gtk_label_new("Controller");
    GtkWidget *network4Status = gtk_label_new("OK");
    GtkWidget *network4RefreshButton = gtk_button_new_with_label("R");

    /*Put all the boxes inside each other.*/
    gtk_box_pack_start(GTK_BOX(statusOuterBox), networkStatusBox, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(networkStatusBox), networkLabelBox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(networkLabelBox), networkLabel, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(networkStatusBox), networkStatusInnerBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(networkStatusInnerBox), network1StatusBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(network1StatusBox), network1Label, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network1StatusBox), network1Status, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network1StatusBox), network1RefreshButton, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(networkStatusInnerBox), network2StatusBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(network2StatusBox), network2Label, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network2StatusBox), network2Status, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network2StatusBox), network2RefreshButton, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(networkStatusInnerBox), network3StatusBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(network3StatusBox), network3Label, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network3StatusBox), network3Status, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network3StatusBox), network3RefreshButton, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(networkStatusInnerBox), network4StatusBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(network4StatusBox), network4Label, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network4StatusBox), network4Status, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(network4StatusBox), network4RefreshButton, FALSE, FALSE, 1);

    /*Ensures equal spacing for the status boxes.*/
    gtk_box_set_homogeneous(GTK_BOX(network1StatusBox), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(network2StatusBox), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(network3StatusBox), TRUE);
    gtk_box_set_homogeneous(GTK_BOX(network4StatusBox), TRUE);

    /*TODO: Button adds for testing sizing.*/
    GtkWidget *button1 = gtk_button_new_with_label("Button1");
    GtkWidget *button2 = gtk_button_new_with_label("Button2");

    gtk_box_pack_start(GTK_BOX(cameraInnerLeftBox), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(cameraInnerRightBox), button2, TRUE, TRUE, 0);
    /*TODO: Button Test end*/

    /*Add the outermost box to the window.*/
    gtk_box_pack_start(GTK_BOX(window), outerBox, TRUE, TRUE, 2);

    return 0;
}