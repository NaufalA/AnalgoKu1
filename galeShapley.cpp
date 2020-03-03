#include <iostream>
#include <String>
#include <Map>
#include <vector>
#include <queue>

using namespace std;

typedef vector<string> prefList;
typedef map<string, prefList> prefMap;
typedef map<string, string> pairs;

bool prefers(prefList &prefer, string man, string partner)
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

pairs GS(queue<string> freemen, prefMap mPref, prefMap wPref)
{
    pairs couples;
    while (!freemen.empty())
    {
        string currman = freemen.front();
        prefList manpref = mPref[currman];
        cout << "freeman " << currman << " arrived\n";
        for (auto i = manpref.begin(); i != manpref.end(); i++)
        {
            string currpref = *i;
            cout << currman << " proposed to " << currpref << "\n";
            if (couples.find(currpref) == couples.end())
            {
                cout << currpref << " accepted " << currman << "\n";
                couples.insert(pair<string, string>(currpref, currman));
                break;
            }

            string partner = couples[currpref];
            cout << "turns out " << currpref << " already with " << partner << "\n";

            if (prefers(wPref[currpref], currman, partner))
            {
                cout << currpref << " left " << partner << " for " << currman << "\n";
                freemen.push(partner);
                couples[currpref] = currman;
                break;
            }
            else
            {
                cout << currman << " was rejected\n";
            }
        }
        freemen.pop();
    }
    return couples;
}

int main()
{
    const int N = 5;

    prefMap men_pref, women_pref;
    queue<string> freemen;

    string menPref[N][N + 1] = {
        {"Victor", "Bertha", "Amy", "Diane", "Erika", "Claire"},
        {"Wyatt", "Diane", "Bertha", "Amy", "Claire", "Erika"},
        {"Xavier", "Bertha", "Erika", "Claire", "Diane", "Amy"},
        {"Yancy", "Amy", "Diane", "Claire", "Bertha", "Erika"},
        {"Zeus", "Bertha", "Diane", "Amy", "Erika", "Claire"}};

    string womenPref[N][N + 1]{
        {"Amy", "Zeus", "Victor", "Wyatt", "Yancy", "Xavier"},
        {"Wyatt", "Xavier", "Wyatt", "Yancy", "Victor", "Zeus"},
        {"Claire", "Wyatt", "Xavier", "Yancy", "Zeus", "Victor"},
        {"Diane", "Victor", "Zeus", "Yancy", "Xavier", "Wyatt"},
        {"Erika", "Yancy", "Wyatt", "Zeus", "Xavier", "Victor"}};

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
        cout << menPref[i][0] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << menPref[i][j] << " | ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (int i = 0; i < 5; i++)
    {
        cout << womenPref[0][i] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << womenPref[i][j] << " | ";
        }
        cout << "\n";
    }

    pairs couples = GS(freemen, men_pref, women_pref);

    cout << "Final Pairs :\n";
    for (auto couple : couples)
    {
        cout << couple.second << " >< " << couple.first << "\n";
    }
}