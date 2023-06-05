/**
 ******************************************************************************
 * @file    simple_ui.c/h
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

static void draw_ui(simple_ui_s_t *ui);

simple_ui_error_e_t SUI_Init(simple_ui_s_t *ui, uint8_t number_of_first_level_menu_pages)
{
    ui->number_of_first_level_menu_pages = number_of_first_level_menu_pages; // 设置一级菜单页数

    ui->first_level_menu = (simple_ui_first_level_item_s_t(*)[NUM_OF_FIRST_LEVEL_ITEMS])malloc(
        number_of_first_level_menu_pages * sizeof(simple_ui_first_level_item_s_t));
    if (ui->first_level_menu == NULL)
    {
        // 内存分配失败
        return SUI_ERROR;
    }

    ui->index[0] = 0;
    ui->index[1] = 0;
    ui->index[2] = 0;
    ui->index[3] = 0;
    ui->index[4] = 0;
    ui->index[5] = 0;
    ui->index[6] = 0;
}

simple_ui_error_e_t SUI_AddFirstLevelItem(simple_ui_s_t *ui, uint8_t first_level_page_index,
                                          uint8_t first_level_item_index, char name[10],
                                          uint8_t number_of_second_level_menu_pages)
{
    strcpy(ui->first_level_menu[first_level_page_index][first_level_item_index].name, name);

    ui->first_level_menu[first_level_page_index][first_level_item_index].number_of_second_level_menu_pages =
        number_of_second_level_menu_pages;

    ui->first_level_menu[first_level_page_index][first_level_item_index].second_level_menu =
        (simple_ui_second_level_item_s_t(*)[NUM_OF_SECOND_LEVEL_ITEMS])malloc(number_of_second_level_menu_pages *
                                                                              sizeof(simple_ui_second_level_item_s_t));
    if (ui->first_level_menu[first_level_page_index][first_level_item_index].second_level_menu == NULL)
    {
        // 内存分配失败
        return SUI_ERROR;
    }
}

simple_ui_error_e_t SUI_AddSecondLevelItem(simple_ui_s_t *ui, uint8_t first_level_page_index,
                                           uint8_t first_level_item_index, uint8_t second_level_page_index,
                                           uint8_t second_level_item_index, char name[10],
                                           uint8_t number_of_unit_level_menu_pages)
{
    strcpy(ui->first_level_menu[first_level_page_index][first_level_item_index]
               .second_level_menu[second_level_page_index][second_level_item_index]
               .name,
           name);

    ui->first_level_menu[first_level_page_index][first_level_item_index]
        .second_level_menu[second_level_page_index][second_level_item_index]
        .number_of_unit_level_menu_pages = number_of_unit_level_menu_pages;

    ui->first_level_menu[first_level_page_index][first_level_item_index]
        .second_level_menu[second_level_page_index][second_level_item_index]
        .unit_level_menu = (simple_ui_unit_level_s_t(*)[NUM_OF_UNIT_LEVEL_ITEMS])malloc(
        number_of_unit_level_menu_pages * sizeof(simple_ui_unit_level_s_t));
    if (ui->first_level_menu[first_level_page_index][first_level_item_index].second_level_menu == NULL)
    {
        // 内存分配失败
        return SUI_ERROR;
    }
}

simple_ui_error_e_t SUI_AddUnitLevelItem(simple_ui_s_t *ui, uint8_t first_level_page_index,
                                         uint8_t first_level_item_index, uint8_t second_level_page_index,
                                         uint8_t second_level_item_index, uint8_t unit_level_page_index,
                                         uint8_t unit_level_item_index, char name[10])
{
}

void SUI_Run(simple_ui_s_t *ui)
{
    draw_ui(ui);
}

static void draw_ui(simple_ui_s_t *ui)
{
    printf("\r\n============================================\r\n");
    switch (ui->index[0])
    {
    case 0: {
        printf("\r\nUI\r\n");
        if (ui->first_level_menu[ui->index[1]][ui->index[2]].name)
        {
            printf("%s\r\n", ui->first_level_menu[ui->index[1]][0].name);
        }
    }
    break;
    case 1:
        break;
    case 2:
        break;

    default:
        break;
    }
    printf("\r\n============================================\r\n");
}