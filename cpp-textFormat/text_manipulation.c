#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

int is_space(char character){
    if(character == ' ' || character == '\t' || character == '\n'){
        return 1;
    } else {
        return 0;
    }
}

int remove_spaces(const char *source, char *result, int *num_spaces_removed){
    int i, j, curr_index = 0, source_length, prev_num_spaces = *num_spaces_removed;

    if(source == NULL){
        result[0] = '\0';
        return FAILURE;
    }
    source_length = strlen(source);
    if(source_length == 0){
        result[0] = '\0';
        return FAILURE;
    }
    *num_spaces_removed = 0;
    for(i = 0; i < source_length; i++){
        if(is_space(source[i])){
            *num_spaces_removed = *num_spaces_removed + 1;
        } else {
            break;
        }        
    }
    for(j = 0; source[i] != '\0'; i++){
        if(source[i] == ' '){
            curr_index = i;
            while(is_space(source[curr_index]))curr_index++;
            if(source[curr_index] == '\0'){
                *num_spaces_removed = *num_spaces_removed + ( source_length - i  );
                break;        
            }
        }
        result[j++]=source[i];
    }
    result[j]='\0';

    if(*num_spaces_removed == 0){
        *num_spaces_removed = prev_num_spaces;
    }

    return SUCCESS;
}



int add_characters(char *result, int size, int curr_index, char character){
    int i;

    for (i = 0; i < size; i++){
        result[curr_index++] = character;
    }
    return 0;
}

int center(const char *source, int width, char *result){

    int source_length, spaces, i;

    if (source == NULL) {
        result[0] = '\0';
        return FAILURE;
    }
    source_length = strlen(source);
    if (source_length == 0){
        result[0] = '\0';
        return FAILURE;
    }
    if (width < source_length){
        result[0] = '\0';
        return FAILURE;
    }

    spaces = (width - source_length) / 2;
    if( spaces < 0 ){
        result[0] = '\0';
        spaces = 0;
    }
    add_characters(result, spaces, 0, ' ');
    for (i = 0; i <= source_length; i++){
        result[spaces + i] = source[i];
    }
    add_characters(result, spaces, spaces + i - 1, ' ');
    result[2 * spaces + i - 1] = '\0';


    return SUCCESS;
}