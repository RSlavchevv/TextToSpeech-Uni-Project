// Извикваме всички нужни библиотеки 
#include <stdio.h>   // за printf, scanf, FILE 
#include <stdlib.h>  // за malloc, free, system 
#include <string.h>  // за strcmp, strlen, strcat 
#include <unistd.h> //  за sleep 

//Дефинира константа MAX_TEXT_LINE което означава че програмата поддържа до 100 реда текст
//Това се използва за оразмеряване на масиви и цикли
#define MAX_TEXT_LINE 100     // Макс. брой редове които се поддържат
#define MAX_TEXT_LENGTH 256 // Макс. дължина на един ред текст


// 1) Структура 
// Тази структура InputText ще ми помагне да държа информацията за всеки ред
// Съдържа само един указател Stringline, който ще сочи към динамично алокирана памет за текста
typedef struct
{
    char *Stringline;  // Пойнтър за динамично алокиране на памет където ще се държи реалния текст на всеки ред.
} InputText;


// 2) Bubble Sort
// Тази функция Bubble сортира масива от структурата InputText по азбучен ред
// използвайки класическия алгоритъм Bubble Sort

void Bubble(InputText *arr, int n)
{
    // Външен for цикъл който се върти от 0 до n-1
    // След всяко завъртане най-големият (по strcmp) ред "отива" в края
    for (int i = 0; i < n - 1; i++)
    {
        // Вътрешеният for цикъл: обхожда двойки съседни елементи
        // и разменя ако не са в правилния ред
       for (int j = 0; j < n - i - 1; j++)
    {
        // Ако arr[j].Stringline е по-голям"(strcmp > 0) от arr[j+1].Stringline,
        // се разменят
        if (strcmp(arr[j].Stringline, arr[j + 1].Stringline) > 0)
        {
            // temp е временна променлива която временно задържа стойността на arr[j]
            InputText temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
    }

    }
}

// 3) Функция която пише 
// Тази функция SafetoFile позволява на програмата да записва текст във файл
// Потребителят въвежда редове докато не се въведе "STOP"
void SavetoFile(const char *filename)
{
    //fp е указател към файлов поток а условието if (fp == NULL) проверява дали файлът е успешно отворен за запис
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        // Ако не могже да се отвори файла отпечатвам съобщение на потребителят за грешка като задавам return с цел да излезе от функцията
        printf("Error opening file for writing!\n");
        return;
    }
    printf("Enter lines of text (type 'STOP' on a line to finish):\n");

// while (1) създава безкраен цикъл който продължава да чете вход от потребителя, докато не настъпи условие за прекъсване
// Чрез безкраен цикъл е basic начин да се обработва вход с неизвестна дължина прекъсвайки цикъла само при определени събития
// Този безкраен цикъл чете редове от стандартния вход докато не срещне "STOP".
    while (1)
    {
        // UserInput е масив, в който ще се чете всеки ред който е въвел потребителя
        char UserInput[MAX_TEXT_LENGTH];
        //fgets чете ред и го записва в UserInput
        if (fgets(UserInput, sizeof(UserInput), stdin) == NULL)
        {
            break; 
        }
        // Проверявамe дължината на прочетения ред.
        size_t len = strlen(UserInput);
        // Ако последният символ е "\n" го заменямe с '\0' (край на string)
        if (len > 0 && UserInput[len - 1] == '\n')
        {
            UserInput[len - 1] = '\0';
        }
        // Ако e въведено "STOP" цикъла спира
        if (strcmp(UserInput, "STOP") == 0)
        {
            break;
        }
        // Ако програмата не прочете "STOP" записва се прочетения ред във файла като добавяме нов ред  \n
        // за да запиша всеки ред от входният текст на нов ред във файла
        fprintf(fp, "%s\n", UserInput);
    }
    // Затваря файла с цел да може информацията да се запише коректно
    fclose(fp);
    printf("Text saved to %s\n", filename);
}

