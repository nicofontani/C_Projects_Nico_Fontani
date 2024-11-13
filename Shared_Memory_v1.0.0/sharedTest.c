/******************************************************************************/
/*                                                                            */
/*                                SHARED MEMORY EXAMPLE                      */
/*                                                                            */
/* DESCRIZIONE:                                                               */
/* Questo programma dimostra come accedere e manipolare la memoria condivisa  */
/* in un ambiente multi-processo. Utilizza un segmento di memoria condivisa   */
/* identificato da una chiave predefinita (SHM_KEY), vi scrive un valore, e  */
/* poi crea un processo figlio che leggerà tale valore.                       */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Data di creazione: 13 Nov 2024                                             */
/*                                                                            */
/* Questo codice è stato sviluppato da Nico Fontani. È consentito             */
/* l'utilizzo e la modifica del codice, a condizione che ogni modifica venga  */
/* dichiarata. L'autore e la data devono essere aggiornati per riconoscere    */
/* il contributo di ciascun sviluppatore e mantenere una chiara tracciabilità */
/* delle versioni.                                                            */
/*                                                                            */
/* Autore originale: Nico Fontani                                             */
/* Data di ultima modifica: 13 Nov 2024                                        */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include "shared.h"  // Include the shared memory library

#define SHM_KEY 4242  // Shared memory key

int main(int argc, char* argv[]) {
    int shm_id;
    
    // Find the shared memory using the 'shared_find' function
    int* shared = (int*) shared_find(SHM_KEY, &shm_id);
    if (!shared) {
        perror("Error accessing shared memory");
        return -1;
    }

    // Write a value to shared memory and print it
    *shared = 42;
    printf("{%d} I read %d.\n", getpid(), *shared);

    // Prepare the command to execute the shared reader
    char* cmd[] = {"sharedReader", NULL};
    if (!fork()) {
        // Execute the command
        execvp(cmd[0], cmd);
        perror("Error executing execvp");
        exit(-2); // Exit with an error code if execvp fails
    }

    // Wait for the child process to terminate
    int status;
    if (waitpid(-1, &status, 0) == -1) {
        perror("Error in waitpid function");
        return -3;
    }

    if (WIFEXITED(status)) {
        printf("The child process terminated with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
