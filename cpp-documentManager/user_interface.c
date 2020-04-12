#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "document.h"


char* removeSpaces(char* string_from_file) {
	/* 
	* return 0 is not comment else 1
	*/

	int count = 0;
	char *temp_ptr = string_from_file;
	while((*temp_ptr == ' ' || *temp_ptr == '\t')  && count++ < MAX_COMMAND_LINE_SIZE){
		/* remove leading spaces */
		temp_ptr = temp_ptr + 1;
	}
	return temp_ptr;
}

int getCommand(char* string_from_file, char *command_name){
	/* 
	* return 0 is comment
	* return -1 empty line
	* return 1 if command
	*/
	int str_size, i;
	char* temp_ptr = removeSpaces(string_from_file);
	
	if(temp_ptr[0] == '#'){
		return 0;
	}
	if( strlen(temp_ptr) == 0 ){
		/* in case of empty line */
		return -1;
	}
	str_size = strlen(temp_ptr);
	for(i = 0; i < str_size; i++){
		if ( temp_ptr[i] == ' ' || temp_ptr[i] == '\t'){
			break;
		}
		command_name[i] = temp_ptr[i];
	}
	command_name[i] = '\0';
	return 1;
}

int perform_command(Document *doc, const char* command, char* current_line) {
	char argc2[1024], argc3[1024];
	int argi1 = -1, argi2 = -1;
	current_line = removeSpaces(current_line);

	if(strcmp(command, "load_file") == 0){
		*argc2 = '\0', *argc3 = '\0';
		sscanf(current_line, "%s %s\n", argc2, argc3);
		if(strlen(argc2) == 0 || strlen(argc3) == 0){
			return SUCCESS;
		}
		load_file(doc, argc3);
	} else if (strcmp(command, "print_document") == 0){
		print_document(doc);
	} else if (strcmp(command, "remove_text") == 0) {
		*argc2 = '\0';
		sscanf(current_line, "remove_text \"%s\"\n", argc2);
		if(strlen(argc2) == 0){
			return SUCCESS;
		}
		argc2[strlen(argc2) - 1] = '\0';
		remove_text(doc, argc2);
	} else if (strcmp(command, "highlight_text") == 0){
		*argc2 = '\0';
		sscanf(current_line, "highlight_text \"%s\"\n", argc2);
		if(strlen(argc2) == 0){
			return SUCCESS;
		}
		argc2[strlen(argc2) - 1] = '\0';
		highlight_text(doc, argc2);
	} else if(strcmp(command, "save_document") == 0){
		*argc2 = '\0';
		sscanf(current_line, "save_document %s\n", argc2);
		if(strlen(argc2) == 0){
			return SUCCESS;
		}
		save_document(doc, argc2);
	} else if(strcmp(command, "add_line_after") == 0){
		*argc2 = '\0', argi1 = -1, argi2 = -1;
		sscanf(current_line, "add_line_after %d %d *%[^\n]s\n", 
				&argi1, &argi2, argc2);
		if(strlen(argc2) == 0 || argi1 == -1 || argi2 == -1){
			/* this actually means something is missing so we 
			* need to error
			*/
			return SUCCESS;
		}
		add_line_after(doc, argi1, argi2, argc2);
	} else if(strcmp(command, "add_paragraph_after") == 0){
		argi1 = -1;
		sscanf(current_line, "add_paragraph_after %d\n", &argi1);
		if(argi1 == -1){
			return SUCCESS;
		}
		add_paragraph_after(doc, argi1);
	} else if(strcmp(command, "append_line") == 0) {
		*argc2 = '\0', argi1 = -1;
		sscanf(current_line, "append_line %d *%[^\n]s\n", &argi1, argc2);
		if(strlen(argc2) == 0 || argi1 == -1) {
			return SUCCESS;
		}
		append_line(doc, argi1, argc2);
	} else if(strcmp(command, "remove_line") == 0){
		argi1 = -1, argi2 = -1;
		sscanf(current_line, "remove_line %d %d\n", 
				&argi1, &argi2);
		if(argi1 == -1 || argi2 == -1){
			return SUCCESS;
		}
		remove_line(doc, argi1, argi2);
	} else if(strcmp(command, "replace_text") == 0){
		*argc2 = '\0', *argc3 = '\0';
		sscanf(current_line, "replace_text \"%s \"%[^\"]s\"", argc2, argc3);
		if(strlen(argc2) == 0 || strlen(argc3) == 0){
			return SUCCESS;
		}
		argc2[strlen(argc2) - 1] = '\0';
		replace_text(doc, argc2, argc3);
		
	}

	return SUCCESS;
}

int file_mode( FILE* fptr ) {

	Document doc;
	char current_line[MAX_COMMAND_LINE_SIZE + 1];
	char command[100];
	int valid_command = 0, line_size;

	init_document(&doc, "main_document");

	while(fgets(current_line, MAX_STR_SIZE, fptr)) {

		line_size = strlen(current_line) - 1;
		current_line[line_size] = '\0';
		valid_command = getCommand(current_line, command);

		if(valid_command == 1){
			if (strcmp(command, "exit") == 0){
				break;
			}
			perform_command(&doc, command, current_line);
		}
		valid_command = 0;

	}
	return SUCCESS;
}

int command_mode() {
	Document doc;
	char current_line[MAX_COMMAND_LINE_SIZE + 1];
	char command[100];
	int valid_command = 0, line_size;

	init_document(&doc, "main_document");
	printf("> ");
	while(fgets(current_line, MAX_STR_SIZE, stdin)) {
		
		line_size = strlen(current_line) - 1;
		current_line[line_size] = '\0';

		valid_command = getCommand(current_line, command);

		if(valid_command == 1){
			if (strcmp(command, "exit") == 0){
				break;
			}
			if (strcmp(command, "quit") == 0){
				break;
			}
			perform_command(&doc, command, current_line);
		}
		valid_command = 0;
		printf("> ");
	}
	return SUCCESS;
}


int main(int argc, char** argv) {

	FILE* fptr;

	if (argc > 2) {
		fprintf(stderr, "Usage: user_interface\n"); 
		fprintf(stderr, "Usage: user_interface <filename>\n"); 
		exit(EX_USAGE);
	}
	if (argc == 2){
		/* file name is provided */
		fptr = fopen(argv[1], "r");
		if (fptr == NULL){
			fprintf(stderr, "%s cannot be opened.\n", argv[1]);
			exit(EX_OSERR);
		}
		file_mode(fptr);
	} else {
		/* input from cmd line */
		command_mode();
	}
}
