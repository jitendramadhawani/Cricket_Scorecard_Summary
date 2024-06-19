#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global declaration of variables
int wickets_batA = 0;
char batsman_name_batA[30];
int runs_batA, balls_batA, total_balls_batA = 0, total_runs_batA = 0, runouts_batA = 0, extras_batA = 0; // batsman variables of teamA

int wickets_batB = 0;
char batsman_name_batB[30];
int runs_batB, balls_batB, total_balls_batB = 0, total_runs_batB = 0, runouts_batB = 0, extras_batB = 0; // batsman variables of teamB

int wickets_bowlB = 0;
char bowler_name_bowlB[30];
int runs_bowlB, balls_bowlB, total_balls_bowlB, total_runs_bowlB = 0;
int total_wickets_bowlB; // bowler variables of teamB

int wickets_bowlA = 0;
char bowler_name_bowlA[30];
int runs_bowlA, balls_bowlA, total_balls_bowlA, total_runs_bowlA = 0;
int total_wickets_bowlA; // bowler variables of teamA

char teamA[30], teamB[30]; // to store the names of two playing teams

int i = 0, j = 0, l;

// struct print_bat for batsmen
struct print_bat
{
	char name[30];
	int runs, balls;
} main_order_bat[11]; // array of structure for 11 batsman

// struct print_bowl for bowlers
struct print_bowl
{
	char name[30];
	int runs, balls, wickets;
} main_order_bowl[11]; // array of structure for at max 11 players

// struct batsman for storing statistics of batsmen
struct batsman
{
	char player_name[30];
	int runs, balls;
	struct batsman *left;
	struct batsman *right;

} *root_batA = NULL, *root_batB = NULL; // root pointer for both batting innings

// struct bowler for storing statistics of bowler
struct bowler
{
	char player_name[30];
	int balls, runs, wickets;
	struct bowler *left;
	struct bowler *right;

} *root_bowlA = NULL, *root_bowlB = NULL; // root pointer for both bowling innings

// function newnode_bat for assigning the values of batsman at structure variables
struct batsman *newnode_bat(char name[30], int runs, int balls)
{
	struct batsman *temp = (struct batsman *)malloc(sizeof(struct batsman)); // dynamic memory allocation for batsman structure
	temp->left = NULL;
	temp->right = NULL;

	strcpy(temp->player_name, name);
	temp->runs = runs;
	temp->balls = balls;

	return temp;
}

// function insert_batsman for storing the all statistics of batsmen
struct batsman *insert_batsman(struct batsman *root_bat, char name[30], int runs, int balls)
{
	if (root_bat == NULL) // if first node is Null
		return newnode_bat(name, runs, balls);

	else if (root_bat->runs > runs) // if node runs is greater than this insertion runs then goes left sub-tree
		root_bat->left = insert_batsman(root_bat->left, name, runs, balls);

	else // else for node runs is less than this insertion runs then goes right sub-tree
		root_bat->right = insert_batsman(root_bat->right, name, runs, balls);

	return root_bat;
}

// function newnode_bowl for assigning the values of bowler at structure variables
struct bowler *newnode_bowl(char name[30], int runs, int balls, int wickets)
{
	struct bowler *temp = (struct bowler *)malloc(sizeof(struct bowler)); // dynamic memory allocation for bowler structure
	temp->left = NULL;
	temp->right = NULL;

	strcpy(temp->player_name, name);
	temp->runs = runs;
	temp->balls = balls;
	temp->wickets = wickets;

	return temp;
}

// function insert_bowler for storing the all statistics of bowlers
struct bowler *insert_bowler(struct bowler *root_bowl, char name[30], int runs, int balls, int wickets)
{
	if (root_bowl == NULL) // if first node is having NULL then
		return newnode_bowl(name, runs, balls, wickets);

	else if (root_bowl->wickets > wickets) // if node wickets is greater than this insertion wickets then goes left sub-tree
		root_bowl->left = insert_bowler(root_bowl->left, name, runs, balls, wickets);

	else if (root_bowl->wickets == wickets && root_bowl->runs > runs)
		root_bowl->left = insert_bowler(root_bowl->left, name, runs, balls, wickets);

