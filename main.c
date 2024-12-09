#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


typedef struct{
    int l[11];
    int len;
} list;

typedef struct{
    int id;
    char nom[30];
    char categorie[30];
    float prix;
    int quantite;
    char date[11];
} produit;

int format_date(char date[]){  //tester si la date sous la forme (DD/MM/AAAA) ou non
    for(int i=0; i<10;i++){
        if(i==2 || i==5){
            if(date[i]!='/'){
                printf("\nERROR: La date doit etre sous la forme (DD/MM/AAAA)\n");
                return 0;
            }
        }else{
            if(isdigit(date[i])==0){
                printf("\nERROR: Les caracteres doivent etre des chiffres\n");
                return 0;
            }
        }
    }
    return 1;
}

void ajouter_produit() {
    produit p;
    FILE *fichier = fopen("produit.txt", "a");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    printf("ID du produit : ");
    scanf("%d", &p.id);
    printf("Nom du produit : ");
    scanf(" %[^\n]", p.nom);
    printf("Categorie : ");
    scanf(" %[^\n]", p.categorie);
    printf("Prix : ");
    scanf("%f", &p.prix);
    printf("Quantite : ");
    scanf("%d", &p.quantite);
    do {
        printf("Date d'expiration (JJ/MM/AAAA): ");
        scanf("%10s", p.date);
        if(strlen(p.date)>10){
            continue;
        }
    } while(format_date(p.date)==0);
    if (fprintf(fichier, "%d\t%s\t%s\t%.2f\t%d\t%s\n", p.id, p.nom, p.categorie, p.prix, p.quantite, p.date) < 0) {
        printf("Erreur lors de l'ecriture dans le fichier.\n");
    } else {
        printf("Produit ajoute avec succes !\n");
    }
    fclose(fichier);
}
void afficher_produit(int id) {   //afficher list des produits avec l'ID id
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if (p.id == id) {
            printf("\n__________Produit trouve__________ :\n");
            printf("ID: %d\nNom: %s\nCategorie: %s\nPrix: %.2f\nQuantite: %d\nDate d'expiration: %s\n", p.id, p.nom, p.categorie, p.prix, p.quantite, p.date);
            trouve = 1;
            printf("__________________________________\n");
            break;
        }
    }

    if (trouve==0) {
        printf("Aucun produit avec l'ID %d n'a ete trouve.\n", id);
    }

    fclose(fichier);
}
void autre_produit(int id) {  //afficher liste des produits dans une ligne chaqu'un
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    while (fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if (p.id == id) {
            printf("    ID: %d | Nom: %s | Prix: %.2f\n", p.id, p.nom, p.prix);
            break;
        }
    }
    fclose(fichier);
}

void modifier_quantite(int id, int q){
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erreur lors de la creation du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    int trouve=0;
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(p.id==id){
            p.quantite=q+p.quantite;
            trouve=1;
            printf("Quantite modifiee avec succes pour le produit ID %d.\n", id);
        }
        fprintf(temp, "%d\t%s\t%s\t%.2f\t%d\t%s\n", p.id, p.nom, p.categorie, p.prix, p.quantite, p.date);
    }
    if (trouve==0) {
        printf("Aucun produit avec l'ID %d n'a ete trouve.\n", id);
    }

    fclose(fichier);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt", "produit.txt");
}
void modifier_prix(int id, int nv_prix){
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    int trouve=0;
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(p.id==id){
            p.prix=nv_prix;
            trouve=1;
            printf("Prix modifiee avec succes pour le produit ID %d.\n", id);
        }
        fprintf(temp, "%d\t%s\t%s\t%.2f\t%d\t%s\n", p.id, p.nom, p.categorie, p.prix, p.quantite, p.date);
    }
    if (trouve==0) {
        printf("Aucun produit avec l'ID %d n'a ete trouve.\n", id);
    }

    fclose(fichier);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt", "produit.txt");
}

