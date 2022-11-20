# Braço robótico monitorado por alarme Iot 
O presente projeto, da disciplina Objetos Inteligentes Conectados, consiste na montagem e programação de um braço robótico pré-fabricado, utilizado para simular uma máquina industrial que realiza movimentos repetitivos, monitorado por um sistema de alarme. Para tanto, realizei o posicionamento automático do braço ao definir funções e atribuí-las para servo motores. Além disso, inclui um sistema de alarme que envia e recebe dados por meio do protocolo MQTT. 

### modelo de montagem Fritzing:
![image](https://user-images.githubusercontent.com/57760392/202878216-be96d332-ce7f-4495-ad93-3b25705fe681.png)

# Software desenvolvido e a documentação do código
O software desenvolvido com o uso da IDE Arduino, 
Ademais, será feito o uso de um sensor ultrassônico que fara o monitoramento de quem se aproxima do braço robótico. Caso seja ultrapassado o limite de segurança fictício de 30 cm, automaticamente será acionado um alarme (buzzer ativo). 

# Descrição do hardware e plataforma de desenvolvimento utilizada
- [X] Arduino IDE (ambiente de desenvolvimento) - link para download: https://www.arduino.cc/en/software;
- [X] 1 buzzer ativo 5v;
- [X] 10 jumpers macho/femea e 5 jumpers macho/macho;
- [X] 1 kit com braço robótico em acrílico, 4 servos 9g e 1 kit de parafusos para montagem (encontrado facilmente para venda pela internet);
- [X] 1 led 5mm vermelho;
- [X] 1 placa de desemvolvimento NodeMCU(ESP8266);
- [X] 1 protoboard de pelo menos 400 pontos;
- [X] 1 sensor de distância ultrassônico HC-SR04;
- [X] 1 resistor 1K 1/4W

# Documentação das interfaces, protocolos e módulos de comunicação.

 O projeto deve possuir comunicação/controle via internet (TCP/IP) e uso do Protocolo MQTT.


