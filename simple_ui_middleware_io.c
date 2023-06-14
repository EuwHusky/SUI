/**
 ******************************************************************************
 * @file    simple_ui_middleware_io.c
 * @author  Enoky Bertram
 * @version v0.0.0 dev4
 * @date    Jun.6.2023
 * @brief   中间层 交互接口
 * @note    happyhappyhappy
 ******************************************************************************
 */

#include "simple_ui_middleware_io.h"

static uint8_t calculate_blank_between_item(uint8_t display_area_height, uint8_t item_num)
{
    uint8_t blank_num = 1;
    while (display_area_height >= item_num * blank_num)
        blank_num++;
    return (blank_num - 2);
}
static void show_string(uint8_t x, uint8_t y, const char *str)
{
    printf("%s\r\n", str);
}
static void show_integer(uint8_t x, uint8_t y, uint8_t *num)
{
    printf("%d\r\n", *num);
}
static void show_float(uint8_t x, uint8_t y, float *num)
{
    printf("%f\r\n", *num);
}
static void sui_display_menu_name(const char *menu_name)
{
    // 第一行靠左显示
    show_string(DISPLAY_AREA_WIDTH / 4 - strlen(menu_name) / 2, 0, menu_name);
}
static void sui_display_page_mark(uint8_t *current_page)
{
    // 第一行靠右显示
    show_string(DISPLAY_AREA_WIDTH - 4, 0, "P-");
    show_integer(DISPLAY_AREA_WIDTH - 2, 0, current_page);
}
static void sui_display_item_mark(uint8_t y)
{
    // 菜单项所在行左右两侧显示
    show_string(0, y, ">");
    show_string(DISPLAY_AREA_WIDTH - 1, y, "<");
}
static void sui_display_item_name(uint8_t y, const char *item_name)
{
    // 菜单项所在行靠左显示
    show_string(DISPLAY_AREA_WIDTH / 2 - strlen(item_name), y, item_name);
}
static void sui_display_item_data(uint8_t y, simple_ui_node_type_e_t node_type, void *data)
{
    // 菜单项所在行靠右显示
    if (SUI_SWITCH == node_type) // 切换类型用整形显示
    {
        show_integer(DISPLAY_AREA_WIDTH - 2, y, data);
    }
    else if (SUI_ADJUST == node_type || SUI_DISPLAY == node_type) // 调整和显示类型用浮点型表示
    {
        show_float(DISPLAY_AREA_WIDTH - 9, y, data);
    }
    else if (SUI_MENU == node_type) // 菜单项无数据，显示提示信息
    {
        show_string(DISPLAY_AREA_WIDTH - 5, y, "<*>");
    }
}

void sui_display_page(const char *menu_name)
{
    sui_display_menu_name(menu_name);
}
void sui_display_item(simple_ui_menu_level_e_t level, uint8_t current_item, const char *item_name,
                      simple_ui_node_type_e_t node_type, void *data)
{

    uint8_t y = DISPLAY_AREA_HEIGHT;
    switch (level)
    {
    case SUI_FIRST: {
        y -= ((NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY - current_item) *
              (calculate_blank_between_item(DISPLAY_AREA_HEIGHT, NUM_OF_FIRST_LEVEL_PAGE_ITEM_CAPACITY) + 1));
    }
    break;
    case SUI_SECOND: {
        y -= ((NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY - current_item) *
              (calculate_blank_between_item(DISPLAY_AREA_HEIGHT, NUM_OF_SECOND_LEVEL_PAGE_ITEM_CAPACITY) + 1));
    }
    break;
    case SUI_THIRD: {
        y -= ((NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY - current_item) *
              (calculate_blank_between_item(DISPLAY_AREA_HEIGHT, NUM_OF_THIRD_LEVEL_PAGE_ITEM_CAPACITY) + 1));
    }
    break;

    default:
        break;
    }

    sui_display_item_mark(y);
    sui_display_item_name(y, item_name);
    sui_display_item_data(y, node_type, data);
}

simple_ui_menu_operation_e_t sui_get_input()
{
    int key = _getch();

    switch (key)
    {
    case 87:
        printf("the key you press is up\n");
        return SUI_PRE_ITEM;
    case 83:
        printf("the key you press is down\n");
        return SUI_NEXT_ITEM;
    case 65:
        printf("the key you press is left\n");
        return SUI_PRE_PAGE;
    case 68:
        printf("the key you press is right\n");
        return SUI_NEXT_PAGE;
    case 13:
        printf("the key you press is enter\n");
        return SUI_ENTER;
    case 8:
        printf("the key you press is back\n");
        return SUI_RETURN;
    default:
        return SUI_NO_ACTION;
    }

    return SUI_NO_ACTION;
}
