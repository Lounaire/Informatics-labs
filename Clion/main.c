#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_GROUP 10
#define MAX_PHONE 13


// Структура для хранения информации о студенте

typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    char group[MAX_GROUP];
    char phone[MAX_PHONE];
} Student;

// Глобальные переменные
Student students[MAX_STUDENTS];
int studentCount = 0;

// Прототипы функций
void addStudent();
void addMultipleStudents();
void deleteStudent();
void displayAllStudents();
void searchStudent();
void saveToFile();
void loadFromFile();
void clearBuffer();
void displayMenu();
void clearSreen();



int main(void) {
    int choice;

    // Загружаем данные из файла при запуске
    loadFromFile();

    do {
        displayMenu();
        printf("Выберите действие: ");
        scanf("%d", &choice);
        clearBuffer();
        clearSreen();

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                deleteStudent();
                break;

            case 3:
                displayAllStudents();
                break;

            case 4:
                searchStudent();
                break;

            case 5:
                saveToFile();
                break;

            case 6:
                addMultipleStudents();
                break;

            case 0:
                saveToFile();
                printf("Программа завершена.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }

    } while (choice != 0);

    return 0;
}

// Очистка буфера ввода
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Вывод меню
void displayMenu() {
    printf("\n======== База данных студентов ========\n");
    printf("\nМеню:\n");
    printf("1. Добавить студента\n");
    printf("2. Удалить студента\n");
    printf("3. Показать всех студентов\n");
    printf("4. Поиск студента\n");
    printf("5. Сохранить в файл\n");
    printf("6. Добавить несколько студентов\n");
    printf("0. Выйти\n");
}


// Добавление нового студента
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("База данных заполнена. Невозможно добавить нового студента.\n");
        return;
    }

    Student newStudent;
    newStudent.id = studentCount + 1;

    printf("Введите ФИО студента: ");
    fgets(newStudent.name, MAX_NAME, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Удаляем символ новой строки

    printf("Введите возраст студента: ");
    scanf("%d", &newStudent.age);
    clearBuffer();

    printf("Введите группу студента: ");
    fgets(newStudent.group, MAX_GROUP, stdin);
    newStudent.group[strcspn(newStudent.group, "\n")] = 0;

    printf("Введите телефон студента: ");
    fgets(newStudent.phone, MAX_PHONE, stdin);
    newStudent.phone[strcspn(newStudent.phone, "\n")] = 0;

    students[studentCount++] = newStudent;
    printf("Студент успешно добавлен.\n");
}


// Удаление студента
void deleteStudent() {
    int id, found = 0;

    if (studentCount == 0) {
        printf("База данных пуста.\n");
        return;
    }

    printf("Введите ID студента для удаления: ");
    scanf("%d", &id);
    clearBuffer();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;

            // Сдвигаем все записи
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
                // Обновляем ID
                students[j].id = j + 1;
            }

            studentCount--;
            printf("Студент успешно удален.\n");
            break;
        }
    }

    if (!found) {
        printf("Студент с ID %d не найден.\n", id);
    }
}

// Отображение всех студентов
void displayAllStudents() {
    if (studentCount == 0) {
        printf("База данных пуста.\n");
        return;
    }else {
        printf("\n╔═════╦══════════════════════════════╦═══════╦════════════════╦════════════════╗\n");
        printf("║ ID  ║ ФИО                          ║ Возр. ║ Группа         ║ Телефон        ║\n");
        printf("╠═════╬══════════════════════════════╬═══════╬════════════════╬════════════════╣\n");

        for (int i = 0; i < studentCount; i++) {
            printf("║ %-3d ║ %-28s ║ %-5d ║ %-14s ║ %-14s ║\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].group,
                students[i].phone);

            if (i < studentCount - 1) {
                printf("╠═════╬══════════════════════════════╬═══════╬════════════════╬════════════════╣\n");
            }
        }

        printf("╚═════╩══════════════════════════════╩═══════╩════════════════╩════════════════╝");
    }
}

