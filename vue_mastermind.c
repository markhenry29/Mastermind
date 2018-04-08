/** vue_mastermind.c

Par LE Richard, en quête d'aventure...

*/

#include "vue_mastermind.h"

/**
	Initialise une fenêtre gtk.
	La positionne au milieu de la fenêtre et lui donne comme nom "Le jeu du MasterMind".
	Lui modifie aussi sa taille. (en pixels)
    @return la fenetre Initialisé
 */
void initialiser_window(vue_master_t* m)
{
	m->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(m->window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_title(GTK_WINDOW(m->window), "Le jeu du Mastermind");
	gtk_window_set_default_size(GTK_WINDOW(m->window), 800, 685);
}

void initialiser_hbox(vue_master_t* m)
{
	m->hbox = gtk_hbox_new(TRUE, 10);
}

void initialiser_vbox(vue_master_t* m)
{
	m->vbox = gtk_vbox_new(FALSE, 15);
	m->vbox2 = gtk_vbox_new(FALSE, 0);
}

void initialiser_dialog_box(vue_master_t* m)
{
    m->dialogBoxWin = gtk_dialog_new_with_buttons("Le Jeu du Mastermind",
                                                  GTK_WINDOW(m->window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_STOCK_OK,
                                                  GTK_RESPONSE_OK,
                                                  NULL);
}

/**
	Initialise le tableau du struct m passé en entré par des boutons.
	Désactive tout les boutons sur la dernière colonne et la dernière ligne.
	@param *m un pointeur sur un struct
 */
void initialiser_tabBouton(vue_master_t* m)
{
	int i;

	for(i = 0; i < NB_BOUTONS; i++)
		m->tabBouton[i] = gtk_button_new();

	for(i = 4; i < NB_BOUTONS; i+=5)
    {
		gtk_widget_set_sensitive(m->tabBouton[i], FALSE);
    }

    for(i = 60; i < NB_BOUTONS; i++)
    {
        gtk_widget_set_sensitive(m->tabBouton[i], FALSE);
        gtk_button_set_label(GTK_BUTTON(m->tabBouton[i]), "?");
    }

	gtk_button_set_label(GTK_BUTTON(m->tabBouton[64]), "Le Code Secret");
}

/**
	Initialise la table gtk 12 lignes et 5 colonnes.
	Attache tout les boutons à la table qui est dans notre struct passé en entré.
    Modifie aussi l'espace entre les lignes et la dernière colonne pour mieux les distinguer.
	@param *m un pointeur sur une structure
 */
void initialiser_table(vue_master_t* m)
{
	int i;
	int j;

	m->table = gtk_table_new(NB_LIGNE, NB_COLONNE, TRUE);
    gtk_table_set_col_spacing(GTK_TABLE(m->table), 3, 15);
    for(i = 0; i < NB_LIGNE; i++)
    {
        gtk_table_set_row_spacing(GTK_TABLE(m->table), i, 10);
        for(j = 0; j < NB_COLONNE; j++)
        {
            gtk_table_attach_defaults(GTK_TABLE(m->table), m->tabBouton[i*NB_COLONNE + j], j, j + 1, i, i + 1);
        }
    }
}

void initialiser_confirm_rejouer(vue_master_t* m)
{
    m->confirm = gtk_toggle_button_new_with_label("CONFIRMER");
    m->rejouer = gtk_toggle_button_new_with_label("REJOUER");

    gtk_widget_set_sensitive(m->confirm, FALSE);
    gtk_widget_set_sensitive(m->rejouer, FALSE);
}


void initialiser_menu(vue_master_t* m)
{
    /* initialisation de la bar de menu */
    m->menuBar = gtk_menu_bar_new();
    m->menu = gtk_menu_new();
    m->menu2 = gtk_menu_new();

    /* on initialise et on colle nos items sur le menu */

    /* MODE 1 */
    m->menuItem = gtk_menu_item_new_with_label(" Mode 1 (joueur) ");
    gtk_menu_shell_append(GTK_MENU_SHELL(m->menu), m->menuItem);
    /* si on click sur (mode 1) on lance replay_joueur*/
    g_signal_connect(G_OBJECT(m->menuItem), "activate", G_CALLBACK(replay_joueur), m);

    /* MODE 2 */
    m->menuItem = gtk_menu_item_new_with_label(" Mode 2 (ordinateur) ");
    gtk_menu_shell_append(GTK_MENU_SHELL(m->menu), m->menuItem);
    /* si on click sur (mode 2) on lance vue_mastermind_ordi */
    g_signal_connect(G_OBJECT(m->menuItem), "activate", G_CALLBACK(vue_mastermind_ordinateur), m);

    /* QUIT */
    m->menuItem = gtk_menu_item_new_with_label(" Quitter ");
    gtk_menu_shell_append(GTK_MENU_SHELL(m->menu), m->menuItem);
    /* Si on click sur quitter dans le menu, on appelle la fonction quitter_partie */
    g_signal_connect(G_OBJECT(m->menuItem), "activate", G_CALLBACK(quitter_partie), m);

    m->menuItem = gtk_menu_item_new_with_label("Nouvelle Partie ");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(m->menuItem), m->menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(m->menuBar), m->menuItem);


    m->menuItem = gtk_menu_item_new_with_label("Abandonner ");
    gtk_menu_shell_append(GTK_MENU_SHELL(m->menu2), m->menuItem);
    g_signal_connect(G_OBJECT(m->menuItem), "activate", G_CALLBACK(abandonner), m);


    m->menuItem = gtk_menu_item_new_with_label("Jeu ");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(m->menuItem), m->menu2);
    gtk_menu_shell_append(GTK_MENU_SHELL(m->menuBar), m->menuItem);
}
/**
    Initialise l'ensemble des widgets GTK et introduit tout ces éléments dans la vue graphique.
    Elle appelle donc toute les fonctions d'initialisations écrites auparavant.
    @param *m un pointeur sur un struct
*/
void initialiser_ensemble(vue_master_t* m)
{
    initialiser_window(m);
    initialiser_tabBouton(m);
    initialiser_hbox(m);
    initialiser_vbox(m);
    initialiser_dialog_box(m);
    initialiser_table(m);
    initialiser_confirm_rejouer(m);
    initialiser_menu(m);

    /* on va coller les éléments dans la fenêtre */
    gtk_box_pack_end(GTK_BOX(m->vbox2), m->vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(m->vbox2), m->menuBar, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(m->vbox), m->table, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(m->vbox), m->hbox, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(m->hbox), m->rejouer, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(m->hbox), m->confirm, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(m->window), m->vbox2);

    /* on commence par le rouge quand on click sur un bouton */
    m->couleur = COULEUR_ROUGE;
    /* et on commence par le mode de jeu du joueur */
    m->mode = MODE_JOUEUR;
}

