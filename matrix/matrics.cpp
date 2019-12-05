#include <iostream>

using namespace std;

void input_3_3_matrix(float matrix[3][3]){
	// helper function to help taking 3 X 3 matrix input
	for(int i=0; i<=2; i++){
		cin >> matrix[i][0] >> matrix[i][1] >> matrix[i][2] ;
	}
	return;
}

void menu(){
	// print menu
	cout << "Welcome to matrix menu\n";
	cout << "-----------------------\n";
	cout << "Please select an option\n";
	cout << "1) Set Identity\n";
	cout << "2) Display matrix\n";
	cout << "3) Add Matrix\n";
	cout << "4) Subtract Matrix\n";
	cout << "5) Multiply Matrix\n";
	cout << "6) Copy Matrix\n";
	cout << "7) Exit\n";

}

void displaMatrix(float matrix[3][3]) {
	// display content of 3X3 matrix passed
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			cout << "\t" << matrix[j][i];
			cout << "\t" << " ";
		}
		cout << "\n";
	}
}

void addMatrix(float matrix_result[3][3], float matrix_a[3][3], float matrix_b[3][3]) {
	// addition of 2 matrix and storing result in matrix_result
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			matrix_result[j][i] = matrix_a[j][i] + matrix_b[j][i] ;
		}
	}
	cout << "Matrix after additions :\n";
	displaMatrix(matrix_result);
	return;
}

void subMatrix(float matrix_result[3][3], float matrix_a[3][3], float matrix_b[3][3]) {
	// subtraction of 2 matrix and storing result in matrix_result

	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			matrix_result[j][i] = matrix_a[j][i] - matrix_b[j][i] ;
		}
	}
	cout << "Matrix after additions :\n";
	displaMatrix(matrix_result);
	return;
}

void mulMatrix(float matrix_result[3][3], float matrix_a[3][3], float matrix_b[3][3]) {
	// Multiplication of 2 matrix and storing result in matrix_result

	for(int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			int sum = 0;
			for (int k = 0; k <=2; k++){
				sum = sum + matrix_a[i][k] * matrix_b[k][j];
				matrix_result[i][j] = sum ;
			}
		}
	}
	cout << "Matrix after Multiplication :\n";

	displaMatrix(matrix_result);
}

void setMatrixIdentity(float matrix[3][3]){
	// Set a matrix to identity matrix

	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			matrix[j][i] = 0;
		}
		matrix[j][j] = 1;
	}
	cout << "3 * 3 Identity matrix \n";
	displaMatrix(matrix);
}

void copyMatrix(float matrix_result[3][3], float matrix_a[3][3]){
	// copy data from 1 matrix to other

	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			matrix_result[j][i] = matrix_a[j][i];
		}
	}
	cout << "This matrix is copied to other matrix :\n";

	displaMatrix(matrix_result);
}


int main(int argc, char** argv){

	const int ROW = 3;
	const int COL = 3;
	int menu_response;
	float matrix_result[ROW][COL], 
        matrix_a[ROW][COL],
        matrix_b[ROW][COL]; ;

	while(1) {
		menu();
		cin >> menu_response;

		if (menu_response == 1){
			setMatrixIdentity(matrix_result);
		} else if(menu_response == 2){
			cout << "Enter values of 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_result);
			displaMatrix(matrix_result);
		} else if(menu_response == 3){
			// Add matrix
			cout << "Enter values of 1st 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_a);
			cout << "Enter values of 2nd 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_b);

			addMatrix(matrix_result, matrix_a, matrix_b);
		} else if(menu_response == 4){

			cout << "Enter values of 1st 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_a);
			cout << "Enter values of 2nd 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_b);

			subMatrix(matrix_result, matrix_a, matrix_b);
		} else if(menu_response == 5){
			cout << "Enter values of 1st 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_a);
			cout << "Enter values of 2nd 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_b);

			mulMatrix(matrix_result, matrix_a, matrix_b);
		} else if(menu_response == 6){
			cout << "Enter values of 3*3 matrix" << endl ;
			input_3_3_matrix(matrix_a);
			copyMatrix(matrix_result, matrix_a);
		} else if(menu_response == 7){
			cout << "Bye bye..\n";
		} else {
			cout << "Invalid Input\n";
		}
	}

	return 0;
}
