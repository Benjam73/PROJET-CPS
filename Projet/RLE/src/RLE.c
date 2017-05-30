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
    int entier = 0;
    char courant ;
    char compare ;
    

    //On lit les deux premiers caractères du fichier
    fscanf(f_input, "%c", &courant) ;
    fscanf(f_input,"%c", &compare);


    while (!feof(f_input)) {
        //On compare les deux derniers caractères récupérés
        if (courant == compare){
            //S'ils sont identiques, on regarde combien de fois il faut les écrire
            fscanf(f_input, "%d", &entier);
            //fprintf(f_output,"_%d_",entier);
            while(entier+2 > 0){
                fprintf(f_output,"%c",courant);
                entier--;
            }
            //On récupère les deux caractères suivants
            fscanf(f_input, "%c", &courant) ;
            fscanf(f_input,"%c", &compare);
        }else{ 
            //Sinon on écrit un seul caractère et on recommence avec le suivant
            fprintf(f_output,"%c",courant);
            courant = compare;
            fscanf(f_input, "%c", &compare) ;
        }

    }
}

