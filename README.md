# Parallel & Distributed Systems — Project 1

This repository contains the C implementations created for the first project in the *Parallel and Distributed Systems* course, offered within the Department of Electrical and Computer Engineering at **Aristotle University of Thessaloniki (AUTH)**.

The primary objective of the assignment was twofold:

1. **Design and implement a correct sequential solution** for a given computational problem.
2. **Parallelize the solution** using multiple programming models to evaluate how parallel execution affects performance across different CPU cores.

By exploring several parallelization frameworks, the project highlights practical differences in programmability, workload distribution, and speedup efficiency.

---

## 🧠 Project Overview

The core problem (described in detail inside the project files) is first solved using a standard single-threaded C implementation.  
The sequential solution is then extended into multiple parallel versions, each leveraging a different parallel programming technology:

- **OpenCilk** – for task-parallel decomposition with lightweight work-stealing scheduling  
- **OpenMP** – for structured parallelism using compiler directives  
- **POSIX Threads (pthreads)** – for explicit thread creation, synchronization, and workload management  

These implementations demonstrate how the same algorithm can be mapped onto various parallel paradigms, offering insights into performance, scalability, and implementation complexity.

---

## 📂 Repository Structure
