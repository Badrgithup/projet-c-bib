#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 1000
typedef struct
{
    void *contents[MAX_QUEUE_SIZE];
    unsigned front, rear;
} queue;
unsigned queue_size(queue *q)
{
    return (MAX_QUEUE_SIZE + q -> rear - q -> front) % MAX_QUEUE_SIZE;
}

queue *queue_new(void)
{
    queue *q;
    q = malloc(sizeof(queue));
    if (!q)
        return NULL;
    q -> front = 0;
    q -> rear = 0;
    return q;
}

int queue_send(queue *q, void *p)
{
    if (queue_size(q) >= MAX_QUEUE_SIZE - 1)
        return -1;
    q -> contents[q -> rear] = p;
    q -> rear = (q -> rear + 1) % MAX_QUEUE_SIZE;
    return 0;
}

void *queue_receive(queue *q)
{
    void *p;
    if (q -> front == q -> rear)
        return NULL;
    p = q -> contents[q -> front];
    q -> front = (q -> front + 1) % MAX_QUEUE_SIZE;
    return p;
}

struct date {
    int year;
    int month;
    int day;
};

struct livre {
    int id;
    char titre[50];
    char auteur[50];
    int etat;
    struct date pub_date;
};

struct Client {
    int id;
    char nom[100];
    char prenom[100];
    char email[100];
    char telephone[20];
    char adresse[200];
};

int ajout() {
    FILE *bib_txt;
    struct livre li;
    bib_txt = fopen("bib.txt", "a");
    if (bib_txt == NULL) {
        return -1;
    }
    li.etat = 1;
    printf("Donner les donnees du livre :\n");
    printf("SVP separez entre les mots par '_' :\n");
    printf("ID : ");
    scanf("%d", &li.id);
    printf("Titre : ");
    scanf("%s", li.titre);
    printf("Auteur : ");
    scanf("%s", li.auteur);
    printf("Donner la date de publication sous la forme jj mm aaaa : ");
    scanf("%d %d %d", &li.pub_date.day, &li.pub_date.month, &li.pub_date.year);
    fprintf(bib_txt, "ID: %d, Titre: %s, Auteur: %s, Date: %02d-%02d-%04d , etat: %d\n",
            li.id, li.titre, li.auteur,
            li.pub_date.day, li.pub_date.month, li.pub_date.year, li.etat);
    fclose(bib_txt);
    printf("Livre ajoute avec succes !\n");
    return 0;
}

int afficher() {
    FILE *bib_txt;
    int i = 1;
    char li[1024];
    if ((bib_txt = fopen("bib.txt", "rt")) != NULL) {
        while (fgets(li, sizeof(li), bib_txt) != NULL) {
            printf("Livre num %i: %s", i, li);
            i++;
        }
        fclose(bib_txt);
    } else {
        return -1;
    }
    return 0;
}


char* chercher(char nom_a_chercher[50]) {
    static char result[1024];
    FILE *bib_txt;
    char li[1024];


    bib_txt = fopen("bib.txt", "rt");
    if (bib_txt == NULL) {
        return NULL;
    }


    while (fgets(li, sizeof(li), bib_txt) != NULL) {

        char *start = strstr(li, "Titre: ");
        if (start != NULL) {
            start += 7;
            char name[50];
            int i = 0;


            while (start[i] != '\0' && start[i] != ',') {
                name[i] = start[i];
                i++;
            }
            name[i] = '\0';


            if (strncmp(name, nom_a_chercher, 50) == 0) {
                strcpy(result, li);
                fclose(bib_txt);
                return result;
            }
        }
    }

    fclose(bib_txt);
    return NULL;
}

char* chercherclient(char id_a_chercher[50]) {
    static char result[1024];
    FILE *client_txt;
    char li[1024];


    client_txt = fopen("client.txt", "rt");
    if (client_txt == NULL) {
        return NULL;
    }


    while (fgets(li, sizeof(li), client_txt) != NULL) {

        char *start = strstr(li, "ID: ");
        if (start != NULL) {
            start += 4;
            char id[50];
            int i = 0;


            while (start[i] != '\0' && start[i] != ',') {
                id[i] = start[i];
                i++;
            }
            id[i] = '\0';


            if (strncmp(id, id_a_chercher, 50) == 0) {
                strcpy(result, li);
                fclose(client_txt);
                return result;
            }
        }
    }

    fclose(client_txt);
    return NULL;
}

int supprimer(char nom_a_supprimer[50]) {
    FILE *bib_txt = fopen("bib.txt", "rt");
    FILE *tt_txt = fopen("tt.txt", "wt");
    char li[1024];
    int supprime = 0;

    if (bib_txt && tt_txt) {
        while (fgets(li, sizeof(li), bib_txt)) {
            char *start = strstr(li, "Titre: ");
            if (start) {
                start += 7;
                if (strncmp(start, nom_a_supprimer, strlen(nom_a_supprimer)) == 0 && start[strlen(nom_a_supprimer)] == ',') {
                    supprime = 1;
                    continue;
                }
            }
            fprintf(tt_txt, "%s", li);
        }
        fclose(bib_txt);
        fclose(tt_txt);
        remove("bib.txt");
        rename("tt.txt", "bib.txt");
    } else {
        return -1;
    }

    if(supprime) printf("Le livre a ete supprime avec succes!!\n") ;
        else printf("Le livre n'existe pas!!\n");
    return 0;
}

