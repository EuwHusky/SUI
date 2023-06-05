#include "simple_ui.h"

simple_ui_s_t gUI = {0};

int main(void)
{
    float test_num = 0.0f;

    SUI_Init(&gUI);

    printf("%d\r\n", SUI_AddFirstLevelItem(&gUI, "haha", 0));
    printf("%d\r\n", SUI_AddFirstLevelItem(&gUI, "haha", 0));

    // simple_ui_node_s_t *guagua = find_ui_node(gUI.ui_tree[0], "haha");

    while (1)
    {
        test_num++;
        // printf("%s\r\n", guagua->info.name);
        printf("%s\r\n", gUI.ui_tree[0]->first_child->info.name);
        printf("%s\r\n", gUI.ui_tree[0]->first_child->next_sibling->info.name);
        Sleep(1000);
    }
}
