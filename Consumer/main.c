#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "shm_com.h"



/*----------------------------------------------------------------------*/
/*         Очистка буфера ввода          */
/*---------------------------------------*/
void clearInputBuffer() 
{
    int c;

    // чтение символов из входного буфера до тех пор, пока не будет достигнут символ новой строки ('\n') или конец файла (EOF) 
    while ((c = getchar()) != '\n' && c != EOF) { }

    // символ равен новой строке или концу файла, while-цикл завершается. Управление передаётся основной функции
    return;
}

/*----------------------------------------------------------------------*/
/*     выблр действия пользователя   */
/*----------------------------------*/

void getchoice(char* choice,char* filepath_ish, char* filepath_shifr)                   // строка хранения пароля    
{
    memset(choice, 0, sizeof(*choice));             // очистка массива выбора пользователя
    scanf(" %s", choice);
   
    // бесконечный цикл ввода пароля
    while(true)
    {
        if((strlen(choice) == 1))                  // в ответе пользователя должна содержаться одна буква
        {
            // пользователь захотел поменять пароль
            if (choice[0] == 'A' || choice[0] == 'a') 
            {
               printf("Начинаем шифровать исходный файл: %s\n\n", filepath_ish);
               break;
            }

            // пользователь выбрал не менять пароль
            else if (choice[0] == 'B' || choice[0] == 'b')
            {
                printf("Начинаем расшифровывать зашифрованный файл: %s\n\n", filepath_shifr);
                break;                              // прерываем цикл - пароль установлен
            }

            else if(choice[0] == 'C' || choice[0] == 'c')
            {
                printf("\nЗавершение программы\n\n");
                exit(0);
            }

            // пользователь ввел неправильную букву выбора
            else
            {
                printf("Попробуйте ввести выбор заново - введённое значение не соответствует ни одному из предложенных\n");
                printf("*****\n");
                printf("Ввод: ");
                memset(choice, 0, sizeof(*choice)); // очистка массива выбора ввода
                scanf("%s", choice);               // просим повторить ввод - цикл начинается заново
            }// if
        }

        // пользователь ввел несколько символов при выборе
        else
        {   
            printf("Попробуйте ввести выбор заново - введённое значение не соответствует ни одному из предложенных\n");
            printf("*****\n");
            printf("Ввод: ");
            memset(choice, 0, sizeof(*choice));     // очистка массива выбора ввода
            scanf("%s", choice);                   // просим повторить ввод - цикл начинается заново
        }// if((strlen(choice) == 1))

    }// while()

    return;                                        // вернули обещанное значение
}

