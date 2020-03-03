#include <iostream>
#include <String>
#include <Map>
#include <vector>
#include <queue>

using namespace std;

const int N = 5;

typedef vector<int> prefList;
typedef map<int, prefList> prefMap;
typedef map<int, int> pairs;

bool prefers(prefList &prefer, int man, int partner)
{
    for (auto i : prefer)
    {
        if (i == man)
            return true;
        if (i == partner)
            return false;
    }
    return false;
}

void GS(queue<int> freemen, pairs &couples, prefMap mPref, prefMap wPref)
{
    while (!freemen.empty())
    {
        int currman = freemen.front();
        prefList manpref = mPref[currman];
        for (auto i = manpref.begin(); i != manpref.end(); i++)
        {
            int currpref = *i;
            if(couples.find(currpref) == couples.end())
            {
                couples.insert(pair<int,int>(currpref,currman));
                break;
            }

            int partner = couples[currpref];

            if(prefers(wPref[currpref], currman, partner))
            {
                freemen.push(partner);
                couples[currpref] = currman;
                break;
            }
        }
        freemen.pop();
    }
}

int main()
{
    string M[]{"Victor", "Wyatt", "Xavier", "Yancy", "Zeus"};
    string W[]{"Amy", "Bertha", "Claire", "Diane", "Erika"};

    prefMap men_pref, women_pref;
    queue<int> freemen;

    int menPref[N][N + 1] = {
        {0, 1, 0, 3, 4, 2},
        {1, 3, 1, 0, 2, 4},
        {2, 1, 4, 2, 3, 0},
        {3, 0, 3, 2, 1, 4},
        {4, 1, 3, 0, 4, 2}};

    int womenPref[N][N + 1]{
        {0, 4, 0, 1, 3, 2},
        {1, 2, 1, 3, 0, 4},
        {2, 1, 2, 3, 4, 0},
        {3, 0, 4, 3, 2, 1},
        {4, 3, 1, 4, 2, 0}};

    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {
            men_pref[menPref[i][0]].push_back(menPref[i][j]);
            women_pref[menPref[i][0]].push_back(womenPref[i][j]);
        }
        freemen.push(menPref[i][0]);
    }

    for (int i = 0; i < 5; i++)
    {
        cout << M[i] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << W[menPref[i][j]] << " | ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (int i = 0; i < 5; i++)
    {
        cout << W[i] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << M[womenPref[i][j]] << " | ";
        }
        cout << "\n";
    }

    pairs couples;

    GS(freemen, couples, men_pref, women_pref);

    cout << "Final Pairs :\n";
    for(auto couple : couples)
    {
        cout << M[couple.second] << " >< " << W[couple.first] << "\n";
    }
}