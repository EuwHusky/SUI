#include "simple_ui.h"

int main(void)
{
    simple_ui_s_t ui = {0};
    SUI_Init(&ui, 1);
    SUI_AddFirstLevelItem(&ui, 0, 0, "benbing", 1);

    while (1)
    {
        SUI_Run(&ui);
        Sleep(500);
    }
}
