#include <cassert>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void write_to_ledger(string filename, string type, int sender, int reciever, int amount) {
    ofstream myfile;
    myfile.open(filename, fstream::app);
    myfile << type << ' ' << sender << ' ' << reciever << ' ' << amount << endl;
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

// Use .\create_transaction.exe [type] [user1] [user2] [amount]
int main(int argc, char *argv[]) {
    assert(argc == 5);

    string type = argv[1], sender = argv[2], reciever = argv[3];
    int amount = stoi(argv[4]);

    assert(type == "r" || type == "p");

    map<string, int> user_id;
    int max_id = get_max_id("users.txt", user_id);

    assert(user_id[sender] <= max_id);
    assert(user_id[reciever] <= max_id);
    assert(user_id[sender] != user_id[reciever]);

    write_to_ledger("testing.txt", type, user_id[sender], user_id[reciever], amount);

    return 0;
}