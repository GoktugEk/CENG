import * as crypto from 'crypto';
import * as fs from 'fs';

// The given values
const student_id = "e238034";
const passwd = "nZhKeHtNosYXvhS5g5OgJVQIdddn7Tia";

// Load the gradecoin_public_key from a file
const gradecoin_public_key = fs.readFileSync('gradecoin.pub', 'utf8');

// Generate a new RSA key pair (in this case, we only use the public key in the object)
const { publicKey, privateKey } = crypto.generateKeyPairSync('rsa', {
    modulusLength: 1024,
    publicKeyEncoding: {
      type: 'pkcs1',
      format: 'pem',
    },
    privateKeyEncoding: {
      type: 'pkcs1',
      format: 'pem',
    },
});

// Save the RSA private key for future use
fs.writeFileSync('rsa_private_key.pem', privateKey);
fs.writeFileSync('rsa_public_key.pem', publicKey);

const P_AR = {
    student_id: student_id,
    passwd: passwd,
    public_key: publicKey
}

// Pick a random 128 bit temporary key and a random IV
const k_temp = crypto.randomBytes(16);
const iv = crypto.randomBytes(16);

// Save the temporary key and IV for future use
fs.writeFileSync('k_temp.txt', k_temp.toString('hex'));
fs.writeFileSync('iv.txt', iv.toString('hex'));

// Serialize and encrypt P_AR
const cipher = crypto.createCipheriv('aes-128-cbc', k_temp, iv);
let C_AR = cipher.update(JSON.stringify(P_AR), 'utf8', 'base64');
C_AR += cipher.final('base64');

// Encrypt k_temp with RSA
const key_ciphertext = crypto.publicEncrypt({
    key: gradecoin_public_key,
    padding: crypto.constants.RSA_PKCS1_OAEP_PADDING,
}, k_temp).toString('base64');

// Base64 encode the IV
const iv_base64 = iv.toString('base64');

// The final payload
const auth_request = {
    c: C_AR,
    iv: iv_base64,
    key: key_ciphertext
}

console.log(JSON.stringify(auth_request));

