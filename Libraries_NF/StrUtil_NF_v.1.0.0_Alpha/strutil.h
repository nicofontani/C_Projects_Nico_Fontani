/******************************************************************************/
/*                                                                            */
/*                            String Utility Library                          */
/*                                                                            */
/* DESCRIPTION:                                                               */
/* This library provides functions to manipulate strings in C, including      */
/* searching for characters, replacing characters, and concatenating strings. */
/* It simplifies common string operations in C and ensures safe memory usage. */
/*                                                                            */
/* Copyright (c) 2024, Nico Fontani                                           */
/* Creation Date: 8 Nov 2024                                                  */
/*                                                                            */
/* Original Author: Nico Fontani                                              */
/* Last Modified: 13 Nov 2024                                                 */
/*                                                                            */
/* Supported by C Programming                                                 */
/*                                                                            */
/******************************************************************************/

#ifndef STRUTIL_H
#define STRUTIL_H

#include <stdio.h>
#include <string.h>

/* Function prototypes */

/* Counts the occurrences of a character in a string */
int str_count(const char* str, char ch);

/* Replaces all occurrences of a character in a string with a new character */
void str_replace(char* str, char old_ch, char new_ch);

/* Concatenates two strings */
void str_concat(char* dest, const char* src);

/* Finds a substring within a string */
char* str_find(const char* str, const char* sub_str);

#endif /* STRUTIL_H */