// 4) Функция четене от файл
// Тази функция readFromFile прочита редове от файл
// и ги записва в динамично алокирания масив от InputText.
int readFile(const char *filename, InputText *ArrInput, int maxLines)
{
    // Отваря файла в режим четене ("r").
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
         // Ако не може да се отвори файлът печатам грешка и връщам 0 (тоест че са прочетени нула редове).
        printf("Error opening file for reading!\n");
        return 0;
    }
    // брояч колко реда е прочела програмата - counter
    int addUp = 0;
    // Ще се четът ред по ред докато не стигне дефинираната стойност на maxLines или края на файла.
    while ( addUp < maxLines)
    {
         // Използвам fgets за да прочета ред в ArrInput[addUp].StringLine.
        if (fgets(ArrInput[addUp].Stringline, MAX_TEXT_LENGTH, fp) == NULL)
        {
             // Ако не може да прочете ред излизаме от цикъла
            break;  
        }
        // проверявам дължината и махам '\n' накрая ако го има.
        size_t len = strlen(ArrInput[addUp].Stringline);
        // Проверяваме дали низът не е празен и дали последният му символ е нов ред (\n).
        // Ако е така, заменяме новия ред с терминиращ символ (\0).
        if (len > 0 && ArrInput[addUp].Stringline[len - 1] == '\n')
        {
            ArrInput[addUp].Stringline[len - 1] = '\0';
        }
         // Инкрементирам брояча на прочетени редове
        addUp++;
    }
     // Затварям файла след приключване на четенето
    fclose(fp);
    // Връща броя редове които са прочетени
    return addUp;
}

// 5) Функция която принтира на терминала вкаряният от потребителя текст
// Тази функция printTXT обхожда n на брой редове от
// масива ArrInput и ги отпечатва на екрана.
void printTXT(InputText *ArrInput, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", ArrInput[i].Stringline);
    }
}

// 6) От текст към глас - функция
// Функция textToGlas използва външна програма espeak, за да изговори текста
// language -> избор на език - БГ - АЕ и Испански (en, bg, es)
// pitch -> височина на гласа (0-99)
// generateWav -> ако е 1, генерира wav файл (output.wav), ако е 0, изговаря текста на момента
void textToGlas(const char *text, const char *language, int pitch, int generateWav)
{
    // textContainer създава масив от 512 символа който се използва за съхраняване на текст а след това се подава на system()
    char textContainer[512];
    // Ако generateWav == 1 програмата създава wav файл
    if (generateWav == 1)
    {
        // snprintf форматира данните и ги записва в буферната памет като гарантира че няма да се препълни паметта.
        snprintf(textContainer, sizeof(textContainer),
                 "espeak -w output.wav -v %s -p %d \"%s\"",
                 language, pitch, text);
        printf("Generating WAV file: output.wav\n");
    }
    else
    {
        // Ако не прави файл го изговаря на живо
        // Стартира еSpeek като изговаря въведеният текст
        snprintf(textContainer, sizeof(textContainer),
                 "espeak -v %s -p %d \"%s\"",
                 language, pitch, text);
        printf("Speaking text live...\n");
    }

    // Използваме system() за да извикаме еSpeak
    // Изпълнява командата в терминала
    system(textContainer);
}

