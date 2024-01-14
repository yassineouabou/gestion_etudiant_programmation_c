#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#define MAX_ETUDIANTS 100
//STRUCTURES
typedef struct Etudiant{
    char Nom[20];
    int Num_inscription;
    float Note;
    int presence[6];
}Etudiant;

typedef struct Login{
    char Nom[20],Password[30];
}Login;

//FONCTION VALIDATON
int validerNom(char *nom) {
    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalpha(nom[i])) {
            return 0; // Caractère non alphabétique trouvé
        }
    }
    return 1; // Nom valide
}

int validerNum_Inscription(int num_Inscription) {
    // Exemple : Longueur de 8 chiffres
    int longueur = 0;
    while (num_Inscription != 0) {
        num_Inscription /= 10;
        longueur++;
    }
    return (longueur == 6); //numéro contient 6 chiffre 
}

int validerNote(float note) {
    return (note >= 0.00 && note <= 20.00); 
}

int validerPresence(int *presence) {
    int i;
    for(i=0;i<6;i++){
        if (presence[i] != 0 && presence[i] != 1)
            return 0;
    }
    return 1;
}
//AJOUTER ETUDIANT
void ajouterEtudiant(Etudiant etudiants[], int *nbrEtudiants) {
    int i;
    if (*nbrEtudiants < MAX_ETUDIANTS) {
        printf("\n\n");
        do {
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|tEntrez le nom de l etudiant : ");
            scanf("%s",etudiants[*nbrEtudiants].Nom);
        } while (!validerNom(etudiants[*nbrEtudiants].Nom));
        
        do {
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|Entrez le numero d inscription (6 chiffres) : ");
            scanf("%d", &etudiants[*nbrEtudiants].Num_inscription);
        } while (!validerNum_Inscription(etudiants[*nbrEtudiants].Num_inscription));

        do {
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|Entrez la note de l etudiant : ");
            scanf("%f", &etudiants[*nbrEtudiants].Note);
        } while (!validerNote(etudiants[*nbrEtudiants].Note));

         do {
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|Entrez la presence de la semaine (0 pour absent, 1 pour present):\n");
            for(i=0;i<6;i++)
                scanf("\t\t   %d", &etudiants[*nbrEtudiants].presence[i]);

        } while (!validerPresence(etudiants[*nbrEtudiants].presence));
        (*nbrEtudiants)++;
        system("cls");
        printf("Etudiant ajoute avec succes.\n");
    } else {
        printf("Nombre maximum d etudiants atteint.\n");
    }
}
// Fonction pour afficher les informations d'un étudiant
void rechercherEtudiant(Etudiant etudiants[],int nbrEtudiants) {
    int i,j,num;
    printf("Entrez le numero d inscription de l etudiant a rechercher : ");
    scanf("%d",&num);
    system("cls");
    for (i = 0; i < nbrEtudiants; i++){
        if(etudiants[i].Num_inscription==num){
            printf("\n\n");
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|Nom: %s\n", etudiants[i].Nom);
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|Numero d'inscription: %d\n", etudiants[i].Num_inscription);
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|Note: %.2f\n", etudiants[i].Note);
            printf("\t\t|-------------------------------------------------------|\n");
            printf("\t\t|Presence de la semaine (0 pour absent, 1 pour present): \n");
            for(j=0;j<6;j++)
            printf("\t    %d  ", etudiants[i].presence[j]);
        printf("\n\t\t|-------------------------------------------------------|\n");
        printf("\n\n");
        }
    }
}
// Fonction pour afficher tous les étudiants
void afficherTousLesEtudiants(Etudiant etudiants[], int nombreEtudiants) {
    int i,j;
    for (i = 0; i < nombreEtudiants; i++) {
        printf("\n");
        printf("\t\t|-------------------------------------------------------|\n");
        printf("\t\t|Nom: %s\n", etudiants[i].Nom);
        printf("\t\t|-------------------------------------------------------|\n");
        printf("\t\t|Numero d'inscription: %d\n",  etudiants[i].Num_inscription);
        printf("\t\t|-------------------------------------------------------|\n");
        printf("\t\t|Note: %.2f\n", etudiants[i].Note);
        printf("\t\t|-------------------------------------------------------|\n");
        printf("\t\tPresence de la semaine (0 pour absent, 1 pour present):\n \n");
        printf("\t");
        for (j = 0; j < 6; j++)
            printf("\t    %d  ", etudiants[i].presence[j]);
        printf("\n\t\t|-------------------------------------------------------|\n");
        printf("\n\n");
    }
}

