# Atividades de Sistemas Embarcados

Este repositorio contem exemplos e exercicios praticos para o curso de sistemas embarcados utilizando Zephyr RTOS. As atividades exploram recursos como GPIO, PWM, timers e o sistema de logs.

## Atividade 2 - Controle de Brilho de LED com GPIO, PWM e Botao

### Descricao da atividade

- O projeto associa o LED ao alias `led0`, o PWM a `pwm_led0` e o botao a `sw0`. Caso a placa nao disponha desses aliases, e necessario ajustar o device tree ou criar um overlay.
- No modo padrao (GPIO) o LED pisca em intervalo configuravel (`CONFIG_LED_BLINK_INTERVAL_MS`) usando `gpio_pin_set_dt`.
- Um toque no botao alterna para o modo PWM. Nesse modo o codigo ajusta continuamente o duty cycle (via `pwm_set_dt`) criando o efeito de fade in/out. O passo percentual (`CONFIG_LED_PWM_STEP_PCT`) e o intervalo entre passos (`CONFIG_LED_PWM_STEP_INTERVAL_MS`) podem ser configurados.
- O botao passa por uma rotina simples de debounce com historico de estado (`CONFIG_BUTTON_DEBOUNCE_MS`), garantindo que apenas transicoes reais mudem o modo.
- Logs `LOG_INF` documentam a troca de modos e eventuais erros de perifericos sao sinalizados com `LOG_ERR`.

### Parametros configuraveis (Kconfig)

- `CONFIG_LED_BLINK_INTERVAL_MS`: intervalo do pisca digital em milissegundos.
- `CONFIG_LED_PWM_PERIOD_US`: periodo do sinal PWM em microssegundos.
- `CONFIG_LED_PWM_STEP_PCT`: percentual de variacao aplicado ao duty cycle em cada passo.
- `CONFIG_LED_PWM_STEP_INTERVAL_MS`: intervalo em milissegundos entre os passos do fade.
- `CONFIG_BUTTON_DEBOUNCE_MS`: janela minima para considerar uma nova leitura do botao.

### Arquivos principais

- `src/main.c`: implementacao completa dos modos GPIO e PWM e da maquina de estados do botao.
- `prj.conf`: habilita LOG, define o tamanho da pilha principal e ativa o driver PWM.
- `Kconfig`: concentra os parametros ajustaveis que personalizam o comportamento da aplicacao.
- (Opcional) `boards/*.overlay`: utilize se precisar mapear aliases de LED, PWM ou botao para sua placa.

### Como executar o projeto

1. Prepare o ambiente Zephyr (instale o SDK/toolchain, exporte `ZEPHYR_BASE`, instale `west` e atualize os manifests).
2. Dentro do diretorio do projeto, execute `west build -b <placa> -p auto .`, substituindo `<placa>` pela board alvo (ex.: `nrf52dk_nrf52832` ou `nucleo_f746zg`).
3. Conecte a placa via USB e rode `west flash` para gravar o binario. Esse passo tambem reseta o dispositivo.
4. Abra um terminal serial para acompanhar os logs (por exemplo `west build -t run` para QEMU, `west espressif monitor` para placas Espressif, ou qualquer terminal serial apontado para a porta correspondente).
5. Verifique o LED: inicialmente ele pisca no modo GPIO; pressione o botao (`sw0`) para alternar para o modo de fade PWM e pressione novamente para retornar ao pisca digital.

## Observacoes

- Certifique-se de que os aliases `led0`, `pwm_led0` e `sw0` existem no device tree da sua placa; caso contrario, ajuste-os em um overlay.
- Ajuste os parametros do `Kconfig` conforme necessario (por exemplo, para acelerar o efeito de fade ou alterar o debounce).
- Teste em hardware real quando possivel; alguns emuladores podem nao expor PWM ou entradas de botao.
