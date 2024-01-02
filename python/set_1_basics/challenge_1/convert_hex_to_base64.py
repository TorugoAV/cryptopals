import base64

s = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
r = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

print("Hex String:", s)
b = bytes.fromhex(s)
b64 = base64.b64encode(b).decode()

if b64 == r:
    print("Result:", b64)
    print("Success")

