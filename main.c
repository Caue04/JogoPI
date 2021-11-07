#include <allegro.h>

//funções
void sair();

//Variáveis Globais
int sai    = 0;
int width  = 800;
int height = 600;

BITMAP *buffer, *imagem;

int main() {
	
    //Iniciação
	allegro_init();
    install_keyboard();
	set_color_depth(32);
	set_window_title("Meu Programa");
	set_close_button_callback(sair);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);  
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	
	//Variáveis Locais
	buffer = create_bitmap(width, height);
	//img    = load_bitmap("img/imagem.bmp", NULL);
		
	while (!(sai || key[KEY_ESC]))
	{		
		//textprintf_ex(buffer, font, 10, 10, 0xffffff, -1,"Teste %i", txt);
		draw_sprite(screen, buffer, 0, 0);
		rest(10);
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

