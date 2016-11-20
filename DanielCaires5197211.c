/********************************
*Fundamentos de Analise Numerica*
*Aluno: Daniel Oliveira Caires  *
*NUSP: 5197211                  *
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*As funcoes f1, g1, f2, g2, f3, g3 recebem um valor de x e de y 
e retornam o resultado de acordo com as funcoes descritas no enunciado*/
float f1(float x, float y){
	return (pow(x,3)-3*x*pow(y,2)-1);
}
float g1(float x, float y){
	return (3*pow(x,2)*y-pow(y,3));
}
float f2(float x, float y){
	return (pow(x,4)-6*pow(x,2)*pow(y,2)+pow(y,4)-1);
}
float g2(float x, float y){
	return (4*pow(x,3)*y-4*x*pow(y,3));
}
float f3(float x, float y){
	return (cos(3*pow(x,2))*y);
}
float g3(float x, float y){
	return (cos(3*pow(y,2))*x);
}
/*fxy e gxy recebem os valores de x e y e o numero do teste,
de acordo com este numero ela seleciona uma das funcoes acima*/
float fxy(float x, float y, int teste){
	if(teste == 1){return(f1(x,y));}
	if(teste == 2){return(f2(x,y));}
	if(teste == 3){return(f3(x,y));}
}
float gxy(float x, float y, int teste){
	if(teste == 1){return(g1(x,y));}
	if(teste == 2){return(g2(x,y));}
	if(teste == 3){return(g3(x,y));}
}

float derivada_numerica(float fsoma, float fdif, float h){
	/*recebe f(x+h), f(x-h) e h, respectivamente. E retorna a aproximacao da derivada de f em x*/
	float derivada;
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
		/*se o determinante nao for zero, calcula a inversa explicitamente usando seu valor e retorna 1*/
		inversa[0][0] = (matriz[1][1])/determinante;
		inversa[1][1] = (matriz[0][0])/determinante;
		inversa[0][1] = (-1*(matriz[0][1]))/determinante;
		inversa[1][0] = (-1*(matriz[1][0]))/determinante;
		return(1);
	} else {
		/*se o determinante for igual a 0, a matriz nao eh inversivel e a funcao retorna 0*/
		return(0);
	}
}

int proximo_ponto(int teste, float h, float xk, float yk, float *xl, float *yl){
	/*essa funcao recebe o numero do teste, o espacamento para derivada, os pontos da atual iteracao
	e dois ponteiros, de forma que atribua a xl e yl os valores do ponto da proxima iteracao*/
	float matriz[2][2], inversa[2][2];

	/*preenche a matriz das derivadas parciais para o calculo do proximo ponto*/
	matriz[0][0] = derivada_numerica(fxy(xk+h, yk, teste), fxy(xk-h, yk, teste), h);
	matriz[0][1] = derivada_numerica(fxy(xk, yk+h, teste), fxy(xk, yk-h, teste), h);
	matriz[1][0] = derivada_numerica(gxy(xk+h, yk, teste), gxy(xk-h, yk, teste), h);
	matriz[1][1] = derivada_numerica(gxy(xk, yk+h, teste), gxy(xk, yk-h, teste), h);

	if(inverte_22(matriz,inversa)){
		/*Se a funcao inverte_22 retornar 1, calcula-se o proximo ponto e retorna 1*/
		*xl = xk-((inversa[0][0]*fxy(xk, yk, teste))+(inversa[0][1]*gxy(xk, yk, teste)));
		*yl = yk-((inversa[1][0]*fxy(xk, yk, teste))+(inversa[1][1]*gxy(xk, yk, teste)));

		return(1);
	} else {
		/*se a matriz das derivadas nao for inversivel a funcao retorna o valor 0*/
		return(0);
	}	
}

