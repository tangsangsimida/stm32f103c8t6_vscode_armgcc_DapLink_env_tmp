#include "user_main.hpp"

#include "main.h"

int user_main()
{
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
    // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_Delay(1000);
    return 0;
}
