#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

const char *first_pipe = "first_pipe.fifo";
const char *second_pipe = "second_pipe.fifo";

const int max_sym_size = 5000;

int main(int argc, char *argv[]) {
    char buffer[max_sym_size];
    (void) umask(0);
    if (argc != 3) {
        printf("Please run the program with 2 arguments: names for input and output files.\n");
        return 0;
    }
    int size;
    int first;
    int second;
    mknod(first_pipe, S_IFIFO | 0666, 0);
    mknod(second_pipe, S_IFIFO | 0666, 0);
    int input_file = open(argv[1], O_RDONLY, 0666);
    // Проверяем на корректность
    if (input_file < 0) {
        printf("ERROR: open file\n");
        exit(1);
    }
    // Cчитываемние из файла
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
    // Записыем в первый канал
    size = write(first, buffer, max_sym_size);
    // Проверяем на корректность
    if (size != max_sym_size) {
        printf("ERROR: write all string to FIFO\n");
        exit(1);
    }
    if (close(first) < 0) {
        printf("ERROR: close writing side of FIFO for parent\n");
        exit(1);
    }
    // Первый процесс
    // Считаем результат выполнения функции второго канала
    // Выводим результат выполнения
    second = open(second_pipe, O_RDONLY);
    if (second < 0) {
        printf("ERROR: open FIFO for reading\n");
        exit(1);
    }
    // Считаем результат выполнения функции через второй канал
    // Выводим результат
    size = read(second, buffer, max_sym_size - 1);
    buffer[size] = '\0';
    // Проверяем на корректность
    if (size < 0) {
        printf("ERROR: read string from FIFO\n");
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
    return 0;
}