ESP32-P4 

esp-dev-kits 文档

## Table of contents

Table of contents i
1 ESP32-P4X-Function-EV-Board 3
1.1 ESP32-P4X-Function-EV-Board . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 3
1.1.1 入门指南 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 3
1.1.2 硬件参考 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 11
1.1.3 硬件版本 . . . . . . . . . . . . . . . 14
1.1.4 相关文档 14
2 ESP32-P4X-EYE 15
2.1 ESP32-P4X-EYE 15
2.1.1 入门指南 15
2.1.2 硬件参考 22
2.1.3 硬件版本 25
2.1.4 相关文档 25
3 寿命终止开发板 29
3.1 ESP32-P4-Function-EV-Board 29
3.1.1 ESP32-P4-Function-EV-Board v1.5.2 29
3.2 ESP32-P4-EYE 45
3.2.1 ESP32-P4-EYE 45
4 相关文档和资源 59
4.1 开发者社区 59
4.2 产品 59
4.3 联系我们 59
5 免责声明和版权公告 61

该文档详细介绍了 ESP32-P4系列开发板的用户指南和示例。

备注: 如需获取乐鑫全部系列开发板的有关信息，请访问 乐鑫开发板概览。

# ESP32-P4X-Function-EV-Board

ESP32-P4X-Function-EV-Board 是一款基于 ESP32-P4 芯片的多媒体开发板。ESP32-P4 搭载双核 RISC-V处理器，支持最大 32 MB PSRAM。此外，ESP32-P4 支持 USB 2.0 标准, MIPI-CSI/DSI, H264 Encoder 等多种外设，可满足客户对低成本、高性能、低功耗的多媒体产品的开发需求。

## 1.1 ESP32-P4X-Function-EV-Board

备注: 搭载 ESP32-P4 芯片版本 v3.1 的 ESP32-P4X-Function-EV-Board 不支持安全下载功能，请不要启用安全下载模式。详情请见 ESP32-P4系列芯片勘误表 > ROM-770。

要识别所使用的芯片版本，请查看 ESP32-P4 系列芯片勘误表 > 芯片版本标识。

本指南将帮助您快速上手 ESP32-P4X-Function-EV-Board，并提供该款开发板的详细信息。

ESP32-P4X-Function-EV-Board 是一款基于 ESP32-P4 芯片的多媒体开发板。ESP32-P4 搭载双核 RISC-V处理器，支持最大 32 MB PSRAM。此外，ESP32-P4 支持 USB 2.0 标准, MIPI-CSI/DSI, H264 Encoder 等多种外设，可满足客户对低成本、高性能、低功耗的多媒体产品的开发需求。

此开发板搭载了 ESP32-C6-MINI-1 2.4 GHz Wi-Fi 6 & Bluetooth 5 (LE) 模组，用于该开发板的 Wi-Fi 和蓝牙通信；它还配置了一块7英寸电容式触摸屏，分辨率为1024 x 600，并配有一颗200万像素的MIPI CSI接口摄像头，丰富了用户的交互体验。该开发板适用于可视门铃、网络摄像头、智能家居中控屏、LCD电子价签、两轮车仪表盘等产品的原型构建。

板上模组大部分管脚均已引出至排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备。

本指南包括如下内容：

• 入门指南：简要介绍了 ESP32-P4X-Function-EV-Board 和硬件、软件设置指南。

• 硬件参考：详细介绍了 ESP32-P4X-Function-EV-Board 的硬件。

• 硬件版本：介绍硬件历史版本和已知问题，并提供链接至历史版本开发板的入门指南（如有）。

• 相关文档：列出了相关文档的链接。

## 1.1.1 入门指南

本小节将简要介绍 ESP32-P4X-Function-EV-Board，说明如何在 ESP32-P4X-Function-EV-Board 上烧录固件及相关准备工作。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/33d22ff4d30e63c8973d66d3ddeac0e293755ed93f270e5894a89bbdcd7e71c8.jpg)



图 1: ESP32-P4X-Function-EV-Board


## 组件介绍

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/b7b803b06545e5335b580316b80d748710bdf7799d3d4317c5d2e3bdb0703e83.jpg)



图 2: ESP32-P4X-Function-EV-Board - 正面（点击放大）



下面从 J1开始按照顺时针的顺序依次介绍开发板正面和背面的主要组件。


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/3f77b2d586dd783dadcd82e76a7b958aaf94679d96a47d65c80fb4f02b1c7d7b.jpg)



图 3: ESP32-P4X-Function-EV-Board - 背面（点击放大）


<table><tr><td>组件编号</td><td>主要组件</td><td>介绍</td></tr><tr><td>1</td><td>J1</td><td>所有可用 GPIO 管脚均已引出至排针 J1,详细信息请见排针。</td></tr><tr><td>2</td><td>ESP32-C6 Module Programming Connector (ESP32-C6模组固件烧录接口)</td><td>该接口可配合使用 ESP-Prog 或其他 UART 工具为 ESP32-C6 模组烧录固件。</td></tr><tr><td>3</td><td>ESP32-C6-MINI-1 Module (ESP32-C6-MINI-1 模组)</td><td>ESP32-C6-MINI-1 模组用于该开发板的 Wi-Fi 和蓝牙通信。</td></tr><tr><td>4</td><td>Microphone (麦克风)</td><td>板载麦克风,连接至 Audio Codec Chip 接口。</td></tr><tr><td>5</td><td>Reset Button (Reset键)</td><td>复位按键。</td></tr><tr><td>6</td><td>Audio Codec Chip(音频编解码芯片)</td><td>音频编解码器芯片 ES8311 是一种低功耗单声道音频编解码器,包含单通道 ADC、单通道 DAC、低噪声前置放大器、耳机驱动器、数字音效、模拟混音和增益功能。它通过 I2S 和 I2C 总线与 ESP32-P4 芯片连接,以提供独立于音频应用程序的硬件音频处理。</td></tr><tr><td>7</td><td>Speaker Output Port (扬声器输出端口)</td><td>该输出端口用于连接扬声器。最高输出功率可以驱动 4 Ω 3 W 扬声器,引脚间距为 2.00 mm/0.08”。</td></tr><tr><td>8</td><td>Audio PA Chip (音频功率放大器)</td><td>NS4150 是一款低 EMI、3 W 单声道 D 类音频功率放大器,用于放大来自音频编解码芯片的音频信号,以驱动扬声器。</td></tr><tr><td>9</td><td>5 V to 3.3 V LDO (5 V转 3.3 V LDO)</td><td>电源转换器,输入 5 V,输出 3.3 V。</td></tr><tr><td>10</td><td>BOOT Button (BOOT 键)</td><td>启动模式控制按键,保持按住 BOOT 键的同时按一下 Reset 键,ESP-P4 将重新启动并进入“固件下载”模式,这时可以通过 USB 串口/JTAG 接口下载固件到板载 SPI flash 中。</td></tr><tr><td>11</td><td>Ethernet PHY IC</td><td>以太网 PHY 芯片,与 ESP32-P4 EMAC RMII 接口和 RJ45 以太网模块端口连接。</td></tr><tr><td colspan="2">Expressif System Block Converter (降压转换器)</td><td>用于 3.3 V 电源的降压型 DC-DC 转换器。 Release master Submit Document Feedback</td></tr><tr><td>13</td><td>5 V Power-on LED (5 V 电源指示灯)</td><td>开发板通过任一 USB Type-C 接口连接电源后,该指示灯亮起。</td></tr><tr><td>19</td><td>Power Switch(电源开关)</td><td>电源开关。拨向ON一侧,开发板连接5V电源上电;拨离ON一侧,开发板断开5V电源掉电。</td></tr><tr><td>20</td><td>Switch(开关)</td><td>TPS2051C是一款USB电源开关,提供500mA输出电流限制。</td></tr><tr><td>21</td><td>MIPI CSI Connector (MIPI CSI连接器)</td><td>FPC连接器1.0K-GT-15PB,用以连接外接摄像头模组,实现图像传输,详情请见相关文档中的1.0K-GT-15PB规格书。适配的FPC规格:间距1.0mm,管脚宽度0.7mm,厚度0.3mm,管脚数量15。</td></tr><tr><td>22</td><td>Buck Converter(降压转换器)</td><td>用于VDD_HP电源的降压型DC-DC转换器。</td></tr><tr><td>23</td><td>ESP32-P4</td><td>ESP32-P4是一款高性能MCU,支持超大片上内存,具有强大的图像和语音处理能力。</td></tr><tr><td>24</td><td>40 MHz XTAL</td><td>40 MHz晶振,用于提供系统时钟。</td></tr><tr><td>25</td><td>32.768 kHz XTAL</td><td>32.768 kHz晶振,可提供Deep-sleep下使用的低功耗时钟。</td></tr><tr><td>26</td><td>MIPI DSI Connector (MIPI DSI连接器)</td><td>FPC连接器1.0K-GT-15PB,用以连接LCD扩展板,详情请见相关文档中的1.0K-GT-15PB规格书。适配的FPC规格:间距1.0mm,管脚宽度0.7mm,厚度0.3mm,管脚数量15。</td></tr><tr><td>27</td><td>SPI flash</td><td>通过SPI接口与ESP32-P4芯片连接,大小为16MB。</td></tr><tr><td>28</td><td>MicroSD Card Slot(MicroSD卡槽)</td><td>本开发板支持4-bit模式的MicroSD卡,可以存储或播放MicroSD卡中的音频文件。</td></tr></table>

备注: 关于 LDO_VO3 / LDO_VO4 的使用说明：

在 ESP32-P4X-Function-EV-Board 上，LDO_VO3 与 LDO_VO4 用于为板上部分 VDD 电源域供电。用户需在软件中配置正确的输出电压及使能状态。

在 Light-sleep 或 Deep-sleep 模式下，若 LDO_VO3 / LDO_VO4 保持使能，系统功耗将相对偏高；即使关闭，由于板级供电结构的影响，整体功耗仍可能高于芯片规格书中的典型低功耗指标。

如应用对功耗有严格要求，建议在自定义硬件设计中优化电源架构。

## 开发板配件

ESP32-P4X-Function-EV-Board 的包装盒中包含以下可选配件：

• 显示屏及其附件（可选）

– 7 英寸 MIPI DSI 电容式触摸屏，分辨率为 1024 x 600 像素

– LCD 屏幕适配板

– 附件包，包括杜邦线、屏幕排线、长铜柱（长度为 20 mm）、短铜柱（长度为8 mm）

• 摄像头及其附件（可选）

– 200 万像素 MIPI CSI 接口摄像头

– 摄像头适配板

– 摄像头排线

备注: 同向线序的排线为摄像头排线，其排线两侧的金属触点在同一面上；反向线序的排线为屏幕排线，其排线两侧的金属触点在不同面上。

## 应用示例

以下为开发板的应用示例：

• ESP_Brookesia Phone - 展示了一个类似安卓的界面，使用 ESP_Brookesia，利用开发板上的 MIPI-DSI、MIPI-CSI、ESP32-C6、SD卡和音频接口运行多个应用程序，为高效的多媒体应用开发提供了基础。