	else // else for wickets is less than this insertion wickets then goes right sub-tree
		root_bowl->right = insert_bowler(root_bowl->right, name, runs, balls, wickets);

	return root_bowl;
}

// function inorder_bat for assigning the values in descending order as per algorithm
void inorder_bat(struct batsman *root_bat)
{
	if (root_bat != NULL)
	{

		inorder_bat(root_bat->right);

		// storing the values in the struct array that we made before so that we can print only 4 i.e top 4 batsman from the innings
		strcpy(main_order_bat[i].name, root_bat->player_name);
		main_order_bat[i].runs = root_bat->runs;
		main_order_bat[i].balls = root_bat->balls;
		i++;

		inorder_bat(root_bat->left);
	}
}

// function inorder_bowl for assigning the values in descending order as per algorithm
void inorder_bowl(struct bowler *root_bowl)
{
	if (root_bowl != NULL)
	{

		inorder_bowl(root_bowl->right);

		// storing the values in the struct array that we made before so that we can print only 4 i.e top 4 bowlers from the innings
		strcpy(main_order_bowl[j].name, root_bowl->player_name);
		main_order_bowl[j].wickets = root_bowl->wickets;
		main_order_bowl[j].runs = root_bowl->runs;
		main_order_bowl[j].balls = root_bowl->balls;
		j++;

		inorder_bowl(root_bowl->left);
	}
}

// function batting_teamA for team A of innings-1
void batting_teamA()
{
	int counter = 0, i = 1;
	printf("\n----------------------------%s------------------------------\n\n", teamA);
	printf("INNIGING-1 : Batting Statistics of %s: \n\n", teamA);
	printf("Player\t\tName\t\t\tRuns\tBalls\n");
	printf("\n--------------------------------------------------------------------\n");
	do
	{

		printf("Player%d    \t", i);
		fflush(stdin);
		// getting the players' name, runs and balls as per wicket goes down of batting team A
		scanf("%s", batsman_name_batA);
		scanf("%d", &runs_batA);

		scanf("%d", &balls_batA);
		// while the last player's balls is less than 120 i.e. 20 overs then this loop iterates
		while ((total_balls_batA + balls_batA) > 120)
		{
			printf("\n--> Invalid Input of balls from Player%d\n", i);
			printf("--> Please Enter Valid Balls Input : ");
			scanf("%d", &balls_batA); // scanning balls again due to exception
		}

		// passing all the statistics in BST
		root_batA = insert_batsman(root_batA, batsman_name_batA, runs_batA, balls_batA);

		total_balls_batA += balls_batA;
		total_runs_batA += runs_batA;
		wickets_batA++;
		i++;

		/* wickets would have to be less then 10 and balls have to be less than 120 */
	} while (wickets_batA < 10 && total_balls_batA < 120);

	/*if wickets are not 10 i.e. not all out then decrease 2 wickets from total wickets as per rules and instruction */
	if (wickets_batA <= 10)
		wickets_batA -= 2;

	printf("\nExtra(s) : ");
	scanf("%d", &extras_batA);
	total_runs_batA += extras_batA;

	printf("\nRun Out(s) : ");
	scanf("%d", &runouts_batA);

	printf("\n%s : %d/%d (%d.%d)\n", teamA, total_runs_batA, wickets_batA, (total_balls_batA) / 6, (total_balls_batA) % 6);
}

