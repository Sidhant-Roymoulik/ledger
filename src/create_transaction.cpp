#include <cassert>
#include <fstream>
#include <map>
#include <string>

using namespace std;

#define users "data/users.txt"
#define transactions "data/transactions.txt"

int get_max_id(map<string, int> &user_id) {
    ifstream ifs;
    ifs.open(users, fstream::app);

    int id = -1;
    string user_name;
    while (!ifs.eof()) {
        ifs >> id >> user_name;
        user_id[user_name] = id;
    }

    return id;
}

void write_to_ledger(string type, int user_1, int user_2, int amount) {
    ofstream ofs;
    ofs.open(transactions, fstream::app);

    ofs << type << ' ' << user_1 << ' ' << user_2 << ' ' << amount << endl;

    ofs.close();
}

// Use .\create_transaction.exe r [requester] [debtor] [amount]
// Use .\create_transaction.exe p [payer] [reciever] [amount]
int main(int argc, char *argv[]) {
    assert(argc == 5);

    string type = argv[1];
    int amount  = stoi(argv[4]);

    assert(type == "r" || type == "p");

    map<string, int> user_id;
    int max_id = get_max_id(user_id);

    if (type == "r") {
        string requester = argv[2];
        string debtor    = argv[3];

        assert(user_id[requester] <= max_id);
        assert(user_id[debtor] <= max_id);
        assert(user_id[requester] != user_id[debtor]);

        write_to_ledger(type, user_id[requester], user_id[debtor], amount);
    } else if (type == "p") {
        string payer    = argv[2];
        string reciever = argv[3];

        assert(user_id[payer] <= max_id);
        assert(user_id[reciever] <= max_id);
        assert(user_id[payer] != user_id[reciever]);

        write_to_ledger(type, user_id[payer], user_id[reciever], amount);
    }

    return 0;
}