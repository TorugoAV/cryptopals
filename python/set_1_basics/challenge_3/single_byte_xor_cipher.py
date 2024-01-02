def score_english_plaintext(decoded_buffer: bytes)->int:
    letter_frequency = {'E' : 12.0, 'T' : 9.10, 'A' : 8.12, 'O' : 7.68, 'I' : 7.31, 'N' : 6.95, 'S' : 6.28, 'R' : 6.02, 'H' : 5.92, 'D' : 4.32, 'L' : 3.98, 'U' : 2.88, 'C' : 2.71, 'M' : 2.61, 'F' : 2.30, 'Y' : 2.11, 'W' : 2.09, 'G' : 2.03, 'P' : 1.82, 'B' : 1.49, 'V' : 1.11, 'K' : 0.69, 'X' : 0.17, 'Q' : 0.11, 'J' : 0.10, 'Z' : 0.07, ' ': 35.0 }
    char_ammount = {}
    char_percentage = {}
    score = 0
# GET THE AMMOUNT OF LETTERS IN THE BUFFER
    for byte in decoded_buffer.upper():
        if byte in char_ammount:
            char_ammount[byte] += 1
        else:
            char_ammount.update({byte: 1})
# GET THE PERCENTAGE OF THE TEXT IN THE BUFFER
    for elem in char_ammount:
            char_percentage.update({elem: char_ammount[elem] / len(decoded_buffer * 100)})
# result - freq
    for elem in letter_frequency:
        try:
            score += letter_frequency[elem] - char_percentage[ord(elem)]
        except:
            pass
    return score

def fixed_xor(buffer_1: bytes, buffer_2: bytes)->bytes:
    if len(buffer_1) != len(buffer_2):
        raise Exception("[!] Different size buffers!")
    r = b""
    for i in range(len(buffer_1)):
        r += (buffer_1[i] ^ buffer_2[i]).to_bytes(1,"little")
    return r

encrypted = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
encrypted_bytes = bytes.fromhex(encrypted)
results = []

print("[+] Encrypted Text:", encrypted)

for b in range(1, 255):
    r = fixed_xor(encrypted_bytes, b.to_bytes(1,"little") * len(encrypted_bytes))
    score = score_english_plaintext(r)
    results.append([b, score, r])

results.sort(key=lambda x: x[1], reverse=True)

print("[+] Top Three Keys")

for i in range(0,3):
    print("\n[+] Key:", results[i][0])
    print("[+] Score:", results[i][1])
    print("[+] Decoded Message:", results[i][2].decode())