/**
    initialise le modèle du jeu de mastermind.
    @param *m un pointeur sur un struct
*/
void initialiser_modele(vue_master_t* m)
{
    srand(time(NULL));
    mastermind_initialiser_avec_secret(&m->mastermind);
}


/**
	Permet la vue du jeu MasterMind.
	Initialise l'ensemble des Widgets, fenêtre, boutons, images etc...
	Affiche l'ensemble de ces Widgets dans la fenêtre.
	Si on click sur un des boutons, on appelle les fonctions callback déclarées et définies au préalable.
	@param *m un pointeur sur une structure
 */
void vue_mastermind(vue_master_t* m)
{
    int i;

    initialiser_ensemble(m);
    initialiser_modele(m);

    /* dès qu'on click sur un bouton, on le modifie et on active confirmer si besoin. */
    for(i = 0; i < NB_BOUTONS; i++)
    {
        g_signal_connect(G_OBJECT(m->tabBouton[i]), "clicked", G_CALLBACK(modifier_bouton), m);
        g_signal_connect(G_OBJECT(m->tabBouton[i]), "clicked", G_CALLBACK(activer_confirmer_if), m);
    }

    /* si on click sur rejouer, confirmer, ou si on quitte. */
    g_signal_connect(G_OBJECT(m->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(m->confirm), "clicked", G_CALLBACK(confirmer), m);
    g_signal_connect(G_OBJECT(m->rejouer), "clicked", G_CALLBACK(replay_joueur), m);
}

/**
	Modifie la couleur et le label du bouton selon la valeur du type enuméré Couleurs.
	On distingue 8 cas, se sont les 8 couleurs.
	Dès lors qu'on click sur un bouton, un label et une nouvelle image est chargé puis affiché.
	@param b un bouton
	@param *m un pointeur de struct
 */
void modifier_bouton(GtkWidget* b, vue_master_t* m)
{
    int i;
    int j;
    int tmp;
    int decal = 0;
    int cle;
    GtkWidget* image = NULL;

    for(i = 0; i < NB_BOUTONS; i++)
    {
        if(m->tabBouton[i] == b)
        {
            /* il y a decalage puisque il y a des boutons inactifs. On le calcule ici.*/
            for(j = 1; j < NB_LIGNE; j++)
            {
                tmp = i - j*NB_COLONNE;
                if(tmp >= 0)
                    decal++;

                else
                    break;
            }
            /* la cle est la case ou l'on veut stocker l'information (modèle). Donc pareil on calcule. */
            cle = ((i - 1*decal) % 4) + 1;
            switch(m->couleur)
            {
                case COULEUR_INDETERMINEE:
                    m->couleur = COULEUR_ROUGE;
                break;
                case COULEUR_ROUGE:
                    image = gtk_image_new_from_file("rouge.png");
                    gtk_button_set_label(GTK_BUTTON(b), "Rouge ");
                    gtk_button_set_image(GTK_BUTTON(b), image);
                    mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_ROUGE);
                    m->couleur = COULEUR_VERT;
                break;

                case COULEUR_VERT:
                    STOCKER_IMAGE("vert.png");
                    SET_LABEL("Vert ");
                    SET_IMAGE;
                    mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_VERT);
                    m->couleur = COULEUR_BLEU;
                break;

                case COULEUR_BLEU:
                    STOCKER_IMAGE("bleu.png");
                    SET_LABEL("Bleu ");
                    SET_IMAGE;
                    mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_BLEU);
                    m->couleur = COULEUR_MAUVE;
                break;

                case COULEUR_MAUVE:
                    STOCKER_IMAGE("violet.png");
                    SET_LABEL("Mauve ");
                    SET_IMAGE;
                    mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_MAUVE);
                    m->couleur = COULEUR_ORANGE;
                break;

                case COULEUR_ORANGE:
                    STOCKER_IMAGE("orange.png");
                    SET_LABEL("Orange ");
                    SET_IMAGE;
                    mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_ORANGE);
                    m->couleur = COULEUR_JAUNE;
                break;

                case COULEUR_JAUNE:
                    STOCKER_IMAGE("jaune.png");
                    SET_LABEL("Jaune ");
                    SET_IMAGE;
                        mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_JAUNE);
                    m->couleur = COULEUR_BLANC;
                break;

                case COULEUR_BLANC:
                    STOCKER_IMAGE("blanc.png");
                    SET_LABEL("Blanc ");
                    SET_IMAGE;
                    mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_BLANC);
                    m->couleur = COULEUR_NOIR;
                break;
                case COULEUR_NOIR:
                    STOCKER_IMAGE("noir.png");
                    SET_LABEL("Noir ");
                    SET_IMAGE;
                    mastermind_set_essai_encours(&m->mastermind, cle, COULEUR_NOIR);
                    m->couleur = COULEUR_ROUGE;
                break;
            }
        }
    }
}

