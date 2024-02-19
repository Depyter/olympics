#include <stdio.h>
#include <math.h>

// Create a structure that stores the scores of each athlete
// We have two arrays to store the scores of the center and outside judges
struct athlete_scorecard {
    double center_scores[10];
    double outside_scores[10];
    double combined_scores[20];
};

// We pass the array of structs, "logical" size of array and the index 
// of the element we want to remove
void remove_element (double arr[], double value, int size) {

    // lmao wa ni nagamit
    // We first look for the element we want to remove
    // After we find it we shift all the elements to the left
    // We then decrement the "logical" size of the array
    // int i;
    // for (i = 0; i < *size; i++) {
    //    if (i == index) {
    //        int j;
    //        for (j = i; j < *size - 1; j++) {
    //            scorecard[j] = scorecard[j + 1];
    //        }
    //        *size--;
    //        break;
    //    }
    // }
    int i;
    double tolerance = 0.001; 

    // Compare the absolute value of the difference of the element and the value
    // Sometimes doubles are not the same due to how floating points are stored
    for (i = 0; i < size; i++) {
        if (fabs(arr[i] - value) < tolerance) {
            arr[i] = 0;
            break;
        }
    }
}

double get_minimum(double arr[], int size) {
    double min = arr[0];
    int i;
    if (min == 0) {
        for (i = 1; i < size; i++) {
            if (arr[i] != 0) {
                min = arr[i];
                break;
            }
        }
    }
    for (i = 1; i < size; i++) {
        if (arr[i] < min && arr[i] != 0) {
            min = arr[i];
        }
    }
    return min;
}

double get_maximum(double arr[], int size) {
    double max = arr[0];
    int i;
    if (max == 0) {
        for (i = 1; i < size; i++) {
            if (arr[i] != 0) {
                max = arr[i];
                break;
            }
        }
    }
    for (i = 1; i < size; i++) {
        if (arr[i] > max && arr[i] != 0) {
            max = arr[i];
        }
    }
    return max;
}

void print_all_minimum(double arr[], int size) {
    double min = get_minimum(arr, size);
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] == min) {
            if (i >= 10) {
                printf("%d ", i - 10 + 1);
            } else {
                printf("%d ", i + 1);
            }
        }
    }
}

void print_all_maximum(double arr[], int size) {
    double max = get_maximum(arr, size);
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] == max) {
            if (i >= 10) {
                printf("%d ", i - 10 + 1);
            } else {
                printf("%d ", i + 1);
            }
        }
    }
}

void combine_scores (struct athlete_scorecard *scorecard) {
    int j;
    for (j = 0; j < 10; j++) {
        scorecard->combined_scores[j] = scorecard->center_scores[j];
    }
    for (j = 0; j < 10; j++) {
        scorecard->combined_scores[j + 10] = scorecard->outside_scores[j];
    }
}

void get_average(double arr[], int size) {
    double sum = 0.00;
    int i;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    printf("%0.2f\n", sum / 14);
}

int main() {

    // Take the desired number of athletes competing in the olympics
    int num_of_atheletes;
    scanf("%d", &num_of_atheletes);

    // We create a struct array to store the scores of each athlete
    // We use the number of the athletes to determine the size of the array
    struct athlete_scorecard athlete_scores[num_of_atheletes];
    

    // We then add each individual scores to the array
    int i;
    for (i = 0; i < num_of_atheletes; i++) {

        // We take the scores from the center judges and put it inside the "ith" struct
        // We then take the scores from the outside judges and put it inside the "ith" struct
        // We also set the "logical" size of the array to 10 for both center_scores and outside_scores
        int j;
        for (j = 0; j < 10; j++) {
            scanf("%lf", &athlete_scores[i].center_scores[j]);
        }

        for (j = 0; j < 10; j++) {
            scanf("%lf", &athlete_scores[i].outside_scores[j]);
        }
    }
    
    for (i = 0; i < num_of_atheletes; i++) {
        
        // We print the index of the lowest and highest scores of the center and outside judges
        print_all_minimum(athlete_scores[i].center_scores, 10);
        print_all_maximum(athlete_scores[i].center_scores, 10);
        printf("\n");
        print_all_minimum(athlete_scores[i].outside_scores, 10);
        print_all_maximum(athlete_scores[i].outside_scores, 10);
        printf("\n");

        // Get the index of max and min and set it to 0
        double min_judge = get_minimum(athlete_scores[i].center_scores, 10);
        double max_judge = get_maximum(athlete_scores[i].center_scores, 10);
        
        // Set that to 0
        remove_element(athlete_scores[i].center_scores, min_judge, 10);
        remove_element(athlete_scores[i].center_scores, max_judge, 10);

        min_judge = get_minimum(athlete_scores[i].outside_scores, 10);
        max_judge = get_maximum(athlete_scores[i].outside_scores, 10);

        remove_element(athlete_scores[i].outside_scores, min_judge, 10);
        remove_element(athlete_scores[i].outside_scores, max_judge, 10);

        // We then combine the scores of the center and outside judges
        combine_scores(&athlete_scores[i]);   

        print_all_minimum(athlete_scores[i].combined_scores, 20);
        print_all_maximum(athlete_scores[i].combined_scores, 20);
        printf("\n");

        min_judge = get_minimum(athlete_scores[i].combined_scores, 20);
        max_judge = get_maximum(athlete_scores[i].combined_scores, 20);

        remove_element(athlete_scores[i].combined_scores, min_judge, 20);
        remove_element(athlete_scores[i].combined_scores, max_judge, 20);

        get_average(athlete_scores[i].combined_scores, 20);
    }
     return 0;
}
