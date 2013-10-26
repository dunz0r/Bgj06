// A Game for bacongamejam06
//

#include <stdio.h>

// Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, const char *argv[]){
	// Initialize Allegro
	al_init();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio;
	al_init_acodec_addon();
	al_reserve_samples(1000);
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_MOUSE_STATE mouse;
	return 0;
}
