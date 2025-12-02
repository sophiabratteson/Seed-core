from node import Node

A = Node("Laptop_A")

print("=== Laptop A ===")

# Step 1 — Import B's file if it exists
A.import_transactions("from_B.json")

# Step 2 — Ask user to create a transaction
receiver = input("Send money to: ")
amount = float(input("Amount to send: "))
A.create_transaction(receiver, amount)

# Step 3 — Export A's data for B
A.export_transactions("from_A.json")

# Step 4 — Show the full ledger
A.show_ledger()

print("Now copy from_A.json to Laptop B.")

