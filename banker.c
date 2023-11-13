#include<iostream>
using namespace std;

const int MAX = 10; // Define a maximum value for the number of processes and resources

void calculateNeed(int need[MAX][MAX], int maxm[MAX][MAX], int allot[MAX][MAX], int P, int R) {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}

bool isSafe(int processes[], int avail[], int maxm[][MAX], int allot[][MAX], int P, int R) {
    int need[MAX][MAX];

    calculateNeed(need, maxm, allot, P, R);

    bool finish[MAX] = {0};
    int safeSeq[MAX];
    int work[MAX];

    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (found == false) {
            cout << "System is not in a safe state";
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < P; i++)
        cout << safeSeq[i] << " ";

    return true;
}

int main() {
    int P, R;

    cout << "Enter the number of processes: ";
    cin >> P;

    cout << "Enter the number of resources: ";
    cin >> R;

    int processes[MAX];
    int avail[MAX];
    int maxm[MAX][MAX];
    int allot[MAX][MAX];

    cout << "Enter the processes: ";
    for (int i = 0; i < P; i++)
        cin >> processes[i];

    cout << "Enter the available resources: ";
    for (int i = 0; i < R; i++)
        cin >> avail[i];

    cout << "Enter the maximum resources that can be allocated:\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> maxm[i][j];

    cout << "Enter the resources currently allocated to processes:\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> allot[i][j];

    isSafe(processes, avail, maxm, allot, P, R);

    return 0;
}
