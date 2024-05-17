#include "operations.h"

#define NUM_OF_KEYWORDS 50

const char *keys[NUM_OF_KEYWORDS] = {
    "goto",
    "sizeof",
    "if",
    "int",
    "enum",
    "long",
    "namespace",
    "for",
    "register",
    "return",
    "short",
    "try",
    "const",
    "auto",
    "break",
    "case",
    "char",
    "continue",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
    "default",
    "do",
    "double",
    "else",
    "extern",
    "float",
    "signed",
    "static",
    "struct",

    "asm",
    "bool",
    "class",
    "delete",
    "export",
    "false",
    "friend",
    "inline",
    "new",
    "operator",
    "this",
    "true",
    "template",
    "using",
    "virtual",
    "private",
};

const char *values[NUM_OF_KEYWORDS] = {
    "Оператор безусловного перехода goto\nОператор goto передает управление программой оператору, помеченному меткой, которая задана в операторе goto.\n" \
    "Общая форма записи оператора goto имеет следующий вид:\n\n" \
    "goto метка;\n" \
    "\t...\n" \
    "метка:\n",

    "Оператор sizeof\n\nОператор sizeof может послужить в качестве оператора времени компиляции, используемого для определения размера (в байтах)\n" \
    "переменной или типа данных, включая классы, структуры и объединения. При использовании вместе с типом имя типа должно быть заключено в круглые\n" \
    "скобки.\n",

    "Условные операторы if/else\n\nУсловный оператор if позволяет менять направление выполняемых программой действий в зависимости\n" \
    "от результата проверки условия. Общая форма записи оператора if имеет следующий вид:\n\n" \
    "if(условие) {\n" \
	"\tблок_операторов_1\n" \
    "}\n" \
    "else {\n" \
	"\tблок_операторов_2\n" \
    "}\n\n" \
    "Если блок_операторов состоит только из одного оператора, в фигурных скобках необходимость отпадает. Оператор else необязателен.\n",

    "Тип данных int\n\nРазмер в байтах: 2(4)\nДиапазон: –32768 до 32767 (-2 147 483 648 до 2 147 483 647)\n",

    "enum (перечисления)\n\nПеречисление — это список именованных целочисленных констант. Таким образом, тип перечисления — \n" \
    "это спецификация списка имён, принадлежащих конкретному перечислению. Для создания перечисления используется ключевое слово enum.\n" \
    "Общая форма перечисления имеет следующий вид:\n\n" \
    "enum имя_перечисления {список_имён} список_переменных;\n\n" \
    "Здесь имя_перечисления — имя типа данного перечисления. В списке имён, как и в списке переменных, элементы списка отделяются один от другого запятыми.\n",

    "Тип данных long\n\nРазмер в байтах: 4\nДиапазон: -2 147 483 648 до 2 147 483 647\n",

    "Пространства имён. namespace\n\n" \
    "Ключевое слово namespace позволяет разделить глобальное пространство имен путем создания некоторой декларативной области. По сути,\n" \
    "пространство имен определяет область видимости. Общая форма задания пространства имен имеет следующий вид:\n\n" \
    "namespace имя {\n" \
	"\t//Объявления\n" \
    "}\n\n",

    "Цикл for\n\nЦикл for позволяет выполнить автоматическую инициализацию и увеличение переменной счетчика.\n" \
    "Общая форма записи такова: \n\n" \
    "for (инициализация; условие; инкремент) {\n" \
    "\t//блок_операторов\n" \
    "}\n" \
    "Если блок операторов состоит только из одного оператора, в фигурных скобках необходимость отпадает.\n",

    "register\n\nСпецификатор register просит, чтобы компилятор сохранил переменную способом, позволяющим осуществлять наибыстрейший доступ.\n" \
    "Для целых чисел и символов это обычно подразумевает размещение не в памяти, а в регистрах процессора. Для других типов переменных компилятор\n" \
    "может использовать другие способы для уменьшения времени доступа. Компилятор может просто игнорировать данную просьбу.\n",

    "Возврат значений (оператор return)\n\nВозврат значений в функции осуществляется с помощью оператора return. он имеет две формы записи:\n" \
    "\nreturn;\n" \
    "return значение;\n" \
    "В языке C99 и C++ форма оператора return, которая не задаёт возвращаемого значения, должна использоваться только в void-функциях.\n",

    "Тип данных short\n\nРазмер в байтах: 2\nДиапазон: –32768 до 32767\nИмеет псевдонимы short int, signed short и signed short int.\n",

    "Обработка исключений (try)\n\n" \
    "try {\n" \
	"\t//блок_trу\n" \
    "}\n" \
    "catch (тип1 arg) {\n" \
    "\t//блок_саtch_l\n" \
    "}\n" \
    "catch (тип2 arg) {\n" \
    "\t//блок_catch_2\n" \
    "}\n" \
    "catch (типЗ arg) {\n" \
    "\t//блок_сatch_3\n" \
    "}\n" \
    "// . . .\n"
    "catch (типN arg) {\n" \
    "//блок_catch_N\n" \
    "}\n", 

    "const\n\nОбъекты типа const не могут быть изменены программой во время её выполнения. Кроме того, объект,\n" \
    "адресуемый с помощью указателя, который определён как const, также не может быть модифицирован. Компилятор волен\n" \
    "поместить переменную этого типа в память, предназначенную только для чтения (read-only mem — ROM). Переменная,\n" \
    "определённая как const, получит своё значение либо из явной инициализации, либо посредством применения аппаратно-зависимых\n" \
    "методов.\n\nconst int a = 10;\n",

    "\033[36mauto\033[0m\n\nСпецификатор auto уведомляет компилятор о том, что локальная переменная, перед именем которой он стоит,\n" \
    "создаётся при входе в блок и разрушается при выходе из блока. Все переменные, определённые внутри функции, являются\n" \
    "автоматическими по умолчанию, и по этому ключевое слово auto используется крайне редко.\n",

    "Оператор break\n\nОператор break используется для выхода из циклов do, for и while в обход обычного условия выхода из цикла.\n" \
    "Он также используется для выхода из блока оператора switch. Ниже показан пример оператора break в цикле.\n",

    "Оператор case (в операторе switch)\n\nswitch (выражение) {\n" \
	"\tcase константа_1:\n" \
	"\t\tпоследовательность_операторов_1;\n" \
	"\t\t\tbreak;\n" \
	"\tcase константа_2:\n" \
    "\t\tпоследовательность_операторов_2;\n" \
	"\t\t\tbreak;\n" \
	"\t...\n" \
	"\tcase константа_N:\n" \
	"\t\tпоследовательность_операторов_N;\n" \
	"\t\t\tbreak;\n" \
	"\tdefault: default-операторы;\n" \
    "}\n",

    "Тип данных char\n\nРазмер в байтах: 1\nДиапазон: -128 - 127\n",

    "Оператор continue\n\nОператор continue используется для пропуска оставшихся операторов в теле цикла и передает управление\n" \
    "на следующую итерацию, которая начинается с вычисления условного выражения.\n",

    "Оператор switch\n\nswitch (выражение) {\n" \
	"\tcase константа_1:\n" \
	"\t\tпоследовательность_операторов_1;\n" \
	"\t\t\tbreak;\n" \
	"\tcase константа_2:\n" \
    "\t\tпоследовательность_операторов_2;\n" \
	"\t\t\tbreak;\n" \
	"\t...\n" \
	"\tcase константа_N:\n" \
	"\t\tпоследовательность_операторов_N;\n" \
	"\t\t\tbreak;\n" \
	"\tdefault: default-операторы;\n" \
    "}\n",

    "typedef\n\n" \
    "С помощью ключевого слова typedef можно создать новое имя для уже существующего типа. Общая форма записи такова:\n\n" \
    "typedef тип новое_имя_типа;\n\n",

    "Объединения\n\n" \
    "Объединения — это тип класса, в котором все данные разделяют одну и туже область памяти. В языке C++ объединение может включать как функции,\n" \
    "так и данные. Все члены объединения открыты по умолчанию. Для создания закрытых элементов необходимо использовать ключевое слово private.\n" \
    "Общая форма объявления объединения выглядит следующим образом:\n\n" \
    "union имя_класса {\n" \
	"\t//Открытые члены по умолчанию.\n" \
    "private:\n" \
	"\t//Закрытые члены.\n" \
    "} список_объектов;\n\n" \
    "Элементы объединения перекрывают друг друга\n",

    "Модификатор unsigned\n\nМодификатор unsigned указывает, что целочисленный тип беззнаковый\n",

    "void\n\nПустой тип данных\n",

    "volatile\n\n" \
    "Модификатор volatile сообщает компилятору, что значение переменной может быть изменено средствами, заданными в программе неявным образом.\n" \
    "Например, адрес глобальной переменной можно передавать системной процедуре отсчёта времени и обновлять после каждого тиканья системных часов.\n",

    "while\n\n" \
    "Для цикла while используется следующая общая форма:\n\n" \
    "whi1е(условие) {\n" \
	"\tблок_операторов\n" \
    "}\n\n" \
    "Если блок_операторов цикла while состоит только из одного оператора, фигурные скобки можно опустить.\n" \
    "При выполнении цикла while сначала проверяется условие. Следовательно, если условие дает ложный результат\n" \
    "при первой же проверке, тело цикла (блок_операторов) не выполняется ни разу. Элемент условие может быть любым выражением.\n",

    "Оператор default\n\nОператор default используется в операторе switch, чтобы сигнализировать о том, что, если в операторе\n" \
    "switch не обнаружится ни одного совпадения, будет выполнен блок кода, помеченный ключевым словом default.\n",

    "Цикл do\n\nОбщая форма записи цикла do имеет такой вид:\n\n" \
    "do {\n" \
    "\tблок_операторов\n" \
    "} while(условие);\n\n" \
    "Если при выполнении цикла повторяется только один оператор, то фигурные скобки можно опустить, хотя они вносят в этот оператор\n" \
    "определенную ясность. Цикл do — это единственный цикл в языке C++, который будет всегда иметь по крайней мере одну итерацию,\n" \
    "поскольку условие проверяется после выполнения тела цикла.\n",

    "Тип данных double\n\nРазмер в байтах: 8\nДиапазон: 1.7E-308 - 1.7E+308 (10 значащих цифр)\n",

    "Условные операторы if/else\n\nУсловный оператор if позволяет менять направление выполняемых программой действий в зависимости\n" \
    "от результата проверки условия. Общая форма записи оператора if имеет следующий вид:\n\n" \
    "if(условие) {\n" \
	"\tблок_операторов_1\n" \
    "}\n" \
    "else {\n" \
	"\tблок_операторов_2\n" \
    "}\n\n" \
    "Если блок_операторов состоит только из одного оператора, в фигурных скобках необходимость отпадает. Оператор else необязателен.\n",
    
    "extern\n\nЕсли спецификатор extern размещается перед именем переменной, компилятор будет 'знать', что переменная имеет внешнюю привязку,\n" \
    "т.е. что память для этой переменной выделена где-то в другом месте программы. Внешняя 'привязка' означает, что данный объект виден вне\n" \
    "его собственного файла. По сути, спецификатор extern сообщает компилятору лишь тип переменной, не не выделяя для неё области памяти.\n" \
    "Чаще всего спецификатор extern используется в тех случаях, когда одни и те же глобальные переменные используются в двух или более файлах.\n",

    "Тип данных float\n\nРазмер в байтах: 4\nДиапазон: 3.4E-38 - 3.4E+38 (6 значащих цифр)\n",

    "Модификатор signed\n\nМодификатор signed указывает, что целочисленный тип знаковый\n",

    "static\n\n" \
    "Спецификатор static указывает компилятору на хранение локальной переменной во время всего жизненного цикла программы вместо ее создания\n" \
    "и разрушения при каждом входе в область действия и выходе из неё. Следовательно, возведение локальных переменных в ранг статистических\n" \
    "позволяет поддерживать их значения между вызовами функций.\n" \
    "Модификатор ststic можно также применять к глобальным переменным. В этом случае область видимости такой переменной ограничивается файлом.\n",

    "Структуры\n\n" \
    "Структура создаётся с помощью ключевого слова struct. В языке C++ структура также определяет класс. Единственное различие между\n" \
    "class- и struct- объектами состоит в том, что по умолчанию все члены структуры являются открытыми. Чтобы сделать член закрытым,\n" \
    "необходимо использовать ключевое слово private. Общая форма объявления структуры имеет следующий вид:\n\n" \
    "struct имя_структуры: список_наследования {\n" \
	"\t//Открытые члены.\n" \
    "protected:\n" \
	"\t//Закрытые члены, которые могут быть унаследованы.\n" \
    "private:\n" \
	"\t//Закрытые члены.\n" \
    "} список_объектов;\n\n",

    "asm\n\n" \
    "Ключевое слово asm используется для вставки в С++-программу одной или нескольких инструкций ассемблерного кода.\n" \
    "Общая форма записи оператора asm имеет следующий вид:\n" \
    "asm(\"инструкция\");\n" \
    "Здесь элемент инструкция означает оператор языка Assembler, который передается непосредственно компилятору для сборки\n" \
    "в вашей программе.\n",

    "Спецификатор типа bool\n\n" \
    "Спецификатор типа bool используется для объявления в языке C++ логических значений(т.е. истина/ложь).\n",

    "class\n\n" \
    "Класс — это основной элемент инкапсуляции в языке C++. Класс определяется с помощью ключевого слова class. Переменные и функции образующие класс,\n" \
    "называются членами. Ниже показана общая форма записи класса:\n\n" \
    "class имя_класса : список_наследования {\n" \
	"\t//Закрытые члены, установленные по умолчанию.\n" \
    "private:\n" \
	"\t//Закрытые члены, установленные по умолчанию.\n" \
    "protected:\n" \
	"\t//Закрытые члены которые могут быть унаследованы\n" \
    "public:\n" \
	"\t//Открытые члены.\n" \
    "} список_объектов;\n\n",

    "Оператор delete\n\n" \
    "Оператор delete освобождает память, на которую указывает аргумент. Эта память предварительно должна быть выделена с помощью оператора new.\n" \
    "Общая форма оператора delete следующая: \n\n" \
    "delete p_var;\n\n" \
    "Здесь p_var — это указатель на ранее выделенную память.\n",

    "Ключевое слово export\n\n" \
    "Ключевое слово export может предварять объявление template. Оно позволяет другим файлам использовать шаблон, объявленый в другом файле путём\n" \
    "задания лишь его объявления (вместо дублирования его полного объявления).\n",

    "Ключевое слово false\n\n" \
    "Ключевое слово false в языке C++ представляет собой логическую константу, имеющую значение \"ложь\".\n",

    "friend\n\n" \
    "Ключевое слово friend предоставляет функции, не являющиеся членом класса, доступ к закрытым членам этого класса. Для создания функции необходимо\n" \
    "включить её прототип в открытый раздел объявления класса и предварить прототип ключевым словом friend.\n", 

    "Подставляемые (inline) функции\n\n" \
    "Спецификатор inline сообщает компилятору о намерении программиста поместить тело функции непосредственно в текст программы (вместо организации обычного вызова функции).\n" \
    "Спецификатор inline является \"заявкой\", а не командой, поскольку существуют определённые факторы, способные помешать встраиванию кода функции в текст программы.\n" \
    "Такие ограничения касаются рекурсивных функций, функций содержащих циклы или операторы switch, а также функции содержащие статистические данные.\n",

    "Оператор new\n\n" \
    "Оператор new выделяет динамическую память и возвращает указатель соответствующего типа на эту область памяти. Общая форма записи этого оператора такова:\n\n" \
    "p_var = new тип;\n\n",

    "Перегрузка операторов (operator)\n\n" \
    "Ключевое слово operator используется для создания перегруженных функций-операторов. Функции-операторы существуют в двух ипостасях: члена и не члена.\n" \
    "Общая форма записи функции-оператора как члена имеет следующий вид:\n\n" \
    "тип_возврата имя_класса :: operator # (список_параметров)\n" \
    "{\n" \
    "\t//...\n" \
    "}\n\n",

    "Ключевое слово this\n\n" \
    "Ключевое слово this используется для обозначения указателей на объект, который сгенерировал обращение к функции-члену.\n" \
    "Всем функциям-членам указатель this передаётся автоматически. Например.\n",

    "Ключевое слово true\n\n" \
    "Ключевое слово true в языке C++ представляет собой логическую константу, имеющую значение \"истина\".\n",

    "template\n\n" \
    "Ключевое слово template используется для создания обобщённых функций и классов. Тип данных, обрабатываемый обобщённой функцией или классом,\n" \
    "задаётся как параметр. Следовательно, одно определение функции или класса можно использовать с несколькими типами данных.\n",

    "Оператор using\n\n" \
    "Если члены пространства имен будут использоваться часто, то для упрощения доступа к ним можно применить директиву using.\n" \
    "Оператор using имеет две общие формы записи:\n\n" \
    "using namespace имя;\n" \
    "using имя::член;\n\n",

    "virtual\n\n" \
    "Спецификатор virtual создаёт виртуальную функцию. Виртуальная функция — это член базового класса, который может быть переопределён производным классом.\n" \
    "Если функция не переопределяется производным классом, используется определение базового класса.\n\n" \
    "virtual тип_возврата имя_функции(список_параметров) = 0;\n\n",


    "private\n\n" \
    "Спецификатор доступа определяет способ наследования базового класса. Приватные члены (private) не доступны для клиента\n",
};


