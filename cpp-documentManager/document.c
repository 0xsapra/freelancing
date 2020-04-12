#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "document.h"

int init_document(Document *doc, const char *name){
	int size_name;

	if(doc == NULL || name == NULL){
		return FAILURE;
	}
	size_name = strlen(name);
	if(size_name > MAX_STR_SIZE){
		return FAILURE;
	}
	doc->number_of_paragraphs = 0;
	strncpy(doc->name, name, size_name + 1);
	return SUCCESS;
}

int print_document(Document *doc){
	int i, j, print_newline = 0;

	if(doc == NULL){
		return FAILURE;
	}
	printf("Document name: \"%s\"\n", doc->name);
	printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
	for(i = 0; i < doc->number_of_paragraphs; i++){
		Paragraph paragraph = doc->paragraphs[i];
		for(j = 0; j < paragraph.number_of_lines; j++){
			print_newline = 1;
			printf("%s\n", paragraph.lines[j]);
		}
		if(print_newline == 1){
			print_newline = 0;
			if( i != doc->number_of_paragraphs - 1){
				printf("\n");	
			}
			
		}
		
	}
	return SUCCESS;
}

int reset_document(Document *doc){
	if(doc == NULL){
		return FAILURE;
	}
	doc->number_of_paragraphs = 0;
	return SUCCESS;
}

int add_paragraph_after(Document *doc, int paragraph_number){
	Paragraph *paragraph;
	int prev_para_number;

	if(doc == NULL){
		return FAILURE;
	}
	if(doc->number_of_paragraphs >= MAX_PARAGRAPHS ){
		return FAILURE;
	}
	if(paragraph_number >= MAX_PARAGRAPHS){
		return FAILURE;
	}
	prev_para_number = doc->number_of_paragraphs;
	if(paragraph_number > prev_para_number + 1){
		return FAILURE;
	}

	doc->number_of_paragraphs = paragraph_number + 1;
	paragraph = &doc->paragraphs[paragraph_number];
	paragraph->number_of_lines = 0;
	return SUCCESS;
}

int add_line_after(Document *doc, int paragraph_number, int line_number,
		   const char *new_line){
	int paragraph_index, line_index, new_line_size;
	Paragraph *paragraph;

	if(doc == NULL){
		return FAILURE;
	}
	if(doc->number_of_paragraphs >= MAX_PARAGRAPHS ){
		return FAILURE;
	}
	if(line_number >= MAX_PARAGRAPH_LINES){
		return FAILURE;
	}
	if(new_line == NULL){
		return FAILURE;
	}
	new_line_size = strlen(new_line);
	/*
	What if the new line size if greater than avialble size. In that case we clip
	*/
	if(new_line_size > MAX_STR_SIZE){
		return FAILURE;
	}
	/*
	the paragraph already has the maximum number of lines allowed
	*/
	paragraph_index = paragraph_number - 1;
	line_index = line_number;
	paragraph = &doc->paragraphs[paragraph_index];
	if(paragraph->number_of_lines >= MAX_PARAGRAPH_LINES){
		return FAILURE;
	}
	paragraph->number_of_lines = line_number + 1;
	strncpy(paragraph->lines[line_index], new_line, new_line_size + 1);

	return SUCCESS;
}


int append_line(Document *doc, int paragraph_number, const char *new_line){
	int paragraph_index, line_number, new_line_size;
	Paragraph *paragraph;

	if(doc == NULL){
		return FAILURE;
	}
	if(doc->number_of_paragraphs >= MAX_PARAGRAPHS ){
		return FAILURE;
	}
	if(new_line == NULL){
		return FAILURE;
	}
	new_line_size = strlen(new_line);
	if(new_line_size > MAX_STR_SIZE){
		return FAILURE;
	}
	paragraph_index = paragraph_number - 1;
	paragraph = &doc->paragraphs[paragraph_index];
	line_number = paragraph->number_of_lines;
	if(line_number >= MAX_PARAGRAPH_LINES){
		return FAILURE;
	}
	add_line_after(doc, paragraph_number, line_number, new_line);
	return SUCCESS;
}

