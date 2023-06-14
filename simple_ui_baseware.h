/**
 ******************************************************************************
 * @file    simple_ui_base.h
 * @author  Enoky Bertram
 * @version v0.0.0 dev4
 * @date    Jun.6.2023
 * @brief   基础层
 * @note    happyhappyhappy
 ******************************************************************************
 */

#ifndef __SIMPLE_UI_BASE_H_
#define __SIMPLE_UI_BASE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*在下面这里添加交互接口所需头文件*/

#include <conio.h>

/*在上面这里添加交互接口所需头文件*/

#define DISPLAY_AREA_HEIGHT 8
#define DISPLAY_AREA_WIDTH 21

#define NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY 3
#define NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY 5
#define NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY 7

typedef enum SimpleUiMenuLevel
{
    SUI_FIRST = 1,
    SUI_SECOND,
    SUI_THIRD,
} simple_ui_menu_level_e_t;

typedef enum SimpleUiNodeType
{
    SUI_MENU,    // 菜单项
    SUI_DISPLAY, // 可操作项 操作类型-显示
    SUI_SWITCH,  // 可操作项 操作类型-切换
    SUI_ADJUST,  // 可操作项 操作类型-调整
} simple_ui_node_type_e_t;

#endif /* __SIMPLE_UI_BASE_H_ */