void mettreAJourEtudiant(Etudiant etudiants[], int nombreEtudiants) {
    int num,i,j;
    printf("Entrez le numero d'inscription de l'etudiant a mettre a jour : ");
    scanf("%d", &num);

    for (i = 0; i < nombreEtudiants; i++) {
        if (etudiants[i].Num_inscription == num) {
            do{
                printf("Entrez le nouveau nom de l'etudiant : ");
                scanf("%s",etudiants[i].Nom);
            }while(!validerNom(etudiants[i].Nom));
            do{
                printf("Entrez la nouvelle note de l'etudiant : ");
                scanf("%f", &etudiants[i].Note);
            }while(!validerNote(etudiants[i].Note));
            do{
                printf("Entrez le nouveau nombre de jours de presence de l'etudiant: \n");
                for(j=0;j<6;j++)
                    scanf("%d", &etudiants[i].presence[j]);
            }while(!validerPresence(etudiants[i].presence));
            system("cls");
            printf("Etudiant mis a jour avec succes.\n");
        }
    }
}

void sauvegarderDansFichier(Etudiant etudiants[], int nombreEtudiants) {
    FILE *pf ;
    int i,j;
    pf = fopen("data.txt", "w");
    if (pf == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        return;
    }
    for (i = 0; i < nombreEtudiants; i++) {
        fprintf(pf, "%s\t%d\t%.2f\t", etudiants[i].Nom, etudiants[i].Num_inscription, etudiants[i].Note);
        for (j = 0; j <6; j++)
            fprintf(pf,"%d ",etudiants[i].presence[j]);
        fprintf(pf,"\n");
    }
    fclose(pf);
    printf("Donnees sauvegardees dans le fichier avec succes.\n");
    return;
}
//trier par nom

void trierparnom(Etudiant etudiants[],int nombreEtudiants){
    int i,op,j;
    Etudiant E;
    printf("\n");
    printf("\t\t////////////////////////////////////\n");
    printf("\n");
    printf("\t\t//\t  1-trier croissant.      //\n");
    printf("\n");
    printf("\t\t//\t  2-trier decroissant.    //\n");
    printf("\n\t\t////////////////////////////////////\n"); 
    printf("\n\tsaisir votre choix: ");
    scanf("%d",&op);
    if(op == 2){
        for (i = 0; i < nombreEtudiants-1; i++)
            for (j = i+1; j < nombreEtudiants; j++)
                if(strcmp(etudiants[i].Nom,etudiants[j].Nom)<0){
                    E = etudiants[i];
                    etudiants[i]=etudiants[j];
                    etudiants[j] = E;
                }
    }
    else if(op == 1){
        for (i = 0; i < nombreEtudiants-1; i++)
            for (j = i+1; j < nombreEtudiants; j++)
                if(strcmp(etudiants[i].Nom,etudiants[j].Nom)>0){
                    E = etudiants[i];
                    etudiants[i]=etudiants[j];
                    etudiants[j] = E;
                }
    }
    system("cls");
    printf("liste d etudiants est trier par nom.\n");
}