int remove_line(Document *doc, int paragraph_number, int line_number){
	int i, paragraph_index;
	Paragraph *paragraph;

	if(doc == NULL){
		return FAILURE;
	}
	if(paragraph_number >= MAX_PARAGRAPHS){
		return FAILURE;
	}
	if(line_number >= MAX_PARAGRAPH_LINES){
		return FAILURE;
	}
	paragraph_index = paragraph_number - 1;
	paragraph = &doc->paragraphs[paragraph_index];
	for(i = line_number - 1;i < paragraph->number_of_lines - 1; i++){
		strcpy(paragraph->lines[i],paragraph->lines[i+1]);
	}
	paragraph->number_of_lines = paragraph->number_of_lines - 1;
	return SUCCESS;
}

int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines){
	int i, paragraph_number = doc->number_of_paragraphs;
	char* current_line;

	if(doc == NULL){
		return FAILURE;
	}
	if(data_lines <= 0){
		return FAILURE;
	}
	if(data == NULL){
		return FAILURE;
	}
	add_paragraph_after(doc, paragraph_number);
	paragraph_number++;
	for(i = 0;i < data_lines; i++){
		current_line = data[i];
		if(strcmp(current_line, "") == 0){
			add_paragraph_after(doc, paragraph_number);
			paragraph_number++;
		} else {
			append_line(doc, paragraph_number, current_line);
		}
	}

	return SUCCESS;
}
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines){
	Paragraph *paragraph;
	int lines_count;

	if(doc == NULL){
		return FAILURE;
	}
	if(paragraph_number > MAX_PARAGRAPHS){
		return FAILURE;
	}
	if(number_of_lines == NULL){
		return FAILURE;
	}
	paragraph = &doc->paragraphs[paragraph_number];
	lines_count = paragraph->number_of_lines;
	*number_of_lines = lines_count;
	return SUCCESS;
}

int str_replace(char *subject, const char *search, const char* replace ){

	char buffer[MAX_STR_SIZE + 1];
	int i = 0, j = 0, loc, search_string_len, replace_str_len, prev_val = 0;
	if(strlen(subject) == 0){
		return FAILURE;
	}
	loc = strstr(subject, search) - subject;
	search_string_len = strlen(search);
	replace_str_len = strlen(replace);
	if(loc <= -1){
		return FAILURE;
	}
	if(search_string_len == 0){
		return FAILURE;
	}
	strcpy(buffer, subject);
	while(loc >= 0 && loc <= MAX_STR_SIZE){
		for(;prev_val < loc; i++){
			subject[i] = buffer[prev_val++];
		}
		for(j = 0; j < replace_str_len; j++, i++){
			subject[i] = replace[j];
		}
		if(loc >= strlen(subject)){
			break;
		}
		loc = strstr(subject + prev_val +1, search ) - (subject);
		prev_val = prev_val + search_string_len;
	}
	while(subject[prev_val] != '\0'){
		subject[i] = buffer[prev_val];
		i++;
		prev_val++;
	}
	subject[i] = '\0';
	return SUCCESS;
}

int replace_text(Document *doc, const char *target, const char *replacement){
	Paragraph *paragraph;
	int i, j;

	if(doc == NULL){
		return FAILURE;
	}
	if(target == NULL || replacement == NULL){
		return FAILURE;
	}
	for(i = 0; i < doc->number_of_paragraphs; i++){
		paragraph = &doc->paragraphs[i];
		for(j = 0; j < paragraph->number_of_lines; j++){
			str_replace(paragraph->lines[j], target, replacement);
		}
	}
	return SUCCESS;
}
int str_replace1(char *subject, const char *search, const char* replace ){

	char buffer[MAX_STR_SIZE + 1];
	int i = 0, j = 0, loc, search_string_len, replace_str_len, prev_val = 0;
	if(strlen(subject) == 0){
		return FAILURE;
	}
	loc = strstr(subject, search) - subject;
	search_string_len = strlen(search);
	replace_str_len = strlen(replace);
	if(loc <= -1){
		return FAILURE;
	}
	if(search_string_len == 0){
		return FAILURE;
	}
	strcpy(buffer, subject);
	while(loc >= 0 && loc <= MAX_STR_SIZE){
		for(;prev_val < loc; i++){
			subject[i] = buffer[prev_val++];
		}
		for(j = 0; j < replace_str_len; j++, i++){
			subject[i] = replace[j];
		}
		if(loc >= strlen(subject)){
			break;
		}
		loc = strstr(buffer + prev_val +1, search ) - (subject);
		prev_val = prev_val + search_string_len;
	}
	while(subject[prev_val] != '\0'){
		subject[i] = buffer[prev_val];
		i++;
		prev_val++;
	}
	subject[i] = '\0';
	return SUCCESS;
}

