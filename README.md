# Creating a very simple ledger for me and my friends to use

## Usage Instructions:

Creating the executables:
```bash
make
```
Adding Users:
```bash
.\create_user.exe [name]
```
Adding Request Transaction:
```bash
.\create_transaction.exe r [requester] [debtor] [amount]
```
Adding Payment Transaction:
```bash
.\create_transaction.exe p [payer] [reciever] [amount]
```
Calculate Easiest Close-Out Transactions:
```bash
.\calc_ledger.exe
```
