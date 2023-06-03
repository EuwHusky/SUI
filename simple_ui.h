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

typedef enum UnitType
{
    DISPLAY,
    SWITCH,
    ADJUST,
} unit_type_e_t;

typedef enum MenuOperation
{
    NEXT_PAGE,
    PRE_PAGE,
    NEXT_ITEM,
    PRE_ITEM,
    SELECT_ITEM,
} menu_operation_e_t;

/**
 * @brief UI 最小可操作单位
 */
typedef struct Unit
{
    unit_type_e_t unit_type;
};

/**
 * @brief UI 结构体
 */
typedef struct SimpleUi
{
    uint8_t number_of_first_level_menu_pages; // 一级菜单页数
} simple_ui_s_t;

#endif /* __SIMPLE_UI_H_ */