int highlight_text(Document *doc, const char *target){
	Paragraph *paragraph;
	int i, j, target_len;
	char replacement[100] = HIGHLIGHT_START_STR;
	
	target_len = strlen(target);
	strcat(replacement, target);
	strcat(replacement, HIGHLIGHT_END_STR);
	if(doc == NULL){
		return FAILURE;
	}
	if(target == NULL){
		return FAILURE;
	}
	for(i = 0; i < doc->number_of_paragraphs; i++){
		paragraph = &doc->paragraphs[i];
		for(j = 0; j < paragraph->number_of_lines; j++){
			str_replace1(paragraph->lines[j], target, replacement);
		}
	}
	return SUCCESS;
}

int remove_text(Document *doc, const char *target){
	Paragraph *paragraph;
	int i, j;
	char remove[] = "";

	if(doc == NULL){
		return FAILURE;
	}
	if(target == NULL){
		return FAILURE;
	}
	for(i = 0; i < doc->number_of_paragraphs; i++){
		paragraph = &doc->paragraphs[i];
		for(j = 0; j < paragraph->number_of_lines; j++){
			str_replace(paragraph->lines[j], target, remove);
		}
	}
	return SUCCESS;
}

int load_file(Document *doc, const char *filename){

	FILE *fptr;
	char data[MAX_PARAGRAPHS * MAX_PARAGRAPH_LINES + 1][MAX_STR_SIZE + 1], current_line[MAX_STR_SIZE + 1];
	int current_paragraph_line = 0, paragraph_count = 1, current_line_size;

	if(doc == NULL){
		return FAILURE;
	}
	if(filename == NULL){
		return FAILURE;
	}
	fptr = fopen(filename,"r");
	if(NULL == fptr){
		/* Document suggest not to send error, idk what to do*/
        return FAILURE;
    }
	/* return FAIL: opening the file failed, or the number of paragraphs would exceed MAX PARAGRAPHS; 
	
	. If the number of paragraphs would exceed MAX PARAGRAPHS, the function adds
	paragraphs until the maximum limit is reached. Notice no error message is generated if the file cannot
	be opened.
	*/
	while(fgets(current_line, MAX_STR_SIZE, fptr)) {

		current_line_size = strlen(current_line) - 1;
		current_line[current_line_size] = '\x00';

		if ( current_line_size > MAX_STR_SIZE){
			current_line_size = MAX_STR_SIZE;
		}
    	strncpy(data[current_paragraph_line], current_line, current_line_size + 1 );
    	current_paragraph_line++;
    	if( isspace(current_line[0]) ){
    		paragraph_count += 1;
    		if ( paragraph_count >= MAX_PARAGRAPHS ){
    			break;
    		}
    	}
	}
	load_document(doc, data, current_paragraph_line);

	return SUCCESS;
}

int save_document(Document *doc, const char *filename){

	int i, j, print_newline = 0;
	FILE *fptr;

	if(doc == NULL){
		return FAILURE;
	}
	if(filename == NULL){
		return FAILURE;
	}

	fptr = fopen(filename, "w");
	printf("***** SAVED FILE *****\n");
	if(fptr == NULL){
		return FAILURE;
	}
	for(i = 0; i < doc->number_of_paragraphs; i++){
		Paragraph paragraph = doc->paragraphs[i];
		for(j = 0; j < paragraph.number_of_lines; j++){
			print_newline = 1;
			fprintf(fptr, "%s\n", paragraph.lines[j]);
			printf("%s\n", paragraph.lines[j]);
		}
		if(print_newline == 1){
			print_newline = 0;
			fprintf(fptr, "\n");
			printf("\n");
		}	
	}
	return SUCCESS;

}


