# Atividades de Sistemas Embarcados

Este repositorio contem exemplos e exercicios praticos desenvolvidos para o curso de sistemas embarcados utilizando Zephyr RTOS. Cada atividade explora um conjunto diferente de APIs do sistema operacional, incluindo temporizadores, GPIO, PWM, filas de mensagens e comunicacao por ZBus.

## Atividade 4 - Sincronizacao SNTP via ZBus

### Descricao

- A thread cliente SNTP sincroniza o relogio do sistema com o servidor configurado em `CONFIG_SNTP_SERVER_HOSTNAME` e `CONFIG_SNTP_SERVER_PORT`, utilizando `sntp_simple`.
- O horario sincronizado e encapsulado em `struct time_message`, contendo epoch em segundos, milissegundos fracionarios, valor combinado em ms e a estrutura `struct tm`.
- As leituras sao publicadas no canal ZBus `time_channel` (definido com `ZBUS_CHAN_DEFINE`) e entregues a dois assinantes (`logger_sub` e `app_sub`).
- A thread logger registra o horario completo em UTC, servindo como trilha de auditoria.
- A thread de aplicacao calcula o intervalo desde a ultima atualizacao para demonstrar uso do horario distribuido.
- Falhas na sincronizacao geram apenas `LOG_WRN`, sem publicar novos dados, garantindo que os assinantes recebam apenas horarios validos.

### Como executar

1. Configure rede e servidor SNTP: ajuste `CONFIG_SNTP_SERVER_HOSTNAME`, `CONFIG_SNTP_SERVER_PORT` e demais opcoes em `prj.conf` (`CONFIG_NET_CONFIG_*`).
2. Certifique-se de que a placa escolhida suporta networking (ex.: `qemu_x86`, `frdm_k64f`, `nrf52840dk_nrf52840`).
3. Compile com `west build -b <placa> -p auto .`.
4. Execute `west flash` ou `west build -t run` (para QEMU, configure TAP/SLIP conforme necessario).
5. Abra o console de logs e verifique: mensagens do logger mostram data/hora UTC, enquanto a aplicacao registra o delta entre sincronizacoes.

## Observacoes Gerais

- Ajuste os parametros em `Kconfig` e `prj.conf` conforme o hardware ou o cenario de teste.
- Garanta que aliases de hardware (como `led0`, `pwm_led0`, `sw0`) estejam presentes no device tree da placa ou em arquivos overlay.
- Para atividades que dependem de rede, valide a configuracao de enderecos IPv4 e a disponibilidade do servidor remoto antes de executar.
- Utilize `west build -t menuconfig` para alterar rapidamente configuracoes expostas no `Kconfig`.
