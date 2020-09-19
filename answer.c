#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//save payload into string[]
void load_post_string(char string[]) {
	char c;
	int a = 0, n = atoi(getenv( "CONTENT_LENGTH"));
	
	while ((c = getchar()) != EOF && a < n) {
		if (a<200) {
			if (c!='+') string[a]=c;
	       		else string[a] = ' ';
	 		a++;
		}
	}
	string[a] = '\0';
}

// redirect player to new chamber with URL, goldnum, and direction
void output(char* URL, int goldnum, char* direction) {

	printf("Content_Type:text/html\n\n");
	printf("<html>");
	printf("<a href=\"%s%d\">Press HERE to go %s</a>", URL, goldnum, direction);
	printf("</html>");
}

// display the player with current gold pieces
void gold(char line[], int *goldnum) {
	// URL to go back to current chamber
	char URL[] = "https://www.cs.mcgill.ca/~zxu45/cgi-bin/addgold.cgi?gold=";
	// If goldnum has not been initialized
	if (strstr(line, "gold") == NULL) *goldnum = 10;
	
	printf("Content_Type:text/html\n\n");
	printf("<html>");
	printf("<b> You have %d pieces of gold.</b>", *goldnum);
	printf("<a href=\"%s%d\">Press HERE to go back</a>", URL, *goldnum);
	printf("</html>");

}
void check_answer(char* answer, int *goldnum) {
	// URL to go back to current chamber
	char URL[] = "https://www.cs.mcgill.ca/~zxu45/cgi-bin/addgold.cgi?gold=";
	printf("Content_Type:text/html\n\n");
	printf("<html>");
	
	// "10" is the answer (in binary)
	if (strcmp(answer, "10") == 0) {
		printf("<b> Correct. </b>");
		*goldnum = *goldnum + 10;
	}
	else {
		printf("<b> Wrong! </b>");
		*goldnum = *goldnum - 5;
	}	

	printf("<a href=\"%s%d\">Press HERE to go back</a>", URL, *goldnum);
	printf("</html>");

}



void main() {
	
	char payload[200];
	//save payload to payload[200]
	load_post_string(payload);
	
	char answer[20];
	int goldnum;
	//parse answer and goldnum
	sscanf(payload, "user_input=%[^&]&gold=%d", answer, &goldnum);
	
	if (goldnum < 0 || goldnum > 100) goldnum = 10;

	// LOSE
	if (goldnum == 0) {
		printf("Content_Type:text/html\n\n");
		printf("<html>");
		printf("<b> YOU LOSE! </b>");
		printf("<img src=\"/~zxu45/lose.jpg\" alt=\"meme\" height=\"259\" width=\"300\">");
		printf("</html>");
		return;
	}
	// WIN
	else if (goldnum == 100) {
		printf("Content_Type:text/html\n\n");
		printf("<html>");
		printf("<b> YOU WIN! </b>");
		printf("<img src=\"/~zxu45/win.jpg\" alt=\"meme\" height=\"240\" width=\"309\">");
		printf("</html>");
		return;
	}
	
	// else check answer
	if ( strcmp(answer, "NORTH") == 0) {
		output("https://www.cs.mcgill.ca/~kliu31/cgi-bin/addgold.cgi?gold=", goldnum, "north");		
	} else if ( strcmp(answer, "SOUTH") == 0) {
		output("https://www.cs.mcgill.ca/~jzhou70/cgi-bin/addgold.cgi?gold=", goldnum, "south");	
	} else if ( strcmp(answer, "EAST") == 0) {
		output("https://www.cs.mcgill.ca/~yfu14/cgi-bin/addgold.cgi?gold=", goldnum, "east");
	} else if ( strcmp(answer, "WEST") == 0) {
		output("https://www.cs.mcgill.ca/~zxiao10/cgi-bin/addgold.cgi?gold=", goldnum, "west");
	} else if ( strcmp(answer, "GOLD") == 0) {
		gold(payload, &goldnum);
	} else {
		// then the user must typed answer to the question
		check_answer(answer, &goldnum);
	}


}

