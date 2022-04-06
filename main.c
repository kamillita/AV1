#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char LETRAS[10] = {'A','B','C','D','E', 'F', 'G', 'H', 'I', 'J'};    

int ehNumero(char caractere)
{
    const char *numeros = "0123456789";
    if (strchr(numeros, caractere))
        {
            return 1;
        }
    return 0;
}

const char* toUpperCase(char string[1000]) {
  char* saida = calloc(1000, sizeof(char));
  
  strcpy(saida, string);
  for(int i = 0; string[i]; i++){
    saida[i] = (string[i]);
  }

  return saida;
}

int acharPosicao(char * array, char caracter) {
  int i = 0;

  for(i = 0; i < strlen(array);i++) {
    if(array[i] == caracter) {
      return i;
    }
  }
  
  return i;
}

const char* encodeNumeros(char string[1000]) {
  // Alocar memoria para 
  char* saida = calloc(1000, sizeof(char));

  int i;
  for (i = 0; i < strlen(string); i++) {
    if( string[i] == 'Z') {
      strncat(saida, "Z", 1); 
    }
    
    // Se for digito: eh convertido em um par de letras sendo a primeira um Z e a segunda uma letra
    if(ehNumero(string[i]) == 1){
      strncat(saida, "Z", 1);
      strncat(saida, &LETRAS[atoi(&string[i])], 1);
    } 
    // Se nao for: apenas adiciona na string de saida
    else {
      strncat(saida, &string[i], 1);
    }
  }

  return saida;
}

const char* encodeLetras(char string[1000]) {
  // Alocar memoria
  char* saida = calloc(1000, sizeof(char));

  int i = 0;
  int j = 0;
  int contador = 0;
  
  while ( i < strlen(string)){
    for (j = i; j < strlen(string); j++) {
      // Conta a quantidade de letras repetidas seguidas
      if( string[i] == string[j]) {
        contador++;
      }
      // Se a próxima letra for diferente, quebra o iterador
      else{
        break;
      }
      
    }

    if(contador > 1) {
      // Transforma o contador de repetidos em string
      char texto_numero[5];
      sprintf(texto_numero, "%d", contador);  
      // Adiciona a quantidade de letras na saida
      strncat(saida, texto_numero, 1);
    }


    // Adiciona a letra na saida
    strncat(saida, &string[i], 1);

    // Pula pra próxima letra que ainda não foi contada
    if(contador == 1) {
      i++;
    } else {
      i = i + contador;
    }

    contador = 0;
  }

  return saida;
}

const char* decodeLetras(char string[1000]) {
  // Alocar memoria
  char* saida = calloc(1000, sizeof(char));


  int j = 0;
  int i;
  while(j < strlen(string)){
    if((ehNumero(string[j]) == 1) && ((j + 1) < strlen(string))){
      for(i = 0; i < atoi(&string[j]); i++){
        strncat(saida, &string[j + 1], 1);
      }

      j = j + 2;
    } else {
      strncat(saida, &string[j], 1);
      j++;
    }
  }

  return saida;
}

const char* decodeNumeros(char string[1000]) {
  // Alocar memoria
  char* saida = calloc(1000, sizeof(char));

  int 
  i = 0;
  while(i < strlen(string)){
    if( string[i] == 'Z' && ((i + 1) < strlen(string))) {
      // Se o proximo caracter for Z, adiciona apenas um Z
      if(string[i + 1] == 'Z') {
        strncat(saida, "Z", 1); 
        i = i + 2;
      }
      // Se o proximo caracter 
      else{
        char posicao_letra_string[2];
        int posicao_letra_numero = acharPosicao(LETRAS, string[i + 1]);
        sprintf(posicao_letra_string, "%d", posicao_letra_numero); 
        strncat(saida, posicao_letra_string, 1);
        i = i + 2;
      }
    } else {
      strncat(saida, &string[i], 1);
      i++;
    }
  }

  return saida;
}

int main(void) {
  char codigo[1];
  char entrada[1000];
  char saida[1000];
  
    printf("Digite C para codificar e D para decodificar: ");
    scanf("%s", &codigo);
    
    printf("Informe o código que deseja usar: ");
    scanf("%s", &entrada);

  if(codigo[0] == 'C'){
    strcpy(saida, toUpperCase(entrada));
    strcpy(saida, encodeNumeros(saida));
    strcpy(saida, encodeLetras(saida));
    printf("Saida: %s", saida);
  }

  if(codigo[0] == 'D'){
    strcpy(saida, toUpperCase(entrada));
    strcpy(saida, decodeLetras(saida));
    strcpy(saida, decodeNumeros(saida));
    printf("Saida: %s", saida);
  }
  
  return 0;
}
