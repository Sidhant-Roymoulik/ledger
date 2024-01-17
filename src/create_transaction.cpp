#include <cassert>
#include <fstream>
#include <map>
#include <string>

using namespace std;

#define users "data/users.txt"
#define transactions "data/transactions.txt"

void write_to_ledger(string filename, string type, int user_1, int user_2, int amount) {
    ofstream f;
    f.open(filename, fstream::app);

    f << type << ' ' << user_1 << ' ' << user_2 << ' ' << amount << endl;

    f.close();
}

int get_max_id(string filename, map<string, int> &user_id) {
    ifstream ifs;
    ifs.open(filename, fstream::app);

    int id = -1;
    string user_name;
    while (!ifs.eof()) {
        ifs >> id >> user_name;
        user_id[user_name] = id;
    }

    return id;
}

// Use .\create_transaction.exe r [requester] [debtor] [amount]
// Use .\create_transaction.exe p [payer] [reciever] [amount]
int main(int argc, char *argv[]) {
    assert(argc == 5);

    string type = argv[1], requester = argv[2], payer = argv[3];
    int amount = stoi(argv[4]);

    assert(type == "r" || type == "p");

    map<string, int> user_id;
    int max_id = get_max_id(users, user_id);

    if (type == "p") {
        requester = argv[3];
        payer     = argv[2];
    }

    assert(user_id[requester] <= max_id);
    assert(user_id[payer] <= max_id);
    assert(user_id[requester] != user_id[payer]);

    if (type == "r")
        write_to_ledger(transactions, type, user_id[requester], user_id[payer], amount);
    else if (type == "p")
        write_to_ledger(transactions, type, user_id[payer], user_id[requester], amount);

    return 0;
}