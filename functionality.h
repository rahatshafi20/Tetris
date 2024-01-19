/* Name : Muhammad Rahat Shafi
Student id : 22i-1061
Final Project Of Programming Fundamentals BSCS 2022*/
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */
//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int colorNum_array[], int current_level, int& rotation_number, int& num_block, int next_blocks_array[],int& colorNum, bool& bomb_drop, float total_time)
{
	static int first_block = true;	//To remove the first block(that contains only one piece) and replace it with another block...
    if (timer>delay || first_block == true)
    {
    	gameGrid[0][0] = 0;	//To remove the first red block that stucks on the screen...
    	if (first_block != true)
    	{
		    for (int i=0;i<4;i++)
		    {
		        point_2[i][0]=point_1[i][0];
		        point_2[i][1]=point_1[i][1];
		        point_1[i][1]+=1;                   //How much units downward
		    }
        }
        if (!anamoly() || first_block == true)
        {
        	first_block = false;
        	if (first_block != true)
		    	for (int k=0; k<4; k++)
		    	{
		    		gameGrid[point_2[k][1]][point_2[k][0]] = colorNum;
		    	}
		    	
			colorNum = colorNum_array[0];	//Storing the current blocks color in colorNum[4] as it will be used later...
			static int next_block = 0;
			static int turn = 0;	//This is beacuse the following loop should only be executed once...
			if (turn ==0)
			{
				for (int i=0; i<3; i++)
				{	
					if (current_level==1)	//Checking the current level of the game... 
						next_blocks_array[i] = rand()%4;
					else	//else if the level of the game is advance (level 2)
						next_blocks_array[i] = rand()%7;
					colorNum_array[i] = rand() % 7 + 1;	//Random colour generator...
				}
				turn++;
			}
          	num_block = next_blocks_array[next_block % 3];
			static int blocks_generated = 0;
			blocks_generated += 1;
			if (int(total_time) == rand()%100 || blocks_generated == 20 )	
			//To allow bomb to fall after random time or after 20 blocks fall..
			
        	{
        		bomb_drop = true;
        		blocks_generated = 0;	//reseting the value of blocks..
        		return;	//to exit this function...	
        	}
        	
        	
			//now adding new values to array and replacing the use ones...
			for (int j=0; j< 3; j++)
			{
				if (j != 2)	//Previous values moved one place ahead
				{
					next_blocks_array[j] = next_blocks_array[j+1];
					colorNum_array[j] = colorNum_array[j+1];
				}
				else	//new value to be added to the vacant place created (by moving values forward)...
				{
					if (current_level==1)	//Checking the current level of the game... 
						next_blocks_array[j] = rand()%4;
					else	//else if the level of the game is advance (level 2)
						next_blocks_array[j] = rand()%7;
					colorNum_array[j] = rand() % 7 + 1;	//Random colour generator...
				}
			}
          	int random_x_value = rand()%6;	//This will generate random x position of bonm within range of (0-5)
            for (int k=0 ; k<4 ; k++)
            {
            	point_1[k][0] = BLOCKS[num_block][k] / 2 + random_x_value;	//X-Axis...
            	point_1[k][1] = BLOCKS[num_block][k] % 2;	//Y-Axis...
            }
        
                //I have changed point_1[i][0] = BLOCKS[n][i] % 2; into point_1[i][0] = BLOCKS[n][i] / 2; as x axis has to store values from 0 to 3, also i have changed point_1[i][1] = BLOCKS[n][i] / 2; into point_1[i][1] = BLOCKS[n][i] % 2; as y axis only needs to store 0 and 1;
            rotation_number = 0;	//I have reset the rotation number as after each block the rotation number should be reset...
        }
        timer=0;  
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
//Function Number 1 :
//Function used to move the block to the left or right...
void move_x (int &delta_x)	
{
	bool move = true;
	if (delta_x == 1)	
	{
		for (int k=0; k<4 ; k++)
		{
			 if (point_1[k][0] >= N-1 || (gameGrid[point_1[k][1]][point_1[k][0]+1] !=0 && gameGrid[point_1[k][1]][point_1[k][0]+1] !=10))
//To check that the block should not be at the right end and no other block except a shadow should be at the place of movement...
			 {
			 	move = false;
			 	break;
			 }
		}
	}
	if (delta_x == -1)	
	{
		for (int k=0; k<4 ; k++)
		{
			 if (point_1[k][0] <= 0 || (gameGrid[point_1[k][1]][point_1[k][0]-1] !=0 && gameGrid[point_1[k][1]][point_1[k][0]-1] !=0))	
//To check that the block should not be at the left end and no other block except a shadow should be at the place of movement...
			 {
	 			move = false;
			 	break;
			 }
		}
	}

	if (move == true)
	{ 
		for (int m=0; m<4 ; m++)	
			point_1[m][0] += delta_x;
	}
	delta_x = 0;	//To reset delta_x...
}

//Function Number 2 :
//Function used to rotate the piece...
void rotate_piece(bool& rotate, int& rotation_number, int& num_block)
{
	if (rotate == true)
	{

	/*To make the logic of this what I did is that I took a simple block of the shape. Then I numbered them 
	  according to the same which I had in the BLOCKS array. Then I made rotations to see which block should 
	  change position and how (x and y shift). Then I detected the piece that should be changed. In my program
	  first i divided each piece (4 pieces) into x and y coordinated and then I applied the changes...
	*/
	//One thing that is to be noted in my program is that after 4 rotations (360 degrees) the pieces form
	//the same arrangment as they originally had, which makes the rotations generic...
		
		rotation_number += 1;
		//Each block has 4 piece and each piece has 2 coordinates so I am storing their information sepaately..
			
		int piece_1_x = point_1[0][0];
		int piece_1_y = point_1[0][1];
			
		int piece_2_x = point_1[1][0];
		int piece_2_y = point_1[1][1];
			
		int piece_3_x = point_1[2][0];
		int piece_3_y = point_1[2][1];
			
		int piece_4_x = point_1[3][0];
		int piece_4_y = point_1[3][1];
		
		bool should_rotate = true;
		//I will check if the place where the piece should move should be availaible for the block (should be within
		//the grid and should not be occupied by any other block.) If it is avaliable then this boolean will remain true
		// and allow the rotation, otherwise it will become false and will not allow rotation...
		switch (num_block)
		{
			case 0:	break;	//Block 0 doesnot rotate...
			case 1:	////////////Case 1 starts here//////////////////////////
				if (rotation_number % 4 == 1 && should_rotate == true)	
				//If it is the first rotation of the block (90 degree rotation)...
				{
				//Piece 1 will move at the up of piece 2 so following shifts will use it to do so...
					point_1[0][0] = piece_1_x + 1;	//its x value will increase by 1...
					point_1[0][1] = piece_1_y - 1;	//its y value will decrease by 1...
				//Then piece 3 will move below piece 2...	
					
					point_1[2][0] = piece_3_x - 1;	//its x value will decrease by 1...
					point_1[2][1] = piece_3_y + 1;	//its y value will increase by 1...
				//And at the end piece 4 will move below piece 3...	
					point_1[3][0] = piece_4_x - 2;	//its x value will decrease by 2...
					point_1[3][1] = piece_4_y + 2;	//its y value will increase by 2...
				}
				if (rotation_number % 4 == 2 && should_rotate == true)
				//If it is the second rotation of the block (180 degree rotation)...
				{
				//Piece 2 will move one unit downwards...
					point_1[1][1] = piece_2_y + 1;	//its y value will increase by 1...
				//Piece 1 will move 2 units downwards and 1 unit left...
					point_1[0][0] = piece_1_x - 1;	//its x value will decrease by 1...
					point_1[0][1] = piece_1_y + 2;	//its y value will increase by 2...
				//Piece 3 will move 1 units right...
					point_1[2][0] = piece_3_x + 1;	//its x value will increase by 1...
				//Piece 4 will move 2 units upwards and 2 unit right...
					point_1[3][0] = piece_4_x + 2;	//its x value will increase by 2...
					point_1[3][1] = piece_4_y - 1;	//its y value will decrease by 1...
				}
				if (rotation_number % 4 == 3 && should_rotate == true)
				//If it is the third rotation of the block (270 degree rotation)...
				{
				//Piece 2 will move one unit to the right...
					point_1[1][0] = piece_2_x + 1;	//its x value will increase by 1...
				//Piece 3 will move 1 units upwards...
					point_1[2][1] = piece_3_y - 1;	//its y value will decrease by 1...
				//Piece 1 will move 1 units downwards and 2 unit right...
					point_1[0][0] = piece_1_x + 2;	//its x value will increase by 2...
					point_1[0][1] = piece_1_y + 1;	//its y value will increase by 2...
				//Piece 4 will move 2 units upwards and 1 unit left...
					point_1[3][0] = piece_4_x - 1;	//its x value will decrease by 1...
					point_1[3][1] = piece_4_y - 2;	//its y value will decrease by 2...
				}
				if (rotation_number % 4 == 0 && should_rotate == true)
				//If it is the fourth rotation of the block (360 degree rotation)...
				{
				//Bringing Piece 1 back to its original place...
					point_1[0][0] = piece_1_x - 2;	//Its x value decreases by 2...
					point_1[0][1] = piece_1_y - 2;	//Its y value decreases by 1...
				//Now bringing piece 2 to where it was originally..
					point_1[1][0] = piece_2_x - 1;	//its x value will decrease by 1...
					point_1[1][1] = piece_2_y - 1;	//its y value will decrease by 1...
				//Piece 3 is where it was originally...
				//Now bringing piece 4 to where it was originally..
					point_1[3][0] = piece_4_x + 1;	//its x value will increase by 1...
					point_1[3][1] = piece_4_y + 1;	//its y value will increase by 1...
				}
				break;
			         ////////////Case 1 ends here////////////////////////////
			case 2:	////////////Case 2 starts here//////////////////////////
				//Note : here centre of rotation is piece 3
				if (rotation_number % 4 == 1 && should_rotate == true)	
				//If it is the first rotation of the block (90 degree rotation)...
				{
				//Piece 1 will move at the up of piece 3(the centre of rotation)so following shifts will use it to do so...
					point_1[0][0] = piece_1_x + 1;	//its x value will increase by 1...
				//Then piece 4 will move below piece 3...	
					point_1[3][0] = piece_4_x - 1;	//its x value will decrease by 1...
					point_1[3][1] = piece_4_y + 1;	//its y value will increase by 1...
				//And at the end piece 2 will move one unit down...	
					point_1[1][1] = piece_2_y + 1;
				}
				if (rotation_number % 4 == 2 && should_rotate == true)	
				//If it is the second rotation of the block (180 degree rotation)...
				{
				//Piece 2 will move one unit upwards...
					point_1[1][1] = piece_2_y - 1;	
				//Piece 1 will move one unit downwards and 1 unit right...
					point_1[0][0] = piece_1_x + 1;	
					point_1[0][1] = piece_1_y + 1;	
				//Piece 4 will move one unit right...
					point_1[3][0] = piece_4_x + 1;	
				}
				
				if (rotation_number % 4 == 3 && should_rotate == true)	
				//If it is the third rotation of the block (270 degree rotation)...
				{
				//Piece 1 will move one unit up...
					point_1[0][1] = piece_1_y - 1;	
				//Piece 2 will move 1 units upwards and 1 unit right...
					point_1[1][0] = piece_2_x + 1;
					point_1[1][1] = piece_2_y - 1;	
				//Piece 4 will move 1 units left...
					point_1[3][0] = piece_4_x - 1;	
				}
				if (rotation_number % 4 == 0 && should_rotate == true)	
				//If it is the fourth rotation of the block (360 degree rotation)...
				{
				//Bringing Piece 1 back to its original place...
					point_1[0][0] = piece_1_x - 2;	//Its x value decreases by 2...
				//Now bringing piece 2 to where it was originally..
					point_1[1][0] = piece_2_x - 1;	//its x value will decrease by 1...
					point_1[1][1] = piece_2_y + 1;	//its y value will increase by 1...
				//Piece 3 is where it was originally...
				//Now bringing piece 4 to where it was originally..
					point_1[3][0] = piece_4_x + 1;	//its x value will increase by 1...
					point_1[3][1] = piece_4_y - 1;	//its y value will decrease by 1...
				}
				break;
					 /////////////Case 2 ends here///////////////////////////
			case 3:	////////////Case 3 starts here//////////////////////////
				//Note Piece 3 has been used as rotating point in this case
				if (rotation_number % 4 == 1 && should_rotate == true)	
				//If it is the first rotation of the block (90 degree rotation)...
				{
				//Piece 1 will move one unit up...
					point_1[0][1] = piece_1_y - 1;
				//Then piece 4 will move one unit left ...	
					point_1[3][0] = piece_4_x - 1;
				//And at the end piece 3 will move one unit down and one unit left...	
					point_1[2][0] = piece_3_x - 1;
					point_1[2][1] = piece_3_y + 1;
				}
				if (rotation_number % 4 == 2 && should_rotate == true)	
				//If it is the second rotation of the block (180 degree rotation)...
				{
				//Piece 1 will move one unit downwards...
					point_1[0][1] = piece_1_y + 1;	
				//Piece 4 will move 1 units downwards and 1 unit right...
					point_1[3][0] = piece_4_x + 1;	
					point_1[3][1] = piece_4_y + 1;	
				//Piece 3 will move 1 units left...
					point_1[2][0] = piece_3_x - 1;	
				}
				if (rotation_number % 4 == 3 && should_rotate == true)	
				//If it is the third rotation of the block (270 degree rotation)...
				{
				//Piece 3 will move 1 units right...
					point_1[2][0] = piece_3_x + 1;
				//Piece 1 will move 1 units upwards and 1 unit right...
					point_1[0][0] = piece_1_x + 1;
					point_1[0][1] = piece_1_y - 1;
				//Piece 4 will move 1 units downwards...
					point_1[3][1] = piece_4_y + 1;
				}
				if (rotation_number % 4 == 0 && should_rotate == true)	
				//If it is the fourth rotation of the block (360 degree rotation)...
				{
				//Bringing Piece 1 back to its original place...
					point_1[0][0] = piece_1_x - 1;	//Its x value decreases by 1...
					point_1[0][1] = piece_1_y + 1;	//Its y value increases by 1...
				//Now bringing piece 3 to where it was originally..
					point_1[2][0] = piece_3_x + 1;	//its x value will increase by 1...
					point_1[2][1] = piece_3_y - 1;	//its y value will decrease by 1...
				//Piece 2 is where it was originally...
				//Now bringing piece 4 to where it was originally..
					point_1[3][1] = piece_4_y - 2;	//its y value will decrease by 2...
				}
				break;
			         ////////////Case 3 ends here///////////////////////////
			case 4:	////////////Case 4 starts here//////////////////////////
				//Note : here centre of rotation is piece 3
				if (rotation_number % 4 == 1 && should_rotate == true)	
				//If it is the first rotation of the block (90 degree rotation)...
				{
				//Then piece 4 will move below piece 3...	
					point_1[3][0] = piece_4_x - 1;	//its x value will decrease by 1...
					point_1[3][1] = piece_4_y + 2;	//its y value will increase by 2...
				//And piece 2 will move one unit left...	
					point_1[1][0] = piece_2_x - 1;
				}
				if (rotation_number % 4 == 2 && should_rotate == true)	
				//If it is the second rotation of the block (180 degree rotation)...
				{
				//Piece 2 will move one unit downwards and 2 units right...
					point_1[1][0] = piece_2_x + 2;
					point_1[1][1] = piece_2_y + 1;	
				//Piece 1 will move one unit downwards...
					point_1[0][1] = piece_1_y + 1;	
				}
				if (rotation_number % 4 == 3 && should_rotate == true)	
				//If it is the third rotation of the block (270 degree rotation)...
				{
				//Piece 1 will move 2 units up and one unit right...
					point_1[0][0] = piece_1_x + 1;
					point_1[0][1] = piece_1_y - 2;	
				//Piece 4 will move 1 units right...
					point_1[3][0] = piece_4_x + 1;	
				}
				if (rotation_number % 4 == 0 && should_rotate == true) 	
				//If it is the fourth rotation of the block (360 degree rotation)...
				{
				//Bringing Piece 1 back to its original place...
					point_1[0][0] = piece_1_x - 1;	//Its x value decreases by 1...
					point_1[0][1] = piece_1_y + 1;	//Its y value increases by 1...
				//Now bringing piece 2 to where it was originally..
					point_1[1][0] = piece_2_x - 1;	//its x value will decrease by 1...
					point_1[1][1] = piece_2_y - 1;	//its y value will decrease by 1...
				//Piece 3 is where it was originally...
				//Now bringing piece 4 to where it was originally..
					point_1[3][1] = piece_4_y - 2;	//its y value will decrease by 2...
				}
				break;
					 ////////////Case 4 ends here////////////////////////////
			case 5:	////////////Case 5 starts here//////////////////////////
				//Note : here centre of rotation is piece 3
				if (rotation_number % 4 == 1 && should_rotate == true)	
				//If it is the first rotation of the block (90 degree rotation)...
				{
				//Piece 1 will move at the left of piece 3(the centre of rotation)so following shifts will use it to do so...
					point_1[0][1] = piece_1_y + 1;	//its y value will increase by 1...
				//Then piece 4 will move below piece 1...	
					point_1[3][0] = piece_4_x - 2;	//its x value will decrease by 2...
					point_1[3][1] = piece_4_y + 1;	//its y value will increase by 1...
				}
				if (rotation_number % 4 == 2 && should_rotate == true)
					//If it is the second rotation of the block (180 degree rotation)...
				{
				//Piece 2 will move two unit downwards...
					point_1[1][1] = piece_2_y + 2;	
				//Piece 4 will move two unit right...
					point_1[3][0] = piece_4_x + 2;	
				}
				if (rotation_number % 4 == 3 && should_rotate == true)
				//If it is the third rotation of the block (270 degree rotation)...
				{
				//Piece 1 will move one unit up and two units right...
					point_1[0][0] = piece_1_x + 2;	
					point_1[0][1] = piece_1_y - 1;	
				//Piece 4 will move 1 units up...
					point_1[3][1] = piece_4_y - 1;	
				}
				if (rotation_number % 4 == 0 && should_rotate == true)
				//If it is the fourth rotation of the block (360 degree rotation)...
				{
				//Bringing Piece 1 back to its original place...
					point_1[0][0] = piece_1_x - 2;	//Its x value decreases by 2...
				//Now bringing piece 2 to where it was originally..
					point_1[1][1] = piece_2_y - 2;	//its y value will decrease by 2...
				//Piece 3 is where it was originally...
				//Piece 4 is also where it was originally...
				}
				break;
			         ////////////Case 5 ends here////////////////////////////
			case 6:	////////////Case 6 starts here//////////////////////////
				if (rotation_number % 4 == 1 && should_rotate == true)	
				//If it is the first rotation of the block (90 degree rotation)...
				{
				//In first rotation only last piece(the last piece on my block array) will change its value...
					point_1[3][0] = piece_4_x - 1;	//its x value will decrease by 1...
					point_1[3][1] = piece_4_y + 1;	//its y value will increase by 1...
				}
				if (rotation_number % 4 == 2 && should_rotate == true)	
				//If it is the second rotation of the block (180 degree rotation)...
				{
				//Bringing Piece 4 back to its position...so that order remains unchanged...
					point_1[3][0] = piece_4_x + 1;	//its x value will decrease by 1...
					point_1[3][1] = piece_4_y - 1;	//its y value will increase by 1...
				//Now chainging position of block 2 to meet the rotation requirements...
					point_1[1][1] = piece_2_y + 2;	//its y value will increase by 2...
				}
				if (rotation_number % 4 == 3 && should_rotate == true)	
				//If it is the third rotation of the block (270 degree rotation)...
				{
				//In the third rotation only first piece(the first piece on my block array) will change its value...
					point_1[0][0] = piece_1_x + 1;
					point_1[0][1] = piece_1_y - 1;
				}
				
				if (rotation_number % 4 == 0 && should_rotate == true)	
				//If it is the fourth rotation of the block (360 degree rotation)...
				{
				//Bringing Piece 1 back to its original place...
					point_1[0][0] = piece_1_x - 1;
					point_1[0][1] = piece_1_y + 1;
				//Now bringing piece 2 to where it was originally..
					point_1[1][1] = piece_2_y - 2;	//its y value will decrease by 2...
				}
				break;
			////////////////////////////Case 6 ends here//////////////////////
			//A default case is not rquired as there are only 7 shapes which are to be choosen by the system...
		}
		rotate = false;
	}
}
//Function Number 3 :
//To check if the grid is full to see whether the game is over or not...
bool check_game_over()
{
	bool found = false;
	int filled_rows =0;
	for (int rows=0; rows<M; rows ++ )
	{
		for (int col = 0 ; col < N ; col++)
		{
			if (gameGrid[rows][col] != 0)
			{
				filled_rows++;
				break;
			}
		}
	}
	if (filled_rows == 20)
		found = true;
	return found;
}
//Function Number 4 :
//This function is used to reset the grid for replay....
void reset_the_grid(bool found)
{
	
	if (found == true)
	{
		for (int k = 0; k<M ; k++)
		{
			for (int l=0; l<N; l++)
				gameGrid[k][l]=0;	//Resetting the grid...
		}
	}
	
}

//Function Number 5 :
//Function to add shadow on the falling piece...
void add_shadow(int shadow_point[][2],bool& show_shadow)
{
	show_shadow = true;
	int row;	//will store the row number
    bool empty;	//To check that the row is empty or not...
    for (int i=0;i<4;i++)
    {
		for (int k=0; k<4; k++)
		{
			if (point_1[k][1] == shadow_point[i][1] || ((point_1[k][1]+1) == shadow_point[i][1]))
				show_shadow == false;
		}
    }
    for (int i=0; i<4; i++)
	{
		shadow_point[i][0] = 0;
		shadow_point[i][1] = 0;
	}
    if (show_shadow == true)
    {	
		for (int k=0; k<4; k++)
		{
			shadow_point[k][0]=point_1[k][0];
			shadow_point[k][1]=point_1[k][1];
		}
		for (row=0; row<M; row++)	//This will go from first row till the last row...
		{
				empty = true;
				for (int k=0; k<4; k++)
				{
					if (gameGrid[row][point_1[k][0]] != 0 && row != point_1[k][1]) 	
					//This will help search in only the column under the piece..
					{
						empty = false;
						row--;
						break;
					}
				}
				if (empty == false || row == M-1)	//added row==19 to end loop if this is start and no row is filled up...
					break;
		} 
		bool move_shadow = true;
		int counter = 0;	
		//I have added this counter to repeat this only as many times as there are rows so that at no stage the loop beacomes infinite...
		do
		{
			for (int i=0; i<4; i++)
			{
				shadow_point[i][1] += 1;
				if (shadow_point[i][1] == row)
				{
					move_shadow = false;
				}
			}
			counter++;
			if (counter == M-1 )
				break;
		}
		while (move_shadow == true);
		} 
}



//This function will remove the rows which the user has successfully filled...
//Function Number 6 :
int row_removed ()
{
	int row_rem_counter = 0, row,col;
	bool row_filled;
	
	for (row =0; row < M; row ++)
	{
		row_filled = true;	//To check if a particular row is filled or not...
		for(int col =0; col <N; col ++)
		{
			if (gameGrid[row][col] == 0 || gameGrid[row][col] == 12)	
			//This will check for any vacant position on the grid which shoud also not be 12 as 12 is used to fill the rows whcih should not be used and it is also used for shadows......
			{
				row_filled = false;
				break;
			}
		}
		if (row_filled == true)	//If there is no vacant position on that row, so that row has been filled... 
		{
			row_rem_counter++;
			for (int i=0; i<N; i++)
			{
				gameGrid[row][i] = 0;	//All values of that row are reset, making it an empty row.
			}
		}
	}
	
	//After clearing the rows lets move the rows down to fill the space...
	bool row_empty;
	for (row=M; row>0; row--)	//This loop will go from the bottom to the top...
	{
		row_empty = true;
		for (col=0;col<N;col++)	
		{
			if (gameGrid[row][col] != 0 )	//This will check for any filled position in that row...
			{
				row_empty = false;
				break;
			}
		}
		if (row_empty == true)	//If no filled position in any row then that row is vacant and should be filled by rows above it...
		{
			for (int i=row-1; i>0;i--)	//Going from row above the vacant row till the top of the program...
			{
				for (int j=0; j<10; j++)	//Going acroos each element of that row...
				{
					gameGrid[i+1][j] = gameGrid[i][j];	//The row below that row(vacant) will get the values of the row above it...
					gameGrid[i][j]=0;	//The above row (whose values are being transfered to the vacant row) will become vacant now...
					//This will continue until all the cleared rows get filled by moving other rows downwards...
				}
			}		
		}
	}
	return row_rem_counter;	//To return how many rows are removed which will go as an input to the score calculation function...
}

//Function Number 7 :
//This function will be used to drop the bomb and act accordingly...
void bomb_fell(bool& bomb_drop, int& colorNum, float& timer, float delay, bool& reset_grid)
{ 
	
	static int turn=1;
	if (timer>delay)
	{
		if (turn == 1)
		{
			int coordinates[4][2] = {0,0,0,0};
			int random_x_value = rand()%10;	//This will generate random x position of bonm within range of (0-9)
			for (int i=0; i<4; i++)
			{
				point_1[i][0] = coordinates[i][0] / 2 + random_x_value;
				point_1[i][1] = coordinates[i][1] % 2;
			}
			turn++;
			colorNum = rand()%7 + 1;
		}
		else
		{
			if (gameGrid[point_1[0][1]+1][point_1[0][0]] != 0 || point_1[0][1] == 19 )
			{
				turn = 1;	//resetting the turn
				bomb_drop = false;	//resetting the condition of the bomb...
				if (gameGrid[point_1[0][1]+1][point_1[0][0]] == colorNum)
				//If the colour of the block matches with the one below it then reset grid..
				{
					reset_grid = true;
					gameGrid[point_1[0][1]][point_1[0][0]]=0;	//also reseting the bomb so that it doesnot move down...
				}
				else if (gameGrid[point_1[0][1]+1][point_1[0][0]] != colorNum)
				//If the colour of the block doesn't matches with the one below it then destroy square blocks...
				{
					gameGrid[point_1[0][1]][point_1[0][0]]=0;	//destroying bomb itsef...
					gameGrid[point_1[0][1]+1][point_1[0][0]]=0; //disapearing block below it...
					gameGrid[point_1[0][1]+2][point_1[0][0]]=0; //disapearing block 2 places below it...
					if (gameGrid[point_1[0][1]][point_1[0][0]+1] != 0 || gameGrid[point_1[0][1]+1][point_1[0][0]+1]!=0)
					 //disapearing block to the right of it...)
					{
						gameGrid[point_1[0][1]][point_1[0][0]+1]=0; //disapearing block right side of it...
						gameGrid[point_1[0][1]+1][point_1[0][0]+1]=0; //disapearing block 2 places below and right...
					}
					else if (gameGrid[point_1[0][1]][point_1[0][0]-1] != 0 || gameGrid[point_1[0][1]+1][point_1[0][0]-1] !=0)
					 //disapearing block to the left of it...)
					{
						gameGrid[point_1[0][1]][point_1[0][0]-1]=0; //disapearing block right side of it...
						gameGrid[point_1[0][1]+1][point_1[0][0]-1]=0; //disapearing block 2 places below and right...
					}
				
				}
				else if (point_1[0][1] == M-1)	//if the block fall on the last row
				//if it falls at vacant area
				{
					gameGrid[point_1[0][1]][point_1[0][0]] = 0; //To disappear the bomb itself...
				}
				point_1[0][1]==19;	//to end the blcok...//wrong find alternative
			}
			else 
			{
					for (int j=0; j<4; j++)	//Incresing its y position to make it fall...
						point_1[j][1]++;
			}
			
		}
	timer = 0;
	}
}
//Function Number 8 :
//This function will drop the object immediately after a space bar detected....
void space_bar_effect(bool& drop_immediate)
{
	
	int row; bool row_found = false;
	if (drop_immediate == true)
	{
	//Now checking the last row free under that column...
	for (row=0; row<M; row++)	//This will go from first row till the last row...
	{
		for(int i=0; i<4; i++ )	
		{
			
			if (gameGrid[row][point_1[i][0]] != 0 || row == 19)	//This will help search in only the column under the piece..
			{
				row_found = true;
				break;
			}
		}
		if (row_found == true)
			break;
	}
	row -= 1;	//As destination row should be one less than the occupied row
	if (row_found == true)
	{
		while ((point_1[0][1] < row) && (point_1[1][1] < row) && (point_1[2][1] < row) && (point_1[3][1]<row))
		//This will increment the y position of the block until any one piece of the block reaches the desired location...
		{
			for (int i=0; i<4; i++)
				point_1[i][1]+=1;
		}
	}
	//
	
	}
	drop_immediate = false;	//resetting the value of the drop boolean...
}
//Function Number 9 :
//This will handle the level of the game...
void level(int& current_level, float& delay, bool difficulty_increased)
{
	if (difficulty_increased == true)	//This will increase the current level if difficulty incraese...
		current_level = 2;
	if (current_level==1)
	{
		delay = 0.3;	//For beginner level, the speed of falling block is less
		//difficulty_increased = true;
	}
	if (current_level==2)
	{
		delay = 0.2;	//The level of game has now advanced so the speed in now increased...
	}
}
//Function Number 10 :
//This will increase the difficulty of the game as the time passes..
void increasing_difficulty(float total_time, float& delay, bool& difficulty_increased, int score)
{
	int times=1;	//How namy times the difficulty increases
	if ((total_time / (60*5)) >=times)	//If five minutes of game is passed then this loop will execute...
	{
		delay = 0.2;	//This will increase the speed of the block falling after 1 minutes pass...
		difficulty_increased = true;
		//Making the last row non-interactive for the game
		for (int i=0; i<N;i++)
			gameGrid[M-1][i] = 12;	//Making it grey indicating can't ba used any more
		total_time = 0;
		times++;
	}
	if (score >= 70)
		difficulty_increased = true;
}
//Function Number 10 :
//This function is used to calculate the user score...
void score_calculation(int& user_score,int row_rem)
{
	switch (row_rem)
	{
	case 1: user_score += 10;	//If one row is removed, users score will increase by 10...
			break;
	case 2: user_score += 30;	//If two row is removed, users score will increase by 30...
			break;
	case 3: user_score += 60;	//If three row is removed, users score will increase by 60...
			break;
	case 4: user_score += 100;	//If four rows are removed, users score will increase by 100...
			break;
	}
}
//Function Number 11 :
//The below function is used to display the main menu and act according the the options choosen by the user...
#include<fstream>	//I have added this as I would need to read and write to files...
using namespace sf;
void start_game();				//Forward declaration of my helper function...
void display_help(RenderWindow& window);	//Forward declaration of Helper to display the help page...
void see_highScores (RenderWindow& window);	//Forward declaration of Helper function to see the high scores...
//Forward declarations finished, now function of menu starts...
void display_menu(bool& close_main,int turn, int user_score)	
{
	Text text, text_1, text_2, text_3;
	Font font;
	font.loadFromFile("arial.ttf");	//Loading the font that I have added in this folder (arial)...
	RenderWindow window(VideoMode(320, 480), "Tetris Game");
	Texture menu;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))                   //Event is occurring - until the game is in running state
		{ 
		 	if (event.type == Event::KeyPressed) 
		    	{
				if (event.key.code == Keyboard::Num1)            //Check if the other key pressed is '1'...
				{
					window.close();                         //This will close this window to restart the game...
					start_game();
				}
			    	else if (event.key.code == Keyboard::Num2)     //Check if the other key pressed is '2'
                 		{
                 			see_highScores(window);
                 			sf::FloatRect visibleArea(0, 0, 320, 480);	//To restore window size
        				window.setView(sf::View(visibleArea));
                 		}
				else if (event.key.code == Keyboard::Num3)    //Check if the other key pressed is '3'...
				 //Writing the code to output the help...
				{
					display_help(window);
					sf::FloatRect visibleArea(0, 0, 320, 480);	//To restore window size
        				window.setView(sf::View(visibleArea));
				}
				else if (event.key.code == Keyboard::Num4)				//Checking for a '4' key pressed...
				{
					//This will add the scores in the file...
					fstream file("file.txt", ios::app);
					file<<user_score<<endl;
					file.close();
					//Till here...
				    	//Below code is to close other window along with this window...
				    	close_main = true;	//This will change the value of "close_main" to close the other window as well...
				    	window.close();	//This will close this current window...
				}
				else if (event.key.code == Keyboard::Num5)				//Checking for a '5' key pressed...
				{
					window.close();	//This will close the window_1 so that the game could continue...
				}
			}
		}
	text.setFont(font); 
   	text.setString("Menu For Tetris Game\n");
    	text.setCharacterSize(28);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold | Text::Underlined);
	text.setPosition(0,10);
	text_1.setFont(font); 
    	text_1.setString("1.\tStart New Game\n\n2.\tSee High-Scores\n\n3.\tHelp\n\n4.\tExit\n");
    	text_1.setCharacterSize(24);
	text_1.setFillColor(Color::White);
	text_1.setStyle(Text::Bold);
	text_1.setPosition(35,100);
	text_2.setFont(font); 
	if (turn != 1)
    		text_2.setString("5.\tContinue\n");
    	else
    		text_2.setString("\n\n\n");
    	text_2.setCharacterSize(24);
	text_2.setFillColor(Color::White);
	text_2.setStyle(Text::Bold);
	text_2.setPosition(35,320);
	text_3.setFont(font); 
    	text_3.setString("Note: You should press\n1 Key to execute first option\n2 Key to execute second option\nand so on...");
    	text_3.setCharacterSize(18);
	text_3.setFillColor(Color::White);
	text_3.setStyle(Text::Bold);
	text_3.setPosition(0,365);
	window.clear(Color::Black);
	window.draw(text);
	window.draw(text_1);
	window.draw(text_2);
	window.draw(text_3);
	window.display();
    }
}
//Helper function for menu
void start_game ()
{
	Text text, text_1;
	Font font;
	font.loadFromFile("arial.ttf");	//Loading the font that I have added in this folder (arial)...
	//input name...
 	string str="";
   	fstream file("file.txt", ios::app);
 	RenderWindow window(VideoMode(750, 100), "Input User Name");
	while (window.isOpen())
    	{
	    	Event event;
 		while (window.pollEvent(event))
		{  
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Return || event.key.code == Keyboard::Space)	
		    		//The window will be closed once Enter or Space is pressed...
		    		{
		            		file<<' ';	//To add a space between score and name in the file...
		            		file.close();	//To close the text file ...
		            		window.close(); //To close the window..
		            	} 
		            	if (event.type == Event::TextEntered)
		            	{
		            		str += char(event.text.unicode);	
		            		//To store the string in the str variable to output it to the user fo asthetic purpose...
		            		file<<char(event.text.unicode);	//To add the characters to the file...
		            	}
		}
		text.setFont(font); 
    		text.setString("Enter your User Name:\nPress 'Enter' or 'Space' after you are done");
		text.setCharacterSize(30);
		text.setFillColor(Color::Black);
		text.setStyle(Text::Bold);
		text.setPosition(0,0);
		text_1.setFont(font); 
    		text_1.setString(str);
		text_1.setCharacterSize(30);
		text_1.setFillColor(Color::Black);
		text_1.setStyle(Text::Bold);
		text_1.setPosition(400,0);
		window.clear(Color::Blue);
		window.draw(text);
		window.draw(text_1);
		window.display();
	}
}
void display_help(RenderWindow& window)		//Helper to display the help page...
{
	// update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, 600, 700);
        window.setView(sf::View(visibleArea));
        
	Text text, text_1;
	Font font;
	font.loadFromFile("arial.ttf");	//Loading the font that I have added in this folder (arial)...
	while (window.isOpen())
	{
	  	Event event;
		while (window.pollEvent(event))
		{  
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::E)
					return;
	      	}
		text.setFont(font); 
    		text.setString("Rules Of Tetris Game");
		text.setCharacterSize(30);
		text.setFillColor(Color::Black);
		text.setStyle(Text::Bold);
		text.setPosition(0,0);
		text_1.setFont(font); 
    		text_1.setString("1)\tPoint Scoring:\nDestroying 1 line = 10 points.\nDestroying 2 lines = 30 points.\nDestroying 3 lines = 60 points.\nDestroying 4 lines = 100 points.\n2)Bomb will fall at random time if:\ni)its color matches with the block it falls on,\n then all blocks will be destroyed.\nii)if colour doesn't match then only 4 blocks\n will be distroyed.\niii)if bomb falls at vacant position then no destruction.\nnote: The movement of bomb can't be controlled.\n3)As time passes the grid will shrink.\n4)In beginner level 3 next block suggestions\n will be provided and in advance level\n only 1 next block suggestion.\n5)Speed of falling block increases in advance level.\n5)Game will be over when the blocks reaches the top.\n6)Up arrow key will be used for rotation.\n7)Down arrow key will increase speed of falling block.\n8)Left right arrows can be used to move the blocks.\n\nPress 'E' to exit this Help... ");
		text_1.setCharacterSize(24);
		text_1.setFillColor(Color::Black);
		text_1.setPosition(0,50);
		window.clear(Color::White);
		window.draw(text);
		window.draw(text_1);
		window.display();
	}
}
void see_highScores (RenderWindow& window)	//Helper function to see the highh scores
{
	// update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, 460, 360);
        window.setView(sf::View(visibleArea));
        
	Text text, text_1, text_2, text_3;
	Font font;
	font.loadFromFile("arial.ttf");	//Loading the font that I have added in this folder (arial)...
	//write code for see high scores
	const int array_size = 10;	//Indicated on project statement
	string name[array_size];	
	int score[array_size]={0};	//initializing score with zero is important so that buffer is not taken...
	ifstream infile("file.txt");
	int counter=0;
	int temp;	//to temporiarily store the score while swapping...
	string temp_s;	//to temporarily store the string while swapping...
	while(infile>>name[counter]>>score[counter])
		counter++;
	infile.close();
	//Below is the algorithm for BUBBLE SORT to sort the scores to get high scores
	for (int i=0; i<array_size-2; i++)
	{
		for(int j=0; j<array_size-1; j++)
		{
			if (score[j] < score[j+1])
		         {
		         	temp = score[j];
		         	temp_s = name[j];
		         	score[j] = score[j+1];
		       		name [j] = name[j+1];
		         	score[j+1] = temp;
		        	name [j+1] = temp_s;
			}
		}
	}
	//Now I will output the first 3 positions
	//RenderWindow window_4(VideoMode(1000, 400), "Output High Score");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{  
		 	if (event.type == Event::KeyPressed)
		    		if (event.key.code == Keyboard::E)	//The window will be closed once 'E' is pressed...
		    			return;		
			text.setFont(font); 
			text.setString("High Scores\nFirst 3 Positions & Scores\n\n\n\n\n\n\n\nPress 'E' to exit this window...");
			text.setCharacterSize(30);
			text.setFillColor(Color::Black);
			text.setStyle(Text::Bold | Text::Underlined);
			text.setPosition(0,0);
			text_1.setFont(font); 
			text_1.setString("1--"+name[0]+"\t\t\t\t"+to_string(score[0]));
			text_1.setCharacterSize(20);
			text_1.setFillColor(Color::Black);
			text_1.setStyle(Text::Bold);
			text_1.setPosition(20,160);
			text_2.setFont(font); 
			text_2.setString("2--"+name[1]+"\t\t\t\t"+to_string(score[1]));
			text_2.setCharacterSize(20);
			text_2.setFillColor(Color::Black);
			text_2.setStyle(Text::Bold);
			text_2.setPosition(20,200);
			text_2.setFont(font); 
			text_3.setString("3--"+name[2]+"\t\t\t\t"+to_string(score[2]));
			text_3.setCharacterSize(20);
			text_3.setFillColor(Color::Black);
			text_3.setStyle(Text::Bold);
			text_3.setPosition(20,240);
			window.clear(Color::White);
			window.draw(text);
			window.draw(text_1);
			window.draw(text_2);
			window.draw(text_3);
			window.display();
		}
	}
}

