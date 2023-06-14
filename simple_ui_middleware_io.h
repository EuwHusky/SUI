/**
 ******************************************************************************
 * @file    simple_ui_middleware_io.h
 * @author  Enoky Bertram
 * @version v0.0.0 dev4
 * @date    Jun.6.2023
 * @brief   中间层 交互接口
 * @note    happyhappyhappy
 ******************************************************************************
 */

#ifndef __SIMPLE_UI_MIDDLEWARE_IO_H_
#define __SIMPLE_UI_MIDDLEWARE_IO_H_

#include "simple_ui_baseware.h"

typedef enum SimpleUiMenuOperation
{
    SUI_NEXT_PAGE,
    SUI_PRE_PAGE,
    SUI_NEXT_ITEM,
    SUI_PRE_ITEM,
    SUI_ENTER,
    SUI_RETURN,
    SUI_NO_ACTION,
} simple_ui_menu_operation_e_t;

void sui_display_page(const char *menu_name);
simple_ui_menu_operation_e_t sui_get_input();

#endif /* __SIMPLE_UI_MIDDLEWARE_IO_H_ */