int main(int argc, char *argv[]) 
{

    if (argc < 5) 
    {
        fprintf(stderr, "Использование: ./<исполняемый файл> <путь_к_файлу_с_исходным кодом> <путь_к_файлу-шифратору>\n\t\t\t\t    <путь_к_зашифрованному_файлу> <путь_к_расшифрованному_файлу>\n");
        exit(EXIT_FAILURE);
    }

    char choice[100];                              // выбор пользователя
    char no_has_file = true;
    char encryptedFilePath[256]; // Переменная для нового пути к зашифрованному файлу
    char decryptedFilePath[256]; // Переменная для нового пути к расшифрованному файлу
    strcpy(encryptedFilePath, argv[3]);
    strcat(encryptedFilePath, "/shifr.txt");

    strcpy(decryptedFilePath, argv[4]);
    strcat(decryptedFilePath, "/translate.txt");

    // бесконечный цикл
    while(1)
    {

        system("clear");          // очищаем экран
        printf("Путь до файла для шифрования:\t\t\t  %s\n", argv[1]);
        printf("Путь до файла со случайной последовательностью:   %s\n", argv[2]);
        printf("Путь до зашифрованного файла:\t\t\t  %s\n", encryptedFilePath);
        printf("Путь до расшифрованного файла, если он создаётся: %s\n\n", decryptedFilePath);

        printf("Выберите действие:\n");
        printf("a) Зашифровать файл\n");
        printf("b) Расшифровать файл\n");
        printf("c) Выйти из программы\n\n");
        printf("Ввод: ");
        getchoice(choice, argv[1], encryptedFilePath);

        if (no_has_file && !(choice[0] == 'a' || choice[0] == 'A'))
        {
            printf("Сначала создайте файл с шифром\n");
            clearInputBuffer();
            getchar();                   // ожидаем ввода символа
            continue;
        }
        
        key_t key = ftok("/tmp", 'A');
        // Преобразуем key в строку
        char key_str[20];
        sprintf(key_str, "%d", (int)key);
        int segm;
        char segm_str[20];
        // дочерний процесс 1
        segm = 1;
        int shmid1 = shmget(key+segm, sizeof(struct shared_data_original), IPC_CREAT | 0666);
    
        if(shmid1 == -1)
        {
            perror("shmget провалилась\n");
            exit(EXIT_FAILURE);
        }

        struct shared_data_original *shared_memory1 = (struct shared_data_original *)shmat(shmid1, NULL, 0);
        printf("Указатель на сегмент 1 разделяемой памяти в родительской программе: %p\n", (void *)shared_memory1);
    
        if (shared_memory1 == (struct shared_data_original *)(-1)) 
        {
            perror("shmat провалилась");
            exit(EXIT_FAILURE);
        }

        segm = 2;
        sprintf(segm_str, "%d", (int)segm); // Преобразование int в строку
        int shmid2 = shmget(key+segm, sizeof(struct shared_data_code), IPC_CREAT | 0666);

        if(shmid2 == -1)
        {
            perror("shmget провалилась\n");
            exit(EXIT_FAILURE);
        }

        struct shared_data_code *shared_memory2 = (struct shared_data_code *)shmat(shmid2, NULL, 0);
        printf("Указатель на сегмент 2 разделяемой памяти в родительской программе: %p\n\n", (void *)shared_memory2);
    
        if (shared_memory2 == (struct shared_data_code *)(-1)) 
        {
            perror("shmat провалилась");
            exit(EXIT_FAILURE);
        }

        pid_t pid1 = fork();
        if (pid1 < 0) 
        {
            fprintf(stderr, "Ошибка при вызове fork()\n");
            exit(EXIT_FAILURE);
        }
        else if (pid1 == 0) 
        {
            // Дочерний процесс 1
            segm = 1;
            char segm_str[20];
            sprintf(segm_str, "%d", (int)segm); // Преобразование int в строку
            if(choice[0] == 'a' || choice[0] == 'A')
            {
                (void)execl("PROVIDER", "PROVIDER", argv[1], key_str, segm_str,  NULL);
            }
            else
            {
                (void)execl("PROVIDER", "PROVIDER", encryptedFilePath, key_str, segm_str,  NULL);
            }
        }

        else 
        {
            pid_t pid2 = fork();

            if (pid2 < 0) 
            {
                fprintf(stderr, "Ошибка при вызове fork()\n");
                return 1;
            } 
            else if (pid2 == 0) 
            {
                // Дочерний процесс 2
                segm = 2;
                char segm_str[20];
                sprintf(segm_str, "%d", (int)segm); // Преобразование int в строку
                (void)execl("PROVIDER", "PROVIDER", argv[2], key_str, segm_str,  NULL);
                exit(EXIT_FAILURE);
            } 
            else 
            {
                // Родительский процесс
                waitpid(pid1, NULL, 0); // Ожидание завершения работы дочернего процесса 1
                waitpid(pid2, NULL, 0); // Ожидание завершения работы дочернего процесса 2

                printf("Считанные данные родительской программой из сегмента 1:\n");
                printf("%s\n", shared_memory1->data);

                printf("Считанные данные родительской программой из сегмента 2:\n");
                printf("%s\n", shared_memory2->data);

                // Определение длины наименьшей считанной информации
                int len1 = strlen(shared_memory1->data);
                int len2 = strlen(shared_memory2->data);
                int min_len = (len1 < len2) ? len1 : len2;
                printf("Длина минимальной считанной строки: %i\n", min_len);
                // Создание результирующего массива и побитовая операция XOR
                char result[min_len + 1];
                for (size_t i = 0; i < min_len; i++) 
                {
                    result[i] = shared_memory1->data[i] ^ shared_memory2->data[i];
                }
                result[min_len] = '\0'; // Добавляем завершающий нуль-символ
                printf("Результат побитовой операции XOR:\n%s\n", result);

                if (choice[0] == 'a' || choice[0] == 'A') // Если выбрано зашифровать файл
                {
                    FILE *file = fopen(encryptedFilePath, "w"); // Открываем файл для записи (очищаем содержимое)
                    if (file == NULL) 
                    {
                        perror("Ошибка открытия файла");
                        exit(EXIT_FAILURE);
                    }
                    printf("Файл с шифром успешно создан\n");
                    // Запись информации в файл
                    fprintf(file, result);
                    fclose(file); // Закрываем файл
                    printf("Файл с шифром успешно заполнен\n");
                    no_has_file = false;
                }
                else
                {
                    FILE *file = fopen(decryptedFilePath, "w"); // Открываем файл для записи (очищаем содержимое)
                    if (file == NULL) 
                    {
                        perror("Ошибка открытия файла");
                        exit(EXIT_FAILURE);
                    }
                    printf("Файл с декодированием шифра успешно создан\n");
                    // Запись информации в файл
                    fprintf(file, result);
                    fclose(file); // Закрываем файл
                    printf("Файл с декодированием шифра успешно заполнен\n");
                }
                
                // Отсоединить общую память после использования
                shmdt(shared_memory1);
                shmdt(shared_memory2);
                // Освободить ресурсы общей памяти
                shmctl(shmid1, IPC_RMID, NULL);
                shmctl(shmid2, IPC_RMID, NULL);
            }

        }
        clearInputBuffer();
        getchar();                   // ожидаем ввода символа
    }
    return 0;
}