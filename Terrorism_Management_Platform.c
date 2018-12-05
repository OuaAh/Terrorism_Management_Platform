#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct{
    char *LOGIN;
    char *MOT_P;
    char *ROLE;
} PERSONNEL;

typedef struct ALERT ALERT;
struct ALERT{
    char* ZONE;
    char ID[7];
    char TYPE;
    ALERT* LIEN;
};

void REMPLIR(PERSONNEL **P,int NP){
    int i;
    char T[25];
    *P=(PERSONNEL*)malloc(NP*sizeof(PERSONNEL));
    for(i=0;i<NP;i++){
        fflush(stdin);
        printf("\n  LOGIN: ");
        gets(T);
        (*P)[i].LOGIN=(char*)malloc(strlen(T)+1);
        strcpy((*P)[i].LOGIN,T);
        printf("  MOT DE PASSE: ");
        gets(T);
        (*P)[i].MOT_P=(char*)malloc(strlen(T)+1);
        strcpy((*P)[i].MOT_P,T);

        do {
                printf("  ROLE:(AGENT/ADMINISTRATEUR) ");
                gets(T);
        }
        while (strcmp(T,"AGENT")&&strcmp(T,"ADMINISTRATEUR"));
        (*P)[i].ROLE=(char*)malloc(strlen(T)+1);
        strcpy((*P)[i].ROLE,T);
        printf("\n");
    }
}

int ASSIGNER(char *L,char *M,PERSONNEL *P,int NP){
    int i=0,B=-1;
    do if((!(strcmp(L,P[i].LOGIN))&&(!(strcmp(M,P[i].MOT_P))))) {
            if (strcmp(P[i].ROLE,"AGENT")) B=1; else B=2;
    }
    else i++;
    while ((i<NP)&&(B==-1));
    return(B);
}

void PREMIERE(ALERT** B){
    char Tx[25];
    (*B)=malloc(sizeof(ALERT));
    fflush(stdin);
    printf("\n ZONE: ");
    gets(Tx);
    (*(*B)).ZONE=malloc(strlen(Tx)+1);
    strcpy((*(*B)).ZONE,Tx);
    sscanf((*(*B)).ZONE,"%2s",((*(*B)).ID));
    strcat((*(*B)).ID,"0001");
    do {fflush(stdin);
        printf(" TYPE(CRITIQUE Y/N): ");
        scanf("%c",&((*(*B)).TYPE));}
    while((((*(*B)).TYPE)!='Y')&&(((*(*B)).TYPE)!='N'));
    (*(*B)).LIEN=NULL;
    printf("\n ID= %s",(*(*B)).ID);
    getch();
}

int OCCURENCE(ALERT* A,char* Z){
    int i=0;
    while (A){
        if (!(strcmp((*A).ZONE,Z))) i++;
        A=(*A).LIEN;
    }
    return(i);
}

void AJOUTER(ALERT** A){
    ALERT* B;
    char Tx[25];
    char N[5];
    B=malloc(sizeof(ALERT));
    fflush(stdin);
    printf("\n ZONE: ");
    gets(Tx);
    (*B).ZONE=malloc(strlen(Tx)+1);
    strcpy((*B).ZONE,Tx);
    sscanf(((*B).ZONE),"%2s",((*B).ID));
    itoa(OCCURENCE((*A),(*B).ZONE)+1,N,10);
    switch (strlen(N)){
        case 1: strcat((*B).ID,"000");break;
        case 2: strcat((*B).ID,"00");break;
        case 3: strcat((*B).ID,"0");break;
    }
    strcat((*B).ID,N);
    do {fflush(stdin);
        printf(" TYPE(CRITIQUE Y/N): ");
        scanf("%c",&((*B).TYPE));}
    while((((*B).TYPE)!='Y')&&(((*B).TYPE)!='N'));
    (*B).LIEN=(*A);
    (*A)=B;
    printf("\n ID= %s",(*(*A)).ID);
    getch();
}