// 7) Мейн функция на програмата
// Основната функция main тук се съдържа цялата логика на програмата.
int main(void)
{

    // Динамично заделям място за масив от InputText с вече дефинираният размер MAX_TEXT_LINE
    // sizeof(InputText) връща размера на структурата InputText в байтове,
    // за да гарантираме правилното количество памет за всяка структура в масива.
    InputText *ArrInput = malloc(MAX_TEXT_LINE * sizeof(InputText));
    if (ArrInput == NULL)
    {
         // Ако malloc не успее да алокира памет печатам на терминала грешка и прекъсвам програмата
        printf("Memory allocation failed for ArrInput.\n");
        return 1;
    }
      // За всеки елемент от ArrInput заделям допълнителна памет за StringLine
    // (по  символа за всеки ред).
    for (int i = 0; i < MAX_TEXT_LINE; i++)
    {
        ArrInput[i].Stringline = malloc(MAX_TEXT_LENGTH * sizeof(char));
        if (ArrInput[i].Stringline == NULL)
        {
            printf("Memory allocation failed for Stringline[%d].\n", i);
            // Ако не успея да заделя памет за конкретния ред трябва да освободя
            // всичко което съм заделил досега за да избегна memory leak
            for (int j = 0; j < i; j++)
            {
                free(ArrInput[j].Stringline);
            }
            free(ArrInput);
            return 1;
        }
    }
    // ReadedLines ще брои колко реда сме прочели от файл.
    int ReadedLines = 0;
    // filename е името на файла в който пишем и от който четем.
    char filename[50] = "mytext.txt";

    // // Безкраен цикъл който показва менюто на терминала и чака да изберем опция (от 1 до 7)
    while (1)
    {
        // Програмата печата менюто на терминала
        printf("\n-----------------------------------\n");
        printf(" Text-to-Speech in C \n");
        printf("-------------------------------------\n");
        printf("1) Write text to file\n");
        printf("2) Read text from file\n");
        printf("3) Sort text (Bubble Sort)\n");
        printf("4) Print text\n");
        printf("5) Text-to-Speech (live)\n");
        printf("6) Generate WAV file from text\n");
        printf("7) Exit\n");
        printf("Choose an option: ");

        // Променлива option, за да чета избора на потребителя.
        int option;
        // scanf работи с адреси благодарение на него програмата знае къде да запише въведената стойност
        scanf("%d", &option);
        // Чрез getchar()  се изчиства символа "\n" останал в буферната памет
        getchar(); 

        switch (option)
        {
            case 1:
                // 1) Запис във файл
                SavetoFile(filename);
                break;

            case 2:
                // 2) Четене от файл
                ReadedLines = readFile(filename, ArrInput, MAX_TEXT_LINE);
                printf("Read %d lines from %s\n", ReadedLines, filename);
                break;

            case 3:
                // 3) Сортиране (Bubble Sort)
                if (ReadedLines > 0)
                {
                    Bubble(ArrInput, ReadedLines);
                    printf("Text sorted.\n");
                }
            else
            {
            printf("No text to sort! Please read from file first.\n");
            }
            break;

            case 4:
                    // 4) Принтиране на текста
                    if (ReadedLines > 0)
                    {
                        printf("Printing all lines:\n");
                        printTXT(ArrInput, ReadedLines);
                    }
                else
                {
                    printf("No text to print! Please read from file first.\n");
                }
                break;

                case 5:
                        // 5) Изговаряне на живо (Text-to-Speech)
                if (ReadedLines > 0)
            {
                         printf("Select language:\n");
                         printf("1) English\n");
                         printf("2) Bulgarian\n");
                         printf("3) Spanish\n");

                int languageOption;
                scanf("%d", &languageOption);
                getchar();

                        const char *lang;
                        if (languageOption == 1) lang = "en";
                        else if (languageOption == 2) lang = "bg";
                        else if (languageOption == 3) lang = "es";
                        else lang = "en";

                        printf("Enter pitch (0-99 recommended): ");
                        int pitch;
                        scanf("%d", &pitch);
                        getchar();

            char fullText[2048] = "";
            for (int i = 0; i < ReadedLines; i++)
            {
                strcat(fullText, ArrInput[i].Stringline);
                strcat(fullText, ". ");
            }
            textToGlas(fullText, lang, pitch, 0); // 0 - изпълнява говор в момента
            }
            else
            {
            printf("No text to speak! Please read from file first.\n");
            }
            
            break;
    
    case 6:
        // 6) Генериране на WAV
        if (ReadedLines > 0)
        {
                            printf("Select language:\n");
                            printf("1) English\n");
                            printf("2) Bulgarian\n");
                            printf("3) Spanish\n");
                            int languageOption;
                            scanf("%d", &languageOption);
                             getchar();

            const char *lang;
            if (languageOption == 1) lang = "en";
            else if (languageOption == 2) lang = "bg";
            else if (languageOption == 3) lang = "es";
            else lang = "en";

                            printf("Enter pitch (0-99 recommended): ");
                            int pitch;
                            scanf("%d", &pitch);
                            getchar();

            char InputText[2048] = "";
            for (int i = 0; i < ReadedLines; i++)
            {
                strcat(InputText, ArrInput[i].Stringline);
                strcat(InputText, ". ");
            }

        textToGlas(InputText, lang, pitch, 1); // 1 -> генерира output.wav
        }
        else
        {
            printf("No text to convert to WAV! Please read from file first.\n");
        }
        break;

    case 7:
     // 7) Изход от програмата
                printf("Exiting program...\n");
                break;

    default:
        // Невалидна опция (Например ако потребителят въведе числото 8. Понеже няма 8 програмата изписва на терминала че избора не е правилен)
        printf("Invalid choice. Try again.\n");
        break;
    }
        // След всяка опция се чисти терминала за да може да е по пригледно изпълнението на програмата в терминала.
        sleep(5); // Пауза 5 секунди след изпълнението на избрана от потребителя опция
        system("clear");

        if(option == 7)
        {
            break; // излиза от безкрайния цикъл
        }
    }
    // Освобождаваме заетата паметта
    for (int i = 0; i < MAX_TEXT_LINE; i++)
    {
        free(ArrInput[i].Stringline);
    }
    free(ArrInput);

    return 0;
}