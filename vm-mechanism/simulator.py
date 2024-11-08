import random
import matplotlib.pyplot as plt
import numpy as np

def simulate(address_space_size, limit_values):
    """
    Simulates the addressing and calculates the validity fractions.

    Args:
        address_space_size: The size of the address space.
        limit_values: A list of limit values.

    Returns:
        A list of calculated validity fractions.
    """

    fractions = []
    for limit in limit_values:
        valid_count = 0
        total_count = 10000
        for _ in range(total_count):
            vaddr = random.randint(0, address_space_size - 1)
            if vaddr <= limit:
                valid_count += 1
        fractions.append(valid_count / total_count)
    return fractions

# Parameters
address_space_size = 1024
limit_values = range(0, address_space_size + 1)

# Simulate with multiple random seeds
num_seeds = 5
all_fractions = []
for _ in range(num_seeds):
    fractions = simulate(address_space_size, limit_values)
    all_fractions.append(fractions)

# Calculate average fractions and standard deviation
avg_fractions = [sum(f) / num_seeds for f in zip(*all_fractions)]
std_dev = [np.std(f) for f in zip(*all_fractions)]

# Plot the results
plt.plot(limit_values, avg_fractions)
plt.xlabel("Limit Value")
plt.ylabel("Fraction of Valid Addresses")
plt.title("Fraction of Valid Addresses vs. Limit Value")
plt.grid(True)
plt.fill_between(limit_values, [f - s for f, s in zip(avg_fractions, std_dev)], [f + s for f, s in zip(avg_fractions, std_dev)], alpha=0.2)
plt.savefig("vm-mechanism/my_plot.png")