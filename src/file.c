#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"

/**
 * Loads a file into memory and returns a pointer to the data.
 * 
 * Buffer is not NUL-terminated.
 */
struct file_data *file_load(char *filename)
{
    char *buffer, *p;
    struct stat buf;
    int bytes_read, bytes_remaining, total_bytes = 0;

    // Get the file size
    if (stat(filename, &buf) == -1) {
        return NULL;
    }

    // TODO: file check, update for Centos7
    // Make sure it's a regular file
    /* 
    if (!(buf.st_mode & S_IFREG)) {
        return NULL;
    } 
    */

    // Open the file for reading
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        return NULL;
    }

    // Allocate that many bytes
    bytes_remaining = buf.st_size;
    p = buffer = malloc(bytes_remaining);

    if (buffer == NULL) {
        fclose(fp);
        return NULL;
    }

    // Read in the entire file
    while (bytes_read = fread(p, 1, bytes_remaining, fp), bytes_read != 0 && bytes_remaining > 0) {
        if (bytes_read == -1) {
            free(buffer);
            fclose(fp);
            return NULL;
        }

        bytes_remaining -= bytes_read;
        p += bytes_read;
        total_bytes += bytes_read;
    }

    // Allocate the file data struct
    struct file_data *filedata = malloc(sizeof *filedata);

    if (filedata == NULL) {
        free(buffer);
        fclose(fp);
        return NULL;
    }

    filedata->data = buffer;
    filedata->size = total_bytes;

    // TODO: fclose, redundancy check
    fclose(fp);

    return filedata;
}

void file_write(char *filename, char *comment) 
{
    FILE *f = fopen(filename, "a");
    fputs(comment, f);
    fclose(f);
}

/**
 * Frees memory allocated by file_load().
 */
void file_free(struct file_data *filedata)
{
    free(filedata->data);
    free(filedata);
}