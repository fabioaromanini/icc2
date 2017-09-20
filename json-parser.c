#include <stdlib.h>
#include <stdio.h> 
#include <ctype.h>

enum {
	OBJECTS,
	ARRAYS,
	PAIRS,
	STRINGS,
	NUMBERS,
	TRUES,
	FALSES,
	NULLS,
	ANS_SIZE
};

int issign(char c) {
	return c == '-' || c == '+';
}

int isnumber(FILE *fp) {
	int exponent = 0;
	int fraction = 0;
	
	while(!feof(fp)) {
		char c = fgetc(fp);

		if(isdigit(c)) continue;
		else if(c == '.') {
		
			if(fraction)
				return 0;
			fraction = 1;
		
			c = fgetc(fp);
			
			if(!isdigit(c))
				return 0;

			continue;
		}
		else if(c == 'e' || c == 'E') {
		
			if(exponent)
				return 0;
			exponent = 1;
			fraction = 1; // we cannot have a real number on the exponent

			c = fgetc(fp);

			if(issign(c)) {
				c = fgetc(fp);
				
				if(!isdigit(c))
					return 0;
			}
			else if(!isdigit(c))
				return 0;

			continue;
		}
		else if(c == ']' || c == '}' || c == ',' || c == EOF) {
			fseek(fp, -1, SEEK_CUR);
			return 1;
		}
		else
			return 0;
	}
}

int istrue(FILE *fp) {
	int position = 1; 
	const char true[4] = "true";

	while(!feof(fp) && position < 4) {
		char c = fgetc(fp);
		
		if(c != true[position]) {
			return 0;
		}

		position++;
	}

	return 1;
}

int isfalse(FILE *fp) {
	int position = 1; 
	const char false[5] = "false";

	while(!feof(fp) && position < 5) {
		char c = fgetc(fp);
		
		if(c != false[position]) {
			return 0;
		}

		position++;
	}

	return 1;
}

int isnull(FILE *fp) {
	int position = 1; 
	const char null[4] = "null";

	while(!feof(fp) && position < 4) {
		char c = fgetc(fp);
		
		if(c != null[position]) {
			return 0;
		}

		position++;
	}

	return 1;
}

int main(int argc, char const *argv[]) {
	FILE *json_file = stdin;
	int *answer = (int *) calloc(ANS_SIZE, sizeof(int));
	int error = 0;
	int line = 1;

	while(!feof(json_file)) {
		char c = fgetc(json_file);
		if(c == '{') {
			// pop at stack
			answer[OBJECTS]++;
		}
		else if(c == '[') {
			// pop at stack
			answer[ARRAYS]++;
		}
		else if(isdigit(c)) {
			
			if(isnumber(json_file)) {
				answer[NUMBERS]++;
				printf("NUMBER");
				continue;
			}

			error = 1;
			break;
		}
		else if(c == 't') {
			
			if(istrue(json_file)) {
				answer[TRUES]++;
				printf("TRUE");
				continue;
			}

			error = 1;
			break;
		}
		else if(c == 'f') {
			
			if(isfalse(json_file)) {
				answer[FALSES]++;
				printf("FALSE");
				continue;
			}

			error = 1;
			break;
		}
		else if(c == 'n') {
			
			if(isnull(json_file)) {
				answer[NULLS]++;
				printf("NULL");
				continue;
			}

			error = 1;
			break;
		}
		else if(c == EOF || isblank(c)) {
			continue;
		}
		else if(c == '\n')
			line++;

		if(error)
			break;

		printf("%c", c);
	}

	if(error)
		printf("Error line %d\n", line);

	printf("\nFinished file!\n");
	printf("\nthe file had %d lines!\n", line);

	printf("Number of Objects: %d\n", answer[OBJECTS]);
	printf("Number of Arrays: %d\n", answer[ARRAYS]);
	printf("Number of Pairs: %d\n", answer[PAIRS]);
	printf("Number of Strings: %d\n", answer[STRINGS]);
	printf("Number of Numbers: %d\n", answer[NUMBERS]);
	printf("Number of Trues: %d\n", answer[TRUES]);
	printf("Number of Falses: %d\n", answer[FALSES]);
	printf("Number of Nulls: %d\n", answer[NULLS]);
	
	free(answer);
	return 0;
}