/**
 ******************************************************************************
 * @file    simple_ui.c
 * @author  Enoky Bertram
 * @version V0.0.0 dev1
 * @date    Jun.4.2023
 * @brief   A Simple UI Switcher /一个简易用户界面
 * @note    happyhappyhappy
 ******************************************************************************
 * @example
 *
 * @attention
 ******************************************************************************
 */

#include "simple_ui.h"

static simple_ui_node_s_t *create_ui_node(simple_ui_node_type_e_t node_type, const char *name, void *data);
static void add_sub_ui_node(simple_ui_node_s_t *parent, simple_ui_node_s_t *child);
static simple_ui_node_s_t *find_ui_node(simple_ui_node_s_t *parent, const char *target);

simple_ui_error_e_t SUI_Init(simple_ui_s_t *ui)
{
    ui->ui_tree_size = 1;

    ui->ui_tree = (simple_ui_node_s_t **)malloc(ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    ui->ui_tree[0] = create_ui_node(SUI_MENU, "UI", NULL);

    ui->number_of_first_level_item = 0;
    ui->number_of_seconde_level_item = 0;
    ui->number_of_third_level_item = 0;

    ui->first_level_index = 0;
    ui->seconde_level_index = 0;
    ui->third_level_index = 0;
}

simple_ui_error_e_t SUI_AddFirstLevelItem(simple_ui_s_t *ui, const char *name, uint8_t first_level_index)
{
    /* 参数检查-名称重复检查 */
    simple_ui_node_s_t *temp_node = find_ui_node(ui->ui_tree[0], name);
    if (temp_node != NULL)
        return SUI__ADD_FIRST_LEVEL_ITEM_ERROR__EXISTING_ITEM;

    /* 重新分配树空间 */
    ui->ui_tree_size++;
    ui->ui_tree = (simple_ui_node_s_t **)realloc(ui->ui_tree, ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建一级菜单项节点 */
    ui->ui_tree[ui->ui_tree_size - 1] = create_ui_node(SUI_MENU, name, NULL);

    /* 添加一级菜单项节点作为UI节点的子节点 */
    add_sub_ui_node(ui->ui_tree[0], ui->ui_tree[ui->ui_tree_size - 1]);

    // /* 设置一级菜单项索引 */
    // ui->ui_tree[ui->ui_tree_size - 1]->info.first_level_index = first_level_index;

    // /* 记录一级菜单项数量 */
    // ui->number_of_first_level_item++;

    return SUI__OK;
}

simple_ui_error_e_t SUI_AddSecondLevelItem(simple_ui_s_t *ui, const char *belongs_first_level_item_name,
                                           const char *name)
{
    simple_ui_node_s_t *temp_node;

    /* 参数检查-父节点存在性检查 */
    temp_node = find_ui_node(ui->ui_tree[0], belongs_first_level_item_name);
    if (temp_node == NULL)
        return SUI__ADD_SECOND_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST;

    /* 参数检查-名称重复检查 */
    temp_node = find_ui_node(temp_node, name);
    if (temp_node != NULL)
        return SUI__ADD_SECOND_LEVEL_ITEM_ERROR__EXISTING_ITEM;

    /* 重新分配树空间 */
    ui->ui_tree_size++;
    ui->ui_tree = (simple_ui_node_s_t **)realloc(ui->ui_tree, ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建二级菜单项节点 */
    ui->ui_tree[ui->ui_tree_size - 1] = create_ui_node(SUI_MENU, name, NULL);

    /* 添加二级菜单项节点作为一级菜单项节点的子节点 */
    add_sub_ui_node(temp_node, ui->ui_tree[ui->ui_tree_size - 1]);

    // /* 记录一级菜单项数量 */
    // ui->number_of_first_level_item++;

    return SUI__OK;
}

simple_ui_error_e_t SUI_AddThirdLevelItem(simple_ui_s_t *ui, const char *belongs_second_level_item_name,
                                          const char *name)
{
    simple_ui_node_s_t *temp_node;

    /* 参数检查-名称重复检查 */
    temp_node = find_ui_node(ui->ui_tree[0], name);
    if (temp_node != NULL)
        return SUI__ADD_SECOND_LEVEL_ITEM_ERROR__EXISTING_ITEM;

    /* 重新分配树空间 */
    ui->ui_tree_size++;
    ui->ui_tree = (simple_ui_node_s_t **)realloc(ui->ui_tree, ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建二级菜单项节点 */
    ui->ui_tree[ui->ui_tree_size - 1] = create_ui_node(SUI_MENU, name, NULL);

    /* 添加二级菜单项节点作为一级菜单项节点的子节点 */
    temp_node = find_ui_node(ui->ui_tree[0], belongs_second_level_item_name);
    if (temp_node == NULL)
        return SUI__ADD_SECOND_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST;
    add_sub_ui_node(temp_node, ui->ui_tree[ui->ui_tree_size - 1]);

    // /* 记录一级菜单项数量 */
    // ui->number_of_first_level_item++;

    return SUI__OK;
}

static simple_ui_node_s_t *create_ui_node(simple_ui_node_type_e_t node_type, const char *name, void *data)
{
    simple_ui_node_s_t *new_node = (simple_ui_node_s_t *)malloc(sizeof(simple_ui_node_s_t));

    new_node->info.node_type = node_type;
    strcpy(new_node->info.name, name);
    new_node->info.data = data;

    new_node->parent = NULL;
    new_node->first_child = NULL;
    new_node->next_sibling = NULL;

    return new_node;
}

static void add_sub_ui_node(simple_ui_node_s_t *parent, simple_ui_node_s_t *child)
{
    child->parent = parent;

    if (parent->first_child == NULL)
    {
        parent->first_child = child;
    }
    else
    {
        simple_ui_node_s_t *sibling = parent->first_child;
        while (sibling->next_sibling != NULL)
        {
            sibling = sibling->next_sibling;
        }
        sibling->next_sibling = child;
    }
}

static simple_ui_node_s_t *find_ui_node(simple_ui_node_s_t *parent, const char *target)
{
    // 如果父节点为空或者父节点的值等于目标值，直接返回父节点
    if (parent == NULL || *parent->info.name == *target)
    {
        return parent;
    }
    // 在孩子树中查找目标值
    simple_ui_node_s_t *found_node = find_ui_node(parent->first_child, target);
    // 如果在孩子树中未找到目标值，继续在兄弟树中查找
    if (found_node == NULL)
    {
        found_node = find_ui_node(parent->next_sibling, target);
    }
    // 返回找到的节点指针（如果找到）或者 NULL（如果未找到）
    return found_node;
}

static simple_ui_node_s_t *find_child_ui_node(simple_ui_node_s_t *parent, const char *target)
{
    // 如果父节点为空,直接返回父节点
    if (parent == NULL)
    {
        return parent;
    }
    // 在孩子树中查找目标值
    simple_ui_node_s_t *found_node = find_ui_node(parent->first_child, target);
    // 如果在孩子树中未找到目标值，继续在兄弟树中查找
    if (found_node == NULL)
    {
        found_node = find_ui_node(parent->next_sibling, target);
    }
    // 返回找到的节点指针（如果找到）或者 NULL（如果未找到）
    return found_node;
}
