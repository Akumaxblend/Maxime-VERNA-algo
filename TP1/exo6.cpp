#include <iostream>

using namespace std;

struct Noeud{
    int donnee;
    Noeud* suivant;
};

struct Liste{
    Noeud* premier;
    // your code
};

struct DynaTableau{
    int* donnees;
    // your code
    int size;
    int nbElem;
};  


void initialise(Liste* liste)
{
    liste->premier = nullptr;
}

bool est_vide(const Liste* liste)
{
    if(liste->premier == nullptr){

        return true;
    }
    else
    return false;
}

void ajoute(Liste* liste, int valeur)
{
    Noeud * elem = new Noeud;
    elem->donnee = valeur;
    elem->suivant = nullptr;

    if(est_vide(liste)){

        liste->premier = elem;
    }

    else{

        Noeud * target = liste->premier;

    while (target->suivant != nullptr)
    {
        target = target->suivant;
    }

        target->suivant = elem;

    }
    
    
}

void affiche(const Liste* liste)
{
    Noeud * target = liste->premier;
    while(target != nullptr){

        cout << target->donnee << endl;
        target = target->suivant;
    }
}

int recupere(const Liste* liste, int n)
{
    Noeud * target = liste->premier;

    for(int i = 0 ; i < n ; i ++){

        if(target == nullptr){

            return -1; 
        }

        target = target->suivant;
        
    }

    return target->donnee;
}

int cherche(const Liste* liste, int valeur)
{
    int i = 1;
    Noeud * target = liste->premier;

    while(target != nullptr){

        if(target->donnee == valeur){

            return i;
        }
        target = target->suivant;
        i++;
    }
    return -1;
}

void stocke(Liste* liste, int n, int valeur)
{
    Noeud * target = liste->premier;

    for (int i = 0 ; i < n-1 ; i++){

    target = target->suivant;   

        if(target == nullptr){

            return;
        }
        
    }
    target->donnee = valeur;
}

void ajoute(DynaTableau* tableau, int valeur)
{

    if(tableau->nbElem >= tableau->size){ //Si le tableau est plein alors on alloue la mémoire supplémentaire

        int * tmp = new int[tableau->size * 2]; //Tableau faisant 2 fois la taille riginale
        tmp = tableau->donnees; //On copie les anciennes données dans le nouveau tableau

        tableau->donnees = tmp; //On fait pointer le tableau vers le tableau plus grand

        //delete tmp; //Nettoyage mémoiiire

        tableau->size *= 2; //Maintenant la taille est doublée :)

    }

    tableau->donnees[tableau->nbElem] = valeur; //Enfin, on ajoute la valeur dans la tableau
    tableau->nbElem ++;

}


void initialise(DynaTableau* tableau, int capacite)
{
    tableau->donnees = new int[capacite];
    tableau->size = capacite;
    tableau->nbElem = 0;
}

bool est_vide(const DynaTableau* tableau)
{
    if(tableau->nbElem == 0) return true;
    else return false;
}

void affiche(const DynaTableau* tableau)
{
    for(int i = 0; i< tableau->nbElem ; i++){

        cout << tableau->donnees[i] << endl;
    }
}

int recupere(const DynaTableau* tableau, int n)
{
    if(n < tableau->size)
    return tableau->donnees[n];

    else return -1;
}

int cherche(const DynaTableau* tableau, int valeur)
{
    for(int i = 0 ; i < tableau->size ; i++){

        if(tableau->donnees[i] == valeur) return i+1;
        else i++;
    }
    return -1;
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    if(n >= tableau->nbElem){
        return;
    }

    tableau->donnees[n-1] = valeur;
}

void pousse_file(DynaTableau* liste, int valeur)
//void pousse_file(Liste* liste, int valeur)
{
    int * tmp = new int[liste->nbElem + 1];
    for(int i = 0 ; i < liste->nbElem ; i++){

        tmp[i+1] = liste->donnees[i];
    }
    tmp[0] = valeur;
    liste->donnees = tmp;
}

//int retire_file(Liste* liste)
int retire_file(DynaTableau* liste)
{
    if (est_vide(liste)) return 0;
    
    int * tmp = new int[liste->nbElem - 1];

    for(int i = 0 ; i < liste->nbElem ; i++){

        tmp[i] = liste->donnees[i+1];

    }

    int toReturn = liste->donnees[liste->nbElem-1];
    liste->donnees = tmp;
    liste->nbElem --;
    return toReturn;
}

void pousse_pile(DynaTableau* liste, int valeur)
//void pousse_pile(Liste* liste, int valeur)
{
    ajoute(liste, valeur);
}

int retire_pile(DynaTableau* liste)
//int retire_pile(Liste* liste)
{
    if(est_vide(liste)) return 0;
    
    int * tmp = new int[liste->nbElem - 1];

    for(int i = 0 ; i < liste->nbElem - 1 ; i++){

        tmp[i] = liste->donnees[i];
    }

    int toReturn = liste->donnees[liste->nbElem];

    liste->donnees = tmp;

    liste->nbElem --;
    
    return toReturn;

}


int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau1" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste à " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste à " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    DynaTableau pile;
    DynaTableau file;

    initialise(&pile,1);
    initialise(&file,1);

    for (int i=1; i<=9; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
