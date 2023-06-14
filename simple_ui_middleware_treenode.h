/**
 ******************************************************************************
 * @file    simple_ui_middleware_treenode.h
 * @author  Enoky Bertram
 * @version v0.0.0 dev5
 * @date    Jun.14.2023
 * @brief   中间层 数据结构
 * @note    happyhappyhappy
 ******************************************************************************
 */

#ifndef __SIMPLE_UI_MIDDLEWARE_TREENODE_H_
#define __SIMPLE_UI_MIDDLEWARE_TREENODE_H_

#include "simple_ui_baseware.h"

typedef struct SimpleUIInfo
{
    simple_ui_node_type_e_t node_type; // 节点类型

    char name[10]; // 节点名称
    void *data;    // 节点数据
} simple_ui_info_s_t;

typedef struct SimpleUINode
{
    simple_ui_info_s_t info; // 节点信息

    struct SimpleUINode *parent;       // 父节点指针
    struct SimpleUINode *first_child;  // 第一个子节点指针
    struct SimpleUINode *next_sibling; // 下一个兄弟节点指针
} simple_ui_node_s_t;

extern simple_ui_node_s_t *create_ui_node(simple_ui_node_type_e_t node_type, const char *name, void *data);
extern void add_sub_ui_node(simple_ui_node_s_t *parent, simple_ui_node_s_t *child);
extern simple_ui_node_s_t *find_ui_node(simple_ui_node_s_t *parent, const char *target);
extern simple_ui_node_s_t *find_child_ui_node_by_name(simple_ui_node_s_t *parent, const char *target);
extern simple_ui_node_s_t *find_child_ui_node_by_index(simple_ui_node_s_t *parent, uint8_t index);
extern uint8_t get_node_index_of_root(simple_ui_node_s_t *child);
extern uint8_t get_node_index_of_parent(simple_ui_node_s_t *child);
extern uint8_t get_child_node_num_of_parent(simple_ui_node_s_t *parent);

#define get_first_level_node_by_path(root, first_name) find_child_ui_node_by_name(root, first_name)

#define get_second_level_node_by_path(root, first_name, second_name)                                                   \
    find_child_ui_node_by_name(find_child_ui_node_by_name(root, first_name), second_name)

#define get_third_level_node_by_path(root, first_name, second_name, third_name)                                        \
    find_child_ui_node_by_name(find_child_ui_node_by_name(find_child_ui_node_by_name(root, first_name), second_name),  \
                               third_name)

#endif /* __SIMPLE_UI_MIDDLEWARE_TREENODE_H_ */