void TRAITER(ALERT* A,char I[7],ALERT** O){
    int i,B;
    ALERT* D;
    ALERT* C=NULL;
    D=A;
    RETOUR:
    A=D;
    ALERT* G;
    G=A;
    char N[5],X[3];
    system("cls");
    fflush(stdin);
    printf("\n ID: ");
    gets(I);
    while(A&&B){
        B=strcmp((*A).ID,I);
        if (!B) {
            RETRAITER:
            system("cls");
            printf("\n 1.AFFICHIER\n 2.MODIFIER\n 3.SUPPRIMER\n ");
            scanf("%d",&i);
            switch (i) {
                case 1: {system("cls");printf("\n ZONE: %s\tID: %s\tTYPE(CRITIQUE(N/Y)): %c \n ",(*A).ZONE,(*A).ID,(*A).TYPE);getch();} break;
                case 2: {
                    system("cls");
                    printf("\n 1.TOUTE L'ALERT (ZONE/TYPE)\n 2.TYPE SEULEMENT\n 3.ANNULER\n ");
                    scanf("%d",&i);
                    switch(i){
                    case 1:{
                    char Tx[25];
                    fflush(stdin);
                    system("cls");
                    printf("\n ZONE: ");
                    gets(Tx);

                    if (strcmp((*A).ZONE,Tx)){
                     while (strcmp((*A).ID,(*G).ID)){

                          if (!(strcmp((*A).ZONE,(*G).ZONE))){
                           sscanf(((*G).ID),"%2s%4s",X,N);
                           strcpy((*G).ID,X);
                           itoa(atoi(N)-1,N,10);
                           switch (strlen(N)){
                               case 1: strcat((*G).ID,"000");break;
                               case 2: strcat((*G).ID,"00");break;
                               case 3: strcat((*G).ID,"0");break;
                           }
                           strcat((*G).ID,N);
                        }
                        G=(*G).LIEN;
                    }

                    (*A).ZONE=malloc(strlen(Tx)+1);
                    strcpy((*A).ZONE,Tx);
                    sscanf(((*A).ZONE),"%2s",((*A).ID));
                    itoa(OCCURENCE(D,(*A).ZONE),N,10);
                    switch (strlen(N)){
                        case 1: strcat((*A).ID,"000");break;
                        case 2: strcat((*A).ID,"00");break;
                        case 3: strcat((*A).ID,"0");break;
                    }
                    strcat((*A).ID,N);
                    do {fflush(stdin);
                        printf(" TYPE(CRITIQUE Y/N): ");
                        scanf("%c",&((*A).TYPE));}
                     while((((*A).TYPE)!='Y')&&(((*A).TYPE)!='N'));
                    }}break;
                    case 2:{
                    do {fflush(stdin);
                        printf("\n TYPE(CRITIQUE Y/N): ");
                        scanf("%c",&((*A).TYPE));}
                     while((((*A).TYPE)!='Y')&&(((*A).TYPE)!='N'));
                    } break;
                    default : goto RETRAITER;
                    }
                } break;
                case 3: {
                     while (strcmp((*A).ID,(*G).ID)){

                          if (!(strcmp((*A).ZONE,(*G).ZONE))){
                           sscanf(((*G).ID),"%2s%4s",X,N);
                           strcpy((*G).ID,X);
                           itoa(atoi(N)-1,N,10);
                           switch (strlen(N)){
                               case 1: strcat((*G).ID,"000");break;
                               case 2: strcat((*G).ID,"00");break;
                               case 3: strcat((*G).ID,"0");break;
                           }
                           strcat((*G).ID,N);
                           printf("%s\n",(*G).ID);
                        }
                        G=(*G).LIEN;
                    }
                    if (C) (*C).LIEN=(*A).LIEN;
                    else if ((*(*O)).LIEN) (*O)=(*(*O)).LIEN;
                              else (*O)=NULL;
                               } break;
                default: {printf("\n CHOIX INCORRECT");getch();goto RETRAITER;}
            }
            }
        C=A;
        A=(*A).LIEN;
    }
    if (B) {printf("\n ID INCORRECT.");getch();
            REESOR:
            system("cls");
            printf("\n 1.REESSAYER\n 2.SORTIR\n ");
            scanf("%d",&i);
            switch (i){
                case 1: goto RETOUR;break;
                case 2:  exit(EXIT_FAILURE);break;
                default : {printf("\n CHOIX INCORRECT");getch();goto REESOR;}
            }
            }
}

