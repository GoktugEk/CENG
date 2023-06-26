import requests
import json
import hashlib
import jwt
import datetime
import time
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.backends import default_backend

# Load your RSA private key from a PEM file
with open("rsa_private_key.pem", "rb") as key_file:
    private_key = serialization.load_pem_private_key(
        key_file.read(),
        password=None,
        backend=default_backend()
    )

def transaction(source_fingerprint, target_fingerprint, amount):
    # Current timestamp in ISO 8601 format
    timestamp = datetime.datetime.now().isoformat()

    # Transaction JSON object
    transaction = {
        "source": source_fingerprint,
        "target": target_fingerprint,
        "amount": amount,
        "timestamp": timestamp
    }

    # Convert transaction object to JSON string
    transaction_json = json.dumps(transaction, separators=(',', ':'))

    # Compute MD5 hash of the transaction JSON string
    transaction_md5 = hashlib.md5(transaction_json.encode('utf-8')).hexdigest()

    # JWT payload
    payload = {
        "tha": transaction_md5,
        "iat": int(datetime.datetime.now().timestamp()),  # Current Unix time
        "exp": int((datetime.datetime.now() + datetime.timedelta(minutes=120)).timestamp())  # Unix time 5 minutes from now
    }

    # Generate JWT with the transaction hash, signed with your private key
    jwt_token = jwt.encode(payload, private_key, algorithm='RS256')

    # The URL for the transaction endpoint
    url = "https://gradecoin.xyz/transaction"

    # The headers for the POST request
    headers = {
        "Authorization": f"Bearer {jwt_token}",
        "Content-Type": "application/json"
    }

    # Send the POST request
    response = requests.post(url, headers=headers, data=transaction_json)

    # Print the response

    print(response.text)

goktug = "9bea5a9afc98347f5990267ed7f6a5a2d4a098a58e29e5ffd06bbe0845843b53"
berk = "657cf38d31980919b3641bf46d5beb9c71cddbd9c4f24481d2cde2882299079d"
hazal = "94997bdec60b4609e4dad2dcf520350ea72ff0dbfff7868d867d11e4e8730086"
bot1 = "a4d9a38a04d0aa7de7c29fef061a1a539e6a192ef75ea9730aff49f9bb029f99"
bot2 = "f44f83688b33213c639bc16f9c167543568d4173d5f4fc7eb1256f6c7bb23b26"
bot3 = "5dcdedc9a04ea6950153c9279d0f8c1ac9528ee8cdf5cd912bebcf7764b3f9db"
bot4 = "4319647f2ad81e83bf602692b32a082a6120c070b6fd4a1dbc589f16d37cbe1d"
fakir1 = "e901759d43cacb4614c5ee13c1cd422583b33b7d8001c1d56cd5cfdf8fb99396"
fakir2 = "0afbfbfcb261543490b83debfca5151805f1236af749373aade582d8225d9840"
yigit = "31a00c9f1d4d4b615e5bce2ae62a337c913e2a7444af348bc170d697b1b20607"

hazal_counter = 0
berk_counter = 0
yigit_counter = 0
bots = 138
fakirs = 2

while True:
    # Get the current transactions
    response = requests.get("https://gradecoin.xyz/transaction")
    transactions = response.json()

    # # Check if there is a transaction between Goktug and Berk
    # goktug_berk_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == berk)
    
    # # If there isn't, make a transaction
    # if not goktug_berk_transaction:
    #     berk_counter += 1
    #     transaction(goktug, berk, 1)

    # Check if there is a transaction between Goktug and Yigit
    goktug_yigit_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == yigit)

    # If there isn't, make a transaction
    if not goktug_yigit_transaction:
        yigit_counter += 1
        transaction(goktug, yigit, 1)

    # Check if there is a transaction between Goktug and Hazal
    goktug_hazal_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == hazal)

    # If there isn't, make a transaction
    if not goktug_hazal_transaction:
        hazal_counter += 1
        transaction(goktug, hazal, 1)

    # Check if there is a transaction between Goktug and bot1
    goktug_bot1_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == bot1)

    # If there isn't, make a transaction
    if not goktug_bot1_transaction:
        bots += 1
        transaction(goktug, bot1, 1)

    # Check if there is a transaction between Goktug and bot2
    goktug_bot2_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == bot2)

    # If there isn't, make a transaction
    if not goktug_bot2_transaction:
        bots += 1
        transaction(goktug, bot2, 1)

    # Check if there is a transaction between Goktug and bot3
    goktug_bot3_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == bot3)
    
    # If there isn't, make a transaction
    if not goktug_bot3_transaction:
        bots += 1
        transaction(goktug, bot3, 1)

    # Check if there is a transaction between Goktug and bot4
    goktug_bot4_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == bot4)

    # If there isn't, make a transaction
    if not goktug_bot4_transaction:
        bots += 1
        transaction(goktug, bot4, 1)

    # Check if there is a transaction between Goktug and fakir1
    goktug_fakir1_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == fakir1)

    # If there isn't, make a transaction
    if not goktug_fakir1_transaction:
        fakirs += 1
        transaction(goktug, fakir1, 1)

    # Check if there is a transaction between Goktug and fakir2
    goktug_fakir2_transaction = any(t for t in transactions.values() if t["source"] == goktug and t["target"] == fakir2)

    # If there isn't, make a transaction
    if not goktug_fakir2_transaction:
        fakirs += 1
        transaction(goktug, fakir2, 1)

    print(f"Yigit: {yigit_counter}, Hazals: {hazal_counter}, Bots: {bots}, Fakirs: {fakirs}")

    time.sleep(5)