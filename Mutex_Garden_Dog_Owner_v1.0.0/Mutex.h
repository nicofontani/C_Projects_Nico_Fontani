/******************************************************************************/
/*                                                                            */
/*                                Mutex Library                               */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This is a wrapper library for the functions in <sys/sem.h> to simplify the */
/* management of a mutex using semaphores. It provides functions for creating, */
/* locking, unlocking, and removing a mutex semaphore.                         */
/* Version: 2.0                                                               */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 13 Nov 2024                                                 */
/*                                                                            */
/* This code was developed by Nico Fontani. Its use and modification are      */
/* permitted, provided that any changes are documented, and the author        */
/* and date are updated to recognize each developer's contribution            */
/* and maintain clear version tracking.                                       */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/******************************************************************************/

#ifndef __MUTEX_H
#define __MUTEX_H

/*                      mutex.h
        Wrapper library for the functions in <sys/sem.h> 
                (simplifies mutex management)
*/

/* Prototypes */
int mutex_create (key_t ipc_key, int starting_value);
int mutex_find (key_t ipc_key);
int mutex_lock(int sem_id);
int mutex_unlock(int sem_id);
int mutex_remove(int sem_id);

/* Structs for the semop() system calls to modify the mutex value
   (semop() operates on a set of semaphores within an IPC structure) */
struct sembuf sem_lock = {
                0,              /* Position of the mutex in the semaphore set */
                -1,             /* Decrements the mutex value by one */
                SEM_UNDO };     /* The process will release the mutex even if there's an error */
                
struct sembuf sem_unlock = {
                0,              /* Position of the mutex in the semaphore set */
                +1,             /* Increments the mutex value by one */
                SEM_UNDO };     /* The process will release the mutex even if there's an error */

/* mutex_create()
   RECEIVES: The IPC key for the semaphore set and the initial value for the mutex
   RETURNS: A semaphore ID that identifies the mutex */
int mutex_create (key_t ipc_key, int starting_value) {
  int ret, sem_id;

  /* semget() creates a semaphore set
     ipc_key      --> Unique key for the IPC set
     1            --> Number of semaphores to create
     3rd parameter --> Operations to be performed in OR:
                      IPC_CREAT : Creates the IPC set
                      IPC_EXCL  : Returns an invalid value if the structure already exists
                      0666      : Read/Write access for all users (in octal) */
   sem_id = semget(ipc_key, 1, IPC_CREAT | IPC_EXCL | 0666);
   if (sem_id == -1)
     return (sem_id);  // Error: Creation failed

  /* semctl() performs operations on a semaphore set
      sem_id        --> ID of the semaphore set
      0             --> Position of the semaphore
      SETVAL        --> Operation to execute: set the semaphore value
      starting_value--> Initial value to set for the semaphore */
    ret = semctl(sem_id, 0, SETVAL, starting_value);

    if (ret == -1)
                return (ret);  // Error: Modification failed

    return (sem_id);
 }

/* mutex_find()
   RECEIVES: The IPC key for the semaphore set
   RETURNS: The ID of the semaphore set */
int mutex_find (key_t ipc_key) {
     /* semget() retrieves a semaphore set
     ipc_key      --> Unique key for the semaphore set
     The 2nd parameter is unused
     The 3rd parameter indicates no operations on the set */
  return semget(ipc_key, 0, 0);
 }

/* mutex_lock()
   RECEIVES: The semaphore set ID
   RETURNS: 0 on success */
int mutex_lock(int sem_id) {
     /* semop
         sem_id     --> ID of the semaphore set
         &sem_lock  --> Operation to perform
         1          --> Number of operations in the second argument */
    return semop(sem_id, &sem_lock, 1);
}

/* mutex_unlock()
   RECEIVES: The semaphore set ID
   RETURNS: 0 on success */
int mutex_unlock(int sem_id) {
     /* semop
         sem_id     --> ID of the semaphore set
         &sem_unlock  --> Operation to perform
         1          --> Number of operations in the second argument */
    return semop(sem_id, &sem_unlock, 1);
 }

/* mutex_remove()
   RECEIVES: The semaphore set ID
   RETURNS: 0 on success */
int mutex_remove(int sem_id) {
  /* semctl() performs control operations on a semaphore set
     sem_id       --> ID of the semaphore set
     2nd parameter --> Ignored
     IPC_RMID     --> Operation to REMOVE the semaphore set */
  return semctl(sem_id, 0, IPC_RMID);
}

#endif  /* __MUTEX_H */
