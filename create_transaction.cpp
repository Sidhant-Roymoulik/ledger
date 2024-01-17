#include <cassert>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void write_to_ledger(string filename, string type, int requester, int payer, int amount) {
    ofstream myfile;
    myfile.open(filename, fstream::app);
    myfile << type << ' ' << requester << ' ' << payer << ' ' << amount << endl;
    myfile.close();
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

// Use .\create_transaction.exe [type] [requester] [payer] [amount]
int main(int argc, char *argv[]) {
    assert(argc == 5);

    string type = argv[1], requester = argv[2], payer = argv[3];
    int amount = stoi(argv[4]);

    assert(type == "r" || type == "p");

    map<string, int> user_id;
    int max_id = get_max_id("users.txt", user_id);

    assert(user_id[requester] <= max_id);
    assert(user_id[payer] <= max_id);
    assert(user_id[requester] != user_id[payer]);

    write_to_ledger("testing.txt", type, user_id[requester], user_id[payer], amount);

    return 0;
}