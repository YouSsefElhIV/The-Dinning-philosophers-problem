# Philosophers

The " Dining philosophers problem" is a problem about multiple philosophers each has one fork and in order to eat each needs 2 forks, therefore it is important to synchronize between them in order to feed them all if the time limit is favorable to do so. The philosophers is a representation of thread or process and the point of the project is to learn how to synchronize between them to create a functional program.

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
