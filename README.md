# Edge Computing - Checkpoint 4

# Introdução
Como andamento ao projeto do [Checkpoint 2](https://github.com/Projetos-Fiap/Edge-Computing-CP02), de monitorador de luminosidade, temperatura e umidade, agora nesta continuação do projeto temos a implementação de um módulo Wi-Fi no circuito, que fará o envio dos dados captados para a internet.
Este projeto é pensado para o case da Vinheria Agnello, para que possa ser usado para um melhor controle do armazenamento de garrafas de vinho.

# Arquitetura do projeto
O projeto utiliza como plataforma principal a placa Arduino Uno R3. Conectada nela temos dois sensores: sensor de luz fotossensível (LDR) para medições de luminosidade; e sensor DHT11 para medições de temperatura e umidade. As medições de luminosidade serão exibidas através dos leds ou acionamento do buzzer. Já as medições de temperatura e umidade serão exibidas no display LCD, junto de mensagens informando se os níveis estão adequados ou não. Caso o nível dessas esteja inadequado, também haverá acionamento do buzzer e do led amarelo.
Também faremos a utilização de um módulo Arduino Wi-Fi, o ESP32. Esse módulo será configurado para captar as leituras de luminosidade, temperatura e umidade do Arduino, e enviá-las pela internet a cada 5 segundos, para nosso Device da Tago.io

# Componentes utilizados
<li>Arduino Uno R3</li>
<li>Módulo Wi-Fi ESP32</li>
<li>LCD 16x2</li>
<li>Sensor LDR (para luminosidade)</li>
<li>Sensor DHT11 (para temperatura e umidade)</li>
<li>Protoboard</li>
<li>LEDs</li>
<li>Potênciometros</li>
<li>Resistores</li>
<li>Buzzer</li>
<li>Cabos Jumper</li>

# Grupo
<li>André Lambert (RM99148)</li>  
<li>Bryan Willian (RM551305)</li>
<li>Lucas Feijó (RM99727)</li>
<li>Vitor Maia (RM99658)</li>
