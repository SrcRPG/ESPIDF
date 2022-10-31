#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xSemaphore = NULL;

void vTask1()
{
  // xSemaphoreTake(xSempahore, portMAX_DELAY);
  for (size_t i = 0; i < 3; i++)
  {
    printf("Task3 %d: %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("\n");
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}

void vTask2()
{
  xSemaphoreTake(xSempahore, portMAX_DELAY);
  for (size_t i = 0; i < 3; i++)
  {
    printf("Task3 %d: %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("\n");
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}

void vTask3()
{
  xSemaphoreTake(xSempahore, portMAX_DELAY);
  for (size_t i = 0; i < 3; i++)
  {
    printf("Task3 %d: %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("\n");
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}

void app_main(void)
{
  printf("\n");
  xSemaphore = xSemaphoreCreateBinary();  //function take is inside, that's why we can't take on task1
  
  xTaskCreate(vTask1, "Task1", 2048, NULL, 2, NULL);
  xTaskCreate(vTask2, "Task2", 2048, NULL, 2, NULL);
  xTaskCreate(vTask3, "Task3", 2048, NULL, 2, NULL);
}
