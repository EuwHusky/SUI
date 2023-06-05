/**
 ******************************************************************************
 * @file    simple_ui.c/h
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

typedef enum SimpleUiUnitType
{
    DISPLAY,
    SWITCH,
    ADJUST,
} simple_ui_unit_type_e_t;

typedef enum SimpleUiMenuOperation
{
    NEXT_PAGE,
    PRE_PAGE,
    NEXT_ITEM,
    PRE_ITEM,
    SELECT_ITEM,
} simple_ui_menu_operation_e_t;

typedef enum SimpleUiError
{
    OK = 0,
    SUI_ERROR,
} simple_ui_error_e_t;

/**
 * @brief UI 最小可操作单位
 */
typedef struct SimpleUiUnit
{
    char name[10]; // 名称

    simple_ui_unit_type_e_t unit_type; // 可操作单位类型
} simple_ui_unit_level_s_t;

/**
 * @brief UI 次级菜单项结构体
 */
typedef struct SimpleUiSecondLevelItem
{
    char name[10]; // 名称

    uint8_t number_of_unit_level_menu_pages; // 单元层菜单页数

    simple_ui_unit_level_s_t (*unit_level_menu)[NUM_OF_UNIT_LEVEL_ITEMS];
} simple_ui_second_level_item_s_t;

/**
 * @brief UI 一级菜单项结构体
 */
typedef struct SimpleUiFirstLevelItem
{
    char name[10]; // 名称

    uint8_t number_of_second_level_menu_pages; // 次级菜单页数

    simple_ui_second_level_item_s_t (*second_level_menu)[NUM_OF_SECOND_LEVEL_ITEMS]; //[次级菜单页][次级菜单项]
} simple_ui_first_level_item_s_t;

/**
 * @brief UI 结构体
 */
typedef struct SimpleUi
{
    uint8_t number_of_first_level_menu_pages; // 一级菜单页数

    simple_ui_first_level_item_s_t (*first_level_menu)[NUM_OF_FIRST_LEVEL_ITEMS]; //[一级菜单页][一级菜单项]

    /**
     * @brief 索引
     * [0] UI所在层级
     * [1] 一级菜单所在页
     * [2] 一级菜单所在项
     * [3] 次级菜单所在页
     * [4] 次级菜单所在项
     * [5] 三级菜单所在页
     * [6] 三级菜单所在项
     */
    uint8_t index[7];
} simple_ui_s_t;

simple_ui_error_e_t SUI_Init(simple_ui_s_t *ui, uint8_t number_of_first_level_menu_pages);
simple_ui_error_e_t SUI_AddFirstLevelItem(simple_ui_s_t *ui, uint8_t first_level_page_index,
                                          uint8_t first_level_item_index, char name[10],
                                          uint8_t number_of_second_level_menu_pages);
void SUI_Run(simple_ui_s_t *ui);

#endif /* __SIMPLE_UI_H_ */