/**
    Appuyer sur confirmer implique beaucoup de chose:
    1) on déclare des chaines de caractères pour stocker l'information.
    2) on regarde le nombre de couleurs placées et si l'éssai est valide.
    3) selon les couleurs choisi par l'utilisateur, on affiche les chaines de caractères spécifiques.
    4) on desactive confirmer.
    5) on affiche la combinaison gagnante si le joueur perd ou gagne.
    @param b un bouton
    @param *m un pointeur de struct
*/
void confirmer(GtkWidget* b, vue_master_t* m)
{
    int dernier_essai;
    int etat_partie;
    gchar chaine1[50];
    gchar chaine2[50];
    gchar info[100];
    if(mastermind_est_essai_encours_valide(&m->mastermind) == 1 && m->mode == MODE_JOUEUR)
    {
        mastermind_valider_essai_encours(&m->mastermind);

        dernier_essai = mastermind_get_num_dernier_essai(&m->mastermind);
        etat_partie = mastermind_get_etat(&m->mastermind);

        /* Selon le nombre de couleur correctes, on stock la chaine de caractère */
        sprintf(chaine1, " %d couleur(s) correcte(s) \n", mastermind_get_nb_couleurs_correctes(&m->mastermind, dernier_essai));
        /* idem sauf qu'il s'agit du placement des couleurs */
        sprintf(chaine2, " dont %d bien placee(s) ", mastermind_get_nb_couleurs_placees(&m->mastermind, dernier_essai));

        /* on concatène les informations recueullis */
        g_stpcpy(info, g_strconcat(g_strconcat(chaine1, chaine2, NULL), NULL));

        /* on change le label du bouton correspondant */
        gtk_button_set_label(GTK_BUTTON(m->tabBouton[4*dernier_essai + 1*(dernier_essai - 1)]), info);
        /* on desactive confirmer */
        gtk_widget_set_sensitive(m->confirm, FALSE);

        if(etat_partie == ETAT_MM_GAGNE || etat_partie == ETAT_MM_PERDU)
        {
            afficher_combi_gagnant(m);
            desactiver_tab_bouton(m, NB_BOUTONS);
            gtk_widget_set_sensitive(m->rejouer, TRUE);
            afficher_fin(b, m);
        }
    }

    /*else
    {
        mastermind_valider_secret(&m->mastermind);
        if(mastermind_est_secret_valide(&m->mastermind))
        {

        }
    }*/
}

