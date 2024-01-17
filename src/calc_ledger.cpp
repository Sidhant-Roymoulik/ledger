#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define users "data/users.txt"
#define transactions "data/transactions.txt"

int iter_users(map<int, string> &id_to_username) {
    ifstream ifs;
    ifs.open(users, fstream::app);

    int id = -1;
    string user_name;
    while (!ifs.eof()) {
        ifs >> id >> user_name;
        id_to_username[id] = user_name;
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
        int id_1, id_2, amount;
        ifs >> type >> id_1 >> id_2 >> amount;

        // cout << type << ' ' << id_1 << ' ' << id_2 << ' ' << amount << endl;

        if (type == "r" || type == "p") {
            net[id_1] += amount;
            net[id_2] -= amount;
        }
    }
    ifs.close();
    return net;
}

void min_cash_flow(vector<int> &net, int num_users, map<int, string> &id_to_username) {
    int max_credit_index = max_element(net.begin(), net.end()) - net.begin();
    int max_debit_index  = min_element(net.begin(), net.end()) - net.begin();

    if (net[max_credit_index] == 0 && net[max_debit_index] == 0) return;

    int transaction_amount = min(net[max_credit_index], -net[max_debit_index]);
    net[max_credit_index] -= transaction_amount;
    net[max_debit_index] += transaction_amount;

    std::printf("%8s  pays %8s  $%d.%02d\n", id_to_username[max_debit_index].c_str(),
                id_to_username[max_credit_index].c_str(), transaction_amount / 100, transaction_amount % 100);

    min_cash_flow(net, num_users, id_to_username);
}

int main(int argc, char *argv[]) {
    map<int, string> id_to_username;
    int num_users = iter_users(id_to_username);

    vector<int> net = fill_need(transactions, num_users);

    for (int i = 0; i < num_users; i++) {
        cout << net[i] << ' ';
    }
    cout << endl;

    min_cash_flow(net, num_users, id_to_username);

    return 0;
}