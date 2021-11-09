#include <allegro.h>

//funções
void sair();
void blocos();
void control();
void mapa();
int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh);

struct obj{int wx, wy, x, y, w, h;};
struct obj
	p = {0,0,500,50,64,64,0,0},
	bloco[14][18];
	
//Variáveis Globais
int sai    = 0;
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
int out = -500;
int ataque = 0;
int ult;

BITMAP *buffer, *imagem;

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

	//Variáveis Locais
	buffer = create_bitmap(width, height);
	imagem = load_bitmap("sprites/robosprite.bmp", NULL);
	
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
	while (!(sai || key[KEY_ESC]))
	{		
		blocos();
		control();
		masked_blit(imagem, buffer, p.wx + nTile*64,p.wy + dir*64,p.x,p.y,p.w,p.h);
		draw_sprite(screen, buffer, 0, 0);
		rest(45);
		clear(buffer);	
			
	}
	//Finalização
	destroy_bitmap(buffer);
	destroy_bitmap(imagem);
	return 0;
}

END_OF_MAIN();

void mapa(){
	int i,j;
	char map[14][18] = {{4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5},
						{2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{2,18,2,18,2,18,16,17,15,18,2,18,2,18,2,18,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{2,18,2,1,2,18,2,18,2,18,1,18,2,16,17,15,2,18},
						{18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2,18,2},
						{16,17,15,18,2,18,2,20,2,18,2,18,2,1,2,18,2,18},
						{18,2,18,2,18,2,16,17,15,2,1,2,18,2,18,2,18,2},
						{2,18,2,18,1,18,2,18,2,18,2,18,2,18,2,18,2,18},
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

void blocos(){
int i,j;			
			for(i=0;i<14;i++){
				for(j=0; j < 18; j++){
						masked_blit(imagem,buffer,bloco[i][j].wx,bloco[i][j].wy,bloco[i][j].x,bloco[i][j].y,bloco[i][j].w,bloco[i][j].h);
						if (colidir(p.x, p.y+30 , bloco[i][j].x , bloco[i][j].y, p.w-24,40 , bloco[i][j].w-24 ,10)){
						if(mp[i][j] != 3 && mp[i][j] != 9 && mp[i][j] != 4 && mp[i][j] != 5 && mp[i][j] != 2 && mp[i][j] != 18 && mp[i][j] != 21 && mp[i][j] != 22 ){
						p.y = bloco[i][j].y - p.h;
						caindo = 0;
						}
					}
				}
			}	
	
}

void control(){
	
	if(key[KEY_Z]){
		ataque = 1;
		}
	
	if(key[KEY_SPACE] && !pulando && !vly){
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
 	if(ataque && (key[KEY_RIGHT])){
		dir = 3;nTile++;
		pulando=0;
		if(nTile < 0) nTile = 6;
	    else 
		ataque = 0;	
	}
	if(ataque && (key[KEY_LEFT]) ){
		dir = 2;nTile++;
		pulando=0;
		
		if(nTile < 0) nTile = 6;
	    else 
		ataque = 0;	
	}
	if(ataque && dir == 0){
		dir = 3;nTile++;
		 if(nTile >= 6) dir == 0;
	    else 
		ataque = 0;	
	}
	if(ataque && dir == 1){
		dir = 2;nTile++;
		 if(nTile >= 6) dir == 0;
	    else 
		ataque = 0;	
	}

	
	if(pulando && p.y > pLimit - 90){
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