void trierparnumiscription(Etudiant etudiants[],int nombreEtudiants){
    int i,op,j;
    Etudiant E;
    printf("\n");
    printf("\t\t////////////////////////////////////\n");
    printf("\n");
    printf("\t\t//\t  1-trier croissant.      //\n");
    printf("\n");
    printf("\t\t//\t  2-trier decroissant.    //\n");
    printf("\n\t\t////////////////////////////////////\n"); 
    printf("\n\tsaisir votre choix: ");
    scanf("%d",&op);
    if(op == 2){
        for (i = 0; i < nombreEtudiants-1; i++)
            for (j = i+1; j < nombreEtudiants; j++)
                if(etudiants[i].Num_inscription < etudiants[j].Num_inscription){
                    E = etudiants[i];
                    etudiants[i]=etudiants[j];
                    etudiants[j] = E;
                }
    }
    else if(op == 1){
        for (i = 0; i < nombreEtudiants-1; i++)
            for (j = i+1; j < nombreEtudiants; j++)
                if(etudiants[i].Num_inscription > etudiants[j].Num_inscription){
                    E = etudiants[i];
                    etudiants[i]=etudiants[j];
                    etudiants[j] = E;
                }
    }
    system("cls");
    printf("liste d etudiants est trier par num d inscription.\n");
}

void trierparnote(Etudiant etudiants[],int nombreEtudiants){
    int i,op,j;
    Etudiant E;
    printf("\n");
    printf("\t\t////////////////////////////////////\n");
    printf("\n");
    printf("\t\t//\t  1-trier croissant.      //\n");
    printf("\n");
    printf("\t\t//\t  2-trier decroissant.    //\n");
    printf("\n\t\t////////////////////////////////////\n"); 
    printf("\n\tsaisir votre choix: ");
    scanf("%d",&op);
    if(op == 2){
        for (i = 0; i < nombreEtudiants-1; i++)
            for (j = i+1; j < nombreEtudiants; j++)
                if(etudiants[i].Note < etudiants[j].Note){
                    E = etudiants[i];
                    etudiants[i]=etudiants[j];
                    etudiants[j] = E;
                }
        system("cls");
        printf("liste d etudiants est trier par les notes.\n");
    }

    else if(op == 1){
        for (i = 0; i < nombreEtudiants-1; i++)
            for (j = i+1; j < nombreEtudiants; j++)
                if(etudiants[i].Note > etudiants[j].Note){
                    E = etudiants[i];
                    etudiants[i]=etudiants[j];
                    etudiants[j] = E;
                }
        system("cls");
        printf("liste d etudiants est trier par les notes.\n");
    }
    else 
        printf("operation incorrect !!\n");
    
}

int afficherinformation(char *nomchercher){
    FILE *pf;
    char Nom[30];
    int num, presence[6], i;
    float note;
    int trouver;
    pf = fopen("data.txt","r");
    if (pf == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    } else {
        while (feof(pf)==0) {
            fscanf(pf, "%s\t%d\t%f", Nom, &num, &note);
            if (strcmp(Nom, nomchercher) == 0) {
                for (i = 0; i < 6; i++)
                    fscanf(pf, "%d", &presence[i]);
                printf("\n\n");
                printf("\t\t|-------------------------------------------------------|\n");
                printf("\t\t|Nom: %s\n", Nom);
                printf("\t\t|-------------------------------------------------------|\n");
                printf("\t\t|Numero d'inscription: %d\n", num);
                printf("\t\t|-------------------------------------------------------|\n");
                printf("\t\t|Note: %.2f\n", note);
                printf("\t\t|-------------------------------------------------------|\n");
                printf("\t\tPresence de la semaine (0 pour absent, 1 pour present):\n \n");
                printf("\t");
                for (i = 0; i < 6; i++)
                    printf("\t    %d  ", presence[i]);
                printf("\n\t\t|-------------------------------------------------------|\n");
                printf("\n\n");
                break;
            } 
        }
        fclose(pf);
    }
    return 0;
} 

void add_data(Etudiant etd[],int *nbr){
    FILE *pf;
    int i,j;
    pf = fopen("data.txt","r");
    if(pf==NULL)
        printf("Erreur lors de l'ouverture du fichier");
    else{
        while(feof(pf)==0){
            fscanf(pf,"%s\t%d\t%f\t",etd[*nbr].Nom,&etd[*nbr].Num_inscription,etd[*nbr].Note);
            for (i = 0; i <6; i++)
                fscanf(pf,"%d ",etd[*nbr].presence[i]);
            nbr++;
        }
    fclose(pf);
    }


}

