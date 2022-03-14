//Hypercube Simple Graphical Engine header
#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <string>
#include <stdexcept>
//#include <iostream>

using namespace std;

class HC_Objeto //classe de objetos na tela
{
	private:
	SDL_Rect dest; //onde na tela vai ficar
	SDL_Rect src; //escala da imagem original
	SDL_Texture* tex; //textura
	bool solid; //para colisão - se o objeto tem colisão ou não
	int id;

	public:
	HC_Objeto(){solid=1;}
	HC_Objeto(int so){solid=so;}
	~HC_Objeto(){if(tex) SDL_DestroyTexture(tex);}
	//getters e setters
	SDL_Rect getDest() {return dest;}
	SDL_Rect getSource() {return src;}
	SDL_Texture* getTex() {return tex;}
	bool getSolid() {return solid;}
	int getDX() {return dest.x;}//para saber posição do objeto (getDestX)
	int getDY() {return dest.y;}
	int getDW() {return dest.w;}
	int getDH()	{return dest.h;}
	int getID() {return id;}

	void setDest(int x, int y, int w, int h);
	void setDest(int x, int y);//para mover a tela
	void setSource(int x, int y, int w, int h);//de onde vai começar a carregar a imagem, qual a porção da imagem que vai carregar. Pode cortar partes da imagem
	void setImage(string filename, SDL_Renderer* ren);//carrega uma textura
	void setSolid(bool s){solid=s;}
	void setID(int ID){id=ID;}
};

class HC_audio //para audio
{
	private:
	SDL_AudioSpec wavSpec;//apenas arquivos wave
	Uint32 wavLength; //TEM que ser esse o tipo
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceID;
	
	public:
	~HC_audio();
	void Adicionar(string filename);
	void Play();
};

class HC_Botao : public HC_Objeto//um objeto com função extra de botão
{
	private:
	bool click=false;
	public:
	int tamx, tamy;
	void Setclick(bool set){click=set;}
	bool Getclick(){return click;}
	bool Sobre();//verifica se o mouse está sobre o botão
	void setDest(int x, int y, int w, int h);
};

class HC_CaixaTxt : public HC_Botao//um botão com função extra de caixa de texto
{
	private:
	string txt;//guarda o texto
	bool ativ;
	public:
	HC_CaixaTxt();
	int r, g, b, f; //cor, handle da fonte
	//getters e setters
	string Gettxt(){return txt;}
	bool Getativ(){return ativ;}
	void Setativ(bool set){ativ=set;}
	void Texto(string a);//para atualizar o texto da caixa
	void Ativar();//para ativar/desativar a caixa de texto
};

class HC_Entidade : public HC_Objeto
{
	private:
	struct cycle //informações da animação
	{
		int row;
		int w;
		int h;
		int amount;
		int speed;
		int tick;
	};
	vector<cycle> animations;//vector que guarda todas as animações
	int curAnim;//animação atual
	int begin;//frame da animação
	bool rev, nAb;//para reverter animação
	int newAnim;//para mudar uma animação

	public:
	HC_Entidade(){rev=0;}
	//getter e setters
	void setCurAnimation(int c) {begin=0;curAnim=c;}
	int getCurAnimation() const {return curAnim;}
	void reverse(bool r) {rev=r;}//para inverter a animação

	int createCycle(int r, int w, int h, int amount, int speed);//cria uma animação(linha da imagem original, tamanho wxh, quantos frames, velocidade [quanto menor o número maior a velocidade]), retorna o código desta animação
	void updateAnimation();//atualiza o estado da animação atual
	void reverse(bool r, int nA){rev=r; nAb=1; nA=newAnim;}//inverte a animação e seta uma nova (booleana, codigo da nova animaçao)
};

class HC //engine em si
{
	private:
	int altura;//tamanho da janela
	int largura;
	SDL_Renderer* rende;//renderizador
	SDL_Window* janela;//janela
	vector<TTF_Font*>FontHandles;//fontes abertas
	SDL_Event eventos;//fila de eventos
	int frameCount=0, timerFPS, lastFrame=0, fps, lastTime=0;//para calcular e limitar fps

	public:
	string buftxt;
	~HC();
	HC();
	SDL_Window* getJanela(){return janela;}
	SDL_Event* getEvent(){return &eventos;}
	SDL_Renderer* getRende(){return rende;}
	void CriarJanela(int alt, int lar, string nome);
	vector<int> HaInput();//verificar se há input e qual é esse input. Retorna 0 se não tiver, -1 se o usuário clicou no X da janela, retorna um vector de duas posições nos outros casos: o primeiro elemento do vector é o tipo de evento e o segundo o código do evento (ascii caso seja do teclado)
	void SetBackground(int r, int g, int b, int a);//seta um fundo
	void Commit(int fps);//mostra o renderizador (frame) na tela
	int CalcFps();//calcula o fps, o int retornado é o fps atual
	void CriarObj(HC_Objeto* aux, string img, int x, int y, int l, int a);//cria um objeto (caminho de diretório para a textura, posção xy de onde vai começar a carregar essa textura, largura e altura dessa textura)
	void CriarBtn(HC_Botao* aux, string img, int x, int y, int l, int a);//criar um botão a partir de uma imagem
	void CriarBtn(HC_Botao* aux, int l, int a);//cria um botão invisível, NÃO SE DEVE CHAMAR A FUNÇÃO "DESENHAR" NESSE CASO
	void CriarCaixaTxt(HC_CaixaTxt* aux, string img, int f, int r, int g, int b, int x, int y, int l, int a);//cria uma caixa de texto com imagem (fonte, cor do texto, ponto do qual começará a carregar a imagem original, tamanho)
	void CriarCaixaTxt(HC_CaixaTxt* aux, int f, int r, int g, int b, int l, int a);//para criar uma caixa de texto invisível(mesmo que o anterior, mas sem ponto para carregar imagem)
	void CriarEntidade(HC_Entidade* aux, string img, int x, int y, int l, int a);//cria entidade (mesmo que criar objeto)
	void Desenhar(HC_Objeto* o); //quando o objeto já tem posição
	void Desenhar(HC_Objeto* o, int x, int y);//quando quer atribuir posição ao objeto
	void Desenhar(string msg, int f, int x, int y, int r, int g, int b);//para texto (mensagem, codigo da fonte, posição xy, cor rgb)
	void Desenhar(bool fil, int alt, int lar, int x, int y, int r, int g, int b, int a);//para retangulos(se é para preencher, altura x largura, posição xy, cor)
	void Desenhar(int x, int y, int fx, int fy, int r, int g, int b);//Para linhas(ponto xy inicial, ponto xy final,...)
	void Desenhar(int x, int y, int r, int g, int b);//Para pontos
	void Desenhar(HC_CaixaTxt* a, int mx, int my);//para desenhar o texto de uma caixa (caixa, true, ajuste x y do texto)
	int AbrirFonte(string arqv, int tam);//abre uma fonte de texto. Retorna o código para essa fonte (diretório do arquivo ttf, tamanho)
};
