# Philosophers

The " Dining philosophers problem" is a problem about multiple philosophers each has one fork and in order to eat each needs 2 forks, therefore it is important to synchronize between them in order to feed them all if the time limit is favorable to do so. The philosophers is a representation of thread or process and the point of the project is to learn how to synchronize between them to create a functional program.

## Goal

 - Deepen the understanding of processes, threads and the diffrence between the two.
 - Leanr about mutexes and semaphores as tools to synchronize and managing resources for threads.


## Implementation Overview

- Each Philosopher is implemented as a thread (for them andatory part) or a process (for the bonus part), alternating between 3 actions: Eating, sleeping, thinking, and We MUST avoid DEADLOCK.
      A deadlock is when a thread keep waiting for a mutex for too long, or for better representation, when 2 philosophers each holds his fork and keep waiting for the other to drop his fork in order to eat, which result to neither eating and therefore both dying.
- They can do one action at a time.
- We manage the shared resources between the threads with mutexes to avoid a data races.
      data race occurs when 2 threads access the same shared variable, both changing on it or one changing and the other reading.
## Deployment

To deploy this project run

```bash
  Make
  ./philo number of philosophers time to die time to eat time to sleep number of time to eat(optional)
```
    ◦ number_of_philosophers: The number of philosophers and also the number
    of forks.
    ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
    milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
    ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
    During that time, they will need to hold two forks.
    ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
    ◦ number_of_times_each_philosopher_must_eat (optional argument): If all
    philosophers have eaten at least number_of_times_each_philosopher_must_eat
    times, the simulation stops. If not specified, the simulation stops when a
    philosopher dies.
