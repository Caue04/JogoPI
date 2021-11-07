#include <allegro.h>

//funções
void sair();
void control();

struct obj{int wx, wy, x, y, w, h;};
struct obj
	p = {0,0,500,50,64,64,0,0},
	bloco[13][15];

//Variáveis Globais
int sai    = 0;
int width  = 900;
int height = 720;
int dir = 0;
int nTile = 0;

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
	
	//Variáveis Locais
	buffer = create_bitmap(width, height);
	imagem = load_bitmap("sprites/robosprite.bmp", NULL);
		
	while (!(sai || key[KEY_ESC]))
	{		
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
void sair(){sai= 1;}
END_OF_FUNCTION(sair);

void control(){
	
	if(key[KEY_RIGHT]){p.x+=10; dir = 0; nTile++;}
	else if(key[KEY_LEFT]) {p.x-=10; dir = 1; nTile++;}
	else nTile = 0;
	if(nTile < 0) nTile = 6;
	if(nTile > 6) nTile = 0;
	
}