//Function # 12:
//This function is used to end the game..
void game_over(bool found, bool& close_main,bool& restart,int user_score, RenderWindow& previous_window)
{
	Text text, text_1, text_2, text_3;
	Font font;
	font.loadFromFile("arial.ttf");	//Loading the font that I have added in this folder (arial)...
	if (found == true)
	{
		//This will add the scores in the file...
		fstream file("file.txt", ios::app);
		file<<user_score<<endl;
		file.close();
		//closing the previous window and opening a new one
		previous_window.close();
		RenderWindow window(VideoMode(480, 200), "Game Over");
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{  
				if (event.type == Event::KeyPressed) 
				{
					if (event.key.code == Keyboard::Num1)            //Check if the other key pressed is '1'...
					{
						restart = true;	//To set restart to true...
						window.close();	//to close this window...
		    			}
		    			else if (event.key.code == Keyboard::Num2)            //Check if the other key pressed is '1'...
					{
						close_main=true;	//This will be used to close the main window...
						window.close();	//This will close this window...
		    			}
		    		
		    		}
			    	text.setFont(font); 
				text.setString("Your Game is Over!!!\n");
				text.setCharacterSize(28);
				text.setFillColor(Color::White);
				text.setStyle(Text::Bold | Text::Underlined);
				text.setPosition(0,0);
				text_2.setFont(font); 
				text_2.setString("Your Score was ");
				text_2.setCharacterSize(28);
				text_2.setFillColor(Color::White);
				text_2.setStyle(Text::Bold);
				text_2.setPosition(0,35);
				text_3.setFont(font); 
				text_3.setString(to_string(user_score));
				text_3.setCharacterSize(28);
				text_3.setFillColor(Color::White);
				text_3.setStyle(Text::Bold);
				text_3.setPosition(220,35);
				text_1.setFont(font); 
				text_1.setString("1-Go Back To Menu\n2-Exit\n");
				text_1.setCharacterSize(28);
				text_1.setFillColor(Color::White);
				text_1.setStyle(Text::Bold);
				text_1.setPosition(0,80);
				window.clear(Color::Black);
				window.draw(text);
				window.draw(text_1);
				window.draw(text_2);
				window.draw(text_3);
				window.display();
			}
		}
	}
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
