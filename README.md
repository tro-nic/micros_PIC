<div align="center">

  <h1>🔌 Microcontroladores PIC: Análisis, Drivers y Aplicaciones</h1>
  
  <p>
    <strong>Repositorio dedicado al desarrollo de firmware, análisis de arquitectura y control de periféricos con microcontroladores Microchip PIC (8 bits).</strong>
  </p>

  <!-- Badges de tecnologías -->
  <p>
    <img src="https://img.shields.io/badge/Microchip-PIC_8--bit-ED1C24?style=for-the-badge&logo=microchip&logoColor=white" alt="Microchip PIC" />
    <img src="https://img.shields.io/badge/Lenguaje-C_%2F_ASM-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C y Ensamblador" />
    <img src="https://img.shields.io/badge/Protocolos-I2C_%7C_SPI_%7C_UART_%7C_USB-2EA44F?style=for-the-badge" alt="Protocolos" />
    <img src="https://img.shields.io/badge/Hardware-Tproto_DevBoard-F39C12?style=for-the-badge" alt="Tproto DevBoard" />
  </p>

</div>

<hr />

<h2>🧠 Microcontroladores Analizados y Utilizados</h2>
<p>Los dispositivos están organizados según su gama y arquitectura interna:</p>

<table>
  <thead>
    <tr>
      <th align="left">Familia / Arquitectura</th>
      <th align="left">Modelos</th>
      <th align="left">Características Destacadas</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Gama Base (12-bit core)</strong><br><code>PIC12F5xx</code></td>
      <td>
        • <code>PIC12F508</code><br>
        • <code>PIC12F509</code>
      </td>
      <td>8 pines, bajo costo, tareas de control lógico sencillo y temporización básica.</td>
    </tr>
    <tr>
      <td><strong>Gama Media (14-bit core)</strong><br><code>PIC12F6xx</code> / <code>PIC16Fxxx</code></td>
      <td>
        • <code>PIC12F683</code><br>
        • <code>PIC16F84</code> / <code>PIC16F84A</code><br>
        • <code>PIC16F88</code><br>
        • <code>PIC16F628</code> / <code>PIC16F648</code><br>
        • <code>PIC16F676</code><br>
        • <code>PIC16F872</code> / <code>PIC16F873</code> / <code>PIC16F877</code>
      </td>
      <td>Arquitectura clásica, módulos CCP (PWM), ADC de 10 bits, USART y comparadores analógicos.</td>
    </tr>
    <tr>
      <td><strong>Gama Media Mejorada</strong><br><code>PIC16F1xxxx</code></td>
      <td>
        • <code>PIC16F1619</code>
      </td>
      <td>Periféricos independientes del núcleo (CIP), CLC, CWG y mayor eficiencia energética.</td>
    </tr>
    <tr>
      <td><strong>Gama Alta (16-bit core)</strong><br><code>PIC18Fxxxx</code> / <code>Q10</code></td>
      <td>
        • <code>PIC18F4550</code> / <code>PIC18F45K50</code><br>
        • <code>PIC18F25Q10</code> / <code>PIC18F47Q10</code>
      </td>
      <td>Conectividad USB 2.0 nativa, multiplicador por hardware, PPS (Peripheral Pin Select) y alta velocidad de reloj.</td>
    </tr>
  </tbody>
</table>

<br />

<h2>🛠️ Periféricos, Protocolos y Hardware Asociado</h2>

<table>
  <thead>
    <tr>
      <th align="left">Categoría</th>
      <th align="left">Componentes y Tecnologías</th>
      <th align="left">Interfaz / Notas</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>🖥️ Visualización (Displays)</strong></td>
      <td>
        • Pantalla LCD alfanumérica <code>2x16</code><br>
        • Displays de <code>7 segmentos</code><br>
        • Pantalla OLED <code>SSD1306</code>
      </td>
      <td>
        • Modo paralelo (4/8 bits)<br>
        • Multiplexación directa / decodificadores<br>
        • Bus <code>I2C</code>
      </td>
    </tr>
    <tr>
      <td><strong>💾 Memoria y Almacenamiento</strong></td>
      <td>
        • Memorias EEPROM serie <code>24CXX</code><br>
        • Ranura para tarjeta <code>SD</code> (integrada en <em>Tproto</em>)
      </td>
      <td>
        • Bus <code>I2C</code><br>
        • Bus <code>SPI</code> (sistemas de archivos / registro de datos)
      </td>
    </tr>
    <tr>
      <td><strong>⚡ Potencia y Control de Motores</strong></td>
      <td>
        • Motores DC<br>
        • Drivers puente H / controladores de motor<br>
        • Drivers de compuerta para MOSFET<br>
        • Reguladores lineales, conmutados (PWM) y modulación FM
      </td>
      <td>
        • Control de velocidad y sentido mediante señales <code>PWM</code> y etapas de potencia aisladas.
      </td>
    </tr>
    <tr>
      <td><strong>🎛️ Plataformas de Desarrollo</strong></td>
      <td>
        • <strong>Tarjeta Tproto DevBoard</strong>
      </td>
      <td>
        • Placa de prototipado propia con soporte para encapsulados DIP-40 (<code>PIC18F45K50</code> / <code>PIC18F47Q10</code>) y periféricos integrados.
      </td>
    </tr>
  </tbody>
</table>

<br />

<h2>📂 Estructura del Repositorio</h2>
<pre>
micros_PIC/
├── PIC12F/          # Códigos y pruebas para encapsulados de 8 pines
├── PIC16F/          # Proyectos de gama media y gama media mejorada
├── PIC18F/          # Aplicaciones avanzadas, USB, SPI y serie Q10
├── Librerias/       # Drivers reutilizables (LCD, SSD1306, I2C, EEPROM)
└── Hardware/        # Esquemáticos y notas de la placa Tproto
</pre>

<div align="center">
  <p><sub>Desarrollado y documentado para experimentación e ingeniería embebida.</sub></p>
</div>
