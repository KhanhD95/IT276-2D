#include <SDL.h>
#include "ent.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "gf2d_audio.h"



int main(int argc, char * argv[])
{
	/*variable declarations*/
	int done = 0;
	int start = 0;
	const Uint8 * keys = NULL;
	

	int mx =0, my = 0;
	int count = 0;
	float mf = 0;
	int timer = 0;
	Uint8 mousestate;

	Sprite *sprite;
	Sprite *mouse;
	Sprite *enemy; //spawn circle enemy
	Sprite *enemyTri; //spawn triangle enemy
	Sprite *laser; //test laser
	Sprite *enemyHex; //spawn hexagon enemy
	Sprite *blueCir; // spawn blue circle 
	Sprite *orangeTri; // spawn orange tri enemy 
	Sprite *blueHex; // spawn blue hexagon enemy 
	Sprite *menu; // load menu 
	Sprite *speedBoost; // shooting power up
	Sprite *playerS; // testing player
	Sprite *blueLaser; //testing enemy laser

	Vector4D mouseColor = { 120,200,300,255 }; //was 255,100,255,200

	Entity tester; //tester is circle enemy var
	Entity tri; //tri is triangle enemy var
	Entity slaser[5]; //test laser array
	Entity hex; //hex is hexagon enemy var
	Entity circle; // blue circle enemy var 
	Entity oTri; // orange tri enemy var
	Entity bHex; // blue hex enemy var
	Entity sBoost; // shooting boost var 
	Entity player; // testing player var
	Entity blaser[5];// enemy laser

	SDL_Event event1; // event type

	Mix_Music *music; //music var
	Mix_Chunk *blaster; //blaster sound
	Mix_Chunk *sPower; // shooting power up sound

	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"gf2d",
		1200,
		720,
		1200,
		720,
		vector4d(0, 0, 0, 255),
		0);
	gf2d_graphics_set_frame_delay(16);
	gf2d_audio_init(256, 16, 4, 1, 1, 1);
	gf2d_sprite_init(1024);
	gf2d_entity_system_init(200); // add 200 max entities
	SDL_ShowCursor(SDL_DISABLE);

	/*game setup*/

	/*background,player,projectile, power ups*/
	sprite = gf2d_sprite_load_image("images/backgrounds/space_background_2_by_tonic_tf-d8doqs3.png");
	menu = gf2d_sprite_load_image("images/backgrounds/Mainmenu.png");// testing menu
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	laser = gf2d_sprite_load_all("images/laserRed12.png", 13, 57, 16); // testing laser
	speedBoost = gf2d_sprite_load_all("images/bolt_gold.png",32,32,16); //testing speed boost
	blueLaser = gf2d_sprite_load_all("images/laserBlue10.png",13,57,16);// testing blue laser
	
	
	/*Player & Enemies*/
	playerS = gf2d_sprite_load_all("images/playerShip1_green.png",100,100,16); //testing player
	enemy = gf2d_sprite_load_all("images/ufoGreen.png", 100, 100, 16); //circle enemy
	enemyTri = gf2d_sprite_load_all("images/playerShip3_blue.png", 100, 100, 16); //triangle enemy
	enemyHex = gf2d_sprite_load_all("images/enemyRed4.png", 100, 100, 16); //hexagon enemy
	blueCir = gf2d_sprite_load_all("images/ufoBlue.png", 100, 100, 16);// blue circle
	orangeTri = gf2d_sprite_load_all("images/playerShip3_orange.png", 100, 100, 16); // orange triangle
	blueHex = gf2d_sprite_load_all("images/enemyBlue4.png", 100, 100, 16);// blue hex 


	/*Audio*/
	music = Mix_LoadMUS("sounds/Kaivon - Reborn.wav"); //testing theme music
	blaster = Mix_LoadWAV("sounds/blaster.wav"); //testing blaster sound
	sPower = Mix_LoadWAV("sounds/Metroid_Door-Brandino480-995195341.wav"); // testing power up sound
	Mix_PlayMusic(music, -1);

	//Circle enemy
	gf2d_entity_new(); //save space for new ent
	tester.sprite = enemy;
	tester.inuse = 1;
	tester.position = vector2d(300, 300);
	tester.frame = 0; // initialize frame var
	tester.scale = vector2d(0.5, 0.5);
	tester.scaleCenter = vector2d(0, 0);

	//Circle enemy #2
	gf2d_entity_new(); //save space for new ent
	circle.sprite = blueCir;
	circle.inuse = 1;
	circle.position = vector2d(1000, 100);
	circle.frame = 0; // initialize frame var
	circle.scale = vector2d(0.5, 0.5);
	circle.scaleCenter = vector2d(0, 0);

	//Triangle enemy
	gf2d_entity_new();
	tri.sprite = enemyTri;
	tri.inuse = 1;
	tri.position = vector2d(300, 200);
	tri.frame = 0;
	tri.scale = vector2d(0.5, 0.5);
	tri.scaleCenter = vector2d(0, 0);

	//Triangle enemy #2
	gf2d_entity_new();
	oTri.sprite = orangeTri;
	oTri.inuse = 1;
	oTri.position = vector2d(700, 200);
	oTri.frame = 0;
	oTri.scale = vector2d(0.5, 0.5);
	oTri.scaleCenter = vector2d(0, 0);


	//Hexagon enemy
	gf2d_entity_new();
	hex.sprite = enemyHex;
	hex.inuse = 1;
	hex.position = vector2d(300, 100);
	hex.frame = 0;
	hex.scale = vector2d(0.5, 0.5);
	hex.scaleCenter = vector2d(0, 0);

	//Hexagon enemy#2
	gf2d_entity_new();
	bHex.sprite = blueHex;
	bHex.inuse = 1;
	bHex.position = vector2d(800, 300);
	bHex.frame = 0;
	bHex.scale = vector2d(0.5, 0.5);
	bHex.scaleCenter = vector2d(0, 0);

	//Testing player laser
	gf2d_entity_new();
	for (int i = 0; i < 5; i++) 
	{
		slaser[i].sprite = laser;
		slaser[i].inuse = 1;
		slaser[i].position = vector2d(0, 0);
		slaser[i].frame = 0.1;
		slaser[i].scale = vector2d(0.5, 0.5);
		slaser[i].scaleCenter = vector2d(1, 1);

	}
	//Testing enemy laser
	gf2d_entity_new();
	for (int i = 0; i < 5; i++) 
	{
		slaser[i].sprite = laser;
		slaser[i].inuse = 1;
		slaser[i].position = vector2d(0, 0);
		slaser[i].frame = 0.1;
		slaser[i].scale = vector2d(0.5, 0.5);
		slaser[i].scaleCenter = vector2d(1, 1);
	}

	//testing shooting boost
	gf2d_entity_new();
	sBoost.sprite = speedBoost;
	sBoost.inuse = 1;
	sBoost.position = vector2d(500, 500);
	sBoost.frame = 0;
	sBoost.scale = vector2d(0.75, 0.75);
	sBoost.scaleCenter = vector2d(1, 1);


	/*start menu loop*/
	while (!start)
	{
		SDL_PumpEvents();
		gf2d_graphics_clear_screen();
		gf2d_sprite_draw_image(menu, vector2d(0, 0));
		
		keys = SDL_GetKeyboardState(NULL);
		mousestate = SDL_GetMouseState(&mx, &my);
		mf += 0.1;
		if (mf >= 16.0)mf = 0;
		
		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);

		gf2d_grahics_next_frame();
		if ((SDL_BUTTON(SDL_BUTTON_LEFT)&mousestate))start = 1;
		
		if (keys[SDL_SCANCODE_ESCAPE])start = 1; // exit condition

	}

	/*main game loop*/
	while (!done)
	{
		
		timer++;
		SDL_PumpEvents();   // update SDL's internal event structures
		//SDL_PollEvent(&event1);

		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/

		//player mouse
		mousestate = SDL_GetMouseState(&mx, &my);
		mf += 0; // was 0.1
		if (mf >= 0)mf = 0; // was 16
		//if (player.frame >= 150) player.frame = 0;

		//speedboost
		sBoost.frame += 0;
		if (sBoost.frame >= 150) sBoost.frame = 0;


		//circle enemy

		tester.frame += 0;
		if (tester.frame >= 150) tester.frame = 0;

		//blue circle
		circle.frame += 0;
		if (circle.frame >= 150) circle.frame = 0;

		//triangle enemy

		tri.frame += 0;
		if (tri.frame >= 150) tri.frame = 0;

		//orange triangle enemy
		oTri.frame += 0;
		if (oTri.frame >= 150)oTri.frame = 0;

		//hexagon enemy
		hex.frame += 0;
		if (hex.frame >= 150)tri.frame = 0;

		//blue hexagon enemy
		bHex.frame += 0;
		if (bHex.frame >= 150)bHex.frame = 0;

		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame
			//backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));

		// shoot laser using array and timer method

		if ((SDL_BUTTON(SDL_BUTTON_LEFT)&mousestate) && timer >= 50) // change fire rate
		{
			slaser[count].position = vector2d(mx+ 20 , my + 15);
			count++;
			if (count > 4)
			{
				count = 0;
			}

			Mix_PlayChannel(-1, blaster, 0);
			timer = 0;

		}

		for (int i = 0; i < 5; i++)// check last laser position
		{
			if (slaser[i].position.x != 0 && slaser[i].position.y != 0) {
				slaser[i].position.y -= 5; // testing speed of laser 
				gf2d_entity_draw(&slaser[i]);
			}
		}

		//UI elements last

		//testing player mouse
		gf2d_entity_new(); //save space for new ent
		player.sprite = playerS;
		player.inuse = 1;
		player.position = vector2d(mx, my);
		player.frame = 0;
		player.scale = vector2d(0.5, 0.5);
		player.scaleCenter = vector2d(0, 0);

		gf2d_entity_draw(&player);

		//testing speed boost
		gf2d_entity_draw(&sBoost);

		//testing enemy circle y velocity
		tester.position.y -= 0.1;
		gf2d_entity_draw(&tester);
		

		//testing blue circle y velocity
		circle.position.y += 0.1;
		gf2d_entity_draw(&circle);
		
		//testing enemy triangle x velocity 
		tri.position.x -= 0.1;
		gf2d_entity_draw(&tri);
		
		//testing orange triangle x velocity
		oTri.position.x += 0.1;
		gf2d_entity_draw(&oTri);
		

		//testing enemy hexagon x+y velocity
		hex.position.x -= 0.1;
		hex.position.y += 0.1;
		int i = 0;
		if (slaser[i].position.x != 0 && slaser[i].position.y != 0)
		{
			slaser[i].position.y -= 5; // testing speed of laser 
			gf2d_entity_draw(&slaser[i]);
		}
		gf2d_entity_draw(&hex);
		

		//testing blue hexagon x+y velocity 
		bHex.position.x += 0.1;
		bHex.position.y -= 0.1;
		gf2d_entity_draw(&bHex);
		

		/*damamge system*/

		for (int i = 0; i < 5; i++)
		{
			//testing pick up boost 
			if (collide(&player, &sBoost) == true)
			{
				/*for (int i = 0; i < 5; i++)// check last laser position
				{
					if (slaser[i].position.x != 0 && slaser[i].position.y != 0) {
						slaser[i].position.y -= 10; // testing speed of laser 
						slaser[i].position.x += 10;
						gf2d_entity_draw(&slaser[i]);
					}
				}*/
				Mix_PlayChannel(-1, sPower, 0);
				gf2d_sprite_delete(speedBoost);
				gf2d_sprite_free(speedBoost);
				//gf2d_entity_free(speedBoost);


			}


			if (collide(&slaser[i], &tester) == true)
			{
				//destroy green circle enemy
				gf2d_sprite_delete(enemy);
				gf2d_sprite_free(enemy);
				//gf2d_entity_free(enemy);
			}

			if (collide(&slaser[i], &circle) == true)
			{
				//destroy blue circle enemy
				gf2d_sprite_delete(blueCir);
				gf2d_sprite_free(blueCir);
			}

			if (collide(&slaser[i], &tri) == true)
			{
				//destroy blue triangle enemy
				gf2d_sprite_delete(enemyTri);
				gf2d_sprite_free(enemyTri);
			}

			if (collide(&slaser[i], &oTri) == true)
			{
				//destroy orange triangle enemy 
				gf2d_sprite_delete(orangeTri);
				gf2d_sprite_free(orangeTri);
			}

			if (collide(&slaser[i], &hex) == true)
			{
				//destroy red hexagon enemy
				gf2d_sprite_delete(enemyHex);
				gf2d_sprite_free(enemyHex);
			}


			if (collide(&slaser[i], &bHex) == true)
			{
				//destroy blue hexagon enemy 
				gf2d_sprite_delete(blueHex);
				gf2d_sprite_free(blueHex);
			}

		}
		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame   
		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
		//slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second());
	}

	//Mix_HaltMusic(blaster);
	//Mix_FreeMusic(blaster);
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
