#include <stdio.h>
#include <iostream>
#include <fstream>
#define FICHIER_GRAPHE "g8.txt"

using namespace std;

typedef struct {
	int	nbSommets ;
	bool **	MAdj ;	// MAdj[x][y] = TRUE  < == > il existe arc (x,y)
	int ** 	MVal ;	// Si MAdj[x][y] = TRUE alors MVal[x][y] = valeur de l’arc (x,y)
} t_graphe ;

void affichageGrapheAdj(t_graphe **G){
        for(int i = 0; i < (*G)->nbSommets; i++) {
            cout << i << "\t" ;
            for(int j = 0; j < (*G)->nbSommets; j++) {
                if(((*G)->MAdj[i][j] == 1)) {
                    cout << 1 << "\t" ;
                }
                else {
                     cout << 0 << "\t" ;
                }
            }
            cout << "\n" ;
        }
        cout << "\n\n" ;

}

void affichageGrapheVal(t_graphe **G){
    cout << "Graphe valeur";
	for ( int x = 0 ; x < (*G)->nbSommets ; x++ ) {
		cout << x << "\t" ;
		for ( int y = 0 ; y < (*G)->nbSommets ; y ++ ) {
			if ( (*G)->MAdj[x][y] == true ) {
				cout << (*G)->MVal[x][y] << "\t" ;
			} else {
				cout << "x\t" ;
			};
		};
		cout << "\n\n" ;
	};

    cout << "\n\n";
}

void fermetureTransitive(t_graphe **G, t_graphe **F) {
    //Fermeture transitive
    cout << "Fermeture transitive 0" << "\n";
    for(int i = 0; i < (*G)->nbSommets; i++){
        cout << i << "\t" ;
        for(int j = 0; j < (*G)->nbSommets; j++){
            (*F)->MAdj[i][j] = (*G)->MAdj[i][j];
            cout << (*F)->MAdj[i][j] <<"\t" ;
        }
        cout << "\n" ;
    }
    cout << "\n\n" ;

    // if dans ton parcours de ta matrice => diagonale = 1
    // alors tu as un circuit

    for(int k = 0; k < (*G)->nbSommets; k++) {
        cout << "Fermeture transitive "<< k + 1 << "\n\n";
        for(int i = 0; i < (*G)->nbSommets; i++) {
            cout << i << "\t" ;
            for(int j = 0; j < (*G)->nbSommets; j++) {
                if (((*F)->MAdj[i][j]== 1) || ((*F)->MAdj[i][k] && (*F)->MAdj[k][j] == 1)) {
                    (*F)->MAdj[i][j] = true;
                    cout << 1 << "\t" ;
                }
                else {
                     cout << 0 <<"\t" ;
                }
            }
            cout << "\n" ;
        }
        cout << "\n\n" ;
    }

}

bool detectionCircuit (t_graphe **G, t_graphe **F) {
    fermetureTransitive(G, F);
    cout << "Detection de circuit " << "\n\n";
    int temoin = 0;
    for(int i = 0; i < (*G)->nbSommets; i++){
        for(int j = 0; j < (*G)->nbSommets; j++){
            if(i == j && (*F)->MAdj[i][j] == true){
            temoin = 1;
            }
        }
    }

    if(temoin == 1){
        cout << "\n\nIl y a un circuit dans ce graphe" << "\n\n" ;
        return true;
    }
    else{
        cout << "\n\nIl n'y a pas de circuit dans ce graphe" << "\n\n" ;
        return false;
    }
}

void calculRang(t_graphe **G, t_graphe **R){

        int sommeCol = 0;
        int k;
        int i;
        int j;

        cout <<"Rang 1 \n";
        for (j = 0; j < (*G)->nbSommets; j++) {
            /*Rang 1*/
            for (i = 0; i < (*G)->nbSommets; i++) {
                sommeCol = sommeCol + (*G)->MAdj[i][j];
            }
            if (sommeCol == 0) {
                (*R)->MAdj[j][0] = 1;
            }
            sommeCol = 0;
        }
        affichageGrapheAdj(G);
        /*Autre Rang*/
        for (k = 0; k < (*G)->nbSommets; k++) {
                cout <<"Rang " << k + 2 << "\n";
                for( i = 0; i < (*G)->nbSommets; i++) {
                    if ((*R)->MAdj[i][k] == 1) {
                        for (j = 0; j < (*G)->nbSommets; j++) {
                            if ((*G)->MAdj[i][j] == 1) {
                                (*R)->MAdj[j][k+1] = 1; //On ajoute le rang au sommet
                                if((*R)->MAdj[j][k] == 1) //Test du rang max
                                    (*R)->MAdj[j][k] = 0;
                            }
                        }
                    }

                }
            affichageGrapheAdj(G);
        }
}


int main () {

	// Déclaration graphe

	t_graphe * G = new t_graphe;
	t_graphe * F = new t_graphe;
	t_graphe * R = new t_graphe;
//	bool **	 F;     //Matrice fermeture transitive
//	bool ** R;
	// Lecture du graphe sur fichier

	ifstream fg ( FICHIER_GRAPHE ) ;

	fg >> G->nbSommets ; //lecture de sommet
	G->MAdj = new bool * [ G->nbSommets ] ;
	F->MAdj = new bool * [ G->nbSommets ] ;
	R->MAdj = new bool * [ G->nbSommets ] ;
    //F = new bool * [ G->nbSommets ];
    //R = new bool * [ G->nbSommets ];

	for ( int s = 0 ; s < G->nbSommets ; s++ ) {
		G->MAdj[s] = new bool [ G->nbSommets ] ;
		F->MAdj[s] = new bool [ G->nbSommets ] ;
		R->MAdj[s] = new bool [ G->nbSommets ] ;
		//F[s] = new bool [ G->nbSommets ] ;
		//R[s] = new bool [ G->nbSommets ] ;
		for ( int extTerm = 0 ; extTerm < G->nbSommets ; extTerm++ ) {
			G->MAdj[s][extTerm] = false ;
			F->MAdj[s][extTerm] = false ;
			R->MAdj[s][extTerm] = false ;
            //F[s][extTerm] = false ;
            //R[s][extTerm] = false ;
		};
	};
	G->MVal = new int * [ G->nbSommets ] ;
	F->MVal = new int * [ G->nbSommets ] ;
	R->MVal = new int * [ G->nbSommets ] ;
	for ( int s = 0 ; s < G->nbSommets ; s++ ) {
		G->MVal[s] = new int [ G->nbSommets ] ;
		F->MVal[s] = new int [ G->nbSommets ] ;
		R->MVal[s] = new int [ G->nbSommets ] ;
		for ( int extTerm = 0 ; extTerm < G->nbSommets ; extTerm++ ) {
			G->MVal[s][extTerm] = 0 ;
			F->MVal[s][extTerm] = 0 ;
			R->MVal[s][extTerm] = 0 ;
		};
	};

	int extInit ;
	int extTerm ;
	int valeur ;
	fg >> extInit ;
	while ( extInit != -1 ) {
		fg >> extTerm ;
		fg >> valeur ;
		G->MAdj[extInit][extTerm] = true ;
		G->MVal[extInit][extTerm] = valeur ;
		fg >> extInit ;
	} ;

    F->nbSommets = F->nbSommets;
	R->nbSommets = G->nbSommets;
    //fermetureTransitive(&G, (&F));
    bool resultat = detectionCircuit(&G, &F);
    if (resultat == true) {
        cout << "impossible de réaliser le calcul de rang\n";
    }
    else {
        calculRang(&G, &R);
    }
	//system("PAUSE");
	return 1 ;
};
