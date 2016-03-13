/*
This program replaces words in a file by using a vocabulary file.
Vocabulary file format:
	word MARKING_CHARreplacement
	word MARKING_CHARreplacement
	word MARKING_CHARreplacement
	... (NO UPPER CASE LETTERS!)
*/

#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#define WRONG_ARG (-1)
#define CANNOT_OPEN (-2)
#define CANNOT_CLOSE (-3)
#define MAX_COUNT (100)	/* max characters to read at once (one word) */
#define MARKING_CHAR ('A')
#define TEXT_MAX (1000000)	/* max text/line size */

/* functions declartion: */
int get_word(FILE * working_file, char * storage);
int find_next_word(FILE * working_file);
int find_replacement(FILE * working_file, char * word, char * replacement);
int get_replacement(FILE * working_file, char * storage);
void replace_word(FILE * working_file, char * word, int length, char * replacement, int replacement_length);

/* MAIN: */
int main(int argc, char * argv[])
{
	FILE * source_file = NULL;
	FILE * vocabulary_file = NULL;
	char * word;
	char * replacment;
	int word_length;
	int replacment_length;

	/* Check argument count */
	if(argc != 3) {
		printf("Usage: Vocabulary source_file vocabulary_file");
		return WRONG_ARG;
	}

	/* Open files */
	source_file = fopen(argv[1], "r+");
	if (source_file == NULL) {
		printf("Could not open %s.\n", argv[1]);
		return CANNOT_OPEN;
	}

	vocabulary_file = fopen(argv[2], "r");
	if (vocabulary_file == NULL) {
		printf("Could not open %s.\n", argv[2]);
		return CANNOT_OPEN;
	}

	/* Real programming! */
	word = (char *)malloc(MAX_COUNT);
	replacment = (char *)malloc(MAX_COUNT);
	while (find_next_word(source_file) != EOF) {
		word_length = get_word(source_file, word);
		if (find_replacement(vocabulary_file, word, replacment) == 1) {
			replacment_length = get_replacement(vocabulary_file, replacment);
			replace_word(source_file, word, word_length, replacment, replacment_length);
		}
	}

	/* Close files */
	if (fclose(source_file) != 0) {
		printf("Could not close %s.\n", argv[1]);
		return CANNOT_CLOSE;
	}

	if (fclose(vocabulary_file) != 0) {
		printf("Could not close %s.\n", argv[2]);
		return CANNOT_CLOSE;
	}

	/* End of program */
	free(word);
	free(replacment);
	return 0;
}

/* functions definition: */

/* get a word from a file: */
int get_word(FILE * working_file, char * storage)
{
	int i;
	for (i = 0; i < MAX_COUNT; ++i) {
		if (!isalpha(storage[i] = fgetc(working_file))) {
			storage[i] = '\0';		
			return i;
		}
	}
	return 0;
}

/* find where the next word in the file starts, and point to it: */
int find_next_word(FILE * working_file)
{
	int state = 0;
	while (!isalpha(state = fgetc(working_file))) {
		if (state == EOF) {
			break;
		}
	}
	fseek(working_file, -1, SEEK_CUR);	/*return 1 character backward to the first character of the next word*/
	return state;
}

/* find a match in the vocabulary file: */
int find_replacement(FILE * working_file, char * word, char * replacement)
{
	int i;
	rewind(working_file);	/*return to the file start*/
	while (find_next_word(working_file) != EOF) {
		get_word(working_file, replacement);
		if (replacement[0] != MARKING_CHAR) {
			for (i = 0; i < MAX_COUNT; ++i) {
				if (tolower(word[i]) != tolower(replacement[i])) {
					break;
				}
				else if (word[i] == '\0' && replacement[i] == '\0') {
					return 1;
				}
			}
		}
	}
	return 0;
}

/* get the replacement pointer to point on the replacement itself (not the same word) */
int get_replacement(FILE * working_file, char * storage)
{
	int length;
	find_next_word(working_file);
	if (fgetc(working_file) != MARKING_CHAR) {
		fseek(working_file, -1, SEEK_CUR);
	}	/* Not including the MARKING_CHAR at the beginning of each word. */ 
	length = get_word(working_file, storage);
	return length;
}

/* After finding the word to replace, replace it: */
void replace_word(FILE * working_file, char * word, int word_length, char * replacement, int replacement_length)
{
	int i;
	char * text = (char *)malloc(TEXT_MAX);
	int position;
	fseek(working_file, -1, SEEK_CUR);
	position = ftell(working_file);
	for(i = 0; i < TEXT_MAX; ++i) {	/*read all text after the word to replace*/
		if((text[i] = fgetc(working_file)) == EOF) {
			text[i] = '\0';
			break;
		}
	}
	fseek(working_file, position-word_length, SEEK_SET);		/*return to the beginning of the word to replace*/
	for(i = 0; i < replacement_length; ++i) {
		fputc(replacement[i], working_file);
	}
	position = ftell(working_file);
	fputs(text, working_file);
	for (i = 0; i < word_length - replacement_length; ++i)
	{
		fputc('\0', working_file);
	}
	printf(" -%s- ", text);
	free(text);
	fseek(working_file, position, SEEK_SET);
}