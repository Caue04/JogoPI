#include <allegro.h>

//funções

//TIMER
volatile int msecs;
void msecsCount(){
	msecs++;
}
END_OF_FUNCTION(milisecsCount)

void sair();
void blocos();
void blocos2();
void control(); 
void mapa();
void mapa2();
void menu1();
void pause();
void aranha1();
void aranha2();
void dano();
void hpicon();
void coin();
void respawn();

int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh);

struct obj{int wx, wy, x, y, w, h;};
struct obj
	p = {0,0,0,500,64,64},
	c = {0,0,25,320,25,25},
	bloco[14][18],
	bloco2[14][18];

struct inimigo{int wx, wy, x, y, w, h, iniDir, iniEsq, iniHp, iniIframe;};
struct inimigo
	ar 	= {0,0,380,500,64,64,1,0,5,0},
	ar2 = {0,0,630,200,64,64,0,1,5,0},
	rb	= {0,0,840,586,64,64,0,1,3,0},
	rb2	= {0,0,840,186,64,64,0,1,3,0},
	rb3	= {0,0,0,36,64,64,1,0,3,0};
	
	
	
//Variáveis Globais
int sai    = 0;
int pausa = 0;
int width  = 900;
int height = 700;
int dir = 0;
int nTile = 0;
int vly = 0;
int grv = 4;
int caindo = 1;
int pulando = 0;
int vup = 15;
int pLimit = 0;
char mp[14][18];
char mp2[14][18];
int out = -500;
int ataque = 0;
int ult;
int str=0;
int s1;
int hp = 3; //variavel de vida do player
int morreu = 1; 
int marcadorAtq;
int iFrame;
int marcador, marcadorS;
int ctn;
int mapaTroca;
int moedaC;
int contadorI;
int Smapacount;

BITMAP *buffer, *imagem, *menu, *aranha, *vida1, *vida2, *vida3, *pausar, *moeda;
SAMPLE *som, *ataqueS, *puloS, *Scoin, *Smapa, *dAranha;

int main() {
	
    //Iniciação
	allegro_init();
    install_keyboard();
	set_color_depth(32);
	set_window_title("Jogo PI");
	set_close_button_callback(sair);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);  
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	int i,j;
	marcador = msecs;
	marcadorS = msecs;
	mapaTroca = 1;
	moedaC = 0;
	contadorI=0;
	Smapacount = 0;
	//Variáveis Locais
	buffer = create_bitmap(width, height);
	imagem = load_bitmap("sprites/robosprite.bmp", NULL);
	pausar = load_bitmap("sprites/pause.bmp", NULL);
	moeda  = load_bitmap("sprites/coin.bmp", NULL);
	aranha = load_bitmap("sprites/spider.bmp", NULL);
	vida1  = load_bitmap("sprites/HP1.bmp" , NULL);
	vida2  = load_bitmap("sprites/HP2.bmp" , NULL);
	vida3  = load_bitmap("sprites/HP3.bmp" , NULL);
	pausar = load_bitmap("sprites/pause.bmp", NULL);
		
		//SET TIMER
		msecs = 0;
		LOCK_FUNCTION(msecsCount);
		LOCK_VARIABLE(msecs);
		install_int_ex(msecsCount, MSEC_TO_TIMER(1));

	menu   	= load_bitmap("sprites/menu.bmp", NULL);
	som    	= load_sample("somMenu.wav");
	Scoin   = load_sample("coinS.wav");
	Smapa   = load_sample("trocaS.wav");
	ataqueS = load_sample("ataque.wav");
	puloS   = load_sample("pulo.wav");
	dAranha = load_sample("spiderHited.wav"); 
	SAMPLE *sPause  = load_sample("pause.wav");
	
	for(i = 0; i < 14; i++) 	{
		for(j = 0; j < 18; j++){
			bloco[i][j].y = i*50;
			bloco[i][j].x = j*50;
			bloco[i][j].w = 50;
			bloco[i][j].h = 50;
			bloco[i][j].wy =256;
		}
	}
		mapa();
	
	for(i = 0; i < 14; i++) 	{
		for(j = 0; j < 18; j++){
			bloco2[i][j].y = i*50;
			bloco2[i][j].x = j*50;
			bloco2[i][j].w = 50;
			bloco2[i][j].h = 50;
			bloco2[i][j].wy =256;
		}
	}
		mapa2();
		
		
	while (!(sai || key[KEY_ESC]))
	{		
		
		if(key[KEY_SPACE] && !pausa) {
			pausa = 1;
			play_sample(sPause, 225,128,1000,0);			
		}
		
		control();
		if(str == 0)menu1();
		if(mapaTroca == 1)blocos();
		if(mapaTroca == 2)blocos2();
		if(str == 1){ 
		masked_blit(imagem, buffer, p.wx + nTile*64,p.wy + dir*64,p.x,p.y,p.w,p.h);
		coin();
		if(mapaTroca == 1)aranha1();
		if(mapaTroca == 1)aranha2();
		hpicon();
		if(pausa == 1)draw_sprite(buffer, pausar,0,0);
		draw_sprite(screen, buffer, 0, 0);
		pause();
		rest(45);
		clear(buffer);
	}
	}
			

	//Finalização
	destroy_bitmap(buffer);
	destroy_bitmap(menu);
	destroy_bitmap(imagem);
	destroy_bitmap(vida1);
	destroy_bitmap(vida2);
	destroy_bitmap(vida3);
	destroy_bitmap(aranha);
	destroy_bitmap(pausar);
	destroy_sample(som);
	destroy_sample(ataqueS);
	destroy_sample(puloS);
	return 0;
}

