#include <stdlib.h>
#include <stdio.h> 
#include <ctype.h>

#include <bool.h>
#include <stack.h>

#define N_DELIMITERS 200

#define null_st "null"
#define false_st "false"
#define true_st "true"

#define STRING_END '\"'


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

// Token Helper
bool issign(char c) {
	return c == '-' || c == '+';
}

// Tokens
bool isnumber(FILE *fp) {
	bool exponent = FALSE;
	bool fraction = FALSE;
	
	while(!feof(fp)) {

		char c = fgetc(fp);
		if(isdigit(c)) continue;
		else if(c == '.') {
		
			if(fraction)
				return FALSE;
			fraction = TRUE;		

			c = fgetc(fp);
			if(!isdigit(c))
				return FALSE;

			continue;
		}
		else if(c == 'e' || c == 'E') {
		
			if(exponent)
				return FALSE;
			exponent = TRUE;
			fraction = TRUE; // we cannot have a real number on the exponent

			c = fgetc(fp);
			if(issign(c)) {

				c = fgetc(fp);
				if(!isdigit(c))
					return FALSE;
			}
			else if(!isdigit(c))
				return FALSE;

			continue;
		}
		else if(c == ']' || c == '}' || c == ',' || c == EOF) {
			fseek(fp, -1, SEEK_CUR);
			return TRUE;
		}
		else
			return FALSE;
	}

	// This is unnecessary, since the function never executes these lines.
	// But, I'm leaving it here just to prevent warnings in compilation
	return FALSE;
}

bool istrue(FILE *fp) {
	int position = 1; 

	while(!feof(fp) && position < 4) {

		char c = fgetc(fp);	
		if(c != true_st[position])
			return FALSE;

		position++;
	}

	return TRUE;
}


bool isfalse(FILE *fp) {
	int position = 1; 

	while(!feof(fp) && position < 5) {
		
		char c = fgetc(fp);
		if(c != false_st[position])
			return FALSE;

		position++;
	}

	return TRUE;
}

bool isnull(FILE *fp) {
	int position = 1; 

	while(!feof(fp) && position < 4) {
		
		char c = fgetc(fp);
		if(c != null_st[position])
			return FALSE;

		position++;
	}

	return TRUE;
}

// bool isstring(FILE *fp) {
	// int position = 1;

	// while(!feof(fp) && c != '\"') { // '\"' => character that
									// terminates a string
		// char c = fgetc(fp);
		// if(c != )
			// return FALSE;

		// position++;
	// }

	// return TRUE;
// }

int main(int argc, char const *argv[]) {
	FILE *json_file = stdin;
	int *answer = (int *) calloc(ANS_SIZE, sizeof(int));
	bool error = FALSE;
	int line = 1;
	stack_t* delimiters = stack_init(N_DELIMITERS);

	// eventually, this will become a recursion
	while(!feof(json_file)) {
		char c = fgetc(json_file);

		if(c == '{') {
			push(delimiters, '{');
		}
		else if(c == '}') {
			if(pop(delimiters) != '{')
				error = TRUE;
			else
				answer[OBJECTS]++;
		}
		else if(c == '[') {
			push(delimiters, '[');
		}
		else if(c == ']') {
			if(pop(delimiters) != '[')
				error = TRUE;
			else
				answer[ARRAYS]++;
		}
		else if(isdigit(c)) {
			
			if(isnumber(json_file)) {
				answer[NUMBERS]++;
				printf("NUMBER");
				continue;
			}

			error = TRUE;
			break;
		}
		else if(c == 't') {
			
			if(istrue(json_file)) {
				answer[TRUES]++;
				printf("TRUE");
				continue;
			}

			error = TRUE;
			break;
		}
		else if(c == 'f') {
			
			if(isfalse(json_file)) {
				answer[FALSES]++;
				printf("FALSE");
				continue;
			}

			error = TRUE;
			break;
		}
		else if(c == 'n') {
			
			if(isnull(json_file)) {
				answer[NULLS]++;
				printf("NULL");
				continue;
			}

			error = TRUE;
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

	if(!is_empty(delimiters))
		error = TRUE;

	if(error)
		printf("Error line %d\n", line);

	printf("\n\nFinished file!\n");
	printf("the file haves %d lines\n", line);

	printf("Number of Objects: %d\n", answer[OBJECTS]);
	printf("Number of Arrays: %d\n", answer[ARRAYS]);
	printf("Number of Pairs: %d\n", answer[PAIRS]);
	printf("Number of Strings: %d\n", answer[STRINGS]);
	printf("Number of Numbers: %d\n", answer[NUMBERS]);
	printf("Number of Trues: %d\n", answer[TRUES]);
	printf("Number of Falses: %d\n", answer[FALSES]);
	printf("Number of Nulls: %d\n", answer[NULLS]);

	stack_destroy(delimiters);	
	free(answer);
	return 0;
}