//Bacon game jam 06

#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const float fps = 60;

#define DISPLAY_WIDTH 1024
#define DISPLAY_HEIGHT 768
class cRainbow
{
	public:
		float cx,cy,rx,ry,thickness;
		ALLEGRO_COLOR color[7] = { al_map_rgb(0,0,0) };
	void create()
	{
		color[0] = al_map_rgb(255,0,0);
		color[1] = al_map_rgb(255,127,0);
		color[2] = al_map_rgb(255,255,0);
		color[3] = al_map_rgb(0,255,0);
		color[4] = al_map_rgb(0,0,255);
		color[5] = al_map_rgb(75,0,130);
		color[6] = al_map_rgb(143,0,255);
		rx = DISPLAY_WIDTH/2.0;
		ry = 200.0;
		cx = DISPLAY_WIDTH/2;
		cy = 220;
		thickness = 18.0;
	}

	void draw()
	{
		for (int i = 0; i < 7; i++) {
			al_draw_ellipse(cx, cy+(i*16), rx, ry, color[i], thickness);
		}
		al_draw_filled_rectangle(0, 220+(16*7), DISPLAY_HEIGHT, 220+(16*7), al_map_rgb(255,0,0));
	}
};
int main(int argc, char **argv )
{
	//inits
	al_init();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_reserve_samples(1000);
	al_init_image_addon();
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_MOUSE_STATE mouse;

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	al_hide_mouse_cursor(display);

	// Event queue
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool redraw = true;
	timer = al_create_timer(1.0/fps);
	event_queue = al_create_event_queue();

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	al_reserve_samples(1000);

	cRainbow oRainbow;
	oRainbow.create();
	//RUN
	while(1<2)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		al_get_keyboard_state(&key);
		al_get_mouse_state(&mouse);
		al_get_mouse_state_axis(&mouse,0);
		al_get_mouse_state_axis(&mouse,1);
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{

			//Runny tunny
			{

				if(al_key_down(&key,ALLEGRO_KEY_ESCAPE))
				{
					return 0;
				}


			}
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			//draw
			al_clear_to_color(al_map_rgb(0,0,0));
			oRainbow.draw();
			redraw = false;
			al_flip_display();
		}
	}
	return 0;
};