void bowling_teamB()
{
	int i = 1;
	printf("\n---------------------------%s-----------------------------\n\n", teamB);
	printf("INNIGING-1 : Bowling Statistics of %s: \n\n", teamB);
	printf("Player\t\tName\t\tBalls\tRuns\tWickets\n");
	printf("\n-----------------------------------------------------------\n");
	do
	{

		printf("Player%d    \t", i);
		fflush(stdin);
		// getting the bowler's name, balls i.e. overs, runs and wickets for bowling statistics
		scanf("%s", bowler_name_bowlB);

		scanf("%d", &balls_bowlB);
		/* scanning the valid balls input of bowling team as per first innings balls have to as same as batting team's balls
		 and any bowler cannot bowl more than 24 balls i.e. 4 overs
		 or the last bowler's balls would be less then 120 balls i.e. 20 overs */
		while (((total_balls_bowlB + balls_bowlB) < 120 && total_runs_bowlB == total_runs_batA) || balls_bowlB > 24 || (total_balls_bowlB + balls_bowlB) > 120 || (total_balls_bowlB + balls_bowlB) > total_balls_batA)
		{
			printf("\n--> Invalid Input of balls from Player%d\n", i);
			printf("--> Please Enter Valid Balls Input : ");
			scanf("%d", &balls_bowlB);
		}

		scanf("%d", &runs_bowlB);
		/* scanning the valid runs input of bowling team as per first innings runs have to as same as batting team's balls
		 or the last bowler's runs would be not be greater than first inning batting team */
		while (((total_runs_bowlB + runs_bowlB) < total_runs_batA && total_balls_bowlB == total_balls_batA) || (total_runs_bowlB + runs_bowlB) > total_runs_batA)
		{
			printf("\n--> Invalid Input of runs from Player%d\n", i);
			printf("--> Please Enter Valid Runs Input : ");
			scanf("%d", &runs_bowlB);
		}

		scanf("%d", &wickets_bowlB);
		/* scanning the valid wickets input of bowling team as per first inning's wickets have to as same as batting team's wickets
		 and if both input runs would be become same or both input balls input would be become same but wickets would not be same */
		while ((total_wickets_bowlB + wickets_bowlB) > wickets_batA || ((total_wickets_bowlB + wickets_bowlB) < wickets_batA && total_balls_bowlB == total_balls_batA) || ((total_wickets_bowlB + wickets_bowlB) < wickets_batA && total_runs_bowlB == total_runs_batA))
		{
			printf("\n--> Invalid Input of wickets from Player%d\n", i);
			printf("--> Please Enter Valid Wickets Input : ");
			scanf("%d", &wickets_bowlB);
		}

		// passing the values of bowling team to BST
		root_bowlB = insert_bowler(root_bowlB, bowler_name_bowlB, runs_bowlB, balls_bowlB, wickets_bowlB);

		total_balls_bowlB += balls_bowlB;
		total_runs_bowlB += runs_bowlB;
		total_wickets_bowlB += wickets_bowlB;
		i++;

		/* bowling wickets would have to be less than first inning batting wicket
		   or balls and runs would be less than first inning's batting statistics */
	} while ((total_wickets_bowlB + runouts_batA) < wickets_batA || total_balls_bowlB < total_balls_batA && total_runs_bowlB < total_runs_batA);

	printf("\n%s : %d/%d (%d.%d)\n", teamA, total_runs_batA, wickets_batA, (total_balls_bowlB) / 6, (total_balls_bowlB) % 6);
}

void batting_teamB()
{
	int counter = 0, i = 1;
	printf("\n----------------------------%s------------------------------\n\n", teamB);
	printf("INNIGING-2 : Batting Statistics of %s: \n\n", teamB);
	printf("Player\t\tName\t\tRuns\tBalls\n");
	printf("---------------------------------------------------------------\n");
	do
	{
		printf("Player%d    \t", i);
		fflush(stdin);
		// getting the players' name, runs and balls as per wicket goes down of batting team B
		scanf("%s", batsman_name_batB);

		scanf("%d", &runs_batB);
		/* while the last player's runs is less than the addition of 6 runs of first batting team
		 because of winning condition as per team B successfully chase the target */
		while ((total_runs_batB + runs_batB) > (total_runs_batA + 6))
		{
			printf("\n--> Invalid Input of runs from Player%d\n", i);
			printf("--> Please Enter Valid Runs Input : ");
			scanf("%d", &runs_batB);
		}

		scanf("%d", &balls_batB);
		/* while the last player's total balls addition is greater than 120 balls i.e. 20 overs
		 as per team B's 20 overs batting condition */
		while ((total_balls_batB + balls_batB) > 120)
		{
			printf("\n--> Invalid Input of balls from Player%d\n", i);
			printf("--> Please Enter Valid Balls Input : ");
			scanf("%d", &balls_batB);
		}

		// passing the statistics to BST
		root_batB = insert_batsman(root_batB, batsman_name_batB, runs_batB, balls_batB);

		total_balls_batB += balls_batB;
		total_runs_batB += runs_batB;
		wickets_batB++;
		i++;

		/* wickets would have to be less then 10 and balls have to be less than 120
		   and second inning's runs would have to be less than first inning's runs */
	} while (wickets_batB < 10 && total_balls_batB < 120 && total_runs_batB <= total_runs_batA);

	if (wickets_batB <= 10) // if wickets are not 10 i.e. not all out then decrease 2 wickets from total wickets as per rules and instruction
		wickets_batB -= 2;

	printf("\nExtra(s) : ");
	scanf("%d", &extras_batB);
	total_runs_batB += extras_batB;

	printf("\nRun Out(s) : ");
	scanf("%d", &runouts_batB);

	printf("\n%s : %d/%d (%d.%d)\n", teamB, total_runs_batB, wickets_batB, (total_balls_batB) / 6, (total_balls_batB) % 6);
}

