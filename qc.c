/* 
QC v0.1.0
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
*/
#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>
#include<time.h>
#include "qc.h"


Q normalize(Q q) {
    /* normalizing qubit values */
    cfloat magnitude = csqrt(cpow(q.zero,2) + cpow(q.one, 2));
    q.zero = q.zero / magnitude;
    q.one = q.one / magnitude;
    return q;
}


Q new_qubit(cfloat zero, cfloat one) {
    /* creating new qubit and normalizing values */
    Q q = {zero, one};
    return normalize(q);
}


Q zero_qubit() {
    Q q = {1.0f, 0.0f};
    return q;
}


Q one_qubit() {
    Q q = {0.0f, 1.0f};
    return q;
}


Q multiply_2_matrix(Q q, M2 matrix) {
    /* multiplying two 2x2 matrices */
    cfloat q_vector[2] = {q.zero, q.one};
    cfloat new_vector[2] = {0,0};
    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j < 2; j ++) {
            new_vector[i] += q_vector[j] * matrix.m[i][j];
        }
    }
    q.zero = new_vector[0];
    q.one = new_vector[1];
    return q;
}


void matrix_2_cp(M2 *output, cfloat input[2][2]) {
    /* copying values of 2x2 matrices */
    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j < 2; j ++) {
            output->m[i][j] = input[i][j];
        }
    }
}


void matrix_4_cp(M4 *output, cfloat input[4][4]) {
    /* copying values of 4x4 matrices */
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            output->m[i][j] = input[i][j];
        }
    }
}


void matrix_8_cp(M8 *output, cfloat input[8][8]) {
    /* copying values of 8x8 matrices */
    for (int i = 0; i < 8; i ++) {
        for (int j = 0; j < 8; j ++) {
            output->m[i][j] = input[i][j];
        }
    }
}


S2 state_from_2_qubit(Q q1, Q q2) {
    /* getting state vector of 2 qubits */
    S2 state;
    state.m[0] = q1.zero * q2.zero;
    state.m[1] = q1.zero * q2.one;
    state.m[2] = q1.one * q2.zero;
    state.m[3] = q1.one * q2.one;
    return state;
}


S3 state_from_3_qubit(Q q1, Q q2, Q q3) {
    /* getting state vector of 2 qubits */
    S3 state;
    state.m[0] = q1.zero * q2.zero * q3.zero;
    state.m[1] = q1.zero * q2.zero * q3.one;
    state.m[2] = q1.zero * q2.one * q3.zero;
    state.m[3] = q1.zero * q2.one * q3.one;
    state.m[4] = q1.one * q2.zero * q3.zero;
    state.m[5] = q1.one * q2.zero * q3.one;
    state.m[6] = q1.one * q2.one * q3.zero;
    state.m[7] = q1.one * q2.one * q3.one;
    return state;
}


Q2 qubit_2_from_state(S2 state) {
    /* getting 2 qubits from state vector */
    Q q1, q2;
    q1.zero = state.m[0] + state.m[1];
    q1.one = state.m[2] + state.m[3];
    q2.zero = state.m[0] + state.m[2];
    q2.one = state.m[1] + state.m[3];
    q1 = normalize(q1);
    q2 = normalize(q2);
    Q2 q_group = {q1, q2};
    return q_group;
}


Q3 qubit_3_from_state(S3 state) {
    /* getting 2 qubits from state vector */
    Q q1, q2, q3;
    q1.zero = state.m[0] + state.m[2] + state.m[4] + state.m[6];
    q1.one = state.m[1] + state.m[3] + state.m[5] + state.m[7];
    q2.zero = state.m[0] + state.m[1] + state.m[4] + state.m[5];
    q2.one = state.m[2] + state.m[3] + state.m[6] + state.m[7];
    q3.zero = state.m[0] + state.m[1] + state.m[2] + state.m[3];
    q3.one = state.m[4] + state.m[5] + state.m[6] + state.m[7];
    q1 = normalize(q1);
    q2 = normalize(q2);
    q3 = normalize(q3);
    Q3 q_group = {q3, q2, q1};
    return q_group;
}


Q2 multiply_4_matrix(Q q1, Q q2, M4 matrix) {
    /* multiply 4x4 matrix and state vector */
    S2 state = state_from_2_qubit(q1, q2);

    cfloat new_vector[] = {0.0,0.0,0.0,0.0};
    for (int i = 0; i < 4; i ++) {
        for (int j =0; j < 4; j ++) {
            new_vector[i] += state.m[j] * matrix.m[i][j];
        }
    }
    
    S2 new_state;
    for (int i = 0; i < 4; i ++) {
        new_state.m[i] = new_vector[i];
    }

    Q2 qubit_group = qubit_2_from_state(new_state);
    return qubit_group;
}


