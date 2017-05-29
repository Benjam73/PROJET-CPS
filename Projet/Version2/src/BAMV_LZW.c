#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "LZW.h"





// Retourne : 
//   0 si tout s'est bien passé
//   -1 si l'appel n'etait pas correct ou que l'utilisateur a demandé de l'aide
//   1 si un des arguments n'etait pas un fichier valable
int main(int argc, char *argv[]){

	int argument_aide = false, comp = false, decomp =false ;
	

	FILE *f_input_c, *f_output_c, *f_input_x, *f_output_x ;

	#ifdef TEST_IO
	test_IO();
	#endif
	
	#ifdef TEST_CHAINE_CARAC
	test_chaine_carac();
	#endif

	for (int i = 1 ; i < argc && !argument_aide ; i++){
		if (strcmp(argv[i], "-h") == 0){
			argument_aide = true ;
		}
	}

	if(argc < 3 || argc > 7 || argument_aide){
		fprintf(stdout, "%s [-c fichier_entree ficher_sortie] [-x fichier_entree ficher_sortie]\n", argv[0]);
		fprintf(stdout, "Arguments : \n\t -c : compression\n\t -x : decompression\n");
		return 1 ;
	}


	// Ouverture fichiers donnes en parametres
	for (int i = 1 ; i < argc && !(comp && decomp) ; i++){
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



	if (comp){
		fprintf(stdout, "On effectue une compression\n");
		compression (f_input_c, f_output_c);
	}

	if (decomp){
		fprintf(stdout, "On effectue une decompression\n");
		decompression (f_input_x, f_output_x);
	}



	if (comp){
		fclose(f_input_c);
		fclose(f_output_c);
	}

	if (decomp){
		fclose(f_input_x);
		fclose(f_output_x);	
	}

	return 0;
}