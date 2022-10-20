#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<math.h>

int quantLinhasTab = 20;
int quantColunasTab = 30;
char tabuleiro[20][30];
int cobra[8][2];
int controlePosiCabeca[2];
int colunaFruta = 3;
int linhaFruta = 2;
int x,y,i,pontos,tamCobra = 3;
char tCIMA = 119;
char tBAIXO = 115;
char tDIREITA = 100;
char tESQUERDA = 97;
char tecla;

inicializarCobra(){
	
	cobra[0][0] = 6;
	cobra[1][0] = 5;
	cobra[1][1] = 6;
	cobra[2][0] = 4;
	cobra[2][1] = 6;
	cobra[0][1] = 6;
 	controlePosiCabeca[0] = cobra[0][0];
 	controlePosiCabeca[1] = cobra[0][1];
}

gerarNovaFruta(){
	
	colunaFruta = (rand() %  (quantColunasTab - 2)) + 1;
	
	linhaFruta = (rand() %  (quantLinhasTab - 2)) + 1;
	
}

capturarTecla(){
	
	char teclaPress;
	
	if(kbhit()){
		teclaPress = getch();
	}
	
	if(teclaPress == tCIMA || teclaPress == tBAIXO || teclaPress == tDIREITA || teclaPress == tESQUERDA){
		tecla = teclaPress;
	}
}

moverCobra(){
	
	i = tamCobra;

	//comando w no teclado
	if(tecla == tCIMA){
		if(cobra[0][1] > 1){
			controlePosiCabeca[1] = cobra[0][1] - 1;
		}
		else{
			controlePosiCabeca[1] = quantLinhasTab - 2;
		}
		controlePosiCabeca[0] = cobra[0][0];	
	}
	
	//comando s no teclado
	if(tecla == tBAIXO){
		if(cobra[0][1] < quantLinhasTab - 2){
			controlePosiCabeca[1] = cobra[0][1] + 1;
		}
		else{
			controlePosiCabeca[1] = 1;
		}
		controlePosiCabeca[0] = cobra[0][0];
	}
	
	//comando a no teclado
	if(tecla == tESQUERDA){
		if(cobra[0][0] > 1){
			controlePosiCabeca[0] = cobra[0][0] - 1;
		}
		else{
			controlePosiCabeca[0] = quantColunasTab - 2;
		}
		controlePosiCabeca[1] = cobra[0][1];
	}
	
	//comando d no teclado
	if(tecla == tDIREITA){
		if(cobra[0][0] < quantColunasTab - 2){
			controlePosiCabeca[0] = cobra[0][0] + 1;
		}
		else{
			controlePosiCabeca[0] = 1;
		}
		controlePosiCabeca[1] = cobra[0][1];
	}
	
		
	for(i;i>1;i--){
		cobra[i-1][0] = cobra[i-2][0];
		cobra[i-1][1] = cobra[i-2][1];
	}
	
	cobra[0][0] = controlePosiCabeca[0];
	cobra[0][1] = controlePosiCabeca[1];
}

verificarSeFrutaFoiComida(){
	if(cobra[0][0] == colunaFruta && cobra[0][1] == linhaFruta){
		pontos = pontos + 1;
		tamCobra = tamCobra + 1;
		gerarNovaFruta();
	}
}

gerarTabuleiro(){
	for (y = 0; y < quantLinhasTab; y++){
		for (x = 0; x < quantColunasTab; x++){
			if( y == 0 || y == quantLinhasTab - 1 || x == 0 || x == quantColunasTab - 1){
				tabuleiro[y][x] = 177;
			}
			else if(y == linhaFruta && x == colunaFruta){
				tabuleiro[y][x] = 208;
			}
			else{
				tabuleiro[y][x] = ' ';
			}
		}
	}
	
	for(i = 0; i < tamCobra; i++){
		y = cobra[i][1];
		x = cobra[i][0];
		tabuleiro [y][x] = 220;
	}
}


imprimirTabuleiro(){
	system("cls");
	
	printf("Pontos: %d \n",pontos);	
	
	for (y = 0; y < quantLinhasTab; y++){
		for (x = 0; x < quantColunasTab; x++){
			printf("%c",tabuleiro[y][x]);
		}
		printf("\n");
	}
}

iniciarJogo(){
	
	inicializarCobra();
	
	while (1){
		capturarTecla();
		moverCobra();
		verificarSeFrutaFoiComida();
		gerarTabuleiro();
		imprimirTabuleiro();
		sleep(0.5);
	}
}

int main(){
	
	
		
	iniciarJogo();
	
	
	
	
	
		
}
