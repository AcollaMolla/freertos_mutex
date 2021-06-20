#ifdef __cplusplus
}
#endif
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static int shared_var = 0;

void incTask(void *parameters){
  int local_var;

  while(1){
    local_var = shared_var;
    local_var++;
    vTaskDelay(random(100,500)/portTICK_PERIOD_MS);
    shared_var = local_var;
    Serial.println(shared_var);
  }
}

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);
  vTaskDelay(1000/portTICK_PERIOD_MS);

  xTaskCreatePinnedToCore(incTask,
    "Increment Task 1",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);

  xTaskCreatePinnedToCore(incTask,
    "Increment Task 2",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);

    vTaskDelete(NULL);
}


void loop() {

}
