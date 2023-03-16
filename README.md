# ИДЗ №1 по ОС (на 9 баллов)
Омирбекова Дария, группа БПИ-217<br>
Вариант 13

# Используемые файлы:
> папка с кодом - [code](https://github.com/Raaazzy/Home_work_4/tree/main/untitled4)

# Пояснения к запуску и эксплуатации:
Программа предложит ввести число от 3 до 10 - это количество островов, на которых пираты будут искать сокровище.
Количество пиратов всегда на 1 меньше, чем количество островов.

# На 4 балла:
### Приведено условие задачи:
Программа генерирует введенное количество островов и количество пиратов (на 1 меньше).
Далее каждому пирату выдается по одному или несколько участков, которые он должен будет обыскать. После обыска участка пират сообщает: нашел он клад на острове или нет.

### Описана модель параллельных вычислений, используемая при разработке многопоточной программы.
Была выбрана модель "портфель задач". Задача делится на конечное число подзадач: чтобы найти клад пиратам нужно обыскать участок. Распределение работ между потоками определяется динамически: пират (процесс) обыскивает свой участок и докладывает о наличии клада, если больше нетронутых участков нет, то пират прекращает обыск (процесс завершился). "Портфелем" в данном случае является определенный участок. Доступ к участку в определенный момент времени осуществляется только одним процессом (одним пиратом). Все процессы выполняют одну и ту же задачу - обыскивают участок.

### Описаны взодные данные программы, включающие вариативные диапазоны, возможные при многократных запусках.
Количество участков, на которые поделен остров - [3;10]

### Реализовано консольное приложение, решающее поставленную задачу с использованием одного варианта синхропримитивов.

### Ввод данных в приложение реализован с консоли.

# На 5 баллов:
### В программу добавлены комментарии, поясняющие выполняемые действия и описание используемых переменных.

### Приведен сценарий, описывающий одновременное поведение представленных в условии задания сущеностей в терминах предметной области.
Существует два класса: пиратов (Pirate) и участков островов (Island). У каждого пирата есть id и plan: id - индивидуальный номер пирата, plan - список участков, которые будет обыскивать пират. У каждого участка острова есть id и isThereTreasure: id - индивидуальный номер острова, isThereTreasure - флаг, определяющий есть ли на участке сокровище. <br>
Каждый пират представляет собой поток. В определенный момент времени только один пират имеет достук к одному участку острова, то есть код с логикой взимодействия пиратов и учатков блокируется мьютексом (pthread_mutex_lock). После данного взаимодействия мютекс снимается (phtread_mutex_unlock), что означает, что пират обыскал данный участок острова. Состояние пирата на данном острове выводится в консоль. Также в консоль выводится результат обыска участка. Все это происходит в методе PirateFunc. Каждый остров также представляется собой поток, его работа представляется аналогично работе пирата и осуществляется в методе IslandFunc. После того, как все участки обысканы, то выводится сообщение об окончании работы всех пиратов и остров, а также сообщение о том, на каких островах клад найден, а на каких - нет. 

# На 6 баллов:
### Обощенный алгорит:
Пользователь вводит количество участков, на которые стоит поделить остров.<br>
Программа генерирует эти n участков, и присваивает каждому участку состояние: "имеет сокровище" или "нет".<br>
Запускается n потоков с островами. <br>
Программа распределяет n-1 пиратов по n островам (одному из пиратов достается несколько участков).<br>
Запускается n-1 потоков с пиратами. Они начинаются обыскивать острова. Выводятся сообщения о состоянии обыска.<br>
После завершения работ на данном участке поток с участком завершается и выводится сообщение о проделанном труде (найдено сокровище на острове или нет).
После обыска всех участков завершаются и потоки пиратов.

### Реализован ввод данных с командной строки.