void bowling_teamA()
{
	int i = 1;
	printf("\n------------------------------%s---------------------------------------\n\n", teamA);
	printf("INNIGING-2 : Bowling Statistics of %s: \n\n", teamA);
	printf("Player\t\tName\t\tBalls\tRuns\tWickets\n");
	printf("\n--------------------------------------------------------------------\n");
	do
	{
		printf("Player%d    \t", i);
		fflush(stdin);
		scanf("%s", bowler_name_bowlA);
		scanf("%d", &balls_bowlA);

		/* scanning the valid balls input of bowling team as per first innings balls have to as same as batting team's balls
		 and any bowler cannot bowl more than 24 balls i.e. 4 overs
		 or the last bowler's balls would be less then 120 balls i.e. 20 overs */
		while (((total_balls_bowlA + balls_bowlA) < 120 && total_runs_bowlA == total_runs_batB) || balls_bowlA > 24 || (total_balls_bowlA + balls_bowlA) > 120 || (total_balls_bowlA + balls_bowlA) > total_balls_batB)
		{
			printf("\n--> Invalid Input of balls from Player%d\n", i);
			printf("--> Please Enter Valid Balls Input : ");
			scanf("%d", &balls_bowlA);
		}

		scanf("%d", &runs_bowlA);
		/* scanning the valid runs input of bowling team as per first innings runs have to as same as batting team's balls
		   or the last bowler's runs would be not be greater than first inning batting team */
		while (((total_runs_bowlA + runs_bowlA) < total_runs_batB && total_balls_bowlA == total_balls_batB) || (total_runs_bowlA + runs_bowlA) > total_runs_batB)
		{
			printf("\n--> Invalid Input of runs from Player%d\n", i);
			printf("--> Please Enter Valid Runs Input : ");
			scanf("%d", &runs_bowlA);
		}

		scanf("%d", &wickets_bowlA);
		/* scanning the valid wickets input of bowling team as per first inning's wickets have to as same as batting team's wickets
		   and if both input runs would be become same or both input balls input would be become same but wickets would not be same */
		while ((total_wickets_bowlA + wickets_bowlA) > wickets_batB || ((total_wickets_bowlA + wickets_bowlA) < wickets_batB && total_balls_bowlA == total_balls_batB) || ((total_wickets_bowlA + wickets_bowlA) < wickets_batB && total_runs_bowlA == total_runs_batB))
		{
			printf("\n--> Invalid Input of wickets from Player%d\n", i);
			printf("--> Please Enter Valid Wickets Input : ");
			scanf("%d", &wickets_bowlA);
		}

		// passing the statistics to BST
		root_bowlA = insert_bowler(root_bowlA, bowler_name_bowlA, runs_bowlA, balls_bowlA, wickets_bowlA);

		total_balls_bowlA += balls_bowlA;
		total_runs_bowlA += runs_bowlA;
		total_wickets_bowlA += wickets_bowlA;
		i++;

		/* total balls of second inning's have to be less than that same inning's batting side and same as for runs
		   and wickets of that second inning bowling would be less than that inning's batting wickets */
	} while ((total_wickets_bowlA + runouts_batB) < wickets_batB || total_balls_bowlA < total_balls_batB && total_runs_bowlA < total_runs_batB);

	printf("\n%s : %d/%d (%d.%d)\n", teamB, total_runs_batB, wickets_batB, (total_balls_bowlA) / 6, (total_balls_bowlA) % 6);
}

