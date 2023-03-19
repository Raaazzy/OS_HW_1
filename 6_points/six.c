#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../library.h"

const int max_sym_size = 5000;

int main(int argc, char *argv[]) {
    char buffer[max_sym_size];
    if (argc != 3) {
        printf("Please run the program with 2 arguments: names for input and output files.\n");
        return 0;
    }
    int size;
    int process;
    int first[2];
    int second[2];
    // Создаем первый канал для передачи первого процессa во второй
    if (pipe(second) < 0) {
        printf("ERROR: open second pipe\n");
        exit(1);
    }
    // Создаем первый канал для передачи второго процессa в третий
    if (pipe(first) < 0) {
        printf("ERROR: open pipe\n");
        exit(1);
    }
    // Cоздаем процессы два процесса
    process = fork();
    if (process < 0) {
        printf("ERROR: fork child\n");
        exit(1);
    } else if (process == 0) {
        // Второй процесс
        // Делим второй процесс на второй и третий
        if (close(second[1]) < 0) {
            printf("ERROR: close writing flow of pipe for child\n");
            exit(1);
        }
        // Считываем второй канал и записываем размер строки
        size = read(second[0], buffer, max_sym_size - 1);
        buffer[size] = '\0';
        // Проверяем на корректность
        if (size < 0) {
            printf("ERROR: read string from pipe\n");
            exit(1);
        }
        // Меняем заглавный буквы на строчные и наоборот
        change_register(buffer);
        // Проверяем на корректность
        if (close(second[0]) < 0) {
            printf("ERROR: close reading flow of pipe for child\n");
            exit(1);
        }
        // Записываем во второй канал
        size = write(first[1], buffer, max_sym_size);
        // Проверяем на корректность
        if (size != max_sym_size) {
            printf("ERROR: write all string to pipe\n");
            exit(1);
        }
        if (close(first[1]) < 0) {
            printf("ERROR: close writing flow of pipe for parent\n");
            exit(1);
        }
        exit(0);
    } else {
        // В первом процессе считываем информацию из файла
        // Направляем результат в первый поток, чтобы направить во второй процесс
        if (close(second[0]) < 0) {
            printf("ERROR: close reading flow of pipe for parent\n");
            exit(1);
        }
        int input_file = open(argv[1], O_RDONLY, 0666);
        // Проверяем на корректность
        if (input_file < 0) {
            printf("ERROR: open file\n");
            exit(1);
        }
        // Считываем информацию с файла
        size = read(input_file, buffer, max_sym_size);
        buffer[size] = '\0';
        // Проверяем на корректность
        if (close(input_file) < 0) {
            printf("ERROR: close file\n");
        }
        // Записываем в первый канал
        size = write(second[1], buffer, max_sym_size);
        // Проверяем на корректность
        if (size != max_sym_size) {
            printf("ERROR: write all string to pipe\n");
            exit(1);
        }
        if (close(second[1]) < 0) {
            printf("ERROR: close writing flow of pipe for parent\n");
            exit(1);
        }
    }
    // Первый процесс
    // Считаем результат выполнения функции второго канала
    // Выводим результат выполнения
    while (wait(NULL) > 0) {
    }
    // Проверяем на корректность
    if (close(first[1]) < 0) {
        printf("ERROR: close writing flow of pipe for child\n");
        exit(1);
    }
    // Считываем второй канал
    size = read(first[0], buffer, max_sym_size - 1);
    buffer[size] = '\0';
    // Проверяем на корректность
    if (size < 0) {
        printf("ERROR: read string from pipe\n");
        exit(1);
    }
    if (close(first[0]) < 0) {
        printf("ERROR: close reading side of pipe for chiled\n");
        exit(1);
    }
    // Открываем файл для вывода
    int output_file = open(argv[2], O_WRONLY | O_CREAT, 0666);
    // Проверяем на корректность
    if (output_file < 0) {
        printf("ERROR: open file\n");
        exit(1);
    }
    // Записываем в файл
    size = write(output_file, buffer, strlen(buffer));
    // Проверяем на корректность
    if (size != strlen(buffer)) {
        printf("ERROR: write all string\n");
        exit(1);
    }
    if (close(output_file) < 0) {
        printf("ERROR: close file\n");
    }
    return 0;
}