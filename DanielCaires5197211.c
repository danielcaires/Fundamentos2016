#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void escreve_pixel(FILE *fp){
	fprintf(fp,"100 0 0 ");
}

float derivada_numerica(float fsoma, float fdif, float h){
	/*recebe f(x+h), f(x-h) e h, respectivamente. E retorna a aproximacao da derivada de f em x*/
	float derivada;
	printf("%f \n",fsoma);
	derivada = (fsoma-fdif)/(2*h);

	return(derivada);
}

float distancia(float x1, float y1, float x2, float y2){
	/*Retorna a distancia entre os pontos (x1,y1) e (x2,y2)*/
	float resultado;
	resultado = sqrt(pow((x1-x2),2)+pow((y1-y2),2));

	return(resultado);
}

float determinante_22(float matriz[2][2]){
	/*Retorna o determinante de uma matriz 2x2*/
	float determinante;
	determinante = (matriz[0][0]*matriz[1][1])-(matriz[0][1]*matriz[1][0]);

	return(determinante);
}

int inverte_22(float matriz [2][2], float inversa[2][2]){
	/*recebe uma matriz 2x2 e atribui sua inversa ao segundo parametro*/
	float determinante;

	determinante = determinante_22(matriz);
	if(determinante!=0){
		inversa[0][0] = (matriz[1][1])/determinante;
		inversa[1][1] = (matriz[0][0])/determinante;
		inversa[0][1] = (-1*(matriz[0][1]))/determinante;
		inversa[1][0] = (-1*(matriz[1][0]))/determinante;
		return(1);
	} else {
		return(0);
	}
}

int main(){
	/*declara as variaveis*/
  int teste, itmax, linhas, colunas, i, j;
  float a, b, c, d, h, epsilon;
  FILE * arquivo;
  float varteste[2][2];
  int cores[20][3] ={{0, 100, 80},{80, 0, 100},{100, 80, 0},{0, 80, 100},{100, 0, 80},{80, 100, 0},{0, 100, 100},{100, 0, 100},{100, 100, 0},
  									{0, 80, 80},{80, 0, 80},{80, 80, 0},{0, 0, 80},{0, 80, 0},{80, 0, 0},{0, 0, 100},{0, 100, 0},{100, 0, 0},{200, 200, 200},
  									{0, 80, 80}};
  								
  float matriz[2][2] = {1,0,0,2}; //variavel de teste
  int indice;


  /*le o arquivo e preenche as variaveis*/
  arquivo = fopen("entrada.txt","r");
  fscanf(arquivo, "%d %f %f %f %f %e %d %e %d %d", &teste, &a, &b, &c, &d, &h, &itmax, &epsilon, &linhas, &colunas);
  fclose(arquivo);

  /*Cria o arquivo de imagem e preenche o cabecalio*/
 	arquivo = fopen("imagem.ppm","w");
 	fprintf(arquivo,"P3 %d %d 255\n", colunas, linhas);
 	
  /*itera a regiao do dominio a ser estudada*/
  for(i=0;i<linhas;i++){
  	for(j=0;j<colunas;j++){
  		indice = (i/(linhas/20))%20;    /*---ATENCAO--- Teste de cores, apagar */
  		fprintf(arquivo, "%d %d %d ", cores[indice][0], cores[indice][1], cores[indice][2]);
  	}
  }

  fclose(arquivo);
  printf("Finalizado \n");

  return(0);
}
