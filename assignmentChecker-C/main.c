// gcc main.c -lm && ./a.out  < public01.txt   | diff public01-out.txt -
// gcc main.c -lm && ./a.out  < public02-in.txt   | diff public02-out.txt -
// gcc main.c -lm && ./a.out  < public03-in.txt   | diff public03-out.txt -
// gcc main.c -lm && ./a.out  < public04-in.txt   | diff public04-out.txt -

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NA 50
#define MAX(X, Y) ((X > Y) ? X : Y)

struct assignment_struct{
    int number;
    int score;
    int weight;
    int late_days;
    int value;
    int adjusted_weight;
    int real_score;
    int active;
};

/* return the square of double number */
double square(double num){
    return num * num;
}

/* Take user input required to create new assignment from user from stdin */
struct assignment_struct *inputAssignment(){

    struct assignment_struct *assignment = (struct assignment_struct *)
	malloc(sizeof(struct assignment_struct));
    scanf("%d,%d,%d,%d",
          &assignment->number,
          &assignment->score,
          &assignment->weight,
          &assignment->late_days);
    assignment->active = 1; /* active will be 0 for dropped assignments*/
    assignment->value = assignment->score * assignment->weight;
    return assignment;
}

/* Swap 2 values from assignments array */
void swap(struct assignment_struct **assignments, int i, int j){
    struct assignment_struct *assignment = assignments[i];
    assignments[i] = assignments[j];
    assignments[j] = assignment;
    return;
}

/* bubble sort assignments array on bases of serial number */
void sort_assignment(struct assignment_struct **assignments, int na){
    int i, j;

    for (i = 0; i < na; i++){
        for (j = i; j < na; j++){
            if (assignments[i]->number > assignments[j]->number){
                swap(assignments, i, j);
            }
        }
    }
}

/* 
Print assignment, i.e number, score, weight and lateday
from assignments array .
*/
void print_assignments(struct assignment_struct **assignments, int na){

    int i;

    for (i = 0; i < na; i++){
        printf("%d, %d, %d, %d\n",
            assignments[i]->number,
            assignments[i]->score,
            assignments[i]->weight,
            assignments[i]->late_days);
    }
    return;
}

/* 
print stats, i.e mean and Standard deviation for each 
assignment in assignemts array 
*/
void print_stats(struct assignment_struct **assignments, int na){
    int i, sum = 0;
    double mean = 0, sd = 0;

    for (i = 0; i < na; i++){
        sum += assignments[i]->real_score;
    }
    mean = sum / na;
    for (i = 0; i < na; i++){
        sd += square(assignments[i]->real_score - mean);
    }
    sd = sqrt(sd / na);
    printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, sd);
    return;
}

/* 
Drop lowest valued assignments from assignment array on bases
of there assignment score(i.e score * weight). 
After dropping nd amount of assignements, the total weight is 
also unbalanced. So also re balance weights among left over 
assignments.
*/
void drop_and_adjust_assignments(struct assignment_struct **assignments,
                                 int na, 
                                 int nd){

    /* find nd'th least values from assignments and set is active=0
	thn do adjustment */
    int i, j, curr_min = 10000, prev_min = 0, adjust_weight = 0, 
    	adjust_count = na;
    float adjusted_precision;

    /* drop un required weights */
    for (i = 0; i < nd; i++){
        for (j = 0; j < na; j++){
            if (assignments[j]->value < curr_min &&
                assignments[j]->value > prev_min){
                curr_min = assignments[j]->value;
            }
        }
        for (j = 0; j < na; j++){
            if (assignments[j]->value == curr_min){
                assignments[j]->active = 0;
                adjust_count--;
                adjust_weight += assignments[j]->weight;
                /* This is nth lowest value and we wanna drop it */
            }
        }
        prev_min = curr_min;
        curr_min = 10000;
    }
    /* adjust weights */
    adjusted_precision = adjust_weight / adjust_count;
    for (i = 0; i < na; i++){
        if (assignments[i]->active){
            assignments[i]->adjusted_weight = assignments[i]->weight +
                                              adjusted_precision;
        }
    }
    return;
}

int main(){

    int penalty_per_day, nd, na, weight_total = 0, isActive, score, late, i;
    char stats; /* Y/N , i.e should we generate stats or not*/
    float numeric_score = 0;
    struct assignment_struct *assignments[MAX_NA]; /* array of assignment*/

    scanf("%d %d %c", &penalty_per_day, &nd, &stats);
    scanf("%d", &na);

    if (na > MAX_NA){
        printf("Maximum assignments is 50\n");
        return 1;
    }
    for (i = 0; i < na; i++){
        assignments[i] = inputAssignment();
        score = assignments[i]->score;
        late = assignments[i]->late_days;
        assignments[i]->real_score = MAX(score - (late * penalty_per_day), 0);
        weight_total += assignments[i]->weight;
    }

    if (weight_total != 100){
        printf("ERROR: Invalid values provided\n");
        return 1;
    }

    sort_assignment(assignments, na);

    /* drop and adjust assignments*/
    drop_and_adjust_assignments(assignments, na, nd);
    /* calculate numeric score*/
    for (i = 0; i < na; i++){
        isActive = assignments[i]->active;
        if (isActive == 1){
            int real_score = assignments[i]->real_score;
            int weight = assignments[i]->adjusted_weight;
            numeric_score += ((float)(real_score * weight) / 100);
        }
    }
    /* print stuff*/
    printf("Numeric Score: %5.4f\n", numeric_score);
    printf("Points Penalty Per Day Late: %d\n", penalty_per_day);
    printf("Number of Assignments Dropped: %d\n", nd);
    printf("Values Provided:\n");
    printf("Assignment, Score, Weight, Days Late\n");
    print_assignments(assignments, na);
    /* print stats*/
    if (stats == 'Y' || stats == 'y'){
        print_stats(assignments, na);
    }
    return 0;
}