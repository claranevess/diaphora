<h1 align="center">Projeto Diaphora</h1>
<div align="center" >
<img src="https://github.com/claranevess/diaphora/assets/166565110/16511514-8892-4b20-9ebf-0ea0a4088369 alt="Imagem Arredondada" style="width: 40%;  border-radius: 50%;">
</div>

# 💻Projeto Diaphorá
<p align="center">O projeto Diaphora é uma solução inovadora destinada a auxiliar psicopedagogo e psicólogos no apoio a pessoas com Transtorno de Déficit de Atenção e Hiperatividade (TDAH) a melhorar a sua concentração e habilidades de foco no dia a dia. O dispositivo principal do projeto é uma caixa equipada com um sistema de reforço positivo que só é aberta após a execução de uma determinada sequência de luzes.</p>

# ⚙️Componentes
● Arduino Uno
● 3 Botões
● 3 leds
● 4 Resistores
● No Mimimo 30 Jumpers
● 2 Servos Motores
● 1 LCD I2C
● Uma caixa de MDF de 13x18,5 cm

# 📝Principais Funções do Codigo
- setup()  
Inicializa as configurações do Arduino, incluindo pinos, LCD e servos.
- loop()  
Loop principal que chama as funções de controle de cronômetro, botões e atualização do LCD.
- controleCronometro()  
Verifica o estado dos botões de início e pausa para controlar o cronômetro.
- controleBotoes()  
Lê o estado dos botões verde e vermelho e chama as funções apropriadas para cada um.
- trataBotaoVerde()  
Atualiza o estado dos LEDs RGB e contadores quando o botão verde é pressionado.
- trataBotaoVermelho()  
Atualiza o estado dos LEDs RGB e contadores quando o botão vermelho é pressionado.
- verificaCondicoesLEDs()  
Verifica se três LEDs verdes ou vermelhos estão acesos e controla os servos de acordo.
- resetaLEDs()  
Desliga todos os LEDs RGB.
- atualizaCronometro()  
Atualiza o cronômetro no LCD quando ele está em execução.
##  Bibliotecas Utilizadas
- Wire.h: Comunicação I2C para o LCD.
- LiquidCrystal_I2C.h: Controle do LCD via I2C.
- Servo.h: Controle dos servos motores.
## Como isntalar o codigo
- Baixe o Arduine IDE na sua máquina, instale as bibliotecas necessárias e logo após isso copie o codigo dentro da IDE. No mais, certifique-se de
verificar se todos os botões e led estão localizados nas posições corretas conforme o código, após isso selecione dentro da IDE a porta logica necessária 
para a conexão do prototipo com sua máquina e pode complilar o codigo.
## Link dos tutorias
 - 
 -  
## 🙋‍♂️ Criado por:
- [Matheus Lustosa](https://github.com/MatheusLustosa)
- [Rodrigo Tenório](https://github.com/RodrigoBLT)
- [Pedro Barreto](https://github.com/pedromb2005)