int connect_admin(char name[]){
    Etudiant etudiants[MAX_ETUDIANTS];
    int nbr_etudiants=0;
    int choix;
    FILE *pf;
    int i,j;
    do {
        printf("\t\t     ///    Bienvenu %s     \\\\\\\n\n",name);
        printf("\n\t\t         * Gestion des Etudiants *\n");
        printf("\t--------------------------------------------------------\n");
        
        printf("\t\t1. Ajouter un Etudiant\n\n");
        printf("\t\t2. Rechercher un Etudiant\n\n");
        printf("\t\t3. Afficher Tous Les Etudiants\n\n");
        printf("\t\t4. mettre a jour un Etudiant\n\n");
        printf("\t\t5. Trier les Etudiants par Nom\n\n");
        printf("\t\t6. Trier les Etudiants par le numero d inscription\n\n");
        printf("\t\t7. Trier les Etudiants par les notes\n\n");
        printf("\t\t8. Sauvegarder les Donnees dans un Fichier\n\n");
        printf("\t\t9. Quitter\n\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                system("cls");
                ajouterEtudiant(etudiants,&nbr_etudiants);
                break;
            case 2:
                system("cls");
                rechercherEtudiant(etudiants,nbr_etudiants);
                break;
            case 3:
                system("cls");
                afficherTousLesEtudiants(etudiants,nbr_etudiants);
                break;
            case 4:
                system("cls");
                mettreAJourEtudiant(etudiants, nbr_etudiants);
                break;
            case 5:
                system("cls");
                trierparnom(etudiants,nbr_etudiants);
                break;
            case 6:
                system("cls");
                trierparnumiscription(etudiants,nbr_etudiants);
                break;
            case 7:
                system("cls");
                trierparnote(etudiants,nbr_etudiants);
                break;
            case 8:
                system("cls");
                sauvegarderDansFichier(etudiants,nbr_etudiants);
                break;
            case 9:
                system("cls");
                return 0;
            default:
                system("cls");
                printf("Choix invalide ! Veuillez entrer une option valide.\n");
        }
    } while (choix != 9);
}

int connect_etudiant(char name[]){
    int op;
    do{
    printf("\n");
    printf("\t\t     ///     Bienvenu %s    \\\\\\\n",name);
    printf("\n");
    printf("\t\t|--------------------------------------|\n");
    printf("\t\t|     1-Afficher vos informations.     |\n");
    printf("\t\t|--------------------------------------|\n");
    printf("\t\t|              2-quitter               |\n");
    printf("\t\t|--------------------------------------|\n");
    printf("\n\t saisir votre choix: ");
    scanf("%d",&op);
    if(op==1){
        system("cls");
        op = afficherinformation(name);
    }
        
    else if(op==2)
        return 0;
    else
        system("cls");

    }while(op!=1 && op!=2);

}
//LOGIN FONCTIONS
char* login_etudiant(){
    FILE *pf;
    Login user;
    int op,num;
    char username[20],password[30],*nom;
    nom = (char*)malloc(20*sizeof(char)); 
    printf("\n");
    printf("\t\t    ///   Bienvenu Etudiant   \\\\\\\n\n");
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|Nom: ");
    scanf("%s",user.Nom);
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|mot de passe: ");
    scanf("%s",user.Password); 
    pf = fopen("etudiant.txt","r");
    if(pf==NULL)
        printf ("Erreur a l'ouverture du fichier\n");
    else{
        while(feof(pf)==0){
            fscanf(pf,"%s\t%d\t%s\n",username,num,password);
            if(strcmp(username,user.Nom)==0 && strcmp(user.Password,password)==0){
                system("cls");
                strcpy(nom,user.Nom);
                return nom;//puor login admin
            }
        }        
        system("cls");
        printf("Incorrect! \n");
        fclose(pf);
        return NULL;  
    } 
}

