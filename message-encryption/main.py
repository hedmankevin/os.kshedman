from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from base64 import urlsafe_b64encode, urlsafe_b64decode
from cryptography.hazmat.primitives import padding
from os import urandom

def encrypt_message(message, key):
    # Generate a random IV (Initialization Vector)
    iv = urandom(16)

    # Pad the message to ensure it's a multiple of the block size
    padder = padding.PKCS7(algorithms.AES.block_size).padder()
    padded_message = padder.update(message.encode()) + padder.finalize()

    # Create a cipher object with AES algorithm, CBC mode, and the provided key and IV
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv), backend=default_backend())

    # Encrypt the padded message
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(padded_message) + encryptor.finalize()

    # Combine IV and ciphertext, then base64 encode for easier storage and transmission
    encrypted_message = urlsafe_b64encode(iv + ciphertext).decode()
    return encrypted_message

def decrypt_message(encrypted_message, key):
    # Base64 decode the combined IV and ciphertext
    combined = urlsafe_b64decode(encrypted_message)

    # Extract IV and ciphertext
    iv = combined[:16]
    ciphertext = combined[16:]

    # Create a cipher object with AES algorithm, CBC mode, and the provided key and IV
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv), backend=default_backend())

    # Decrypt the ciphertext
    decryptor = cipher.decryptor()
    decrypted_padded_message = decryptor.update(ciphertext) + decryptor.finalize()

    # Unpad the decrypted message
    unpadder = padding.PKCS7(algorithms.AES.block_size).unpadder()
    decrypted_message = unpadder.update(decrypted_padded_message) + unpadder.finalize()

    return decrypted_message.decode()

# Example usage:
symmetric_key = urandom(32)  # Use a secure method to generate a key
message_to_encrypt = 'Hello, this is a secret message!'

encrypted_message = encrypt_message(message_to_encrypt, symmetric_key)
print(f'Encrypted Message: {encrypted_message}')

decrypted_message = decrypt_message(encrypted_message, symmetric_key)
print(f'Decrypted Message: {decrypted_message}')