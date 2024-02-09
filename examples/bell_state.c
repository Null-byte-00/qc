#include<stdio.h>
#include "qc.h"

int main() {
    Q q0 = one_qubit();
    Q q1 = zero_qubit();
    q0 = H(q0);
    Q2 q_group = cnot(q0, q1);
    q0 = q_group.first;
    q1 = q_group.second;

    printf("Q0:\n");
    printf("Zero Probability: %lf \n",  zero_chance(q0)); // 0.5
    printf("One Probability: %lf \n",  one_chance(q0)); // 0.5
    printf("Measured: %d\n", measure(q0));
    printf("Q1:\n");
    printf("Zero Probability: %lf \n", zero_chance(q1)); // 0.5
    printf("One Probability: %lf \n", one_chance(q1)); // 0.5
    printf("Measured: %d\n", measure(q1));
}