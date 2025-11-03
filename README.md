# Atividades de Sistemas Embarcados

Este repositorio contem exemplos e exercicios praticos desenvolvidos ao longo do curso de sistemas embarcados utilizando Zephyr RTOS. Cada atividade explora um conjunto diferente de APIs, desde temporizadores e GPIO ate comunicacao entre threads com filas de mensagens.

## Atividade 3 - Comunicacao entre Threads com Filtro Intermediario

### Descricao da atividade

- Dois produtores (`producer_thread`) simulam sensores de temperatura e umidade usando padroes ciclicos e periodos configurados por `CONFIG_TEMP_PRODUCER_INTERVAL_MS` e `CONFIG_HUM_PRODUCER_INTERVAL_MS`.
- As leituras sao enfileiradas em `input_queue`. A thread de filtro (`filter_thread`) valida cada amostra conforme limites definidos em `Kconfig`, encaminhando dados validos para `output_queue` e inconsistencias para `error_queue`.
- A thread consumidora (`consumer_thread`) processa apenas leituras validadas, registrando-as com `LOG_INF`.
- Um logger dedicado (`error_logger_thread`) consome a fila de erros e publica avisos (`LOG_WRN`) com detalhes da faixa esperada e do valor fora do padrao.
- Todas as filas usam `K_MSGQ_DEFINE` com capacidade compartilhada e alinhamento constante, assegurando operacao deterministica sem alocacao dinamica.

### Fluxo de processamento

- **Produtores**: geram amostras com timestamp (`k_uptime_get`) e colocam em `input_queue`. Logs `LOG_DBG` ajudam a rastrear o fluxo.
- **Filtro**: chama `validate_reading`, que retorna limites e identifica se a leitura ficou abaixo ou acima do permitido.
- **Consumidor**: imprime os dados aprovados com o tipo de sensor correspondente.
- **Logger de erros**: converte inconsistencias em estruturas `sensor_fault` e emite avisos descrevendo a direcao do erro (abaixo/acima da faixa).

### Regras de validacao

- Temperatura valida entre `CONFIG_TEMP_VALID_MIN_C` e `CONFIG_TEMP_VALID_MAX_C` (padrao 18 a 30 graus Celsius).
- Umidade valida entre `CONFIG_HUM_VALID_MIN_PCT` e `CONFIG_HUM_VALID_MAX_PCT` (padrao 40 a 70%).
- Fora dessas faixas, a leitura e classificada como `SENSOR_ERR_TOO_LOW` ou `SENSOR_ERR_TOO_HIGH` e enviada para o canal de erro.

### Parametros configuraveis (Kconfig)

- `CONFIG_TEMP_VALID_MIN_C` e `CONFIG_TEMP_VALID_MAX_C`: limites de temperatura aceitos.
- `CONFIG_HUM_VALID_MIN_PCT` e `CONFIG_HUM_VALID_MAX_PCT`: faixa valida de umidade.
- `CONFIG_TEMP_PRODUCER_INTERVAL_MS`: intervalo de producao do sensor de temperatura.
- `CONFIG_HUM_PRODUCER_INTERVAL_MS`: intervalo de producao do sensor de umidade.
- `CONFIG_FILTER_QUEUE_DEPTH`: profundidade das filas de entrada, saida e erro.

### Arquivos principais

- `src/main.c`: concentra as quatro threads, estruturas `sensor_reading`/`sensor_fault` e a logica de validacao.
- `prj.conf`: define niveis de log, tamanhos de pilha e intervalos padrao das threads produtoras.
- `Kconfig`: expoe as faixas validas e a capacidade das filas para customizacao via `menuconfig` ou `west build -t menuconfig`.

### Como executar o projeto

1. Prepare o ambiente Zephyr (instale o SDK, configure `ZEPHYR_BASE`, instale `west` e rode `west update`).
2. A partir do diretorio do projeto, execute `west build -b <placa> -p auto .` selecionando uma placa suportada (por exemplo `qemu_x86` para testar em emulacao ou `nrf52840dk_nrf52840` para hardware real).
3. Realize o flash com `west flash` (ou `west build -t run` se estiver usando QEMU) mantendo a placa conectada.
4. Abra o console de logs (`west build -t run`, `west debug`, `west espressif monitor`, `minicom`, etc.).
5. Analise a saida: mensagens `LOG_INF` indicam dados aprovados consumidos, enquanto `LOG_WRN` sinalizam leituras fora da faixa com informacao da faixa esperada e timestamp.

## Observacoes

- Para a Atividade 2, garanta que os aliases `led0`, `pwm_led0` e `sw0` estejam definidos no device tree da placa; ajuste um arquivo em `boards/` caso necessario.
- Para a Atividade 3, ajuste os limites e intervalos no `Kconfig` conforme o comportamento desejado e utilize `CONFIG_FILTER_QUEUE_DEPTH` maior se notar filas cheias.
- Teste sempre que possivel em hardware real para validar temporizacoes e perifericos; em ausencia de hardware, o QEMU e uma alternativa util para inspecionar logs e fluxo de threads.
