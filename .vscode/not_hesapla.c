#include <stdio.h>
int main() {
    int i, midterm_count, has_homework;
    float midterm_weight, homework_weight;
    float midterm_grade, midterm_total_grade = 0;
    float homework_grade, homework_total_score;
    float final_grade, makeup_grade;
    float average;

    printf("How many midterm exams do you have: ");
    scanf("%d", &midterm_count);

    printf("What is the total weight of midterms (e.g., 40 for 40%%): ");
    scanf("%f", &midterm_weight);
    midterm_weight /= 100.0; 

    if (midterm_count == 1) {
        printf("Enter midterm grade: ");
        scanf("%f", &midterm_grade);
        midterm_total_grade = midterm_grade * midterm_weight;
    }
    else {
        for (i = 0; i < midterm_count; i++) {
            printf("Enter %d. midterm grade: ", i + 1);
            scanf("%f", &midterm_grade);
            midterm_total_grade += midterm_grade * (midterm_weight / midterm_count);
        }
    }

    printf("Do you have homework? (1 for Yes, 0 for No): ");
    scanf("%d", &has_homework);

    while (has_homework != 0 && has_homework != 1) {
        printf("Please enter a valid number (1 or 0): ");
        scanf("%d", &has_homework);
    }
    if (has_homework == 1) {
        printf("Enter homework grade: ");
        scanf("%f", &homework_grade);
        printf("What is the weight of homework (e.g., 15 for 15%%): ");
        scanf("%f", &homework_weight);
        homework_weight /=100;
    }
    else {
        homework_weight = 0.0;
    }
    homework_total_score = homework_grade * homework_weight;

    printf("Enter final exam grade: ");
    scanf("%f", &final_grade);

    if (final_grade < 40) {
        printf("Enter makeup exam grade: ");
        scanf("%f", &makeup_grade);
        final_grade = makeup_grade;
    }

    average = homework_total_score + midterm_total_grade + (final_grade * (1.0 - midterm_weight - homework_weight));

    printf("Your final grade is: %.2f", average);

    return 0;
}