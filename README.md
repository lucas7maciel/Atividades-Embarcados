# Atividades de Sistemas Embarcados

Este repositorio contem exemplos e exercicios praticos para o curso de sistemas embarcados utilizando Zephyr RTOS. As atividades abordam conceitos fundamentais como GPIO, PWM, timers e uso do sistema de logs.

## Atividade 1 - Hello World com Timer

### Descricao da atividade

- A aplicacao define um timer periodico (`hello_timer`) usando `K_TIMER_DEFINE`, com periodo configurado pela opcao `CONFIG_HELLO_TIMER_PERIOD_MS`.
- A cada disparo o callback registra um `LOG_INF` com a mensagem "Hello World!" e um `LOG_DBG` com o contador de execucoes para facilitar o acompanhamento no console.
- A cada dez disparos o callback emite adicionalmente um `LOG_ERR`, demonstrando o uso de diferentes niveis de log no Zephyr.
- No `main`, o timer eh iniciado logo apos o boot e o thread principal entra em espera infinita (`k_sleep(K_FOREVER)`), deixando o timer responsavel pelo fluxo de mensagens.

Os arquivos envolvidos estao em `src/main.c`, `prj.conf` e `Kconfig`, onde ficam as configuracoes de log e do periodo do timer.

### Como executar o projeto

1. Configure previamente o ambiente do Zephyr conforme o guia oficial (variaveis `ZEPHYR_BASE`, `west`, SDK ou toolchain equivalentes).
2. No diretorio do projeto, utilize `west build -b <placa> -p auto .` substituindo `<placa>` pelo board alvo (por exemplo, `nrf52dk_nrf52832`).
3. Para enviar a aplicacao ao hardware, execute `west flash` apos a etapa de build com a placa conectada via USB.
4. Abra um terminal serial (ex.: `west espressif monitor` ou `west debug --runner jlink`) para acompanhar os logs e verificar as mensagens periodicas.

## Observacoes

- Utilize o Zephyr RTOS e consulte a documentacao oficial para detalhes sobre APIs de GPIO, PWM, timers e logs.
- Os parametros de configuracao devem ser definidos nos arquivos `prj.conf` e `Kconfig` do projeto.
- Teste as funcionalidades em hardware compativel ou emuladores suportados pelo Zephyr.