char* login_admin(){
    FILE *pf;
    Login user;
    int op;
    char username[20],password[30],*nom;
    nom = (char*)malloc(20*sizeof(char)); 
    printf("\n");
    printf("\t\t     ///    Bienvenue Admin    \\\\\\\n\n");
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|Nom: ");
    scanf("%s",user.Nom);
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|mot de passe: ");
    scanf("%s",user.Password); 
    pf = fopen("admin.txt","r");
    if(pf==NULL)
        printf ("Erreur a l'ouverture du fichier\n");
    else{
        while(feof(pf)==0){
            fscanf(pf,"%s\t%s\n",username,password);
            if(strcmp(username,user.Nom)==0 && strcmp(user.Password,password)==0){
                system("cls");
                strcpy(nom,user.Nom);
                return nom;//puor login admin
            }
        }        
        system("cls");
        printf("Incorrect! \n");
        fclose(pf);
        return NULL;  
    } 
}
 
int create_etudiant(){
    FILE *pf;
    char Nom[20],Password[30];
    int Num_inscription;
    printf("\n");
    printf("\t\t   ///   Bienvenue Etudiant   \\\\\\\n\n");
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|Nom: ");
    scanf("%s",Nom);
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|Num_inscription: ");
    scanf("%d",&Num_inscription); 
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|mot de passe: ");
    scanf("%s",Password);        
    pf = fopen("etudiant.txt","a");
    if(pf==NULL)
        printf ("Erreur a l ouverture du fichier\n");
    else{
        fprintf(pf,"%s\t%d\t%s\n",Nom,Num_inscription,Password);
        system("cls");
        printf("information added to fichier\n");
    fclose(pf); 
    } 
    return 0;
}

int create_admin(){
    FILE *pf;
    Login user;
    char Nom[20],Password[30];
    printf("\n");
    printf("\t\t    ///   Bienvenu Admin  \\\\\\\n\n");
    printf("\t\t|-----------------------------------|\n");
    printf("\t\t|Nom: ");
    scanf("%s",Nom);
    printf("\n\t\t|-----------------------------------|\n");
    printf("\t\t|mot de passe: ");
    scanf("%s",Password);        
    pf = fopen("admin.txt","a");
    if(pf==NULL)
        printf ("Erreur a l ouverture du fichier\n");
    else{
        fprintf(pf,"%s\t%s\n",Nom,Password);
        system("cls");
        printf("informations ajoutees au fichier\n");
    fclose(pf); 
    } 
    return 0;
}

int Home(char mot[]){
    int op;
    char *name;
    do{
        system("cls");
    printf("\n");
    printf("\t\t     ///   Bienvenu %s   \\\\\\\n",mot);
    printf("\n\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\t\t|           1-Se connecter          |\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\t\t|          2-Creer un compte        |\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\t\t|            3-quitter              |\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\n\t saisir votre choix: ");
        scanf("%d",&op);
        if(op==2){
            system("cls");
            if(strcmp(mot,"Admin")==0)
            op = create_admin();
            else
            op = create_etudiant();
        }
        if(op==1){
            system("cls");
            if(strcmp(mot,"Admin")==0){
                name = login_admin();
                if(name)
                op = connect_admin(name);
            }
            else{
                name = login_etudiant();
                if(name)
                op = connect_etudiant(name);
            }
        
        }
        else if(op==3)
            return 0;

    }while(name==NULL ||(op!=1 && op!=2 && op!=3));
}

int main(){
    int op;
    char *mot;
    mot =(char*)malloc(10*sizeof(char)); 
    do{
        system("cls");
        printf("\n\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\t\t|                                   |\n");
        printf("\t\t|             1-Admin               |\n");
        printf("\t\t|                                   |\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\t\t|                                   |\n");
        printf("\t\t|            2-Etudiant             |\n");
        printf("\t\t|                                   |\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\t\t|                                   |\n");
        printf("\t\t|            3-quitter              |\n");
        printf("\t\t|                                   |\n");
        printf("\t\t|-----------------------------------|\n");
        printf("\n\tsaisir votre choix: ");
        scanf("%d",&op);
        if(op==1){
            strcpy(mot,"Admin");
            system("cls");
           op =  Home(mot);
        }
        if(op==2){
            strcpy(mot,"Etudiant");
            system("cls");
           op = Home(mot);
        }
        if(op==3)
            exit(0);
    }while(op!=1 && op!=2 && op!=3);

    return 0;
}