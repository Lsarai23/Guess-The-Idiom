/* Integrantes:
 * Lucas Pires de Camargo Sarai - 10418013
 * Vitor Alves Pereira - 10410862
 * 
 * Ciência da Computação
 * 3D
 * Projeto e Analise de Algoritmos 1
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Encontrar o indice do elemento no vetor
int getIndex(char v[], char e) { // O(n)
  for (int i = 0; v[i] != '\0'; i++) {
    if (v[i] == e)
      return i;
  }
  return -1;
}

/* merge: combina os subarrays realizando a ordenação */
void merge(char content[], char left[], int lengthLeft, char right[],
           int lengthRight) { // O(n)
  int idxLeft = 0;
  int idxRight = 0;
  int idxMain = 0;

  // Condição 1: comparação entre quem vem antes e adiciona no vetor
  while (idxLeft < lengthLeft && idxRight < lengthRight) {

    // Condição 2: caso o elemento da esquerda venha antes

    if (left[idxLeft] <= right[idxRight]) {
      content[idxMain] = left[idxLeft++];

    } else {
      content[idxMain] = right[idxRight++];
    }

    idxMain++;
  }

  // Adicionando elementos restantes
  while (idxLeft < lengthLeft) {
    content[idxMain++] = left[idxLeft++];
  }
  while (idxRight < lengthRight) {
    content[idxMain++] = right[idxRight++];
  }
}

/* merge_sort: ordenação de um vetor de caracteres. */
void merge_sort(int length, char content[]) { // O(n log n)
  if (length < 2)
    return;

  int middle = length / 2;
  int nLeft = middle;
  int nRight = length - middle;

  char left[nLeft], right[nRight];

  // Copia os elementos para os vetores temporários
  for (int i = 0; i < nLeft; i++) {
    left[i] = tolower(content[i]);
  }

  for (int i = 0; i < nRight; i++) {
    right[i] = tolower(content[middle + i]);
  }

  merge_sort(nLeft, left);
  merge_sort(nRight, right);
  merge(content, left, nLeft, right, nRight);
}

// Calcular a frequência da letra no texto
float getFrequency(char el, char input[], int length) { // O(n)
  int count = 0;
  float freq = 0.0f;
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == el) count++;
  }
  freq = (float)count/ (float)length;
  return freq;
}
// Calcular o tamho exato da entrada
int getLength(char input[]) { // O(n)
  int count;
  for (count = 0; input[count] != '\0'; count++);
  return count;
}

// Adivinhar a palavra
int guess(char input[], int length) { // O(n)
  char alfb[] = "abcdefghijklmnopqrstuvwxyz";
  // Probabilidade de cada letra, arredondadas para formar inteiros
  // OBS: As probabilidades quem fossem mesmo que minimamente maiores, foram
  // arrendondadas para cima, e para baixo caso fossem menores Isso facilita na
  // comparacao, diferenciando mais as probabilidades
  int probsPort[] = {15, 1,  4, 5, 12, 1, 1, 1, 6, 1, 0, 2, 5,
                     5,  11, 3, 2, 7,  8, 4, 5, 2, 0, 1, 0, 1};
  int probsIng[] = {8, 2, 2, 4, 13, 3, 3,  7, 7, 0, 1, 5, 2,
                    7, 7, 1, 0, 5,  6, 10, 2, 0, 3, 0, 2, 0};
  int pC = 0, iC = 0, probPortEl = 0, probIngEl = 0, indexEl,
      readInd = 0;
  float freqEl, difP, difI;
  char readEls[length];

  merge_sort(length, input); // Ordenar

  // Para cada elemento, calcular sua frequência e ,comparar as probabilidades
  // de cada idioma. OBS: Evita calcular elementos repetidos
  for (int i = 0; input[i] != '\0'; ++i) {
    char current = input[i];
    if ((current >= 97 && current <= 122) && getIndex(readEls, current) == -1 ) {
      indexEl = getIndex(alfb, current); // Posição no alfabeto

      probPortEl = probsPort[indexEl]; // Probabilidade em portugûes
      probIngEl = probsIng[indexEl];   // Probabilidade em inglês
      freqEl = getFrequency(current, input,
                            length); // Frequência do elemento na entrada
      freqEl *=100; //Ajustando para porcentagem
      readEls[readInd++] = current; // Adiciona no vetor de elementos lidos
     
      // Procura o idioma de frequência mais próxima
      difP = probPortEl - freqEl;
      if(difP < 0) difP *= -1;
      difI = probIngEl - freqEl;
      if(difI < 0) difI *= -1;

      //Aumenta o contador de acordo com o idioma com menor diferença
      if (difP <= difI){
        pC++;
      }else{
        iC++;
      }
    }
  }
  //Retorna o idioma de maior contador
  if (pC >= iC) 
    return 1;
  else
    return 0;
}

int main(void) {
  char input[50000];
  printf("Insira um texto:\n");
  fgets(input, 50000, stdin);
  
  //Removendo o caractere de fim de linha
  int i;
  for(i = 0; input[i] != '\n'; i++);
  input[i] = '\0';

  //Análise
  int length = getLength(input);
  if (guess(input, length) == 1)
    printf("\n\nIdioma: Português\n");
  else
    printf("\n\nIdioma: Inglês\n");

  return 0;
}