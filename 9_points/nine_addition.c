#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../library.h"

const int max_size = 200;
const int max_sym_size = 20;
const char *first_pipe = "first_pipe.fifo";
const char *second_pipe = "second_pipe.fifo";

int main(int argc, char *argv[]) {
    char buffer[max_size];
    mknod(first_pipe, S_IFIFO | 0666, 0);
    mknod(second_pipe, S_IFIFO | 0666, 0);
    int size;
    int first;
    int second = 0;
    // Первый процесс
    // Считываем информаицю и направляем в первый поток во второй процесс
    ssize_t read_bytes;
    ssize_t write_bytes = 0;
    first = open(first_pipe, O_RDONLY);
    // Проверяем на корректность
    if (first < 0) {
        printf("ERROR: open FIFO for reading\n");
        exit(1);
    }
    // Считываем из первого канала
    do {
        char mini_buffer[max_sym_size];
        read_bytes = read(first, mini_buffer, max_sym_size - 1);
        mini_buffer[read_bytes] = '\0';
        if (read_bytes == -1) {
            printf("ERROR: read from first\n");
            exit(1);
        }
        // Меняем заглавный буквы на строчные и наоборот
        change_register(mini_buffer);
        for (ssize_t i = write_bytes; i < write_bytes + read_bytes; ++i) {
            buffer[i] = mini_buffer[i - write_bytes];
        }
        write_bytes += read_bytes;
    } while (read_bytes == max_sym_size - 1);
    // Проверяем на корректность
    if (close(first) < 0) {
        printf("ERROR: close writing side of FIFO for parent\n");
        exit(1);
    }
    second = open(second_pipe, O_WRONLY);
    if (second < 0) {
        printf("ERROR: open FIFO-2 for writing\n");
        exit(1);
    }
    // Записываем во второй канал
    size = write(second, buffer, max_size);
    // Проверяем на корректность
    if (size != max_size) {
        printf("ERROR: write all string to FIFO\n");
        exit(1);
    }
    if (close(second) < 0) {
        printf("ERROR: close FIFO for parent\n");
        exit(1);
    }
    return 0;
}