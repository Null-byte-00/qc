/* 
QC v0.1.0
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
*/
#ifndef _QC_H_
#define _QC_H_
#include<complex.h>

typedef float _Complex cfloat;

struct Qubit {
    cfloat zero;
    cfloat one;
};

typedef struct Qubit Q;


struct Double_Qubit {
    Q first;
    Q second;
};

typedef struct Double_Qubit Q2;


struct Triple_Qubit {
    Q first;
    Q second;
    Q third;
};

typedef struct Triple_Qubit Q3;


struct Matrix_2 {
    cfloat m[2][2];
};

typedef struct Matrix_2 M2;


struct Matrix_4 {
    cfloat m[4][4];
};

typedef struct Matrix_4 M4;


struct Matrix_8 {
    cfloat m[8][8];
};

typedef struct Matrix_8 M8;


struct State_Vector_2 {
    /* state vector for 2 qubits */
    cfloat m[4];
};

typedef struct State_Vector_2 S2;


struct State_Vector_3 {
    cfloat m[8];
};

typedef struct State_Vector_3 S3;

extern Q normalize(Q q);

extern Q zero_qubit();

extern Q one_qubit();

extern Q new_qubit(cfloat zero, cfloat one);

extern Q pauli_x(Q q);

extern Q pauli_y(Q q);

extern Q pauli_z(Q q);

extern Q hadamard(Q q);

extern Q phase(Q q);

extern Q t_gate(Q q);

extern Q2 cnot(Q control, Q target);

extern Q2 cz(Q control, Q target);

extern Q2 cs(Q control, Q target);

extern Q3 ccnot(Q control1, Q control2, Q target);

extern Q X(Q q);

extern Q Y(Q q);

extern Q Z(Q q);

extern Q H(Q q);

extern Q P(Q q);

extern Q T(Q q);

extern float one_chance(Q q);

extern int measure(Q q);

extern float zero_chance(Q q);

extern float one_chance(Q q);

#endif
