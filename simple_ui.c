/**
 ******************************************************************************
 * @file    simple_ui.c
 * @author  Enoky Bertram
 * @version v0.0.0 dev4
 * @date    Jun.6.2023
 * @brief   A Simple UI Switcher /一个简易用户界面
 * @note    happyhappyhappy
 ******************************************************************************
 * @example
 *
 * @attention
 ******************************************************************************
 */

#include "simple_ui.h"

simple_ui_error_e_t SUI_Init(simple_ui_s_t *ui, const char *ui_name)
{
    /* 初始化树空间 */
    ui->ui_tree_size = 1;
    ui->ui_tree = (simple_ui_node_s_t **)malloc(ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建UI根节点 */
    ui->ui_tree[0] = create_ui_node(SUI_MENU, ui_name, NULL);

    /* 初始化头指针指向根节点 */
    ui->head_node = ui->ui_tree[0];

    /* 初始化菜单索引 */
    ui->menu_level_index = 0;
    ui->menu_page_index = 0;
    ui->menu_item_index = 0;

    ui->action = SUI_NO_ACTION;
    ui->last_action = SUI_NO_ACTION;

    ui->ui_status = SUI_ENABLED;
    ui->ui_last_status = SUI_DISABLED;
}

simple_ui_error_e_t SUI_AddFirstLevelItem(simple_ui_s_t *ui, const char *name)
{
    /* 参数检查-名称重复检查 */
    simple_ui_node_s_t *existing_node = find_child_ui_node(ui->ui_tree[0], name);
    if (existing_node != NULL)
        return SUI__ADD_FIRST_LEVEL_ITEM_ERROR__EXISTING_ITEM;

    /* 重新分配树空间 */
    ui->ui_tree_size++;
    ui->ui_tree = (simple_ui_node_s_t **)realloc(ui->ui_tree, ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建一级菜单项节点 */
    ui->ui_tree[ui->ui_tree_size - 1] = create_ui_node(SUI_MENU, name, NULL);

    /* 添加一级菜单项节点作为UI节点的子节点 */
    add_sub_ui_node(ui->ui_tree[0], ui->ui_tree[ui->ui_tree_size - 1]);

    return SUI__OK;
}

simple_ui_error_e_t SUI_AddSecondLevelItem(simple_ui_s_t *ui, const char *belongs_first_level_item_name,
                                           const char *name)
{
    simple_ui_node_s_t *parent_node, *existing_node;

    /* 参数检查-路径存在性检查 */
    parent_node = find_child_ui_node(ui->ui_tree[0], belongs_first_level_item_name);
    if (parent_node == NULL)
        return SUI__ADD_SECOND_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST;

    /* 参数检查-名称重复检查 */
    existing_node = find_child_ui_node(parent_node, name);
    if (existing_node != NULL)
        return SUI__ADD_SECOND_LEVEL_ITEM_ERROR__EXISTING_ITEM;

    /* 重新分配树空间 */
    ui->ui_tree_size++;
    ui->ui_tree = (simple_ui_node_s_t **)realloc(ui->ui_tree, ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建二级菜单项节点 */
    ui->ui_tree[ui->ui_tree_size - 1] = create_ui_node(SUI_MENU, name, NULL);

    /* 添加二级菜单项节点作为一级菜单项节点的子节点 */
    add_sub_ui_node(parent_node, ui->ui_tree[ui->ui_tree_size - 1]);

    return SUI__OK;
}

simple_ui_error_e_t SUI_AddThirdLevelItem(simple_ui_s_t *ui, const char *belongs_first_level_item_name,
                                          const char *belongs_second_level_item_name, const char *name,
                                          simple_ui_node_type_e_t node_type, void *data)
{
    simple_ui_node_s_t *parent_node, *existing_node;

    /* 参数检查-路径存在性检查 */
    parent_node = find_child_ui_node(ui->ui_tree[0], belongs_first_level_item_name);
    if (parent_node == NULL)
        return SUI__ADD_THIRD_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST;

    parent_node = find_child_ui_node(parent_node, belongs_second_level_item_name);
    if (parent_node == NULL)
        return SUI__ADD_THIRD_LEVEL_ITEM_ERROR__BELONGS_SECOND_LEVEL_ITEM_DOES_NOT_EXIST;

    /* 参数检查-名称重复检查 */
    existing_node = find_child_ui_node(parent_node, name);
    if (existing_node != NULL)
        return SUI__ADD_THIRD_LEVEL_ITEM_ERROR__EXISTING_ITEM;

    /* 重新分配树空间 */
    ui->ui_tree_size++;
    ui->ui_tree = (simple_ui_node_s_t **)realloc(ui->ui_tree, ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建三级菜单项节点 */
    ui->ui_tree[ui->ui_tree_size - 1] = create_ui_node(node_type, name, data);

    /* 添加三级菜单项节点作为二级菜单项节点的子节点 */
    add_sub_ui_node(parent_node, ui->ui_tree[ui->ui_tree_size - 1]);

    return SUI__OK;
}

void SUI_Run(simple_ui_s_t *ui)
{
    // if (SUI_ENABLED == ui->ui_status)

    /* UI交互 */
    ui->last_action = ui->action; // 更新操作
    ui->action = sui_get_input();
    if ((SUI_NO_ACTION != ui->action) && (SUI_NO_ACTION == ui->last_action)) // 获取操作类型
    {
        switch (ui->action)
        {
        case SUI_NEXT_PAGE: {
        }
        break;
        case SUI_PRE_PAGE: {
        }
        break;
        case SUI_NEXT_ITEM: {
        }
        break;
        case SUI_PRE_ITEM: {
        }
        break;
        case SUI_ENTER: {
            if (ui->head_node->first_child != NULL)
                ui->head_node = ui->head_node->first_child;
        }
        break;
        case SUI_RETURN: {
            if (ui->head_node->parent != NULL)
                ui->head_node = ui->head_node->parent;
        }
        break;

        default:
            break;
        }
    }

    /* UI显示 */
    sui_display_page(ui->head_node->info.name);
}
