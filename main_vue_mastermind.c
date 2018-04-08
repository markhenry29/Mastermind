/** main_vue_mastermind.c

Par LE Richard, la toute pouissance

*/
#include "vue_mastermind.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    vue_master_t master;

    gtk_init(NULL, NULL);
    vue_mastermind(&master);
    GtkSettings* default_settings = gtk_settings_get_default();
	g_object_set(default_settings, "gtk-button-images", TRUE, NULL);

    gtk_widget_show_all(master.window);
    gtk_main();
    return EXIT_SUCCESS;
}


