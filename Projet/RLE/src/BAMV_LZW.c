#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "LZW.h"
#include "RLE.h"

#define true 1
#define false 0



// Retourne : 
//   0 si tout s'est bien passé
//   -1 si l'appel n'etait pas correct ou que l'utilisateur a demandé de l'aide
//   1 si un des arguments n'etait pas un fichier valable
int main(int argc, char *argv[]){

	int argument_aide = false, comp = false, decomp =false, RLE = false, ELR = false ;
	

	FILE *f_input_c, *f_output_c, *f_input_x, *f_output_x, *f_input_r, *f_output_r, *f_input_e, *f_output_e ;

	
	#ifdef TEST_CHAINE_CARAC
	test_chaine_carac();
	#endif

	for (int i = 1 ; i < argc && !argument_aide ; i++){
		if (strcmp(argv[i], "-h") == 0){
			argument_aide = true ;
		}
	}

	if(argc < 3 || argc > 5 || argument_aide){
		fprintf(stdout, "%s [-c fichier_entree ficher_sortie] [-x fichier_entree ficher_sortie]\n", argv[0]);
		fprintf(stdout, "Arguments : \n\t -c : compression\n\t -x : decompression\n\t -r : rle \n\t -e : elr\n" );
		return 1 ;
	}


	// Ouverture fichiers donnes en parametres
	for (int i = 1 ; i < argc && !(comp && decomp && RLE && ELR) ; i++){
		if (strcmp(argv[i], "-c") == 0){
			f_input_c = fopen(argv[i + 1], "rb");
			f_output_c = fopen(argv[i + 2], "wb");
			comp = true ;
		}
		if (strcmp(argv[i], "-x") == 0){
			f_input_x = fopen(argv[i + 1], "rb");
			f_output_x = fopen(argv[i + 2], "wb");
			decomp = true ;
		}
		if (strcmp(argv[i], "-r") == 0){
			f_input_r = fopen(argv[i + 1], "r");
			f_output_r = fopen(argv[i + 2], "w");
			RLE= true ;
		}
		if (strcmp(argv[i], "-e") == 0){
			f_input_e = fopen(argv[i + 1], "r");
			f_output_e = fopen(argv[i + 2], "w");
			ELR = true ;
		}
	}
	// Verifications ouverture fichiers donnes en parametres
	if(comp) {
		if (f_input_c == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher entree compression");
			return 1 ;
		}
		if (f_output_c == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher sortie compression");
			return 1 ;
		}		
	}
	if(decomp){
		if (f_input_x == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher entree decompression");
			return 1 ;
		}
		if (f_output_x == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher sortie decompression");
			return 1 ;
		}
	}
	if(RLE) {
		if (f_input_r == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher entree rle");
			return 1 ;
		}
		if (f_output_r == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher sortie rle");
			return 1 ;
		}		
	}
	if(ELR){
		if (f_input_e == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher entree elr");
			return 1 ;
		}
		if (f_output_e == NULL){
			fprintf(stdout, "%s\n", "Erreur ouverture ficher sortie elr");
			return 1 ;
		}
	}



	if (comp){
		fprintf(stdout, "On effectue une compression\n");
		compression (f_input_c, f_output_c);
	}

	if (decomp){
		fprintf(stdout, "On effectue une decompression\n");
		decompression (f_input_x, f_output_x);
	}
	if (RLE){
		fprintf(stdout, "On effectue un codage RLE\n");
		rle (f_input_r, f_output_r);
	}

	if (ELR){
		fprintf(stdout, "On effectue un décodage ELR\n");
		elr (f_input_e, f_output_e);
	}



	if (comp){
		fclose(f_input_c);
		fclose(f_output_c);
	}

	if (decomp){
		fclose(f_input_x);
		fclose(f_output_x);	
	}
	if (RLE){
		fclose(f_input_r);
		fclose(f_output_r);
	}

	if (ELR){
		fclose(f_input_e);
		fclose(f_output_e);	
	}

	return 0;
}