#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include <conio.h>
#include <windows.h>
#include<unistd.h>
#include <math.h>

int x,y,i,pontos=0;
int tamanhoX = 40;
int tamanhoY = 20;
int xCobra = 5;
int yCobra = 3;
int xFruta = 9;
int yFruta = 6;
char tecla,teclaPress;


imprimir_tela(){
	printf("Pontos: %d \n",pontos);
	
	for (y = 0; y < tamanhoY; y++){
		for (x = 0; x < tamanhoX; x++){
			if( y == 0 || y == tamanhoY-1 || x==0 || x==tamanhoX-1){
				printf("%c",177);
			}
			else{
				if(y == yCobra && x == xCobra){
					printf("%c",220);
				}
					
				else if(y == yFruta && x == xFruta){
					printf("%c",208);
				}
				else{
					printf(" ");	
				}
			}
		}
		printf("\n");
	}
	
	
	system("cls");
}

mover_para_cima(){
	if(yCobra>1){
		yCobra = yCobra-1;
	}
	else{
		yCobra = tamanhoY-2;
	}
}

mover_para_baixo(){
	if(yCobra<tamanhoY-2){
		yCobra = yCobra+1;
	}
	else{
		yCobra = 1;
	}
}

mover_para_direita(){
	if(xCobra<tamanhoX-2){
		xCobra = xCobra+1;
	}
	else{
		xCobra=1;
	}
}

mover_para_esquerda(){
	if(xCobra>1){
		xCobra = xCobra-1;
	}
	else{
		xCobra= tamanhoX-2;
	}

}

captura_tecla(){
	if(kbhit()){
		teclaPress = getch();
	}
}

validacao_tecla(){
	if(teclaPress==119 ||teclaPress==97 ||teclaPress==100 ||teclaPress==115){
		tecla=teclaPress;
	}
}

movimentar_cobra(){
	
	if(tecla==119){//w
		mover_para_cima();	
	}
	if(tecla==97){//a
		mover_para_esquerda();
	}
	if(tecla==100){//d
		mover_para_direita();
	}
	if(tecla==115){//s
		mover_para_baixo();
	}
	
}

recriar_fruta(){
	xFruta=rand()% (tamanhoX-1);
	
	if(xFruta==1){
		xFruta=rand()% (tamanhoX-1);
		}
	
	yFruta=rand()% (tamanhoY-1);
	if(yFruta==1){
		yFruta=rand()% (tamanhoX-1);
	}
}

verificar_se_fruta_foi_comida(){
	if(xCobra==xFruta && yCobra==yFruta){
		pontos=pontos+1;
		recriar_fruta();
	}
}


iniciar_jogo(){
	
	while(i=1){
		imprimir_tela();
		captura_tecla();
		validacao_tecla();
		movimentar_cobra();
		verificar_se_fruta_foi_comida();
		}
}


int main(){

	iniciar_jogo();
	
	
}
