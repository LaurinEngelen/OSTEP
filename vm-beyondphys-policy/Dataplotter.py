import numpy as np
import matplotlib.pyplot as plt
import re
import subprocess

def extract_page_references(trace_file):
    page_refs = []
    page_size = 4096  # Standard page size

    with open(trace_file, 'r') as f:
        for line in f:
            try:
                parts = line.split()
                if len(parts) > 1:
                    address = int(parts[1], 16)
                    page_number = address // page_size
                    page_refs.append(page_number)
            except:
                continue

    return page_refs

def extract_hit_rate(output):
    # Extract the hit rate from the simulator's output
    hits = re.search(r'Hits:(\d+)', output)
    misses = re.search(r'Misses:(\d+)', output)
    print(f"Extracting hit rate from output: {output}")  # Debug print
    if hits:
        print(f"Found hits: {hits.group(1)}")  # Debug print
    if misses:
        print(f"Found misses: {misses.group(1)}")  # Debug print
    if hits and misses:
        hits = int(hits.group(1))
        misses = int(misses.group(1))
        return hits / (hits + misses)
    return None


def analyze_working_set(page_refs, max_cache_size=500):
    hit_rates = []
    cache_sizes = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]
    
    for cache_size in cache_sizes:
    # Run the simulator and capture the output
        result = subprocess.run(
            ['./paging-policy.py', '-f', 'pagetrace.out', '-C', str(cache_size), '-p', 'LRU', '-c'],
          capture_output=True, text=True
        )
    # Print the output for debugging
        print(f"Cache Size: {cache_size}")
        print(result.stdout)
    
    # Extract hit rate from the result
        hit_rate = extract_hit_rate(result.stdout)
        if hit_rate is not None:
            hit_rates.append(hit_rate)
        else:
           print(f"Failed to extract hit rate for cache size {cache_size}")

def plot_working_set(hit_rates):
    plt.figure(figsize=(10, 6))
    plt.plot(range(1, len(hit_rates) + 1), hit_rates)
    plt.title('Cache Working Set Analysis')
    plt.xlabel('Cache Size (Pages)')
    plt.ylabel('Hit Rate')
    plt.grid(True)
    plt.savefig('working_set.png')

# Main execution
trace_file = 'memtrace'
page_refs = extract_page_references(trace_file)
hit_rates = analyze_working_set(page_refs)
plot_working_set(hit_rates)

# Print interesting statistics
print(f"Total unique pages referenced: {len(set(page_refs))}")
print(f"Cache size for 90% hit rate: {next((i for i, hr in enumerate(hit_rates, 1) if hr >= 0.9), 'Not found')}")