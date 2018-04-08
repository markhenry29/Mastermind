/** vue_mastermind.h

Par LE Richard, le seul et l'unique.

*/

#ifndef __VUE_MASTERMIND_H__
#define __VUE_MASTERMIND_H__

#include "mastermind.h"
#include "stat-essai.h"
#include "combinaison.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gtk/gtk.h>

#define NB_COLONNE (TAILLE_COMBI + 1)
#define NB_LIGNE (NB_ESSAIS + 1)
#define NB_BOUTONS NB_COLONNE*NB_LIGNE

#define STOCKER_IMAGE(nom_du_fichier) image = gtk_image_new_from_file(nom_du_fichier);
#define SET_LABEL(label) gtk_button_set_label(GTK_BUTTON(b), label);
#define SET_IMAGE gtk_button_set_image(GTK_BUTTON(b), image);

#define MODE_JOUEUR 1
#define MODE_ORDINATEUR 2

struct vue_mastermind_s{
	GtkWidget* window;
	GtkWidget* hbox;
	GtkWidget* vbox;
	GtkWidget* tabBouton[NB_BOUTONS];
	GtkWidget* table;
	GtkWidget* confirm;
	GtkWidget* rejouer;
	GtkWidget* dialogBoxWin;

	GtkWidget* vbox2;
	GtkWidget* menuItem;
	GtkWidget* menuBar;
	GtkWidget* menu;
    GtkWidget* menu2;

	couleur couleur;
	int mode;

    mastermind mastermind;
};

typedef struct vue_mastermind_s vue_master_t;

void initialiser_window(vue_master_t* m);
void initialiser_hbox(vue_master_t* m);
void initialiser_vbox(vue_master_t* m);
void initialiser_dialog_box(vue_master_t* m);
void initialiser_tabBouton(vue_master_t* m);
void initialiser_table(vue_master_t* m);
void initialiser_confirm_rejouer(vue_master_t* m);
void initialiser_menu(vue_master_t* m);
void initialiser_ensemble(vue_master_t* m);
void initialiser_modele(vue_master_t* m);



void modifier_bouton(GtkWidget* b, vue_master_t* m);
void confirmer(GtkWidget* b, vue_master_t* m);
void activer_confirmer_if(GtkWidget* b, vue_master_t *m);
void afficher_combi_gagnant(vue_master_t* m);
void vue_mastermind(vue_master_t* m);
void replay_joueur(GtkWidget* b, vue_master_t* m);
void afficher_fin(GtkWidget* b, vue_master_t* m);
void desactiver_tab_bouton(vue_master_t* m, int n);
void quitter_partie(GtkWidget* menu, vue_master_t* m);
void abandonner(GtkWidget* menu, vue_master_t* m);
void refresh(vue_master_t* m);
void vue_mastermind_ordinateur(GtkWidget* menu, vue_master_t* m);


#endif
