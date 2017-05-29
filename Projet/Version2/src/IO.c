#include "IO.h"

void test_IO(){
  dict_index_t index ;
  
  int lg = 9 ;
  uint8_t *binarray = malloc(8 * sizeof(uint8_t));
  
  uint8_t *buffer = malloc(8 * sizeof(uint8_t));
  int *lg_buf = malloc(sizeof(int)) ;
  *lg_buf = 0 ;

  FILE* f = fopen("output/test.txt", "wb");

  index = 97 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(f, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 98 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(f, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 99 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(f, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 100 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(f, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 259 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(f, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 100 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(f, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  index = 256 ;
  printf("Source : %" PRIu8 "\n", index);  
  binarray = dec_to_binarray(index, lg);
  printf("Version binaire :\t"); fprintf_binarray(stdout, binarray, lg); printf("\n");
  fprintf_index(f, buffer, lg_buf, binarray, lg);
  fprintf(stdout, "\nContenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");

  fflush_index(f, buffer, *lg_buf);

  fclose(f) ;

  printf("\n**********\n\n");

  f = fopen("output/test.txt", "rb");

  uint8_t* buffer_fread = malloc(8 * sizeof(uint8_t)) ;
  int* buffer_fread_length = malloc(sizeof(int)) ;
  *buffer_fread_length = 0 ;
  uint8_t* index_fread = malloc(9 * sizeof(uint8_t)) ;
  int index_fread_length = 9 ;


  for (int i = 0; i < 7; i++){

    // printf("On recupere %d bit(s)\n", index_fread_length);
    fread_index(f, buffer_fread, buffer_fread_length, index_fread, index_fread_length);
    printf("On a recupere dans index : "); fprintf_binarray(stdout, index_fread, index_fread_length);printf("\n");
    printf("Cela donne : %hi \n", binarray_to_dec(index_fread, index_fread_length)); 
    printf("Contenu du buffer : "); fprintf_binarray(stdout, buffer_fread, *buffer_fread_length);printf("\n");
    printf("\n");
  }

  fclose(f);



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

// Resultat systematiquement de taille 8
uint8_t* byte_to_binarray(const uint8_t* byte){

  // int offset, bit, count;

  // count = 0;
  uint8_t* array = malloc(8 * sizeof(uint8_t));


  // if ( array == NULL ){
  //   exit(EXIT_FAILURE);
  // }

  // for (offset = 7 ; offset >= 0 ; offset--){

  //   bit = 8 >> offset;

  //   if (bit & 1){
  //     *(array+count) = 1 ;
  //   }
  //   else{
  //     *(array+count) = 0 ;
  //   }

  //   count++;
  // }
  // #ifdef DEBUG
  // printf("On renvoit ");fprintf_binarray(stdout,array, 8);printf("\n");
  // #endif

  for (int i = 0; i < 8; i++){
    array[7 - i] = (*byte & (1 << i)) >> i;
  }

  return  array; 
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

// Parametre systematiquement de taille 8
uint8_t* binarray_to_byte(const uint8_t* array){
  uint8_t *byte = malloc(sizeof(uint8_t));
  *byte = 0; 

  for(int i = 0 ; i < 8 ; i++){
    *byte = (*byte << 1) + array[i] ;
  }
  return byte ;
} 


void fprintf_index (FILE* f, uint8_t* current_buffer, int* buffer_length, const uint8_t* index, const int index_length){

  uint8_t* writing_byte ;

  uint8_t* writing_buffer = malloc(8*sizeof(uint8_t)) ; // Buffer de 8 uint8_t pour fwrite
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
  fprintf(stdout, "On va ecrire :\t"); fprintf_binarray(stdout, writing_buffer, 8); fprintf(stdout, "\n");
  #endif
  writing_byte = binarray_to_byte(writing_buffer);
  if (fwrite(writing_byte, 1, 1, f) < 1){
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
    fprintf(stdout, "On va ecrire :\t"); fprintf_binarray(stdout, writing_buffer, 8); fprintf(stdout, "\n");
    #endif
    writing_byte = binarray_to_byte(writing_buffer);
    if (fwrite(writing_byte, 1, 1, f) < 1){
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

  uint8_t* writing_byte ;

  if (buffer_length != 0){
    #ifdef DEBUG
    fprintf(stdout, "On va ajouter %i bit(s) de padding\n", 8 - buffer_length);
    #endif
    
    // On place les 0s de padding a la fin du buffer
    for (int i = buffer_length; i < 8 - buffer_length; i++){
      current_buffer[i] = 0 ;
    }

    // On ecrit ce buffer
    #ifdef DEBUG
    fprintf(stdout, "FF : On va ecrire :\t"); fprintf_binarray(stdout, current_buffer, 8); fprintf(stdout, "\n");
    #endif
    writing_byte = binarray_to_byte(current_buffer);
    if (fwrite(writing_byte, 1, 1, f) < 1){
      #ifdef DEBUG
      fprintf(stdout, "Erreur d'ecriture\n");
      #endif
      exit(EXIT_FAILURE);
    }
  }
  #ifdef DEBUG
  else{
    printf("On n'ajoute pas de padding\n");
  }
  #endif

}


void fread_index(FILE* f, uint8_t* current_buffer, int* buffer_length, uint8_t* index, const int index_length){

  uint8_t* reading_byte = malloc(sizeof(uint8_t)); // octet pour fread
  uint8_t* reading_buffer = malloc(8*sizeof(uint8_t)) ; // Buffer de 8 uint8_t pour fread
  int bits_to_write ; // Nombre de bits restant a ecrire dans index

  int written_bits = 0 ; // Nombre de bits ecrits dans index
  int first_bit_remaining_in_reading_buffer = 1 ; // Le premier bit restant dans reading_buffer n'ayant pas ete copie dans index
  int bits_remaining = 0 ; // Le nombre de bits restant dans reading_buffer n'ayant pas ete copies dans index
  int written_bits_from_reading_buffer = 0 ; // Le nombre de bits ecrits dans index depuis l'octet lu et en cours de traitement 

  // On recopie current_buffer dans index[0 .. buffer_length]
  for (int i = 0; i < *buffer_length ; ++i){
    index[i] = current_buffer[i] ;
  }
  written_bits = *buffer_length ;



  // Tant que index n'est pas remplit 
  while(written_bits < index_length){

    bits_to_write = index_length - written_bits ;

    // On recupere un octet depuis le fichier 
    if(fread(reading_byte, 1, 1, f) == 0){
      printf("ERREUR LECTURE\n");
      exit(EXIT_FAILURE);
    }
    reading_buffer = byte_to_binarray(reading_byte);

    #ifdef DEBUG
    printf("On a lu ");fprintf_binarray(stdout, reading_buffer, 8);printf("\n");
    #endif

    // On recopie cet octet dans index
    written_bits_from_reading_buffer = 0 ;
    first_bit_remaining_in_reading_buffer = 0 ;
    for (int i = 0 ; i < bits_to_write && i < 8 ; i++){
      index[written_bits + i] = reading_buffer[i] ;
      first_bit_remaining_in_reading_buffer++ ;
      written_bits_from_reading_buffer++ ;
    }
    written_bits += written_bits_from_reading_buffer ;
  }

  // On recopie le reste du dernier octet lu et on le place dans current_buffer
  bits_remaining = 8 - first_bit_remaining_in_reading_buffer ;
  for (int i = 0; i < bits_remaining ; ++i){
    current_buffer[i] = reading_buffer[first_bit_remaining_in_reading_buffer + i] ;
  }
  *buffer_length = bits_remaining ;
}