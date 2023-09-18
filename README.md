# Edge Computing - Checkpoint 4

# Introdução
Como andamento ao projeto do [Checkpoint 2](https://github.com/Projetos-Fiap/Edge-Computing-CP02), de monitorador de luminosidade, temperatura e umidade, agora nesta continuação do projeto temos a implementação de um módulo Wi-Fi no circuito, que irá fazer o envio dos dados coletados para internet.
Este projeto é pensado para o case da Vinheria Agnello, para que possa ser usado para um melhor controle do armazenamento de garrafas de vinho.

# Arquitetura do projeto
O projeto utiliza o módulo Wi-Fi ESP32. Conectado nele temos dois sensores: sensor de luz fotossensível (LDR) para medições de luminosidade; e sensor DHT11 para medições de temperatura e umidade. As medições serão enviadas pela internet a cada 5 segundos, para nosso Device da Tago.io

# Componentes utilizados
<li>Módulo Wi-Fi ESP32</li>
<li>Sensor LDR (para luminosidade)</li>
<li>Sensor DHT11 (para temperatura e umidade)</li>
<li>Protoboard</li>
<li>Resistores</li>
<li>Cabos Jumper</li>

# Grupo
<li>André Lambert (RM99148)</li>  
<li>Bryan Willian (RM551305)</li>
<li>Lucas Feijó (RM99727)</li>
<li>Vitor Maia (RM99658)</li>
