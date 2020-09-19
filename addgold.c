#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
	printf("Content_Type:text/html\n\n");
	int goldpieces, found = 0;
	char line[200];
	FILE * f = fopen("../index.html", "rt");
	
	char *payload=getenv("QUERY_STRING");

	sscanf(payload, "gold=%d", &goldpieces); 

	if (f == NULL) printf("Error!");
	else {
	fgets(line, 199, f);
	while(!feof(f)) {
		printf("%s", line);
		if (found == 1) {
			// insert the hiddent field on the next loop when "<form" is found 
			printf("<input type=\"hidden\" name=\"gold\"value=\"%d\">", goldpieces);
			found = 0;
		}
		// if "<form" is found
		if (strstr(line, "<form") != NULL) found = 1;
		fgets(line, 199, f);
		}
	}
}
