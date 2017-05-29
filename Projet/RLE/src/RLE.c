#include "RLE.h"


void rle (FILE* f_input, FILE* f_output){
	char courant ;
	char compare ;
	fscanf(f_input, "%c", &compare) ;

	int cpt = 1;

	while (!feof(f_input)) {
		fscanf(f_input, "%c", &courant) ;
		if (compare == courant){
			cpt++;
		}
		else{
            // Si le compteur est superieur a 1 alors il y a une repetition du char compare.
			if (cpt>1){
				fprintf(f_output,"%d", cpt);
				fprintf(f_output,"%c", compare);
			}else{ // Sinon il n'y a pas de repetion donc on affiche que le char.
				fprintf(f_output,"%c", compare);
			}

            // Permettant de mettre un point entre chaque couple (int, char), sert alors de separateur
			fprintf(f_output, ".");
			compare = courant;
			cpt = 1;
		}
	}
}

void elr (FILE* f_input, FILE* f_output){
    int entier=0;
    char carac;

    while (!feof(f_input)) {

        // Consomme et met dans une variable l'entier, le caractere et consomme juste le point.
        int scan_int = fscanf(f_input,"%d", &entier);
       	fscanf(f_input,"%c", &carac);
        fscanf(f_input,".");

        // Si le caractere est un point c'est qu'il a une entree : .123. Ici on doit alors afficher 12 fois le chiffre 3.
        if (carac == '.'){
            // Si l'entier est inferieur a 10 alors on a juste a mettre le chiffre dans le fichier.
            if (entier<10){
                fprintf(f_output, "%d", entier);
            }else{ // Sinon c'est qu'il y a une repetion d'un chiffre
                // Recupere l'unite de l'entier qui est l'entier a repeter
                int unite = entier%10;
                // Recupere le nombre de fois qu'il faut repeter l'entier unite
                int new_cpt = (entier-unite)/10;
                while(new_cpt != 0){
                    // Met unite le nombre de fois necessaire
                    fprintf(f_output, "%d", unite);
                    new_cpt--;
                }
            }
        }else{
            // Si le scanf recuperant l'entier n'a pas reussi a trouver d'entier alors on met dans le fichier le caractere une seule fois car il n'y a pas de repetition de celui-ci
            if (scan_int == 0){
                fprintf(f_output, "%c", carac);
            }else{ // Sinon on met dans le fichier f_output le caractere le nombre de fois donne par l'entier
                while(entier != 0){
                    fprintf(f_output, "%c", carac);
                    entier--;
                }
            }
        }
    }
}

