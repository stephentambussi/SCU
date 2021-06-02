def intersect(seq1, seq2):
    res = []
    for x in seq1:
        if x in seq2:
            res.append(x)
    return res

s1 = "SPAM"
s2 = "SCAM"
result1 = intersect(s1,s2)
print(result1)

result2 = intersect([1,2,3], (1,4))
print(result2)
