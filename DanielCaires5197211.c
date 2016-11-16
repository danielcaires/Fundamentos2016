#include <stdio.h>
#include <stdlib.h>

void escreve_pixel(FILE *fp){
	fprintf(fp,"255 0 0 ");
}

int main(){
	/*declara as variaveis*/
  int teste, itmax, linhas, colunas, i, j;
  float a, b, c, d, h, epsilon;
  FILE * arquivo;

  /*le o arquivo e preenche as variaveis*/
  arquivo = fopen("entrada.txt","r");
  fscanf(arquivo, "%d %f %f %f %f %e %d %e %d %d", &teste, &a, &b, &c, &d, &h, &itmax, &epsilon, &linhas, &colunas);
  fclose(arquivo);

 	arquivo = fopen("imagem.ppm","w");
 	fprintf(arquivo,"P3 %d %d 255\n", colunas, linhas);
 	
  /*itera a região do dominio a ser estudada*/
  for(i=0;i<linhas;i++){
  	for(j=0;j<colunas;j++){
  		escreve_pixel(arquivo);
  	}
  	printf("\n");
  }

  fclose(arquivo);
  printf("Finalizado, %d \n", colunas);

  return(0);
}