int main()
{
	printf("--> Instructions  : \n");
	printf("-> FROM BOWLING SIDE, ANY BOWLER CAN BE BOWL AT MAX 24 BALLS i.e. MAXIMUM 4 OVERS\n");
	printf("-> FORM BATTING SIDE, TWO PLAYERS WOULD BE GONE NOT OUT AT THE END OF INNING\n");
	printf("------------------------------------------------------------------------------------------------\n");

	printf(" \t\t\t\t\tENTER NAME OF TEAM 1: ");
	fflush(stdin);
	gets(teamA);
	printf(" \t\t\t\t\tENTER NAME OF TEAM 2: ");
	gets(teamB);
	printf("\n");
	// CALLING FUNCTIONS TO TAKE INPUT OF 1st INNINGS
	batting_teamA();
	bowling_teamB();

	// calling respective inorder functions to store the values in struct array that we made so that we can print the required no. of batsman and bowlers
	inorder_bat(root_batA);
	inorder_bowl(root_bowlB);

	// CALLING FUNCTIONS TO TAKE INPUT OF 2nd INNINGS
	batting_teamB();
	bowling_teamA();

	printf("\n------------------------------------------------------------------\n");
	printf("INNING-1 : \n");
	printf("\n%s\t\t\t\t", teamA);
	printf("%d/%d\t(%d.%d)\n", total_runs_batA, wickets_batA, (total_balls_batA) / 6, (total_balls_batA) % 6);
	printf("--------------------------------------------------------------------\n");

	// printing top-4 batsmen as per runs and top-4 bowlers as per wickets from first innings from the data that we stored in strcut array by calling inorder functions
	for (l = 0; l < 4; l++)
	{
		printf("%s\t\t", main_order_bat[l].name);
		printf("%d(%d)\t\t\t", main_order_bat[l].runs, main_order_bat[l].balls);
		printf("%s\t", main_order_bowl[l].name);
		printf("%d-%d\t%d.%d\n", main_order_bowl[l].wickets, main_order_bowl[l].runs, (main_order_bowl[l].balls) / 6, (main_order_bowl[l].balls) % 6);
	}

	i = 0;
	j = 0;
	// calling respective inorder functions to store the values in struct array that we made so that we can print the required no. of batsman and bowlers for 2nd INNINGS
	inorder_bat(root_batB);
	inorder_bowl(root_bowlA);

	printf("--------------------------------------------------------------------\n");
	printf("INNING-2 : \n");
	printf("\n%s\t\t\t", teamB);
	printf("%d/%d\t(%d.%d)\n", total_runs_batB, wickets_batB, (total_balls_batB) / 6, (total_balls_batB) % 6);
	printf("--------------------------------------------------------------------\n");

	/* printing top-4 batsmen as per runs and top-4 bowlers as per wickets from first innings from the data
	   that we stored in strcut array by calling inorder functions for 2nd INNINGS */
	for (l = 0; l < 4; l++)
	{
		printf("%s\t\t", main_order_bat[l].name);
		printf("%d(%d)\t\t\t", main_order_bat[l].runs, main_order_bat[l].balls);
		printf("%s\t", main_order_bowl[l].name);
		printf("%d-%d\t%d.%d\n", main_order_bowl[l].wickets, main_order_bowl[l].runs, (main_order_bowl[l].balls) / 6, (main_order_bowl[l].balls) % 6);
	}

	printf("--------------------------------------------------------------------\n");
	printf("\n\n");
	printf("--------------------------------------------------------------------\n");

	/* if in second innings team B's runs are greater than first innings team A's runs
	   team B won as per it's remaining wickets  */
	if (total_runs_batB > total_runs_batA)
		printf("\n\n\t\t%s WON WITH %d WICKETS REMAINING\n\n", teamB, (10 - wickets_batB));

	/* else if in second innings team B's runs are less than first inning team A's runs
	 then team A won as per the difference of both teams runs  */
	else if (total_runs_batB < total_runs_batA)
		printf("\n\n\t\t%s WON BY %d RUNS\n\n", teamA, (total_runs_batA - total_runs_batB));

	// else if both team's runs are same then the match would be draw
	else
		printf("\n\n\t\t CLOSE GAME!! IT WAS A DRAW\n\n!!!");

	printf("--------------------------------------------------------------------\n");
	printf("\n\n\n");

	return 0;
}
