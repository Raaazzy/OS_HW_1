#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../library.h"

const int max_sym_size = 5000;

const char *first_pipe = "first_pipe.fifo";
const char *second_pipe = "second_pipe.fifo";

int main(int argc, char *argv[]) {
    char buffer[max_sym_size];
    if (argc != 3) {
        printf("Please run the program with 2 arguments: names for input and output files.\n");
        return 0;
    }
    int size;
    int process;
    int first;
    int second;
    mknod(first_pipe, S_IFIFO | 0666, 0);
    mknod(second_pipe, S_IFIFO | 0666, 0);
    second = 0;
    // Cоздаем процессы два процесса
    process = fork();
    if (process < 0) {
        printf("ERROR: fork child\n");
        exit(1);
    } else if (process == 0) {
        // Второй процесс
        // Делим второй процесс на второй и третий
        int result_1 = fork();
        if (result_1 < 0) {
            printf("ERROR: fork child\n");
            exit(1);
        } else if (result_1 == 0) {
            // Третий процесс
            // Печатаем результат выполнения в файл
            second = open(second_pipe, O_RDONLY);
            if (second < 0) {
                printf("ERROR: open FIFO for reading\n");
                exit(1);
            }
            // Считываем второй канал и записываем размер строки
            size = read(second, buffer, max_sym_size - 1);
            buffer[size] = '\0';
            // Проверяем на корректность
            if (size < 0) {
                printf("ERROR: read from FIFO\n");
                exit(1);
            }
            if (close(second) < 0) {
                printf("ERROR: close FIFO\n");
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
            // Удаляем pipe-ы из файловой системы
            unlink(first_pipe);
            unlink(second_pipe);
        } else {
            // Во втором процессе считываем информацию из файла
            // Производим необходимые изменения строки
            // Направляем получившийся результат во второй канал, чтобы передать в третий процесс
            if ((first = open(first_pipe, O_RDONLY)) < 0) {
                printf("ERROR: open FIFO for reading\n");
                exit(1);
            }
            // Считывание из первого канала
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
            if ((second = open(second_pipe, O_WRONLY)) < 0) {
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
                printf("ERROR: close FIFO for child\n");
                exit(1);
            }
        }
    } else {
        // В первом процессе считываем информацию из файла
        // Направляем результат в первый поток, чтобы направить во второй процесс
        int input_file = open(argv[1], O_RDONLY, 0666);
        if (input_file < 0) {
            printf("ERROR: open file\n");
            exit(1);
        }
        // Читаем файл и запоминаем размер
        size = read(input_file, buffer, max_sym_size - 1);
        buffer[size] = '\0';
        // Проверяем на корректность
        if (close(input_file) < 0) {
            printf("ERROR: close file\n");
        }
        if ((first = open(first_pipe, O_WRONLY)) < 0) {
            printf("ERROR: open FIFO for writing\n");
            exit(1);
        }
        // Записываем в первый канал
        size = write(first, buffer, max_sym_size);
        // Проверяем на корректность
        if (size != max_sym_size) {
            printf("ERROR: write all string to FIFO\n");
            exit(1);
        }
        if (close(first) < 0) {
            printf("ERROR: close writing flow of FIFO for parent\n");
            exit(1);
        }
    }

    return 0;
}