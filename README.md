# Optimal Page Replacement Algorithm 
This is an implementation of the Optimal page replacement algorithm.

## Overview
This is a C program that implements the Optimal page replacement algorithm. The program reads a file containing a list of memory references, and simulates how the memory management system would operate with a given number of physical pages and page size.



## Usage
The program calculates the number of page faults for a sequence of memory references (i.e., the
memory reference trace in the .mem-files) when using the Optimal page replacement policy.

The program takes the number of physical pages, the page size, and the name of the trace file:
```sh
./optimal no_phys_pages page_size filename
```

The program then returns the resulting number of page faults for that specific combination of number of pages and page size,
for either mp3d.mem or mult.mem.
Example execution:
```sh
 ./optimal 32 128 mp3d.mem
```
Output:
```sh
No physical pages = 32, page size = 128
Reading memory trace from mp3d.mem... Read 100000 memory references
Result: 824 page faults
```



## Contributing
Contributions to this project are welcome. If you find a bug or want to suggest an improvement, please open an issue or submit a pull request.
Or email me here: f.asadi2002@gmail.com

## License
This code is released under the MIT License.
