# QC: Quantum Computing Simulator library for C
![QC](https://raw.githubusercontent.com/Null-byte-00/qc/main/image/qc.png)<br>
QC is a minimalistic C library for simulating quantum circuits and algorithms<br>
## Basics
### defining qubits
defining a zero qubit:
```c
Q q = zero_qubit();
```
defining a one qubit:
```c
Q q = one_qubit();
```
defining a qubit with different probabilities
```c
Q q = new_qubit(1,1);
```
the first parameter of new_qubit function is probability of qubit being zero and the second is the probability of it being one<br>
note: new_qubit function normalizes the values so in this example both probabilities will be 1/sqrt(2) or 0.7071<br>
### defining qubit groups 
defining a group of two qubits
```c
Q q0, q1;
Q2 q_group = {q0, q1};
```
defining group of three qubits<br>
```c
Q q0,q1,q2;
Q3 q_group = {q0, q1, q2};
```
### Gates
Pauli-X gate:<br>
``` pauli_x() ``` or  ``` X() ``` <br>
Pauli-Y gate:<br>
 ``` pauli_y() ```  or  ``` Y() ``` <br>
Pauli-Z gate:<br>
 ``` pauli_z() ```  or Z()<br>
Hadamard gate:<br>
 ``` hadamard() ```  or  ``` H() ``` <br>
Phase gate:<br>
 ``` phase() ```  or  ``` P() ``` <br>
T gate:<br>
 ``` t_gate() ```  or  ``` T() ``` <br>
Controlled NOT Gate:<br>
 ``` cnot() ``` <br>
Controlled Z Gate:<br>
 ``` cz() ``` <br>
Controlled S Gate:<br>
 ``` cs() ``` <br>
Toffoli (CCNOT) Gate:<br>
 ``` ccnot() ``` <br>

### Measuring
getting probability of qubit being zero:
```
float zero_prob = zero_chance(q);
```
getting probability of qubit being one:
```
float one_prob = one_chance(q);
```
measuring the value based on probabilities
```
int result = measure(q); // always 1 or 0
```
## Example
Bell state:
```c
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
```
## Donation
If you found this useful and would like to support, you can send donations to this XMR address: 
43EfpCz23b5WPgzaw6UVnF9KsbvueFUumTuk3yMJ8acQbPPFoxgHfq6LE2qD8gNfR3j6Fzc4oGvXRCHvvfmdsYEvPtUXK2v