void menu()
{
    fprintf(stdout, MENU);
}

operation_t choose_operation()
{
    int operation;
    
    while (true)
    {
        menu();
        fprintf(stdout, ENTER_OPERATION);
        __fpurge(stdin);
   
        int input = fscanf(stdin, "%d", &operation);

        if (input == 1 && operation >= 0 && operation <= COMPARE_MEMORY)
        {
            break;
        }
    
        err_message(ERR_INVALID_OPERATION);
    }

    return operation;
}


error_t init_structures(open_hash_table_t **open_hash_table, closed_hash_table_t **closed_hash_table,
    tree_node_t **tree, tree_node_t **balanced_tree)
{
    *open_hash_table = open_hash_table_create(DEFAULT_OPEN_TABLE_SIZE, hash_func);
    
    if (*open_hash_table == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    *closed_hash_table = closed_hash_table_create(DEFAULT_CLOSED_TABLE_SIZE, hash_func);

    if (*closed_hash_table == NULL)
    {
        open_hash_table_free(*open_hash_table);
        return ERR_MEMORY_ALLOCATION;
    }


    error_t err;
    for (size_t i = 0; i < NUM_OF_KEYWORDS; i++)
    {
        err = closed_hash_table_insert(*closed_hash_table, keys[i], values[i]);
        if (err)
        {
            break;
        }

        err = open_hash_table_insert(*open_hash_table, keys[i], values[i]);
        if (err)
        {
            break;
        }

        err = bst_insert_key(tree, NULL, keys[i], values[i]);
        if (err)
        {
            break;
        }

        err = bst_insert_key(balanced_tree, NULL, keys[i], values[i]);
        if (err)
        {
            break;
        }
    }

    if (err)
    {
        open_hash_table_free(*open_hash_table);
    }

    *balanced_tree = bst_balance(*balanced_tree);

    return err;
}


// FIND_DATA
error_t find_data(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t *tree, tree_node_t *balanced_tree) 
{
    char *data;
    char key[MAX_KEY_LEN + 20]; 
    size_t open_count = 0, closed_count = 0, tree_count = 0, balanced_tree_count = 0;
    error_t err;

    err = get_key(key);
    if (err)
    {
        return err;
    }

    err = open_hash_table_find(open_hash_table, &open_count, key, &data);
    if (err)
    {
        return err;
    }

    printf("\n\033[36m-----------------------------------------------------------------------------------------\033[0m\n");
    printf("%s", data);
    printf("\n\033[36m-----------------------------------------------------------------------------------------\033[0m\n\n");

    err = closed_hash_table_find(closed_hash_table, &closed_count, key, &data);
    if (err)
    {
        return err;
    }
    err = bst_find(tree, &tree_count, key, &data);
    if (err)
    {
        return err;
    }
    err = bst_find(balanced_tree, &balanced_tree_count, key, &data);
    if (err)
    {
        return err;
    }

    printf("Количество сравнений для хеш-таблицы с открытой адресацией: %s%zu%s\n", BLUE, open_count, CANCEL);
    printf("Количество сравнений для хеш-таблицы с закрытой адресацией: %s%zu%s\n", BLUE, closed_count, CANCEL);
    printf("Количество сравнений для несбалансированного дерева: %s%zu%s\n", BLUE, tree_count, CANCEL);
    printf("Количество сравнений для АВЛ-дерева: %s%zu%s\n", BLUE, balanced_tree_count, CANCEL);

    return STATUS_OK;
}

// INSERT_DATA
error_t insert_data(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t **tree, tree_node_t **balanced_tree)
{
    error_t err;
    char data[MAX_VALUE_LEN + 20];
    char key[MAX_KEY_LEN + 20]; 

    err = get_key_data(key, data);
    if (err)
    {
        return err;
    }

    err = closed_hash_table_insert(closed_hash_table, key, data);
    if (err)
    {
        return err;
    }
    err = open_hash_table_insert(open_hash_table, key, data);
    if (err)
    {
        return err;
    }
    err = bst_insert_key(tree, NULL, key, data);
    if (err)
    {
        return err;
    }
    err = bst_insert_key(balanced_tree, NULL, key, data);
    if (err)
    {
        return err;
    }

    *balanced_tree = bst_balance(*balanced_tree);

    printf("[OK]: Ключевое слово добавлено успешно.\n");
    return STATUS_OK;
}

// RESTRUCTURE_HASH_TABLES (change size of hash-tables)
error_t restructure_open_hash_table(open_hash_table_t *open_hash_table)
{
    error_t err;
    size_t new_size;

    err = get_table_size(open_hash_table->size, &new_size);
    if (err)
    {
        return err;
    }

    unsigned long long start, end;

    microseconds_now(&start);
    err = open_hash_table_restruct(open_hash_table, (size_t) new_size);
    microseconds_now(&end);
    if (err)
    {
        return err;
    }

    printf("Затраченное время: %llu мкс\n", end - start);
    printf("[OK]: Хеш-таблица реструктурирована успешно.\n");

    return STATUS_OK;
}


error_t restructure_closed_hash_table(closed_hash_table_t *closed_hash_table)
{
    error_t err;
    size_t new_size;

    err = get_table_size(closed_hash_table->size, &new_size);
    if (err)
    {
        return err;
    }

    unsigned long long start, end;

    microseconds_now(&start);
    err = closed_hash_table_restruct(closed_hash_table, (size_t) new_size);
    microseconds_now(&end);
    if (err)
    {
        return err;
    }

    printf("Затраченное время: %llu мкс\n", end - start);
    printf("[OK]: Хеш-таблица реструктурирована успешно.\n");

    return STATUS_OK;
}


error_t measure_search_time(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t *tree, tree_node_t *balanced_tree, search_stats_t *stats, const char *key)
{   
    char *data;
    error_t err;
    unsigned long long start, end;
    size_t open_count = 0, closed_count = 0, tree_count = 0, balanced_tree_count = 0;

    microseconds_now(&start);
    err = open_hash_table_find(open_hash_table, &open_count, key, &data);
    microseconds_now(&end);
    stats->open_hash_table_search_time = end - start;
    if (err)
    {
        return err;
    }
    
    microseconds_now(&start);
    err = closed_hash_table_find(closed_hash_table, &closed_count, key, &data);
    microseconds_now(&end);
    stats->closed_hash_table_search_time = end - start;
    if (err)
    {
        return err;
    }

    microseconds_now(&start);
    err = bst_find(tree, &tree_count, key, &data);
    microseconds_now(&end);
    stats->tree_search_time = end - start;
    if (err)
    {
        return err;
    }

    microseconds_now(&start);
    err = bst_find(balanced_tree, &balanced_tree_count, key, &data);
    microseconds_now(&end);
    stats->balanced_tree_search_time = end - start;
    if (err)
    {
        return err;
    }

    stats->open_hash_table_count = open_count;
    stats->closed_hash_table_count = closed_count;
    stats->tree_count = tree_count;
    stats->balanced_tree_count = balanced_tree_count;

    return STATUS_OK;
}

error_t measure_user_key_time(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t *tree, tree_node_t *balanced_tree, search_stats_t *stats)
{
    char key[MAX_KEY_LEN + 20]; 
    error_t err;

    err = get_key(key);
    if (err)
    {
        return err;
    }

    err = measure_search_time(open_hash_table, closed_hash_table, tree, balanced_tree, stats, key);
    if (err)
    {
        return err;
    }

    return STATUS_OK;
}


error_t measure_avg_search_time(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t *tree, tree_node_t *balanced_tree, avg_search_stats_t *stats)
{   
    error_t err;
    search_stats_t one_measurement;
    init_avg_stats(stats);

    for (size_t i = 0; i < closed_hash_table->size; i++)
    {
        if (strlen(closed_hash_table->data[i].key) != 0)
        {
            err = measure_search_time(open_hash_table, closed_hash_table, tree, balanced_tree,
                &one_measurement, closed_hash_table->data[i].key);

            if (err)
            {
                return err;
            }

            stats->open_hash_table_search_time += one_measurement.open_hash_table_search_time;
            stats->open_hash_table_count += one_measurement.open_hash_table_count;

            stats->closed_hash_table_search_time += one_measurement.closed_hash_table_search_time;
            stats->closed_hash_table_count += one_measurement.closed_hash_table_count;

            stats->tree_search_time += one_measurement.tree_search_time;
            stats->tree_count += one_measurement.tree_count;

            stats->balanced_tree_search_time += one_measurement.balanced_tree_search_time;
            stats->balanced_tree_count += one_measurement.balanced_tree_count;
        }
    }

    stats->open_hash_table_search_time /= (double) open_hash_table->len;
    stats->closed_hash_table_search_time /= (double) open_hash_table->len;
    stats->tree_search_time /= (double) open_hash_table->len;
    stats->balanced_tree_search_time /= (double) open_hash_table->len;
    stats->open_hash_table_count /= (double) open_hash_table->len;
    stats->closed_hash_table_count /= (double) open_hash_table->len;
    stats->tree_count /= (double) open_hash_table->len;
    stats->balanced_tree_count /= (double) open_hash_table->len;

    return STATUS_OK;
}

void сalc_memory(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table, memory_stats_t *stats)
{
    stats->open_hash_table_size = open_hash_table->size;
    stats->closed_hash_table_size = closed_hash_table->size;
    stats->tree_size = open_hash_table->len;
    stats->balanced_tree_size = open_hash_table->len;
    stats->len = open_hash_table->len;

    stats->closed_hash_table_memory = sizeof(closed_hash_table_t) + sizeof(block_t) * closed_hash_table->size;

    stats->open_hash_table_memory = sizeof(open_hash_table_t);
    bucket_node_t *curr;
    for (size_t i = 0; i < open_hash_table->size; i++)
    {
        curr = open_hash_table->data + i;
        while (curr != NULL)
        {
            stats->open_hash_table_memory += sizeof(bucket_node_t);
            curr = curr->next;
        }
    }

    stats->tree_memory = sizeof(tree_node_t) * open_hash_table->len;
    stats->balanced_tree_memory = sizeof(tree_node_t) * open_hash_table->len;
}