Ribbon Cable in the Forward Direction for Camera


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/c69414b02b1b0239f6aa7ed2ae30c59b6b30cf1a442381a365a20c5887a723ae.jpg)


## Strip


Ribbon Cable in the Reverse Direction for LCD


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/541a963422cb40e00c2a57727fc462c90cc844a691ce071b5a005a328f21fc3f.jpg)



图4: 正向和反向线序排线


• LVGL Demo v8 - 演示如何在配备 7 英寸 LCD 屏幕的 ESP32-P4X-Function-EV-Board 上移植 LVGLv8，并使用 LVGL的内置演示进行性能测试，为基于 LVGL v8 开发应用程序提供基础。

• LVGL Demo v9 - 演示如何在 ESP32-P4X-Function-EV-Board 上移植 LVGL v9 并使用 LVGL 内置的演示进行性能测试，作为基于 LVGL v9 开发应用程序的基础。

更多示例及最新更新请参阅 examples 文件夹。

也可以通过ESP Launchpad直接在浏览器中体验出厂示例及其他预编译示例。ESP Launchpad提供便捷的固件烧录方式，无需安装 ESP-IDF，也无需自行编译源代码。

如需尝试应用示例或开发自定义应用，请参照开始开发应用小节中的步骤进行操作。

## 开始开发应用

通电前，请确保 ESP32-P4X-Function-EV-Board 完好无损。

## 必备硬件

• ESP32-P4X-Function-EV-Board 

• USB 数据线

• 电脑（Windows、Linux 或 macOS）

## 备注: 请确保使用优质 USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

## 可选硬件

• MicroSD 卡

硬件设置 使用 USB 数据线将 ESP32-P4X-Function-EV-Board 连接到电脑，可通过任何一个 USB Type-C端口为开发板供电。建议使用 USB串口/JTAG接口烧录固件和调试。

下图展示了开发板、LCD 屏幕适配板和摄像头组装完成后的整体效果。主要组件说明请参考组装后的ESP32-P4X-Function-EV-Board 组件说明。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/208569526cfe76fedb5e8b253630d61ea73c77c2b5a1995505db692e7399c266.jpg)



图 5: 完整组装后的 ESP32-P4X-Function-EV-Board


如需使用显示屏，请按照以下步骤连接显示屏：

1. 用短铜柱将开发板固定在LCD 屏幕适配板中心的四个螺母柱上。

2. 用屏幕排线（反向线序）连接 LCD 屏幕适配板的 J3 排针和开发板的 MIPI DSI 连接器。LCD 屏幕适配板已与LCD 连接。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/d857ae0f1fdbf0fe700b850a1ec9d37902a7a8731b4baa81e94150ba84e7a4f2.jpg)



图6: LCD 屏幕排线细节


3. 用杜邦线将开发板 J1 排针的 GPIO27 引脚连接至 LCD 屏幕适配板 J6 排针的 RST_LCD 引脚。RST_LCD 对应的 GPIO 可由软件设置，默认为 GPIO27。

4. 用杜邦线将将开发板 J1 排针的 GPIO26 引脚连接至 LCD 屏幕适配板 J6 排针的 PWM 引脚。PWM对应的GPIO 可由软件设置，默认为 GPIO26。

5. 推荐使用外接 USB 供电连接 LCD 屏幕适配板 J1 排针对屏幕供电。如果条件不允许，也可以在开发板供电充足的情况下，使用杜邦线将开发板 J1 排针的 5V 与 GND 引脚连接至 LCD 屏幕适配板的 5V 与 GND 管脚。

连接关系如下表所示：


表1: 杜邦线连接表


<table><tr><td>ESP32-P4X-Function-EV</td><td>LCD 屏幕适配板</td></tr><tr><td>MIPI DSI 连接器</td><td>J3 排针</td></tr><tr><td>J1 排针 GPIO27 引脚</td><td>J6 排针 RST_LCD 引脚</td></tr><tr><td>J1 排针 GPIO26 引脚</td><td>J6 排针 PWM 引脚</td></tr><tr><td>J1 排针 5V 引脚</td><td>J6 排针 5V 引脚</td></tr><tr><td>J1 排针 GND 引脚</td><td>J6 排针 GND 引脚</td></tr></table>

6. 将长铜柱固定在 LCD 屏幕适配板四周的四个螺母柱上，可以将 LCD 立放。

备注:

• 如果使用外接USB供电连接LCD 屏幕适配板，则不需要连接 5V 和GND 引脚。

• 如需使用摄像头，请将摄像头排线（同向线序）连接至摄像头适配板和开发板的 MIPI CSI 连接器。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/1b7cb72f2396adcd7cbead2ac5534e4702f7c76a532050b59f452546b0b8575b.jpg)



图 7: 杜邦线连接细节



表 2: 组装后的 ESP32-P4X-Function-EV-Board 组件说明


<table><tr><td>组件编号</td><td>主要组件</td></tr><tr><td>1</td><td>Long Brass Standoff(长铜柱)</td></tr><tr><td>2</td><td>Camera Ribbon Cable(摄像头排线)</td></tr><tr><td>3</td><td>Short Brass Standoff(短铜柱)</td></tr><tr><td>4</td><td>USB Cable(USB 数据线)</td></tr><tr><td>5</td><td>LCD Ribbon Cable(LCD 屏幕排线)</td></tr><tr><td>6</td><td>GPIO27 to RST_LCD</td></tr><tr><td>7</td><td>GPIO26 to PWM</td></tr><tr><td>8</td><td>GND to GND</td></tr><tr><td>9</td><td>5V to 5V</td></tr><tr><td>10</td><td>Camera Front(摄像头正面)</td></tr></table>

软件设置 请前往 ESP-IDF 快速入门，查看如何快速设置开发环境，将应用程序烧录至您的开发板。

## 1.1.2 硬件参考

功能框图

ESP32-P4X-Function-EV-Board 的主要组件和连接方式如下图所示。

## 电源选项

可通过以下接口为开发板供电：

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/41238798826a61ab85869b57634479848ba9b529d1f68636aed754b51fd9fb2d.jpg)



图 8: 摄像头


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/bf42cc2dd393cc5231d405af6c9d358fecf27666df872b3343d4b3d602a04324.jpg)



图 9: ESP32-P4X-Function-EV-Board 功能框图（点击放大）


• USB 2.0 Type-C 接口

• USB 全速接口

• USB 串口/JTAG 接口

如果用于调试的 USB 数据线无法提供足够的电流，可通过空闲的 USB Type-C 接口连接电源适配器。

## 排针

下表列出了开发板排针 J1 的 名称和 功能，排针的名称如图ESP32-P4X-Function-EV-Board - 正面（点击放大） 所示，排针的序号与 ESP32-P4X-Function-EV-Board 参考设计 里的原理图一致。

<table><tr><td>序号</td><td>名称</td><td>类型1</td><td>功能</td></tr><tr><td>1</td><td>3V3</td><td>P</td><td>3.3 V 电源</td></tr><tr><td>2</td><td>5V</td><td>P</td><td>5 V 电源</td></tr><tr><td>3</td><td>7</td><td>I/O/T</td><td>GPIO7</td></tr><tr><td>4</td><td>5V</td><td>P</td><td>5 V 电源</td></tr><tr><td>5</td><td>8</td><td>I/O/T</td><td>GPIO8</td></tr><tr><td>6</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>7</td><td>23</td><td>I/O/T</td><td>GPIO23</td></tr><tr><td>8</td><td>37</td><td>I/O/T</td><td>U0TXD, GPIO37</td></tr><tr><td>9</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>10</td><td>38</td><td>I/O/T</td><td>U0RXD, GPIO38</td></tr><tr><td>11</td><td>21</td><td>I/O/T</td><td>GPIO21</td></tr><tr><td>12</td><td>22</td><td>I/O/T</td><td>GPIO22</td></tr><tr><td>13</td><td>20</td><td>I/O/T</td><td>GPIO20</td></tr><tr><td>14</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>15</td><td>6</td><td>I/O/T</td><td>GPIO6</td></tr><tr><td>16</td><td>5</td><td>I/O/T</td><td>GPIO5</td></tr><tr><td>17</td><td>3V3</td><td>P</td><td>3.3 V 电源</td></tr><tr><td>18</td><td>4</td><td>I/O/T</td><td>GPIO4</td></tr><tr><td>19</td><td>3</td><td>I/O/T</td><td>GPIO3</td></tr><tr><td>20</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>21</td><td>2</td><td>I/O/T</td><td>GPIO2</td></tr><tr><td>22</td><td>NC(1)</td><td>I/O/T</td><td><eq>\text{GPIO1}^2</eq></td></tr><tr><td>23</td><td>NC(0)</td><td>I/O/T</td><td><eq>\text{GPIO0}^2</eq></td></tr><tr><td>24</td><td>36</td><td>I/O/T</td><td>GPIO36</td></tr><tr><td>25</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>26</td><td>32</td><td>I/O/T</td><td>GPIO32</td></tr><tr><td>27</td><td>NC</td><td>-</td><td>空管脚</td></tr><tr><td>28</td><td>NC</td><td>-</td><td>空管脚</td></tr><tr><td>29</td><td>33</td><td>I/O/T</td><td>GPIO33</td></tr><tr><td>30</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>31</td><td>26</td><td>I/O/T</td><td>GPIO26</td></tr><tr><td>32</td><td>54</td><td>I/O/T</td><td>GPIO54</td></tr><tr><td>33</td><td>48</td><td>I/O/T</td><td>GPIO48</td></tr><tr><td>34</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>35</td><td>53</td><td>I/O/T</td><td>GPIO53</td></tr><tr><td>36</td><td>46</td><td>I/O/T</td><td>GPIO46</td></tr><tr><td>37</td><td>47</td><td>I/O/T</td><td>GPIO47</td></tr><tr><td>38</td><td>27</td><td>I/O/T</td><td>GPIO27</td></tr><tr><td>39</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>40</td><td>NC(45)</td><td>I/O/T</td><td><eq>\text{GPIO45}^3</eq></td></tr></table>

## J1

## 1.1.3 硬件版本

开发板 ESP32-P4X-Function-EV-Board 相较于ESP32-P4-Function-EV-Board 的区别是主芯片更新为 ESP32-P4芯片版本 v3.1及之后版本。

## 1.1.4 相关文档

请前往 esp-dev-kits 文档 HTML 网页版本 下载以下文档。

• ESP32-P4X-Function-EV-Board 参考设计 (ZIP)

• ESP32-P4 系列芯片勘误表

• 1.0K-GT-15PB 规格书 (PDF)

• 摄像头规格书 (PDF)

• 显示屏规格书 (PDF)

• 显示屏驱动芯片 EK73217BCGA 规格书 (PDF)

• 显示屏驱动芯片 EK79007AD 规格书 (PDF)

• 显示屏适配板原理图(PDF)

• 显示屏适配板 PCB 布局图 (PDF)

