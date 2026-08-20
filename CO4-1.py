def encrypt(plaintext, key):
    plaintext = ''.join(c.upper() for c in plaintext if c.isalpha())

    ciphertext = ""

    for i in range(len(plaintext)):
        p = ord(plaintext[i]) - ord('A')
        c = (p + key[i]) % 26
        ciphertext += chr(c + ord('A'))

    return ciphertext


def find_key(ciphertext, plaintext):
    key = []

    for c, p in zip(ciphertext, plaintext):
        c_value = ord(c) - ord('A')
        p_value = ord(p) - ord('A')

        key.append((c_value - p_value) % 26)

    return key


# Part (a)
plaintext = "send more money"
key = [9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9]

ciphertext = encrypt(plaintext, key)

print("Part (a)")
print("Plaintext :", plaintext)
print("Key       :", key)
print("Ciphertext:", ciphertext)

# Part (b)
new_plaintext = "cash not needed"

new_key = find_key(ciphertext, ''.join(
    c.upper() for c in new_plaintext if c.isalpha()
))

print("\nPart (b)")
print("Ciphertext :", ciphertext)
print("Plaintext  :", new_plaintext)
print("Required Key:", new_key)