int afficher_cl() {
    FILE *client_txt;
    int i = 1;
    char li[1024];
    if ((client_txt = fopen("client.txt", "rt")) != NULL) {
        while (fgets(li, sizeof(li), client_txt) != NULL) {
            printf("client num %i: %s", i, li);
            i++;
        }
        fclose(client_txt);
    } else {
        return -1;
    }
    return 0;
}

int ajout_client() {
    FILE *client_txt;
    struct Client cl;
    client_txt = fopen("client.txt", "a");
    if (client_txt == NULL) {
        return -1;
    }
    printf("Donner les donnees du nouveau client :\n");
    printf("ID : ");
    scanf("%d", &cl.id);
    printf("Nom : ");
    scanf("%s", cl.nom);
    printf("prenom : ");
    scanf("%s", cl.prenom);
    printf("email : ");
    scanf("%s", cl.email);
    printf("numero de telephone : ");
    scanf("%s", cl.telephone);
    printf("adresse : ");
    scanf("%s", cl.adresse);
    fprintf(client_txt, "ID: %d, nom: %s, prenom: %s, email: %s, num telephone: %s, adresse: %s\n",
            cl.id, cl.nom, cl.prenom, cl.email, cl.telephone, cl.adresse);
    fclose(client_txt);
    printf("Client ajoute avec succes !\n");
    return 0;
}

void mettre_a_jour_etat_livre(char titre[50], int nouvel_etat) {
    FILE *bib_txt = fopen("bib.txt", "rt");
    FILE *temp_txt = fopen("temp.txt", "wt");
    char li[1024];

    while (fgets(li, sizeof(li), bib_txt)!=NULL) {
        char *start = strstr(li, "Titre: ");
        if (start) {
            start += 7;
            if (strncmp(start, titre, strlen(titre)) == 0 && start[strlen(titre)] == ',') {
                char *etat_pos = strstr(li, "etat: ");
                if (etat_pos) sprintf(etat_pos, "etat: %d\n", nouvel_etat);
            }
        }
        fprintf(temp_txt, "%s", li);
    }

    fclose(bib_txt);
    fclose(temp_txt);
    remove("bib.txt");
    rename("temp.txt", "bib.txt");
}

void emprunt_livre(queue *livres, queue *clients, char titre[50], char id[50]) {
    char *livre_ligne = chercher(titre);
    char *client_ligne=chercherclient(id);
    if (!livre_ligne) {
        printf("Livre non trouve.\n");
        return;
    }
    if (!client_ligne){
        printf("client non trouve");
        return;
    }

    if (strstr(livre_ligne, "etat: 0")) {
        printf("Le livre est deja emprunte.\n");
        return;
    }

    mettre_a_jour_etat_livre(titre, 0);

    char *titre_copy = malloc(strlen(titre) + 1);
    if (!titre_copy) return;
    strcpy(titre_copy, titre);

    char *client_copy = malloc(strlen(id) + 1);
    if (!client_copy) return;
    strcpy(client_copy, id);

    queue_send(livres, titre_copy);
    queue_send(clients, client_copy);
    printf("Livre emprunte avec succes !\n");
}

void rendre_livre(queue *livres, queue *clients) {
    if ((MAX_QUEUE_SIZE + livres->rear - livres->front) % MAX_QUEUE_SIZE == 0) {
        printf("Aucun livre en cours d'emprunt.\n");
        return;
    }

    char *titre = (char *)queue_receive(livres);
    char *idclient = (char *)queue_receive(clients);
    mettre_a_jour_etat_livre(titre, 1);
    printf("Livre %s rendu avec succes par le client d'ID %s \n",titre,idclient);
    free(titre);
}


int main() {
    queue *emprunt_livres=queue_new();;
    queue *emprunt_clients=queue_new();;

    int test = 1;
    printf("\n                         ******  BIBLIOTHEQUE ENSI  ********\n\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("                    ** Bienvenue dans notre bibliotheque **\n");
    printf("-------------------------------------------------------------------------------------\n");
    while (test) {
        printf("--------- Choisir une option ----------\n");
        printf("1) Ajouter un livre\n");
        printf("2) Afficher les livres\n");
        printf("3) Chercher un livre\n");
        printf("4) Supprimer un livre\n");
        printf("5) Ajouter client\n");
        printf("6) Afficher les clients\n");
        printf("7) Emprunter un livre\n");
        printf("8) rendre le livre emprunte\n");
        printf("9) Quitter\n");
        int choix;
        printf("Votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                ajout();
                break;
            case 2:
                afficher();
                break;
            case 3: {
                char nom[50];
                printf("ecrire le nom du livre que vous cherchez : \n");
                scanf("%s", nom);
                char *result = chercher(nom);
                if (result == NULL) {
                    printf("Le livre n'existe pas !!\n");
                } else {
                    printf("Livre cherche : %s\n", result);
                }
                break;
            }
            case 4: {
                char nom[50];
                printf("donner le titre du livre a supprimer : \n");
                scanf("%s", nom);
                supprimer(nom);
                break;
            }
            case 5:
                ajout_client();
                break;
            case 6:
                afficher_cl();
                break;
            case 7: {
                char titre[50];
                char ID[50];
                printf("donner le titre du livre a emprunter : \n");
                scanf("%s", titre);
                printf("donner l'ID du client : \n");
                scanf("%s", ID);

                emprunt_livre(emprunt_livres, emprunt_clients,titre, ID);
                break;
            }
            case 8: {

                rendre_livre(emprunt_livres, emprunt_clients);
                break;
            }
            case 9:
                test = 0;
                printf("Merci d'avoir explore notre bibliotheque\n");
                printf("            Au revoir !\n");
                break;
            default:
                printf("Option invalide, essayez encore.\n");
        }
    }
    return 0;
}
