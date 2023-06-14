/**
 ******************************************************************************
 * @file    simple_ui.c
 * @author  Enoky Bertram
 * @version v0.0.0 dev5
 * @date    Jun.14.2023
 * @brief   A Simple UI/一个简易用户界面
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
    ui->head_node = ui->ui_tree[0]; // 在调用SUI_AddFirstLevelItem为UI添加第一个子节点时会将头指针自动指向第一个子节点

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
    simple_ui_node_s_t *existing_node = find_child_ui_node_by_name(ui->ui_tree[0], name);
    if (existing_node != NULL)
        return SUI__ADD_FIRST_LEVEL_ITEM_ERROR__EXISTING_ITEM;

    /* 重新分配树空间 */
    ui->ui_tree_size++;
    ui->ui_tree = (simple_ui_node_s_t **)realloc(ui->ui_tree, ui->ui_tree_size * sizeof(simple_ui_node_s_t));

    /* 创建一级菜单项节点 */
    ui->ui_tree[ui->ui_tree_size - 1] = create_ui_node(SUI_MENU, name, NULL);

    /* 添加一级菜单项节点作为UI节点的子节点 */
    add_sub_ui_node(ui->ui_tree[0], ui->ui_tree[ui->ui_tree_size - 1]);

    if ((get_node_index_of_root(ui->ui_tree[ui->ui_tree_size - 1]) == 1) &&
        (get_node_index_of_parent(ui->ui_tree[ui->ui_tree_size - 1]) == 0))
        ui->head_node = ui->ui_tree[ui->ui_tree_size - 1];

    return SUI__OK;
}

