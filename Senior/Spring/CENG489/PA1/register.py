from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding as symmetric_padding
from cryptography.hazmat.backends import default_backend
import os
import json
import base64

# The given values
student_id = "e238050"
passwd = "8p+2GpCUI3F1E91+0N2BiDY75ytgiSw1"

# Load the gradecoin_public_key from a file
with open("gradecoin.pub", "rb") as key_file:
    gradecoin_public_key = serialization.load_pem_public_key(
        key_file.read(),
        backend=default_backend()
    )

# Generate a new RSA key pair
private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048,
    backend=default_backend()
)
public_key = private_key.public_key()

# Save the RSA private key for future use
pem = private_key.private_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PrivateFormat.PKCS8,
    encryption_algorithm=serialization.NoEncryption()
)
with open('rsa_private_key.pem', 'wb') as pem_out:
    pem_out.write(pem)
with open('rsa_public_key.pem', 'wb') as pem_out:
    pem_out.write(public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    ))

P_AR = {
    "student_id": student_id,
    "passwd": passwd,
    "public_key": public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    ).decode('utf-8')
}

# Pick a random 128 bit temporary key and a random IV
k_temp = os.urandom(16)
iv = os.urandom(16)

# Save the temporary key and IV for future use
with open('k_temp.txt', 'w') as file:
    file.write(k_temp.hex())
with open('iv.txt', 'w') as file:
    file.write(iv.hex())

# Serialize and encrypt P_AR
cipher = Cipher(algorithms.AES(k_temp), modes.CBC(iv), backend=default_backend())
encryptor = cipher.encryptor()
padder = symmetric_padding.PKCS7(128).padder()
padded_data = padder.update(json.dumps(P_AR).encode('utf-8')) + padder.finalize()
C_AR = base64.b64encode(encryptor.update(padded_data) + encryptor.finalize()).decode('utf-8')

# Encrypt k_temp with RSA
key_ciphertext = base64.b64encode(
    gradecoin_public_key.encrypt(
        k_temp,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
).decode('utf-8')

# Base64 encode the IV
iv_base64 = base64.b64encode(iv).decode('utf-8')

# The final payload
auth_request = {
    "c": C_AR,
    "iv": iv_base64,
    "key": key_ciphertext
}

print(json.dumps(auth_request))
