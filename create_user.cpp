#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int get_index(string name) {
    ifstream ifs;
    ifs.open("users.txt", fstream::app);

    int id = -1;
    string user_name;
    while (!ifs.eof()) {
        ifs >> id >> user_name;

        if (user_name == name) {
            cout << "This user is already registered" << endl;
            ifs.close();
            return -1;
        }
    }
    ifs.close();
    return id + 1;
}

void write_to_ledger(int id, string name) {
    if (id == -1) return;

    ofstream f;
    f.open("users.txt", fstream::app);
    f << id << ' ' << name << endl;
    f.close();
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    string name = argv[1];

    int id = get_index(name);

    if (id == -1) return 0;

    write_to_ledger(id, name);

    return 0;
}