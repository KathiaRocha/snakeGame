#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<math.h>

int quantLinhasTab = 20;
int quantColunasTab = 60;
char tabuleiro[20][60];
int novaPosicaoCabeca[2];
int colunaFruta = 3;
int linhaFruta = 2;
int x,y,pontos,tamCobra;
int cobra[15][2];
char tCIMA = 119;
char tBAIXO = 115;
char tDIREITA = 100;
char tESQUERDA = 97;
char tecla;
int estaJogoFinalizado = 0; 

inicializarCobra(){
	
	tamCobra = 3;
	
	cobra[0][1] = 7;
	cobra[0][0] = 6;
	cobra[1][1] = 7;
	cobra[1][0] = 5;
	cobra[2][1] = 7;
	cobra[2][0] = 4;
	
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
	
	//para impedir que a cobra movimente antes de uma tecla ser acionada.
	if(tecla==0){
		return 1;
	}
	
	//comando w no teclado
	if(tecla == tCIMA){
		if(cobra[0][1] > 1){
			novaPosicaoCabeca[1] = cobra[0][1] - 1;
		}
		else{
			novaPosicaoCabeca[1] = quantLinhasTab - 2;
		}
		novaPosicaoCabeca[0] = cobra[0][0];	
	}
	
	//comando s no teclado
	else if(tecla == tBAIXO){
		if(cobra[0][1] < quantLinhasTab - 2){
			novaPosicaoCabeca[1] = cobra[0][1] + 1;
		}
		else{
			novaPosicaoCabeca[1] = 1;
		}
		novaPosicaoCabeca[0] = cobra[0][0];
	}
	
	//comando a no teclado
	else if(tecla == tESQUERDA){
		if(cobra[0][0] > 1){
			novaPosicaoCabeca[0] = cobra[0][0] - 1;
		}
		else{
			novaPosicaoCabeca[0] = quantColunasTab - 2;
		}
		novaPosicaoCabeca[1] = cobra[0][1];
	}
	
	//comando d no teclado
	else if(tecla == tDIREITA){
		if(cobra[0][0] < quantColunasTab - 2){
			novaPosicaoCabeca[0] = cobra[0][0] + 1;
		}
		else{
			novaPosicaoCabeca[0] = 1;
		}
		novaPosicaoCabeca[1] = cobra[0][1];
	}
	
	//para inicar o controle de posição antes de qualquer movimento.
	else{
		novaPosicaoCabeca[0] = cobra[0][0];
 		novaPosicaoCabeca[1] = cobra[0][1];	
 		//return 1;
	}
	
	// passa a parte posterior da cobra para parte anterior.	
	for(int i = tamCobra; i > 1; i--){
		cobra[i-1][0] = cobra[i-2][0];
		cobra[i-1][1] = cobra[i-2][1];
	}
	//atualiza a cabeça para nova posição de acordo com o movimento realizado.
	cobra[0][0] = novaPosicaoCabeca[0];
	cobra[0][1] = novaPosicaoCabeca[1];
	
	
}

verificarSeFrutaFoiComida(){
	if(cobra[0][0] == colunaFruta && cobra[0][1] == linhaFruta){
		pontos = pontos + 1;
		tamCobra = tamCobra + 1;
		gerarNovaFruta();
	}
}

verificarColisaoCobraComCorpo(){
	for(int i = 1; i < tamCobra; i++){
		if(cobra[0][0] == cobra[i][0] && cobra[0][1] == cobra[i][1]){
			estaJogoFinalizado=1;
			break;			
		}
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
	
	for(int i = 1; i < tamCobra; i++){
		y = cobra[i][1];
		x = cobra[i][0];
		tabuleiro [y][x] = 219;
	}
	
	x = cobra[0][0];
	y = cobra[0][1];
	tabuleiro [y][x] = 178;
	
}


imprimirJogo(){
	
	system("cls");
	
	printf("Pontos: %d ",pontos);
	
	if(estaJogoFinalizado != 0){
		
		printf("---------------------GAME OVER--------------------");		
	}
		
	printf("\n");
	
	for (y = 0; y < quantLinhasTab; y++){
		for (x = 0; x < quantColunasTab; x++){
			printf("%c",tabuleiro[y][x]);
		}
		printf("\n");
	}
}

iniciarJogo(){
	
	inicializarCobra();
	//laço principal do jogo
	while (estaJogoFinalizado != 1){
		capturarTecla();
		verificarSeFrutaFoiComida();
		moverCobra();
		verificarColisaoCobraComCorpo();
		gerarTabuleiro();
		imprimirJogo();
		sleep(0.9);//TODO: criar funcionalidade para escolha da velocidade pelo jogador
	}
}

int main(){
				
	iniciarJogo();
			
}