Q3 multiply_8_matrix(Q q1, Q q2, Q q3, M8 matrix) {
    /* multiply 8x8 matrix and state vector */
    S3 state = state_from_3_qubit(q1, q2, q3);

    cfloat new_vector[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < 8; i ++) {
        for (int j =0; j < 8; j ++) {
            new_vector[i] += state.m[j] * matrix.m[i][j];
        }
    }
    
    S3 new_state;
    for (int i = 0; i < 8; i ++) {
        new_state.m[i] = new_vector[i];
    }

    Q3 qubit_group = qubit_3_from_state(new_state);
    return qubit_group;
}


/* Gates */

Q pauli_x(Q q) {
    /* Pauli-X gate */
    M2 matrix;
    cfloat gate_matrix[2][2] = {{0,1}, {1,0}};
    matrix_2_cp(&matrix, gate_matrix);
    return multiply_2_matrix(q, matrix);
}


Q pauli_y(Q q) {
    /* Pauli-Y gate */
    M2 matrix;
    cfloat gate_matrix[2][2] = {{0,-1 * _Complex_I}, {_Complex_I,0}};
    matrix_2_cp(&matrix, gate_matrix);
    return multiply_2_matrix(q, matrix);
}


Q pauli_z(Q q) {
    /* Pauli-Z gate */
    M2 matrix;
    cfloat gate_matrix[2][2] = {{1,0}, {0,-1}};
    matrix_2_cp(&matrix, gate_matrix);
    return multiply_2_matrix(q, matrix);
}


Q hadamard(Q q) {
    /* hadamard gate */
    M2 matrix;
    cfloat gate_matrix[2][2] = {{1,1}, {1,-1}};  // {{1*sqrt(2),1*sqrt(2)}, {1*sqrt(2),-1*sqrt(2)}};
    matrix_2_cp(&matrix, gate_matrix);
    return multiply_2_matrix(q, matrix);
}


Q phase(Q q) {
    /* Phase gate */
    M2 matrix;
    cfloat gate_matrix[2][2] = {{1,0}, {0,_Complex_I}};
    matrix_2_cp(&matrix, gate_matrix);
    return multiply_2_matrix(q, matrix);
}


Q t_gate(Q q) {
    /* T gate */
    M2 matrix;
    cfloat gate_matrix[2][2] = {{1,0}, {0,cexp((_Complex_I * M_PI)/4)}};
    matrix_2_cp(&matrix, gate_matrix);
    return multiply_2_matrix(q, matrix);
}


Q2 cnot(Q control, Q target) {
    /* Controlled Not Gate */
    M4 matrix;
    cfloat gate_matrix[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,0,1}, 
        {0,0,1,0}
    };
    matrix_4_cp(&matrix, gate_matrix);
    return multiply_4_matrix(control, target, matrix);
}


Q2 cz(Q control, Q target) {
    /* Controlled Z Gate */
    M4 matrix;
    cfloat gate_matrix[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0}, 
        {0,0,0,-1}
    };
    matrix_4_cp(&matrix, gate_matrix);
    return multiply_4_matrix(control, target, matrix);
}


Q2 cs(Q control, Q target) {
    /* Controlled S Gate */
    M4 matrix;
    cfloat gate_matrix[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0}, 
        {0,0,0,_Complex_I}
    };
    matrix_4_cp(&matrix, gate_matrix);
    return multiply_4_matrix(control, target, matrix);
}



Q2 swap(Q control, Q target) {
    /* 
    Swap Gate 
    this one is kinda useless but i wrote it anyways
    */
    M4 matrix;
    cfloat gate_matrix[4][4] = {
        {1,0,0,0},
        {0,0,1,0},
        {0,1,0,0}, 
        {0,0,0,1}
    };
    matrix_4_cp(&matrix, gate_matrix);
    return multiply_4_matrix(control, target, matrix);
}


Q3 ccnot(Q q1, Q q2, Q q3) {
    /* 
    Toffoli gate
    */
    M8 matrix;
    cfloat gate_matrix[8][8] = {
        {1,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0}, 
        {0,0,0,1,0,0,0,0},
        {0,0,0,0,1,0,0,0},
        {0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1,0}
    };
    matrix_8_cp(&matrix, gate_matrix);
    return multiply_8_matrix(q1, q2, q3, matrix);
}


/* Gate shortcuts */

Q X(Q q) { 
    return pauli_x(q);
}

Q Y(Q q) {
    return pauli_y(q);
}

Q Z(Q q) {
    return pauli_z(q);
}

Q H(Q q) {
    return hadamard(q);
}

Q P(Q q) {
    return phase(q);
}

Q T(Q q) {
    return t_gate(q);
}


/* measurement */

float zero_chance(Q q) {
    /* Display probabilities in percentage */
    q = normalize(q);
    return cabsf(cpow(q.zero, 2));
}


float one_chance(Q q) {
    /* Display probabilities in percentage */
    q = normalize(q);
    return cabsf(cpow(q.one, 2));
}


int measure(Q q) {
    /* Measuring value based on probabilities */
    q = normalize(q);
    
    time_t t1;
    srand ( (unsigned) time (&t1));
    
    float random = rand() % 100 + 1;
    float frandom = random / 100;
    float zero_prob = zero_chance(q);
    if (zero_prob > frandom) {
        return 0;
    }
    return 1;
}
