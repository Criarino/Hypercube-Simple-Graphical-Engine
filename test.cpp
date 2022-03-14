//g++ *.cpp -o t -lSDL2 -lSDL2_ttf -lSDL2_image
#include <iostream>
#include "HCSGE.h"

using namespace std;

int rodando=1;
HC Engine;
void input();
void render();
void update();
HC_Objeto testt;
HC_Entidade player;
int corr, idolr;
int sans=Engine.AbrirFonte("Sans.ttf", 15);

int main()
{
	Engine.CriarJanela(1280, 680, "Lorem Ipsum");
	Engine.CriarObj(&testt, "iss.png", 0, 0, 100, 100);//criando um objeto de teste - um retangulo preto guardado em disco
	Engine.CriarEntidade(&player, "player.png", 0, 0, 24, 32);//objeto com animação usando spritesheet
	testt.setDest(340, 300);
	corr=player.createCycle(3, 24, 32, 4, 4);//registrando animações
	idolr=player.createCycle(1, 24, 32, 2, 20);
	player.setCurAnimation(idolr);//setando animação
	while(rodando)
	{
		Engine.SetBackground(126, 192, 238, 255);
		render();
		input();
		update();
	}
	return 0;
}

void input()
{
	vector<int>asc;
	do
	{
		asc=Engine.HaInput();
		switch(asc[0])//qual o tipo de evento
		{
			case -1://caso seja fechar
				rodando=0;
				break;
			case 1://botao pressionado
				break;
			case 3://caso seja clique
				break;
			case 4://caso especial (texto)
				break;
		}
	}while(asc[0]!=0);
}

void render()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Engine.Desenhar(to_string(x)+','+to_string(y), sans, 3, 3, 255, 0, 0);//mostrar a posição x y do mouse no canto da tela
	Engine.Desenhar(&player, 240, 240);
	Engine.Desenhar(&testt);
	Engine.Commit(60);
}

void update()
{
	player.updateAnimation();
}
