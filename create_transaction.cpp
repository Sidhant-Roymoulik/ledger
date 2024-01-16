#include <cassert>
#include <fstream>
#include <string>

using namespace std;

void write_to_ledger(string sender, string reciever, int amount) {
    ofstream myfile;
    myfile.open("transactions.txt", fstream::app);
    myfile << sender << ' ' << reciever << ' ' << amount;
    myfile.close();
}

int main(int argc, char *argv[]) {
    assert(argc == 4);
    string sender = argv[1], reciever = argv[2];
    int amount = stoi(argv[3]);

    write_to_ledger(sender, reciever, amount);

    return 0;
}