• 摄像头适配板原理图(PDF)

• 摄像头适配板 PCB 布局图 (PDF)

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

# ESP32-P4X-EYE

ESP32-P4X-EYE 是一款基于 ESP32-P4芯片的视觉开发板，主要面向摄像头应用。开发板的应用示例存放在 Examples 文件夹中。

## 2.1 ESP32-P4X-EYE

本指南将帮助您快速上手 ESP32-P4X-EYE，并提供该款开发板的详细信息。

ESP32-P4X-EYE 是一款基于 ESP32-P4 芯片的视觉开发板，主要面向摄像头应用。ESP32-P4 搭载双核RISC-V 处理器，支持最大 32 MB PSRAM。此外，ESP32-P4 支持 USB 2.0 标准, MIPI-CSI/DSI, H264 Encoder等多种外设，可满足客户对低成本、高性能、低功耗的多媒体产品的开发需求。

此开发板搭载了 ESP32-C6-MINI-1U 模组，用于该开发板的 Wi-Fi 和蓝牙通信；支持 MIPI-CSI 摄像头接口和USB 2.0 High-Speed从机模式。板载功能丰富，包括摄像头、显示屏、麦克风和MicroSD卡扩展，使得设备能够实时监测周围环境并采集图像、音频数据。适用于智能安防摄像头、视觉模型检测、物联网边缘计算等需要实时图像处理与无线通信的应用场景。

板上芯片大部分管脚均已引出至排母，开发人员可根据实际需求，轻松通过跳线连接多种外围设备。

本指南包括如下内容：

• 入门指南：简要介绍了 ESP32-P4X-EYE和硬件、软件设置指南。

• 硬件参考：详细介绍了 ESP32-P4X-EYE 的硬件。

• 硬件版本：介绍硬件历史版本和已知问题，并提供链接至历史版本开发板的入门指南（如有）。

• 相关文档：列出了相关文档的链接。

## 2.1.1 入门指南

本节介绍如何开始使用 ESP32-P4X-EYE。首先，介绍一些关于 ESP32-P4X-EYE 的基本信息，然后在应用程序开发 章节介绍如何开始使用该开发板进行开发。

## 组件介绍

以下按照顺时针的顺序依次介绍正面 PCB 上的主要组件。为了方便用户使用，我们同时在 ESP32-P4XEYE 的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/8f1d529fb50a72695dae3dcf32afd346fa5ab9be63b4f625b8c73d7ec46082f3.jpg)



图 1: ESP32-P4X-EYE 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/a4f49fa70ca71f6765db15b1cb2ad7dc2e092f108fc95232da0b22844ce0b989.jpg)



图 2: ESP32-P4X-EYE 背面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/f6c46b91adc247915334b9dfe2ca0316636bc42af779904ccf6c5f9920938c4a.jpg)



图 3: ESP32-P4X-EYE PCB 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/310208c25d057bf2fcac608612bf4c575af3af7726a89e3428f252606bc14e00.jpg)



图 4: ESP32-P4X-EYE 正面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td>MicroSD Card Slot (MicroSD卡槽)</td><td>支持通过4线SD总线连接MicroSD卡,兼容SDIO协议与SPI协议两种通信模式。</td></tr><tr><td>Test Points(测试点)</td><td>用于对ESP32-C6-MINI-1U进行烧录测试的测试点,可焊接杜邦线。</td></tr><tr><td>USB 2.0 Device Port (USB 2.0Device接口)</td><td>USB 2.0 Device接口与ESP32-P4芯片的USB 2.0 OTG High-Speed接口连接,支持USB 2.0标准。通过该接口进行USB通讯时,ESP32-P4作为USB Device设备与其他USB Host设备连接。该接口也可用作开发板的供电接口,外壳上以USB 2.0符号标识。</td></tr><tr><td>USB Debug Port (USB Debug接口)</td><td>该接口可用作开发板的供电接口,可烧录固件至芯片,也可作为通信接口,与ESP32-P4芯片上的USB Serial JTAG接口连接。外壳上以Debug符号标识。</td></tr><tr><td>Power Switch(电源开关)</td><td>电源开关。拨向I一侧,开发板连接5V电源上电;拨向○一侧,开发板断开5V电源掉电。</td></tr><tr><td>User-defined Buttons(用户自定义按键)</td><td>用户可根据应用自定义相关功能。</td></tr><tr><td>LCD FPC Connector(屏幕连接器)</td><td>用于连接1.54英寸LCD屏幕。</td></tr><tr><td>LCD</td><td>1.54英寸LCD,SPI接口,分辨率为240x240,支持Camera图像实时显示。详细参数请参考显示屏规格书。</td></tr><tr><td>Charging Indicator(充电指示灯)</td><td>为电池充电时,充电指示灯为红色;充电完成后,指示灯变为绿色。</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/e7a29551cf83faf22320b5b21d36dd54492981bc8645fafa8365002a846fcded.jpg)



图 5: ESP32-P4X-EYE 开发板背面图（点击放大）


以下按照顺时针的顺序依次介绍背面 PCB 上的主要组件。为了方便用户使用，我们同时在 ESP32-P4XEYE 的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/9e67d51144e3d3497cf86441597a100652700af5041fafed348d2d9ba324b927.jpg)



图 6: ESP32-P4X-EYE 背面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td>Rotary Encoder(旋转编码器)</td><td>用户可根据应用自定义相关功能,比如可用于拨动控制LCD界面和摄像头像素缩放。</td></tr><tr><td>ESP32-C6-MINI-1U</td><td>ESP32-C6-MINI-1U模组用于该开发板的Wi-Fi和蓝牙通信。</td></tr><tr><td>Fill Light(补光灯)</td><td>用于拍照录像时补光。</td></tr><tr><td>Digital Microphone(数字麦克风)</td><td>用于语音识别或者录制视频时收音。</td></tr><tr><td>MIPI CSI Connector(MIPI CSI连接器)</td><td>用于连接摄像头模组。</td></tr><tr><td>Female Header(排母)</td><td>2 x 10P排母,用户可根据应用进行自定义。</td></tr><tr><td>SPI flash</td><td>通过SPI接口与ESP32-P4芯片连接,大小为16 MB。</td></tr><tr><td>ESP32-P4</td><td>ESP32-P4是一款高性能MCU,支持超大片上内存,具有强大的图像和语音处理能力。</td></tr><tr><td>Battery Connector(电池接口)</td><td>用于连接锂电池。</td></tr><tr><td>Reset Button (Reset 键)</td><td>复位按键,外壳上以符号标识。</td></tr><tr><td>Boot Button (Boot 键)</td><td>启动模式控制按键,外壳上以符号标识。保持按住Boot键的同时按一下Reset键,ESP-P4将重新启动并进入“固件下载”模式,这时可以通过USB Debug接口下载固件到板载SPI flash中。正常使用中可以作为确认按钮。</td></tr><tr><td>Camera</td><td>分辨率为200万像素,可旋转摄像头进行手动聚焦。详细参数请参考摄像头规格书。</td></tr></table>

## 应用示例

以下为开发板的应用示例：

• Factory Demo - 展示了一个基于 ESP32-P4X-EYE 的全功能迷你相机方案。它不仅实现了拍照、定时拍照、录像、相册预览、USB SD卡挂载和图像参数设置等基础相机功能，还集成了先进的AI视觉能力，包括面部检测、行人检测和基于 YOLOv11nano 模型的实时物体检测。

更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照应用程序开发小节中的步骤进行操作。

## 应用程序开发

通电前，请确保 ESP32-P4X-EYE 完好无损。

## 必备硬件

• ESP32-P4X-EYE 

• USB 数据线

• 电脑（Windows、Linux 或 macOS）

## 备注: 请确保使用优质 USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

## 可选硬件

• MicroSD 卡

• 锂电池

硬件设置 使用 USB 数据线将 ESP32-P4X-EYE 连接到电脑，可通过 USB 2.0 Device 接口或 USBDebug 接口为开发板供电。建议使用USB Debug 接口烧录固件和调试。

软件设置 请前往 快速入门中详细安装步骤 一节查看如何快速设置开发环境。

## 2.1.2 硬件参考

## 功能框图

ESP32-P4X-EYE 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/7c6bdf712f74d34149b6df898717ee40f4af7d9dfb0d0172099e80fb9cc4d9e5.jpg)



图 7: ESP32-P4X-EYE 功能框图（点击放大）


## 电源选项

可通过以下方法为开发板供电：

1. 通过 USB 2.0 Device 接口或 USB Debug 接口供电

使用该方法供电时，应使用 USB Type-C 数据线将开发板通过上述任一接口连接至供电设备。如果已安装锂电池，会同时对锂电池进行充电。

2. 通过 电池接口使用外部锂电池供电

使用该方法供电时，应将外壳拆开，然后将电池接入电池接口。锂电池体积不超过4 mm x 25mm x 45 mm，使用1.25 mm 间距连接器，正负极需与开发板上标识保持一致。

排母

USB 2.0 Device 接口

LCD 接口

请注意，该接口支持连接SPI接口屏幕，该开发板使用的屏幕型号为ST7789，LCD_BL(GPIO20)可用于控制屏幕背光。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/196493d58fb6f275025b5a0665a825944331da5a800d8d791561bb4b295a5c80.jpg)



图 8: 电池连接图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/720fac31f6617bd5fdc3ae20e08d4f25187e67e0a192377054944408b46991ad.jpg)



图 9: 排母实物图（点击放大）


## USB HighSpeed & Power in:

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/8a585fbe59d374ac105bc66225baaec5bf56d008a139cf657b07f5ace8a571a4.jpg)



图 10: USB 2.0 Device 接口电路图（点击放大）


## 1.54 INCH LCD:

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/e00cec23b9c0ca6cf460fcd399bc88e061fbe3161bbe6cf407c1611971eb17c6.jpg)



图11: LCD 接口电路图（点击放大）


SD 卡接口

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/47cf407c80c5295b32011f9965adae0fb8ec7b924ea7f1e9a4419d9116fb24a5.jpg)



图 12: SD 卡接口电路图（点击放大）


## 请注意，SD 卡接口支持：

• 1-线和 4-线的 SD 总线配置

• 可通过SDIO 协议或 SPI协议通信

充电电路

麦克风接口

摄像头接口

滚动编码器接口

ESP32-C6-MINI-1U 模组接口

## 2.1.3 硬件版本

开发板 ESP32-P4X-EYE 相较于ESP32-P4-EYE 的区别是主芯片更新为 ESP32-P4 芯片版本 v3.1 及之后版本。

## 2.1.4 相关文档

请前往 esp-dev-kits 文档 HTML 网页版本 下载以下文档。

• ESP32-P4X-EYE 参考设计 (ZIP)

• 摄像头规格书 (PDF)

• 显示屏规格书 (PDF)

• ST7789VW 规格书 (PDF)

• OV2710 概述 (PDF)

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/ee3487536316fcb6bbeb3f050bc98196ccf2693c2d2114a7337ad745af2c899e.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/c07d84dcbb36a96a25f0ada0c3ec75e0ba4f2d1aa0f1b00e8066f2b910bc1450.jpg)



