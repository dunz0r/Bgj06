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

//block class, maybe circular
class cBlock
{
	public:
		float x,y;
		bool exists;
	void draw()
	{
		if(exists == true)
		{
			al_draw_filled_circle(x,y,16,al_map_rgb(255,0,0));
		}
	}
};

//levelcreate
class cLevel
{
	public:
		float blockx,blocky,blocksin;
		int blocknum, blockamount;
		cBlock oBlock[100];
		bool makeLevel;
		void init()
		{
			makeLevel = true;
			blocknum = 0;
			blockamount = 100;
			blockx = 0;
			blocky = 400;
			blocksin = 0;
		}
		void createLevel()
		{
			blocksin +=0.2;
			if(makeLevel == true)
			{
				if(blocknum < blockamount)
				{
					oBlock[blocknum].x = blockx;
					oBlock[blocknum].y = blocky;
					oBlock[blocknum].exists = true;
					blockx += 32;
					blocky +=sin(blocksin)*20;
					blocknum ++;
				}
			}
		}
		void draw()
		{
			for(int i = 0; i < blocknum;i++)
			{
				oBlock[i].draw();
			}
			al_draw_ellipse(480,200,500,60,al_map_rgb(255,0,0),28);
			al_draw_filled_rectangle(0,0,1024,768,al_map_rgb(0,0,0));
		}
};

//player class, runs around and jumps
class cPlayer
{
	public:
		float x,y,vspeed,hspeed,gravity, dx,dy;
		bool onGround;
	void create()
	{
		onGround = false;
		x = 200;
		y = 400;
		vspeed = 0;
		gravity = 0.2;
	}
	void checkCollision(float otherx, float othery, ALLEGRO_KEYBOARD_STATE *key)
	{
		dx = otherx-x;
		dy = othery-y;
		if(((dx*dx)+(dy*dy))< (32*32))
		{
			onGround = true;
		}
		if(((dx*dx)+(dy*dy))< (32*32))//collision has happened
		{
			gravity = 0;
			vspeed = 0;
			x -= dx/10;
			y -= dy/10;
		}
		else
		{
			gravity = 0.2;
		}
	};
	void run(ALLEGRO_KEYBOARD_STATE *key)
	{
		//vspeed += gravity;
		x += hspeed;
		y += vspeed;
		vspeed += gravity;
		if(al_key_down(key,ALLEGRO_KEY_UP)&&onGround == true)
		{
			vspeed = -4.5;
			onGround = false;
		}
		if(al_key_down(key,ALLEGRO_KEY_RIGHT))
		{
			hspeed = 2;
		}
		if(al_key_down(key,ALLEGRO_KEY_LEFT))
		{
			hspeed = -2;
		}	
		if(al_key_down(key,ALLEGRO_KEY_DOWN))
		{
			vspeed = 2;
		}
		if(!al_key_down(key,ALLEGRO_KEY_LEFT)&&!al_key_down(key,ALLEGRO_KEY_RIGHT)){hspeed = 0;};
	}
	void draw()
	{
		if(onGround == true)
		{
			al_draw_filled_circle(x,y,16,al_map_rgb(0,0,255));
		}
		else
		{
			al_draw_filled_circle(x,y,16,al_map_rgb(0,255,0));
		}
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
    
    cLevel oLevel;
    oLevel.init();
    
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
				oLevel.createLevel();
				oPlayer.run(&key);
				//player collision check
				for(int i = 0;i<oLevel.blocknum;i++)
				{
					oPlayer.checkCollision(oLevel.oBlock[i].x,oLevel.oBlock[i].y,&key);
				}
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
			oLevel.draw();
			//////
		
            redraw = false;
            //
            al_flip_display();
        }
    }
    return 0;
};
