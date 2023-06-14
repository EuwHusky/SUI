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

    printf("%d\r\n", SUI_AddFirstLevelItem(&ui, "A"));
    printf("%d\r\n", SUI_AddSecondLevelItem(&ui, "A", "A_a"));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_1", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_2", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_3", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_4", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_5", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_6", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_7", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_8", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_9", SUI_DISPLAY, &test_num_display));
    printf("%d\r\n", SUI_AddThirdLevelItem(&ui, "A", "A_a", "A_a_10", SUI_DISPLAY, &test_num_display));

    printf("%d\r\n", SUI_AddFirstLevelItem(&ui, "B"));

    printf("%d\r\n", SUI_AddFirstLevelItem(&ui, "C"));

    printf("%d\r\n", SUI_AddFirstLevelItem(&ui, "D"));

    while (1)
    {
        test_num_display++;

        printf("\r\n===+==========================+===\r\n");
        SUI_Run(&ui);
        printf("\r\n===+==========================+===\r\n");
    }
}