simple_ui_error_e_t SUI_AddSecondLevelItem(simple_ui_s_t *ui, const char *belongs_first_level_item_name,
                                           const char *name)
{
    simple_ui_node_s_t *parent_node, *existing_node;

    /* 参数检查-路径存在性检查 */
    parent_node = find_child_ui_node_by_name(ui->ui_tree[0], belongs_first_level_item_name);
    if (parent_node == NULL)
        return SUI__ADD_SECOND_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST;

    /* 参数检查-名称重复检查 */
    existing_node = find_child_ui_node_by_name(parent_node, name);
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
    parent_node = find_child_ui_node_by_name(ui->ui_tree[0], belongs_first_level_item_name);
    if (parent_node == NULL)
        return SUI__ADD_THIRD_LEVEL_ITEM_ERROR__BELONGS_FIRST_LEVEL_ITEM_DOES_NOT_EXIST;

    parent_node = find_child_ui_node_by_name(parent_node, belongs_second_level_item_name);
    if (parent_node == NULL)
        return SUI__ADD_THIRD_LEVEL_ITEM_ERROR__BELONGS_SECOND_LEVEL_ITEM_DOES_NOT_EXIST;

    /* 参数检查-名称重复检查 */
    existing_node = find_child_ui_node_by_name(parent_node, name);
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

simple_ui_error_e_t SUI_Run(simple_ui_s_t *ui)
{
    uint8_t head_node_index_of_root = get_node_index_of_root(ui->head_node);
    uint8_t head_node_index_of_parent = get_node_index_of_parent(ui->head_node);
    uint8_t head_node_index_of_page = 1;
    uint8_t head_node_index_of_item = 0;

    uint8_t number_of_items_remaining_on_this_and_subsequent_pages = 0;

    simple_ui_node_s_t *temp_node = ui->head_node->parent->first_child;

    // if (SUI_ENABLED == ui->ui_status)

    // 显示页信息
    sui_display_page(ui->head_node->parent->info.name);

    ui->last_action = ui->action; // 更新上一次操作
    ui->action = sui_get_input(); // 获取本次操作

    switch (head_node_index_of_root)
    {
    case SUI_FIRST: {
        // 获取头指针在UI内的页、项信息
        head_node_index_of_page = (head_node_index_of_parent) / NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY + 1;
        head_node_index_of_item = (head_node_index_of_parent) % NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY;
        number_of_items_remaining_on_this_and_subsequent_pages =
            get_child_node_num_of_parent(ui->head_node->parent) -
            (head_node_index_of_page - 1) * NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY;
        // 显示项信息
        temp_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                (head_node_index_of_page - 1) * NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY);
        for (int i = 0; i < NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY; i++)
        {
            sui_display_an_item(NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY, head_node_index_of_item, i, temp_node->info.name,
                                temp_node->info.node_type, temp_node->info.data);
            if (temp_node->next_sibling != NULL)
                temp_node = temp_node->next_sibling;
            else
                break;
        }
        // 根据用户输入操作头指针在UI内移动
        if ((SUI_NO_ACTION != ui->action) && (SUI_NO_ACTION == ui->last_action)) // 获取操作类型
        {
            switch (ui->action)
            {
            case SUI_NEXT_PAGE: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    ui->head_node = ui->head_node->parent->first_child;
                }
                else
                {
                    ui->head_node = find_child_ui_node_by_index(
                        ui->head_node->parent, (head_node_index_of_page)*NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_PRE_PAGE: {
                if (head_node_index_of_page > 1)
                {
                    ui->head_node = find_child_ui_node_by_index(
                        ui->head_node->parent, (head_node_index_of_page - 2) * NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY);
                }
                else
                {
                    ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                get_child_node_num_of_parent(ui->head_node->parent) /
                                                                    NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY *
                                                                    NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_NEXT_ITEM: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    if (head_node_index_of_item < number_of_items_remaining_on_this_and_subsequent_pages - 1)
                        ui->head_node = ui->head_node->next_sibling;
                    else
                        ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                    (head_node_index_of_page - 1) *
                                                                        NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY);
                }
                else
                {
                    if (head_node_index_of_item < NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY - 1)
                        ui->head_node = ui->head_node->next_sibling;
                    else
                        ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                    (head_node_index_of_page - 1) *
                                                                        NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_PRE_ITEM: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    if (head_node_index_of_item > 0)
                        ui->head_node =
                            find_child_ui_node_by_index(ui->head_node->parent, head_node_index_of_parent - 1);
                    else
                        ui->head_node = find_child_ui_node_by_index(
                            ui->head_node->parent,
                            (head_node_index_of_page - 1) * NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY +
                                number_of_items_remaining_on_this_and_subsequent_pages - 1);
                }
                else
                {
                    if (head_node_index_of_item > 0)
                        ui->head_node =
                            find_child_ui_node_by_index(ui->head_node->parent, head_node_index_of_parent - 1);
                    else
                        ui->head_node = find_child_ui_node_by_index(
                            ui->head_node->parent, head_node_index_of_page * NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY - 1);
                }
            }
            break;
            case SUI_ENTER: {
                if (ui->head_node->first_child != NULL)
                    ui->head_node = ui->head_node->first_child;
            }
            break;
            case SUI_RETURN: {
                if (ui->head_node->parent->parent != NULL)
                    ui->head_node = ui->head_node->parent;
            }
            break;

            default:
                break;
            }
        }
    }
    break;
    case SUI_SECOND: {
        // 获取头指针在UI内的页、项信息
        head_node_index_of_page = (head_node_index_of_parent) / NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY + 1;
        head_node_index_of_item = (head_node_index_of_parent) % NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY;
        number_of_items_remaining_on_this_and_subsequent_pages =
            get_child_node_num_of_parent(ui->head_node->parent) -
            (head_node_index_of_page - 1) * NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY;
        // 显示项信息
        temp_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                (head_node_index_of_page - 1) * NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY);
        for (int i = 0; i < NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY; i++)
        {
            sui_display_an_item(NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY, head_node_index_of_item, i,
                                temp_node->info.name, temp_node->info.node_type, temp_node->info.data);
            if (temp_node->next_sibling != NULL)
                temp_node = temp_node->next_sibling;
            else
                break;
        }
        // 根据用户输入操作头指针在UI内移动
        if ((SUI_NO_ACTION != ui->action) && (SUI_NO_ACTION == ui->last_action)) // 获取操作类型
        {
            switch (ui->action)
            {
            case SUI_NEXT_PAGE: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    ui->head_node = ui->head_node->parent->first_child;
                }
                else
                {
                    ui->head_node = find_child_ui_node_by_index(
                        ui->head_node->parent, (head_node_index_of_page)*NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_PRE_PAGE: {
                if (head_node_index_of_page > 1)
                {
                    ui->head_node = find_child_ui_node_by_index(
                        ui->head_node->parent, (head_node_index_of_page - 2) * NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY);
                }
                else
                {
                    ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                get_child_node_num_of_parent(ui->head_node->parent) /
                                                                    NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY *
                                                                    NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_NEXT_ITEM: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    if (head_node_index_of_item < number_of_items_remaining_on_this_and_subsequent_pages - 1)
                        ui->head_node = ui->head_node->next_sibling;
                    else
                        ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                    (head_node_index_of_page - 1) *
                                                                        NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY);
                }
                else
                {
                    if (head_node_index_of_item < NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY - 1)
                        ui->head_node = ui->head_node->next_sibling;
                    else
                        ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                    (head_node_index_of_page - 1) *
                                                                        NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_PRE_ITEM: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    if (head_node_index_of_item > 0)
                        ui->head_node =
                            find_child_ui_node_by_index(ui->head_node->parent, head_node_index_of_parent - 1);
                    else
                        ui->head_node = find_child_ui_node_by_index(
                            ui->head_node->parent,
                            (head_node_index_of_page - 1) * NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY +
                                number_of_items_remaining_on_this_and_subsequent_pages - 1);
                }
                else
                {
                    if (head_node_index_of_item > 0)
                        ui->head_node =
                            find_child_ui_node_by_index(ui->head_node->parent, head_node_index_of_parent - 1);
                    else
                        ui->head_node = find_child_ui_node_by_index(
                            ui->head_node->parent,
                            head_node_index_of_page * NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY - 1);
                }
            }
            break;
            case SUI_ENTER: {
                if (ui->head_node->first_child != NULL)
                    ui->head_node = ui->head_node->first_child;
            }
            break;
            case SUI_RETURN: {
                if (ui->head_node->parent->parent != NULL)
                    ui->head_node = ui->head_node->parent;
            }
            break;

            default:
                break;
            }
        }
    }
    break;
    case SUI_THIRD: {
        // 获取头指针在UI内的页、项信息
        head_node_index_of_page = (head_node_index_of_parent) / NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY + 1;
        head_node_index_of_item = (head_node_index_of_parent) % NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY;
        number_of_items_remaining_on_this_and_subsequent_pages =
            get_child_node_num_of_parent(ui->head_node->parent) -
            (head_node_index_of_page - 1) * NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY;
        // 显示项信息
        temp_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                (head_node_index_of_page - 1) * NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY);
        for (int i = 0; i < NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY; i++)
        {
            sui_display_an_item(NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY, head_node_index_of_item, i, temp_node->info.name,
                                temp_node->info.node_type, temp_node->info.data);
            if (temp_node->next_sibling != NULL)
                temp_node = temp_node->next_sibling;
            else
                break;
        }
        // 根据用户输入操作头指针在UI内移动
        if ((SUI_NO_ACTION != ui->action) && (SUI_NO_ACTION == ui->last_action)) // 获取操作类型
        {
            switch (ui->action)
            {
            case SUI_NEXT_PAGE: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    ui->head_node = ui->head_node->parent->first_child;
                }
                else
                {
                    ui->head_node = find_child_ui_node_by_index(
                        ui->head_node->parent, (head_node_index_of_page)*NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_PRE_PAGE: {
                if (head_node_index_of_page > 1)
                {
                    ui->head_node = find_child_ui_node_by_index(
                        ui->head_node->parent, (head_node_index_of_page - 2) * NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY);
                }
                else
                {
                    ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                get_child_node_num_of_parent(ui->head_node->parent) /
                                                                    NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY *
                                                                    NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_NEXT_ITEM: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    if (head_node_index_of_item < number_of_items_remaining_on_this_and_subsequent_pages - 1)
                        ui->head_node = ui->head_node->next_sibling;
                    else
                        ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                    (head_node_index_of_page - 1) *
                                                                        NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY);
                }
                else
                {
                    if (head_node_index_of_item < NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY - 1)
                        ui->head_node = ui->head_node->next_sibling;
                    else
                        ui->head_node = find_child_ui_node_by_index(ui->head_node->parent,
                                                                    (head_node_index_of_page - 1) *
                                                                        NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY);
                }
            }
            break;
            case SUI_PRE_ITEM: {
                if (number_of_items_remaining_on_this_and_subsequent_pages < NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY)
                {
                    if (head_node_index_of_item > 0)
                        ui->head_node =
                            find_child_ui_node_by_index(ui->head_node->parent, head_node_index_of_parent - 1);
                    else
                        ui->head_node = find_child_ui_node_by_index(
                            ui->head_node->parent,
                            (head_node_index_of_page - 1) * NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY +
                                number_of_items_remaining_on_this_and_subsequent_pages - 1);
                }
                else
                {
                    if (head_node_index_of_item > 0)
                        ui->head_node =
                            find_child_ui_node_by_index(ui->head_node->parent, head_node_index_of_parent - 1);
                    else
                        ui->head_node = find_child_ui_node_by_index(
                            ui->head_node->parent, head_node_index_of_page * NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY - 1);
                }
            }
            break;
            case SUI_ENTER: {
                if (ui->head_node->first_child != NULL)
                    ui->head_node = ui->head_node->first_child;
            }
            break;
            case SUI_RETURN: {
                if (ui->head_node->parent->parent != NULL)
                    ui->head_node = ui->head_node->parent;
            }
            break;

            default:
                break;
            }
        }
    }
    break;

    default:
        break;
    }

    return SUI__OK;
}