图13: 充电电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/f07dda3a8ab6d5ebf8bdce0bda4449a0a833aaa619c3c727ab7ca6ed70f32b18.jpg)



图14: 麦克风接口电路图（点击放大）



I2C LevelShift:


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/2318ce5ac16f80979887b8bf806a0d35bb9788623310f73e4b6f9c069484f373.jpg)



图15: 摄像头接口电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/f9e53b87425631575f865bc957f8c0d3fcc5f65727b216798ab2b33c6f473724.jpg)



图16: 滚动编码器接口电路图（点击放大）



WiFi & BT Module:


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/15d87971f1f4242993b5cbe61e865644844238f7509ed9a4e8b397950757a91d.jpg)



图 17: ESP32-C6-MINI-1U 模组接口电路图（点击放大）


# Chapter 3

# 寿命终止开发板

本节包含 ESP32-P4 寿命终止开发板的用户指南，内容仅供参考。这些开发板虽然可能仍在市场上销售或在遗留系统中使用，但已停止接收更新、错误修复及官方支持。建议切换至新款开发板，以享受更优性能和更丰富的功能。

## 3.1 ESP32-P4-Function-EV-Board

ESP32-P4-Function-EV-Board 是一款基于 ESP32-P4 芯片的多媒体开发板。ESP32-P4 搭载双核 RISC-V 处理器，支持最大 32 MB PSRAM。此外，ESP32-P4 支持 USB 2.0 标准, MIPI-CSI/DSI, H264 Encoder 等多种外设，可满足客户对低成本、高性能、低功耗的多媒体产品的开发需求。

## 3.1.1 ESP32-P4-Function-EV-Board v1.5.2

更早版本：ESP32-P4-Function-EV-Board v1.4

备注: 若您使用的是搭载芯片版本 v3.x 的 ESP32-P4X-Function-EV-Board，请参阅此用户指南。

版本号v1.5.2指开发板的硬件版本。要识别所使用的芯片版本，请查看ESP32-P4系列芯片勘误表>芯片版本标识。

本指南将帮助您快速上手 ESP32-P4-Function-EV-Board，并提供该款开发板的详细信息。

ESP32-P4-Function-EV-Board 是一款基于 ESP32-P4 芯片的多媒体开发板。ESP32-P4 搭载双核 RISC-V 处理器，支持最大 32 MB PSRAM。此外，ESP32-P4 支持 USB 2.0 标准, MIPI-CSI/DSI, H264 Encoder 等多种外设，可满足客户对低成本、高性能、低功耗的多媒体产品的开发需求。

此开发板搭载了 ESP32-C6-MINI-1 2.4 GHz Wi-Fi 6 & Bluetooth 5 (LE) 模组，用于该开发板的 Wi-Fi 和蓝牙通信；它还配置了一块7英寸电容式触摸屏，分辨率为1024 x 600，并配有一颗200万像素的MIPI CSI接口摄像头，丰富了用户的交互体验。该开发板适用于可视门铃、网络摄像头、智能家居中控屏、LCD电子价签、两轮车仪表盘等产品的原型构建。

板上模组大部分管脚均已引出至排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备。

本指南包括如下内容：

• 入门指南：简要介绍了 ESP32-P4-Function-EV-Board 和硬件、软件设置指南。

• 硬件参考：详细介绍了 ESP32-P4-Function-EV-Board 的硬件。

• 硬件版本：介绍硬件历史版本和已知问题，并提供链接至历史版本开发板的入门指南（如有）。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/3942c093390f0a21121173c10c7be28cfbf8250a1b2b65453a07848bd3f6c88c.jpg)



图 1: ESP32-P4-Function-EV-Board


• 相关文档：列出了相关文档的链接。

## 入门指南

本小节将简要介绍 ESP32-P4-Function-EV-Board，说明如何在 ESP32-P4-Function-EV-Board 上烧录固件及相关准备工作。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/11942576c51fa584e6e1281bdb1ff253172dce9c390cd647144b441fdaa052d5.jpg)



图 2: ESP32-P4-Function-EV-Board - 正面（点击放大）



组件介绍 下面从 J1开始按照顺时针的顺序依次介绍开发板正面和背面的主要组件。


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/46560776349f8f79170eba381db3392f7d33ec51729b1bbfed6545c4a94ec84e.jpg)



图 3: ESP32-P4-Function-EV-Board - 背面（点击放大）


<table><tr><td>组件编号</td><td>主要组件</td><td>介绍</td></tr><tr><td>1</td><td>J1</td><td>所有可用 GPIO 管脚均已引出至排针 J1,详细信息请见排针。</td></tr><tr><td>2</td><td>ESP32-C6 Module Programming Connector (ESP32-C6模组固件烧录接口)</td><td>该接口可配合使用 ESP-Prog 或其他 UART 工具为 ESP32-C6 模组烧录固件。</td></tr><tr><td>3</td><td>ESP32-C6-MINI-1 Module (ESP32-C6-MINI-1 模组)</td><td>ESP32-C6-MINI-1 模组用于该开发板的 Wi-Fi 和蓝牙通信。</td></tr><tr><td>4</td><td>Microphone (麦克风)</td><td>板载麦克风,连接至 Audio Codec Chip 接口。</td></tr><tr><td>5</td><td>Reset Button (Reset键)</td><td>复位按键。</td></tr><tr><td>6</td><td>Audio Codec Chip(音频编解码芯片)</td><td>音频编解码器芯片 ES8311 是一种低功耗单声道音频编解码器,包含单通道 ADC、单通道 DAC、低噪声前置放大器、耳机驱动器、数字音效、模拟混音和增益功能。它通过 I2S 和 I2C 总线与 ESP32-P4 芯片连接,以提供独立于音频应用程序的硬件音频处理。</td></tr><tr><td>7</td><td>Speaker Output Port (扬声器输出端口)</td><td>该输出端口用于连接扬声器。最高输出功率可以驱动 4 Ω 3 W 扬声器,引脚间距为 2.00 mm/0.08”。</td></tr><tr><td>8</td><td>Audio PA Chip (音频功率放大器)</td><td>NS4150 是一款低 EMI、3 W 单声道 D 类音频功率放大器,用于放大来自音频编解码芯片的音频信号,以驱动扬声器。</td></tr><tr><td>9</td><td>5 V to 3.3 V LDO (5 V转 3.3 V LDO)</td><td>电源转换器,输入 5 V,输出 3.3 V。</td></tr><tr><td>10</td><td>BOOT Button (BOOT 键)</td><td>启动模式控制按键,保持按住 BOOT 键的同时按一下 Reset 键,ESP-P4 将重新启动并进入“固件下载”模式,这时可以通过 USB 串口/JTAG 接口下载固件到板载 SPI flash 中。</td></tr><tr><td>11</td><td>Ethernet PHY IC</td><td>以太网 PHY 芯片,与 ESP32-P4 EMAC RMII 接口和 RJ45 以太网模块端口连接。</td></tr><tr><td colspan="2">Expressif System Block Converter (降压转换器)</td><td>用于 3.3 V 电源的降压型 DC-DC 转换器。 Release master Submit Document Feedback</td></tr><tr><td>13</td><td>5 V Power-on LED (5 V 电源指示灯)</td><td>开发板通过任一 USB Type-C 接口连接电源后,该指示灯亮起。</td></tr><tr><td>19</td><td>Power Switch(电源开关)</td><td>电源开关。拨向ON一侧,开发板连接5V电源上电;拨离ON一侧,开发板断开5V电源掉电。</td></tr><tr><td>20</td><td>Switch(开关)</td><td>TPS2051C是一款USB电源开关,提供500mA输出电流限制。</td></tr><tr><td>21</td><td>MIPI CSI Connector (MIPI CSI连接器)</td><td>FPC连接器1.0K-GT-15PB,用以连接外接摄像头模组,实现图像传输,详情请见相关文档中的1.0K-GT-15PB规格书。适配的FPC规格:间距1.0mm,管脚宽度0.7mm,厚度0.3mm,管脚数量15。</td></tr><tr><td>22</td><td>Buck Converter(降压转换器)</td><td>用于VDD_HP电源的降压型DC-DC转换器。</td></tr><tr><td>23</td><td>ESP32-P4</td><td>ESP32-P4是一款高性能MCU,支持超大片上内存,具有强大的图像和语音处理能力。</td></tr><tr><td>24</td><td>40 MHz XTAL</td><td>40 MHz晶振,用于提供系统时钟。</td></tr><tr><td>25</td><td>32.768 kHz XTAL</td><td>32.768 kHz晶振,可提供Deep-sleep下使用的低功耗时钟。</td></tr><tr><td>26</td><td>MIPI DSI Connector (MIPI DSI连接器)</td><td>FPC连接器1.0K-GT-15PB,用以连接LCD扩展板,详情请见相关文档中的1.0K-GT-15PB规格书。适配的FPC规格:间距1.0mm,管脚宽度0.7mm,厚度0.3mm,管脚数量15。</td></tr><tr><td>27</td><td>SPI flash</td><td>通过SPI接口与ESP32-P4芯片连接,大小为16MB。</td></tr><tr><td>28</td><td>MicroSD Card Slot(MicroSD卡槽)</td><td>本开发板支持4-bit模式的MicroSD卡,可以存储或播放MicroSD卡中的音频文件。</td></tr></table>

开发板配件 ESP32-P4-Function-EV-Board 的包装盒中包含以下可选配件：

• 显示屏及其附件（可选）

– 7 英寸 MIPI DSI 电容式触摸屏，分辨率为 1024 x 600 像素

– LCD 屏幕适配板

– 附件包，包括杜邦线、屏幕排线、长铜柱（长度为 20 mm）、短铜柱（长度为8 mm）

• 摄像头及其附件（可选）

– 200 万像素 MIPI CSI 接口摄像头

– 摄像头适配板

– 摄像头排线


Ribbon Cable in the Forward Direction for Camera


<table><tr><td colspan="6">AWM 20624 80C 60V VW-1</td><td colspan="5">AWM 20624 80C 60V VW-1</td></tr><tr><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td></tr><tr><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V VW-1</td></tr><tr><td>VW-1</td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C 60V</td></tr><tr><td>60V VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V VW-1</td><td></td><td></td><td>AWM</td><td>20624 80C</td></tr></table>

## Strip


Ribbon Cable in the Reverse Direction for LCD


<table><tr><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td></tr><tr><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td></tr><tr><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td></tr><tr><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td></tr><tr><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td></tr></table>


图4: 正向和反向线序排线


备注: 同向线序的排线为摄像头排线，其排线两侧的金属触点在同一面上；反向线序的排线为屏幕排线，

其排线两侧的金属触点在不同面上。

应用示例 以下为开发板的应用示例：

• ESP_Brookesia Phone - 展示了一个类似安卓的界面，使用 ESP_Brookesia，利用开发板上的 MIPI-DSI、MIPI-CSI、ESP32-C6、SD卡和音频接口运行多个应用程序，为高效的多媒体应用开发提供了基础。

