#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define users "data/users.txt"

int iter_users() {
    ifstream ifs;
    ifs.open(users, fstream::app);

    int id = -1;
    string user_name;
    while (!ifs.eof()) {
        ifs >> id >> user_name;
    }
    ifs.close();
    return id + 1;
}

vector<int> fill_need(string filename, int num_users) {
    vector<int> net(num_users, 0);
    ifstream ifs;
    ifs.open(filename, fstream::app);

    while (!ifs.eof()) {
        string type;
        int id_r, id_l, amount;
        ifs >> type >> id_r >> id_l >> amount;

        // cout << type << ' ' << id_r << ' ' << id_l << ' ' << amount << endl;

        if (type == "r") {
            net[id_r] += amount;
            net[id_l] -= amount;
        } else if (type == "p") {
            net[id_r] -= amount;
            net[id_l] += amount;
        }
    }
    ifs.close();
    return net;
}

int main(int argc, char *argv[]) {
    int num_users   = iter_users();
    vector<int> net = fill_need("data/testing.txt", num_users);

    for (int i = 0; i < num_users; i++) {
        cout << net[i] << ' ';
    }
    cout << endl;

    return 0;
}