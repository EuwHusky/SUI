/**
 ******************************************************************************
 * @file    simple_ui.h
 * @author  Enoky Bertram
 * @version V0.0.0 dev1
 * @date    Jun.4.2023
 * @brief   A Simple UI Switcher /一个简易用户界面
 * @note    happyhappyhappy
 ******************************************************************************
 */

#ifndef __SIMPLE_UI_H_
#define __SIMPLE_UI_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*在下面这里添加自定义头文件*/

#include <windows.h>

/*在上面这里添加自定义头文件*/

#define NUM_OF_FIRST_LEVEL_ITEMS 3
#define NUM_OF_SECOND_LEVEL_ITEMS 5
#define NUM_OF_UNIT_LEVEL_ITEMS 7

typedef enum SimpleUiNodeType
{
    SUI_MENU,    // 菜单项
    SUI_DISPLAY, // 可操作项 操作类型-显示
    SUI_SWITCH,  // 可操作项 操作类型-切换
    SUI_ADJUST,  // 可操作项 操作类型-调整
} simple_ui_node_type_e_t;

typedef enum SimpleUiMenuOperation
{
    SUI_NEXT_PAGE,
    SUI_PRE_PAGE,
    SUI_NEXT_ITEM,
    SUI_PRE_ITEM,
    SUI_SELECT_ITEM,
} simple_ui_menu_operation_e_t;

typedef struct SimpleUIInfo
{
    simple_ui_node_type_e_t node_type; // 节点类型

    char name[20]; // 节点名称
    void *data;    // 节点数据

    uint8_t first_level_index;
    uint8_t seconde_level_index;
    uint8_t third_level_index;
} simple_ui_info_s_t;

typedef struct SimpleUINode
{
    simple_ui_info_s_t info; // 节点信息

    struct SimpleUINode *parent;       // 父节点指针
    struct SimpleUINode *first_child;  // 第一个子节点指针
    struct SimpleUINode *next_sibling; // 下一个兄弟节点指针
} simple_ui_node_s_t;

typedef struct SimpleUI
{
    uint8_t ui_tree_size;

    simple_ui_node_s_t **ui_tree;

    uint8_t number_of_first_level_item;
    uint8_t number_of_seconde_level_item;
    uint8_t number_of_third_level_item;

    uint8_t first_level_index;
    uint8_t seconde_level_index;
    uint8_t third_level_index;
} simple_ui_s_t;

typedef enum SimpleUiError
{
    SUI__OK = 0,
    SUI__ADD_FIRST_LEVEL_ITEM_ERROR__EXISTING_ITEM,
    SUI__ADD_SECOND_LEVEL_ITEM_ERROR__EXISTING_ITEM,
    SUI__ADD_SECOND_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST,
    SUI__ERROR,
    SUI_ERROR = 1,
} simple_ui_error_e_t;

simple_ui_error_e_t SUI_Init(simple_ui_s_t *ui);
simple_ui_error_e_t SUI_AddFirstLevelItem(simple_ui_s_t *ui, const char *name, uint8_t first_level_index);

#endif /* __SIMPLE_UI_H_ */
