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

class cPlayer
{
	public:
		float x,y,vspeed,hspeed,gravity;
	void create()
	{
		x = 200;
		y = 400;
		vspeed = 0;
		gravity = 0.2;
	}
	void run(ALLEGRO_KEYBOARD_STATE *key)
	{
		//vspeed += gravity;
		x += hspeed;
		y += vspeed;
		vspeed += gravity;
		if(y < 600)
		{
			gravity = 0.2;
		}
		else
		{
			vspeed = 0;
			gravity = 0;
		}
		if(al_key_down(key,ALLEGRO_KEY_RIGHT))
		{
			vspeed = 0;
			hspeed = 2;
		}
		else if(al_key_down(key,ALLEGRO_KEY_LEFT))
		{
			vspeed = 0;
			hspeed = -2;
		}
		else if(al_key_down(key,ALLEGRO_KEY_UP))
		{
			hspeed = 0;
			vspeed = -2;
		}
		else if(al_key_down(key,ALLEGRO_KEY_DOWN))
		{
			hspeed = 0;
			vspeed = 2;
		}
	}
	void draw()
	{
		al_draw_filled_circle(x,y,16,al_map_rgb(0,0,255));
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
    
    display = al_create_display(1024, 768);
    
    al_hide_mouse_cursor(display);

	//
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;
    timer = al_create_timer(1.0/fps);
    event_queue = al_create_event_queue();
    
    //SAMPLES
    
    
    ///OBJECTS
    cPlayer oPlayer;
    oPlayer.create();
    
    ////
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    al_reserve_samples(1000);
    
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
		
				oPlayer.run(&key);
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
		
			oPlayer.draw();
		
			//////
		
            redraw = false;
            //
            al_flip_display();
        }
    }
    return 0;
};
