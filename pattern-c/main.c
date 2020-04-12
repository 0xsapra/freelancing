#include<stdio.h>

void drawRectangle(char character, int width, int length){

	int i,j;
	if (width == 0 || length == 0){
		printf("Invalid data provided.\n");
		return;
	}

	if(character == '*' || character ==  '%' || character =='#'){
		for(i=0; i<width; i++){
			for(j=0; j<length; j++){
				printf("%c", character);
			}
		printf("\n");
		}	
	}else{
		printf("Invalid data provided.\n");
	}

	
}

void drawTraingle(char character, int rows){

	int i,j,k;
	if(rows == 0){
		printf("Invalid data provided.\n");
		return;
	}

	if(character == '*' || character ==  '%' || character =='#'){
		for (i=1; i<=rows; ++i) {
			k = 0;
	        for (j=1; j<=rows-i; ++j){ 
	        	printf(" "); 
	        }
	        while (k!=2*i-1) {
	            printf("%c",character);
	            ++k;
	        }
	        printf("\n");
	    }   	
	}else{
		printf("Invalid data provided.\n");
	}
	
}

void drawShape(char character, int rows){

	int i,j;
	if(rows == 0){
		printf("Invalid data provided.\n");
		return;
	}
	if(character == '*' || character ==  '%' || character =='#'){
		for (i=1; i<=rows; ++i) {
        	for (j=1; j<=i; ++j){ 
        		printf("* "); 
        	}
        printf("\n");
    	}
	}else{
		printf("Invalid data provided.\n");
	}
	
}

int main(){

	int exitCondition;
	int userInput;
	char character;
	int width, length, size;

	exitCondition = 0;

	while(!exitCondition){
			
		printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
		scanf("%d", &userInput);
		switch (userInput){
			case 0:
				exitCondition = 1;
				break;
			case 1:
				printf("Enter character, width and length: ");
				scanf("\n%c %d %d",&character, &width, &length);
				drawRectangle(character, width, length);
				break;
			case 2:
				printf("Enter character and size: ");
				scanf("\n%c %d", &character, &size);
				drawTraingle(character,size);
				break;
			case 3:
				printf("Enter character and size: ");
				scanf("\n%c %d", &character, &size);
				drawShape(character,size);
				break;
			default:
				printf("Invalid choice.\n");
				break;
		}

		if(exitCondition == 1){
			break;
		}
	}
	printf("Bye Bye\n");


	return 0;
}