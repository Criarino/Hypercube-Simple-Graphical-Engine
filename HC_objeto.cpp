#include "HCSGE.h"

void HC_Objeto::setDest(int x, int y, int w, int h)
{
	dest.x=x;
	dest.y=y;
	dest.w=w;
	dest.h=h;
}

void HC_Objeto::setDest(int x, int y)
{
	dest.x=x;
	dest.y=y;
}

void HC_Objeto::setSource(int x, int y, int w, int h)
{
	src.x=x;
	src.y=y;
	src.w=w;
	src.h=h;
}

void HC_Objeto::setImage(string filename, SDL_Renderer* rende)
{
	if(tex)
		SDL_DestroyTexture(tex);
	tex=IMG_LoadTexture(rende, filename.c_str());
	if(!tex)
		throw runtime_error("Error on IMG_LoadTexture()");
}

int HC_Entidade::createCycle(int r, int w, int h, int amount, int speed) //cria uma struct do tipo cycle com todas as informações da animação e a coloca no vector
{
	cycle tmp;
	tmp.row=r-1;
	tmp.w=w;
	tmp.h=h;
	tmp.amount=amount;
	tmp.speed=speed;
	tmp.tick=0;
	animations.push_back(tmp);
	return animations.size()-1;
}

void HC_Entidade::updateAnimation()
{
	setSource(animations[curAnim].w*animations[curAnim].tick, animations[curAnim].row*animations[curAnim].h, animations[curAnim].w, animations[curAnim].h);//setando o frame atual
	if(begin>animations[curAnim].speed)//se uma animação já tiver começado
	{
		if(!rev)//para reverter animações
			animations[curAnim].tick++;
		if (rev)
			animations[curAnim].tick--;
		begin=0;
	}
	begin++;
	if(animations[curAnim].tick>=animations[curAnim].amount)//resetando
		animations[curAnim].tick=0;
	if(animations[curAnim].tick<=0)//setando nova animação
	{
		if(nAb)
		{
			curAnim=newAnim;
			nAb=0;
			rev=0;
		}
		else
			animations[curAnim].tick=0;
	}
}

bool HC_Botao::Sobre()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if(((getDX()<=x)&&(x<=(getDX()+tamx))) && ((getDY()<=y)&&(y<=(getDY()+tamy))))
		return true;
	else
		return false;
}

void HC_Botao::setDest(int x, int y, int w, int h)
{
	HC_Objeto::setDest(x, y, w, h);
	tamx=w;
	tamy=h;
}

HC_CaixaTxt::HC_CaixaTxt()
{
	txt="";
	ativ=false;
}

void HC_CaixaTxt::Texto(string a)
{
	if ((a.size()>1) && (txt.size()>0))
		txt.pop_back();
	else if(a.size()==1)		
			txt+=a;
}

void HC_CaixaTxt::Ativar()
{
	if (ativ)
	{
		SDL_StopTextInput();
		ativ=false;
	}
	else
	{
		SDL_StartTextInput();
		ativ=true;
	}
}
