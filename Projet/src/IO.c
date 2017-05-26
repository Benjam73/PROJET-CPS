#include "IO.h"

void test_IO(){
  int lg = 9 ;
  dict_index_t index = 256 ;
  uint8_t *binarray ;  


  printf("Source : %" PRIu8 "\n", index);  

  binarray = dec_to_binarray(index, lg);
  fprintf_binarray (stdout, binarray, lg);printf("\n");

  printf("Resultat : %" PRIu8 "\n",binarray_to_dec(binarray, lg));
}



uint8_t* dec_to_binarray(dict_index_t n, int array_length){

  int offset, bit, count;
  uint8_t *pointer;

  count = 0;
  pointer = (uint8_t*) malloc(sizeof(n));


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

void fprintf_binarray (FILE* f, uint8_t *binarray, const int array_length){

  for (int i = 0; i < array_length; ++i){
    fprintf(f, "%" PRIu8 "",binarray[i]);
  }
}

dict_index_t binarray_to_dec(uint8_t* array, int array_length){

  dict_index_t res = 0 ; 

  for(int i = 0 ; i < array_length ; i++){
    res = (res << 1) + array[i] ;
  }

  return res ;

}