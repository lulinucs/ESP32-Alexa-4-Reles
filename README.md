
# Controle de 4 módulos relés com ESP RainMaker e Alexa

Este projeto tem como objetivo criar um sistema de controle de 4 módulos relés utilizando o microcontrolador ESP32 e a conectividade com o ESP RainMaker para possibilitar a integração com a Alexa.
Esta é uma modificação do exemplo oficial da Rainmaker [RMakerSwitch.ino](https://github.com/espressif/arduino-esp32/blob/master/libraries/RainMaker/examples/RMakerSwitch/RMakerSwitch.ino). O exemplo oficial só da suporte para um Switch, no meu exemplo adicionei mais 3 switches, mas você pode incluir mais se quiser, a única limitação é a quantidade de portas digitais do ESP32.

## Materiais necessários

-   ESP32 (NodeMCU-32s)
-   4 módulos relés
-   Fios de jumper
-   Fonte de alimentação 
-	Cabo USB
-	Aplicativo ESPRainmaker ([ESP RainMaker – Apps no Google Play](https://play.google.com/store/apps/details?id=com.espressif.rainmaker&hl=pt_BR&gl=US)

## Esquema de conexão

Utilize os jumpers para conectar os módulos relés às portas digitais da ESP32. Em cada módulo relé você pode conectar uma tomada ou bocal de lâmpada, para controlar estes dispositivos remotamente.

![Esquema de Conexão](https://images2.imgbox.com/12/04/pMsU9gwv_o.png)


## Configuração do ESP RainMaker

O ESP RainMaker é uma plataforma IoT da Espressif que permite a criação de dispositivos conectados à internet com facilidade. Para configurá-lo, é necessário seguir os seguintes passos:

1.  Utilizando a IDE do Arduino previamente configurada para suportar a ESP32, suba o código para a ESP32.
2.  Abra o Serial Monitor, copie o link gerado e cole no navegador para obter o QRCode
3.  Abra o aplicativo EspRainMaker no seu smartphone e clique no símbolo "+" e leia o QR code.
4. Ainda no aplicativo, selecione sua rede wifi e insira a senha.
5. Aguarde sua ESP32 se conectar ao wifi.
6. Seus 4 switches digitais devem aparecer na tela inicial do EspRainMaker e já é possível acionar os relés através destes botões.

## Configuração da Alexa

Para controlar os módulos relés com a Alexa, basta abrir o aplicativo da Alexa no seu smartphone e solicitar para que ela busque novos dispositivos.

## Funcionamento do sistema

Após a configuração do ESP RainMaker e da habilidade da Alexa, o sistema estará pronto para uso. Basta enviar um comando de voz para a Alexa para ligar ou desligar os módulos relés conectados à placa Arduino. Note que você pode alterar os nomes dos dispositivos "Switch1", "Switch2", "Switch3" e "Switch4" no código-fonte ou então manter dessa forma e renomeá-los diretamente no app da Alexa.