// Поиск студента
void searchStudent() {
    char searchTerm[MAX_NAME];
    int found = 0;
    int searchChoice;

    if (studentCount == 0) {
        printf("База данных пуста.\n");
        return;
    }

    printf("\n======== Поиск студента ========\n");
    printf("1. Поиск по ID\n");
    printf("2. Поиск по имени\n");
    printf("3. Поиск по возрасту\n");
    printf("4. Поиск по группе\n");
    printf("5. Поиск по телефону\n");
    printf("0. Отмена\n");
    printf("Выберите тип поиска: ");
    scanf("%d", &searchChoice);
    clearBuffer();

    if (searchChoice == 0) {
        return;
    }

    printf("Введите строку для поиска: ");
    fgets(searchTerm, MAX_NAME, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    printf("\n╔═════╦══════════════════════════════╦═══════╦════════════════╦════════════════╗\n");
    printf("║ ID  ║ ФИО                          ║ Возр. ║ Группа         ║ Телефон        ║\n");
    printf("╠═════╬══════════════════════════════╬═══════╬════════════════╬════════════════╣\n");


    for (int i = 0; i < studentCount; i++) {
        int match = 0;
        char idStr[10], ageStr[10];
        switch (searchChoice) {
            case 1: // Поиск по ID
                sprintf(idStr, "%d", students[i].id);
                match = strstr(idStr, searchTerm) != NULL;
                break;
            case 2: // Поиск по имени
                match = strstr(students[i].name, searchTerm) != NULL;
                break;
            case 3: // Поиск по возрасту
                sprintf(ageStr, "%d", students[i].age);
                match = strstr(ageStr, searchTerm) != NULL;
                break;
            case 4: // Поиск по группе
                match = strstr(students[i].group, searchTerm) != NULL;
                break;
            case 5: // Поиск по телефону
                match = strstr(students[i].phone, searchTerm) != NULL;
                break;
            case 0:
                return;
            default:
                printf("Неверный выбор критерия. Попробуйте снова.\n");
                return;
        }

        if (match) {
            printf("║ %-3d ║ %-28s ║ %-5d ║ %-14s ║ %-14s ║\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].group,
                students[i].phone);

            if (found > 0) {
                printf("╠═════╬══════════════════════════════╬═══════╬════════════════╬════════════════╣\n");
            }
            found++;
        }
    }

    if (found > 0) {
        printf("╚═════╩══════════════════════════════╩═══════╩════════════════╩════════════════╝\n");
        printf("Найдено записей: %d\n", found);
    } else {
        printf("╚═════╩══════════════════════════════╩═══════╩════════════════╩════════════════╝\n");
        printf("Записей не найдено.\n");
    }
}

// Сохранение данных в файл
void saveToFile(){
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи\n");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);

    fclose(file);
    printf("Данные успешно сохранены в файл.\n");
}

// Загрузка данных из файла
void loadFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Файл не найден. Создана новая база данных.\n");
        return;
    }

    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);

    fclose(file);
    printf("Данные успешно загружены из файла.\n");
}

// Очистка экрана
void clearSreen() {
    #ifdef _WIN32
        system("cls");
    #else
    printf("\033[2J");
    printf("\033[H");
    #endif
}

void addMultipleStudents() {
    int count;

    if (studentCount > 0) {
        printf("База данных не пуста. Добавление нескольких студентов невозможно.\n");
        return;
    }

    printf("Введите количество студентов для добавления: ");
    scanf("%d", &count);
    clearBuffer();

    if (count <= 0) {
        printf("Неверное количество студентов.\n");
        return;
    }

    if (count > MAX_STUDENTS) {
        printf("Превышено максимальное количество студентов.\n");
        count = MAX_STUDENTS;
    }

    printf("Введите данные для %d студентов:\n", count);

    for (int i = 0; i < count; i++) {
        Student newStudent;
        newStudent.id = i + 1;

        printf("\n Студент %d:\n", i + 1);
        printf("Введите ФИО студента: ");
        fgets(newStudent.name, MAX_NAME, stdin);
        newStudent.name[strcspn(newStudent.name, "\n")] = 0;

        printf("Введите возраст студента: ");
        scanf("%d", &newStudent.age);
        clearBuffer();

        printf("Введите группу студента: ");
        fgets(newStudent.group, MAX_GROUP, stdin);
        newStudent.group[strcspn(newStudent.group, "\n")] = 0;

        printf("Введите телефон студента: ");
        fgets(newStudent.phone, MAX_PHONE, stdin);
        newStudent.phone[strcspn(newStudent.phone, "\n")] = 0;

        students[studentCount++] = newStudent;
    }

    printf("Добавлено %d студентов.\n", count);
}