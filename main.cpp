/* Name : Muhammad Rahat Shafi
Student id : 22i-1061
Final Project Of Programming Funndamentals BSCS 2022*/
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
using namespace std;	//reove this also
#include<iostream>	//remove it after testing
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include<fstream>	//I have added this as I would need to read and write to files...
using namespace sf;
int main(){
    start:
    	srand(time(0));
  	//////////////////////////////////
   	Texture obj1, obj2, obj3;
    	obj1.loadFromFile ("img/tiles.png");
    	obj2.loadFromFile ("img/background.png");
   	obj3.loadFromFile ("img/frame.png");
   	//Added shadow object for shadows
   	RectangleShape shadow(Vector2f(18, 18)); // Shadow looks
	shadow.setFillColor(Color::Transparent);
	shadow.setOutlineThickness(0.5);
	shadow.setOutlineColor(Color::White);
   	Sprite sprite(obj1), background(obj2), frame(obj3);	
    	//////////////////////////////////
    	Text text, text_1, score, text_2, text_3;
	Font font;
    	font.loadFromFile("arial.ttf");	//Loading the font that I have added in this folder (arial)...
    	//////////////////////////////////
   	int delta_x=0, colorNum_array[3]={1};	//Making color num an array to store the colors of next block
    	float timer=0, delay=0.3;
    	bool rotate=0;
    	int colorNum=1;	//this is also required to store current blocks colors ... 
   	//////////////////////////These below are some varibales I have made for the program to progress.../////////////////////////////
  	//This is the time from the start of the game till its end...
    	float total_time = 0;	
	//To make a boolean variable check if we want to immeditaely drop an object...
	bool drop_immediate = false;
	//To record a 'P' pressed by the user
	bool difficulty_increased=false;	//Shows time when the difficulty has not been increased...
	int current_level = 1;	// current level of the game..
	int rotation_number = 0;	//To see the rotation number of a block...
	int num_block;	//This was first declared in the function 'fallingpiece' but I needed it in function'rotate_pieces' so I have declared it here...
	int user_score = 0;	//To store the user score...
	int next_blocks_array[3] = {0,0,0};	//To store the upcoming blocks...
	static bool bomb_drop = false;	//To see if the bomb is coming or not...
	static int shadow_point[4][2] = {{0,0},{0,0},{0,0},{0,0}};	//To store the coordinates of shadow points..
	bool show_shadow = true;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //To display menu and act accordingly
	bool close_main = false;
	static int turn = 1;	//To see if this is the first time this loop is running(at the start of the game)...
	display_menu(close_main, turn, user_score);	//Function called to display main menu...
	turn++;	//Incrementing the turns so that the game knows if the menu is called the first time or in between the game...
    	Clock clock;
    	RenderWindow window(VideoMode(320, 480), title);
    	while (window.isOpen()){
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;
		total_time+=time;
		if (close_main == true)
			window.close();	//Thus if the user says to 'Exit' then this window will be closed as well...  
		//---Event Listening Part---//
		Event e;
		while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
		    if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
		        window.close();                            //Opened window disposes
		    if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
		        if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
		            rotate = true;                         //Rotation gets on
		        else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
		            delta_x = -1;                          //Change in X-Axis - Negative
		        else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
		            delta_x = 1;                           //Change in X-Axis - Positive
		        else if (e.key.code == Keyboard::Space)				//Checking for a spacebar pressed...
		        	drop_immediate = true;
		        else if (e.key.code == Keyboard::H)				//Checking for a 'H' key pressed pressed...
		        {
		        	display_menu(close_main, turn, user_score);
		        	if (close_main == true)
					window.close();	//Thus if the user says to 'Exit' then this window will be closed as well...  
		        }
		        	
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
			if (bomb_drop == false)	//As bomb should not be controlled like this...
		    	delay=0.05;	//If DOWN key is pressed, delay in falling piece decreases from 0.3 to 0.05...

			 
		///////////////////////////////////////////////
		///*** START CALLING YOUR FUNCTIONS HERE ***///
		if (bomb_drop == false)	//These below functions won't work for the bomb...
		{
			move_x (delta_x);	//To move the block across the x-axis...
			fallingPiece (timer, delay, colorNum_array, current_level, rotation_number, num_block, next_blocks_array,colorNum, bomb_drop, total_time);	//To fall the current block with time and to choose new blocks...
			rotate_piece(rotate, rotation_number, num_block);	//To rotate the block...
			bool restart = false;	//Boolaen to check for restart...
			game_over(check_game_over(), close_main,restart, user_score, window);	//To see if the game is over and to act accordingly...
			if (restart == true)	//If user choose to restart than this will take place...
			{
				turn = 1;	//As turn is static variable to have to reset it
				goto start;	//To restart the game...
			}
			if (close_main == true)	//If the user choose to end the game then this path will be followed...
				window.close();	//Thus if the user says to 'Exit' then this window will be closed as well...  
			int row_rem = row_removed ();	//This will remove filled rows and return the removed rows to (row_rem)...
			score_calculation(user_score, row_rem);	//This function will be used to calculate user score...
			space_bar_effect(drop_immediate);	//If space bar is pressed then this function will be used to immediately drop the block...
			add_shadow(shadow_point, show_shadow); //This will add shadow of the falling block...
		        increasing_difficulty(total_time, delay, difficulty_increased, user_score);	//This will increase the difficulty of the game as the time passes..
		        level(current_level, delay, difficulty_increased);	//This will handle the level of the game...
	 	}
	 	else	//If the bomb is falling then this path will be executed...
	 	{
	 		bool reset_grid = false;
			bomb_fell(bomb_drop, colorNum, timer, delay, reset_grid);	//This will make the bomb fall and then act accordingly...
			reset_the_grid(reset_grid);	//if the grid is to be reset the command will pass to the function(reset_grid)...
		}
		///*** YOUR CALLING STATEMENTS END HERE ***///
		//////////////////////////////////////////////
		window.clear(Color::Black);
		window.draw(background);
			////////////////////////////////////////This is used to give the title of "Next Block" on the screen...
			text_1.setFont(font); 
		text_1.setString("Next\nBlocks");
		text_1.setCharacterSize(24);
			text_1.setFillColor(Color::Yellow);
			text_1.setStyle(Text::Bold | Text::Underlined);
			text_1.setPosition(228,100);
			window.draw(text_1);
			/////////////////////////////////////////This is used to give the title of "Score" on the screen...
		text.setFont(font); 
		text.setString("Score");
		text.setCharacterSize(24);
			text.setFillColor(Color::Blue);
			text.setStyle(Text::Bold | Text::Underlined);
			text.setPosition(228,310);
			window.draw(text);
		////////////////////////////////////////This is used to give the User Score on the screen...
		score.setFont(font); 
		score.setString(to_string(user_score));	//I have used the to_string to covert integer type to string to display it on screen...
		score.setCharacterSize(24);
			score.setFillColor(Color::Cyan);
			score.setPosition(228,345);
			window.draw(score);
		//////////////////////////////////////////This is used to give the title of "Level" on the screen...
		text_2.setFont(font); 
		text_2.setString("Level");
		text_2.setCharacterSize(24);
			text_2.setFillColor(Color::Green);
			text_2.setStyle(Text::Bold | Text::Underlined);
			text_2.setPosition(228,370);
			window.draw(text_2);
		//////////////////////////////////////////This is used to show the current on the screen...
		text_3.setFont(font); 
		if (current_level == 1)
			text_3.setString("Beginner");
		else
			text_3.setString("Advance");
		text_3.setCharacterSize(24);
		if (current_level == 1)
			text_3.setFillColor(Color::White);
		else
			text_3.setFillColor(Color::Red);
		text_3.setStyle(Text::Bold);
		text_3.setPosition(200,400);
		window.draw(text_3);
		//////////////////////////////////////////
		
		for (int i=0; i<M; i++){
		    for (int j=0; j<N; j++){
		        if (gameGrid[i][j]==0)
		            continue;
		        sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
		        sprite.setPosition(j*18,i*18);
		        sprite.move(28,31); //offset
		        window.draw(sprite);
		    }
		}
		for (int i=0; i<4; i++){
		    sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
		    sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
		    sprite.move(28,31);
		    window.draw(sprite);
		  }
		  //This is used to display shadow point on the screen...
		 //For shadow_point...
		 if (show_shadow == true)
		 {
			for (int i=0; i<4; i++)
			{
				shadow.setPosition(shadow_point[i][0]*18,shadow_point[i][1]*18);
				shadow.move(28,31);
				window.draw(shadow);
			}
		  }
		  //Block Suggestions...//////////////////////////////////////////////////
		  //Making a similar grid(to the one created above) for blocks suggestion (first block suggestion)...
		  static int next_block_calc;
		  next_block_calc = 0;
		  //For the calculation of the number of next block according to the its position in blocks array...
		  int next_block = next_blocks_array[next_block_calc];//hardcode for testing...
		  //next_block_calc++;
		  for (int i=0; i<2; i++){
		    for (int j=0; j<4; j++){
		        if (gameGrid[i][j]==0)
		            continue;
		        sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
		        sprite.setPosition(j*18,i*18);
		        sprite.move(240,170); //offset
		        window.draw(sprite);
		    }
		}
		//BLOCKS[next_block][i] /2;	will give the x-axis values for the new block(that is to be displayed at tis position)...
		//BLOCKS[next_block][i] %2; will give the x-axis values for the new block(that is to be displayed at tis position)...
		for (int i=0; i<4; i++){
		    sprite.setTextureRect(IntRect(colorNum_array[next_block_calc]*18,0,18,18));
		    sprite.setPosition((BLOCKS[next_block][i] /2)*18,(BLOCKS[next_block][i] %2)*18);
		    sprite.move(240,170);
		    window.draw(sprite);
		  }
		  //Block one completed.../////////////////////////////////////////////////////
		  //Block two started...//////////////////////////////////////////////////////
		  //Making a similar grid(to the one created above) for blocks suggestion (second block suggestion)...
		  if (current_level==1)	//Due to increasing difficulty of the game, in advance level this won't be shown up...
		  {
			      next_block_calc = 1;
			      //For the calculation of the number of next block according to the its position in blocks array...
			      next_block = next_blocks_array[next_block_calc];//hardcode for testing...
			      //next_block_calc++;
			      for (int i=0; i<2; i++){
				for (int j=0; j<4; j++){
				    if (gameGrid[i][j]==0)
				        continue;
				    sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
				    sprite.setPosition(j*18,i*18);
				    sprite.move(240,215); //offset
				    window.draw(sprite);
				}
			    }
			    //BLOCKS[next_block][i] /2;	will give the x-axis values for the new block(that is to be displayed at tis position)...
			    //BLOCKS[next_block][i] %2; will give the x-axis values for the new block(that is to be displayed at tis position)...
			    for (int i=0; i<4; i++){
				sprite.setTextureRect(IntRect(colorNum_array[next_block_calc]*18,0,18,18));
				sprite.setPosition((BLOCKS[next_block][i] /2)*18,(BLOCKS[next_block][i] %2)*18);
				sprite.move(240,215);
				window.draw(sprite);
			      }
		  }
		  //Block two completed.../////////////////////////////////
		  //Block three started...////////////////////////////////
		  //Making a similar grid(to the one created above) for blocks suggestion (Third block suggestion)...
		  if (current_level==1)	//Due to increasing difficulty of the game, in advance level this won't be shown up...
		  {
			      next_block_calc = 2;
			      //For the calculation of the number of next block according to the its position in blocks array...
			      next_block = next_blocks_array[next_block_calc];//hardcode for testing...
			      //next_block_calc++;
			      for (int i=0; i<2; i++){
				for (int j=0; j<4; j++){
				    if (gameGrid[i][j]==0)
				        continue;
				    sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
				    sprite.setPosition(j*18,i*18);
				    sprite.move(240,260); //offset
				    window.draw(sprite);
				}
			    }
			    //BLOCKS[next_block][i] /2;	will give the x-axis values for the new block(that is to be displayed at tis position)...
			    //BLOCKS[next_block][i] %2; will give the x-axis values for the new block(that is to be displayed at tis position)...
			    for (int i=0; i<4; i++){
				sprite.setTextureRect(IntRect(colorNum_array[next_block_calc]*18,0,18,18));
				sprite.setPosition((BLOCKS[next_block][i] /2)*18,(BLOCKS[next_block][i] %2)*18);
				sprite.move(240,260);
				window.draw(sprite);
			      }
		  }
		  //Block three completed...////////////////////////////////
		  //////////////////////////////////////////////////////////
		 //The End For Block Suggestions...////////////////////////
		//////////////////////////////////////////////////////////
		
		//---The Final on Which Everything is Drawn Over is Loaded---//
		window.draw(frame);
		
		//---The Window that now Contains the Frame is Displayed---//
		window.display();
		if (difficulty_increased == false)
			delay=0.3;
	    }
    return 0;
}