/**
    Active ou desactive le bouton confirmer si le joueur a bien joué les 4 couleurs d'une ligne.
    Déclare une variable temporaire qui est incrémenté à chaque fois qu'on compte une image.
    @param b un bouton
    @param *m un pointeur sur un struct
 */
void activer_confirmer_if(GtkWidget* b, vue_master_t *m)
{
/*
	#if(DEBUG == 1)
		printf("%s\n", __func__);
	#endif
*/
    int i = 0;
    int compteurTemp = 0;
    int essai_encours = mastermind_get_num_essai_encours(&m->mastermind);
    GtkWidget* imageTemp;


    /* on compte le nombre de couleurs saisies sur la ligne en question. */
    for(i = (essai_encours - 1)*NB_COLONNE; i < NB_COLONNE*essai_encours - 1; i++)
    {
        imageTemp = gtk_button_get_image(GTK_BUTTON(m->tabBouton[i]));
        if(imageTemp != NULL)
            compteurTemp++;
    }

    /* on active le bouton confirmer */
    if(compteurTemp == 4)
        gtk_widget_set_sensitive(m->confirm, TRUE);
/*
	#if(DEBUG == 1)
	printf("%s sortie\n", __func__);
	#endif
*/
}

/**
    Afficher la combinaison gagnante qui se situe sur la dernière ligne du tableau de boutons.
    @param *m un pointeur de struct
*/
void afficher_combi_gagnant(vue_master_t* m)
{
    int i;
    couleur c;
    for(i = 1; i < 5; i++)
    {
        c = mastermind_get_secret(&m->mastermind, i);
        m->couleur = c;
        modifier_bouton(m->tabBouton[59 + i], m);
    }
}

/**
    Permet au joueur de rejouer en cliquant sur le bouton rejouer.
    D'abord on remet tout à zero, on reset l'affichage des boutons.
    On réinitialise le modèle et on désactive confirmer.
    Le jeu peut se relancer tranquillement.
    @param b un bouton
    @param *m un pointeur de struct
*/
void replay_joueur(GtkWidget* b, vue_master_t* m)
{
    refresh(m);

    /* on réinitialise le modele */
    initialiser_modele(m);
    initialiser_dialog_box(m);

    gtk_widget_set_sensitive(m->confirm, FALSE);
}


/**
    Affiche une boite de dialogue à la fin du jeu lorsque le joueur perd ou gagne.
    @param b un bouton
    @param *m un pointeur de struct vue_master_t
 */
