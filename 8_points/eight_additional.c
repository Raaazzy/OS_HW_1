#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../library.h"

const char *first_pipe = "first_pipe.fifo";
const char *second_pipe = "second_pipe.fifo";

const int max_sym_size = 5000;

int main(int argc, char *argv[]) {
    char buffer[max_sym_size];
    mknod(first_pipe, S_IFIFO | 0666, 0);
    mknod(second_pipe, S_IFIFO | 0666, 0);
    int size;
    int second;
    // Второй процесс
    // Считываем первый канал
    // Напрвляем информацию во второй канал
    int first = open(first_pipe, O_RDONLY);
    // Проверяем на корректность
    if (first < 0) {
        printf("ERROR: open FIFO for reading\n");
        exit(1);
    }
    // Считываем из первого канала
    size = read(first, buffer, max_sym_size - 1);
    buffer[size] = '\0';
    // Проверяем на корректность
    if (size < 0) {
        printf("ERROR: read string from FIFO\n");
        exit(1);
    }
    // Меняем заглавный буквы на строчные и наоборот
    change_register(buffer);
    // Проверяем на корректность
    if (close(first) < 0) {
        printf("ERROR: close FIFO for child\n");
        exit(1);
    }
    second = open(second_pipe, O_WRONLY);
    // Проверяем на корректность
    if (second < 0) {
        printf("ERROR: open FIFO for writing\n");
        exit(1);
    }
    // Записываем во второй канал
    size = write(second, buffer, max_sym_size);
    // Проверяем на корректность
    if (size != max_sym_size) {
        printf("ERROR: write all string to FIFO\n");
        exit(1);
    }
    if (close(second) < 0) {
        printf("ERROR: close FIFO for parent\n");
        exit(1);
    }
    return 0;
}