END_OF_MAIN();

void coin() {
	if(moedaC == 0)masked_blit(moeda, buffer,c.wx+(contadorI/3)*25,c.wy,c.x,c.y,24,24);
	contadorI++;
	if(contadorI > 15)contadorI = 0;
	if(colidir(p.x, p.y+30 , c.x , c.y, p.w-24,40 , c.w-24 ,25)){ 
		moedaC++;	
		if(moedaC == 1)play_sample(Scoin, 225,128,1000,0);
	}	
	if( moedaC >= 1){
		mapaTroca = 2;
	}
}

void hpicon() {
	if (hp == 3)draw_sprite(buffer, vida3, 830, 30);
	if (hp == 2)draw_sprite(buffer, vida2, 830, 30);
	if (hp == 1)draw_sprite(buffer, vida1, 830, 30);	
}


void aranha1() {
	//MOVIMENTO
	if(ar.x < 550 && ar.iniDir == 1)
		ar.x += 10;
	else if(ar.x == 550){
		ar.iniDir = 0;
		ar.iniEsq = 1;
	}
	if(ar.x > 380 && ar.iniEsq == 1)
		ar.x -= 10;
	else if(ar.x == 380){
		ar.iniEsq = 0;
		ar.iniDir = 1;
	}
	//COLISÃO PLAYER e DANO
	if (colidir(p.x + 20, p.y + 31 , ar.x + 15 , ar.y + 19, 24 , 35 , 30 , 36) && msecs - iFrame >= 1000 && ar.iniHp > 0){
		iFrame = msecs;
		dano();
	}
	if (colidir(p.x, p.y + 31 , ar.x + 15 , ar.y + 19, 64 , 35 , 30 , 36) && key[KEY_Z] && msecs - ar.iniIframe >= 500){
		if(ar.iniHp > 0)
			play_sample(dAranha, 100, 110, 1000, 0);
		ar.iniHp--;
		ar.iniIframe = msecs;
	}
	//DRAW
	if(ar.iniHp > 0) 
		masked_blit(aranha, buffer, ar.wx,ar.wy,ar.x,ar.y,ar.w,ar.h);
}
void aranha2() {
	//MOVIMENTO
	if(ar2.x < 750 && ar2.iniDir == 1)
		ar2.x += 10;
	else if(ar2.x == 750){
		ar2.iniDir = 0;
		ar2.iniEsq = 1;
	}
	if(ar2.x > 630 && ar2.iniEsq == 1)
		ar2.x -= 10;
	else if(ar2.x == 630){
		ar2.iniEsq = 0;
		ar2.iniDir = 1;
	}
	//COLISÃO PLAYER e DANO
	if (colidir(p.x + 20, p.y + 31 , ar2.x + 15 , ar2.y + 19, 24 , 35 , 30 , 36) && msecs - iFrame >= 1000 && ar2.iniHp > 0){
		iFrame = msecs;
		dano();
	}
	if (colidir(p.x, p.y + 31 , ar2.x + 15 , ar2.y + 19, 64 , 35 , 30 , 36) && key[KEY_Z] && msecs - ar2.iniIframe >= 500){
		if(ar2.iniHp > 0)
			play_sample(dAranha, 100, 110, 1000, 0);
		ar2.iniHp--;	
		ar2.iniIframe = msecs;
	}
	//DRAW
	if(ar2.iniHp > 0 && mapaTroca == 1)
		masked_blit(aranha, buffer, ar2.wx,ar2.wy,ar2.x,ar2.y,ar2.w,ar2.h);	
}