void afficher_fin(GtkWidget* b, vue_master_t* m)
{
    gchar chaine[200];
    GtkWidget* label;

    sprintf(chaine, "Vous avez réussi à trouver le code secret en %d essais !\n", mastermind_get_num_dernier_essai(&m->mastermind));

    if(mastermind_get_etat(&m->mastermind) == ETAT_MM_PERDU)
        g_stpcpy(chaine, "Vous avez perdu ! Vous aurez plus de chance la prochaine fois !");


    label = gtk_label_new(chaine);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(m->dialogBoxWin)->vbox), label, TRUE, FALSE, 0);

    /* on affiche tout ce qu'il y a dedans */
    gtk_widget_show_all(m->dialogBoxWin);
    /* on lance la boite */
    gtk_dialog_run(GTK_DIALOG(m->dialogBoxWin));
    /* on détruit la boite de dialogue */
    gtk_widget_destroy(m->dialogBoxWin);
}

void desactiver_tab_bouton(vue_master_t* m, int n)
{
    int i;
    for(i = 0; i < n; i++)
        gtk_widget_set_sensitive(m->tabBouton[i], FALSE);
}

/**
    Ouvre une boite de dialog lorsque qu'on click sur quitter dans le menu.
    Clicker sur "yes" pour quitter et "no" sinon
    @param *menu un pointeur sur un menu
    @param *m un pointeur de struct vue_master_t
 */
void quitter_partie(GtkWidget* menu, vue_master_t* m)
{
    GtkWidget* question;

    /* initialisation de la boite de dialogue */
    question = gtk_message_dialog_new(GTK_WINDOW(m->window),
                                      GTK_DIALOG_MODAL,
                                      GTK_MESSAGE_QUESTION,
                                      GTK_BUTTONS_YES_NO,
                                      "Voulez vous vraiment \n"
                                      "quitter le programme ? " );

    /* Selon les choix de l'utilisateur, faire... */
    switch(gtk_dialog_run(GTK_DIALOG(question)))
    {
        case GTK_RESPONSE_YES:
            gtk_main_quit();
        break;
        case GTK_RESPONSE_NONE:
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(question);
        break;
    }
}

/**
    Si vous êtes faible, il y a toujours une option pour vous.
    @param *menu un pointeur sur un menu
    @param *m un pointeur de struct vue_master_t
 */
void abandonner(GtkWidget* menu, vue_master_t* m)
{
    desactiver_tab_bouton(m, NB_BOUTONS);
    afficher_combi_gagnant(m);
}

/**
    Reset l'ensemble des boutons et widgets comme au départ.
    @param *m un pointeur vue_master_t
 */
void refresh(vue_master_t* m)
{
    int i;
    /* on configure nos boutons comme à l'initialisation */
    for(i = 0; i < NB_BOUTONS - 1; i++)
    {
        gtk_button_set_image(GTK_BUTTON(m->tabBouton[i]), NULL);
        gtk_button_set_label(GTK_BUTTON(m->tabBouton[i]), "");
        if(i < 60)
            gtk_widget_set_sensitive(m->tabBouton[i], TRUE);
    }

    for(i = 4; i < NB_BOUTONS; i+= 5)
        gtk_widget_set_sensitive(m->tabBouton[i], FALSE);

    for(i = 60; i < NB_BOUTONS - 1; i++)
        gtk_button_set_label(GTK_BUTTON(m->tabBouton[i]), "?");
}

/**
    Permet de jouer au deuxième mode de jeu.
    La fonction marche pas :( dommage
    @param *menu un pointeur sur un GtkWidget
    @param *m un pointeur
 */
void vue_mastermind_ordinateur(GtkWidget* menu, vue_master_t* m)
{
    int i;
    refresh(m);
    desactiver_tab_bouton(m, 60);
    /* on active les boutons du code secret pour pouvoir la modifier */
    for(i = 60; i < NB_BOUTONS - 1; i++)
        gtk_widget_set_sensitive(m->tabBouton[i], TRUE);

    /* on active confirmer */
    gtk_widget_set_sensitive(m->confirm, TRUE);
    m->mode = MODE_ORDINATEUR;

    /*mastermind_initialiser(&m->mastermind);*/
}
