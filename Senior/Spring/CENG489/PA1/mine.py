import requests
import json
import time
from hashlib import blake2s
import jwt
import datetime
import sys

with open('rsa_private_key.pem', 'r') as f:
    private_key = f.read()


def create_jwt(block_hash):
    payload = {
        "tha": block_hash,
        "iat": int(time.time()),
        "exp": int(time.time()) + 3600  # 1 hour from now
    }
    encoded_jwt = jwt.encode(payload, private_key, algorithm='RS256')
    return encoded_jwt

def mine_block(transactions, nonce=0):
    timestamp = time.strftime("%Y-%m-%dT%H:%M:%S")
    nonce = nonce


    while True:
        temp_block = {
            "transaction_list": transactions,  # select first 10 transactions
            "nonce": nonce,
            "timestamp": timestamp
        }
        temp_block_json = json.dumps(temp_block, separators=(',', ':'))
        block_hash = blake2s(temp_block_json.encode('utf-8')).hexdigest()

        if block_hash.startswith('0' * 6):
            return temp_block, block_hash  # returning the block instead of json string
        

        nonce += 4

def mine(nonce=0):
    goktug = "9bea5a9afc98347f5990267ed7f6a5a2d4a098a58e29e5ffd06bbe0845843b53"
    berk = "657cf38d31980919b3641bf46d5beb9c71cddbd9c4f24481d2cde2882299079d"
    hazal = "94997bdec60b4609e4dad2dcf520350ea72ff0dbfff7868d867d11e4e8730086"
    yigit = "31a00c9f1d4d4b615e5bce2ae62a337c913e2a7444af348bc170d697b1b20607"

    while True:
        print("Mining...")
        response = requests.get("https://gradecoin.xyz/transaction")


        all_transactions = response.json()


        # Get your transactions
        your_transactions = [tx_id for tx_id, tx in all_transactions.items() if tx['source'] == goktug]

        # Friends transactions
        friends_transactions = [tx_id for tx_id, tx in all_transactions.items() if tx['source'] == yigit]

        # Get other transactions
        other_transactions = [tx_id for tx_id, tx in all_transactions.items() if tx['source'] != goktug and tx['source'] != yigit]

        # Combine your transactions with others' transactions to get a total of 10 transactions
        transactions = your_transactions + friends_transactions + other_transactions[:10 - len(your_transactions) - len(friends_transactions)]

        print(len(transactions))

        if(len(transactions) < 10):
            time.sleep(3)
            continue

        block, block_hash = mine_block(transactions,nonce)
        
        url = "https://gradecoin.xyz/block"


        payload = {
            "tha": block_hash,
            "iat": int(datetime.datetime.now().timestamp()),  # Current Unix time
            "exp": int((datetime.datetime.now() + datetime.timedelta(minutes=120)).timestamp())  # Unix time 5 minutes from now
        }


        jwt_token = jwt.encode(payload, private_key, algorithm='RS256')


        headers = {
            "Authorization": f"Bearer {jwt_token}",
            "Content-Type": "application/json"
        }

        data = {
            "transaction_list": block["transaction_list"],
            "nonce": block["nonce"],
            "timestamp": block["timestamp"],
            "hash": block_hash
        }

        
        response = requests.post(url, headers=headers, data=json.dumps(data))
        print(response.text)





if __name__ == "__main__":
    nonce = int(sys.argv[1])

    mine(nonce)

