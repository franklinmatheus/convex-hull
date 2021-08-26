import matplotlib.pyplot as plt

input = "data/input1.txt"
output_graham = "data/graham_output1.txt"

points = []
infile = open(input, "r", encoding="utf8")
for line in infile:
    if line != "":
        points.append(list(map(int, line.replace("\n","").split(" "))))

result = []
outfile = open(output_graham, "r", encoding="utf8")
for line in outfile:
    if line != "":
        result.append(list(map(int, line.replace("\n","").split(","))))

fig, ax = plt.subplots(figsize=(5,5))
x, y = zip(*points)
ax.scatter(x=x,y=y, label="Pontos")

result.append(result[0])
ax.plot(*zip(*result), "r", label="Convex Hull")

plt.xlabel("X")
plt.ylabel("Y")
plt.tight_layout()
fig.savefig("temp.png", dpi=fig.dpi)