• LVGL Demo v8 - 演示如何在配备 7 英寸 LCD 屏幕的 ESP32-P4-Function-EV-Board 上移植 LVGL v8并使用LVGL的内置演示进行性能测试，为基于 LVGL v8 开发应用程序提供基础。

• LVGL Demo v9 - 演示如何在 ESP32-P4-Function-EV-Board 上移植 LVGL v9 并使用 LVGL 内置的演示进行性能测试，作为基于 LVGL v9 开发应用程序的基础。

更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照开始开发应用小节中的步骤进行操作。

开始开发应用 通电前，请确保 ESP32-P4-Function-EV-Board 完好无损。

## 必备硬件

• ESP32-P4-Function-EV-Board 

• USB 数据线

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用优质 USB 数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

## 可选硬件

• MicroSD 卡

硬件设置 使用 USB 数据线将 ESP32-P4-Function-EV 连接到电脑，可通过任何一个 USB Type-C 端口为开发板供电。建议使用 USB 串口/JTAG 接口烧录固件和调试。

如需使用显示屏，请按照以下步骤连接显示屏：

1. 用短铜柱将开发板固定在LCD 屏幕适配板中心的四个螺母柱上。

2. 用屏幕排线（反向线序）连接 LCD 屏幕适配板的 J3 排针和开发板的 MIPI DSI 连接器。LCD 屏幕适配板已与LCD 连接。

3. 用杜邦线将LCD屏幕适配板J6排针的RST_LCD引脚连接到开发板J1排针的GPIO27引脚。使用时RST_LCD 由ESP32-P4 芯片控制，具体引脚可由软件设置，默认为 GPIO27。

4. 用杜邦线将 LCD 屏幕适配板 J6 排针的 PWM 引脚连接到开发板 J1 排针的 GPIO26 引脚。使用时PWM由 ESP32-P4芯片控制，具体引脚可由软件设置，默认为 GPIO26。

5. 推荐使用外接 USB 供电连接 LCD 屏幕适配板 J1 排针对屏幕供电。如果条件不允许，也可以在开发板供电充足的情况下，使用杜邦线将 LCD 屏幕适配板的 5V 与 GND 管脚连接到开发板的 J1 排针的 5V与 GND引脚。

6. 将长铜柱固定在 LCD 屏幕适配板四周的四个螺母柱上，可以将 LCD 立放。

连接关系如下表所示：

<table><tr><td>LCD屏幕适配板</td><td>ESP32-P4-Function-EV</td></tr><tr><td>J3排针</td><td>MIPI DSI连接器</td></tr><tr><td>J6排针RST_LCD引脚</td><td>J1排针GPIO27引脚</td></tr><tr><td>J6排针PWM引脚</td><td>J1排针GPIO26引脚</td></tr><tr><td>J6排针5V引脚</td><td>J1排针5V引脚</td></tr><tr><td>J6排针GND引脚</td><td>J1排针GND引脚</td></tr></table>

备注:

• 如果使用外接USB供电连接LCD 屏幕适配板，则不需要连接 5V 和GND 引脚。

• 如需使用摄像头，请将摄像头排线（同向线序）连接至摄像头适配板和开发板的 MIPI CSI 连接器。

软件设置 请前往 ESP-IDF 快速入门，查看如何快速设置开发环境，将应用程序烧录至您的开发板。

硬件参考

功能框图 ESP32-P4-Function-EV-Board 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/49bdcc1de5b318ab08f0376b702da6773d22ba2c3d0d5f12cbfb5cf8baa53dbe.jpg)



图 5: ESP32-P4-Function-EV-Board 功能框图（点击放大）


电源选项 可通过以下接口为开发板供电：

• USB 2.0 Type-C 接口

• USB 全速接口

• USB 串口/JTAG 接口

如果用于调试的 USB数据线无法提供足够的电流，可通过空闲的 USB Type-C 接口连接电源适配器。

排针 下表列出了开发板排针 J1 的 名称和 功能，排针的名称如图ESP32-P4-Function-EV-Board - 正面（点击放大） 所示，排针的序号与 ESP32-P4-Function-EV-Board 原理图 一致。

<table><tr><td>序号</td><td>名称</td><td>类型<eq>^{Page 36,1}</eq></td><td>功能</td></tr><tr><td>1</td><td>3V3</td><td>P</td><td>3.3 V电源</td></tr><tr><td>2</td><td>5V</td><td>P</td><td>5 V电源</td></tr><tr><td>3</td><td>7</td><td>I/O/T</td><td>GPIO7</td></tr><tr><td>4</td><td>5V</td><td>P</td><td>5 V电源</td></tr><tr><td>5</td><td>8</td><td>I/O/T</td><td>GPIO8</td></tr><tr><td>6</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>7</td><td>23</td><td>I/O/T</td><td>GPIO23</td></tr><tr><td>8</td><td>37</td><td>I/O/T</td><td>U0TXD, GPIO37</td></tr><tr><td>9</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>10</td><td>38</td><td>I/O/T</td><td>U0RXD, GPIO38</td></tr><tr><td>11</td><td>21</td><td>I/O/T</td><td>GPIO21</td></tr><tr><td>12</td><td>22</td><td>I/O/T</td><td>GPIO22</td></tr><tr><td>13</td><td>20</td><td>I/O/T</td><td>GPIO20</td></tr><tr><td>14</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>15</td><td>6</td><td>I/O/T</td><td>GPIO6</td></tr><tr><td>16</td><td>5</td><td>I/O/T</td><td>GPIO5</td></tr><tr><td>17</td><td>3V3</td><td>P</td><td>3.3 V电源</td></tr><tr><td>18</td><td>4</td><td>I/O/T</td><td>GPIO4</td></tr><tr><td>19</td><td>3</td><td>I/O/T</td><td>GPIO3</td></tr><tr><td>20</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>21</td><td>2</td><td>I/O/T</td><td>GPIO2</td></tr><tr><td>22</td><td>NC(1)</td><td>I/O/T</td><td><eq>GPIO1^2</eq></td></tr><tr><td>23</td><td>NC(0)</td><td>I/O/T</td><td><eq>GPIO0^2</eq></td></tr><tr><td>24</td><td>36</td><td>I/O/T</td><td>GPIO36</td></tr><tr><td>25</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>26</td><td>32</td><td>I/O/T</td><td>GPIO32</td></tr><tr><td>27</td><td>NC</td><td>-</td><td>空管脚</td></tr><tr><td>28</td><td>NC</td><td>-</td><td>空管脚</td></tr><tr><td>29</td><td>33</td><td>I/O/T</td><td>GPIO33</td></tr><tr><td>30</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>31</td><td>26</td><td>I/O/T</td><td>GPIO26</td></tr><tr><td>32</td><td>54</td><td>I/O/T</td><td>GPIO54</td></tr><tr><td>33</td><td>48</td><td>I/O/T</td><td>GPIO48</td></tr><tr><td>34</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>35</td><td>53</td><td>I/O/T</td><td>GPIO53</td></tr><tr><td>36</td><td>46</td><td>I/O/T</td><td>GPIO46</td></tr><tr><td>37</td><td>47</td><td>I/O/T</td><td>GPIO47</td></tr><tr><td>38</td><td>27</td><td>I/O/T</td><td>GPIO27</td></tr><tr><td>39</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>40</td><td>NC(45)</td><td>I/O/T</td><td><eq>GPIO45^3</eq></td></tr></table>

## J1

硬件版本

首次发布

备注: 开发板 v1.52 版本相较于 v1.4 版本的主要改进包括：将调试用的 USB-to-UART Type-C 接口替换为 ESP32-P4 芯片内置的 USB 串口/JTAG 接口，并新增了全速 USB OTG 至 Type-C 的接口引出。IO24、IO25 管脚不再引出到排针。

## 相关文档

请前往 esp-dev-kits 文档 HTML 网页版本 下载以下文档。

• ESP32-P4-Function-EV-Board 原理图 (PDF)

• ESP32-P4-Function-EV-Board PCB 布局图 (PDF)

• ESP32-P4-Function-EV-Board 元件位号图 (PDF)

• ESP32-P4-Function-EV-Board 尺寸图 (PDF)

• ESP32-P4-Function-EV-Board 尺寸图源文件 (DXF) - 可使用 Autodesk Viewer 查看

• 1.0K-GT-15PB 规格书 (PDF)

• 摄像头规格书 (PDF)

• 显示屏规格书 (PDF)

• 显示屏驱动芯片 EK73217BCGA 规格书 (PDF)

• 显示屏驱动芯片 EK79007AD 规格书 (PDF)

• 显示屏适配板原理图(PDF)

• 显示屏适配板 PCB 布局图 (PDF)

• 摄像头适配板原理图(PDF)

• 摄像头适配板 PCB 布局图 (PDF)

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

## ESP32-P4-Function-EV-Board v1.4

最新版本：ESP32-P4-Function-EV-Board v1.5.2

备注: 若您使用的是搭载芯片版本 v3.x 的 ESP32-P4X-Function-EV-Board，请参阅此用户指南。

版本号 v1.4 指开发板的硬件版本。要识别所使用的芯片版本，请查看 ESP32-P4 系列芯片勘误表 > 芯片版本标识。

本指南将帮助您快速上手 ESP32-P4-Function-EV-Board，并提供该款开发板的详细信息。

ESP32-P4-Function-EV-Board 是一款基于 ESP32-P4 芯片的多媒体开发板。ESP32-P4 搭载双核 RISC-V 处理器，支持最大 32 MB PSRAM。此外，ESP32-P4 支持 USB 2.0 标准, MIPI-CSI/DSI, H264 Encoder 等多种外设，可满足客户对低成本、高性能、低功耗的多媒体产品的开发需求。

此开发板搭载了 ESP32-C6-MINI-1 2.4 GHz Wi-Fi 6 & Bluetooth 5 (LE) 模组，用于该开发板的 Wi-Fi 和蓝牙通信；它还配置了一块7英寸电容式触摸屏，分辨率为1024 x 600，并配有一颗200万像素的MIPI CS接口摄像头，丰富了用户的交互体验。该开发板适用于可视门铃、网络摄像头、智能家居中控屏、LCD电子价签、两轮车仪表盘等产品的原型构建。

板上模组大部分管脚均已引出至排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备。

本指南包括如下内容：

• 入门指南：简要介绍了 ESP32-P4-Function-EV-Board 和硬件、软件设置指南。

• 硬件参考：详细介绍了 ESP32-P4-Function-EV-Board 的硬件。

• 硬件版本：介绍硬件历史版本和已知问题，并提供链接至历史版本开发板的入门指南（如有）。

• 相关文档：列出了相关文档的链接。

入门指南 本小节将简要介绍 ESP32-P4-Function-EV-Board，说明如何在 ESP32-P4-Function-EV-Board 上烧录固件及相关准备工作。

