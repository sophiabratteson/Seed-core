import json, os, uuid

class Node:
    def __init__(self, node_id):
        self.node_id = node_id
        self.ledger = {}

    def create_transaction(self, receiver, amount):
        tx = {
            "tx_id": str(uuid.uuid4()),
            "sender": self.node_id,
            "receiver": receiver,
            "amount": amount
        }
        self.ledger[tx["tx_id"]] = tx
        print(f"Created transaction: {tx}")
        return tx

    def import_transactions(self, filename):
        try:
            with open(filename, "r") as f:
                data = json.load(f)
            for tx in data:
                self.ledger[tx["tx_id"]] = tx
            print(f"Imported {len(data)} transactions from {filename}")
        except:
            print(f"No file named {filename} found. Skipping.")

    def export_transactions(self, filename):
        all_txs = list(self.ledger.values())
        with open(filename, "w") as f:
            json.dump(all_txs, f, indent=2)
        print(f"Exported {len(all_txs)} transactions to {filename}")

    def show_ledger(self):
        print("\n--- Ledger ---")
        for tx in self.ledger.values():
            print(tx)
        print("--------------\n")

