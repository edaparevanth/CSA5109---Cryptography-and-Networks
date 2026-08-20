from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes


# -------------------------------------------------
# Generate RSA keys
# -------------------------------------------------

private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048
)

public_key = private_key.public_key()


 #-------------------------------------------------

message = input("Enter message: ").encode()

print("\nOriginal Message:")
print(message.decode())


# -------------------------------------------------
# Digital Signature
# -------------------------------------------------

signature = private_key.sign(
    message,
    padding.PSS(
        mgf=padding.MGF1(hashes.SHA256()),
        salt_length=padding.PSS.MAX_LENGTH
    ),
    hashes.SHA256()
)

print("\nDigital signature generated.")


# -------------------------------------------------
# Encrypt message using receiver's public key
# -------------------------------------------------

encrypted_message = public_key.encrypt(
    message,
    padding.OAEP(
        mgf=padding.MGF1(
            algorithm=hashes.SHA256()
        ),
        algorithm=hashes.SHA256(),
        label=None
    )
)

print("Message encrypted successfully.")


decrypted_message = private_key.decrypt(
    encrypted_message,
    padding.OAEP(
        mgf=padding.MGF1(
            algorithm=hashes.SHA256()
        ),
        algorithm=hashes.SHA256(),
        label=None
    )
)

print("\nDecrypted Message:")
print(decrypted_message.decode())


try:

    public_key.verify(
        signature,
        decrypted_message,
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
    )

    print("\nDigital Signature: VALID")
    print("Message is authentic.")

except Exception:
    print("\nDigital Signature: INVALID")
