#include "RLE.h"


void rle (FILE* f_input, FILE* f_output){
	char courant ;
	char compare ;
	fscanf(f_input, "%c", &compare) ;

	int cpt = 1;

	while (!feof(f_input)){

		fscanf(f_input, "%c", &courant) ;
		if (compare == courant && cpt <= 9){
			cpt++;
		}
		else{
            // Si le compteur est superieur a 1 alors il y a une repetition du char compare.
			if (cpt>=2){
                fprintf(f_output,"%c", compare);
                fprintf(f_output,"%c", compare);
                fprintf(f_output,"%d", cpt-2);
            }
            else{ 
            // Sinon il n'y a pas de repetion donc on affiche que le char.
                fprintf(f_output,"%c", compare);
            }

            // Permettant de mettre un point entre chaque couple (int, char), sert alors de separateur
            // fprintf(f_output, ".");
            compare = courant;
            cpt = 1;
        }
    }
}

void elr (FILE* f_input, FILE* f_output){
    int entier = 0;//, unite = 0, new_cpt = 0;
    char courant ;
    char compare ;
    
    fscanf(f_input, "%c", &courant) ;


    while (!feof(f_input)) {

        // Consomme et met dans une variable l'entier, le caractere et consomme juste le point.
        fscanf(f_input,"%c", &compare);
        
        // Si le caractere est un point c'est qu'il a une entree : .123. Ici on doit alors afficher 12 fois le chiffre 3.
        if (courant == compare){
            fscanf(f_input, "%d", &entier);
            fprintf(f_output,"%c",compare);
            fprintf(f_output,"%c",compare);
            while(entier > 0){
                fprintf(f_output,"%c",compare);
                entier--;
            }
        }else{ 
            fprintf(f_output,"%c",courant);
            fscanf(f_input, "%c", &courant) ;
        }

    }
}

