/*
 ============================================================================
 Name        : Testowy.c
 Author      : Group 3
 Version     : 0.01
 1 - one fish
 2 - 2 fishes
 3 - 3 fishes
 0 - no field
 10,11,12,13... - first player penguins
 20,21,22,23... - second player penguins
 30,31,32,32... - third player penguins

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct player *players;
int **playground;
int one_on_playboard;

struct player{
	int playerID;
	int penguins_to_allocate;
	int moving_penguins;
	int fishes;
	int move;
	struct penguin *penguins;
};

struct penguin{
	int penguinID;
	int x_coordinate;
	int y_coordinate;
	int last_temp_x;
	int last_temp_y;
	int can_he_move;
};


//Creates playground filled with 1
void create_playground_filled_with_1(int height, int width){
	srand(time(NULL));
	playground = (int**)malloc(height*sizeof (int*));
	int i=0;
	for(i; i < height; i ++)
	{
		playground[i] = (int*)malloc(width*sizeof(int));
		int j= 0;
		for(j; j < width; j ++)
		{
			if(i%2==1 && j==width-1)
							{
								playground[i][j]=0;
								//printf("[%d,%d]  ",i,j);
							}
							else
							{
								playground[i][j]= 1;
								//printf("[%d,%d]  ",i,j);
							}
		}
		printf("\n");
	}

}
//Creates random playground
void create_playground(int height, int width){
	srand(time(NULL));
	playground = (int**)malloc(height*sizeof (int*));
	int i = 0;
	for(i; i < height; i ++)
	{
		playground[i] = (int*)malloc(width*sizeof(int));
		int j = 0;
		for(j; j < width; j ++)
		{
			if(i%2==1 && j==width-1)
							{
								playground[i][j]=0;
								//printf("[%d,%d]  ",i,j);
							}
							else
							{
								int rando = rand() %3 +1;
								playground[i][j]= rando;
								if(rando == 1){
									one_on_playboard++;
								}
								//printf("[%d,%d]  ",i,j);
							}
		}
		printf("\n");
	}

}
//View table
void print_playground_table(int height, int width){
	int  i= 0;
	for(i; i < height; i++, printf("\n")){
		int j = 0;
		for (j ; j < width; j ++){
			printf("%d\t",playground[i][j]);
		}
	}
}

//View for players
void print_playground(int height, int width){
	int i = 0;
	for (i; i < height; ++i, printf("\n") )
		{
			if(i%2==1) printf("\t");

			int j = 0;
			 for ( j; j < width; ++j)
			 {
					 printf("%d[%d,%d]\t\t",playground[i][j],i,j);

			 }
		}

}
//Prints all info about actual game state <or maybe not old function I don't remember>
void verify_all(int height, int width, int players_ammount, int penguins_per_player){
int i = 0;
	for(i ; i < players_ammount; i++){
		printf("\nPlayer %d :", i );
		printf("\nplayerID: \t%d\npenguins_to_allocate: \t%d\nfishes = \t%d\n",players[i].playerID, players[i].penguins_to_allocate,players[i].fishes);
		int j = 0;
		for(j; j < penguins_per_player;j++){
			printf("\tPenguin %d\n",j);
			printf("\tpenguinID = \t%d\n\t\t\t[%d,%d]\n\tlast_temp_x = \t%d\n\tlast_temp_y= \t%d\n\n",
					players[i].penguins[j].penguinID,players[i].penguins[j].x_coordinate,players[i].penguins[j].y_coordinate,players[i].penguins[j].last_temp_x,players[i].penguins[j].last_temp_y);
		}
	}
	print_playground(height, width);
}
//Frees memory after playground <not important>
void destroy_playground(int height){
	int i =0;
	for(i; i<height; i++)
	 free(playground[i]);
	 free(playground);
	 playground = NULL;
}
//Creates players with penguins
void create_players_with_penguins(int players_ammount, int penguins_per_player)
{
	players = (struct player*) malloc (players_ammount * sizeof(struct player));
	int i = 0;
	for (i; i < players_ammount; i++)
	{
		players[i].fishes = 0;
		players[i].penguins_to_allocate = penguins_per_player;
		players[i].playerID = i;
		players[i].move=penguins_per_player;
		players[i].moving_penguins = penguins_per_player;
		players[i].penguins = (struct penguin*) malloc (penguins_per_player * sizeof(struct penguin));
		int j = 0;
		for(j ; j < penguins_per_player; j++){
			players[i].penguins[j].x_coordinate = 0;
			players[i].penguins[j].y_coordinate = 0;
			players[i].penguins[j].penguinID = 10+i*10+j;
			players[i].penguins[j].can_he_move = 1;
		}
	}
};

//Asks players to put their penguins on the map
void set_penguins(int height, int width,int players_ammount, int penguins_per_player){
	int i = 0;
	for (i; i < penguins_per_player; i ++)
	{
		int j = 0;
		for(j; j < players_ammount; j ++)
		{
		int new_coordinate_x=-1, new_coordinate_y=-1;
		do{
			printf("Player: %d Penguin: %d\nEnter field coordinates with '1' - example: '3 2'\n", j,i);
			scanf("%d %d", &new_coordinate_x, &new_coordinate_y);
		}while(playground[new_coordinate_x][new_coordinate_y] != 1);
		players[j].penguins[i].y_coordinate = new_coordinate_y;
		players[j].penguins[i].x_coordinate = new_coordinate_x;
		players[j].penguins[i].last_temp_x = new_coordinate_x;
		players[j].penguins[i].last_temp_y = new_coordinate_y;
		players[j].fishes++;
		players[j].penguins_to_allocate--;
		playground[new_coordinate_x][new_coordinate_y] = players[j].penguins[i].penguinID;
		}
	}
}

//relocating penguin too coordinates new_x, new_y
void move_penguin_to_coordinates(int new_x, int new_y,int playerID, int penguinID){
	players[playerID].fishes += playground[new_x][new_y];
	playground[new_x][new_y] = players[playerID].penguins[penguinID].penguinID;
//printf("\nmoving_penguin_to_coordinate(x %D, y %d, playerID= %d,penguinID     [%d,%d] = %d\n",new_x,new_y,playerID,penguinID,new_x, new_y,playground[new_x][new_y]);
//printf("\nPrzed: \t[%d,%d] [%d,%d]\n", players[playerID].penguins[penguinID].last_temp_x,players[playerID].penguins[penguinID].last_temp_y,players[playerID].penguins[penguinID].x_coordinate,players[playerID].penguins[penguinID].y_coordinate);
	players[playerID].penguins[penguinID].last_temp_x = players[playerID].penguins[penguinID].x_coordinate;
	players[playerID].penguins[penguinID].last_temp_y = players[playerID].penguins[penguinID].y_coordinate;
	players[playerID].penguins[penguinID].x_coordinate = new_x;
	players[playerID].penguins[penguinID].y_coordinate = new_y;
	playground[players[playerID].penguins[penguinID].last_temp_x][players[playerID].penguins[penguinID].last_temp_y] = 0;
	playground[players[playerID].penguins[penguinID].x_coordinate][players[playerID].penguins[penguinID].y_coordinate]= players[playerID].penguins[penguinID].penguinID;
	//printf("\nPo: \t[%d,%d] [%d,%d]\n", players[playerID].penguins[penguinID].last_temp_x,players[playerID].penguins[penguinID].last_temp_y,players[playerID].penguins[penguinID].x_coordinate,players[playerID].penguins[penguinID].y_coordinate);
}

//No idea. Sth was to long to repeat it in code.
int do_in_switch(int check_x,int check_y,int ammount, int playerID, int penguinID, int move)
{
	int possible_jumps_count = 0;
		if (playground[check_x][check_y] > 3 || playground[check_x][check_y] < 1)
								{
									printf("\nNot enough jumps :( MAX in direction : %d\n",move);
								}else {
									possible_jumps_count++;
								}
								if(move == ammount){
									//printf("\n[%d,%d] -> [%d,%d]\n",players[playerID].penguins[penguinID].x_coordinate,players[playerID].penguins[penguinID].y_coordinate, check_x, check_y);
								}
	return possible_jumps_count;
}

//Checks if player can make a move
void check_direction_and_move(int direction, int ammount, int playerID, int penguinID)
{
	int check_x, check_y,temp, move = 0;
			check_x = players[playerID].penguins[penguinID].x_coordinate;
			check_y = players[playerID].penguins[penguinID].y_coordinate;
			int i = 0;
	for(i; i < ammount; i++)
			{
				if(check_x%2==0){
					switch(direction){
					case 0: //right
						check_y++;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
							printf("\n !! Cant go there! !!\n");
						}else{
							temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
							move = move + temp;
												if(move == ammount){
														move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
												}
						}
						break;
					case 1: //left
						check_y--;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 2: //down-right
						check_x++;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 3: //down-left
						check_x++;
						check_y--;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 4: //up-right
						check_x--;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 5: //up-left
						check_x--;
						check_y--;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 69: //put penguin to sleep
						players[playerID].penguins[penguinID].can_he_move=0;
						printf("\n\tYou shot a pengu but you didn't shoot the deputy\n");
						players[playerID].move--;
							break;
					default:
										printf("\n0-5 dude !\n");
					}
				} else{
					switch(direction){
					case 0: //right
						check_y++;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 1: //left
						check_y--;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 2: //down-right
						check_x++;
						check_y++;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 3: //down-left
						check_x++;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 4: //up-right
						check_x--;
						check_y++;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 5: //up-left
						check_x--;
						if(playground[check_x][check_y] < 1 || playground[check_x][check_y] > 3){
													printf("\n !! Cant go there! !!\n");
												}else{
													temp = do_in_switch(check_x,check_y,ammount,playerID,penguinID,move);
													move = move + temp;
																		if(move == ammount){
																				move_penguin_to_coordinates(check_x,check_y,playerID, penguinID);
																		}
												}
						break;
					case 69: //put penguin to sleep
						players[playerID].penguins[penguinID].can_he_move=0;
						printf("\n\tYou shot a pengu but you didn't shoot the deputy\n");
						players[playerID].move--;
							break;
					default:
						printf("\n0-5 dude !\n");
					}
				}
			}
}

//Asks player what direction and how far he'd like to go
void ask_and_move_to_direction(int playerID, int penguinID){
	int direction,jumps;
	printf("\nEnter direction :\n");
	printf(" 0 - right\n1 - left\n2 - right down\n3 - left down\n4 - right up\n5left up\n69 - put penguin to sleep\n");
	scanf("%d", &direction);
	if(direction == 69){
		printf("\n69 - kinda funny right ? %d\n", direction);
		jumps = 1;
		check_direction_and_move(direction,jumps,playerID,penguinID);
	} else
	{
		printf("How many jumps ?");
		scanf("%d",&jumps);
		check_direction_and_move(direction,jumps,playerID,penguinID);
	}

}

//checks how many of all penguins are not 69 <read code to understand>
int check_if_penguins_can_move(int players_ammount, int penguins_ammount){
	int temp = players_ammount*penguins_ammount;
	int i =0;
		for(i;i < players_ammount; i++){
			int j = 0;
			for(j; j < penguins_ammount;j ++)
			{
				if(players[i].penguins[j].can_he_move == 0)
				{
				temp--;
				}
			}
		}
	return temp;
}

//Asks players to move while there is at least 1 penguin not 69
void turns(int height, int width, int players_ammount, int penguins_per_player){
	int j;
	int temp = check_if_penguins_can_move(players_ammount,penguins_per_player);

	int k= 0;
	while(temp > 0)
	{
		//printf("\nTemp = %d\n", temp);
		int turn=k%players_ammount;
		print_playground(height,width);
		if(players[turn].move > 0){
		printf("\nPlayer '%d' choose penguin:",k%players_ammount);
		scanf("%d", &j);
		//printf("\nk= %d, j = %d, czy piwngwin moze sie ruszyc (%d , %d)\n",k,j,turn, j%10);
		if(players[turn].penguins[j%10].can_he_move== 1)
		{
			//printf("\nIF\n");
			ask_and_move_to_direction(turn,j%10);
		} else {
			//printf("\nELSE %d\n",players[turn].move);
			if(players[turn].move>0) k--;
		}
		}
		k++;
		temp = check_if_penguins_can_move(players_ammount,penguins_per_player);
		}
	}

//Prints players and scores after game.
void print_players_and_scores(int players_ammount){
	int i = 0;
	for (i; i < players_ammount; i++){
			printf("\nPlayer %d \t %d \tfishes",i,players[i].fishes);
		}
}

int main(){
	one_on_playboard=0;
	int players_ammount = 2;
		int penguins_per_player = 2;
		int height = 5;
		int width = 6;

	printf("Enter height of board:\n");
	scanf("%d", &height);
	printf("\nEnter width of board:\n");
	scanf("%d", &width);
	printf("\nEnter players amount:\n");
	scanf("%d", &players_ammount);
	printf("\nHow many penguins per player ?:\n");
	scanf("%d", &penguins_per_player);

do{
	create_playground(height,width);
	printf("\n %d\n",one_on_playboard);
} while (one_on_playboard<players_ammount*penguins_per_player);
	//print_playground(height,width);
	create_players_with_penguins(players_ammount,penguins_per_player);
	//verify_all(height, width, players_ammount,penguins_per_player);
	print_playground(height,width);
	set_penguins(height, width,players_ammount, penguins_per_player);
	//print_playground(height, width);

	turns(height, width,players_ammount,penguins_per_player);
	print_players_and_scores(players_ammount);
	return 0;
}

