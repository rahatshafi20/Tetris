/* Name : Muhammad Rahat Shafi
Student id : 22i-1061
Final Project Of Programming Fundamentals BSCS 2022*/

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * Shape of each piece is represented by rows in the array.
 * TIP: Name the array what is already been coded to avoid any unwanted errors.
 */

 
int BLOCKS[7][4]={  {0,2,1,3},		//For Block 'O'...
					{0,2,4,6},		//For Block 'I'...
					{0,1,3,5},		//For Block 'J'...
					{1,3,5,4},		//For Block 'L'...
					{1,2,3,4},		//For Block 'S'...
					{0,2,3,5},		//For Block 'Z'...
					{1,2,3,5}  } ;	//For Block 'T'...



/*The logic I have used for the creation of the blocks , after careful observation and testing is that,
each block contains 4 values, each storing the coordinates of each piece. The coordinate is calculated in
such a way that the value is divided by 2 to get its x location and the value has a mod to calculate
its y location. For every such piece same calculation has been performed ...*/

