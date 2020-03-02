#include <iostream>
#include <String>
#include <vector>

using namespace std;

const int N = 5;

void GS(int A[N][N], int B[N][N], int i)
{

}

int main()
{
    string M[]{"Victor", "Wyatt", "Xavier", "Yancy", "Zeus"};
    string W[]{"Amy", "Bertha", "Claire", "Diane", "Erika"};

    int menPref[N][N]{{1, 0, 3, 4, 2}, {3, 1, 0, 2, 4}, {1, 4, 2, 3, 0}, {0, 3, 2, 1, 4}, {1, 3, 0, 4, 2}};

    int womenPref[N][N]{{4, 0, 1, 3, 2}, {2, 1, 3, 0, 4}, {1, 2, 3, 4, 0}, {0, 4, 3, 2, 1}, {3, 1, 4, 2, 0}};

    for (int i = 0; i < 5; i++)
    {
        cout << M[i] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << W[menPref[i][j]] << " | ";
        }
        cout << "\n";
    }

    cout << "\n\n";

    for (int i = 0; i < 5; i++)
    {
        cout << W[i] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << M[womenPref[i][j]] << " | ";
        }
        cout << "\n";
    }
}