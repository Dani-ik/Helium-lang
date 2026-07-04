#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

unordered_map<string, int> vars, back_up;

vector<string> split(const string &s)
{
    stringstream ss(s);
    vector<string> v;
    string x;

    while (ss >> x)
    {
        v.push_back(x);
    }

    return v;
}

int add(string a, string b)
{
    int x, y;
    bool isintx = 1, isinty = 1;
    for (char c : a)
    {
        if (!isdigit(c))
        {
            isintx = 0;
            break;
        }
    }
    for (char c : b)
    {
        if (!isdigit(c))
        {
            isinty = 0;
            break;
        }
    }
    if (isintx)
    {
        x = stoi(a);
    }
    else
    {
        x = vars[a];
    }
    if (isinty)
    {
        y = stoi(b);
    }
    else
    {
        y = vars[b];
    }
    return x + y;
}

int main()
{
    ifstream file("main.he");

    if (!file.is_open())
    {
        cout << "Не удалось открыть main.he\n";
        return 1;
    }
    string line;

    while (getline(file, line))
    {
        auto t = split(line);
        if (t.empty())
        {
            continue;
        }
        /*
        cout << "Tokens:\n";
        for (string s : t)
        {
            cout << "[" << s << "] ";
        }
        cout << endl;
        */
        if (t[0] == "let")
        {
            if (t[3] == "add")
            {
                vars[t[1]] = add(t[4], t[5]);
            }
            else
            {
                vars[t[1]] = stoi(t[3]);
            }
        }
        if (t[0] == "del")
        {
            back_up[t[1]] = vars[t[1]];
            vars.erase(t[1]);
        }
        if (t[0] == "rec")
        {
            vars[t[1]] = back_up[t[1]];
            back_up.erase(t[1]);
        }
        if (t[0] == "print")
        {
            if (t[1] == "add")
            {
                cout << add(t[2], t[3]) << endl;
            }
            else
            {
                cout << vars[t[1]] << endl;
            }
        }
    }
    return 0;
}