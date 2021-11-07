#include <allegro.h>

//fun��es
void sair();
void control();
int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh);

struct obj{int wx, wy, x, y, w, h;};
struct obj
	p = {0,0,500,50,64,64,0,0},
	bloco[13][15];

//Vari�veis Globais
int sai    = 0;
int width  = 900;
int height = 720;
int dir = 0;
int nTile = 0;
int vly = 0;
int grv = 4;
int caindo = 1;
int pulando = 0;
int vup = 15;
int pLimit = 0;
char mp[13][15];


BITMAP *buffer, *imagem;

int main() {
	
    //Inicia��o
	allegro_init();
    install_keyboard();
	set_color_depth(32);
	set_window_title("Jogo PI");
	set_close_button_callback(sair);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);  
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	int i,j;

	
	//Vari�veis Locais
	buffer = create_bitmap(width, height);
	imagem = load_bitmap("sprites/robosprite.bmp", NULL);
	
	for(i = 0; i < 13; i++) 	{
		for(j = 0; j < 15; j++){
			bloco[i][j].y = 600;
			bloco[i][j].x = j*60;
			bloco[i][j].w = 50;
			bloco[i][j].h = 50;
			bloco[i][j].wy =256;
				
		}
	
	}
		
	while (!(sai || key[KEY_ESC]))
	{		
		control();
			for(i=0;i<13;i++){
				for(j=0; j < 15; j++){
						masked_blit(imagem,buffer,bloco[i][j].wx,bloco[i][j].wy,bloco[i][j].x,bloco[i][j].y,bloco[i][j].w,bloco[i][j].h);
						if (colidir(p.x , p.y + 10, bloco[i][j].x, bloco[i][j].y, p.w, p.h, bloco[i][j].w, bloco[i][j].h)){
						p.y = bloco[i][j].y - p.h;
						caindo = 0;
					}
				}
			}
	
		masked_blit(imagem, buffer, p.wx + nTile*64,p.wy + dir*64,p.x,p.y,p.w,p.h);
		draw_sprite(screen, buffer, 0, 0);
		rest(45);
		clear(buffer);	
			
	}
	//Finaliza��o
	destroy_bitmap(buffer);
	destroy_bitmap(imagem);
	return 0;
}

END_OF_MAIN();
void sair(){sai= 1;}
END_OF_FUNCTION(sair);

void control(){
	
	if(key[KEY_SPACE] && !pulando && !vly){
		pLimit = p.y;
		pulando = 1;
	}
	if(pulando || caindo){
		if(key[KEY_RIGHT]){p.x+=10; dir = 3; nTile = 0; }	
		else if(key[KEY_LEFT]){p.x-=10; dir = 2; nTile = 0;}	
	} else {
	if(key[KEY_RIGHT]){p.x+=10; dir = 0; nTile++;}
	else if(key[KEY_LEFT]) {p.x-=10; dir = 1; nTile++;}
	else nTile = 0;
	if(nTile < 0) nTile = 6;
	if(nTile > 6) nTile = 0;
	
 }
	if(pulando && p.y > pLimit - 30){
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
	
		if(Ax + Aw > Bx && Ax < Bx +Bw && Ay + Ah > By && Ay < By + Bh)
		return 1;
		return 0;
	
	}	

