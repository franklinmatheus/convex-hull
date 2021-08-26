import matplotlib.pyplot as plt
import numpy as np

brute_time = [list(map(int, line.split(" "))) for line in open("./data/timeBrute_output2.txt","r",encoding="utf-8").read().split("\n") if line != ""]
graham_time = [list(map(int, line.split(" "))) for line in open("./data/timeGraham_output2.txt","r",encoding="utf-8").read().split("\n") if line != ""]

fig, ax = plt.subplots(figsize=(10,6))
ax.plot(*zip(*brute_time), "r", label="Força Bruta")
ax.plot(*zip(*graham_time), "b", label="Varredura de Graham")

plt.xlabel("Número de Pontos")
plt.ylabel("Tempo de Execução (nanosegundos)")
ax.legend()
plt.tight_layout()
plt.xticks(np.arange(4, 1025, 60))

fig.savefig("temp.png", dpi=fig.dpi)