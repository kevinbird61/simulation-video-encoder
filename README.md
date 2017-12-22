# simulation-video-encoder
Network simulation project, with some practices on video encoder server.

--- 

# Requirement
> My develope environment 
## Standard 
- gcc version 5.4.1
- GNU make 4.1
- GNU gdb 7.11.1

## Document/Report
- node.js (latest/v8.8.1) - [install guide](https://github.com/toolbuddy/docoGen/wiki/node.js-%E5%AE%89%E8%A3%9D)
  - [docogen](https://github.com/toolbuddy/docoGen) (v0.1.5)
- gnuplot (v5.0)

---
# Get Started

## Basic
```bash
# compile
$ make

# run example
$ make run

# clean all 
$ make clean

```

## Project result export 
```bash
# Project use case output
$ make proj

# plot the result
$ make plot

# combine together
$ make proj && make plot
```

## Generate document paper
```
# generate document with docogen
$ make docogen

# clean doc dependencies
$ make cleandoc
```

## Debug 

```bash
# compile with gdb options
$ make gdb
# gdb run (with sample config)
$ make run_g
```

# Run 

* You can simpliy run `./main -h` to see helper manual (below).
```bash
Simulation:
Type 1: bottom field
Type 0: top field
Type 2: encoded top field arrival
Type 3: encoded bottom field arrival
Type 4: leaving event
===================================

Usage: ./main [-t time] [-b buffer] [-n nums] [-a alpha] [-e Cenc] [-s Cs] [-f param1] [-c param2] [-r report]

  -n nums:	specify how many times you want to run the simulation routine
  -t time:	specify the total simulation time (hours)
  -b buffer:	specify the buffer size
  -a alpha:	specify the parameter of storage process
  -e Cenc:	specify the encoding speed of encoder
  -s Cstorage:	specify the storaging speed of storage server
  -f param1:	specify the parameter of time between field arrival(secs)
  -c param2:	specify the parameter of complexity of a field(fods)
  -r report:	specify the report type name(for gnuplot usage)

```

# Document 
- [simulation report paper](doc/simulation-report.pdf)
- [discussion note](https://paper.dropbox.com/doc/Project-1-DiscussNote-p1Jgb0YwDkpAioDyNFvHs)

# Flowchart

## Entire system
![](res/flowchart.png)

## Simulation graph of system
![](res/sim.png)

## Initial routine
![](res/initial.png)

## Encoder routine
![](res/encoder.png)

## Memory usage (Queue)
![](res/queue.png)


