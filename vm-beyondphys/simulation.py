import matplotlib.pyplot as plt

# Daten
datasets = {
    4000: [2197.88, 3566.36, 7209.39, 7114.87, 6320.75, 7311.03, 7019.01, 6933.33, 7110.39, 7123.25, 7459.07],
    5000: [2055.34, 4075.46, 7471.14, 7553.81, 7577.47, 7385.40, 7374.88, 7616.04, 7433.14, 7627.37, 6906.83],
    6000: [2142.21, 6436.88, 7518.25, 7337.10, 7598.39, 7737.69, 7690.31, 7652.97, 7507.45, 7668.86, 7632.33],
    7000: [2229.94, 403.05, 7119.36, 7223.08, 7036.48, 7233.82, 7559.25, 7287.65, 7433.89, 6718.46, 6910.16],
    8000: [2840.14, 180.45, 118.16, 128.36, 128.01],
    8500: [2840.14, 94.54, 105.23, 108.43]
}

# Plotten
plt.figure(figsize=(14, 8))

for size, bandwidths in datasets.items():
    loops = list(range(len(bandwidths)))
    plt.plot(loops, bandwidths, label=f'{size} MB', marker='o')

# Diagramm anpassen
plt.title("Bandbreite (MB/s) pro Loop")
plt.xlabel("Loop")
plt.ylabel("Bandbreite (MB/s)")
plt.legend(title="Datenmenge")
plt.grid(True)
plt.tight_layout()

# Diagramm anzeigen
plt.savefig("simulation.png")