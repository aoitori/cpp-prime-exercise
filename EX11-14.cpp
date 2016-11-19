#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main ()
{
    map<string, vector<pair<string, string>>> families;
    cout << "Please enter the family's name: ";
    for(string temp; cin >> temp && temp != "q";)
    {
        cout << "Enter children's name: ";
        for(string name, birth;cin >> name;)
        {
            cin.get();
            cout << "The his/her birthday: ";
            cin >> birth;
            families[temp].push_back(make_pair(name, birth));
            cout << endl << "\nNext children's name: ";
        }
        cout << "\nNext family's name: ";
        cin.clear();
    }
    cout << endl;

    for(const auto &s : families)
    {
        cout << "Family name: " << s.first << endl;
        for (const auto &w : s.second)
            cout << "Name: " << w.first << " Birthday: " << w.second << endl;
    }
    cout << endl;

    return 0;
}
