#include "IO.h"

void test_IO(){
  dict_index_t index = 97 ;
  int lg = 9 ;
  uint8_t *binarray ;  
  
  uint8_t *buffer = malloc(8 * sizeof(uint8_t));
  int *lg_buf = malloc(sizeof(int)) ;
  *lg_buf = 0 ;

  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(stdout, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 98 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(stdout, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 99 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(stdout, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 100 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(stdout, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 259 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(stdout, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 100 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(stdout, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 256 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(stdout, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");


  fflush_index(stdout, buffer, *lg_buf);

}



uint8_t* dec_to_binarray(const dict_index_t n, const int array_length){

  int offset, bit, count;
  uint8_t *pointer;

  count = 0;
  pointer = (uint8_t*) malloc(array_length * sizeof(uint8_t));


  if ( pointer == NULL ){
    exit(EXIT_FAILURE);
  }

  for (offset = array_length-1 ; offset >= 0 ; offset--){

    bit = n >> offset;

    if (bit & 1){
      *(pointer+count) = 1 ;
    }
    else{
      *(pointer+count) = 0 ;
    }

    count++;
  }

  return  pointer;
}

void fprintf_binarray (FILE* f, const uint8_t *binarray, const int array_length){

  for (int i = 0; i < array_length; ++i){
    fprintf(f, "%" PRIu8 "",binarray[i]);
  }
}

dict_index_t binarray_to_dec(const uint8_t* array, const int array_length){

  dict_index_t res = 0 ; 

  for(int i = 0 ; i < array_length ; i++){
    res = (res << 1) + array[i] ;
  }

  return res ;

}

void fprintf_index (FILE* f, uint8_t* current_buffer, int* buffer_length, const uint8_t* index, const int index_length){



  // Buffer de 8 uint8_t pour fwrite
  uint8_t* writing_buffer = malloc(8*sizeof(uint8_t)) ;
  int to_write_from_index = 8 - *buffer_length ; // Le nombre de bits a recuperer dans index et a ajouter dans buffer
  int remaining_in_index = 0 ; // Nombre de bits significatifs encore presents dans index
  int first_bit_remaining_in_index = 0 ; // numero du premier bit significatif encore present dans index
  if (writing_buffer == NULL){
    exit(EXIT_FAILURE);
  }

  // Recopie du buffer precedent dans le buffer a ecrire
  for (int i = 0; i < *buffer_length; i++){
    writing_buffer[i] = current_buffer[i] ;
  }

  // On complete le buffer a ecrire avec l'index
  for (int i = 0 ; i < to_write_from_index ; i++){
    // On ecrit index[0 .. 8 - buffer_length] dans writing_buffer[buffer_length .. 8]
    // #ifdef DEBUG
    // fprintf(stdout, "writing_buffer[%d] <- index[%d] = %u\n", *buffer_length + i, i, index[i]);
    // #endif
    writing_buffer[*buffer_length + i] = index[i] ;
  }

  // On ecrit ce premier buffer
  #ifdef DEBUG
  fprintf(stdout, "On va ecrire :\t\t"); fprintf_binarray(stdout, writing_buffer, 8); fprintf(stdout, "\n");
  #endif
  if (fwrite(writing_buffer, 1, 8, f) < 1){
    #ifdef DEBUG
    fprintf(stdout, "Erreur d'ecriture\n");
    #endif
    exit(EXIT_FAILURE);
  }


  
  // On verifie s'il reste (dans index) de quoi remplir completement un buffer d'ecriture
  // Si oui on l'ecrit
  remaining_in_index = index_length - (to_write_from_index);
  first_bit_remaining_in_index = (to_write_from_index) ;
  while (remaining_in_index >= 8){
    // On recopie index[first_bit_remaining_in_index .. first_bit_remaining_in_index + 7] dans writing_buffer  
    for (int i = 0; i < 8; i++){
      writing_buffer[i] = index[first_bit_remaining_in_index + i] ;
    }
    // On indique que l'on a ecrit 8 bits de plus de l'index
    first_bit_remaining_in_index += 8 ;
    remaining_in_index -= 8 ;

    // On ecrit ce buffer
    #ifdef DEBUG
    fprintf(stdout, "On va ecrire :\t\t"); fprintf_binarray(stdout, writing_buffer, 8); fprintf(stdout, "\n");
    #endif
    if (fwrite(writing_buffer, 1, 1, f) < 1){
      #ifdef DEBUG
      fprintf(stdout, "Erreur d'ecriture\n");
      #endif
      exit(EXIT_FAILURE);
    }
  }


  // On recopie les bits restants de l'index vers le buffer courant
  *buffer_length = index_length - first_bit_remaining_in_index ;
  for (int i = 0; i < *buffer_length ; i++){
    // On recopie index[first_bit_remaining_in_index .. buffer_length] dans index
    current_buffer[i] = index[first_bit_remaining_in_index + i];
  }
  
}

void fflush_index (FILE* f, uint8_t* current_buffer, const int buffer_length){

  #ifdef DEBUG
  fprintf(stdout, "On va ajouter %i bit(s) de padding\n", 8 - buffer_length);
  #endif
  
  if (buffer_length != 0){
    // On place les 0s de padding a la fin du buffer
    for (int i = buffer_length; i < 8 - buffer_length; i++){
      current_buffer[i] = 0 ;
    }

    // On ecrit ce buffer
    #ifdef DEBUG
    fprintf(stdout, "On va ecrire :\t\t"); fprintf_binarray(stdout, current_buffer, 8); fprintf(stdout, "\n");
    #endif
    if (fwrite(current_buffer, 1, 8, f) < 1){
      #ifdef DEBUG
      fprintf(stdout, "Erreur d'ecriture\n");
      #endif
      exit(EXIT_FAILURE);
    }
  }

}
