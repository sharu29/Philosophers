#  Philosophers

The Philosophers project is a classic concurrency problem implemented in C using POSIX threads (pthreads).  
The challenge is to simulate a group of philosophers sitting at a table who alternately think, eat, and sleep — without creating deadlocks or race conditions when accessing shared resources (forks).

This project was developed as part of the 42 Prague curriculum to explore multithreading, mutexes, and resource synchronization.

---

##  What is the Dining Philosophers Problem?

A number of philosophers sit around a circular table with a fork between each pair. Each philosopher needs **two forks** to eat — one from the left and one from the right.

The problem demonstrates the challenges of:
- Synchronization
- Deadlock avoidance
- Starvation prevention
- Thread-safe resource access

---

##  Features

- Multi-threaded simulation of each philosopher  
- Forks protected with **mutexes**  
- Accurate timing for eating, sleeping, and thinking  
- Edge case handling for 1 philosopher  
- Optional death detection and stopping conditions  
- Custom sleep function for precise time tracking  
