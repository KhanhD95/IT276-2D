#include <SDL.h>
#include "ent.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
	Sprite *enemy; //spawn bug

    Vector4D mouseColor = {120,200,300,255}; //was 255,100,255,200
	Entity tester;
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
	gf2d_entity_system_init(100); // add 100 max entities
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/space_background_2_by_tonic_tf-d8doqs3.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	enemy = gf2d_sprite_load_all("images/ufoGreen.png", 100, 100, 16); //testing enemy

	gf2d_entity_new(); //save space for new ent
	tester.sprite = enemy;
	tester.inuse = 1;
	tester.position = vector2d(500, 5000);
	tester.frame = 0; // initialize frame var
	tester.scale = vector2d(1, 1);
	tester.scaleCenter = vector2d(100, 100);


    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/

        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;

			tester.frame += 0.1;
			if (tester.frame >= 150) tester.frame = 0;

        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
            
            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);

			//enemy elements
			gf2d_entity_draw(&tester);
			gf2d_sprite_draw(
				enemy,
				vector2d(500, 200),
				&tester.scale,
				&tester.scaleCenter,
				NULL,
				NULL,
				NULL,
				0);

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame   
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