int main(){
	/*declara as variaveis*/
  int teste, itmax, linhas, colunas; /*Vairaveis a serem atribuidas pelo arquivo de entrada*/
  float a, b, c, d, h, epsilon, lambda; /*Vairaveis a serem atribuidas pelo arquivo de entrada*/
  int i, j, k; /*Variaveis auxiliares utilizadas na iteracao de listas ou matrizes*/
  FILE * arquivo;
  int cores[20][3] = {{0, 250, 200},{200, 0, 250},{250, 200, 0},{0, 200, 250},{250, 0, 200},{200, 250, 0},{0, 250, 250},{250, 0, 250},
  									{250, 250, 0},{0, 200, 200},{200, 0, 200},{200, 200, 0},{0, 0, 200},{0, 200, 0},{200, 0, 0},{0, 0, 250},{0, 250, 0},
  									{250, 0, 0},{250, 250, 250},{0, 200, 200}}; /*Lista com o codigo das cores*/
  int iteracoes=0; 
  float xk, yk, xl, yl; /*xk e yk sao as coordenadas do passo atual de iteracao e xl e yl as do proximo passo*/
  float passox, passoy; /*determinam a distancia entre os pontos iniciais das iteracoes*/
  int retorno; /*variavel auxiliar para identificar se as iteracoes devem parar ou nao*/
  float raizes[20][2]; /*matiz que armazena as raizes*/
  int solucoes=0; /*guarda o numero de solucoes encontradas*/
  int novasolucao; /*variavel auxiliar para determinar se a raiz entonrada eh nova (1) ou se ja foi encontrada antes (0)*/


  /*le o arquivo e preenche as variaveis*/
  arquivo = fopen("entrada.txt","r");
  fscanf(arquivo, "%d %f %f %f %f %e %d %e %d %d", &teste, &a, &b, &c, &d, &h, &itmax, &epsilon, &linhas, &colunas);
  fclose(arquivo);
  
  /*Cria o arquivo de imagem e preenche o cabecalio*/
 	arquivo = fopen("imagem.ppm","w");
 	fprintf(arquivo,"P3 %d %d 255\n", colunas, linhas);

  /*itera a regiao do dominio a ser estudada*/
  passox = (b-a)/colunas;
  passoy = (d-c)/linhas;
  for(i=0;i<linhas;i++){
  	for(j=0;j<colunas;j++){
  		iteracoes = 0;
  		retorno = 1;
  		/*determina o ponto inicial do metodo de Newton*/
		  xk = a + j*(passox); 
		  yk = d - i*(passoy);
		  /*verifica se (xk,yk) ja esta proximo de alguma solucao*/
		  for(k=0;k<solucoes;k++){
		  	if(xk-raizes[k][0]<=2*passox && xk-raizes[k][0]>=-2*passox && yk-raizes[k][1]<=2*passoy && yk-raizes[k][1]>=-2*passoy){
		  		/*se o ponto esta a menos de 2 pixels de distancia de uma solucao, 
		  		pinta o ponto de branco e nem calcula a proxima iteracao. Vai para o proximo passo*/
		  		fprintf(arquivo, "255 255 255 ");
		  		retorno = 0;
		  		break;
		  	}
		  }
			while(retorno==1){
				/*Calcula o proximo ponto e contabiliza a iteracao*/
				retorno = proximo_ponto(teste, h, xk, yk, &xl, &yl);
				iteracoes++;
				if(retorno==1){
					/*se a funcao proximo_ponto retornar 1, faz as verificacoes para continuar as iteracoes ou parar*/
					if(distancia(xk, yk, xl, yl)<epsilon){
						/*se a distancia entre os pontos de duas iteracoes for menor que epsilon, determina-se 
						xl e yl como raiz, e pinta o pixel de acordo com a cor adequada*/
						novasolucao=1; /*supoe-se a principio que a solucao encontrada eh nova*/
						for(k=0;k<solucoes;k++){
							/*percorre a lmatriz de raizes verificando se a solucao encontrada ja foi encontrada antes*/
							if(distancia(xl, yl, raizes[k][0], raizes[k][1])<epsilon){
								novasolucao=0;
								break;
							}
						}
						if(novasolucao==1){
							/*Se a solucao for nova, guarda ela na matriz de raizes e contabiliza uma nova solucao*/
							raizes[solucoes][0]=xl;
							raizes[solucoes][1]=yl;
							solucoes++;
						}
						/*usando o indice da matriz de solucoes como referencia, preenche o arquivo de imagem com a cor adequada*/
						lambda = ((float)itmax-(float)iteracoes)/(float)itmax;
						fprintf(arquivo, "%d %d %d ", (int)(cores[k][0]*lambda), (int)(cores[k][1]*lambda), (int)(cores[k][2]*lambda));
						retorno = 0;
					} else if(iteracoes>itmax) {
						/*Se o numero de iteracoes passar do maximo para o algoritimo e imprime a cor preta no ponto*/
						fprintf(arquivo, "0 0 0 ");
						retorno = 0;
						printf("O ponto nao converge em %d iteracoes \n", itmax);
					} else if(xl<a || xl>b || yl<c || yl>d){
						/*Se a proxima iteracao sair da regiao atribuida, para o algoritimo e imprime a cor preta no ponto*/
						fprintf(arquivo, "0 0 0 ");
						retorno = 0;
					} else {
						/*Se nenhum dos casos anteriores acontecer. Continua a iteracao e atribui o proximo passo ao passo atual*/
						xk = xl;
						yk = yl;
					}
				} else {
					/*Se a funcao proximo_ponto retornar 0, a matriz das derivadas parciais nao eh inversivel e o ponto nao converge*/
					fprintf(arquivo, "0 0 0 ");
					retorno = 0;
				}
			}
		}
	}
	fclose(arquivo);
	/*Imprime os resultados*/
	printf("Daniel Oliveira Caires - NUSP: 5197211\n");
	printf("Teste %d feito no intervalo [%f,%f]x[%f,%f] usando %d x %d pontos e precisao %f \n",teste, a, b, c, d, colunas, linhas, epsilon);
	printf("%d raizes encontradas:\n", solucoes);
	for(k=0;k<solucoes;k++){
	  printf("(%f, %f) - Cor:(%d, %d, %d) \n", raizes[k][0], raizes[k][1], cores[k][0], cores[k][1], cores[k][2]);	  
	}
  return(0);
}