组件介绍 以下按照顺时针的顺序依次介绍开发板上的主要组件。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/354abe1e534e8dfc33fbbb5efadfefc7ec2ceb891c1ca4555b624f8d0f630ddb.jpg)



图 6: ESP32-P4-Function-EV-Board


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/65784b7064233c74f680a5bddecfd9f265533b81a9c8e9109e7a07f31941670d.jpg)



图 7: ESP32-P4-Function-EV-Board - 正面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/86298b95b28d9269bd165d76c0c1384e5e635426364086829d0804be66db145f.jpg)



图 8: ESP32-P4-Function-EV-Board - 背面（点击放大）


<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>J1</td><td>所有可用 GPIO 管脚均已引出至排针 J1,详细信息请见排针。</td></tr><tr><td>ESP32-C6 Module Programming Connector (ESP32-C6 模组固件烧录接口)</td><td>该接口可配合使用 ESP-Prog 或其他 UART 工具为 ESP32-C6 模组烧录固件。</td></tr><tr><td>ESP32-C6-MINI-1 Module (ESP32-C6-MINI-1 模组)</td><td>ESP32-C6-MINI-1 模组用于该开发板的 Wi-Fi 和蓝牙通信。</td></tr><tr><td>Microphone (麦克风)</td><td>板载麦克风,连接至 Audio Codec Chip 接口。</td></tr><tr><td>Reset Button (Reset 键)</td><td>复位按键。</td></tr><tr><td>Audio Codec Chip (音频编解码芯片)</td><td>音频编解码器芯片 ES8311 是一种低功耗单声道音频编解码器,包含单通道 ADC、单通道 DAC、低噪声前置放大器、耳机驱动器、数字音效、模拟混音和增益功能。它通过 I2S 和 I2C 总线与 ESP32-P4 芯片连接,以提供独立于音频应用程序的硬件音频处理。</td></tr><tr><td>Speaker Output Port (扬声器输出端口)</td><td>该输出端口用于连接扬声器。最高输出功率可以驱动 4 Ω 3 W 扬声器,引脚间距为 2.00 mm/0.08”。</td></tr><tr><td>Audio PA Chip (音频功率放大器)</td><td>NS4150 是一款低 EMI、3 W 单声道 D 类音频功率放大器,用于放大来自音频编解码芯片的音频信号,以驱动扬声器。</td></tr><tr><td>5 V to 3.3 V LDO (5 V 转 3.3 V LDO)</td><td>电源转换器,输入 5 V,输出 3.3 V。</td></tr><tr><td>BOOT Button (BOOT 键)</td><td>启动模式控制按键,保持按住 BOOT 键的同时按一下 Reset 键,ESP-P4 将重新启动并进入“固件下载”模式,这时可以通过 USB 转 UART 接口下载固件到板载 SPI flash 中。</td></tr><tr><td>Ethernet PHY IC</td><td>以太网 PHY 芯片,与 ESP32-P4 EMAC RMII 接口和 RJ45 以太网模块端口连接。</td></tr><tr><td>Buck Converter (降压转换器)</td><td>用于 3.3 V 电源的降压型 DC-DC 转换器。</td></tr><tr><td>USB-to-UART Bridge Chip (USB 转 UART 桥接器)</td><td>单芯片 USB 转 UART 桥接器芯片 CP2102N,与 ESP32-P4 UART0 接口、CHIP_PU 及 GPIO35 管脚 (strapping pin) 连接,可提供高达 3 Mbps 的传输速率,用于固件下载和调试 log 打印,支持自动下载功能。</td></tr><tr><td>5 V Power-on LED (5 V 电源指示灯)</td><td>开发板通过任一 USB Type-C 接口连接电源后,该指示灯亮起。</td></tr><tr><td>RJ45 Ethernet Port (RJ45 以太网接口)</td><td>以太网接口,支持 10/100 Mbps 自适应。</td></tr><tr><td>USB-to-UART Port (USB 转 UART 接口)</td><td>USB Type-C 接口,可用作开发板的供电接口,可烧录固件至芯片,也可作为通信接口,通过板载 USB 转 UART 桥接器与 ESP32-P4 芯片通信。</td></tr><tr><td>USB Power-in Port (USB 电源输入接口)</td><td>开发板的 USB Type-C 供电接口。</td></tr><tr><td>USB 2.0 Type-C Port (USB 2.0 Type-C 接口)</td><td>USB 2.0 Type-C 接口与 ESP32-P4 芯片的 USB 2.0 OTG High-Speed 接口连接,支持 USB 2.0 标准。通过该接口进行 USB 通讯时,ESP32-P4 作为 USB Device 设备与其他 USB Host 设备连接。USB 2.0 Type-C 接口和 USB 2.0 Type-A 接口需要二选一使用,不能同时使用。该接口也可用作开发板的供电接口。</td></tr><tr><td>USB 2.0 Type-A Port (USB 2.0 Type-A 接口)</td><td>USB 2.0 Type-A 接口与 ESP32-P4 芯片的 USB 2.0 OTG High-Speed 接口连接,支持 USB 2.0 标准。通过该接口进行 USB 通讯时,ESP32-P4 作为 USB Host 与其它 USB device 设备连接,对外提供最高 500 mA 电流。USB 2.0 Type-C 接口和 USB 2.0 Type-A 接口需要二选一使用,不能同时使用。</td></tr><tr><td>Power Switch (电源开关)</td><td>电源开关。拨向 ON 一侧,开发板连接 5 V 电源上电;拨离 ON 一侧,开发板断开 5 V 电源掉电。</td></tr><tr><td>Switch(开关)</td><td>TPS2051C是一款USB电源开关,提供500mA输出电流限制。</td></tr><tr><td>MIPI CSI Connector(MIPI CSI连接器)</td><td>FPC连接器1.0K-GT-15PB,用以连接外接摄像头模组,实现图像传输,详情请见相关文档中的1.0K-GT-15PB规格书。适配的FPC规格:间距1.0mm,管脚宽度0.7mm,厚度0.3mm,管脚数量15。</td></tr><tr><td>Buck Converter(降压转换器)</td><td>用于VDD_HP电源的降压型DC-DC转换器。</td></tr><tr><td>ESP32-P4</td><td>ESP32-P4是一款高性能MCU,支持超大片上内存,具有强大的图像和语音处理能力。</td></tr><tr><td>40 MHz XTAL</td><td>40 MHz晶振,用于提供系统时钟。</td></tr><tr><td>32.768 kHz XTAL</td><td>32.768 kHz晶振,可提供Deep-sleep下使用的低功耗时钟。</td></tr><tr><td>MIPI DSI Connector(MIPI DSI连接器)</td><td>FPC连接器1.0K-GT-15PB,用以连接LCD扩展板,详情请见相关文档中的1.0K-GT-15PB规格书。适配的FPC规格:间距1.0mm,管脚宽度0.7mm,厚度0.3mm,管脚数量15。</td></tr><tr><td>SPI flash</td><td>通过SPI接口与ESP32-P4芯片连接,大小为16MB。</td></tr><tr><td>MicroSD Card Slot(MicroSD卡槽)</td><td>本开发板支持4-bit模式的MicroSD卡,可以存储或播放MicroSD卡中的音频文件。</td></tr></table>

## 开发板配件 ESP32-P4-Function-EV-Board 的包装盒中包含以下可选配件：

• 显示屏及其附件（可选）

– 7 英寸 MIPI DSI 电容式触摸屏，分辨率为 1024 x 600 像素

– LCD 屏幕适配板

– 附件包，包括杜邦线、屏幕排线、长铜柱（长度为 20 mm）、短铜柱（长度为8 mm）

• 摄像头及其附件（可选）

– 200 万像素 MIPI CSI 接口摄像头

– 摄像头适配板

– 摄像头排线


Ribbon Cable in the Forward Direction for Camera


<table><tr><td colspan="6">AWM 20024 80C 60V VW-1</td><td colspan="6">AWM 20024 80C 60V VW-1</td></tr><tr><td rowspan="2">1</td><td colspan="5">AWM 20624 80C 60V VW-1</td><td colspan="6">AWM 20624 80C 60V VW-1</td></tr><tr><td colspan="5">AWM 20624 80C 60V VW-1</td><td colspan="6">AWM 20624 80C 60V VW-1</td></tr><tr><td colspan="2">VW-1</td><td colspan="5">AWM 20624 80C 60V VW-1</td><td colspan="5">AWM 20624 80C 60V VW-1</td></tr><tr><td colspan="2">60V VW-1</td><td colspan="5">AWM 20624 80C 60V VW-1</td><td colspan="5">AWM 20624 80C 60V VW-1</td></tr></table>


Strip



Ribbon Cable in the Reverse Direction for LCD


<table><tr><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td></tr><tr><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td></tr><tr><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td></tr><tr><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td></tr><tr><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td><td>VW-1</td><td></td><td></td><td>AWM</td><td>20624</td><td>80C</td><td>60V</td></tr></table>


图9: 正向和反向线序排线


备注: 同向线序的排线为摄像头排线，其排线两侧的金属触点在同一面上；反向线序的排线为屏幕排线，其排线两侧的金属触点在不同面上。

应用示例 以下为开发板的应用示例：

• ESP_Brookesia Phone - 展示了一个类似安卓的界面，使用 ESP_Brookesia，利用开发板上的 MIPI-DSI、MIPI-CSI、ESP32-C6、SD卡和音频接口运行多个应用程序，为高效的多媒体应用开发提供了基础。

• LVGL Demo v8 - 演示如何在配备 7 英寸 LCD 屏幕的 ESP32-P4-Function-EV-Board 上移植 LVGL v8，并使用LVGL的内置演示进行性能测试，为基于 LVGL v8 开发应用程序提供基础。

• LVGL Demo v9 - 演示如何在 ESP32-P4-Function-EV-Board 上移植 LVGL v9 并使用 LVGL 内置的演示进行性能测试，作为基于 LVGL v9 开发应用程序的基础。

更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照开始开发应用小节中的步骤进行操作。

开始开发应用 通电前，请确保 ESP32-P4-Function-EV-Board 完好无损。

## 必备硬件

• ESP32-P4-Function-EV-Board 

• USB 数据线

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用优质 USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

## 可选硬件

• MicroSD 卡

硬件设置 使用 USB 数据线将 ESP32-P4-Function-EV 连接到电脑，可通过任何一个 USB Type-C 端口为开发板供电。建议使用 USB转UART接口烧录固件和调试。

如需使用显示屏，请按照以下步骤连接显示屏：

1. 用短铜柱将开发板固定在LCD 屏幕适配板中心的四个螺母柱上。

2. 用屏幕排线（反向线序）连接 LCD 屏幕适配板的 J3 排针和开发板的 MIPI DSI 连接器。LCD 屏幕适配板已与LCD 连接。

3. 用杜邦线将LCD屏幕适配板J6排针的RST_LCD引脚连接到开发板J1排针的GPIO27引脚。使用时RST_LCD 由ESP32-P4 芯片控制，具体引脚可由软件设置，默认为 GPIO27。

