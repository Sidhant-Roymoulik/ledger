### Creating a very simple ledger for me and my friends to use.

## Usage Instructions:

Creating the executables:
```bash
cd .\src\
make
```
Adding Users:
```bash
.\create_user.exe [name]
```
Adding Transactions:
```bash
# Request Transaction
.\create_transaction.exe r [requester] [debtor] [amount]

# Pay-Off Transaction
.\create_transaction.exe p [payer] [reciever] [amount]
```
Calculate Easiest Close-Out Transactions:
```bash
.\calc_ledger.exe
```