void AFFICHIER(ALERT* A){
    while(A){
        printf("\n ZONE: %s\tID: %s\tTYPE(CRITIQUE(N/Y)): %c ",(*A).ZONE,(*A).ID,(*A).TYPE);
        A=(*A).LIEN;
    }
}

int TAILLE(ALERT* A){
    int i=0;
    while(A){
        i++;
        A=(*A).LIEN;
    }
    return(i);
}

float POURCENTAGE(ALERT* A,char* Z){
    float F=(float)OCCURENCE(A,Z)/(float)TAILLE(A);
    if (TAILLE(A)) F=(float)OCCURENCE(A,Z)/(float)TAILLE(A);
    else F=0;
    return(F*100);
}

int main()
{
    PERSONNEL *P;
    int NP;
    char L[25];
    char M[25];
    int T;
    int S;
    do{ printf("\n LE NOMBRE DE PERSONNEL: ");
        scanf("%d",&NP);
    } while (NP<1);
    REMPLIR(&P,NP);

    FILE* F;
    FILE* FAG;
    FILE* FAD;
    int i;
    char LO[25];
    char MP[25];
    char R[15];

    F=fopen("PERSONNEL.txt","w");
    for(i=0;i<NP;i++){
        fprintf(F,"%s\t%s\t%s\n",P[i].LOGIN,P[i].MOT_P,P[i].ROLE);
    }
    fclose(F);

    F=fopen("PERSONNEL.dat","w");
    fwrite(P,sizeof(PERSONNEL),NP,F);
    fclose(F);

    F=fopen("PERSONNEL.txt","r");
    FAG=fopen("AGENT.txt","w");
    FAD=fopen("ADMINISTRATEUR.txt","w");
    for(i=0;i<NP;i++){
        fscanf(F,"%s\t%s\t%s\n",LO,MP,R);
        if (strcmp(R,"AGENT")) fprintf(FAD,"%s\t%s\n",LO,MP);
        else fprintf(FAG,"%s\t%s\n",LO,MP);
    }
    fclose(FAD);
    fclose(FAG);
    fclose(F);

    ALERT* A=NULL;

    RELOGIN :
    system("cls");
    printf("\n 1.CONNECTER\n 2.SORTIR\n ");
    scanf("%d",&i);

    if (i==1) {
    system("cls");
    fflush(stdin);
    printf("\n LOGIN: ");
    gets(L);
    printf(" MOT DE PASSE: ");
    gets(M);
    printf("\n");

    T=ASSIGNER(L,M,P,NP);

    int NA;

    switch (T){
        case -1 : {printf("\n LOGIN OU MOT DE PASSE INCORRECT.");getch();goto RELOGIN;}break;

        case  1 : {
            RAD:
            system("cls");
            printf("\n 1.AFFICHIER LA LISTE DES ALERTES\n 2.AFFICHIER LE POURCENTAGE D'ALERT EN UNE ZONE DONNEE\n 3.DECONNECTER\n ");
            scanf("%d",&S);
            switch (S){
                case 1 : {
                    system("cls");
                    AFFICHIER(A);
                    getch();
                    goto RAD;
                }break;

                case 2 : {
                        system("cls");
                        fflush(stdin);
                        printf("\n ZONE: ");
                        char Z[25];
                        gets(Z);
                        printf("\n LE POURCENTAGE D'ALERT EN %s P= %.0f%c",Z,POURCENTAGE(A,Z),'%');
                        getch();
                        goto RAD;
                }break;

                case 3 : goto RELOGIN;;break;

                default: {printf("\n CHOIX INCORRECT");getch();goto RAD;};break;
            }
            }break;

        case  2 : {
            RAG:
            system("cls");
            printf("\n 1.AJOUTER\n 2.TRAITER\n 3.DECONNECTER\n ");
            scanf("%d",&S);
            switch (S){
                case 1 :{
                    system("cls");
                    if (A) AJOUTER(&A);
                    else PREMIERE(&A);
                    goto RAG;
                }break;

                case 2 :{
                    char I[7];
                    TRAITER(A,I,&A);
                    goto RAG;
                    }break;

                 case 3 : goto RELOGIN;;break;

                default: {printf("\n CHOIX INCORRECT");getch();goto RAG;}break;
        }break;
    }}}
    else if (i!=2) {printf("\n CHOIX INCORRECT");getch();goto RELOGIN;};

    return 0;
}
