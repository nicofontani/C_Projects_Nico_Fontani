/******************************************************************************
 *                                                                            *
 *                                  SHARED.H                                  *
 *                                                                            *
 *                                                                            *
 * This file provides an interface for managing shared memory areas.          *
 * It contains functions for creating, finding, and removing shared memory    *
 * segments using IPC (Inter-Process Communication) keys.                     *
 *                                                                            *
 *                                                                            *
 * Copyright (c) 2024, Nico Fontani                                           *
 * Creation Date: 13 Nov 2024                                                 *
 *                                                                            *
 * This code was developed by Nico Fontani. Its use and modification are      *
 * permitted, provided that any changes are documented, and the author        *
 * and date are updated to recognize each developer's contribution            *
 * and maintain clear version tracking.                                       *
 *                                                                            *
 * Original Author: Nico Fontani                                              *
 * Last Modified: 13 Nov 2024                                                 *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#ifndef __SHARED_H
#define __SHARED_H

/* Function prototypes */

/* shared_create()
 * RECEIVES: IPC key and the size of the memory area to create.
 * RETURNS: A pointer to the shared memory area, or NULL on failure.
 *          The shared memory ID is returned via reference.
 */
void* shared_create(int ipc_key, int len, int* shm_id) {
    void* ret;

    *shm_id = shmget(ipc_key, len, IPC_CREAT | IPC_EXCL | 0666);
    if (*shm_id < 0)
        return NULL;
    
    ret = shmat(*shm_id, NULL, 0);
    return ret;
}

/* shared_find()
 * RECEIVES: IPC key.
 * RETURNS: A pointer to the shared memory area, or NULL on failure.
 *          The shared memory ID is returned via reference.
 */
void* shared_find(int ipc_key, int* shm_id) {
    void* ret;

    *shm_id = shmget(ipc_key, 0, IPC_EXCL);
    if (*shm_id < 0)
        return NULL;

    ret = shmat(*shm_id, NULL, 0);
    return ret;
}

/* shared_remove()
 * RECEIVES: The shared memory ID.
 * RETURNS: 0 on success, 1 on failure.
 */
int shared_remove(int shm_id) {
    int ret;
    ret = shmctl(shm_id, IPC_RMID, NULL);

    return ((ret != -1) ? 0 : 1);
}

#endif /* __SHARED_H */
