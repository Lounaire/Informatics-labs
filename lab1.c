#include <stdio.h>
#include <limits.h>

int Sum_of_two_largest(int matrix[][100], int rows, int cols, int i, int j){
    int max_first = 0, max_second = 0;
    int elements[10000];
    int count = 0;
    
    // Add the element itself
    elements[count++] = matrix[i][j];

    // Down-right staircase
    int r = i, c = j;
    while(1){
        // Move down if possible
        if(r + 1 < rows){
           r++;
            elements[count++] = matrix[r][c];
        } else {
            break;
        }
        
        // Move right if possible
        if(c + 1 < cols){
            c++;
            elements[count++] = matrix[r][c];
        } else {
            break;
        }
    }

    
    // Up-right staircase (starting from the original element again)

    r = i; c = j;
    while (1)
    {
        // Move up if possible
        if(r - 1 >= 0){
            r--;
            elements[count++] = matrix[r][c];
        } else {
            break;
        }

        // Move right if possible
        if(c + 1 < cols){
            c++;
            elements[count++] = matrix[r][c];
        } else {
            break;
        }
    }
    

    int largest = INT_MIN;
    int secondLargest = INT_MIN;

    for(int k = 0; k < count; k++){
        if(elements[k] > largest){
            secondLargest = largest;
            largest = elements[k];
        }
        else if(elements[k] > secondLargest && elements[k] != largest){
            secondLargest = elements[k];
        }
    }

    if(secondLargest == INT_MIN){
        secondLargest = largest;
    }

    return largest + secondLargest;
}



int main(){
    int matrix[100][100];
    int rows, cols;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nOriginal Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    int result[100][100]; // Declare the result matrix
    
    // Calculate the result matrix
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result[i][j] = Sum_of_two_largest(matrix, rows, cols, i, j);
        }
    }

    // Print the result matrix
    printf("\nResult Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}