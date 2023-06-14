/**
 ******************************************************************************
 * @file    simple_ui_middleware_treenode.c
 * @author  Enoky Bertram
 * @version v0.0.0 dev4
 * @date    Jun.6.2023
 * @brief   中间层 数据结构
 * @note    happyhappyhappy
 ******************************************************************************
 */

#include "simple_ui_middleware_treenode.h"

simple_ui_node_s_t *create_ui_node(simple_ui_node_type_e_t node_type, const char *name, void *data)
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

void add_sub_ui_node(simple_ui_node_s_t *parent, simple_ui_node_s_t *child)
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

simple_ui_node_s_t *find_ui_node(simple_ui_node_s_t *parent, const char *target)
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

simple_ui_node_s_t *find_child_ui_node(simple_ui_node_s_t *parent, const char *target)
{
    // 如果父节点为空,直接返回父节点
    if (parent == NULL || parent->first_child == NULL)
    {
        return NULL;
    }

    simple_ui_node_s_t *found_node = parent->first_child;

    if (strcmp(found_node->info.name, target) == 0)
        // if (*found_node->info.name == *target)
        return found_node;
    else
    {
        found_node = found_node->next_sibling;
        while (found_node != NULL)
        {
            if (strcmp(found_node->info.name, target) == 0)
                // if (*found_node->info.name == *target)
                return found_node;
            found_node = found_node->next_sibling;
        }
    }
}

/**
 * @brief 获得子节点在根节点下的索引
 */
uint8_t get_node_index_of_root(simple_ui_node_s_t *child)
{
    if (child == NULL)
        return -1;

    simple_ui_node_s_t *root = child;
    uint8_t index = 0;

    while (root->parent != NULL)
    {
        root = root->parent;
        index++;
    }

    return index;
}

/**
 * @brief 获得子节点在父节点下的索引
 */
uint8_t get_node_index_of_parent(simple_ui_node_s_t *child)
{
    if (child == NULL || child->parent == NULL || child->parent->first_child == NULL)
        return -1;

    simple_ui_node_s_t *first_sibling = child->parent->first_child;
    uint8_t index = 0;

    while (first_sibling != child)
    {
        first_sibling = first_sibling->next_sibling;
        index++;
    }

    return index;
}
