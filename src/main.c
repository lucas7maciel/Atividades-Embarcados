#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app, LOG_LEVEL_DBG);

static void hello_timer_handler(struct k_timer *timer_id)
{
	static uint32_t tick;

	ARG_UNUSED(timer_id);

	LOG_INF("Hello World!");
	LOG_DBG("Disparo #%u", tick);

	if ((tick++ % 10U) == 0U) {
		LOG_ERR("Exemplo de log de erro a cada 10 disparos");
	}
}

K_TIMER_DEFINE(hello_timer, hello_timer_handler, NULL);

int main(void)
{
	LOG_INF("Inicializando timer com periodo %d ms",
		CONFIG_HELLO_TIMER_PERIOD_MS);

	k_timer_start(&hello_timer, K_NO_WAIT,
		      K_MSEC(CONFIG_HELLO_TIMER_PERIOD_MS));

	while (true) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
