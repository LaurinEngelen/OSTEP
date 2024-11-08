import random
import matplotlib.pyplot as plt
import time

class SimulatedMalloc:
    def __init__(self, size, policy, order):
        self.size = size
        self.freelist = [(0, size)]  # Start mit einem großen freien Block
        self.policy = policy  # FIRST, BEST, WORST
        self.order = order  # ADDRSORT, SIZESORT+, SIZESORT-

    def allocate(self, request_size):
        # Sortiere die Liste je nach gewähltem Order
        if self.order == 'ADDRSORT':
            self.freelist.sort(key=lambda x: x[0])  # Nach Adresse
        elif self.order == 'SIZESORT+':
            self.freelist.sort(key=lambda x: x[1])  # Aufsteigend nach Größe
        elif self.order == 'SIZESORT-':
            self.freelist.sort(key=lambda x: -x[1])  # Absteigend nach Größe

        # Simulation der Zuweisungsstrategie
        start_time = time.time()
        bestIdx = -1

        if self.policy == 'FIRST':
            for i, (addr, fsize) in enumerate(self.freelist):
                if fsize >= request_size:
                    bestIdx = i
                    break
        elif self.policy == 'BEST':
            bestSize = float('inf')
            for i, (addr, fsize) in enumerate(self.freelist):
                if fsize >= request_size and fsize < bestSize:
                    bestSize = fsize
                    bestIdx = i
        elif self.policy == 'WORST':
            bestSize = -1
            for i, (addr, fsize) in enumerate(self.freelist):
                if fsize >= request_size and fsize > bestSize:
                    bestSize = fsize
                    bestIdx = i

        end_time = time.time()
        search_time = end_time - start_time

        if bestIdx != -1:
            addr, fsize = self.freelist.pop(bestIdx)
            if fsize > request_size:
                self.freelist.append((addr + request_size, fsize - request_size))
            return search_time
        else:
            return None

def run_simulation(allocations, heap_size=1000, request_size=50):
    policies = ['FIRST', 'BEST', 'WORST']
    orders = ['ADDRSORT', 'SIZESORT+', 'SIZESORT-']
    results = {policy: {order: [] for order in orders} for policy in policies}

    for policy in policies:
        for order in orders:
            malloc_simulator = SimulatedMalloc(size=heap_size, policy=policy, order=order)
            times = []

            for _ in range(allocations):
                search_time = malloc_simulator.allocate(request_size)
                if search_time is not None:
                    times.append(search_time)

            avg_time = sum(times) / len(times) if times else 0
            results[policy][order].append(avg_time)
    
    return results

# Parameters
allocations = 200
heap_size = 1000
request_size = 50

# Run simulation and get results
results = run_simulation(allocations, heap_size, request_size)

# Plot results
fig, ax = plt.subplots()
bar_width = 0.2
x = range(len(results['FIRST'].keys()))
offset = 0

for policy in results:
    avg_times = [results[policy][order][0] for order in results[policy]]
    ax.bar(
        [p + offset for p in x], avg_times, bar_width, label=f'Policy: {policy}'
    )
    offset += bar_width

ax.set_xlabel('Free List Order')
ax.set_ylabel('Average Search Time (s)')
ax.set_title('Effect of List Ordering on Allocation Time')
ax.set_xticks([p + bar_width for p in x])
ax.set_xticklabels(list(results['FIRST'].keys()))
ax.legend()

plt.savefig("vm-freespace/my_plot.png")