void supprimer_produit(int id){
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(p.id!=id){
            fprintf(temp, "%d\t%s\t%s\t%.2f\t%d\t%s\n", p.id, p.nom, p.categorie, p.prix, p.quantite, p.date);
        }
    }
    fclose(fichier);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt", "produit.txt");
}


int exist_produit(int id){ //tester si le produit exist ou non dans le fichier
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int trouve=0;
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(p.id==id){
            trouve=1;
        }
    }
    fclose(fichier);
    return trouve;
}
float prix_produit(int id){   //retouner le prix d'un produit avec l'ID id
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    float prix;
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(p.id==id){
            prix=p.prix;
            break;
        }
    }
    fclose(fichier);
    return prix;
}

int stock(int id){   //retourner la quantite existe d'un produit
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    float stock;
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(p.id==id){
            stock=p.quantite;
            break;
        }
    }
    fclose(fichier);
    return stock;
}

char* nom(int id){   //retouner le nom d'un produit
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    char *nom=malloc(30 * sizeof(char));
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(p.id==id){
            strcpy(nom, p.nom);
            break;
        }
    }
    fclose(fichier);
    return nom;
}

void afficher_liste_achat(int ids[],int stocks[], int n, float prix_total){
    printf("\n------------------------liste d'achat-----------------------\n");
    for(int i=0;i<n; i++){
        printf("%d.\t%d  %s  %.2f  *%d  %.2f\n", i+1, ids[i], nom(ids[i]), prix_produit(ids[i]), stocks[i], stocks[i]*prix_produit(ids[i]));
    }
    printf("                                        Totale: %.2f\n", prix_total);
    printf("------------------------------------------------------------\n");
}


