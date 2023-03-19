# ИДЗ №1 по ОС (на 9 баллов)
Омирбекова Дария<br>
Группа БПИ-217<br>
Вариант 13

### Условие задачи:
Разработать программу, заменяющую все строчные буквы в заданной ASCII-строке прописными, а прописные буквы — строчными.

# Используемые файлы:
> [library.c](https://github.com/Raaazzy/OS_HW_1/blob/main/library.c) - файл с функцией, которая выполняет условие задачи. <br>
> Оставшиеся файлы с именами "i_points/name.c" организуют работу каналов и процессов. <br>
> i - в названии папки соответсвует баллу, на который выполнялась задача.

# Пояснения к запуску и эксплуатации:
Для запуска программы на определенный балл необходимо собрать программу со всеми сишными файлами в данной папке и с файлом, в котором находится функция, которая выполняет условие задачи:
```s
gcc i_points/name.c library.c
./a.out i_points/tests/input_i.txt i_points/tests/output_i.txt
```

# На 4 балла:
### Приведено условие задачи:
> [four.c](https://github.com/Raaazzy/OS_HW_1/blob/main/4_points/four.c)

### Приведены тестовые данные:
> [tests](https://github.com/Raaazzy/OS_HW_1/tree/main/4_points/tests)

### Представлена общая схема решаемой задачи:
Первый процесс считывает данные с файла, а далее передает их второму процессу через неименованный первый канал.<br>
Второй процесс является дочерним процессом первого. Он производит необходимые действия с полученными данными, а далее полученный результат отправляется во второй неименованный канал третьему процессу.<br>
Третий процесс является дочерним процессом второго. Он выводит результирующие данные со второго канала в файл.<br>

# На 5 баллов:
### Приведено условие задачи:
> [five.c](https://github.com/Raaazzy/OS_HW_1/blob/main/5_points/five.c)

### Приведены тестовые данные:
> [tests](https://github.com/Raaazzy/OS_HW_1/tree/main/5_points/tests)

### Представлена общая схема решаемой задачи:
Первый процесс считывает данные с файла, а далее передает их второму процессу через именованный первый канал (pipe_first.fifo).<br>
Второй процесс является дочерним процессом первого. Он производит необходимые действия с полученными данными из первого канала (pipe_first.fifo), а далее полученный результат отправляется во именованный второй канал третьему процессу (pipe_second.fifo).<br>
Третий процесс является дочерним процессом второго. Он выводит результирующие данные со второго канала (pipe_second.fifo) в файл.<br>

# На 6 баллов:
### Приведено условие задачи:
> [six.c](https://github.com/Raaazzy/OS_HW_1/blob/main/6_points/six.c)

### Приведены тестовые данные:
> [tests](https://github.com/Raaazzy/OS_HW_1/tree/main/6_points/tests)

### Представлена общая схема решаемой задачи:
Первый процесс считывает данные с файла, а далее передает их второму процессу через неименованный первый канал.<br>
Второй процесс является дочерним процессом первого. Он производит необходимые действия с данными, а далее передает их через неименнованный второй канал первому процессу.<br>
Далее первый процесс ждет выполнения действий во втором процессе и передачи данный во второй канал. После этого происходит считывание данных со второго канала и запись рехультата в файл.<br>

# На 7 баллов:
### Приведено условие задачи:
> [seven.c](https://github.com/Raaazzy/OS_HW_1/blob/main/7_points/seven.c)

### Приведены тестовые данные:
> [tests](https://github.com/Raaazzy/OS_HW_1/tree/main/7_points/tests)

### Представлена общая схема решаемой задачи:
Первый процесс считывает данные с файла, а далее передает их второму процессу через именованный первый канал (pipe_first.fifo).<br>
Второй процесс является дочерним процессом первого. Он производит необходимые действия с полученными данными из первого канала (pipe_first.fifo), а далее полученный результат отправляется в именованный второй канал первому процессу (pipe_second.fifo).<br>
Далее первый процес ждем выполнения действий во втором процессе и передачи данных во второй канал (pipe_second.fifo). После этого просхожит считывание данных со второго канала (pipe_second.fifo) и запись результата в файл.<br>

# На 8 баллов:
### Приведено условие задачи:
> [eight.c](https://github.com/Raaazzy/OS_HW_1/blob/main/8_points/eight.c)<br>
> [eight_addition.c](https://github.com/Raaazzy/OS_HW_1/blob/main/8_points/eight_addition.c)

### Приведены тестовые данные:
> [tests](https://github.com/Raaazzy/OS_HW_1/tree/main/8_points/tests)

### Представлена общая схема решаемой задачи:
В данной задачи процессы разделены на разные файлы:<br>
Первый процесс - eight.c<br>
Второй процесс - eight_addition.c<br><br>
Первый процесс считывает данные с файла, а далее передает их второму процессу через именованный первый канал (pipe_first.fifo).<br>
Второй процесс производит необходимые действия с полученными данными из первого канала (pipe_first.fifo), а далее полученный результат отправляется в именованный второй канал первому процессу (pipe_second.fifo).<br>
Далее первый процес ждем выполнения действий во втором процессе и передачи данных во второй канал (pipe_second.fifo). После этого просхожит считывание данных со второго канала (pipe_second.fifo) и запись результата в файл.<br>

# На 9 баллов:
### Приведено условие задачи:
> [nine.c](https://github.com/Raaazzy/OS_HW_1/blob/main/9_points/nine.c)<br>
> [nine_addition.c](https://github.com/Raaazzy/OS_HW_1/blob/main/9_points/nine_addition.c)

### Приведены тестовые данные:
> [tests](https://github.com/Raaazzy/OS_HW_1/tree/main/9_points/tests)

### Представлена общая схема решаемой задачи:
В данной задачи процессы разделены на разные файлы:<br>
Первый процесс - nine.c<br>
Второй процесс - nine_addition.c<br><br>
Первый процесс считывает данные с файла по частям (по 20 символов), а далее передает их второму процессу через именованный первый канал (pipe_first.fifo).<br>
Второй процесс производит необходимые действия с полученными данными (по 20 символов) из первого канала (pipe_first.fifo), а далее полученный результат отправляется в именованный второй канал первому процессу (pipe_second.fifo).<br>
Далее первый процес ждет выполнения действий во втором процессе и передачи данных во второй канал (pipe_second.fifo). После этого просходит считывание данных со второго канала (pipe_second.fifo) и запись результата в файл.<br>









