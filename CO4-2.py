from collections import Counter

english_freq = {
    'A': 8.167, 'B': 1.492, 'C': 2.782, 'D': 4.253,
    'E': 12.702, 'F': 2.228, 'G': 2.015, 'H': 6.094,
    'I': 6.966, 'J': 0.153, 'K': 0.772, 'L': 4.025,
    'M': 2.406, 'N': 6.749, 'O': 7.507, 'P': 1.929,
    'Q': 0.095, 'R': 5.987, 'S': 6.327, 'T': 9.056,
    'U': 2.758, 'V': 0.978, 'W': 2.360, 'X': 0.150,
    'Y': 1.974, 'Z': 0.074
}


def decrypt(ciphertext, key):
    result = ""

    for ch in ciphertext:
        if ch.isalpha():
            value = (ord(ch.upper()) - ord('A') - key) % 26
            result += chr(value + ord('A'))
        else:
            result += ch

    return result


def score(text):
    letters = [c for c in text.upper() if c.isalpha()]
    count = Counter(letters)
    total = len(letters)

    chi = 0

    for letter in english_freq:
        observed = count[letter]
        expected = total * english_freq[letter] / 100

        if expected > 0:
            chi += (observed - expected) ** 2 / expected

    return chi


ciphertext = input("Enter ciphertext: ")
top = int(input("How many possible plaintexts? "))

results = []

for key in range(26):
    plaintext = decrypt(ciphertext, key)
    value = score(plaintext)

    results.append((value, key, plaintext))

results.sort()

print("\nMost likely plaintexts:\n")

for i in range(min(top, 26)):
    value, key, plaintext = results[i]

    print(
        f"{i + 1}. Key = {key:2d}, "
        f"Score = {value:.2f}, "
        f"Plaintext = {plaintext}"
    )