4. 用杜邦线将 LCD 屏幕适配板 J6 排针的 PWM 引脚连接到开发板 J1 排针的 GPIO26 引脚。使用时PWM由 ESP32-P4芯片控制，具体引脚可由软件设置，默认为 GPIO26。

5. 推荐使用外接 USB 供电连接 LCD 屏幕适配板 J1 排针对屏幕供电。如果条件不允许，也可以在开发板供电充足的情况下，使用杜邦线将 LCD 屏幕适配板的 5V 与 GND 管脚连接到开发板的 J1 排针的 5V与 GND引脚。

6. 将长铜柱固定在 LCD 屏幕适配板四周的四个螺母柱上，可以将 LCD 立放。

连接关系如下表所示：

<table><tr><td>LCD 屏幕适配板</td><td>ESP32-P4-Function-EV</td></tr><tr><td>J3 排针</td><td>MIPI DSI 连接器</td></tr><tr><td>J6 排针 RST_LCD 引脚</td><td>J1 排针 GPIO27 引脚</td></tr><tr><td>J6 排针 PWM 引脚</td><td>J1 排针 GPIO26 引脚</td></tr><tr><td>J6 排针 5V 引脚</td><td>J1 排针 5V 引脚</td></tr><tr><td>J6 排针 GND 引脚</td><td>J1 排针 GND 引脚</td></tr></table>

## 备注:

• 如果使用外接USB供电连接LCD 屏幕适配板，则不需要连接 5V 和GND 引脚。

续下页

• 如需使用摄像头，请将摄像头排线（同向线序）连接至摄像头适配板和开发板的 MIPI CSI 连接器。

软件设置 请前往 ESP-IDF 快速入门，查看如何快速设置开发环境，将应用程序烧录至您的开发板。

硬件参考

功能框图 ESP32-P4-Function-EV-Board 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/df04d2ba0f7922364297cca20f2b27b1567073f83ff944e4420a59fc200928d1.jpg)



图 10: ESP32-P4-Function-EV-Board v1.4（点击放大）



电源选项 可通过以下接口为开发板供电：



• USB 2.0 Type-C 接口



• USB 电源输入接口



• USB 转 UART 接口



如果用于调试的 USB数据线无法提供足够的电流，可通过空闲的 USB Type-C 接口连接电源适配器。


排针 下表列出了开发板排针 J1 的 名称和 功能，排针的名称如图ESP32-P4-Function-EV-Board - 正面（点击放大） 所示，排针的序号与 ESP32-P4-Function-EV-Board v1.4 原理图 一致。

<table><tr><td>序号</td><td>名称</td><td>类型Page 44,1</td><td>功能</td></tr><tr><td>1</td><td>3V3</td><td>P</td><td>3.3 V电源</td></tr><tr><td>2</td><td>5V</td><td>P</td><td>5 V电源</td></tr><tr><td>3</td><td>7</td><td>I/O/T</td><td>GPIO7</td></tr><tr><td>4</td><td>5V</td><td>P</td><td>5 V电源</td></tr><tr><td>5</td><td>8</td><td>I/O/T</td><td>GPIO8</td></tr><tr><td>6</td><td>GND</td><td>GND</td><td>接地</td></tr></table>


表 2 – 接上页


<table><tr><td>序号</td><td>名称</td><td>类型Page 44,1</td><td>功能</td></tr><tr><td>7</td><td>23</td><td>I/O/T</td><td>GPIO23</td></tr><tr><td>8</td><td>37</td><td>I/O/T</td><td>U0TXD, GPIO37</td></tr><tr><td>9</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>10</td><td>38</td><td>I/O/T</td><td>U0RXD, GPIO38</td></tr><tr><td>11</td><td>21</td><td>I/O/T</td><td>GPIO21</td></tr><tr><td>12</td><td>22</td><td>I/O/T</td><td>GPIO22</td></tr><tr><td>13</td><td>20</td><td>I/O/T</td><td>GPIO20</td></tr><tr><td>14</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>15</td><td>6</td><td>I/O/T</td><td>GPIO6</td></tr><tr><td>16</td><td>5</td><td>I/O/T</td><td>GPIO5</td></tr><tr><td>17</td><td>3V3</td><td>P</td><td>3.3 V电源</td></tr><tr><td>18</td><td>4</td><td>I/O/T</td><td>GPIO4</td></tr><tr><td>19</td><td>3</td><td>I/O/T</td><td>GPIO3</td></tr><tr><td>20</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>21</td><td>2</td><td>I/O/T</td><td>GPIO2</td></tr><tr><td>22</td><td>NC(1)</td><td>I/O/T</td><td><eq>\text{GPIO1}^2</eq></td></tr><tr><td>23</td><td>NC(0)</td><td>I/O/T</td><td><eq>\text{GPIO0}^2</eq></td></tr><tr><td>24</td><td>36</td><td>I/O/T</td><td>GPIO36</td></tr><tr><td>25</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>26</td><td>32</td><td>I/O/T</td><td>GPIO32</td></tr><tr><td>27</td><td>24</td><td>I/O/T</td><td>GPIO24</td></tr><tr><td>28</td><td>25</td><td>I/O/T</td><td>GPIO25</td></tr><tr><td>29</td><td>33</td><td>I/O/T</td><td>GPIO33</td></tr><tr><td>30</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>31</td><td>26</td><td>I/O/T</td><td>GPIO26</td></tr><tr><td>32</td><td>54</td><td>I/O/T</td><td>GPIO54</td></tr><tr><td>33</td><td>48</td><td>I/O/T</td><td>GPIO48</td></tr><tr><td>34</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>35</td><td>53</td><td>I/O/T</td><td>GPIO53</td></tr><tr><td>36</td><td>46</td><td>I/O/T</td><td>GPIO46</td></tr><tr><td>37</td><td>47</td><td>I/O/T</td><td>GPIO47</td></tr><tr><td>38</td><td>27</td><td>I/O/T</td><td>GPIO27</td></tr><tr><td>39</td><td>GND</td><td>GND</td><td>接地</td></tr><tr><td>40</td><td>NC(45)</td><td>I/O/T</td><td><eq>\text{GPIO45}^3</eq></td></tr></table>

## J1

硬件版本 该开发板为最新硬件，尚未有历史版本。

相关文档 请前往 esp-dev-kits文档 HTML 网页版本 下载以下文档。

• ESP32-P4-Function-EV-Board v1.4 原理图 (PDF)

• ESP32-P4-Function-EV-Board v1.4 PCB 布局图 (PDF)

• ESP32-P4-Function-EV-Board v1.4 尺寸图 (PDF)

• ESP32-P4-Function-EV-Board v1.4 尺寸图源文件 (DXF) - 可使用 Autodesk Viewer 查看

• 1.0K-GT-15PB 规格书 (PDF)

• 摄像头规格书 (PDF)

• 显示屏规格书 (PDF)

• 显示屏驱动芯片 EK73217BCGA 规格书 (PDF)

• 显示屏驱动芯片 EK79007AD 规格书 (PDF)

• 显示屏适配板原理图(PDF)

<sup>3</sup> 为启用 GPIO45，可将 R231 移动到 R100 以禁用 SD_PWRn 功能。

• 显示屏适配板 PCB 布局图 (PDF)

• 摄像头适配板原理图(PDF)

• 摄像头适配板 PCB 布局图 (PDF)

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

## 3.2 ESP32-P4-EYE

ESP32-P4-EYE是一款基于 ESP32-P4 芯片的视觉开发板，主要面向摄像头应用。

开发板的应用示例存放在 Examples 文件夹中。

## 3.2.1 ESP32-P4-EYE

备注: 若您使用的是搭载芯片版本 v3.x的ESP32-P4X-EYE，请参阅此用户指南。

要识别所使用的芯片版本，请查看 ESP32-P4 系列芯片勘误表 > 芯片版本标识。

本指南将帮助您快速上手 ESP32-P4-EYE，并提供该款开发板的详细信息。

ESP32-P4-EYE 是一款基于 ESP32-P4 芯片的视觉开发板，主要面向摄像头应用。ESP32-P4 搭载双核 RISC-V 处理器，支持最大 32 MB PSRAM。此外，ESP32-P4 支持 USB 2.0 标准, MIPI-CSI/DSI, H264 Encoder 等多种外设，可满足客户对低成本、高性能、低功耗的多媒体产品的开发需求。

此开发板搭载了 ESP32-C6-MINI-1U 模组，用于该开发板的 Wi-Fi 和蓝牙通信；支持 MIPI-CSI 摄像头接口和USB 2.0 High-Speed从机模式。板载功能丰富，包括摄像头、显示屏、麦克风和MicroSD卡扩展，使得设备能够实时监测周围环境并采集图像、音频数据。适用于智能安防摄像头、视觉模型检测、物联网边缘计算等需要实时图像处理与无线通信的应用场景。

板上芯片大部分管脚均已引出至排母，开发人员可根据实际需求，轻松通过跳线连接多种外围设备。

本指南包括如下内容：

• 入门指南：简要介绍了 ESP32-P4-EYE和硬件、软件设置指南。

• 硬件参考：详细介绍了 ESP32-P4-EYE 的硬件。

• 硬件版本：介绍硬件历史版本和已知问题，并提供链接至历史版本开发板的入门指南（如有）。

• 相关文档：列出了相关文档的链接。

## 入门指南

本节介绍如何开始使用ESP32-P4-EYE。首先，介绍一些关于ESP32-P4-EYE的基本信息，然后在应用程序开发 章节介绍如何开始使用该开发板进行开发。

组件介绍 以下按照顺时针的顺序依次介绍正面 PCB 上的主要组件。为了方便用户使用，我们同时在ESP32-P4-EYE的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/84f63d776996a0280f78c700d6c0e2717d40698f65cccfcf861d65704135e6b4.jpg)



图 11: ESP32-P4-EYE 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/41510383559e87f4ee26ef5f3ebc3c720690ffe8e2af5fddfb602d74a0fd580b.jpg)



图 12: ESP32-P4-EYE 背面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/dc2898409682123b6a49c044c0aadfeb79bb63d51bc4940f449965a8a48c5cd3.jpg)



图 13: ESP32-P4-EYE PCB 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/aa6d8893b5e68906c13d0fcb799097c0c63add7e6524ff5a68e3832367e482ed.jpg)



