#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "timer.h"
#include "writer.h"
#include "reader.h"
#include "open_hash_table.h"
#include "closed_hash_table.h"
#include <stdio_ext.h>

#define MENU "\n=========================================================================================\n" \
             "| Работа с ключевыми словами языка С++ с помощью сбалансированных деревьев и хеш-таблиц |\n" \
             "-----------------------------------------------------------------------------------------\n" \
             "| Операции                                                                              |\n" \
             "|---------------------------------------------------------------------------------------|\n" \
             "| 1. Получить подсказку по введенному ключевому слову                                   |\n" \
             "| 2. Добавить новое ключевое слово                                                      |\n" \
             "| 3. Реструктурировать хеш-таблицы                                                      |\n" \
             "| 4. Вывести на экран хеш-таблицу с открытой адресацией                                 |\n" \
             "| 5. Вывести на экран хеш-таблицу с закрытой адресацией                                 |\n" \
             "| 6. Создать изображения (png) сбалансированного и несбалансированного дерева           |\n" \
             "| 7. Сравнение эффективности поиска в различных структурах данных                       |\n" \
             "| 8. Сравнение затрат памяти для различных структур данных                              |\n" \
             "|                                                                                       |\n" \
             "| 0. Выход из программы.                                                                |\n" \
             "-----------------------------------------------------------------------------------------\n" \

#define ENTER_OPERATION "\nВведите номер операции: "

typedef enum _operation
{
    /// Конец работы программы.
    END = 0,

    FIND_DATA,

    INSERT_DATA,

    RESTRUCTURE_HASH_TABLES, 

    PRINT_OPEN_HASH_TABLE, 
 
    PRINT_CLOSED_HASH_TABLE, 

    CREATE_PNG_TREES, 
    
    COMPARE_SEARCH, 

    COMPARE_MEMORY,

} operation_t;

operation_t choose_operation();

error_t init_structures(open_hash_table_t **open_hash_table, closed_hash_table_t **closed_hash_table,
    tree_node_t **tree, tree_node_t **balanced_tree);

error_t find_data(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t *tree, tree_node_t *balanced_tree);

error_t insert_data(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t **tree, tree_node_t **balanced_tree);

error_t restructure_hash_tables(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    restruct_stats_t *stats);

error_t measure_search_time(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table,
    tree_node_t *tree, tree_node_t *balanced_tree, search_stats_t *stats);

void сalc_memory(open_hash_table_t *open_hash_table, closed_hash_table_t *closed_hash_table, memory_stats_t *stats);

#endif
