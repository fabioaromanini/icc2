#include <stdlib.h>
#include <stdio.h> 
#include <ctype.h>

#include <bool.h>

#define null_st "null"
#define false_st "false"
#define true_st "true"

// this project consists of a json lexical and semantical
// analyzer. it won't work with every single json, but contains
// enough rules to analyze simpler JSON files.

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

// helper function used while reading a number
bool issign(char c);

// tokens
bool isnumber(FILE *json_file);
bool istrue(FILE *json_file);
bool isfalse(FILE *json_file);
bool isnull(FILE *json_file);
bool isstring(FILE *json_file);

// values
bool istoken(FILE *json_file, int *answer);
bool ispair(FILE *json_file, int *answer);
bool isobject(FILE *json_file, int *answer);
bool isarray(FILE *json_file, int *answer);
bool isvalue(FILE *json_file, int *answer);

int main(int argc, char const *argv[]) {
	FILE *json_file = stdin;

	int *answer = (int *) calloc(ANS_SIZE, sizeof(int));
	int n_lines = 1;

	while(!feof(json_file)) {
		if(isvalue(json_file, answer)) {
			char c = fgetc(json_file);
			if(c == EOF) break;
			n_lines++;
		} else {
			printf("Error line %d\n", n_lines);
			break;
		}
	}

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

bool issign(char c) {
	return c == '-' || c == '+';
}

bool isnumber(FILE *json_file) {
	bool exponent = FALSE;
	bool fraction = FALSE;
	
	while(!feof(json_file)) {

		char c = fgetc(json_file);
		if(isdigit(c)) continue;
		else if(c == '.') {
			// since we already read the first digit of the number
			// in the function "istoken", there is no problem if the 
			// first char of the number is a '.'. On the other hand,
			// we can't have two points in a number,
			// so if we're already reading a decimal,
			// and find another point, it is not a valid
			// number. Also, we can't have a real number
			// on the exponent
			if(fraction || exponent)
				return FALSE;
			fraction = TRUE;		

			c = fgetc(json_file);
			if(!isdigit(c))
				return FALSE;

			continue;
		}
		else if(c == 'e' || c == 'E') {
		
			if(exponent)
				return FALSE;
			exponent = TRUE;


			// whether the exponent is signed or not,
			// it must have at least a digit
			c = fgetc(json_file);
			if(issign(c)) {
				c = fgetc(json_file);
				if(!isdigit(c))
					return FALSE;
			}
			else if(!isdigit(c))
				return FALSE;

			continue;
		}
		else if(c == ']' || c == '}' || c == ',' || c == EOF || c == ' ' || c == '\n') {
			fseek(json_file, -1, SEEK_CUR);
			return TRUE;
		}
	}

	return FALSE;
}

bool istrue(FILE *json_file) {
	int position = 1; 

	while(!feof(json_file) && position < 4) {

		char c = fgetc(json_file);	
		if(c != true_st[position])
			return FALSE;

		position++;
	}

	// we alread checked that the word we just read in fact contains
	// the reserved keyword "true". Now we'll check if it's exactly
	// the word we're looking for. The same validation is also
	// executed after the keywords "false" and "null"
	char next_char = fgetc(json_file);
	if(next_char != '}' && next_char != ']' &&
	   next_char != ',' && next_char != EOF && !isblank(next_char)) {
		return FALSE;
	}

	fseek(json_file, -1, SEEK_CUR);

	return TRUE;
}

bool isfalse(FILE *json_file) {
	int position = 1; 

	while(!feof(json_file) && position < 5) {
		
		char c = fgetc(json_file);
		if(c != false_st[position])
			return FALSE;

		position++;
	}

	char next_char = fgetc(json_file);
	if(next_char != '}' && next_char != ']' &&
	   next_char != ',' && next_char != EOF && !isblank(next_char)) {
		return FALSE;
	}

	fseek(json_file, -1, SEEK_CUR);
	return TRUE;
}

bool isnull(FILE *json_file) {
	int position = 1; 

	while(!feof(json_file) && position < 4) {
		
		char c = fgetc(json_file);
		if(c != null_st[position])
			return FALSE;

		position++;
	}

	char next_char = fgetc(json_file);
	if(next_char != '}' && next_char != ']' &&
	   next_char != ',' && next_char != EOF && !isblank(next_char)) {
		return FALSE;
	}

	fseek(json_file, -1, SEEK_CUR);
	return TRUE;
}

bool isstring(FILE *json_file) {
	if(feof(json_file))
		return FALSE;

	char c = fgetc(json_file);
	if(c == '\"'){
		c = fgetc(json_file);

		// """ is not a valid string
		if(c == '\"')
			return FALSE;

		// but "" (empty string) is
		fseek(json_file, -1, SEEK_CUR);
		return TRUE;
	}
	fseek(json_file, -1, SEEK_CUR);

	while(!feof(json_file) && c != '\"') {
		c = fgetc(json_file);
		if(c == '\\') {
			c = fgetc(json_file);

			bool invalid = FALSE;
			invalid += (c == '\\');
			invalid += (c == '\"');
			invalid += (c == EOF);
			invalid += (c == 'b');
			invalid += (c == 'f');
			invalid += (c == 'n');
			invalid += (c == 'r');
			invalid += (c == 't');
			invalid += (c == 'u');
			
			if(invalid) return FALSE;
		}
	}
	
	return TRUE;
}

bool istoken(FILE *json_file, int *answer) {
	char c = fgetc(json_file);
	if(c == '\"') {

		if(isstring(json_file)) {
			answer[STRINGS]++;
			return TRUE;
		}

	} else if(issign(c)) { // deals with signed numbers
		c = fgetc(json_file);

		if(!isdigit(c)) {
			return FALSE;
		}

		if(isnumber(json_file)) {
			answer[NUMBERS]++;
			return TRUE;
		}
	} else if(isdigit(c)) {
		
		if(isnumber(json_file)) {
			answer[NUMBERS]++;
			return TRUE;
		}
	} else if(c == 't') {
		
		if(istrue(json_file)) {
			answer[TRUES]++;
			return TRUE;
		}
	}
	else if(c == 'f') {
		
		if(isfalse(json_file)) {
			answer[FALSES]++;
			return TRUE;
		}
	}
	else if(c == 'n') {
		
		if(isnull(json_file)) {
			answer[NULLS]++;
			return TRUE;
		}
	}

	return FALSE;
}

bool ispair(FILE *json_file, int *answer) {
	if(isstring(json_file)) {
		answer[STRINGS]++;

		char c = fgetc(json_file);
		// ignores whitespaces
		while(isblank(c)) c = fgetc(json_file);

		if(c != ':') return FALSE;

		if(isvalue(json_file, answer)) {
			answer[PAIRS]++;
			return TRUE;
		}
	}

	return FALSE;
}

bool isobject(FILE *json_file, int *answer) {
	while(!feof(json_file)) {
		char c = fgetc(json_file);

		while(isblank(c)) c = fgetc(json_file);
		
		if(c == '}') {
			answer[OBJECTS]++;
			return TRUE;
		} else if(c == ',') {
			c = fgetc(json_file);
			
			while(isblank(c))
				c = fgetc(json_file);
			
			// if we have a comma, we must have
			// at least another pair after the comma
			if(c != '\"')
				return FALSE;
		}

		if(c == '\"' && ispair(json_file, answer)) {
			c = fgetc(json_file);
			while(isblank(c)) c = fgetc(json_file);
			
			if(c == ',' || c == '}') {
				fseek(json_file, -1, SEEK_CUR);
				continue;
			}
		}

		return FALSE;
	}

	// if the file ended, and we haven't finished the object,
	// we surely have an error
	return FALSE;
}

bool isarray(FILE *json_file, int *answer) {
	while(!feof(json_file)) {
		char c = fgetc(json_file);
		while(isblank(c)) {
			c = fgetc(json_file);
		}

		if(c == ',') continue;

		if(c == ']') {
			answer[ARRAYS]++;
			return TRUE;
		}
		else {
			fseek(json_file, -1, SEEK_CUR);
			
			if(!isvalue(json_file, answer))
				return FALSE;
		}
	}

	// as with the object, if the file ended and we haven't
	// finished the array, we have an error
	return FALSE;
}

bool isvalue(FILE *json_file, int *answer) {
	char c = fgetc(json_file);

	while(isspace(c)) c = fgetc(json_file);

	if(c == EOF) return TRUE;
	if(c == '[')
		return isarray(json_file, answer);
	
	else if(c == '{')
		return isobject(json_file, answer);
	
	else {
		fseek(json_file, -1, SEEK_CUR);
		return istoken(json_file, answer);
	}
}
