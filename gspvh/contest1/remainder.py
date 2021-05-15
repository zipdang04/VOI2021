inp = "remainder.inp"
out = "remainder.out"
a = 0; b = 0
with open(inp) as f:
	x = f.readline().split()
	a = int(x[0]); b = int(x[1])

if (b < 0):
	b = -b
a %= b
if (a < 0):
	a += b

f = open(out, "w")
f.write(str(a))