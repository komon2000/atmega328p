#include "scheduler.h"
#include "timer00.h"     // millis()
#include <string.h>
#include "config.h"

typedef struct {
    void (*func)(void);
    uint32_t interval;
    uint32_t last_run;
    const char* name;
    uint8_t enabled;
} task_t;

static task_t tasks[MAX_TASKS];
static uint8_t task_count = 0;

void scheduler_init(void)
{
    task_count = 0;
    memset(tasks, 0, sizeof(tasks));
}

uint8_t scheduler_add(void (*task)(void), uint32_t interval_ms, const char* name)
{
    if (task_count >= MAX_TASKS || task == NULL) {
        return 255;                    // error: no slots or NULL function
    }

    uint8_t id = task_count++;

    tasks[id].func     = task;
    tasks[id].interval = interval_ms;
    tasks[id].name     = name ? name : "Unnamed";
    tasks[id].enabled  = 1;

    // Run as soon as possible on the very first scheduler_run()
    tasks[id].last_run = millis() - interval_ms;

    return id;
}

void scheduler_enable(uint8_t id)
{
    if (id < task_count) tasks[id].enabled = 1;
}

void scheduler_disable(uint8_t id)
{
    if (id < task_count) tasks[id].enabled = 0;
}

void scheduler_run(void)
{
    uint32_t now = millis();

    for (uint8_t i = 0; i < task_count; i++)
    {
        task_t *t = &tasks[i];
        if (t->enabled && (now - t->last_run >= t->interval))
        {
            t->last_run = now;
            t->func();
        }
    }
}