#include "../include/LZW.h"
#define true 1
#define false 0

int adapter_longueur(uint8_t* w1){
	int lg =0;
	for(int i = 0; i<16; i++){
		if(w1[i] != 0x0){
			lg++;
		}
	}
	return lg;
}

uint8_t* init_vect(){
	uint8_t* tab = malloc(sizeof(uint8_t));
	while(adapter_longueur(tab) != 0){
		tab = malloc(sizeof(uint8_t));
	}
	return tab;
}


void fprintf_n_octets(FILE* f, uint8_t* word, int n){
	for (int i = 0; i < n; i++){
		fprintf(f, "%c", word[i]);  
		#ifdef DEBUG
		fprintf(stdout, " -> On ecrit\n");
		#endif
	}
	fflush(f);
}

void fprintf_n_octets_cpt(FILE* f, int word){
	fprintf(f, "%" PRIu8 "", word);  
		#ifdef DEBUG
	fprintf(stdout, " -> On ecrit\n");
		#endif
	
	fflush(f);
}

int uint8_cmp(uint8_t* tab, char* tab2, int taille){
	int monbool = 1;
	for(int i = 0; i < taille && monbool == 1; i++){
		if(tab[i] != tab2[i]){
			monbool = 0;
		}
	}
	return !monbool;
}

int to_int(uint8_t* tab, int taille){
	int result = 0;
	char tmp;
	for(int i = 0; i < taille; i++){
		tmp = tab[i];
		result += atoi(&tmp);
	}
	return result;
}

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
			if (cpt>1){			
				fprintf(f_output,"%d", cpt);
				fprintf(f_output,"%c", compare);
			}
			else{
				fprintf(f_output,"%c", compare);

			}
			fprintf(f_output, ".");
			compare = courant;
			cpt = 1;
		}
	}
}

void elr (FILE* f_input, FILE* f_output){
	char carac;
	char tmp;
	char tempo = 0;
	char cpttemp;
	int cptres = 0;

	//fread(tmp, 1, 1, f_input);

	int cpt = 0;
	while (!feof(f_input)) {
		cpt = 0;
		fscanf(f_input,"%c", tmp);
		//printf("%d",uint8_cmp(tmp,".",1));
		while(tmp == '.') {
			printf("while2\n");
			cpttemp[cpt] = tmp[0];
			cpt++;
			carac = tmp;
			fscanf(f_input,"%c", tmp);
		}
		for (int i = 0 ; cpt > i; i++ ){
			tempo = cpttemp[i];
			cptres = cptres * 10 + to_int(&tempo, 1);
			printf("for1\n");


		}
		for (; cptres > 0 ; cptres --){
			fprintf_n_octets(f_output,carac, 1);
			printf("for2\n");
		}
		// printf("while1\n");
	}
}

int main(int argc, char *argv[]){

	int argument_aide = false, comp = false, decomp =false ;
	

	FILE *f_input_c, *f_output_c, *f_input_x, *f_output_x ;

	
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
		rle (f_input_c, f_output_c);
	}

	if (decomp){
		fprintf(stdout, "On effectue une decompression\n");
		elr(f_input_x, f_output_x);
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