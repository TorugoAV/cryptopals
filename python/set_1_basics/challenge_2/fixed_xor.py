def fixed_xor(buffer_1: bytes, buffer_2: bytes)->bytes:
    if len(buffer_1) != len(buffer_2):
        raise Exception("[!] Different size buffers!")

    r = b""
    for i in range(len(buffer_1)):
        r += (buffer_1[i] ^ buffer_2[i]).to_bytes(1,"little")

    return r

string_1 = "1c0111001f010100061a024b53535009181c"
string_2 = "686974207468652062756c6c277320657965"
result   = "746865206b696420646f6e277420706c6179"

bytes_1 = bytes.fromhex(string_1)
bytes_2 = bytes.fromhex(string_2)

r = bytes.hex(fixed_xor(bytes_1, bytes_2))

if r == result:
    print("Xored string:", r)
    print("Success")
