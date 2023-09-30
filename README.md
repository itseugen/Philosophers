<h1 align="center">
	<p>
		Philosophers
	</p>
</h1>
<h2 align="center">
	<p>
			I never thought philosophy would be so deadly
	</p>
</h2>
<p align="center">
Coded in
	<a href="https://skillicons.dev">
		<img src="https://skillicons.dev/icons?i=c" />
	</a>
</p>

---
## The project:
- My solution to the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem "Link to wikipedia").
- Using threads and mutexes in the mandatory part.
- Using processes and semaphores in the bonus part.
---
## The program:
- The philosophers sit at a round table, with a bowl of spaghetti in the middle.
- Each philosopher has a fork to his right, there are as many forks as philosophers.
- Philosophers can either THINK, EAT or sleep.
- To EAT the philosopher needs his own fork and the fork on his left.
### The input:
- The number of philosophers.
- The time to die (since the beginning of the last meal or the start of the simulation) in milliseconds.
- The time to eat in milliseconds.
- The time to sleep in milliseconds.
- (optional) The time each philosopher has to eat before the simulation stops.
### Technical considerations:
- Each philosopher has to be a thread.
- Each fork should be protected by a mutex.
- No Dataraces or memory leaks: Every variable getting accesed by more than one thread (or the main process), where at least one thread writes to the variable, has to be protected by a mutex.
- The death message should be the last message printed.
- The timestamps have to be in correct order.
### The bonus:
- Each philosopher has to be a process (the main process cannot be a philosopher).
- Semaphores have to be used instead of mutexes.
- The forks are in the middle of the table (two philosphers next to each other are allowed to eat at the same time).
- The forks have to be represented by a mutex.
### Limitations:
- More than 200 philosophers might lead to instability (much fewer for the bonus part).
- Too small times between eating and dying might lead to instability (./philo 4 401 200 200).
- Too small times to EAT/SLEEP/DIE might lead to instability.
- The execution depends a lot on the running computer, a computer on a heavy load might not execute the program properly.
---
## Installation and Usage
1. Clone the repository:
```shell
git clone https://github.com/itseugen/Philosophers
```
2. Enter the directory and build the program:
```shell
cd Philosophers/philo
make
```
Optional (if the pthread isn't linked automatically):
```shell
make debian
```
3. Execute the progam:
```shell
./philo [number_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_has_to_eat]
```
Example:
```shell
./philo 4 800 200 200 6
```
Optional: Execute the bonus
```shell
cd ../philo_bonus
make
./philo_bonus [number_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_has_to_eat]
```
---
<sub><sup>This project is part of my studies at 42 Heilbronn</sup></sub>