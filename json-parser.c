#include <stdlib.h>
#include <stdio.h> 
#include <ctype.h>

#include <bool.h>
#include <stack.h>

#define N_DELIMITERS 200

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

bool issign(char c) {
	return c == '-' || c == '+';
}

bool isnumber(FILE *fp) {
	bool exponent = false;
	bool fraction = false;
	
	while(!feof(fp)) {
		char c = fgetc(fp);

		if(isdigit(c)) continue;
		else if(c == '.') {
		
			if(fraction)
				return false;
			fraction = true;
		
			c = fgetc(fp);
			
			if(!isdigit(c))
				return false;

			continue;
		}
		else if(c == 'e' || c == 'E') {
		
			if(exponent)
				return false;
			exponent = true;
			fraction = true; // we cannot have a real number on the exponent

			c = fgetc(fp);

			if(issign(c)) {
				c = fgetc(fp);
				
				if(!isdigit(c))
					return false;
			}
			else if(!isdigit(c))
				return false;

			continue;
		}
		else if(c == ']' || c == '}' || c == ',' || c == EOF) {
			fseek(fp, -1, SEEK_CUR);
			return true;
		}
		else
			return false;
	}

	return false;
}

bool istrue(FILE *fp) {
	int position = 1; 
	const char true_st[4] = "true";

	while(!feof(fp) && position < 4) {
		char c = fgetc(fp);
		
		if(c != true_st[position]) {
			return false;
		}

		position++;
	}

	return true;
}

int isfalse(FILE *fp) {
	int position = 1; 
	const char false_st[5] = "false";

	while(!feof(fp) && position < 5) {
		char c = fgetc(fp);
		
		if(c != false_st[position]) {
			return false;
		}

		position++;
	}

	return true;
}

bool isnull(FILE *fp) {
	int position = 1; 
	const char null_st[4] = "null";

	while(!feof(fp) && position < 4) {
		char c = fgetc(fp);
		
		if(c != null_st[position]) {
			return false;
		}

		position++;
	}

	return true;
}

int main(int argc, char const *argv[]) {
	FILE *json_file = stdin;
	int *answer = (int *) calloc(ANS_SIZE, sizeof(int));
	bool error = false;
	int line = 1;
	stack_t* delimiters = stack_init(N_DELIMITERS);

	while(!feof(json_file)) {
		char c = fgetc(json_file);

		if(c == '{') {
			push(delimiters, '{');
		}
		else if(c == '}') {
			if(pop(delimiters) != '{')
				error = true;
			else
				answer[OBJECTS]++;
		}
		else if(c == '[') {
			push(delimiters, '[');
		}
		else if(c == ']') {
			if(pop(delimiters) != '[')
				error = true;
			else
				answer[ARRAYS]++;
		}
		else if(isdigit(c)) {
			
			if(isnumber(json_file)) {
				answer[NUMBERS]++;
				// printf("NUMBER");
				continue;
			}

			error = true;
			break;
		}
		else if(c == 't') {
			
			if(istrue(json_file)) {
				answer[TRUES]++;
				// printf("TRUE");
				continue;
			}

			error = true;
			break;
		}
		else if(c == 'f') {
			
			if(isfalse(json_file)) {
				answer[FALSES]++;
				// printf("FALSE");
				continue;
			}

			error = true;
			break;
		}
		else if(c == 'n') {
			
			if(isnull(json_file)) {
				answer[NULLS]++;
				// printf("NULL");
				continue;
			}

			error = true;
			break;
		}
		else if(c == EOF || isblank(c)) {
			continue;
		}
		else if(c == '\n')
			line++;

		if(error)
			break;

		// printf("%c", c);
	}

	if(!is_empty(delimiters))
		error = true;

	if(error)
		printf("Error line %d\n", line);

	// printf("\nFinished file!\n");
	// printf("\nthe file had %d lines!\n", line);

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