void rb1(){
	
}
void rb2(){
	
}
void rb3(){
	
}

void pause() {
	while ( key[KEY_SPACE] && pausa) {
		draw_sprite(buffer, pausar, 0, 0);
	}
	while (!key[KEY_SPACE] && pausa && !(sai || key[KEY_ESC]));
	pausa = 0;
	while (key[KEY_SPACE] && !pausa);
}
void menu1(){
	int time =0, flash = 0;
	
  		play_sample(som, 90, 110, 1000, 10);
		
	
	while (!(sai || key[KEY_ENTER] )){
	
	if (time > 20) time = 0;
	
	draw_sprite(buffer, menu,0,0);
	if (time < 10)
	
	textprintf_centre_ex(buffer, font, width/2, height/1.3, 0xffffff,-1, "APERTE ENTER PARA INICIAR", time);
	draw_sprite(screen, buffer, 0, 0);
	rest(100);
	clear(buffer);	
	time++;
	}
}


void mapa(){
	int i,j;
	char map[14][18] = {{4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5},
						{2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{2,18,2,18,2,18,23,24,23,18,2,18,2,18,2,18,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{2,18,2,23,2,18,2,18,2,18,23,18,2,24,23,24,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{23,24,23,18,2,18,2,20,2,18,2,18,2,24,2,18,2,18},
						{18,2,18,2,18,2,24,23,24,2,24,2,18,2,18,2,18,2},
						{2,18,2,18,23,18,2,18,2,18,2,18,2,18,2,18,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,10,10,10,2,18,2},
						{10,10,10,10,21,22,21,22,10,10,10,10,6,6,6,20,19,20},
						{6,6,6,6,9,9,9,9,6,6,6,6,6,6,6,6,6,6},
						{6,6,6,6,9,9,9,9,6,6,6,6,6,6,6,6,6,6}};

	for(i = 0; i < 14; i++){
		for(j = 0; j < 18; j++){
			if(map[i][j]) bloco[i][j].wx = (map[i][j] - 1) * bloco[i][j].w;
			else bloco[i][j].x = out;
			mp[i][j] = map[i][j];
		}
	}	
}
void mapa2(){
	int i,j;
	char map2[14][18] = {{4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5},
						{2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18},
						{24,23,24,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18},
						{18,2,18,2,24,23,18,2,18,2,18,2,18,2,18,2,18,2},
						{2,18,2,18,2,18,23,24,23,18,2,18,23,18,2,24,23,24},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{23,24,23,18,2,18,2,18,2,18,2,18,2,24,2,18,2,18},
						{18,2,18,2,18,2,18,2,24,23,18,2,18,2,18,2,18,2},
						{2,18,2,18,23,18,2,18,2,18,2,18,2,18,2,18,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,24,23,24,2,18,2},
						{2,18,2,18,2,18,2,18,2,18,23,24,2,18,2,18,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,23,18,2,18,2},
						{19,20,19,20,19,10,10,10,19,20,19,20,19,20,19,10,10,10}};

	for(i = 0; i < 14; i++){
		for(j = 0; j < 18; j++){
			if(map2[i][j]) bloco2[i][j].wx = (map2[i][j] - 1) * bloco2[i][j].w;
			else bloco2[i][j].x = out;
			mp2[i][j] = map2[i][j];
		}
	}	
}

void blocos(){
	int i,j;			
	for(i=0;i<14;i++){
		for(j=0; j < 18; j++){
			masked_blit(imagem,buffer,bloco[i][j].wx,bloco[i][j].wy,bloco[i][j].x,bloco[i][j].y,bloco[i][j].w,bloco[i][j].h);
			if (colidir(p.x, p.y+30 , bloco[i][j].x , bloco[i][j].y, p.w-24,40 , bloco[i][j].w-24 ,50) && p.y >= 486 && !pulando){
				if(mp[i][j] != 3 && mp[i][j] != 9 && mp[i][j] != 4 && mp[i][j] != 5 && mp[i][j] != 2 && mp[i][j] != 18 && mp[i][j] != 19 && mp[i][j] != 20 && mp[i][j] != 21 && mp[i][j] != 22){
					p.y = bloco[i][j].y - p.h;
					caindo = 0;
				}
			}
			else if (colidir(p.x, p.y+30 , bloco[i][j].x , bloco[i][j].y, p.w-24,40 , bloco[i][j].w-24 ,1) && p.y <= 486 && !pulando){
				if(mp[i][j] != 3 && mp[i][j] != 9 && mp[i][j] != 4 && mp[i][j] != 5 && mp[i][j] != 2 && mp[i][j] != 18 && mp[i][j] != 19 && mp[i][j] != 20 && mp[i][j] != 21 && mp[i][j] != 22){
					p.y = bloco[i][j].y - p.h;
					caindo = 0;
				}
			}	
			if(mp[i][j] == 19 || mp[i][j] == 20){
				if (colidir(p.x, p.y+30 , bloco[i][j].x + 5 , bloco[i][j].y + 30, p.w-24,40 , bloco[i][j].w-30 ,50)){
					caindo = 0;
					respawn();
				}
			}		
		}
	}	
}

void blocos2(){
	int i,j;
		
	for(i=0;i<14;i++){
		for(j=0; j < 18; j++){
			masked_blit(imagem,buffer,bloco2[i][j].wx,bloco2[i][j].wy,bloco2[i][j].x,bloco2[i][j].y,bloco2[i][j].w,bloco2[i][j].h);
			if (colidir(p.x, p.y+30 , bloco2[i][j].x , bloco2[i][j].y, p.w-24,40 , bloco2[i][j].w-24 ,50) && p.y >= height - 128 && !pulando){
				if(mp2[i][j] != 3 && mp2[i][j] != 9 && mp2[i][j] != 4 && mp2[i][j] != 5 && mp2[i][j] != 2 && mp2[i][j] != 18 && mp2[i][j] != 19 && mp2[i][j] != 20 && mp2[i][j] != 21 && mp2[i][j] != 22){
					p.y = bloco2[i][j].y - p.h;
					caindo = 0;
				}
			}
			else if (colidir(p.x, p.y+30 , bloco2[i][j].x , bloco2[i][j].y, p.w-24,40 , bloco2[i][j].w-24 ,1) && p.y <= height -124 && !pulando){
				if(mp2[i][j] != 3 && mp2[i][j] != 9 && mp2[i][j] != 4 && mp2[i][j] != 5 && mp2[i][j] != 2 && mp2[i][j] != 18 && mp2[i][j] != 19 && mp2[i][j] != 20 && mp2[i][j] != 21 && mp2[i][j] != 22){
					p.y = bloco2[i][j].y - p.h;
					caindo = 0;
				}
			}		
			if(mp2[i][j] == 19 || mp2[i][j] == 20){
				if (colidir(p.x, p.y+30 , bloco2[i][j].x + 5, bloco2[i][j].y + 30, p.w-24,40 , bloco2[i][j].w-30 ,50)){
					caindo = 0;
					respawn();
				}
			}
		}
	}
		
	textprintf_centre_ex(buffer, font, 100, 220, 0xffffff,-1, "p.y:%d", p.y);
	textprintf_centre_ex(buffer, font, 100, 240, 0xffffff,-1, "p.x:%d", p.x);	
}

void dano(){
	if(hp > 0)
		hp--;
	if(hp == 0){
		stop_sample(som);
		morreu = 1;
		p.y = 444;
		p.x = 0;
		hp = 3;
		msecs = 0;
		iFrame = 0;
		marcadorAtq = 0;
		marcador = 0;
		ar.iniHp = 5;
		ar2.iniHp = 5;
		ar.iniIframe = 0;
		ar2.iniIframe = 0;
		mapaTroca = 1;
		moedaC = 0;
		menu1();
	}
}
//respawnar no inicio da fase
void respawn(){
	if(mapaTroca == 1){
		p.y = 444;
		p.x = 0;
		dano();
	}
	else if(mapaTroca == 2){
		p.y = 286;
		p.x = 10;
		dano();
	}
}

void control(){
	//printsDEBUG
	//textprintf_centre_ex(buffer, font, 100, 100, 0xffffff,-1, "Timer:%d", msecs);
	//textprintf_centre_ex(buffer, font, 100, 200, 0xffffff,-1, "Ar1 HP:%d", ar.iniHp);
	//textprintf_centre_ex(buffer, font, 100, 220, 0xffffff,-1, "Ar2 HP:%d", ar2.iniHp);
	//textprintf_centre_ex(buffer, font, width/2, height/1.3, 0xffffff,-1, "HP = %d", hp , time);
	
	if(key[KEY_M] && msecs - marcadorS >= 750 ){
		marcadorS = msecs;
		stop_sample(som);
		ctn = 0;
	}
	if(key[KEY_N]&& msecs - marcadorS >= 750 ){
		marcadorS = msecs;
		ctn++;
		if(ctn <= 1)play_sample(som, 90, 110, 1000, 10);
	}
	
	if(key[KEY_ENTER]){
		str = 1;
	}
	
	textprintf_centre_ex(buffer, font, width/2, height/1.3, 0xffffff,-1, "HP = %d", hp , time);
	//SISTEMA DE HP
	if(key[KEY_ENTER] && hp == 3 && morreu == 1){
		morreu = 0;
	}	
	
	/*DEBUG VIDA
	if(hp > 0 && key[KEY_H])
		dano();	*/
		
	//DANO AO CAIR
	if(morreu == 0 && p.y > height+64)
		respawn();
	
	if(msecs - marcador >= 450 && key[KEY_Z]&& !pulando && caindo==0){
		marcadorAtq = msecs;
		marcador = msecs;
		play_sample(ataqueS,255,128,1000,0);
		ataque = 1;
		}
	
	if(key[KEY_UP] && !pulando && !vly){
		play_sample(puloS,255,128,1000,0);
		pLimit = p.y;
		pulando = 1;
	}
	if(pulando || caindo){
		if(key[KEY_RIGHT]){p.x+=10; dir = 0; nTile = 7; }	
		else if(key[KEY_LEFT]){p.x-=10; dir = 1; nTile = 7;}	
	} else {
	if(key[KEY_RIGHT]){p.x+=10; dir = 0; nTile++;}
	else if(key[KEY_LEFT]) {p.x-=10; dir = 1; nTile++;}
	else nTile = 0;
	if(nTile < 0) nTile = 6;
	if(nTile > 6) nTile = 0;
	
 }
 	
	if(ataque){
		 if(dir==1)dir = 2;nTile=1;
		 if(dir==0)dir = 3;nTile=1;
		 if(nTile < 0 && dir==2) dir == 1;
		 if(nTile < 0 && dir==3) dir == 0;
		else
		ataque =0;
	}

	
	if(pulando && p.y > pLimit - 50){
			p.y += vly;
			vly =- vup;
			caindo = 1;
		}
	else if(caindo){
		pulando = 0;
		vly += grv;
		p.y += vly;
	}
	else {
		pulando = 0;
		vly = 0;
	}
	caindo = 1;
			
}

int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh){
	
		if( (Ax > Bx + Bw ) || (Ay > By + Bh)|| (Bx > Ax + Aw) || (By > Ay + Ah))
		return 0;
		else
		return 1;
	
	}	
	
void sair(){sai= 1;}
END_OF_FUNCTION(sair);
