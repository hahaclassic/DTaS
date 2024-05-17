#ifndef __WRITER_H__
#define __WRITER_H__

#include <stdio.h>
#include <string.h>
#include "tree.h"

#define ENTER_FILE "\n\nВведите файл в формате '-rwxrwxrwx ДД.ММ.ГГГГ ЧЧ:ММ имя_файла': "

#define ENTER_DATE "\n\nВведите дату в формате 'ДД.ММ.ГГГГ ЧЧ:ММ': "

#define ENTER_FILE_NAME "\n\nВведите имя файла: "


#define STATISTICS  "\n=========================================================================================\n" \
                    "|                            Сравнение эффективности                                    |\n" \
                    "-----------------------------------------------------------------------------------------\n" \
                    "|                                                              |       Время, мкс       |\n" \
                    "|---------------------------------------------------------------------------------------|\n" \
                    "| Удаление из бин. дерева поиска, построенного по алфавиту     |   %-20lld |\n" \
                    "|---------------------------------------------------------------------------------------|\n" \
                    "| Перестроение в бинарное дерево поиска по дате                |   %-20lld |\n" \
                    "|---------------------------------------------------------------------------------------|\n" \
                    "| Удаление из бинарного дерева поиска, построенного по дате    |   %-20lld |\n" \
                    "|---------------------------------------------------------------------------------------|\n" \
                    "| Перестроение в BST по дате и удаление из него                |   %-20lld |\n" \
                    "=========================================================================================\n" 


#define ALPHABET_BST_BEFORE_DOT_FILE "./out/alphabet_before.dot"
#define ALPHABET_BST_AFTER_DOT_FILE "./out/alphabet_after.dot"
#define DATE_BST_BEFORE_DOT_FILE "./out/date_before.dot"
#define DATE_BST_AFTER_DOT_FILE "./out/date_after.dot"

void print_node(node_t *node, void *data);

void to_dot(node_t *node, void *param);

void export_to_dot(char *file_name, const char *tree_name, node_t *root);

void show_stats(unsigned long long alpha_tree_time, unsigned long long date_tree_time,
     unsigned long long convertation_time, unsigned long long deletion_time);

void print_tree(FILE *stream, node_t *root);

void print_date(FILE *stream, node_t *node);

#endif
