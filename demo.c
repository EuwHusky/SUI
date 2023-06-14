#include "simple_ui.h"

#include <stdio.h>
#include <windows.h>

int main(void)
{
    simple_ui_s_t ui = {0};

    float test_num_display = 0.0f;
    uint8_t test_num_switch[2] = {0};
    float test_num_adjust = 0.0f;

    SUI_Init(&ui, "SUI");

    printf("%d\r\n", SUI_AddFirstLevelItem(&ui, "test_1st"));
    printf("%d\r\n", SUI_AddSecondLevelItem(&ui, "test_1st", "test_2cd"));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "test_1st", "test_2cd", "test_3th", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "test_1st", "test_2cd", "test_4th", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "test_1st", "test_2cd", "test_5th", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "test_1st", "test_2cd", "test_6th", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "test_1st", "test_2cd", "test_7th", SUI_DISPLAY, &test_num_display));

    // printf("%d\r\n", get_node_index_of_root(get_second_level_node_by_path(ui.ui_tree[0], "test_1st", "test_2cd")));

    while (1)
    {
        test_num_display++;
        printf("\r\n===+==========================+===\r\n");
        SUI_Run(&ui);
        printf("\r\n===+==========================+===\r\n");

        Sleep(500);
    }
}
