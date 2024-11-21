import re

page_size = 4096  # Assuming a page size of 4KB

with open('memtrace.out', 'r') as infile, open('pagetrace.out', 'w') as outfile:
    for line in infile:
        match = re.search(r'I\s+([0-9a-fA-F]+)', line) or re.search(r'D\s+([0-9a-fA-F]+)', line)
        if match:
            address = int(match.group(1), 16)
            page_number = address // page_size
            outfile.write(f"{page_number}\n")