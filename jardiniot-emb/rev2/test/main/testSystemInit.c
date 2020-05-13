

#include <unity.h>


#include <system_init.h>
                                        
void _super_intensive_test()
{
    printf("Yeet\n");
}

int app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(_super_intensive_test);
    return UNITY_END();
}