void supprimer_produit_expiree(int jour, int mois, int annee) {   //supprimer le produit qui avait un date d'expiration terminee
    produit p;
    FILE *fichier = fopen("produit.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    int date_courante = annee * 10000 + mois * 100 + jour;
    int t=1;
    while (fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n",
                  &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        int annee_p, mois_p, jour_p;
        sscanf(p.date, "%d/%d/%d", &jour_p, &mois_p, &annee_p);
        int date_produit = annee_p * 10000 + mois_p * 100 + jour_p;
        if (date_produit >= date_courante) {
            fprintf(temp, "%d\t%s\t%s\t%.2f\t%d\t%s\n",
                    p.id, p.nom, p.categorie, p.prix, p.quantite, p.date);
        }else{
            t=0;
        }
    }
    fclose(fichier);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt", "produit.txt");
    if(t==0){
        printf("Les produits expires ont ete supprimes avec succes.\n");
    }
}


list meme_categorie(char ch[]){  //retourner une liste contient les ids du produit qui ont la meme nom du categorie(ch)
    produit p;
    list resultat={{0},0};
    FILE *fichier = fopen("produit.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    while(fscanf(fichier, "%d\t%[^\t]\t%[^\t]\t%f\t%d\t%s\n", &p.id, p.nom, p.categorie, &p.prix, &p.quantite, p.date) == 6) {
        if(strcmp(p.categorie, ch)==0){
            resultat.l[resultat.len++]=p.id;
        }
        if(resultat.len==11){
            break;
        }
    }
    fclose(fichier);
    return resultat;
}
int exist(int t[],int n, int id){  //tester une id existe ou non dans une liste t
    for(int i=0; i<n; ++i){
        if(t[i]==id){
            return 1;
        }
    }
    return 0;
}

int main() {
    time_t maintenant;
    time(&maintenant);
    struct tm *temps_local = localtime(&maintenant);
    printf("Temps local: %02d-%02d-%04d %02d:%02d:%02d\n",
           temps_local->tm_mday,
           temps_local->tm_mon+1,
           temps_local->tm_year+1900,
           temps_local->tm_hour,
           temps_local->tm_min,
           temps_local->tm_sec);

    supprimer_produit_expiree(temps_local->tm_mday, temps_local->tm_mon + 1, temps_local->tm_year + 1900);
    int choix;
    char t;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Ajouter un produit\n");
        printf("2. Afficher un produit\n");
        printf("3. Modifier la quantite d'un produit\n");
        printf("4. Supprimer un produit\n");
        printf("5. acheter des produits\n");
        printf("6. Quitter\n");
        printf("\nVotre choix : ");
        if (scanf("%d", &choix) != 1) {
            printf("Entree invalide! Veuillez entrer un numero entre 1 et 6.\n");
            getchar();
            choix = 0;
        } else if (choix < 1 || choix > 6) {
            printf("Veuillez entrer un numero valide (1 a 6).\n");
        }

        switch (choix) {
        case 1: {
            ajouter_produit();
            break;
        }
        case 2: {
            int id;
            printf("Entrez l'ID du produit a afficher : ");
            scanf("%d", &id);
            afficher_produit(id);
            break;
        }
        case 3: {
            int id, q;
            printf("Entrez l'ID du produit : ");
            scanf("%d", &id);
            printf("Entrez la quantite a ajouter (ou une valeur negative pour diminuer) : ");
            scanf("%d", &q);
            modifier_quantite(id, q);
            break;
        }
        case 4: {
            int id;
            printf("Entrez l'ID du produit a supprimer : ");
            scanf("%d", &id);
            if(exist_produit(id)){
                supprimer_produit(id);
                printf("Produit supprimer avec succes pour le produit ID %d\n", id);
            }else{
                printf("Produit deja n'existe pas\n");
            }
            break;
        }
        case 5:{
            int nb,n;
            float total_prix=0;
            int list_achat[101], list_quantite[101];
            printf("Donner le nombre de produit a achete: ");
            scanf("%d", &nb);
            n=nb;
            for(int i=0; i<nb; i++){
                int id, q;
                printf("\nID du produit: ", i);
                scanf("%d", &id);
                printf("Quantite: ");
                scanf("%d", &q);
                if(exist_produit(id)==1){
                    if(stock(id)>q){
                        total_prix=total_prix+prix_produit(id)*q;
                        modifier_quantite(id, -q);
                        list_achat[i]=id;
                        list_quantite[i]=q;
                    }else{
                        total_prix=total_prix+prix_produit(id)*stock(id);
                        supprimer_produit(id);
                        list_achat[i]=id;
                        list_quantite[i]=stock(id);
                    }
                }else{
                    printf("Aucun produit avec l'ID %d n'a ete trouve.\n", id);
                    printf("Entrer:\n\t1. Changer produit\n\t2. Produit suivant\n");
                    int c;
                    printf("\nVotre choix : ");
                    scanf("%d", &c);
                    if(c==1){
                        char ch[30];
                        list L;
                        printf("donner la categorie de votre produit introuvable: ");
                        scanf("%s", ch);
                        L=meme_categorie(ch);
                        printf("\n_____Produit de meme categorie_____\n");
                        for(int i=0; i<L.len; i++){
                            autre_produit(L.l[i]);
                        }
                        printf("___________________________________\n");
                        int id2;
                        printf("\nChoisir une ID: ");
                        scanf("%d", &id2);
                        if(exist(L.l, L.len, id2)==0){
                            n--;
                            continue;
                        }else{
                            if(stock(id2)>q){
                                total_prix=total_prix+prix_produit(id2)*q;
                                modifier_quantite(id2, -q);
                                list_achat[i]=id2;
                                list_quantite[i]=q;
                            }else{
                                total_prix=total_prix+prix_produit(id2)*stock(id2);
                                supprimer_produit(id2);
                                list_achat[i]=id2;
                                list_quantite[i]=stock(id2);
                            }
                        }
                    }else if(c==2){
                        n--;
                        continue;
                    }else{
                        printf("Choix invalide. Veuillez reessayer.\n");
                    }
                }
            }
            afficher_liste_achat(list_achat, list_quantite, n, total_prix);
            printf("Achat effectuee avec succes\n");
            break;
        }
        case 6: {
            printf("Au revoir !\n");
            break;
        }
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
            break;
        }
    } while (choix != 6);

    return 0;
}
