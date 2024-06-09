start=[1634036816,
1763730803,
1953853550,
2003837472,
859321710,
1869881378,
1952802592,
1701344288,
1634493984,
1680613479,
1818391919,
1970348133,
1936028783,
544434464,
1701736053,
1936942435,
7959137,]
from struct import pack
def trans(start):
    output =b''
    for i in start:
        output+=pack('I',i)
    print(output)

trans(start)

flag=[1734437990,
1887007867,
811818803,
1937065582,
1601056817,
859005490,
1681405495,
8206181,]
trans(flag)

# b'Please input "web212" to get the flag ,double quotes is unnecessary\x00'
# b'flag{typ3_c0nFus10n_1299401ffb}\x00'




