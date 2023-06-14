/**
 ******************************************************************************
 * @file    simple_ui.h
 * @author  Enoky Bertram
 * @version v0.0.0 dev5
 * @date    Jun.14.2023
 * @brief   A Simple UI/一个简易用户界面
 * @note    happyhappyhappy
 ******************************************************************************
 */

#ifndef __SIMPLE_UI_H_
#define __SIMPLE_UI_H_

#include "simple_ui_middleware_io.h"
#include "simple_ui_middleware_treenode.h"

enum SimpleUiStatus
{
    SUI_ENABLED,
    SUI_DISABLED,
};

typedef enum SimpleUiError
{
    SUI__OK = 0,

    SUI__ADD_FIRST_LEVEL_ITEM_ERROR__EXISTING_ITEM = 1,

    SUI__ADD_SECOND_LEVEL_ITEM_ERROR__EXISTING_ITEM = 2,
    SUI__ADD_SECOND_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST = 3,

    SUI__ADD_THIRD_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST = 4,
    SUI__ADD_THIRD_LEVEL_ITEM_ERROR__BELONGS_SECOND_LEVEL_ITEM_DOES_NOT_EXIST = 5,
    SUI__ADD_THIRD_LEVEL_ITEM_ERROR__EXISTING_ITEM = 6,
} simple_ui_error_e_t;

typedef struct SimpleUI
{
    uint8_t ui_tree_size;

    simple_ui_node_s_t **ui_tree;

    simple_ui_node_s_t *head_node;

    simple_ui_menu_level_e_t menu_level_index;
    uint8_t menu_page_index;
    uint8_t menu_item_index;

    simple_ui_menu_operation_e_t action;
    simple_ui_menu_operation_e_t last_action;

    uint8_t ui_status;
    uint8_t ui_last_status;
} simple_ui_s_t;

extern simple_ui_error_e_t SUI_Init(simple_ui_s_t *ui, const char *ui_name);
extern simple_ui_error_e_t SUI_AddFirstLevelItem(simple_ui_s_t *ui, const char *name);
extern simple_ui_error_e_t SUI_AddSecondLevelItem(simple_ui_s_t *ui, const char *belongs_first_level_item_name,
                                                  const char *name);
extern simple_ui_error_e_t SUI_AddThirdLevelItem(simple_ui_s_t *ui, const char *belongs_first_level_item_name,
                                                 const char *belongs_second_level_item_name, const char *name,
                                                 simple_ui_node_type_e_t node_type, void *data);
extern simple_ui_error_e_t SUI_Run(simple_ui_s_t *ui);

#endif /* __SIMPLE_UI_H_ */