图 14: ESP32-P4-EYE 正面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td>MicroSD Card Slot (MicroSD卡槽)</td><td>支持通过4线SD总线连接MicroSD卡,兼容SDIO协议与SPI协议两种通信模式。</td></tr><tr><td>Test Points(测试点)</td><td>用于对ESP32-C6-MINI-1U进行烧录测试的测试点,可焊接杜邦线。</td></tr><tr><td>USB 2.0 Device Port (USB 2.0Device接口)</td><td>USB 2.0 Device接口与ESP32-P4芯片的USB 2.0 OTG High-Speed接口连接,支持USB 2.0标准。通过该接口进行USB通讯时,ESP32-P4作为USB Device设备与其他USB Host设备连接。该接口也可用作开发板的供电接口,外壳上以USB 2.0符号标识。</td></tr><tr><td>USB Debug Port (USB Debug接口)</td><td>该接口可用作开发板的供电接口,可烧录固件至芯片,也可作为通信接口,与ESP32-P4芯片上的USB Serial JTAG接口连接。外壳上以Debug符号标识。</td></tr><tr><td>Power Switch(电源开关)</td><td>电源开关。拨向I一侧,开发板连接5V电源上电;拨向○一侧,开发板断开5V电源掉电。</td></tr><tr><td>User-defined Buttons(用户自定义按键)</td><td>用户可根据应用自定义相关功能。</td></tr><tr><td>LCD FPC Connector(屏幕连接器)</td><td>用于连接1.54英寸LCD屏幕。</td></tr><tr><td>LCD</td><td>1.54英寸LCD,SPI接口,分辨率为240x240,支持Camera图像实时显示。详细参数请参考显示屏规格书。</td></tr><tr><td>Charging Indicator(充电指示灯)</td><td>为电池充电时,充电指示灯为红色;充电完成后,指示灯变为绿色。</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/708788b81d62ba35382d134fba33023d904dc1f7044c8b70d022256a08f0c0ed.jpg)



图 15: ESP32-P4-EYE 开发板背面图（点击放大）


以下按照顺时针的顺序依次介绍背面PCB上的主要组件。为了方便用户使用，我们同时在ESP32-P4-EYE的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/bbe1e90cd1b0a07e5877e8080535c3a94bbab82c3f76338d8f32e46295634e99.jpg)



图 16: ESP32-P4-EYE 背面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td>Rotary Encoder(旋转编码器)</td><td>用户可根据应用自定义相关功能,比如可用于拨动控制 LCD 界面和摄像头像素缩放。</td></tr><tr><td>ESP32-C6-MINI-1U</td><td>ESP32-C6-MINI-1U 模组用于该开发板的 Wi-Fi 和蓝牙通信。</td></tr><tr><td>Fill Light(补光灯)</td><td>用于拍照录像时补光。</td></tr><tr><td>Digital Microphone(数字麦克风)</td><td>用于语音识别或者录制视频时收音。</td></tr><tr><td>MIPI CSI Connector(MIPI CSI连接器)</td><td>用于连接摄像头模组。</td></tr><tr><td>Female Header(排母)</td><td>2 x 10P 排母,用户可根据应用进行自定义。</td></tr><tr><td>SPI flash</td><td>通过 SPI 接口与 ESP32-P4 芯片连接,大小为 16 MB。</td></tr><tr><td>ESP32-P4</td><td>ESP32-P4 是一款高性能 MCU,支持超大片上内存,具有强大的图像和语音处理能力。</td></tr><tr><td>Battery Connector(电池接口)</td><td>用于连接锂电池。</td></tr><tr><td>Reset Button (Reset 键)</td><td>复位按键,外壳上以 √ 符号标识。</td></tr><tr><td>Boot Button (Boot 键)</td><td>启动模式控制按键,外壳上以 ☑ 符号标识。保持按住 Boot 键的同时按一下 Reset 键,ESP-P4 将重新启动并进入“固件下载”模式,这时可以通过 USB Debug 接口下载固件到板载 SPI flash 中。正常使用中可以作为确认按钮。</td></tr><tr><td>Camera</td><td>分辨率为 200 万像素,可旋转摄像头进行手动聚焦。详细参数请参考摄像头规格书。</td></tr></table>

## 应用示例 以下为开发板的应用示例：

• Factory Demo - 展示了一个基于 ESP32-P4-EYE 的全功能迷你相机方案。它不仅实现了拍照、定时拍照、录像、相册预览、USB SD卡挂载和图像参数设置等基础相机功能，还集成了先进的AI视觉能力，包括面部检测、行人检测和基于 YOLOv11nano模型的实时物体检测。

更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照应用程序开发小节中的步骤进行操作。

应用程序开发 通电前，请确保 ESP32-P4-EYE完好无损。

## 必备硬件

• ESP32-P4-EYE 

• USB 数据线

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用优质 USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

## 可选硬件

• MicroSD 卡

• 锂电池

硬件设置 使用 USB 数据线将 ESP32-P4-EYE 连接到电脑，可通过 USB 2.0 Device 接口或 USBDebug 接口为开发板供电。建议使用USB Debug 接口烧录固件和调试。

软件设置 请前往 快速入门中详细安装步骤 一节查看如何快速设置开发环境。

## 硬件参考

功能框图 ESP32-P4-EYE 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/a749180f162aa64829ecedfb92ca921d61b186e8590055102a5aa64cd890c5d5.jpg)



图 17: ESP32-P4-EYE 功能框图（点击放大）


电源选项 可通过以下方法为开发板供电：

1. 通过 USB 2.0 Device 接口或 USB Debug 接口供电

使用该方法供电时，应使用 USB Type-C 数据线将开发板通过上述任一接口连接至供电设备。如果已安装锂电池，会同时对锂电池进行充电。

2. 通过 电池接口使用外部锂电池供电

使用该方法供电时，应将外壳拆开，然后将电池接入电池接口。锂电池体积不超过4 mm x 25mm x 45 mm，使用1.25 mm 间距连接器，正负极需与开发板上标识保持一致。

排母

USB 2.0 Device 接口

LCD 接口 请注意，该接口支持连接 SPI 接口屏幕，该开发板使用的屏幕型号为 ST7789，LCD_BL(GPIO20) 可用于控制屏幕背光。

SD 卡接口 请注意，SD 卡接口支持：

• 1-线和 4-线的 SD 总线配置

• 可通过SDIO 协议或 SPI协议通信

## 充电电路

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/9f842568496724691f63eee81be27c853efbc3cc7ded735dd59a5cf9814a4998.jpg)



图18: 电池连接图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/61d0d2702a22f9b2bd331b17d18f00aa988527b73cc8c0fb5081f130997b9c79.jpg)



图19: 排母实物图（点击放大）



USB HighSpeed & Power in:


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/eeea84656ef36aca4707ebeb2c35ca775381f73dd57eea33e90bb571c5a2f87e.jpg)



图 20: USB 2.0 Device 接口电路图（点击放大）


## 1.54 INCH LCD:

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/0e16aba5392843bb94dc2e7a94bedcd39b860eb00223db521ee7998398f2df98.jpg)



图21: LCD 接口电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/91c2ffb1d1aa4c4d3622943afc5644fec10bd73cc8ab1fbf18e6895998edb59e.jpg)



图 22: SD 卡接口电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/c7b4348f3b90eea775f917cad0ebb2c656b1fda33dbecdf7ada8d7d763f5489b.jpg)



图23: 充电电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/70d9c1dc9491f81eb9bc0cf56ad6a31f74e6e39230ce040d05b6311fd685b9d7.jpg)



图24: 麦克风接口电路图（点击放大）



麦克风接口


Camera Connector: 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/72144bc65868b6c58375d7bf3d27383512b2875f17fd184ba5c201668509112f.jpg)



图25: 摄像头接口电路图（点击放大）


摄像头接口

滚动编码器接口

ESP32-C6-MINI-1U 模组接口

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/34a2873d93ba2f707af8ad6db80acbba15c0dbeb530ec858ec708ee2e99ed606.jpg)



图26: 滚动编码器接口电路图（点击放大）



WiFi & BT Module:


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/1eb3a28feba129c873405f5d16ef00638d8d4232fc2f30baad53e770cc10c62c.jpg)



图 27: ESP32-C6-MINI-1U 模组接口电路图（点击放大）


## 硬件版本

该开发板为最新硬件，尚未有历史版本。

## 相关文档

请前往 esp-dev-kits 文档 HTML 网页版本 下载以下文档。

• ESP32-P4-EYE 原理图 (PDF)

• ESP32-P4-EYE PCB 布局图 (PDF)

• 摄像头规格书 (PDF)

• 显示屏规格书 (PDF)

• ST7789VW 规格书 (PDF)

• OV2710 概述 (PDF)


表 3: ESP32-P4 系列开发板


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/2bba9b997f70fd23a9dd48e3dbe7d0368bbead34412bb4a5923b70f71387051c.jpg)



ESP32-P4X-Function-EV-Board


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/6d572e9e-9d71-40ec-847a-b363bf8fcf54/97116ecad003972742779a2cdd0d1e9d398bfcf2cb13596c75cba2f5f5492c31.jpg)



ESP32-P4X-EYE


# Chapter 4

# 相关文档和资源

## 4.1 开发者社区

• ESP32-P4 ESP-IDF 编程指南 –ESP-IDF 开发框架的文档中心。

• ESP-IoT-Solution 编程指南 –ESP-IoT-Solution 开发框架的文档中心。

• ESP-FAQ-由乐鑫官方推出的针对常见问题的总结。

• ESP-IDF 及 GitHub 上的其它开发框架

https://github.com/espressif 

• ESP32 论坛–工程师对工程师 (E2E) 的社区，您可以在这里提出问题、解决问题、分享知识、探索观点。https://esp32.com/

• The ESP Journal –分享乐鑫工程师的最佳实践、技术文章和工作随笔。

https://blog.espressif.com/ 

• SDK和演示、App、工具、AT等下载资源https://espressif.com/zh-hans/support/download/sdks-demos

## 4.2 产品

• ESP32-P4 系列芯片–ESP32-P4 全系列芯片。

https://espressif.com/zh-hans/products/socs?id=ESP32-P4 

• ESP32-P4 系列模组–ESP32-P4 全系列模组。

https://espressif.com/zh-hans/products/modules?id=ESP32-P4 

• ESP32-P4 系列开发板–ESP32-P4 全系列开发板。

https://espressif.com/zh-hans/products/devkits?id=ESP32-P4 

• ESP Product Selector（乐鑫产品选型工具）–通过筛选性能参数、进行产品对比快速定位您所需要的产品。

https://products.espressif.com/#/product-selector 

## 4.3 联系我们

• 商务问题、技术支持、电路原理图& PCB设计审阅、购买样品（线上商店）、成为供应商、意见与建议

https://espressif.com/zh-hans/contact-us/sales-questions 

## Chapter 5

## 免责声明和版权公告

本文档中的信息，包括供参考的 URL 地址，如有变更，恕不另行通知。

本文档可能引用了第三方的信息，所有引用的信息均为“按现状”提供，乐鑫不对信息的准确性、真实性做任何保证。

乐鑫不对本文档的内容做任何保证，包括内容的适销性、是否适用于特定用途，也不提供任何其他乐鑫提案、规格书或样品在他处提到的任何保证。

乐鑫不对本文档是否侵犯第三方权利做任何保证，也不对使用本文档内信息导致的任何侵犯知识产权的行为负责。本文档在此未以禁止反言或其他方式授予任何知识产权许可，不管是明示许可还是暗示许可。

Wi-Fi 联盟成员标志归 Wi-Fi 联盟所有。蓝牙标志是 Bluetooth SIG 的注册商标。

文档中提到的所有商标名称、商标和注册商标均属其各自所有者的财产，特此声明。