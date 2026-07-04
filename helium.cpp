#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <cctype>

/*
g++ -std=c++17 helium.cpp -o Helium
*/

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

int value(string s)
{
    if (isdigit(s[0]) || s[0] == '-')
    {
        return stoi(s);
    }
    else
    {
        return vars[s];
    }
}

int add(string a, string b)
{
    return value(a) + value(b);
}

int sub(string a, string b)
{
    return value(a) - value(b);
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
            else if (t[3] == "sub")
            {
                vars[t[1]] = sub(t[4], t[5]);
            }
            else
            {
                vars[t[1]] = value(t[3]);
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
            else if (t[1] == "sub")
            {
                cout << sub(t[2], t[3]) << endl;
            }
            else
            {
                cout << vars[t[1]] << endl;
            }
        }
    }
    return 0;
}