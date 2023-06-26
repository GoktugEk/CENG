extern crate chrono;
extern crate jsonwebtoken as jwt;
extern crate reqwest;
extern crate ring;
extern crate serde_json;
extern crate blake2_rfc as blake2s;

use std::io::Read;
use std::fs::File;
use chrono::{Utc, Duration};
use jwt::{encode, Header, EncodingKey};
use jwt::Algorithm::RS256;
use reqwest::{Client, header};
use ring::signature::RsaKeyPair;
use serde_json::json;
use serde::{Serialize, Deserialize};
use blake2::{Blake2s, Digest};
use std::collections::HashMap;

#[derive(Debug, Serialize, Deserialize)]
struct Transaction {
    source: String,
    destination: String,
    amount: u32,
    timestamp: String,
}

#[derive(Debug, Deserialize)]
struct Block {
    transaction_list: Vec<String>,
    nonce: u32,
    timestamp: String,
}

#[derive(Debug, Serialize, Deserialize)]
struct Claim {
    tha: String,
    iat: u64,
    exp: u64,
}

fn read_private_key() -> Vec<u8> {
    let mut file = File::open("rsa_private_key.pem").unwrap();
    let mut private_key = Vec::new();
    file.read_to_end(&mut private_key).unwrap();
    private_key
}

async fn main() {
    let private_key = read_private_key();
    let private_key = EncodingKey::from_rsa_pem(&private_key).unwrap();

    let goktug = "9bea5a9afc98347f5990267ed7f6a5a2d4a098a58e29e5ffd06bbe0845843b53";
    let berk = "657cf38d31980919b3641bf46d5beb9c71cddbd9c4f24481d2cde2882299079d";
    let hazal = "94997bdec60b4609e4dad2dcf520350ea72ff0dbfff7868d867d11e4e8730086";
    let yigit = "31a00c9f1d4d4b615e5bce2ae62a337c913e2a7444af348bc170d697b1b20607";

    loop {
        let client = Client::new();
        let transactions: HashMap<String, Transaction> = client.get("https://gradecoin.xyz/transaction")
            .send().unwrap()
            .json().unwrap();

        let mut your_transactions = Vec::new();
        let mut friends_transactions = Vec::new();
        let mut other_transactions = Vec::new();

        for (tx_id, tx) in transactions.iter() {
            if tx.source == goktug {
                your_transactions.push(tx_id);
            } else if tx.source == yigit {
                friends_transactions.push(tx_id);
            } else {
                other_transactions.push(tx_id);
            }
        }

        let mut selected_transactions = Vec::new();
        selected_transactions.extend(your_transactions);
        selected_transactions.extend(friends_transactions);
        selected_transactions.extend(other_transactions.iter().take(10 - your_transactions.len() - friends_transactions.len()).collect::<Vec<_>>());

        if selected_transactions.len() < 10 {
            std::thread::sleep(std::time::Duration::from_secs(3));
            continue;
        }

        let mut nonce = 0;
        let mut block_hash = String::new();
        let timestamp = Utc::now().format("%Y-%m-%dT%H:%M:%S").to_string();

        loop {
            let temp_block = Block {
                transaction_list: selected_transactions.clone(),
                nonce,
                timestamp: timestamp.clone(),
            };
            let temp_block_json = serde_json::to_string(&temp_block).unwrap();
            let mut hasher = Blake2s::new();
            hasher.update(temp_block_json.as_bytes());
            block_hash = format!("{:x}", hasher.finalize());

            if block_hash.starts_with("000000") {
                break;
            }

            nonce += 1;
        }

        let claim = Claim {
            tha: block_hash.clone(),
            iat: Utc::now().timestamp() as u64,
            exp: (Utc::now() + Duration::hours(1)).timestamp() as u64,
        };

        let token = encode(&Header::new(RS256), &claim, &private_key).unwrap();

        let block = json!({
            "transaction_list": selected_transactions,
            "nonce": nonce,
            "timestamp": timestamp,
            "hash": block_hash
        });

        let client = reqwest::Client::new();
        let response = client.post("https://gradecoin.xyz/block")
            .header("Authorization", format!("Bearer {}", token))
            .header("Content-Type", "application/json")
            .body(block.to_string())
            .send().await.unwrap();  // Note the .await here

        let text = response.text().await.unwrap();  // And here
        println!("{}", text);
    }
}
