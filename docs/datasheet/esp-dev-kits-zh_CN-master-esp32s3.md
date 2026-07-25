ESP32-S3 

esp-dev-kits 文档

## Table of contents

Table of contents
i
1 ESP32-S3-DevKitC-1
3
1.1 ESP32-S3-DevKitC-1 v1.1
3
1.1.1 入门指南
3
1.1.2 硬件参考
5
1.1.3 硬件版本
8
1.1.4 相关文档
8
2 ESP32-S3-USB-OTG
15
2.1 ESP32-S3-USB-OTG
15
2.1.1 快速入门
15
2.1.2 硬件参考
20
2.1.3 相关文档
27
3 ESP32-S3-LCD-EV-Board
29
3.1 ESP32-S3-LCD-EV-Board v1.5
29
3.1.1 开发板概述
29
3.1.2 应用程序开发
35
3.1.3 硬件参考
39
3.1.4 硬件版本
44
3.1.5 样品获取
44
3.1.6 相关文档
44
4 ESP-VoCat
61
4.1 ESP-VoCat v1.2
61
4.1.1 入门指南
63
4.1.2 硬件参考
68
4.1.3 硬件版本
73
4.1.4 相关文档
73
5 ESP-DualKey
87
5.1 ESP-DualKey
87
5.1.1 入门指南
88
5.1.2 硬件参考
89
5.1.3 硬件版本
91
5.1.4 相关文档
91
6 寿命终止开发板
93
6.1 ESP32-S3-DevKitM-1
93
6.1.1 ESP32-S3-DevKitM-1
93
6.2 ESP32-S3-USB-Bridge
99
6.2.1 ESP32-S3-USB-Bridge
100
7 相关文档和资源
109
7.1 相关文档
109
7.2 开发者社区

7.3 产品 109  
7.4 联系我们 110  

8 免责声明和版权公告 111

该文档详细介绍了 ESP32-S3系列开发板的用户指南和示例。

备注: 如需获取乐鑫全部系列开发板的有关信息，请访问 乐鑫开发板概览。

# ESP32-S3-DevKitC-1

ESP32-S3-DevKitC-1 是一款入门级开发板，搭载 Wi-Fi + Bluetooth® LE 模组 ESP32-S3-WROOM-1、ESP32-S3-WROOM-1U 或 ESP32-S3-WROOM-2。

板上模组的大部分管脚均已引出至开发板两侧排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备，也可将开发板插在面包板上使用。

## 1.1 ESP32-S3-DevKitC-1 v1.1

更早版本：ESP32-S3-DevKitC-1 v1.0

本指南将帮助你快速上手 ESP32-S3-DevKitC-1，并提供该款开发板的详细信息。

ESP32-S3-DevKitC-1 是一款入门级开发板，搭载 Wi-Fi + Bluetooth® LE 模组 ESP32-S3-WROOM-1、ESP32-S3-WROOM-1U 或 ESP32-S3-WROOM-2。

板上模组的大部分管脚均已引出至开发板两侧排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备，也可将开发板插在面包板上使用。

本指南包括如下内容：

• 入门指南：简要介绍了开发板和硬件、软件设置指南。

• 硬件参考：详细介绍了开发板的硬件。

• 硬件版本：介绍硬件历史版本和已知问题，并提供链接至历史版本开发板的入门指南（如有）。

• 相关文档：列出了相关文档的链接。

## 1.1.1 入门指南

本小节将简要介绍 ESP32-S3-DevKitC-1，说明如何在 ESP32-S3-DevKitC-1 上烧录固件及相关准备工作。

## 组件介绍

以下按照逆时针的顺序依次介绍开发板上的主要组件。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/0ca5a99cbab3cd083c607fc33d2610018b28dcabd0389f73a8db66288784e104.jpg)



图 2: ESP32-S3-DevKitC-1 - 正面


<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>ESP32-S3-WROOM-1/1U/2</td><td>ESP32-S3-WROOM-1、ESP32-S3-WROOM-1U和ESP32-S3-WROOM-2是通用型Wi-Fi+低功耗蓝牙MCU模组,具有丰富的外设接口、强大的神经网络运算能力和信号处理能力,专为人工智能和AIoT市场打造。ESP32-S3-WROOM-1和ESP32-S3-WROOM-2采用PCB板载天线,ESP32-S3-WROOM-1U采用连接器连接外部天线。</td></tr><tr><td>5 V to 3.3 V LDO(5 V转3.3 V LDO)</td><td>电源转换器,输入5V,输出3.3V。</td></tr><tr><td>Pin Headers(排针)</td><td>所有可用GPIO管脚(除flash的SPI总线)均已引出至开发板的排针。请查看排针获取更多信息。</td></tr><tr><td>USB-to-UART Port(USB转UART接口)</td><td>Micro-USB接口,可用作开发板的供电接口,可烧录固件至芯片,也可作为通信接口,通过板载USB转UART桥接器与芯片通信。</td></tr><tr><td>Boot Button(Boot键)</td><td>下载按键。按住Boot键的同时按一下Reset键进入“固件下载”模式,通过串口下载固件。</td></tr><tr><td>Reset Button(Reset键)</td><td>复位按键。</td></tr><tr><td>USB Port(USB接口)</td><td>ESP32-S3 USB OTG接口,支持全速USB1.1标准。ESP32-S3 USB接口可用作开发板的供电接口,可烧录固件至芯片,可通过USB协议与芯片通信,也可用于JTAG调试。</td></tr><tr><td>USB-to-UART Bridge(USB转UART桥接器)</td><td>单芯片USB至UART桥接器,可提供高达3Mbps的传输速率。</td></tr><tr><td>RGB LED</td><td>可寻址RGB发光二极管,由GPIO38驱动。</td></tr><tr><td>3.3 V Power On LED(3.3 V电源指示灯)</td><td>开发板连接USB电源后,该指示灯亮起。</td></tr></table>

备注: 在板载 ESP32-S3-WROOM-1/1U 模组系列（使用 8 线 SPI flash/PSRAM）的开发板和板载 ESP32-S3-WROOM-2 模组系列的开发板中，管脚 GPIO35、GPIO36 和 GPIO37 已用于内部 ESP32-S3 芯片与 SPIflash/PSRAM之间的通信，外部不可使用。

## 开始开发应用

通电前，请确保开发板完好无损。

## 必备硬件

• ESP32-S3-DevKitC-1 

• USB 2.0 数据线（标准 A 型转 Micro-B 型）

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

硬件设置 通过USB转UART接口或ESP32-S3 USB接口连接开发板与电脑。在后续步骤中，默认使用USB 转 UART 接口。

软件设置 请前往 快速入门，在 详细安装步骤 小节查看如何快速设置开发环境，将应用程序烧录至你的开发板。

## 内含组件和包装

订购信息 该开发板有多种型号可供选择，详见下表。

<table><tr><td>订购代码</td><td>搭载模组</td><td>Flash</td><td>PSRAM</td><td>SPI电压</td></tr><tr><td>ESP32-S3-DevKitC-1-N8R8</td><td>ESP32-S3-WROOM-1-N8R8</td><td>8 MB QD</td><td>8 MB OT</td><td>3.3 V</td></tr><tr><td>ESP32-S3-DevKitC-1-N32R16V</td><td>ESP32-S3-WROOM-2-N32R16V</td><td>32 MB OT</td><td>16 MB OT</td><td>1.8 V</td></tr><tr><td>ESP32-S3-DevKitC-1U-N8R8</td><td>ESP32-S3-WROOM-1U-N8R8</td><td>8 MB QD</td><td>8 MB OT</td><td>3.3 V</td></tr></table>

备注: 上表中，QD 指代 Quad SPI，OT 指代 Octal SPI。

零售订单 如购买样品，每个开发板将以防静电袋或零售商选择的其他方式包装。

零售订单请前往 https://www.espressif.com/zh-hans/company/contact/buy-a-sample。

批量订单 如批量购买，开发板将以大纸板箱包装。

批量订单请前往 https://www.espressif.com/zh-hans/contact-us/sales-questions。

## 1.1.2 硬件参考

## 功能框图

ESP32-S3-DevKitC-1 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/a6bc8aa9708a0b4ee70d6560afe70ad99dbced098d842b520d982ad4c65931dc.jpg)



图 3: ESP32-S3-DevKitC-1（点击放大）


电源选项 以下任一供电方式均可给开发板供电：

• USB 转 UART 接口供电或 ESP32-S3 USB 接口供电（选择其一或同时供电），默认供电方式（推荐）

• 5V 和 G (GND) 排针供电

• 3V3 和 G (GND) 排针供电

## 排针

下表列出了开发板两侧排针（J1和J3）的名称和功能，排针的名称如图ESP32-S3-DevKitC-1 -正面所示，排针的序号与 开发板原理图(PDF)一致。


J1


<table><tr><td>序号</td><td>名称</td><td>类型</td><td>功能</td></tr><tr><td>1</td><td>3V3</td><td>P</td><td>3.3 V电源</td></tr><tr><td>2</td><td>3V3</td><td>P</td><td>3.3 V电源</td></tr><tr><td>3</td><td>RST</td><td>I</td><td>EN</td></tr><tr><td>4</td><td>4</td><td>I/O/T</td><td>RTC_GPIO4, GPIO4, TOUCH4, ADC1_CH3</td></tr><tr><td>5</td><td>5</td><td>I/O/T</td><td>RTC_GPIO5, GPIO5, TOUCH5, ADC1_CH4</td></tr><tr><td>6</td><td>6</td><td>I/O/T</td><td>RTC_GPIO6, GPIO6, TOUCH6, ADC1_CH5</td></tr><tr><td>7</td><td>7</td><td>I/O/T</td><td>RTC_GPIO7, GPIO7, TOUCH7, ADC1_CH6</td></tr><tr><td>8</td><td>15</td><td>I/O/T</td><td>RTC_GPIO15, GPIO15, U0RTS, ADC2_CH4, XTAL_32K_P</td></tr><tr><td>9</td><td>16</td><td>I/O/T</td><td>RTC_GPIO16, GPIO16, U0CTS, ADC2_CH5, XTAL_32K_N</td></tr><tr><td>10</td><td>17</td><td>I/O/T</td><td>RTC_GPIO17, GPIO17, U1TXD, ADC2_CH6</td></tr><tr><td>11</td><td>18</td><td>I/O/T</td><td>RTC_GPIO18, GPIO18, U1RXD, ADC2_CH7, CLK_OUT3</td></tr><tr><td>12</td><td>8</td><td>I/O/T</td><td>RTC_GPIO8, GPIO8, TOUCH8, ADC1_CH7, SUBSPICS1</td></tr><tr><td>13</td><td>3</td><td>I/O/T</td><td>RTC_GPIO3, GPIO3, TOUCH3, ADC1_CH2</td></tr><tr><td>14</td><td>46</td><td>I/O/T</td><td>GPIO46</td></tr><tr><td>15</td><td>9</td><td>I/O/T</td><td>RTC_GPIO9, GPIO9, TOUCH9, ADC1_CH8, FSPIHD, SUBSPIHD</td></tr><tr><td>16</td><td>10</td><td>I/O/T</td><td>RTC_GPIO10, GPIO10, TOUCH10, ADC1_CH9, FSPICS0, FSPIIO4, SUB-SPICS0</td></tr><tr><td>17</td><td>11</td><td>I/O/T</td><td>RTC_GPIO11, GPIO11, TOUCH11, ADC2_CH0, FSPID, FSPIIO5, SUBSPID</td></tr><tr><td>18</td><td>12</td><td>I/O/T</td><td>RTC_GPIO12, GPIO12, TOUCH12, ADC2_CH1, FSPICLK, FSPIIO6, SUBSPI-CLK</td></tr><tr><td>19</td><td>13</td><td>I/O/T</td><td>RTC_GPIO13, GPIO13, TOUCH13, ADC2_CH2, FSPIQ, FSPIIO7, SUBSPIQ</td></tr><tr><td>20</td><td>14</td><td>I/O/T</td><td>RTC_GPIO14, GPIO14, TOUCH14, ADC2_CH3, FSPIWP, FSPIDQS, SUB-SPIWP</td></tr><tr><td>21</td><td>5V</td><td>P</td><td>5 V电源</td></tr><tr><td>22</td><td>G</td><td>G</td><td>接地</td></tr></table>


J3


<table><tr><td>序号</td><td>名称</td><td>类型</td><td>功能</td></tr><tr><td>1</td><td>G</td><td>G</td><td>接地</td></tr><tr><td>2</td><td>TX</td><td>I/O/T</td><td>U0TXD, GPIO43, CLK_OUT1</td></tr><tr><td>3</td><td>RX</td><td>I/O/T</td><td>U0RXD, GPIO44, CLK_OUT2</td></tr><tr><td>4</td><td>1</td><td>I/O/T</td><td>RTC_GPIO1, GPIO1, TOUCH1, ADC1_CH0</td></tr><tr><td>5</td><td>2</td><td>I/O/T</td><td>RTC_GPIO2, GPIO2, TOUCH2, ADC1_CH1</td></tr><tr><td>6</td><td>42</td><td>I/O/T</td><td>MTMS, GPIO42</td></tr><tr><td>7</td><td>41</td><td>I/O/T</td><td>MTDI, GPIO41, CLK_OUT1</td></tr><tr><td>8</td><td>40</td><td>I/O/T</td><td>MTDO, GPIO40, CLK_OUT2</td></tr><tr><td>9</td><td>39</td><td>I/O/T</td><td>MTCK, GPIO39, CLK_OUT3, SUBSPICS1</td></tr><tr><td>10</td><td>38</td><td>I/O/T</td><td>GPIO38, FSPIWP, SUBSPIWP, RGB LED</td></tr><tr><td>11</td><td>37</td><td>I/O/T</td><td>SPIDQS, GPIO37, FSPIQ, SUBSPIQ</td></tr><tr><td>12</td><td>36</td><td>I/O/T</td><td>SPIIO7, GPIO36, FSPICLK, SUBSPICLK</td></tr><tr><td>13</td><td>35</td><td>I/O/T</td><td>SPIIO6, GPIO35, FSPID, SUBSPID</td></tr><tr><td>14</td><td>0</td><td>I/O/T</td><td>RTC_GPIO0, GPIO0</td></tr><tr><td>15</td><td>45</td><td>I/O/T</td><td>GPIO45</td></tr><tr><td>16</td><td>48</td><td>I/O/T</td><td>GPIO48, SPICLK_N, SUBSPICLK_N_DIFF</td></tr><tr><td>17</td><td>47</td><td>I/O/T</td><td>GPIO47, SPICLK_P, SUBSPICLK_P_DIFF</td></tr><tr><td>18</td><td>21</td><td>I/O/T</td><td>RTC_GPIO21, GPIO21</td></tr><tr><td>19</td><td>20</td><td>I/O/T</td><td>RTC_GPIO20, GPIO20, U1CTS, ADC2_CH9, CLK_OUT1, USB_D+</td></tr><tr><td>20</td><td>19</td><td>I/O/T</td><td>RTC_GPIO19, GPIO19, U1RTS, ADC2_CH8, CLK_OUT2, USB_D-</td></tr><tr><td>21</td><td>G</td><td>G</td><td>接地</td></tr><tr><td>22</td><td>G</td><td>G</td><td>接地</td></tr></table>


<sup>1</sup> P：电源；I：输入；O：输出；T：可设置为高阻。


有关管脚功能名称的解释，请参考 ESP32-S3 技术规格书(PDF)。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/aac390ea7e9045a680f1a94ba76b5bf1685f7085ee7cafddfd2def049663042e.jpg)



图 4: ESP32-S3-DevKitC-1 管脚布局（点击放大）


## 管脚布局

## 1.1.3 硬件版本

首次发布

备注: 目前首次发布和 v1.1 版本的开发板均可订购，两个版本的主要差异在于 RGB LED 所连接的管脚不同。首次发布版本的 RGB LED 连接到 GPIO48，而 v1.1 版本的 RGB LED 连接到 GPIO38。

## 1.1.4 相关文档

• ESP32-S3 技术规格书 (PDF)

• ESP32-S3-WROOM-1 & ESP32-S3-WROOM-1U 技术规格书 (PDF)

• ESP32-S3-WROOM-2 技术规格书 (PDF)

• ESP32-S3-DevKitC-1 原理图 (PDF)

• ESP32-S3-DevKitC-1 PCB 布局图 (PDF)

• ESP32-S3-DevKitC-1 尺寸图 (PDF)

• ESP32-S3-DevKitC-1 尺寸图源文件 (DXF) - 可使用 Autodesk Viewer 查看

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

ESP32-S3-DevKitC-1 v1.0 

最新版本：ESP32-S3-DevKitC-1 v1.1

本指南将帮助你快速上手 ESP32-S3-DevKitC-1，并提供该款开发板的详细信息。

ESP32-S3-DevKitC-1 是一款入门级开发板，搭载 Wi-Fi + Bluetooth® LE 模组 ESP32-S3-WROOM-1、ESP32-S3-WROOM-1U 或 ESP32-S3-WROOM-2。

板上模组的大部分管脚均已引出至开发板两侧排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备，也可将开发板插在面包板上使用。

## 图 5: ESP32-S3-DevKitC-1（板载 ESP32-S3-WROOM-1 模组）

本指南包括如下内容：

• 入门指南：简要介绍了开发板和硬件、软件设置指南。

• 硬件参考：详细介绍了开发板的硬件。

• 硬件版本：介绍硬件历史版本和已知问题，并提供链接至历史版本开发板的入门指南（如有）。

• 相关文档：列出了相关文档的链接。

入门指南 本小节将简要介绍 ESP32-S3-DevKitC-1，说明如何在 ESP32-S3-DevKitC-1 上烧录固件及相关准备工作。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/30263b214f2a4d6bd9c164adf09d75877acd018c5430bcb0e76293cabb4409b9.jpg)



图 6: ESP32-S3-DevKitC-1 - 正面


组件介绍 以下按照逆时针的顺序依次介绍开发板上的主要组件。

<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>ESP32-S3-WROOM-1/1U/2</td><td>ESP32-S3-WROOM-1、ESP32-S3-WROOM-1U和ESP32-S3-WROOM-2是通用型Wi-Fi+低功耗蓝牙MCU模组,具有丰富的外设接口、强大的神经网络运算能力和信号处理能力,专为人工智能和AIoT市场打造。ESP32-S3-WROOM-1和ESP32-S3-WROOM-2采用PCB板载天线,ESP32-S3-WROOM-1U采用连接器连接外部天线。</td></tr><tr><td>5 V to 3.3 V LDO (5 V转3.3 V LDO)</td><td>电源转换器,输入5V,输出3.3V。</td></tr><tr><td>Pin Headers(排针)</td><td>所有可用GPIO管脚(除flash的SPI总线)均已引出至开发板的排针。请查看排针获取更多信息。</td></tr><tr><td>USB-to-UART Port(USB转UART接口)</td><td>Micro-USB接口,可用作开发板的供电接口,可烧录固件至芯片,也可作为通信接口,通过板载USB转UART桥接器与芯片通信。</td></tr><tr><td>Boot Button(Boot键)</td><td>下载按键。按住Boot键的同时按一下Reset键进入“固件下载”模式,通过串口下载固件。</td></tr><tr><td>Reset Button(Reset键)</td><td>复位按键。</td></tr><tr><td>ESP32-S3 USB Port(ESP32-S3 USB接口)</td><td>ESP32-S3 USB OTG接口,支持全速USB1.1标准。ESP32-S3 USB接口可用作开发板的供电接口,可烧录固件至芯片,可通过USB协议与芯片通信,也可用于JTAG调试。</td></tr><tr><td>USB-to-UART Bridge(USB转UART桥接器)</td><td>单芯片USB至UART桥接器,可提供高达3Mbps的传输速率。</td></tr><tr><td>RGB LED</td><td>可寻址RGB发光二极管,由GPIO48驱动。</td></tr><tr><td>3.3 V Power On LED (3.3 V电源指示灯)</td><td>开发板连接USB电源后,该指示灯亮起。</td></tr></table>

备注: 在板载 ESP32-S3-WROOM-1/1U 模组系列（使用 8 线 SPI flash/PSRAM）的开发板和板载 ESP32-S3-WROOM-2 模组系列的开发板中，管脚 GPIO35、GPIO36 和 GPIO37 已用于内部 ESP32-S3 芯片与 SPIflash/PSRAM之间的通信，外部不可使用。

开始开发应用 通电前，请确保开发板完好无损。

## 必备硬件

• ESP32-S3-DevKitC-1 

• USB 2.0 数据线（标准 A 型转 Micro-B 型）

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

硬件设置 通过USB转UART接口连接开发板与电脑。软件暂不支持通过ESP32-S3 USB接口连接。在后续步骤中，默认使用 USB转UART接口。

软件设置 请前往 快速入门，在 详细安装步骤 小节查看如何快速设置开发环境，将应用程序烧录至你的开发板。

## 内含组件和包装

订购信息 该开发板有多种型号可供选择，详见下表。

<table><tr><td>订购代码</td><td>搭载模组</td><td>Flash</td><td>PSRAM</td><td>SPI电压</td></tr><tr><td>ESP32-S3-DevKitC-1-N8R8</td><td>ESP32-S3-WROOM-1-N8R8</td><td>8 MB QD</td><td>8 MB OT</td><td>3.3 V</td></tr><tr><td>ESP32-S3-DevKitC-1-N32R16V</td><td>ESP32-S3-WROOM-2-N32R16V</td><td>32 MB OT</td><td>16 MB OT</td><td>1.8 V</td></tr><tr><td>ESP32-S3-DevKitC-1U-N8R8</td><td>ESP32-S3-WROOM-1U-N8R8</td><td>8 MB QD</td><td>8 MB OT</td><td>3.3 V</td></tr></table>

备注: 上表中，QD 指代 Quad SPI，OT 指代 Octal SPI。

零售订单 如购买样品，每个开发板将以防静电袋或零售商选择的其他方式包装。

零售订单请前往 https://www.espressif.com/zh-hans/company/contact/buy-a-sample。

批量订单 如批量购买，开发板将以大纸板箱包装。

批量订单请前往 https://www.espressif.com/zh-hans/contact-us/sales-questions。

## 硬件参考

功能框图 ESP32-S3-DevKitC-1的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/a6799a43eca0d1bda5a67f4fed0125bf209e1c42974be7141435526cea3b38f3.jpg)



图 7: ESP32-S3-DevKitC-1（点击放大）



J1


电源选项 以下任一供电方式均可给开发板供电：

• USB转UART接口供电或ESP32-S3 USB接口供电（选择其一或同时供电），默认供电方式（推荐）

• 5V 和 G (GND) 排针供电

• 3V3 和 G (GND) 排针供电

排针 下表列出了开发板两侧排针（J1 和 J3）的 名称和 功能，排针的名称如图ESP32-S3-DevKitC-1 - 正面所示，排针的序号与 开发板原理图(PDF) 一致。

<table><tr><td>序号</td><td>名称</td><td>类型1</td><td>功能</td></tr><tr><td>1</td><td>3V3</td><td>P</td><td>3.3 V 电源</td></tr><tr><td>2</td><td>3V3</td><td>P</td><td>3.3 V 电源</td></tr><tr><td>3</td><td>RST</td><td>I</td><td>EN</td></tr><tr><td>4</td><td>4</td><td>I/O/T</td><td>RTC_GPIO4, GPIO4, TOUCH4, ADC1_CH3</td></tr><tr><td>5</td><td>5</td><td>I/O/T</td><td>RTC_GPIO5, GPIO5, TOUCH5, ADC1_CH4</td></tr><tr><td>6</td><td>6</td><td>I/O/T</td><td>RTC_GPIO6, GPIO6, TOUCH6, ADC1_CH5</td></tr><tr><td>7</td><td>7</td><td>I/O/T</td><td>RTC_GPIO7, GPIO7, TOUCH7, ADC1_CH6</td></tr><tr><td>8</td><td>15</td><td>I/O/T</td><td>RTC_GPIO15, GPIO15, U0RTS, ADC2_CH4, XTAL_32K_P</td></tr><tr><td>9</td><td>16</td><td>I/O/T</td><td>RTC_GPIO16, GPIO16, U0CTS, ADC2_CH5, XTAL_32K_N</td></tr><tr><td>10</td><td>17</td><td>I/O/T</td><td>RTC_GPIO17, GPIO17, U1TXD, ADC2_CH6</td></tr><tr><td>11</td><td>18</td><td>I/O/T</td><td>RTC_GPIO18, GPIO18, U1RXD, ADC2_CH7, CLK_OUT3</td></tr><tr><td>12</td><td>8</td><td>I/O/T</td><td>RTC_GPIO8, GPIO8, TOUCH8, ADC1_CH7, SUBSPICS1</td></tr><tr><td>13</td><td>3</td><td>I/O/T</td><td>RTC_GPIO3, GPIO3, TOUCH3, ADC1_CH2</td></tr><tr><td>14</td><td>46</td><td>I/O/T</td><td>GPIO46</td></tr><tr><td>15</td><td>9</td><td>I/O/T</td><td>RTC_GPIO9, GPIO9, TOUCH9, ADC1_CH8, FSPIHD, SUBSPIHD</td></tr><tr><td>16</td><td>10</td><td>I/O/T</td><td>RTC_GPIO10, GPIO10, TOUCH10, ADC1_CH9, FSPICS0, FSPIIO4, SUB-SPICS0</td></tr><tr><td>17</td><td>11</td><td>I/O/T</td><td>RTC_GPIO11, GPIO11, TOUCH11, ADC2_CH0, FSPID, FSPIIO5, SUBSPID</td></tr><tr><td>18</td><td>12</td><td>I/O/T</td><td>RTC_GPIO12, GPIO12, TOUCH12, ADC2_CH1, FSPICLK, FSPIIO6, SUB-SPICLK</td></tr><tr><td>19</td><td>13</td><td>I/O/T</td><td>RTC_GPIO13, GPIO13, TOUCH13, ADC2_CH2, FSPIQ, FSPIIO7, SUBSPIQ</td></tr><tr><td>20</td><td>14</td><td>I/O/T</td><td>RTC_GPIO14, GPIO14, TOUCH14, ADC2_CH3, FSPIWP, FSPIDQS, SUB-SPIWP</td></tr><tr><td>21</td><td>5V</td><td>P</td><td>5 V 电源</td></tr><tr><td>22</td><td>G</td><td>G</td><td>接地</td></tr></table>


<sup>1</sup> P：电源；I：输入；O：输出；T：可设置为高阻。


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/446d33d4c0e71352dce0c728d19a7e8772d6dfdce002acd32a7d035873727f7b.jpg)



J3


<table><tr><td>序号</td><td>名称</td><td>类型</td><td>功能</td></tr><tr><td>1</td><td>G</td><td>G</td><td>接地</td></tr><tr><td>2</td><td>TX</td><td>I/O/T</td><td>U0TXD, GPIO43, CLK_OUT1</td></tr><tr><td>3</td><td>RX</td><td>I/O/T</td><td>U0RXD, GPIO44, CLK_OUT2</td></tr><tr><td>4</td><td>1</td><td>I/O/T</td><td>RTC_GPIO1, GPIO1, TOUCH1, ADC1_CH0</td></tr><tr><td>5</td><td>2</td><td>I/O/T</td><td>RTC_GPIO2, GPIO2, TOUCH2, ADC1_CH1</td></tr><tr><td>6</td><td>42</td><td>I/O/T</td><td>MTMS, GPIO42</td></tr><tr><td>7</td><td>41</td><td>I/O/T</td><td>MTDI, GPIO41, CLK_OUT1</td></tr><tr><td>8</td><td>40</td><td>I/O/T</td><td>MTDO, GPIO40, CLK_OUT2</td></tr><tr><td>9</td><td>39</td><td>I/O/T</td><td>MTCK, GPIO39, CLK_OUT3, SUBSPICS1</td></tr><tr><td>10</td><td>38</td><td>I/O/T</td><td>GPIO38, FSPIWP, SUBSPIWP</td></tr><tr><td>11</td><td>37</td><td>I/O/T</td><td>SPIDQS, GPIO37, FSPIQ, SUBSPIQ</td></tr><tr><td>12</td><td>36</td><td>I/O/T</td><td>SPIIO7, GPIO36, FSPICLK, SUBSPICLK</td></tr><tr><td>13</td><td>35</td><td>I/O/T</td><td>SPIIO6, GPIO35, FSPID, SUBSPID</td></tr><tr><td>14</td><td>0</td><td>I/O/T</td><td>RTC_GPIO0, GPIO0</td></tr><tr><td>15</td><td>45</td><td>I/O/T</td><td>GPIO45</td></tr><tr><td>16</td><td>48</td><td>I/O/T</td><td>GPIO48, SPICLK_N, SUBSPICLK_N_DIFF, RGB LED</td></tr><tr><td>17</td><td>47</td><td>I/O/T</td><td>GPIO47, SPICLK_P, SUBSPICLK_P_DIFF</td></tr><tr><td>18</td><td>21</td><td>I/O/T</td><td>RTC_GPIO21, GPIO21</td></tr><tr><td>19</td><td>20</td><td>I/O/T</td><td>RTC_GPIO20, GPIO20, U1CTS, ADC2_CH9, CLK_OUT1, USB_D+</td></tr><tr><td>20</td><td>19</td><td>I/O/T</td><td>RTC_GPIO19, GPIO19, U1RTS, ADC2_CH8, CLK_OUT2, USB_D-</td></tr><tr><td>21</td><td>G</td><td>G</td><td>接地</td></tr><tr><td>22</td><td>G</td><td>G</td><td>接地</td></tr></table>


有关管脚功能名称的解释，请参考 芯片规格书 (PDF)。



ESP32-S3-DevKitC-1


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/364f2d0cfda71cb413edf68331a9f2116a5a3ad9cdc387c9335794f89dda1f5e.jpg)



图 8: ESP32-S3-DevKitC-1 管脚布局（点击放大）


## 管脚布局

## 硬件版本 无历史版本。

## 相关文档

• ESP32-S3 技术规格书 (PDF)

• ESP32-S3-WROOM-1 & ESP32-S3-WROOM-1U 技术规格书 (PDF)

• ESP32-S3-WROOM-2 技术规格书 (PDF)

• ESP32-S3-DevKitC-1 原理图 (PDF)

• ESP32-S3-DevKitC-1 PCB 布局图 (PDF)

• ESP32-S3-DevKitC-1 尺寸图 (PDF)

• ESP32-S3-DevKitC-1 尺寸图源文件 (DXF) - 可使用 Autodesk Viewer 查看

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

# Chapter 2

# ESP32-S3-USB-OTG

ESP32-S3-USB-OTG 是一款侧重于 USB-OTG 功能验证和应用开发的开发板。

开发板的应用示例存放在 Examples 文件夹中。

## 2.1 ESP32-S3-USB-OTG

ESP32-S3-USB-OTG 是一款侧重于 USB-OTG 功能验证和应用开发的开发板，基于 ESP32-S3 SoC，支持Wi-Fi 和 BLE 5.0 无线功能，支持 USB 主机和 USB 从机功能。可用于开发无线存储设备、Wi-Fi 网卡、LTE MiFi、多媒体设备、虚拟键鼠等应用。该开发板具有以下特性：

• 板载 ESP32-S3-MINI-1-N8 模组，内置 8 MB flash

• 板载 USB Type-A 主机和从机接口，内置接口切换电路

• 板载 USB 转串口调试芯片（micro USB 接口）

• 板载 1.3 英寸 LCD 彩屏，支持 GUI

• 板载 SD 卡接口，兼容SDIO 和SPI接口

• 板载充电IC，可外接锂电池

## 本指南包括：

• 快速入门：提供 ESP32-S3-USB-OTG的简要概述及必须了解的硬件和软件信息。

• 硬件参考：提供 ESP32-S3-USB-OTG 的详细硬件信息。

• 相关文档：提供相关文档的链接。

## 2.1.1 快速入门

本节介绍如何开始使用 ESP32-S3-USB-OTG。首先，介绍一些关于 ESP32-S3-USB-OTG 的基本信息，然后在应用程序开发章节介绍如何开始使用该开发板进行开发，最后介绍该开发板包装和零售信息。

## 组件介绍

ESP32-S3-USB-OTG 开发板包括以下两部分：

• 主板：ESP32-S3-USB-OTG 主板是整个套件的核心，该主板集成了 ESP32-S3-MINI-1 模组，并提供一个与1.3 英寸 LCD 屏连接的接口。

下表将从左边的 USB_HOST接口开始，以逆时针顺序介绍上图中的主要组件。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/6ccac7a302140d5558a1f0410cb2e8c2e5d6d24e076d188ed02595dec0c178c9.jpg)



图 1: ESP32-S3-USB-OTG（点击图片放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/3bf47dfca9646393259d145265e38ba8ed714e01966bb43d747abd517b7921a3.jpg)



图 2: ESP32-S3-USB-OTG 正面图（点击图片放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td>USB_HOST接口</td><td>USB Type-A 母口,用来连接其它 USB 设备。</td></tr><tr><td>ESP32-S3-MINI-1模组</td><td>ESP32-S3-MINI-1 是通用型 Wi-Fi + 低功耗蓝牙 MCU 模组,具有丰富的外设接口、强大的神经网络运算能力和信号处理能力,专为人工智能和 AIoT 市场打造。ESP32-S3-MINI-1 采用 PCB 板载天线,与 ESP32-S2-MINI-1 pin-to-pin 兼容。</td></tr><tr><td>MENU按键</td><td>菜单按键。</td></tr><tr><td>Micro SD卡槽</td><td>可插入 Micro SD 卡。支持 4-线 SDIO 和 SPI 模式。</td></tr><tr><td>USB Switch IC</td><td>通过设置 USB_SEL 的电平,可以切换 USB 外设连接到 USB_DEV 或 USB_HOST 接口,默认连接到 USB_DEV。</td></tr><tr><td>Reset按钮</td><td>用于重启系统。</td></tr><tr><td>USB_DEV接口</td><td>USB Type-A 公口,可连接其它 USB 主机,也作为锂电池充电。</td></tr><tr><td>电池供电开关</td><td>拨向 ON 按键一侧,使用电池供电;拨向 GND 按键一侧,通过其它方式供电。</td></tr><tr><td>Boot按键</td><td>按键 Boot 键并保持,同时按一下 Reset 键,进入“固件下载”模式,通过串口下载固件。正常使用中可以作为确认按钮。</td></tr><tr><td>DW-按键</td><td>向下按键。</td></tr><tr><td>屏幕排座</td><td>用于连接 1.3 英寸 LCD 屏。</td></tr><tr><td>UP+按键</td><td>向上按键。</td></tr><tr><td>USB转UART接口</td><td>Micro-USB 接口,可用作开发板的供电接口,可烧录固件至芯片,也可作为通信接口,通过板载 USB 转 UART 桥接器与芯片通信。</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/8eed0a70ccdafe27d3e014711ef9ca48f8f2bd356f0c60edbec1b865a76f4bfa.jpg)



图 3: ESP32-S3-USB-OTG 背面图（点击图片放大）



下表将从左边的 USB_HOST接口开始，以逆时针顺序介绍上图中的主要组件。


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td>黄色指示灯</td><td>设置 GPIO16 为高电平,指示灯亮。</td></tr><tr><td>绿色指示灯</td><td>设置 GPIO15 为高电平,指示灯亮。</td></tr><tr><td>充电指示灯</td><td>当为电池充电时,亮起红灯,充电完成红灯熄灭。</td></tr><tr><td>电池焊点</td><td>可焊接 3.6 V 锂电池,为主板供电。</td></tr><tr><td>充电电路</td><td>用于为锂电池充电。</td></tr><tr><td>空闲管脚</td><td>可自定义的空闲管脚。</td></tr><tr><td>USB 转 UART 桥接器</td><td>单芯片 USB 至 UART 桥接器,可提供高达 3 Mbps 的传输速率。</td></tr></table>

• 子板：ESP32-S3-USB-OTG-SUB - 贴装 1.3 英寸 LCD 屏

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/d67d00b371170d69497cc791e50f8a4f2837cf617ab07eb7cf3a9f56e3f4a15a.jpg)



图 4: ESP32-S3-USB-OTG 子板（点击图片放大）


## 应用示例

以下为开发板的应用示例：

• factory - 演示了 ESP32-S3-USB-OTG 开发板的工厂演示，为使用 ESP-IDF 和 ESP Launchpad 构建、烧录和监控项目提供了参考。

更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照应用程序开发小节中的步骤进行操作。

## 应用程序开发

ESP32-S3-USB-OTG上电前，请首先确认开发板完好无损。

## 硬件准备

• ESP32-S3-USB-OTG 

• 一根 USB 2.0 数据线（标准 A 转 Micro-B）

• 电脑（Windows、Linux 或 macOS）

软件设置 请前往 快速入门中详细安装步骤 一节查看如何快速设置开发环境。

## 内容和包装

零售订单 每一个零售 ESP32-S3-USB-OTG开发套件均有独立包装。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/8f77d67f29a706ac23beddaefaa444ea2c7f810cc0a328cf2e647a5e50d5f568.jpg)



图 5: ESP32-S3-USB-OTG 包装 (click to enlarge)


包含以下部分：

• 主板：

– ESP32-S3-USB-OTG 

• 子板：

– ESP32-S3-USB-OTG_SUB 

• 紧固件

– 安装螺栓（x4）

– 螺丝（x4）

– 螺母（x4）

零售订单请前往 https://www.espressif.com/zh-hans/company/contact/buy-a-sample。

批量订单 如批量购买，开发板将以大纸板箱包装。

批量订单请前往 https://www.espressif.com/zh-hans/contact-us/sales-questions。

## 2.1.2 硬件参考

功能框图

ESP32-S3-USB-OTG 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/a50dd3c965e0c323dff97b278d022225bd4a842bfa828373f4b56ea8f40ef5d4.jpg)



图 6: ESP32-S3-USB-OTG 功能框图 (click to enlarge)


请注意，功能框图中的 USB_HOST D+ D- 信号对应的外部接口是 USB DEV，是指 ESP32-S3 作为设备接收其它 USB 主机的信号。USB_DEV D+ D- 信号对应的外部接口是 USB HOST，是指 ESP32-S3 作为主机控制其它设备。

## 开发板供电选择

开发板有三种供电方式：

1. 通过 Micro_USB 接口供电

• 使用方法1供电时，应使用一根USB电缆（标准A转Micro-B）将主控板连接至供电设备，将电源开关置于 OFF。请注意，该供电模式仅有主板和显示屏被供电。

2. 通过 USB_DEV 接口供电

• 使用方法 2 供电时，应将 DEV_VBUS_EN 设置为高电平，并将电源开关设置为 OFF。该供电模式可同时向 USB HOST 接口供电，如已安装锂电池，会同时对锂电池进行充电。

3. 通过电池接口，使用外部锂电池供电

• 使用方法 3 供电时，应将 BOOST_EN 设置为高电平，将电源开关设置为 ON，并将 1S 锂电池(3.7 V ~ 4.2 V) 焊接于主控板背面预留的电源焊点。该供电模式可同时向 USB HOST 接口供电。电池接口说明如下图：

## USB HOST 接口供电选择

USB HOST接口（Type-A 母口）可向已连接的USB设备供电，供电电压为 5 V，最大电流为 500 mA。

• 供电电源有以下两个：

1. 通过 USB_DEV 接口供电，5 V 电源直接来自该接口连接的电源

2. 通过锂电池接口供电，锂电池 3.6 V ~ 4.2 V 电压通过 Boost 电路升压到 5 V。Boost IC 的工作状态可通过 BOOST_EN/GPIO13 控制，GPIO13 为高电平是使能 Boost。

• 供电电源选择：

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/42d5a0feb15253ab3a207ff8fd6aec28b8482ca2264e47c4d8516d56766cccb8.jpg)



图 7: 电池连接图 (click to enlarge)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b74e746a430275aee9e6faec3906f85cbddaf67b8af0b84c22931552321e626e.jpg)



图 8: Boost 电路图 (click to enlarge)


<table><tr><td>BOOST_EN</td><td>DEV_VBUS_EN</td><td>Power Source</td></tr><tr><td>0</td><td>1</td><td>USB_DEV</td></tr><tr><td>1</td><td>0</td><td>Battery</td></tr><tr><td>0</td><td>0</td><td>No output</td></tr><tr><td>1</td><td>1</td><td>Undefined</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/bdbce4859ff4627cd84d51d0f45771e824d742e80cb4fae2ad390a3a6ae37cde.jpg)



图 9: 供电切换电路图


## • 500 mA 限流电路

1. 限 流 IC MIC2005A 可 将 USB HOST 接 口 最 大 输 出 电 流 限 制 为 500 mA。 必 须 设 置IDEV_LIMIT_EN (GPIO17) 为高电平，使能限流 IC，USB HOST 接口才有电压输出。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/cdc717ce8eaf48de1ac4b96795bc4e062a49b1b41e5de10331c94b63013dfab5.jpg)



图 10: 500 mA 限流电路图


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/cfc7f094960058a19cf0e07e45b24e9ab3172a9e8ba3aa4c2522fa337f36f9ee.jpg)



图 11: USB接口切换电路图


## USB 接口选择电路

• 当 USB_SEL (GPIO18) 引脚为高电平时，USB D+/D- (GPIO19, 20) 信号将连通到 USB_DEV D+ D-，这时可通过USB HOST 接口（Type-A 母口）连接其它 USB设备；

• 当 USB_SEL (GPIO18) 引脚为低电平时，USB D+/D- (GPIO19, 20) 信号将连通到 USB_HOST D+D-，这时可通过USB DEV 接口（Type-A 公口）连接到其它 USB主机；

• 默认 USB_SEL 为低电平。

## LCD 接口

请注意，该接口支持连接 SPI 接口屏幕，该开发板使用的屏幕型号为 ST7789，LCD_BL (GPIO9) 可用于控制屏幕背光。

## SD 卡接口

请注意，SD卡接口同时兼容1-线，4-线SDIO模式和SPI模式。上电后，卡会处于3.3 V signaling模式下。发送第一个 CMD0命令选择bus模式：SD 模式或者SPI模式。

## 充电电路

请注意，可将 Type-A 公口接入输出为 5 V 的电源适配器，为电池充电时，充电电路上的红色指示灯亮，电池充电完成，红色指示灯熄灭。在使用充电电路时，请将电源开关置于 OFF。充电电流为212.7 mA。

## GPIO 分配

## 功能引脚：

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/ac39d4e10269d8b3c8cc3908203071d4babed8a189107d654d0fcb2cfa201c31.jpg)



图 12: LCD 接口电路图


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/8832d1318743cb194838bef0e6db9340c4a6d0a2f7b92a612471ab703c8e884c.jpg)



图13: SD 卡接口电路图


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/f713fa7387fda93078d53f919bf0062e492f0793198eb537609152733ef6fae3.jpg)



图 14: 充电电路图


<table><tr><td>No.</td><td>ESP32-S3-MINI-1 管脚</td><td>说明</td></tr><tr><td>1</td><td>GPIO18</td><td>USB_SEL:用于切换 USB 接口,高电平时,USB_HOST 接口使能。低电平时(默认),USB_DEV 接口使能。</td></tr><tr><td>2</td><td>GPIO19</td><td>与 USB_D- 接口相连。</td></tr><tr><td>3</td><td>GPIO20</td><td>与 USB_D+ 接口相连。</td></tr><tr><td>4</td><td>GPIO15</td><td>LED_GREEN:用于控制绿色 LED 灯,高电平时,灯被点亮。</td></tr><tr><td>5</td><td>GPIO16</td><td>LED_YELLOW:用于控制黄色 LED 灯,高电平时,灯被点亮。</td></tr><tr><td>6</td><td>GPIO0</td><td>BUTTON_OK:OK 按键,按下为低电平。</td></tr><tr><td>7</td><td>GPIO11</td><td>BUTTON_DW:Down 按键,按下为低电平。</td></tr><tr><td>8</td><td>GPIO10</td><td>BUTTON_UP:UP 按键,按下为低电平。</td></tr><tr><td>9</td><td>GPIO14</td><td>BUTTON_MENU:MENU 按键,按下为低电平。</td></tr><tr><td>10</td><td>GPIO8</td><td>LCD_RET:用于复位 LCD,低电平时复位。</td></tr><tr><td>11</td><td>GPIO5</td><td>LCD_EN:用于使能 LCD,低电平时使能。</td></tr><tr><td>12</td><td>GPIO4</td><td>LCD_DC:用于切换数据和命令状态。</td></tr><tr><td>13</td><td>GPIO6</td><td>LCD_SCLK:LCD SPI 时钟信号。</td></tr><tr><td>14</td><td>GPIO7</td><td>LCD_SDA:LCD SPI MOSI 信号。</td></tr><tr><td>15</td><td>GPIO9</td><td>LCD_BL:LCD 背光控制信号。</td></tr><tr><td>16</td><td>GPIO36</td><td>SD_SCK:SD SPI CLK / SDIO CLK。</td></tr><tr><td>17</td><td>GPIO37</td><td>SD_DO:SD SPI MISO / SDIO Data0。</td></tr><tr><td>18</td><td>GPIO38</td><td>SD_D1:SDIO Data1。</td></tr><tr><td>19</td><td>GPIO33</td><td>SD_D2:SDIO Data2。</td></tr><tr><td>20</td><td>GPIO34</td><td>SD_D3:SD SPI CS / SDIO Data3。</td></tr><tr><td>21</td><td>GPIO1</td><td>HOST_VOL:USB_DEV 电压监测,ADC1 通道 0。</td></tr><tr><td>22</td><td>GPIO2</td><td>BAT_VOL:电池电压监测,ADC1 通道 1。</td></tr><tr><td>23</td><td>GPIO17</td><td>LIMIT_EN:使能限流芯片,高电平使能。</td></tr><tr><td>24</td><td>GPIO21</td><td>0VER_CURRENT:电流超限信号,高电平代表超限。</td></tr><tr><td>25</td><td>GPIO12</td><td>DEV_VBUS_EN:高电平选择 DEV_VBUS 电源。</td></tr><tr><td>26</td><td>GPIO13</td><td>BOOST_EN:高电平使能 Boost 升压电路。</td></tr></table>


扩展功能引脚：


<table><tr><td>No.</td><td>ESP32-S3-MINI-1 管脚</td><td>说明</td></tr><tr><td>1</td><td>GPIO45</td><td>FREE_1:空闲,可自定义。</td></tr><tr><td>2</td><td>GPIO46</td><td>FREE_2:空闲,可自定义。</td></tr><tr><td>3</td><td>GPIO48</td><td>FREE_3:空闲,可自定义。</td></tr><tr><td>4</td><td>GPIO26</td><td>FREE_4:空闲,可自定义。</td></tr><tr><td>5</td><td>GPIO47</td><td>FREE_5:空闲,可自定义。</td></tr><tr><td>6</td><td>GPIO3</td><td>FREE_6:空闲,可自定义。</td></tr></table>

## 2.1.3 相关文档

请前往 esp-dev-kits 文档 HTML 网页版本 下载以下文档。

• ESP32-S3 技术规格书 (PDF)

• ESP32-S3-MINI-1/1U 技术规格书 (PDF)

• 乐鑫产品选型工具

• ESP32-S3-USB-OTG 原理图 (PDF)

• ESP32-S3-USB-OTG PCB 布局图 (PDF)

• ST7789VW 规格书 (PDF)

# ESP32-S3-LCD-EV-Board

ESP32-S3-LCD-EV-Board是用于评估和验证ESP32-S3屏幕应用的开发板，其由主板和子板构成，通过更换子板可方便接入不同的屏幕。

备注: 请查看主板 ESP32-S3-LCD-EV-Board-MB 背面的丝印版本号，以确认您的开发板版本。对于 v1.5版本的开发板，请参考ESP32-S3-LCD-EV-Board v1.5；对于 v1.4 及以下版本的开发板，请参考ESP32-S3-LCD-EV-Board v1.4。

除非另有说明，本文中的 ESP32-S3-LCD-EV-Board 同时指 ESP32-S3-LCD-EV-Board 和 ESP32-S3-LCD-EV-Board-2 两款开发板。

## 3.1 ESP32-S3-LCD-EV-Board v1.5

备注: 请查看主板 ESP32-S3-LCD-EV-Board-MB 背面的丝印版本号，以确认您的开发板版本。对于 v1.5版本的开发板，请参考当前用户指南；对于 v1.4 及以下版本的开发板，请参考ESP32-S3-LCD-EV-Boardv1.4。

除非另有说明，本文中的 ESP32-S3-LCD-EV-Board 同时指 ESP32-S3-LCD-EV-Board 和 ESP32-S3-LCD-EV-Board-2 两款开发板。

本指南将帮助您快速上手 ESP32-S3-LCD-EV-Board，并提供该款开发板的详细信息。

本指南包括如下内容：

• 开发板概述：简要介绍了开发板的软件和硬件。

• 应用程序开发：介绍了应用程序开发过程中的软硬件设置。

• 硬件参考：详细介绍了开发板的硬件。

• 硬件版本：暂无历史版本。

• 样品获取：如何获取样品。

• 相关文档：列出了相关文档的链接。

## 3.1.1 开发板概述

ESP32-S3-LCD-EV-Board 是一款基于 ESP32-S3 芯片的屏幕交互开发板，通过搭配不同类型的 LCD 子板，可以驱动 IIC、SPI、8080 以及 RGB 接口的 LCD 显示屏。同时它还搭载双麦克风阵列，支持语音识别和近/远场语音唤醒，具有触摸屏交互和语音交互功能，满足用户对多种不同分辨率以及接口的触摸屏应用产品的开发需求。

目前支持两款开发板：

• 搭配 480x480 LCD 的 ESP32-S3-LCD-EV-Board

• 搭配 800x480 LCD 的 ESP32-S3-LCD-EV-Board-2

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/0ae81b7cb62296d93601abe752bfe9cb4e811937d4b1b9dcecf036c7ee40d29c.jpg)



图 1: 搭配 480x480 LCD 的 ESP32-S3-LCD-EV-Board


## 特性列表

该开发板具有以下特性：

• 嵌入式模组：板载 ESP32-S3-WROOM-1 模组，内置 16 MB flash 以及 16 MB PSRAM

• 屏幕：可搭配不同屏幕子板使用，支持RGB、8080、SPI以及I2C接口屏幕，请查看LCD子板了解更多信息

• 音频：板载音频Codec + ADC 功放，支持双麦克风拾音

• USB：板载 USB转串口芯片，并且支持 USB Type-C 接口下载调试

## 功能框图

ESP32-S3-LCD-EV-Board 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/47082680a56b52971830dfd6d986953ab831f1f1db8bb3c00fc8e251dfe4dced.jpg)



图 2: 搭配 800x480 LCD 的 ESP32-S3-LCD-EV-Board-2


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/60062ab3db52468159f056627c8869d3e261f4c9a6a4caec5e8165092b820e5d.jpg)



图 3: ESP32-S3-LCD-EV-Board 功能框图（点击放大）


## 组件介绍

ESP32-S3-LCD-EV-Board 开发板由主板和子板（子板类型请查看LCD 子板）组成，此外还可以选配一块USB Type-A 转接板。

主板 ESP32-S3-LCD-EV-Board-MB 主板是整个套件的核心，该主板集成了 ESP32-S3-WROOM-1 模组，并提供与LCD 子板连接的端口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/c1606442df88e1c55accc601a1723e38dbe08dc2307a61348652cbffdde11bea.jpg)



图 4: ESP32-S3-LCD-EV-Board-MB - 正面（点击放大）


以下按照逆时针顺序依次介绍开发板上的主要组件。

<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>ESP32-S3-WROOM-1-N16R16V 模组</td><td>ESP32-S3-WROOM-1-N16R16V 模组是一款通用型 Wi-Fi + 低功耗蓝牙 MCU 模组,搭载 ESP32-S3 系列芯片,内置 16 MB flash 以及 16 MB PSRAM。除具有丰富的外设接口外,模组还拥有强大的神经网络运算能力和信号处理能力,适用于 AIoT 领域的多种应用场景。</td></tr><tr><td>Reset 按键</td><td>单独按下此按键会重置系统。</td></tr><tr><td>Boot 按键</td><td>长按 Boot 键时,再按 Reset 键可启动固件上传模式,然后便可通过串口或 USB 上传固件。</td></tr><tr><td>扩展连接器</td><td>可供连接所有的 IO 扩展芯片管脚、系统电源管脚以及部分模组管脚。</td></tr><tr><td>I/O 扩展芯片</td><td>TCA9554 是一款 8 位通用并行输入和输出 I/O 扩展芯片,它通过两线 I2C 通信控制 IO 口的模式以及输出电平,丰富了系统的 IO 应用场景。</td></tr><tr><td>LCD 子板连接器</td><td>通过 2.54 mm 间距的连接器可以连接三种不同类型的 LCD 子板。</td></tr><tr><td>LED</td><td>具有 RGB 三色显示功能,可供用户配置用来做状态行为指示。</td></tr><tr><td>USB-to-USB 端口</td><td>为整个系统提供电源(USB-to-USB 端口和 USB-to-UART 端口两者选一)。建议使用至少 5V/2A 电源适配器供电,保证供电稳定。该端口用于 PC 端与 ESP32-S3-WROOM-1 模组的 USB 通信。</td></tr><tr><td>USB-to-UART 端口</td><td>为整个系统提供电源(USB-to-USB 端口和 USB-to-UART 端口两者选一)。建议使用至少 5V/2A 电源适配器供电,保证供电稳定。该端口用于 PC 端与 ESP32-S3-WROOM-1 模组的串口通信。</td></tr><tr><td>左侧麦克风</td><td>板载麦克风,连接至音频模数转换器。</td></tr><tr><td>右侧麦克风</td><td>板载麦克风,连接至音频模数转换器。</td></tr><tr><td>音频模数转换器</td><td>ES7210 是一款用于麦克风阵列应用的高性能、低功耗 4 通道音频模数转换器,同时具备声学回声消除 (AEC) 功能,非常适合音乐和语音应用。</td></tr><tr><td>USB-to-UART 桥接器</td><td>单芯片 USB-UART 桥接器 CP2102N 为软件下载和调试提供高达 3 Mbps 的传输速率。</td></tr><tr><td>音频编解码芯片</td><td>ES8311 是一种低功耗单声道音频编解码器,包含单通道 ADC、单通道 DAC、低噪声前置放大器、耳机驱动器、数字音效、模拟混音和增益功能。它通过 I2S 和 I2C 总线与 ESP32-S3-WROOM-1 模组连接,以提供独立于音频应用程序的硬件音频处理。</td></tr><tr><td>音频功率放大器</td><td>NS4150 是一款低 EMI、3 W 单声道 D 类音频功率放大器,用于放大来自音频编解码芯片的音频信号,以驱动扬声器。</td></tr><tr><td>扬声器连接器</td><td>可通过音频功率放大器的支持,实现外部扬声器播放功能。</td></tr></table>


LCD 子板 主板可搭配以下三种不同类型的子板使用：


<table><tr><td>子板名称</td><td>屏幕(英寸)</td><td>分辨率(px)</td><td>LCD驱动芯片(接口)</td><td>触摸驱动芯片</td><td>在售开发板</td></tr><tr><td rowspan="2">ESP32-S3-LCD-EV-Board-SUB1 v1.0</td><td>0.96</td><td>128 x 64</td><td>SSD1315(I2C)</td><td>N/A</td><td>无</td></tr><tr><td>2.40</td><td>320 x 240</td><td>ST7789V(SPI)</td><td>XTP2046</td><td>无</td></tr><tr><td rowspan="2">ESP32-S3-LCD-EV-Board-SUB2 v1.5</td><td>3.50</td><td>480 x 320</td><td>ST7796S(8080)</td><td>GT911</td><td>无</td></tr><tr><td>3.95</td><td>480 x 480</td><td>GC9503CV(RGB)</td><td>FT5x06</td><td>ESP32-S3-LCD-EV-Board</td></tr><tr><td>ESP32-S3-LCD-EV-Board-SUB3 v1.3</td><td>4.30</td><td>800 x 480</td><td>ST7262E43(RGB)</td><td>GT1151</td><td>ESP32-S3-LCD-EV-Board-2</td></tr></table>

• ESP32-S3-LCD-EV-Board-SUB1 子板提供了两种屏幕接口，分别支持连接一块 2.4 英寸 SPI 接口屏或者一块0.96 英寸 I2C接口屏。该子板暂未做适配，此处不做进一步讲解。

• ESP32-S3-LCD-EV-Board-SUB2 子板提供了两种屏幕接口，分别支持连接一块 RGB 接口屏或者一块 8080 并口屏。当前子板贴装了一块 3.95 英寸、RGB565 接口、分辨率为 480x480 的触摸屏，该屏使用的LCD 驱动芯片型号为 GC9503CV，触摸驱动芯片型号为 FT5x06。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b51bdca3c59683d27be9dabd2d3392ee243384538d34f6df505d29a44c878cea.jpg)



图 5: ESP32-S3-LCD-EV-Board-SUB2 - 正面（点击放大）


• ESP32-S3-LCD-EV-Board-SUB3 子板仅支持 4.3 英寸、RGB565 接口、分辨率为 800x480 的触摸屏，该屏使用的LCD 驱动芯片型号为 ST7262E43，触摸驱动芯片型号为 GT1151。

USB Type-A 转接板 通过连接 USB Type-A 转接板，主板可作为 USB Host 连接 USB 设备。

应用示例

以下为开发板的应用示例：

• 86-box Demo Example - 演示了一个为控制面板 (480x480) 设计的 GUI 示例，适用于常见的墙装 86型底盒，提供了流畅的图形操作体验，包含天气信息、热水器、暖风机页面以及音频输出等功能。

• 86-box Smart Panel Example - 演示了一个用于智能控制面板的工厂示例，支持离线语音识别功能，并为烧录开发板及排查潜在问题提供参考。

• LVGL Demos Example - 演示如何在 ESP32-S3-LCD-EV-Board 上运行 LVGL 示例，展示了三种使用不同缓冲模式避免画面撕裂的方法，并提供了不同缓冲模式的性能测试结果。

• Smart Panel Example - 演示了一个用于智能控制面板的工厂示例，支持离线语音识别功能，提供了如何将示例烧录至 ESP32-S3-LCD-EV-Board 并配置其使用的指导。

• USB Camera LCD Example - 演示如何使用 LCD 显示屏显示从 USB 摄像头捕获的视频，支持将帧传输到 Wi-Fi 和记录内存信息，为基于 ESP32-S3-LCD-EV-Board 的应用开发提供基础。

• USB File System - 演示如何在 ESP32-S2/ESP32-S3 上使用 USB HOST 来读取和写入 USB 闪存驱动器上的文件，并在屏幕上显示其内容，支持预览各种文件格式。

• USB Keyboard Example - 演示如何在 ESP32-S3-LCD-EV-Board 上使用 LCD 和 LVGL 模拟 USB 键盘，提供一个可以像真实键盘一样与 PC交互的USB键盘的图形用户界面。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/728845e53c88499c3b84bed0cad9463930a835dff18c953b57fc73416fabf8f6.jpg)



图 6: ESP32-S3-LCD-EV-Board-SUB2 - 反面（点击放大）


更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照应用程序开发小节中的步骤进行操作。

## 3.1.2 应用程序开发

本节介绍硬件和软件的设置方法，以及烧录固件至开发板以开发应用程序的说明。

必备硬件

• 1 x ESP32-S3-LCD-EV-Board-MB 

• 1 x LCD 子板

• 1 x USB 2.0 数据线（标准 A 型转 Type-C 型）

• 1 x 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和程序烧录。

## 可选硬件

• 1 x 扬声器

## 硬件设置

准备开发板，加载第一个示例应用程序：

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/684656446d98031ab24831f4fb791346f064ac9426acaf32d7e7c0c01c4fdf37.jpg)



图 7: ESP32-S3-LCD-EV-Board-SUB3 - 正面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/e17473ba14ac59db1ead74002f6604b406ce5c0cddd31c0c23cbad6d6357c1ff.jpg)



图 8: ESP32-S3-LCD-EV-Board-SUB3 - 反面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/a54f337ee773ef455a398e48cf6fd275e3285a7c679cb7f1d05aee91a85d137a.jpg)



图 9: USB Type-A 转接板 v1.1 - 正面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/ea42c1df7034db0f4216bb71c858b6ad6b75286cfb8317a984e3a3afe2f294a2.jpg)



图 10: USB Type-A 转接板 v1.1 - 与主板连接（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/da1bf84e1b6f609e4053d12c3b1d109ab1f446fd36beefb19229a985dd6a8724.jpg)



图 11: USB Type-A 转接板 v1.1 - 连接 USB 设备（点击放大）


1. 连接 LCD 子板至 LCD 子板连接器端口。

2. 插入 USB数据线，分别连接PC 与开发板的两个 USB端口之一。

3. LCD 屏幕亮起，可以用手指与触摸屏进行交互。

硬件设置完成，接下来可以进行软件设置。

## 软件设置

ESP32-S3-LCD-EV-Board 的开发框架为 ESP-IDF。ESP-IDF 是基于 FreeRTOS 的乐鑫 SoC 开发框架，具有众多组件，包括 LCD、ADC、RMT、SPI 等。

了解如何快速设置开发环境，请前往 快速入门> 安装。

备注:

• ESP-IDF 的版本要求在 v5.0.1 及以上，推荐使用最新的 release/v5.1 分支开发。

• 关于如何开发LCD 应用的更多信息，请参考 ESP-IoT-Solution编程指南。

## 3.1.3 硬件参考

本节提供关于开发板硬件的更多信息。

## GPIO 分配列表

下表为 ESP32-S3-WROOM-1模组管脚的 GPIO 分配列表，用于控制开发板的特定组件或功能。


表 1: ESP32-S3-WROOM-1 GPIO 分配


<table><tr><td>管脚</td><td>管脚名称</td><td>功能</td></tr><tr><td>1</td><td>GND</td><td>接地</td></tr><tr><td>2</td><td>3V3</td><td>供电</td></tr><tr><td>3</td><td>EN</td><td>RESET</td></tr><tr><td>4</td><td>IO4</td><td>LED</td></tr><tr><td>5</td><td>IO5</td><td>I2S_MCLK</td></tr><tr><td>6</td><td>IO6</td><td>I2S_CODEC_DSDIN</td></tr><tr><td>7</td><td>IO7</td><td>I2S_LRCK</td></tr><tr><td>8</td><td>IO15</td><td>I2S_ADC_SDOUT</td></tr><tr><td>9</td><td>IO16</td><td>I2S_SCLK</td></tr><tr><td>10</td><td>IO17</td><td>LCD_DE</td></tr><tr><td>11</td><td>IO18</td><td>LCD_DATA7</td></tr><tr><td>12</td><td>IO8</td><td>LCD_DATA6</td></tr><tr><td>13</td><td>IO19</td><td>USB_D-</td></tr><tr><td>14</td><td>IO20</td><td>USB_D+</td></tr><tr><td>15</td><td>IO3</td><td>LCD_VSYNC</td></tr><tr><td>16</td><td>IO46</td><td>LCD_HSYNC</td></tr><tr><td>17</td><td>IO9</td><td>LCD_PCLK</td></tr><tr><td>18</td><td>IO10</td><td>LCD_DATA0</td></tr><tr><td>19</td><td>IO11</td><td>LCD_DATA1</td></tr><tr><td>20</td><td>IO12</td><td>LCD_DATA2</td></tr><tr><td>21</td><td>IO13</td><td>LCD_DATA3</td></tr><tr><td>22</td><td>IO14</td><td>LCD_DATA4</td></tr><tr><td>23</td><td>IO21</td><td>LCD_DATA5</td></tr><tr><td>24</td><td>IO47</td><td>I2C_SDA</td></tr><tr><td>25</td><td>IO48</td><td>I2C_SCL</td></tr><tr><td>26</td><td>IO45</td><td>LCD_DATA8</td></tr></table>


表 1 – 接上页


<table><tr><td>管脚</td><td>管脚名称</td><td>功能</td></tr><tr><td>27</td><td>IO0</td><td>BOOT</td></tr><tr><td>28</td><td>IO35</td><td>未连接</td></tr><tr><td>29</td><td>IO36</td><td>未连接</td></tr><tr><td>30</td><td>IO37</td><td>未连接</td></tr><tr><td>31</td><td>IO38</td><td>LCD_DATA9</td></tr><tr><td>32</td><td>IO39</td><td>LCD_DATA10</td></tr><tr><td>33</td><td>IO40</td><td>LCD_DATA11</td></tr><tr><td>34</td><td>IO41</td><td>LCD_DATA12</td></tr><tr><td>35</td><td>IO42</td><td>LCD_DATA13</td></tr><tr><td>36</td><td>RXD0</td><td>UART_RXD0</td></tr><tr><td>37</td><td>TXD0</td><td>UART_TXD0</td></tr><tr><td>38</td><td>IO2</td><td>LCD_DATA14</td></tr><tr><td>39</td><td>IO1</td><td>LCD_DATA15</td></tr><tr><td>40</td><td>GND</td><td>接地</td></tr><tr><td>41</td><td>EPAD</td><td>接地</td></tr></table>


分配给 IO扩展芯片的 GPIO 被进一步分配为多个GPIO。



表 2: IO 扩展芯片 GPIO 分配


<table><tr><td>IO扩展器管脚</td><td>管脚名称</td><td>功能</td></tr><tr><td>1</td><td>A0</td><td>接地</td></tr><tr><td>2</td><td>A1</td><td>接地</td></tr><tr><td>3</td><td>A2</td><td>接地</td></tr><tr><td>4</td><td>P0</td><td>PA_CTRL</td></tr><tr><td>5</td><td>P1</td><td>LCD_SPI_CS</td></tr><tr><td>6</td><td>P2</td><td>LCD_SPI_SCK</td></tr><tr><td>7</td><td>P3</td><td>LCD_SPI_MOSI</td></tr><tr><td>8</td><td>GND</td><td>接地</td></tr><tr><td>9</td><td>P4</td><td>可做任意用途</td></tr><tr><td>10</td><td>P5</td><td>可做任意用途</td></tr><tr><td>11</td><td>P6</td><td>可做任意用途</td></tr><tr><td>12</td><td>P7</td><td>可做任意用途</td></tr><tr><td>13</td><td>INT</td><td>未连接</td></tr><tr><td>14</td><td>SCL</td><td>I2C_SCL</td></tr><tr><td>15</td><td>SDA</td><td>I2C_SDA</td></tr><tr><td>16</td><td>VCC</td><td>供电电压</td></tr></table>

## 供电说明

USB 供电 开发板有两种 USB供电方式：

• 通过 USB-to-USB 端口供电

• 通过 USB-to-UART 端口供电

音频和数字独立供电 ESP32-S3-LCD-EV-Board 可为音频组件和 ESP 模组提供相互独立的电源，可降低数字组件给音频信号带来的噪声并提高组件的整体性能。

## AEC 电路

AEC 电路为AEC 算法提供参考信号。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/fff4b72d4efc5a7144f17817ca1bf9c985944d88b50855a33349386256273e10.jpg)



图 12: ESP32-S3-LCD-EV-Board - USB-to-USB 电源供电


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/74a2b4b17420a81c67074b902c6d3eb43fb0b7ae359b1e2bbc950a652e13be93.jpg)



图 13: ESP32-S3-LCD-EV-Board - USB-to-UART 电源供电


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/e975d04ee849a05dd558dce147996dc2f1dad1f2e0f85f9946921cb8480185b5.jpg)



图 14: ESP32-S3-LCD-EV-Board - 数字供电


Audio VDD 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/64d2d7375d9817bc578cc9efcad37179b2166b064f80987fc3db1dc99a164c68.jpg)



图 15: ESP32-S3-LCD-EV-Board - 音频供电


ESP32-S3-LCD-EV-Board 回 声 参 考 信 号 源 有 两 路 兼 容 设 计， 一 路 是 Codec (ES8311) DAC 输 出(DAC_AOUTLN/DAC_AOUTLP)，一路是 PA (NS4150) 输出 (PA_OUTL+/PA_OUTL-)。推荐将默认 Code(ES8311) DAC 输出 (DAC_AOUTLN/DAC_AOUTLP) 作为回声参考信号，下图中电阻 R54、R56 无需连接。

回声参考信号通过 ADC (ES7210) 的 ADC_MIC3P/ADC_MIC3N 采集后送回给 ESP32-S3 用于 AEC 算法。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/fa1a073537ad133e1404d728e76ab453d373fe5393b2150515ffc5d9105300b6.jpg)



图 16: ESP32-S3-LCD-EV-Board - AEC Codec DAC 输出（点击放大）


## 硬件设置选项

自动下载 可以通过两种方式使开发板进入下载模式：

• 按下 Boot 和 Reset 键，然后先松开 Reset 键，再松开 Boot 键。

• 由软件自动执行下载。软件利用串口的 DTR和 RTS信号来控制开发板 EN、IO0管脚的状态。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b2eea421b081818ffb7f6e706bbff3948d567ee72768a35aa77bac416b6ccec2.jpg)



图 17: ESP32-S3-LCD-EV-Board - AEC PA 输出（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/c489f6490b82e4b7cde665a6d35d1685c5dbc3ca769c413c6fcb355d3353368c.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/311dadb7cf79f1d08f68276233ce99d6ae968497bcbc07c8a28c840b34ba7d98.jpg)



图 18: ESP32-S3-LCD-EV-Board - 参考信号采集（点击放大）


## 3.1.4 硬件版本

ESP32-S3-LCD-EV-Board v1.5 

• 以下管脚已重新分配，以适用于 ESP32-S3-WROOM-1-N16R16V 模组：

– I2C_SCL：由 IO18 改为 IO48

– I2C_SDA：由 IO8 改为 IO47

– LCD_DATA6：由 IO47 改为 IO8

– LCD_DATA7：由 IO48 改为 IO18

• IO47 和IO48 新增电平转换电路，用于将 1.8 V 电平转换为 3.3 V 电平。

ESP32-S3-LCD-EV-Board v1.4 

• 首次发布

## 3.1.5 样品获取

此开发板及转接板适用于评估高性能的 智能屏方案。如有需要，请前往乐鑫官方淘宝商城 进行采购。

## 3.1.6 相关文档

请前往 esp-dev-kits 文档 HTML 网页版本 下载以下文档。

• ESP32-S3 技术规格书

• ESP32-S3-WROOM-1 技术规格书

• 乐鑫产品选型工具

• ESP32-S3-LCD-EV-Board-MB 原理图

• ESP32-S3-LCD-EV-Board-MB PCB 布局图

• ESP32-S3-LCD-EV-Board-SUB1 原理图

• ESP32-S3-LCD-EV-Board-SUB1 PCB 布局图

• ESP32-S3-LCD-EV-Board-SUB2 原理图

• ESP32-S3-LCD-EV-Board-SUB2 PCB 布局图

• 3.95_480x480_RGB_Display 屏幕规格书

• ESP32-S3-LCD-EV-Board-SUB3 原理图

• ESP32-S3-LCD-EV-Board-SUB3 PCB 布局图

• ESP32-S3-LCD-EV-Board USB 转接板原理图

• ESP32-S3-LCD-EV-Board USB 转接板 PCB 布局图

• TCA9554 规格书

• 4.3_800x480_RGB_Display 屏幕规格书

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

ESP32-S3-LCD-EV-Board v1.4 

备注: 请查看主板 ESP32-S3-LCD-EV-Board-MB 背面的丝印版本号，以确认您的开发板版本。对于 v1.4及以下版本的开发板，请参考当前用户指南；对于 v1.5 版本的开发板，请参考ESP32-S3-LCD-EV-Boardv1.5。

除非另有说明，本文中的 ESP32-S3-LCD-EV-Board 同时指 ESP32-S3-LCD-EV-Board 和 ESP32-S3-LCD-EV-Board-2 两款开发板。

本指南将帮助您快速上手 ESP32-S3-LCD-EV-Board，并提供该款开发板的详细信息。

本指南包括如下内容：

• 开发板概述：简要介绍了开发板的软件和硬件。

• 应用程序开发：介绍了应用程序开发过程中的软硬件设置。

• 硬件参考：详细介绍了开发板的硬件。

• 硬件版本：暂无历史版本。

• 样品获取：如何获取样品。

• 相关文档：列出了相关文档的链接。

开发板概述 ESP32-S3-LCD-EV-Board 是一款基于 ESP32-S3 芯片的屏幕交互开发板，通过搭配不同类型的 LCD 子板，可以驱动 IIC、SPI、8080 以及 RGB 接口的 LCD 显示屏。同时它还搭载双麦克风阵列，支持语音识别和近/远场语音唤醒，具有触摸屏交互和语音交互功能，满足用户对多种不同分辨率以及接口的触摸屏应用产品的开发需求。

## 目前支持两款开发板：

• 搭配 480x480 LCD 的 ESP32-S3-LCD-EV-Board

• 搭配 800x480 LCD 的 ESP32-S3-LCD-EV-Board-2

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/85402999cc150a1ddd8cc837d4f6e0fe45e7eb4be09097d386bc4f5c8e6a700c.jpg)



图 19: 搭配 480x480 LCD 的 ESP32-S3-LCD-EV-Board


特性列表 该开发板具有以下特性：

• 嵌入式模组：板载 ESP32-S3-WROOM-1 模组，内置 16 MB flash 以及 8 MB PSRAM

• 屏幕：可搭配不同屏幕子板使用，支持RGB、8080、SPI以及I2C接口屏幕，请查看LCD子板了解更多信息

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/9b6cfa1c714e734f8a8ae8dbe75a28edbd334f20273ffcb03a1528e1cdb3cd61.jpg)



图 20: 搭配 800x480 LCD 的 ESP32-S3-LCD-EV-Board-2


• 音频：板载音频 Codec + ADC 功放，支持双麦克风拾音

• USB：板载 USB转串口芯片，并且支持 USB Type-C 接口下载调试

功能框图 ESP32-S3-LCD-EV-Board 的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/0c0a1643e5dbf1074f92fa1e06e5a8bb99714fc55971d9160e15b3c92a7077f2.jpg)



图 21: ESP32-S3-LCD-EV-Board 功能框图（点击放大）


组件介绍 ESP32-S3-LCD-EV-Board 开发板由主板和子板（子板类型请查看LCD 子板）组成，此外还可以选配一块 USB Type-A 转接板。

主板 ESP32-S3-LCD-EV-Board-MB 主板是整个套件的核心，该主板集成了 ESP32-S3-WROOM-1 模组，并提供与LCD 子板连接的端口。

以下按照逆时针顺序依次介绍开发板上的主要组件。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/065590f8899a9696b50b6604915ba679bb54fc2178dfdcee528538d2639fbea3.jpg)



图 22: ESP32-S3-LCD-EV-Board-MB - 正面（点击放大）


<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>ESP32-S3-WROOM-1-N16R8 模组</td><td>ESP32-S3-WROOM-1-N16R8 模组是一款通用型 Wi-Fi + 低功耗蓝牙 MCU 模组,搭载 ESP32-S3 系列芯片,内置 16 MB flash 以及 8 MB PSRAM。除具有丰富的外设接口外,模组还拥有强大的神经网络运算能力和信号处理能力,适用于 AIoT 领域的多种应用场景。</td></tr><tr><td>Reset 按键</td><td>单独按下此按键会重置系统。</td></tr><tr><td>Boot 按键</td><td>长按 Boot 键时,再按 Reset 键可启动固件上传模式,然后便可通过串口或 USB 上传固件。</td></tr><tr><td>扩展连接器</td><td>可供连接所有的 IO 扩展芯片管脚、系统电源管脚以及部分模组管脚。</td></tr><tr><td>I/O 扩展芯片</td><td>TCA9554 是一款 8 位通用并行输入和输出 I/O 扩展芯片,它通过两线 I2C 通信控制 IO 口的模式以及输出电平,丰富了系统的 IO 应用场景。</td></tr><tr><td>LCD 子板连接器</td><td>通过 2.54 mm 间距的连接器可以连接三种不同类型的 LCD 子板。</td></tr><tr><td>LED</td><td>具有 RGB 三色显示功能,可供用户配置用来做状态行为指示。</td></tr><tr><td>USB-to-USB 端口</td><td>为整个系统提供电源(USB-to-USB 端口和 USB-to-UART 端口两者选一)。建议使用至少 5V/2A 电源适配器供电,保证供电稳定。该端口用于 PC 端与 ESP32-S3-WROOM-1 模组的 USB 通信。</td></tr><tr><td>USB-to-UART 端口</td><td>为整个系统提供电源(USB-to-USB 端口和 USB-to-UART 端口两者选一)。建议使用至少 5V/2A 电源适配器供电,保证供电稳定。该端口用于 PC 端与 ESP32-S3-WROOM-1 模组的串口通信。</td></tr><tr><td>左侧麦克风</td><td>板载麦克风,连接至音频模数转换器。</td></tr><tr><td>右侧麦克风</td><td>板载麦克风,连接至音频模数转换器。</td></tr><tr><td>音频模数转换器</td><td>ES7210 是一款用于麦克风阵列应用的高性能、低功耗 4 通道音频模数转换器,同时具备声学回声消除 (AEC) 功能,非常适合音乐和语音应用。</td></tr><tr><td>USB-to-UART 桥接器</td><td>单芯片 USB-UART 桥接器 CP2102N 为软件下载和调试提供高达 3 Mbps 的传输速率。</td></tr><tr><td>音频编解码芯片</td><td>ES8311 是一种低功耗单声道音频编解码器,包含单通道 ADC、单通道 DAC、低噪声前置放大器、耳机驱动器、数字音效、模拟混音和增益功能。它通过 I2S 和 I2C 总线与 ESP32-S3-WROOM-1 模组连接,以提供独立于音频应用程序的硬件音频处理。</td></tr><tr><td>音频功率放大器</td><td>NS4150 是一款低 EMI、3 W 单声道 D 类音频功率放大器,用于放大来自音频编解码芯片的音频信号,以驱动扬声器。</td></tr><tr><td>扬声器连接器</td><td>可通过音频功率放大器的支持,实现外部扬声器播放功能。</td></tr></table>


LCD 子板 主板可搭配以下三种不同类型的子板使用：


<table><tr><td>子板名称</td><td>屏幕(英寸)</td><td>分辨率(px)</td><td>LCD驱动芯片(接口)</td><td>触摸驱动芯片</td><td>在售开发板</td></tr><tr><td rowspan="2">ESP32-S3-LCD-EV-Board-SUB1 v1.0</td><td>0.96</td><td>128 x 64</td><td>SSD1315(I2C)</td><td>无</td><td>无</td></tr><tr><td>2.40</td><td>320 x 240</td><td>ST7789V(SPI)</td><td>XTP2046</td><td>无</td></tr><tr><td rowspan="2">ESP32-S3-LCD-EV-Board-SUB2 v1.4</td><td>3.50</td><td>480 x 320</td><td>ST7796S(8080)</td><td>GT911</td><td>无</td></tr><tr><td>3.95</td><td>480 x 480</td><td>GC9503CV(RGB)</td><td>FT5x06</td><td>ESP32-S3-LCD-EV-Board</td></tr><tr><td>ESP32-S3-LCD-EV-Board-SUB3 v1.3</td><td>4.30</td><td>800 x 480</td><td>ST7262E43(RGB)</td><td>GT1151</td><td>ESP32-S3-LCD-EV-Board-2</td></tr></table>

• ESP32-S3-LCD-EV-Board-SUB1 子板提供了两种屏幕接口，分别支持连接一块 2.4 英寸 SPI 接口屏或者一块0.96 英寸 I2C接口屏。该子板暂未做适配，此处不做进一步讲解。

• ESP32-S3-LCD-EV-Board-SUB2 子板提供了两种屏幕接口，分别支持连接一块 RGB 接口屏或者一块 8080 并口屏。当前子板贴装了一块 3.95 英寸、RGB565 接口、分辨率为 480x480 的触摸屏，该屏使用的LCD 驱动芯片型号为 GC9503CV，触摸驱动芯片型号为 FT5x06。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/56c62b99bb6b649888a88b0b097302724b92f9599bcf159a1bd7f17661cf1c7c.jpg)



图 23: ESP32-S3-LCD-EV-Board-SUB2 - 正面（点击放大）


• ESP32-S3-LCD-EV-Board-SUB3 子板仅支持 4.3 英寸、RGB565 接口、分辨率为 800x480 的触摸屏，该屏使用的LCD 驱动芯片型号为 ST7262E43，触摸驱动芯片型号为 GT1151。

USB Type-A 转接板 通过连接 USB Type-A 转接板，主板可作为 USB Host 连接 USB 设备。

## 应用示例 以下为开发板的应用示例：

• 86-box Demo Example - 演示了一个为控制面板 (480x480) 设计的 GUI 示例，适用于常见的墙装 86型底盒，提供了流畅的图形操作体验，包含天气信息、热水器、暖风机页面以及音频输出等功能。

• 86-box Smart Panel Example - 演示了一个用于智能控制面板的工厂示例，支持离线语音识别功能，并为烧录开发板及排查潜在问题提供参考。

• LVGL Demos Example - 演示如何在 ESP32-S3-LCD-EV-Board 上运行 LVGL 示例，展示了三种使用不同缓冲模式避免画面撕裂的方法，并提供了不同缓冲模式的性能测试结果。

• Smart Panel Example - 演示了一个用于智能控制面板的工厂示例，支持离线语音识别功能，提供了如何将示例烧录至 ESP32-S3-LCD-EV-Board 并配置其使用的指导。

• USB Camera LCD Example - 演示如何使用 LCD 显示屏显示从 USB 摄像头捕获的视频，支持将帧传输到 Wi-Fi 和记录内存信息，为基于 ESP32-S3-LCD-EV-Board 的应用开发提供基础。

• USB File System - 演示如何在 ESP32-S2/ESP32-S3 上使用 USB HOST 来读取和写入 USB 闪存驱动器上的文件，并在屏幕上显示其内容，支持预览各种文件格式。

• USB Keyboard Example - 演示如何在 ESP32-S3-LCD-EV-Board 上使用 LCD 和 LVGL 模拟 USB 键盘，提供一个可以像真实键盘一样与 PC交互的USB键盘的图形用户界面。

更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照应用程序开发小节中的步骤进行操作。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/87c27494ffcd97898145db9eaba82f695f2af3c570faaf063c8c8417674335b5.jpg)



图 24: ESP32-S3-LCD-EV-Board-SUB2 - 反面（点击放大）


应用程序开发 本节介绍硬件和软件的设置方法，以及烧录固件至开发板以开发应用程序的说明。

## 必备硬件

• 1 x ESP32-S3-LCD-EV-Board-MB 

• 1 x LCD 子板

• 1 x USB 2.0 数据线（标准 A 型转 Type-C 型）

• 1 x 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和程序烧录。

## 可选硬件

• 1 x 扬声器

硬件设置 准备开发板，加载第一个示例应用程序：

1. 连接 LCD子板至 LCD 子板连接器端口。

2. 插入 USB数据线，分别连接PC 与开发板的两个 USB端口之一。

3. LCD 屏幕亮起，可以用手指与触摸屏进行交互。

硬件设置完成，接下来可以进行软件设置。

软件设置 ESP32-S3-LCD-EV-Board 的开发框架为 ESP-IDF。ESP-IDF 是基于 FreeRTOS 的乐鑫 SoC 开发框架，具有众多组件，包括 LCD、ADC、RMT、SPI等。

了解如何快速设置开发环境，请前往 快速入门> 安装。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b336a13d544c28648ce57c5afa9afa12d20c8fd052a209f1de7a2f737273e9b3.jpg)



图 25: ESP32-S3-LCD-EV-Board-SUB3 - 正面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/cea6f5a40afde221091e0fedc0dd2caa6d30d8eef10b4b9acec41e3b6ce9b366.jpg)



图 26: ESP32-S3-LCD-EV-Board-SUB3 - 反面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/c3e8e79475b7266b18320e0078f0a0f73c4d2fc5933533580ee3d05313310c88.jpg)



图 27: USB Type-A 转接板 v1.1 - 正面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b4c39cd1d3b5cb015fb42694692eb5ea375e5697aaa00fb4b3a4bc1369b107e1.jpg)



图 28: USB Type-A 转接板 v1.1 - 与主板连接（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/8b6b96d6381e5f1ee6c0b022fede42f2716b83dec72588e0b4689e626522dc31.jpg)



图 29: USB Type-A 转接板 v1.1 - 连接 USB 设备（点击放大）


备注:

• ESP-IDF 的版本要求在 v5.0.1 及以上，推荐使用最新的 release/v5.1 分支开发。

• 关于如何开发LCD 应用的更多信息，请参考 ESP-IoT-Solution编程指南。

硬件参考 本节提供关于开发板硬件的更多信息。

GPIO分配列表 下表为ESP32-S3-WROOM-1模组管脚的GPIO分配列表，用于控制开发板的特定组件或功能。


表 3: ESP32-S3-WROOM-1 GPIO 分配


<table><tr><td>管脚</td><td>管脚名称</td><td>功能</td></tr><tr><td>1</td><td>GND</td><td>接地</td></tr><tr><td>2</td><td>3V3</td><td>供电</td></tr><tr><td>3</td><td>EN</td><td>RESET</td></tr><tr><td>4</td><td>IO4</td><td>LED</td></tr><tr><td>5</td><td>IO5</td><td>I2S_MCLK</td></tr><tr><td>6</td><td>IO6</td><td>I2S_CODEC_DSDIN</td></tr><tr><td>7</td><td>IO7</td><td>I2S_LRCK</td></tr><tr><td>8</td><td>IO15</td><td>I2S_ADC_SDOUT</td></tr><tr><td>9</td><td>IO16</td><td>I2S_SCLK</td></tr><tr><td>10</td><td>IO17</td><td>LCD_DE</td></tr><tr><td>11</td><td>IO18</td><td>I2C_SCL</td></tr><tr><td>12</td><td>IO8</td><td>I2C_SDA</td></tr><tr><td>13</td><td>IO19</td><td>USB_D-</td></tr><tr><td>14</td><td>IO20</td><td>USB_D+</td></tr><tr><td>15</td><td>IO3</td><td>LCD_VSYNC</td></tr><tr><td>16</td><td>IO46</td><td>LCD_HSYNC</td></tr><tr><td>17</td><td>IO9</td><td>LCD_PCLK</td></tr><tr><td>18</td><td>IO10</td><td>LCD_DATA0</td></tr><tr><td>19</td><td>IO11</td><td>LCD_DATA1</td></tr><tr><td>20</td><td>IO12</td><td>LCD_DATA2</td></tr><tr><td>21</td><td>IO13</td><td>LCD_DATA3</td></tr><tr><td>22</td><td>IO14</td><td>LCD_DATA4</td></tr><tr><td>23</td><td>IO21</td><td>LCD_DATA5</td></tr><tr><td>24</td><td>IO47</td><td>LCD_DATA6</td></tr><tr><td>25</td><td>IO48</td><td>LCD_DATA7</td></tr><tr><td>26</td><td>IO45</td><td>LCD_DATA8</td></tr><tr><td>27</td><td>IO0</td><td>BOOT</td></tr><tr><td>28</td><td>IO35</td><td>未连接</td></tr><tr><td>29</td><td>IO36</td><td>未连接</td></tr><tr><td>30</td><td>IO37</td><td>未连接</td></tr><tr><td>31</td><td>IO38</td><td>LCD_DATA9</td></tr><tr><td>32</td><td>IO39</td><td>LCD_DATA10</td></tr><tr><td>33</td><td>IO40</td><td>LCD_DATA11</td></tr><tr><td>34</td><td>IO41</td><td>LCD_DATA12</td></tr><tr><td>35</td><td>IO42</td><td>LCD_DATA13</td></tr><tr><td>36</td><td>RXD0</td><td>UART_RXD0</td></tr><tr><td>37</td><td>TXD0</td><td>UART_TXD0</td></tr><tr><td>38</td><td>IO2</td><td>LCD_DATA14</td></tr><tr><td>39</td><td>IO1</td><td>LCD_DATA15</td></tr><tr><td>40</td><td>GND</td><td>接地</td></tr><tr><td>41</td><td>EPAD</td><td>接地</td></tr></table>

分配给 IO扩展芯片的 GPIO 被进一步分配为多个GPIO。


表 4: IO 扩展芯片 GPIO 分配


<table><tr><td>IO扩展器管脚</td><td>管脚名称</td><td>功能</td></tr><tr><td>1</td><td>A0</td><td>接地</td></tr><tr><td>2</td><td>A1</td><td>接地</td></tr><tr><td>3</td><td>A2</td><td>接地</td></tr><tr><td>4</td><td>P0</td><td>PA_CTRL</td></tr><tr><td>5</td><td>P1</td><td>LCD_SPI_CS</td></tr><tr><td>6</td><td>P2</td><td>LCD_SPI_SCK</td></tr><tr><td>7</td><td>P3</td><td>LCD_SPI_MOSI</td></tr><tr><td>8</td><td>GND</td><td>接地</td></tr><tr><td>9</td><td>P4</td><td>可做任意用途</td></tr><tr><td>10</td><td>P5</td><td>可做任意用途</td></tr><tr><td>11</td><td>P6</td><td>可做任意用途</td></tr><tr><td>12</td><td>P7</td><td>可做任意用途</td></tr><tr><td>13</td><td>INT</td><td>未连接</td></tr><tr><td>14</td><td>SCL</td><td>I2C_SCL</td></tr><tr><td>15</td><td>SDA</td><td>I2C_SDA</td></tr><tr><td>16</td><td>VCC</td><td>供电电压</td></tr></table>

## 供电说明

USB 供电 开发板有两种 USB供电方式：

• 通过 USB-to-USB 端口供电

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/5eca2d46bf619354983643f6d3f4286313d8a4a9bf9b234bc17aaec1bffbf3ce.jpg)



图 30: ESP32-S3-LCD-EV-Board - USB-to-USB 电源供电



• 通过 USB-to-UART 端口供电


音频和数字独立供电 ESP32-S3-LCD-EV-Board 可为音频组件和 ESP 模组提供相互独立的电源，可降低数字组件给音频信号带来的噪声并提高组件的整体性能。

AEC电路 AEC 电路为 AEC算法提供参考信号。

ESP32-S3-LCD-EV-Board 回 声 参 考 信 号 源 有 两 路 兼 容 设 计， 一 路 是 Codec (ES8311) DAC 输 出(DAC_AOUTLN/DAC_AOUTLP)，一路是 PA (NS4150) 输出 (PA_OUTL+/PA_OUTL-)。推荐将默认 Codec(ES8311) DAC 输出 (DAC_AOUTLN/DAC_AOUTLP) 作为回声参考信号，下图中电阻 R54、R56 无需连接。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/31a304b3dc518416f6b3fe1b7ddd7816a1b74a9693ba78ac9fb16673fb14d331.jpg)



图 31: ESP32-S3-LCD-EV-Board - USB-to-UART 电源供电



SYS VDD


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b96568cc86f0596c09210de820b4c85069bff0dcbfda5f3a6bda0ae99a2c3a89.jpg)



图 32: ESP32-S3-LCD-EV-Board - 数字供电



Audio VDD


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/fc8887b0cb1557efd2a6e3c13714dcbb68a315cc369158d9a4d485920377d4ac.jpg)



图 33: ESP32-S3-LCD-EV-Board - 音频供电


回声参考信号通过 ADC (ES7210) 的 ADC_MIC3P/ADC_MIC3N 采集后送回给 ESP32-S3 用于 AEC 算法。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/2faf7c47d32f40e94b7d07a02542d87f259525092b6dc4e8dcfd246af30fefd0.jpg)



图 34: ESP32-S3-LCD-EV-Board - AEC Codec DAC 输出（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/13d3c2bef76e25c81d5585d587a3a407c7fbe9afa38906727e8e07c6c86df2d6.jpg)



图 35: ESP32-S3-LCD-EV-Board - AEC PA 输出（点击放大）


## 硬件设置选项

自动下载 可以通过两种方式使开发板进入下载模式：

• 按下 Boot 和 Reset 键，然后先松开 Reset 键，再松开 Boot 键。

• 由软件自动执行下载。软件利用串口的 DTR和 RTS信号来控制开发板 EN、IO0管脚的状态。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/bb58185bdc5fff8c7a1ce9de43e5bc714f1c3dfe81ab2ae8519f00437ba64dac.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/ca4555536f7b5e98024d5271523607afa360a42a4fc4a8230cd435c77292691f.jpg)



图 36: ESP32-S3-LCD-EV-Board - 参考信号采集（点击放大）



硬件版本 无历史版本。


样品获取 此开发板及转接板适用于评估高性能的 智能屏方案。如有需要，请前往 乐鑫官方淘宝商城进行采购。

相关文档 请前往 esp-dev-kits文档 HTML 网页版本 下载以下文档。

• ESP32-S3 技术规格书

• ESP32-S3-WROOM-1 技术规格书

• 乐鑫产品选型工具

• ESP32-S3-LCD-EV-Board-MB 原理图

• ESP32-S3-LCD-EV-Board-MB PCB 布局图

• ESP32-S3-LCD-EV-Board-SUB1 原理图

• ESP32-S3-LCD-EV-Board-SUB1 PCB 布局图

• ESP32-S3-LCD-EV-Board-SUB2 原理图

• ESP32-S3-LCD-EV-Board-SUB2 PCB 布局图

• ESP32-S3-LCD-EV-Board-SUB3 原理图

• ESP32-S3-LCD-EV-Board-SUB3 PCB 布局图

• ESP32-S3-LCD-EV-Board USB 转接板原理图

• ESP32-S3-LCD-EV-Board USB 转接板 PCB 布局图

• TCA9554 规格书

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

# Chapter 4

## ESP-VoCat

ESP-VoCat 喵伴是乐鑫携手火山引擎扣子大模型团队打造的智能 AI 开发套件，适用于玩具、智能音箱、智能中控等需要大模型赋能的语音交互类产品。该设备搭载 ESP32-S3 模组，1.85 寸 QSPI 圆形触摸屏，双麦阵列，支持离线语音唤醒与声源定位算法。结合火山引擎提供的大模型能力，喵伴可实现全双工语音交互、多模态识别与智能体控制，为开发者打造完整的端侧 AI应用体验提供坚实基础。

开发板的应用示例存放在 esp-brookesia 工程中。

备注: 请查看主板上的丝印版本号，以确认您的开发板版本。对于v1.0版本的开发板，请参考ESP-VoCav1.0；对于 v1.2 版本的开发板，请参考ESP-VoCat v1.2。

## 4.1 ESP-VoCat v1.2

备注: 请查看主板上的丝印版本号，以确认您的开发板版本。对于v1.0版本的开发板，请参考ESP-VoCatv1.0；对于 v1.2版本的开发板，请参考当前用户指南。

本指南将帮助您快速上手 ESP-VoCat，并提供该款开发板的详细信息。

ESP-VoCat是一款智能AI开发套件，适用于需要大模型能力的语音交互类产品，例如玩具、智能音箱和智能中控系统。设备搭载ESP32-S3-WROOM-1模组、1.85英寸QSPI圆形触控屏、双麦克风阵列，并支持离线语音唤醒与声源定位算法。结合火山引擎扣子、Amazon Nova、OpenAI、小智AI、Gemini等提供的大模型能力，ESP-VoCat 可实现全双工语音交互、多模态识别以及智能体控制，为开发者打造完整的端侧 AI应用体验提供坚实基础。

ESP-VoCat 主控采用乐鑫 ESP32-S3-WROOM-1-N16R16VA 模组，支持 2.4 GHz Wi-Fi 和 Bluetooth 5 (LE)无线连接。存储方面，整机具备16 MB PSRAM、16 MB flash的存储空间，同时还配备了一个可支持高达32GB 的 microSD 卡插槽，满足语音交互和多媒体处理需求。配备 1.85 英寸圆形触摸屏（360 × 360 分辨率）与 ESP32-S3原生触摸传感器，提供直观丰富的交互体验。

音频方面，ESP-VoCat内置3W扬声器和双麦克风阵列，支持本地语音唤醒和声源定位。电源系统兼容5V DC和3.7 V锂电池供电。此外，还集成一个USB-C接口支持供电与编程下载，同时预留Pogopin接口方便功能扩展。

本指南包括如下内容：

• 入门指南：简要介绍了开发板和硬件、软件设置指南。

• 硬件参考：详细介绍了开发板的硬件。

• 硬件版本：介绍硬件历史版本和已知问题（如有）。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/d0cd7b796bd8800047144cef056c46f495364c6c20c2b1227d53c009b31ce05c.jpg)



图 1: ESP-VoCat 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/25df5c60c3416af9fab8456e063c4c21bb68b44b7fbccf9cec15b294f382d030.jpg)



图 2: ESP-VoCat 背面图（点击放大）


• 相关文档：列出了相关文档的链接。

## 4.1.1 入门指南

本小节将简要介绍 ESP-VoCat，说明如何在 ESP-VoCat 上烧录固件及相关准备工作。

组件介绍

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/637407b2e8e4ed15d2d3e1d6930385e49b081df539609a480832985981cc1e59.jpg)



图 3: ESP-VoCat CoreBoard PCB 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/ead6cfea51606f9f1744211f4c360c90eace5f794d0401bb248a43e8f9ff85a4.jpg)



图 4: ESP-VoCat MicBoard PCB 正面图（点击放大）


以下按照顺时针的顺序依次介绍正面PCB上的主要组件。为了方便用户使用，我们同时在ESP-VoCat的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/2ba98d8927706d8a5be8ad2bcee2853af9192012b97a953fbcb130f36b9a5bbe.jpg)



图 5: ESP-VoCat BaseBoard PCB 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/617694a0b9e6ca6df7fc3260fe48cd57016410a11dc96dc88a8dea48a8bf4459.jpg)



图 6: ESP-VoCat 正面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td colspan="2">CoreBoard(核心板)</td></tr><tr><td>ESP32-S3-WROOM-1-N16R16VA</td><td>主控芯片,集成16 MB Flash和16 MB PSRAM,支持2.4 GHz Wi-Fi和Bluetooth 5 (LE)无线连接。</td></tr><tr><td>Battery Connector(电池连接器)</td><td>电池连接器,用于连接3.7 V锂电池,上为正极,下为负极。</td></tr><tr><td>LCD FPC Connector(屏幕连接器)</td><td>用于连接1.85英寸圆形LCD屏幕,分辨率为360 x 360,详细参数请参考显示屏规格书。</td></tr><tr><td>MicBoard Connector(麦克风连接器)</td><td>MicBoard PCB板连接器,连接双麦克风阵列和状态指示LED灯。</td></tr><tr><td>Touch Connector(触摸连接器)</td><td>触摸连接器,用于连接触摸铜箔,实现触摸交互功能。</td></tr><tr><td>Speaker Connector(扬声器连接器)</td><td>2线扬声器连接器,用于连接内置3 W扬声器。</td></tr><tr><td colspan="2">MicBoard(麦克风板)</td></tr><tr><td>Green LED(绿色LED)</td><td>绿色LED指示灯。</td></tr><tr><td>MIC(麦克风阵列)</td><td>双LMA3729T381-OY3S麦克风阵列,支持本地语音唤醒和声源定位功能。</td></tr><tr><td colspan="2">BaseBoard(底板)</td></tr><tr><td>BQ27220(电池管理芯片)</td><td>电池管理芯片,用于电池电量检测、充电管理和电源状态监控。</td></tr><tr><td>TP4057(锂电池充电芯片)</td><td>锂电池充电芯片,用于为锂电池充电,充电电流为250 mA。</td></tr><tr><td>CoreBoard Connector(Core-Board 连接器)</td><td>CoreBoard PCB板连接器,连接核心板与底板。</td></tr><tr><td>TIV62569(DCDC芯片)</td><td>降压转换芯片,用于将5 V电源转换为3.3 V电源,为系统提供稳定供电。</td></tr><tr><td>SAM8108(开关机控制芯片)</td><td>开关机控制芯片,用于控制设备开关机,单击POWER按键即可切换开关机状态。</td></tr><tr><td>Type-C(USB-C接口)</td><td>USB-C接口,用于供电、编程下载和调试,支持对锂电池进行充电。</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/4d1d3ac0a3d63d167905bd6134a388b7621d1846c8620a34702af48df4d72985.jpg)



图 7: ESP-VoCat CoreBoard PCB 背面图（点击放大）


以下按照顺时针的顺序依次介绍背面PCB上的主要组件。为了方便用户使用，我们同时在ESP-VoCat的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/57ec1273fa49ac516c8882e689e1f5d62ccc09aa31bc4ace54b5e18f785ff965.jpg)



图 8: ESP-VoCat MicBoard PCB 背面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/2acd4819d8bbbd627e96622a20709cc85bb80855ec33fa774b6a3fa5b5389210.jpg)



图 9: ESP-VoCat BaseBoard PCB 背面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/597ac06b1c0d9ce1418cf267be479001aa6b313251945d29d4b18b9bc3e2f4bb.jpg)



图 10: ESP-VoCat 背面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td colspan="2">CoreBoard(核心板)</td></tr><tr><td>NS4150B(D类功放)</td><td>超低EMI、无需滤波器、3W单声道D类音频功放。</td></tr><tr><td>ES7210(音频解码芯片)</td><td>高性能四通道音频解码芯片,支持I2S/PDM/TDM数据端口。</td></tr><tr><td>SY8088AAC(DCDC芯片)</td><td>降压转换芯片,用于将5V电源转换为3.3V电源,为Codec提供稳定供电。</td></tr><tr><td>BaseBoard Connector(底板连接器)</td><td>底板连接器,用于连接底板与CoreBoard。</td></tr><tr><td>BMI270(IMU-惯性测量单元)</td><td>用于高性能应用的六轴智能低功耗惯性测量单元。</td></tr><tr><td>ES8311(音频编码解码芯片)</td><td>低功耗单声道音频编码解码器,具有高性能多比特Delta-Sigma音频ADC和DAC。</td></tr><tr><td colspan="2">MicBoard(麦克风板)</td></tr><tr><td>FPC Connector(FPC连接器)</td><td>连接MicBoard与CoreBoard FPC连接口。</td></tr><tr><td colspan="2">BaseBoard(底板)</td></tr><tr><td>M1.6 Welded Nut(M1.6焊接螺母)</td><td>用于固定主板到外壳。</td></tr><tr><td>RST Button(复位按键)</td><td>用于复位主板。</td></tr><tr><td>Magnetic Connector(磁吸连接器)</td><td>用于功能扩展,提供一个串口和5V电源接口,可以连接旋转底座等设备。</td></tr><tr><td>Power Switch(电源按键)</td><td>用于控制设备开关机,单击POWER按键即可切换开关机状态。</td></tr><tr><td>BOOT Button(启动按键)</td><td>在上电时,按住该按键可以进入下载模式。</td></tr><tr><td>SD Card Slot(SD卡槽)</td><td>支持高达32GB的microSD卡插槽,用于存储音频、图片、视频等数据。</td></tr></table>

## 开始开发应用

通电前，请确保 ESP-VoCat 完好无损。

必备硬件

• ESP-VoCat 

• USB 数据线

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

硬件设置 使用 USB 数据线将 ESP-VoCat 连接到电脑，通过 Type-C（USB-C 接口）烧录固件、调试和供电。

软件设置 请前往 ESP-IDF 快速入门小节查看如何快速设置开发环境，将应用程序烧录至您的开发板。

备注: 开发板使用USB端口与电脑通信。大多数操作系统（Windows、Linux、macOS）已预装所需驱动，开发板插入后可自动识别。如无法识别设备或无法建立串口连接，请参考如何建立串口连接获取安装驱动的详细步骤。

乐鑫为多种开发板提供了板级支持包(BSP)，可帮助您更轻松、高效地初始化和使用板载的主要外设，如LCD 显示屏、音频芯片、按键和 LED等。请访问 esp-bsp查询支持的所有开发板。

开发板应用示例存放在 esp-brookesia工程中。

## 4.1.2 硬件参考

## 功能框图

ESP-VoCat的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/4ca6487e9de81d71bda2ad7e0b2202047ecb7a2bfd05878ab8b035be73074494.jpg)



图 11: ESP-VoCat 功能框图（点击放大）


## 电源选项

可通过以下方法为开发板供电：

1. 通过 Type-C（USB-C 接口）供电

使用该方法供电时，使用USB Type-C数据线连接设备上Type-C接口。如果已安装锂电池，需要按下POWER按键开启对设备供电。

2. 通过 Magnetic Connector（磁吸连接器）供电

使用该方法供电时，将设备连接在对应的磁吸连接座上即可对设备进行供电。如果已安装锂电池，需要按下 POWER按键开启对设备供电。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b131d1263c825158bb86cb74f80aa4b032be89d8170c873816d4e32552c6bc0f.jpg)



图12: 磁吸连接器（点击放大）


## 3. 通过 电池供电

设备内部集成3.7 V 锂电池，按下POWER 按键即可对设备进行供电。上述任意外部供电方式，均可对设备内锂电池进行充电。

Type-C 接口

Magnetic Connector 接口

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/0357d2a964c213a64ed0b7bf35c4f0778673d66459e7c90964ea3b9fd2c17154.jpg)



图 13: Type-C 接口电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/ffd60d3fbc7629e55c988d8808709dd9ca11f20a8baa38c9be4e5691317e3b58.jpg)



图 14: Magnetic Connector 接口电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/d603692385607d4a916d369f5e965a25ec1e397910523b6c23467239d816bad6.jpg)



图15: LCD 接口电路图（点击放大）


## LCD 接口

请注意，CN3接口为其他屏幕兼容预留，目前未启用。

U2 接口为正式使用的 LCD 屏幕接口，该开发板使用的屏幕型号为 ST77916，LCD: 1.85”，360 x 360，ST77916，QSPI Interface，LCD_BLK (GPIO44) 可用于控制屏幕背光。

## SD 卡接口

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/2548e23f132a45478424e538237ba3ad63883a48eaab089ea79064c0b5f67d5e.jpg)



图 16: SD 卡接口电路图（点击放大）


请注意，SD卡接口支持：

• 1 线SD 总线配置

• 可通过SDIO 协议通信

开关机电路

POWER ON/OFF MANAGEMENT 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b0b8d43282dcb5ef1194025219dabc999b2270feb1a28e86f8f08423152ed1ba.jpg)



图 17: 开关机电路图（点击放大）


充电电路

麦克风接口

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/51eb7881442f261941f3630352bf67e8fec7a79fce7417b2d03c99e76163d039.jpg)



图18: 充电电路图（点击放大）


## BAT MANAGEMENT

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/82ffe4f62d319c401b2ffa2e9d33a9fda7bca84282713eb8301f2fce2f60e0c3.jpg)



图19: 电池管理电路图（点击放大）


## MIC CONNECT

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/09a7d98425de3993254c11ea85d1d8b4e6df2b3008409b791fed8881018c6d01.jpg)



图20: 麦克风接口电路图（点击放大）


## 4.1.3 硬件版本

ESP-VoCat v1.2 

• 以下管脚已重新分配：

– U1RXD：由 IO5 改为 IO4

– U1TXD：由 IO6 改为 IO5

– I2S_DI：由 IO15 改为 IO3

– PA_CTRL：由 IO4 改为 IO15

– LCD_RST_CTRL：由 IO3 改为 IO47

• TOUCH接口由 1 个增加为2 个，用于滑动触摸传感:

– TOUCH_PAD1：为 IO6

– TOUCH_PAD2：为 IO7

• 新增 CODEC 电源控制:

– CODEC_PWR_CTRL：为 IO48

• 新增 IIC 扩展接口:

– 增加 HC-1.25-4PLT 接口：将 VIN 、I2C_SDA 、I2C_SCL 和 GND 引出

ESP-VoCat v1.0 

• 首次发布

## 4.1.4 相关文档

• ESP-VoCat V1.2 原理图 (PDF)

• ESP-VoCat V1.2 PCB 布局图 (PDF)

• 显示屏规格书 (PDF)

• 用户指南 (HTML)

ESP-VoCat v1.0 

备注: 请查看主板上的丝印版本号，以确认您的开发板版本。对于 v1.0 版本的开发板，请参考当前用户指南；对于 v1.2 版本的开发板，请参考ESP-VoCat v1.2 。

本指南将帮助您快速上手 ESP-VoCat，并提供该款开发板的详细信息。

ESP-VoCat是一款智能AI开发套件，适用于需要大模型能力的语音交互类产品，例如玩具、智能音箱和智能中控系统。设备搭载ESP32-S3-WROOM-1模组、1.85英寸QSPI圆形触控屏、双麦克风阵列，并支持离线语音唤醒与声源定位算法。结合火山引擎扣子、Amazon Nova、OpenAI、小智AI、Gemini等提供的大模型能力，ESP-VoCat 可实现全双工语音交互、多模态识别以及智能体控制，为开发者打造完整的端侧 AI应用体验提供坚实基础。

ESP-VoCat 主控采用乐鑫 ESP32-S3-WROOM-2-N32R16V 模组，支持 2.4 GHz Wi-Fi 和 Bluetooth 5 (LE) 无线连接。存储方面，整机具备 16 MB PSRAM、32 MB flash 的存储空间，同时还配备了一个可支持高达32GB 的 microSD 卡插槽，满足语音交互和多媒体处理需求。配备 1.85 英寸圆形触摸屏（360 × 360 分辨率）与 ESP32-S3原生触摸传感器，提供直观丰富的交互体验。

音频方面，ESP-VoCat内置3W扬声器和双麦克风阵列，支持本地语音唤醒和声源定位。电源系统兼容5V DC和3.7 V锂电池供电。此外，还集成一个USB-C接口支持供电与编程下载，同时预留Pogopin接口方便功能扩展。

本指南包括如下内容：

• 入门指南：简要介绍了开发板和硬件、软件设置指南。

• 硬件参考：详细介绍了开发板的硬件。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/4300b6186cf676e2c16eb56b2278ead395f42ca69ad09077c418c118e1cefe9e.jpg)



图 21: ESP-VoCat 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/74e5868a48b9f5408e1696d5684452d31e7d88035999f0b07e5a61a2c40da34e.jpg)



图 22: ESP-VoCat 背面图（点击放大）


• 硬件版本：介绍硬件历史版本和已知问题（如有）。

• 相关文档：列出了相关文档的链接。

入门指南 本小节将简要介绍 ESP-VoCat，说明如何在 ESP-VoCat 上烧录固件及相关准备工作。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/4b1b11ce508cc4c61afbbad9d3b8585d6d526e8c6c33b85ec70c69344946d60b.jpg)



图 23: ESP-VoCat CoreBoard PCB 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/8ade020b729cac319e5391c7ab3b1c50f416fb615ae44c3882cb5df29f1dbc34.jpg)



图 24: ESP-VoCat MicBoard PCB 正面图（点击放大）


组件介绍 以下按照顺时针的顺序依次介绍正面 PCB 上的主要组件。为了方便用户使用，我们同时在ESP-VoCat的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/03e933164c46f3d569486ffc54c99315bbd384e74e9e50f265a7bf179c0b782e.jpg)



图 25: ESP-VoCat BaseBoard PCB 正面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/de7149d2b32375cc72c7d68aed4777f83b79d7519fed3223021bcf73258ea792.jpg)



图 26: ESP-VoCat 正面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td colspan="2">CoreBoard(核心板)</td></tr><tr><td>ESP32-S3-WROOM-2-N32R16V</td><td>主控芯片,集成32 MB Flash和16 MB PSRAM,支持2.4 GHz Wi-Fi和Bluetooth 5 (LE)无线连接。</td></tr><tr><td>Battery Connector(电池连接器)</td><td>电池连接器,用于连接3.7 V锂电池,上为正极,下为负极。</td></tr><tr><td>LCD FPC Connector(屏幕连接器)</td><td>用于连接1.85英寸圆形LCD屏幕,分辨率为360 x 360,详细参数请参考显示屏规格书。</td></tr><tr><td>MicBoard Connector(麦克风连接器)</td><td>MicBoard PCB板连接器,连接双麦克风阵列和状态指示LED灯。</td></tr><tr><td>Touch Connector(触摸连接器)</td><td>触摸连接器,用于连接触摸铜箔,实现触摸交互功能。</td></tr><tr><td>Speaker Connector(扬声器连接器)</td><td>2线扬声器连接器,用于连接内置3 W扬声器。</td></tr><tr><td colspan="2">MicBoard(麦克风板)</td></tr><tr><td>Green LED(绿色LED)</td><td>绿色LED指示灯。</td></tr><tr><td>MIC(麦克风阵列)</td><td>双LMA3729T381-OY3S麦克风阵列,支持本地语音唤醒和声源定位功能。</td></tr><tr><td colspan="2">BaseBoard(底板)</td></tr><tr><td>BQ27220(电池管理芯片)</td><td>电池管理芯片,用于电池电量检测、充电管理和电源状态监控。</td></tr><tr><td>TP4057(锂电池充电芯片)</td><td>锂电池充电芯片,用于为锂电池充电,充电电流为250 mA。</td></tr><tr><td>CoreBoard Connector(Core-Board 连接器)</td><td>CoreBoard PCB板连接器,连接核心板与底板。</td></tr><tr><td>TIV62569(DCDC芯片)</td><td>降压转换芯片,用于将5 V电源转换为3.3 V电源,为系统提供稳定供电。</td></tr><tr><td>SAM8108(开关机控制芯片)</td><td>开关机控制芯片,用于控制设备开关机,单击POWER按键即可切换开关机状态。</td></tr><tr><td>Type-C(USB-C接口)</td><td>USB-C接口,用于供电、编程下载和调试,支持对锂电池进行充电。</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/a7625ac050c76b73eb8ba6da5a3c96601fc712ec5ccf09420acd0a2fe92c828c.jpg)



图 27: ESP-VoCat CoreBoard PCB 背面图（点击放大）


以下按照顺时针的顺序依次介绍背面PCB上的主要组件。为了方便用户使用，我们同时在ESP-VoCat的外壳上标注出了这些组件或者接口。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/bdbf8b7c63d149e2f1d10bd5bd0b4ae7213f7e17f55cd40b7726b3d673e3e808.jpg)



图 28: ESP-VoCat MicBoard PCB 背面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/388c7ee84465d55fa89c55d3be09072c6e25e5dbed429fa27c8b1b8b00fa51b8.jpg)



图 29: ESP-VoCat BaseBoard PCB 背面图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/ddfed460372ff8d0e07a506afa9bc15eb5572896b2155a98a85a7bfe98e74697.jpg)



图 30: ESP-VoCat 背面图（点击放大）


<table><tr><td>主要组件</td><td>描述</td></tr><tr><td colspan="2">CoreBoard(核心板)</td></tr><tr><td>NS4150B(D类功放)</td><td>超低EMI、无需滤波器、3W单声道D类音频功放。</td></tr><tr><td>ES7210(音频解码芯片)</td><td>高性能四通道音频解码芯片,支持I2S/PDM/TDM数据端口。</td></tr><tr><td>BaseBoard Connector(底板连接器)</td><td>底板连接器,用于连接底板与CoreBoard。</td></tr><tr><td>BMI270(IMU-惯性测量单元)</td><td>用于高性能应用的6轴智能低功耗惯性测量单元。</td></tr><tr><td>ES8311(音频编码解码芯片)</td><td>低功耗单声道音频编码解码器,具有高性能多比特Delta-Sigma音频ADC和DAC。</td></tr><tr><td colspan="2">MicBoard(麦克风板)</td></tr><tr><td>FPC Connector(FPC连接器)</td><td>连接MicBoard与CoreBoard FPC连接口。</td></tr><tr><td colspan="2">BaseBoard(底板)</td></tr><tr><td>M1.6 Welded Nut(M1.6焊接螺母)</td><td>用于固定主板到外壳。</td></tr><tr><td>RST Button(复位按键)</td><td>用于复位主板。</td></tr><tr><td>Magnetic Connector(磁吸连接器)</td><td>用于功能扩展,提供一个串口和5V电源接口,可以连接旋转底座等设备。</td></tr><tr><td>Power Switch(电源按键)</td><td>用于控制设备开关机,单击POWER按键即可切换开关机状态。</td></tr><tr><td>BOOT Button(启动按键)</td><td>在上电时,按住该按键可以进入下载模式。</td></tr><tr><td>SD Card Slot(SD卡槽)</td><td>支持高达32GB的microSD卡插槽,用于存储音频、图片、视频等数据。</td></tr></table>

开始开发应用 通电前，请确保 ESP-VoCat 完好无损。

## 必备硬件

• ESP-VoCat 

• USB 数据线

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

硬件设置 使用 USB 数据线将 ESP-VoCat 连接到电脑，通过 Type-C（USB-C 接口）烧录固件、调试和供电。

软件设置 请前往 ESP-IDF 快速入门小节查看如何快速设置开发环境，将应用程序烧录至您的开发板。

备注: 开发板使用USB端口与电脑通信。大多数操作系统（Windows、Linux、macOS）已预装所需驱动，开发板插入后可自动识别。如无法识别设备或无法建立串口连接，请参考如何建立串口连接获取安装驱动的详细步骤。

乐鑫为多种开发板提供了板级支持包(BSP)，可帮助您更轻松、高效地初始化和使用板载的主要外设，如LCD 显示屏、音频芯片、按键和 LED等。请访问 esp-bsp查询支持的所有开发板。

开发板应用示例存放在 esp-brookesia工程中。

## 硬件参考

功能框图 ESP-VoCat的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/0cc29abb6e64faea1e2f31843d53fb92adbfadb401d3c9f79d6a5ee963e9a7e4.jpg)



图 31: ESP-VoCat 功能框图（点击放大）


电源选项 可通过以下方法为开发板供电：

1. 通过 Type-C（USB-C 接口）供电

使用该方法供电时，使用USB Type-C数据线连接设备上Type-C接口。如果已安装锂电池，需要按下POWER按键开启对设备供电。

2. 通过 Magnetic Connector（磁吸连接器）供电

使用该方法供电时，将设备连接在对应的磁吸连接座上即可对设备进行供电。如果已安装锂电池，需要按下 POWER按键开启对设备供电。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/537c91789736aad8b3bec4a515925b4b1a807fed2c2054466853cb60b4616e4d.jpg)



图32: 磁吸连接器（点击放大）


## 3. 通过 电池供电

设备内部集成3.7 V 锂电池，按下POWER 按键即可对设备进行供电。上述任意外部供电方式，均可对设备内锂电池进行充电。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/22c2dc1b2bf2264635ba57e6bbf0577475410dc688d5f69bfb034e8f0362626f.jpg)



图33: Type-C 接口电路图（点击放大）


Type-C 接口

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/1988b6d865b7866268d662462d5b52c1e5ca0e10765030b47aa4a29106b713a8.jpg)



图 34: Magnetic Connector 接口电路图（点击放大）



Magnetic Connector 接口


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/45723afa0f9b39d82017cde4037785990dfe1697b2f347116d968f66b15d9cf7.jpg)



图35: LCD 接口电路图（点击放大）



LCD 接口 请注意，CN3 接口为其他屏幕兼容预留，目前未启用。


U2 接口为正式使用的 LCD 屏幕接口，该开发板使用的屏幕型号为 ST77916，LCD: 1.85”，360 x 360，ST77916，QSPI Interface，LCD_BLK (GPIO44) 可用于控制屏幕背光。

SD卡接口 请注意，SD卡接口支持：

• 1 线SD 总线配置

• 可通过SDIO 协议通信

开关机电路

充电电路

麦克风接口

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/91114e76f4eea4b27b04ec31f4c4b16fd4c22295dab953b08501baa80948a3b1.jpg)



图 36: SD 卡接口电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/a9afaa7ce6c1b03b4b6810818e63557989ebfea3209bf4ae8bb18b65a73259e4.jpg)



图 37: 开关机电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/9507aa2ce5badc520edac6086545c53f9ace6d7a4f7d26825b2eec52f6e4daa2.jpg)



图38: 充电电路图（点击放大）


## BAT MANAGEMENT

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/2a1ec377163c2ab0ec0214bd9fde18bec9b1166cc084514f39ff4bd50978a252.jpg)



图39: 电池管理电路图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/eddfe6d6bab8c54b66c6c09f2fbdc0d448debb92fe22d798e7c2698b0a930b9d.jpg)



图40: 麦克风接口电路图（点击放大）


硬件版本 无历史版本。

## 相关文档

• ESP-VoCat V1.0 原理图 (PDF)

• ESP-VoCat V1.0 PCB 布局图 (PDF)

• 显示屏规格书 (PDF)

• 复刻教程 (HTML)

• 用户指南 (HTML)

## Chapter 5

## ESP-DualKey

ESP-DualKey 是乐鑫基于 ESP32-S3 芯片开发的智能双键控制器开发板，集成了智能家居控制、蓝牙键盘、USB 键盘等多种功能，可通过物理开关在不同工作模式间切换。该开发板配备双按键、RGB 灯效、电池管理、电源监控等功能，为开发者提供完整的智能按键解决方案。

开发板的应用示例存放在 Examples 目录中。

## 5.1 ESP-DualKey

备注: 请查看主板上的丝印版本号，以确认您的开发板版本。

本指南将帮助您快速上手 ESP-DualKey，并提供该款开发板的详细信息。

ESP-DualKey 是乐鑫基于 ESP32-S3 芯片开发的智能双键控制器开发板，集成了智能家居控制、蓝牙键盘、USB 键盘等多种功能，可通过物理开关在不同工作模式间切换。该开发板配备双按键、RGB 灯效、电池管理、电源监控等功能，为开发者提供完整的智能按键解决方案。

ESP-DualKey 主控采用乐鑫 ESP32-S3 芯片，支持 2.4 GHz Wi-Fi 和 Bluetooth 5 (LE) 无线连接。存储方面，整机具备 8 MB flash 存储空间，满足智能按键应用需求。配备双按键矩阵和 WS2812 RGB 灯效，提供直观丰富的交互体验。

电源方面，ESP-DualKey支持USB-C供电和内置锂电池供电，集成电池管理芯片和电源监控功能。此外，还集成一个 USB-C 接口支持供电与编程下载，同时提供多种工作模式切换功能。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/cc9b035fe77522433baee3a0488cb8b7cfac5280a2fa3773fef374d06dce3e7a.jpg)



图 1: ESP-DualKey 正面图（点击放大）


本指南包括如下内容：

• 入门指南：简要介绍了开发板和硬件、软件设置指南。

• 硬件参考：详细介绍了开发板的硬件。

• 硬件版本：介绍硬件历史版本和已知问题（如有）。

• 相关文档：列出了相关文档的链接。

备注: 关于出厂固件的使用说明，请参考 ESP-DualKey用户指南。

## 5.1.1 入门指南

本小节将简要介绍 ESP-DualKey，说明如何在ESP-DualKey上烧录固件及相关准备工作。

## 特性列表

该开发板具有以下特性：

## 按键矩阵配置：

• 2×1 矩阵配置

• 支持独立按键检测

• 支持组合按键功能

## RGB LED 特性：

• WS2812 可编程 RGB LED

• 支持多种灯效模式

• 支持亮度、色调、饱和度调节

## 模式切换开关：

• 左档位：蓝牙键盘模式

• 中档位：USB键盘模式

• 右档位：智能家居模式 (ESP RainMaker)

## 组件介绍

以下依次介绍开发板上的主要组件。为方便用户使用，ESP-DualKey的外壳上也标注了以下组件或接口。

<table><tr><td>主要组件</td><td>描述</td></tr><tr><td colspan="2">主控芯片</td></tr><tr><td>ESP32-S3</td><td>主控芯片,支持2.4 GHz Wi-Fi和Bluetooth 5 (LE)无线连接,集成8 MB flash存储。</td></tr><tr><td colspan="2">交互</td></tr><tr><td>双按键</td><td>2×1按键矩阵,支持独立按键和组合按键功能。</td></tr><tr><td>模式切换开关</td><td>三档位开关,用于切换工作模式(蓝牙键盘/智能家居/USB键盘)。</td></tr><tr><td colspan="2">RGB灯效</td></tr><tr><td>WS2812 RGB LED</td><td>可编程RGB LED,支持多种灯效模式,包括热力图、呼吸灯、流水灯等。</td></tr><tr><td colspan="2">电源管理</td></tr><tr><td>锂电池充电芯片</td><td>TP4057锂电池充电管理,支持USB-C充电。</td></tr><tr><td colspan="2">接口</td></tr><tr><td>USB-C接口</td><td>USB-C接口,用于供电、编程下载和调试,支持对锂电池进行充电。</td></tr><tr><td>两个HY2.0-4P接口</td><td>支持向外供电,用于连接外置传感器</td></tr><tr><td colspan="2">其他组件</td></tr><tr><td>电池电压监控</td><td>实时监控电池电压和充电状态。</td></tr><tr><td>VBUS监控</td><td>监控USB供电状态。</td></tr><tr><td>Deep-sleep</td><td>支持Deep-sleep模式以节省功耗。</td></tr></table>

## 应用示例

以下为开发板的应用示例：

• ESP-DualKey Smart Button Controller Example - 演示了如何使用 ESP-DualKey 开发板作为智能按钮控制器，具有智能家居控制、蓝牙键盘和 USB键盘功能，允许通过物理开关进行模式切换。

• test_apps - 为 ESP32 和 ESP32-C3 芯片上的 esp_hid 组件提供单元测试，支持开发者验证代码功能并根据需要添加新的测试案例。

更多示例及最新更新请参阅 examples 文件夹。

如需尝试应用示例或开发自定义应用，请参照开始开发应用小节中的步骤进行操作。

开始开发应用

通电前，请确保开发板完好无损。

## 必备硬件

• ESP-DualKey 

• USB 2.0 数据线（标准 A 型转 Type-C 型）

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

硬件设置 使用 USB数据线将ESP-DualKey连接到电脑，通过 USB-C 接口烧录固件、调试和供电。

软件设置 请前往 ESP-IDF 快速入门小节查看如何快速设置开发环境，将应用程序烧录至您的开发板。

备注: 开发板使用USB端口与电脑通信。大多数操作系统（Windows、Linux、macOS）已预装所需驱动，开发板插入后可自动识别。如无法识别设备或无法建立串口连接，请参考如何建立串口连接获取安装驱动的详细步骤。

乐鑫为多种开发板提供了板级支持包(BSP)，可帮助您更轻松、高效地初始化和使用板载的主要外设，如按键、LED和电源管理等。请访问 esp-bsp查询支持的所有开发板。

## 5.1.2 硬件参考

## 功能框图

ESP-DualKey的主要组件和连接方式如下图所示。

电源选项 您可从以下两种供电方式中任选其一给开发板供电：

1. 通过 USB-C 接口供电

使用该方法供电时，使用USB Type-C 数据线连接设备上 USB-C 接口。

2. 通过 内置锂电池供电

设备内部集成锂电池，支持独立供电运行。

模式切换开关 开发板模式切换开关电路图如下所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/2e8ec07d86054bf69afcd554a7a5d626ee5a123d0c92419f18b49d5ac1116ec6.jpg)



图 2: ESP-DualKey 功能框图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/ce22d6fd40bd4bee4412c3363acd009afca4b6e8b1387094bf9ff4a4e4851023.jpg)



图3: 模式切换开关电路图（点击放大）


## 5.1.3 硬件版本

无历史版本。

## 5.1.4 相关文档

• ESP-DualKey 原理图 (PDF)

• 使用指南 (HTML)

# 寿命终止开发板

本节包含ESP32-S3寿命终止开发板的用户指南，内容仅供参考。这些开发板虽然可能仍在市场上销售或在遗留系统中使用，但已停止接收更新、错误修复及官方支持。建议切换至新款开发板，以享受更优性能和更丰富的功能。

## 6.1 ESP32-S3-DevKitM-1

备注: 由于 ESP32-S3-DevKitM-1 开发板与 ESP32-S3-DevKitC-1-N8R8 和 ESP32-S3-DevKitC-1U-N8R8 在功能和用途上基本一致，ESP32-S3-DevKitM-1 已停止生产。开发者可使用 ESP32-S3-DevKitC-1-N8R8 或ESP32-S3-DevKitC-1U-N8R8 进行软件及基础功能测试（请参考ESP32-S3-DevKitC-1 用户指南）。上述调整不影响其所搭载 ESP32-S3-MINI-1/1U 模组的正常供货。

ESP32-S3-DevKitM-1 是一款入门级开发板，搭载的是 Wi-Fi+ 蓝牙 LE 模组 ESP32-S3-MINI-1 或 ESP32-S3-MINI-1U，该款模组因小尺寸而得名。

板上模组的大部分管脚均已引出至开发板两侧排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备，也可将开发板插在面包板上使用。

## 6.1.1 ESP32-S3-DevKitM-1

备注: 由于 ESP32-S3-DevKitM-1 开发板与 ESP32-S3-DevKitC-1-N8R8 和 ESP32-S3-DevKitC-1U-N8R8 在功能和用途上基本一致，ESP32-S3-DevKitM-1 已停止生产。开发者可使用 ESP32-S3-DevKitC-1-N8R8 或ESP32-S3-DevKitC-1U-N8R8 进行软件及基础功能测试（请参考ESP32-S3-DevKitC-1 用户指南）。上述调整不影响其所搭载 ESP32-S3-MINI-1/1U 模组的正常供货。

本指南将帮助你快速上手 ESP32-S3-DevKitM-1，并提供该款开发板的详细信息。

ESP32-S3-DevKitM-1 是一款入门级开发板，搭载的是 Wi-Fi+ 蓝牙 LE 模组 ESP32-S3-MINI-1 或 ESP32-S3-MINI-1U，该款模组因小尺寸而得名。

板上模组的大部分管脚均已引出至开发板两侧排针，开发人员可根据实际需求，轻松通过跳线连接多种外围设备，也可将开发板插在面包板上使用。

本指南包括如下内容：

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/50907e5dd869a9594294193000514bbc46c3cb113bf2eaae6a32363b3e7d957b.jpg)



图 1: ESP32-S3-DevKitM-1（板载 ESP32-S3-MINI-1 模组）


• 入门指南：简要介绍了开发板和硬件、软件设置指南。

• 硬件参考：详细介绍了开发板的硬件。

• 相关文档：列出了相关文档的链接。

## 入门指南

本小节将简要介绍 ESP32-S3-DevKitM-1，说明如何在 ESP32-S3-DevKitM-1 上烧录固件及相关准备工作。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/26de2a15bd2974df393870f0e638470e7309c47820ea00bb2f00b01af4590a1a.jpg)



图 2: ESP32-S3-DevKitM-1 - 正面


组件介绍 以下按照逆时针的顺序依次介绍开发板上的主要组件。

<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>ESP32-S3-MINI-1/1U</td><td>ESP32-S3-MINI-1 和 ESP32-S3-MINI-1U 是通用型 Wi-Fi + 低功耗蓝牙 MCU 模组,具有丰富的外设接口。ESP32-S3-MINI-1 采用 PCB 板载天线,ESP32-S3-MINI-1U 采用连接器连接外部天线。两款模组的核心是 ESP32-S3FN8 芯片。该芯片带有 8 MB flash,由于 flash 直接封装在芯片中,因此 ESP32-S3-MINI-1/1U 模组具有较小的封装尺寸。</td></tr><tr><td>5 V to 3.3 V LDO (5 V 转 3.3 V LDO)</td><td>电源转换器,输入 5 V,输出 3.3 V。</td></tr><tr><td>Pin Headers(排针)</td><td>所有可用 GPIO 管脚(除 flash 的 SPI 总线)均已引出至开发板的排针。请查看排针 获取更多信息。</td></tr><tr><td>USB-to-UART Port (USB 转 UART 接口)</td><td>Micro-USB 接口,可用作开发板的供电接口,可烧录固件至芯片,也可作为通信接口,通过板载 USB 转 UART 桥接器与芯片通信。</td></tr><tr><td>Boot Button (Boot 键)</td><td>下载按键。按住 Boot 键的同时按一下 Reset 键进入“固件下载”模式,通过串口下载固件。</td></tr><tr><td>Reset Button (Reset 键)</td><td>复位按键。</td></tr><tr><td>ESP32-S3 USB Port (ESP32-S3 USB 接口)</td><td>ESP32-S3 USB OTG 接口,支持全速 USB 1.1 标准。ESP32-S3 USB 接口可用作开发板的供电接口,可烧录固件至芯片,可通过 USB 协议与芯片通信,也可用于 JTAG 调试。</td></tr><tr><td>USB-to-UART Bridge (USB 转 UART 桥接器)</td><td>单芯片 USB 至 UART 桥接器,可提供高达 3 Mbps 的传输速率。</td></tr><tr><td>RGB LED</td><td>可寻址 RGB 发光二极管,由 GPIO48 驱动。</td></tr><tr><td>3.3 V Power On LED (3.3 V 电源指示灯)</td><td>开发板连接 USB 电源后,该指示灯亮起。</td></tr></table>

开始开发应用 通电前，请确保开发板完好无损。

## 必备硬件

• ESP32-S3-DevKitM-1 

• USB 2.0 数据线（标准 A 型转 Micro-B 型）

• 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和编程。

硬件设置 通过USB转UART接口或ESP32-S3 USB接口连接开发板与电脑。在后续步骤中，默认使用USB 转 UART 接口。

软件设置 请前往 快速入门，在 详细安装步骤 小节查看如何快速设置开发环境，将应用程序烧录至你的开发板。

## 内含组件和包装

零售订单 如购买样品，每个开发板将以防静电袋或零售商选择的其他方式包装。

零售订单请前往 https://www.espressif.com/zh-hans/company/contact/buy-a-sample。

批量订单 如批量购买，开发板将以大纸板箱包装。

批量订单请前往 https://www.espressif.com/zh-hans/contact-us/sales-questions。

## 硬件参考

功能框图 ESP32-S3-DevKitM-1的主要组件和连接方式如下图所示。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/03aafdbc38527e4bfe0350c130e860cbecebaa50ecb7b8d0a39d3b60087e3bcb.jpg)



图 3: ESP32-S3-DevKitM-1（点击放大）


电源选项 以下任一供电方式均可给开发板供电：

• USB 转 UART 接口供电或 ESP32-S3 USB 接口供电（选择其一或同时供电），默认供电方式（推荐）

• 5V 和 G (GND) 排针供电

• 3V3 和 G (GND) 排针供电

排针 下表列出了开发板两侧排针（J1 和 J3）的 名称和 功能，排针的名称如图ESP32-S3-DevKitM-1 - 正面所示，排针的序号与 开发板原理图(PDF) 一致。


J1


<table><tr><td>序号</td><td>名称</td><td>类型</td><td>功能</td></tr><tr><td>1</td><td>3V3</td><td>P</td><td>3.3 V 电源</td></tr><tr><td>2</td><td>0</td><td>I/O/T</td><td>RTC_GPIO0, GPIO0</td></tr><tr><td>3</td><td>1</td><td>I/O/T</td><td>RTC_GPIO1, GPIO1, TOUCH1, ADC1_CH0</td></tr><tr><td>4</td><td>2</td><td>I/O/T</td><td>RTC_GPIO2, GPIO2, TOUCH2, ADC1_CH1</td></tr><tr><td>5</td><td>3</td><td>I/O/T</td><td>RTC_GPIO3, GPIO3, TOUCH3, ADC1_CH2</td></tr><tr><td>6</td><td>4</td><td>I/O/T</td><td>RTC_GPIO4, GPIO4, TOUCH4, ADC1_CH3</td></tr><tr><td>7</td><td>5</td><td>I/O/T</td><td>RTC_GPIO5, GPIO5, TOUCH5, ADC1_CH4</td></tr><tr><td>8</td><td>6</td><td>I/O/T</td><td>RTC_GPIO6, GPIO6, TOUCH6, ADC1_CH5</td></tr><tr><td>9</td><td>7</td><td>I/O/T</td><td>RTC_GPIO7, GPIO7, TOUCH7, ADC1_CH6</td></tr><tr><td>10</td><td>8</td><td>I/O/T</td><td>RTC_GPIO8, GPIO8, TOUCH8, ADC1_CH7, SUBSPICS1</td></tr><tr><td>11</td><td>9</td><td>I/O/T</td><td>RTC_GPIO9, GPIO9, TOUCH9, ADC1_CH8, FSPIHD, SUBSPIHD</td></tr><tr><td>12</td><td>10</td><td>I/O/T</td><td>RTC_GPIO10, GPIO10, TOUCH10, ADC1_CH9, FSPICS0, FSPIIO4, SUB-SPICS0</td></tr><tr><td>13</td><td>11</td><td>I/O/T</td><td>RTC_GPIO11, GPIO11, TOUCH11, ADC2_CH0, FSPID, FSPIIO5, SUBSPID</td></tr><tr><td>14</td><td>12</td><td>I/O/T</td><td>RTC_GPIO12, GPIO12, TOUCH12, ADC2_CH1, FSPICLK, FSPIIO6, SUB-SPICLK</td></tr><tr><td>15</td><td>13</td><td>I/O/T</td><td>RTC_GPIO13, GPIO13, TOUCH13, ADC2_CH2, FSPIQ, FSPIIO7, SUBSPIQ</td></tr><tr><td>16</td><td>14</td><td>I/O/T</td><td>RTC_GPIO14, GPIO14, TOUCH14, ADC2_CH3, FSPIWP, FSPIDQS, SUB-SPIWP</td></tr><tr><td>17</td><td>15</td><td>I/O/T</td><td>RTC_GPIO15, GPIO15, U0RTS, ADC2_CH4, XTAL_32K_P</td></tr><tr><td>18</td><td>16</td><td>I/O/T</td><td>RTC_GPIO16, GPIO16, U0CTS, ADC2_CH5, XTAL_32K_N</td></tr><tr><td>19</td><td>17</td><td>I/O/T</td><td>RTC_GPIO17, GPIO17, U1TXD, ADC2_CH6</td></tr><tr><td>20</td><td>18</td><td>I/O/T</td><td>RTC_GPIO18, GPIO18, U1RXD, ADC2_CH7, CLK_OUT3</td></tr><tr><td>21</td><td>5V</td><td>P</td><td>5 V 电源</td></tr><tr><td>22</td><td>G</td><td>G</td><td>接地</td></tr></table>


J3


<table><tr><td>序号</td><td>名称</td><td>类型</td><td>功能</td></tr><tr><td>1</td><td>G</td><td>G</td><td>接地</td></tr><tr><td>2</td><td>RST</td><td>I</td><td>EN</td></tr><tr><td>3</td><td>46</td><td>I/O/T</td><td>GPIO46</td></tr><tr><td>4</td><td>45</td><td>I/O/T</td><td>GPIO45</td></tr><tr><td>5</td><td>RX</td><td>I/O/T</td><td>U0RXD, GPIO44, CLK_OUT2</td></tr><tr><td>6</td><td>TX</td><td>I/O/T</td><td>U0TXD, GPIO43, CLK_OUT1</td></tr><tr><td>7</td><td>42</td><td>I/O/T</td><td>MTMS, GPIO42</td></tr><tr><td>8</td><td>41</td><td>I/O/T</td><td>MTDI, GPIO41, CLK_OUT1</td></tr><tr><td>9</td><td>40</td><td>I/O/T</td><td>MTDO, GPIO40, CLK_OUT2</td></tr><tr><td>10</td><td>39</td><td>I/O/T</td><td>MTCK, GPIO39, CLK_OUT3, SUBSPICS1</td></tr><tr><td>11</td><td>38</td><td>I/O/T</td><td>GPIO38, FSPIWP, SUBSPIWP</td></tr><tr><td>12</td><td>37</td><td>I/O/T</td><td>SPIDQS, GPIO37, FSPIQ, SUBSPIQ</td></tr><tr><td>13</td><td>36</td><td>I/O/T</td><td>SPIIO7, GPIO36, FSPICLK, SUBSPICLK</td></tr><tr><td>14</td><td>35</td><td>I/O/T</td><td>SPIIO6, GPIO35, FSPID, SUBSPID</td></tr><tr><td>15</td><td>34</td><td>I/O/T</td><td>SPIIO5, GPIO34, FSPICS0, SUBSPICS0</td></tr><tr><td>16</td><td>33</td><td>I/O/T</td><td>SPIIO4, GPIO33, FSPIHD, SUBSPIHD</td></tr><tr><td>17</td><td>26</td><td>I/O/T</td><td>SPICS1, GPIO26</td></tr><tr><td>18</td><td>21</td><td>I/O/T</td><td>RTC_GPIO21, GPIO21</td></tr><tr><td>19</td><td>20</td><td>I/O/T</td><td>RTC_GPIO20, GPIO20, U1CTS, ADC2_CH9, CLK_OUT1, USB_D+</td></tr><tr><td>20</td><td>19</td><td>I/O/T</td><td>RTC_GPIO19, GPIO19, U1RTS, ADC2_CH8, CLK_OUT2, USB_D-</td></tr><tr><td>21</td><td>48</td><td>I/O/T</td><td>SPICLK_N, GPIO48, SUBSPICLK_N_DIFF, RGB LED</td></tr><tr><td>22</td><td>47</td><td>I/O/T</td><td>SPICLK_P, GPIO47, SUBSPICLK_P_DIFF</td></tr></table>


<sup>1</sup> P：电源；I：输入；O：输出；T：可设置为高阻。


有关管脚功能名称的解释，请参考 ESP32-S3 技术规格书(PDF)。


ESP32-S3-DevKitM-1


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/eb23dcbdaa4c463e61deb3ddb55ba79ce7d4cc505fc2c2152ca02e55caa3fa0a.jpg)



图 4: ESP32-S3-DevKitM-1 管脚布局（点击放大）


## 管脚布局

## 硬件版本

无历史版本。

## 相关文档

• ESP32-S3 技术规格书 (PDF)

• ESP32-S3-MINI-1 & ESP32-S3-MINI-1U 技术规格书 (PDF)

• ESP32-S3-DevKitM-1 原理图 (PDF)

• ESP32-S3-DevKitM-1 PCB 布局图 (PDF)

• ESP32-S3-DevKitM-1 尺寸图 (PDF)

• ESP32-S3-DevKitM-1 尺寸图源文件 (DXF) - 可使用 Autodesk Viewer 查看

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

## 6.2 ESP32-S3-USB-Bridge

ESP32-S3-USB-Bridge 通过在计算机和目前微控制器之间建立桥接，可以作为 USB 转 UART 芯片（如CP210x）或调试器的替代品。

## 6.2.1 ESP32-S3-USB-Bridge

本指南将帮助您快速上手 ESP32-S3-USB-Bridge，并提供该款开发板的详细信息。

本指南包括如下内容：

• 开发板概述：简要介绍了开发板的软件和硬件

• 应用程序开发：介绍了应用程序开发过程中的软硬件设置

• 硬件参考：详细介绍了开发板的硬件

• 硬件版本：暂无历史版本

• 样品获取：如何获取样品

• 相关文档：列出了相关文档的链接

## 开发板概述

ESP32-S3-USB-Bridge 是一款基于 ESP32-S3 芯片的开发板。

• 使用usb_wireless_bridge例程可在计算机和目标芯片之间建立桥接。它可以模拟 USB复合设备，支持多种功能：

– USB 转 UART 桥接：通过 USB 转 UART 桥接，实现计算机与目标芯片的串口数据收发。

– JTAG适配器：通过JTAG桥接，实现计算机与目标芯片之间双向传输JTAG通信。

– MSC 存储设备：通过将UF2 固件文件拖放到开发板的USB存储设备中，实现固件升级。

– 无线桥接：通过 ESP-NOW，实现无线烧录以及无线串口数据收发。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/e475183a46f0479fec6edd1bb29447d73f3329d0b22bd842f58f1477a3259b16.jpg)



图 5: ESP32-S3-USB-Bridge Type-C 连接


此外，开发板还支持USB Type-A 接口，更换方便。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/c9432a720ea69b3f3d314163eea2184a02a3b2182afa99c22e99addfa3af6002.jpg)



图 6: ESP32-S3-USB-Bridge Type-A 连接


## 特性列表 该开发板具有以下特性：

• 嵌入式模组：板载 ESP32-S3-MINI-1 模组，内置 4 MB flash 以及 2 MB PSRAM

• 指示灯：板载一颗WS2812指示灯，以及两颗串口数据指示灯

• USB：板载 USB 转 UART 桥接器及 JTAG 适配器，支持 USB Type-C 接口下载调试

功能框图 ESP32-S3-USB-Bridge的主要组件和连接方式如下图所示。

组件介绍 ESP32-S3-USB-Bridge 开发板较为小巧，尺寸为 23.3 mm * 31.5 mm。其集成了 ESP32-S3-MINI-1 模组，并提供了 12 个外接接口。

以下按照顺时针顺序依次介绍开发板上的主要组件。

<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>ESP32-S3-MINI-1-N4R2 模组</td><td>ESP32-S3-MINI-1-N4R2 模组是一款通用型 Wi-Fi + 低功耗蓝牙 MCU 模组,搭载 ESP32-S3 系列芯片,内置 4 MB flash 以及 2 MB PSRAM。除具有丰富的外设接口外,模组还拥有强大的神经网络运算能力和信号处理能力,适用于 AIoT 领域的多种应用场景。</td></tr><tr><td>TX/RX 指示灯</td><td>用于指示串口数据的收发状态。</td></tr><tr><td>扩展连接器</td><td>可供连接的 JTAG 管脚、串口管脚、TX/RX 管脚、Boot 管脚、Reset 管脚以及系统电压管脚。</td></tr><tr><td>Reset 按键</td><td>此按键连接目标芯片的 Reset 按键,与模组的 IO8 相连。单独按下此按钮,可以复位目标芯片。</td></tr><tr><td>USB 转 USB 接口</td><td>为整个系统提供电源。该端口用于 PC 端与 ESP32-S3-MINI-1 模组的 USB 通信。</td></tr><tr><td>Boot 按键</td><td>此按键连接目标芯片的 Boot 按键,与模组的 IO9 相连。长按 Boot 键时,再按 Reset 键可启动固件上传模式,然后便可通过串口或 USB 上传固件。</td></tr></table>


Boot


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/8ef7889d7403744a0f879e4b9a782b8cd7aedb9c85ef9246a00b03d4d285c039.jpg)



图 7: ESP32-S3-USB-Bridge 功能框图（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/698def3bfda857e3601ee12756f20347519961c75767fd2ea20f8d321a2c9d3d.jpg)



图 8: ESP32-S3-USB-Bridge - 正面（点击放大）


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/9f80617c99b0930b32215567f08acd31a831322e7a8a4d375aab667435d55b2c.jpg)



图 9: ESP32-S3-USB-Bridge - 背面（点击放大）


<table><tr><td>主要组件</td><td>介绍</td></tr><tr><td>5 V转3.3 V</td><td>用于将USB电压转换为3.3 V电压,为ESP32-S3-MINI-1模组供电。</td></tr><tr><td>模组Boot按键</td><td>此按键连接模组的IO0按键,长按此按键再重新给开发板上电,即可让开发板处于下载模式,上传新固件。</td></tr><tr><td>WS2812</td><td>与模组的IO42相连,用于指示开发板当前的状态。</td></tr></table>

软件支持 ESP32-S3-USB-Bridge 的开发框架为 ESP-IDF。ESP-IDF 是基于 FreeRTOS 的乐鑫 SoC 开发框架，具有众多组件，包括LCD、ADC、RMT、SPI等。开发板应用示例存放在Examples 中，在示例目录下输入 idf.py menuconfig 可以配置工程选项。

## 备注:

• 目前支持的 ESP-IDF 版本为 release/5.0。

• 请不要按住模组自身的 Boot按键后上下电，防止默认固件被替换。

## 应用程序开发

本节介绍硬件和软件的设置方法，以及烧录固件至开发板以开发应用程序的说明。

## 必备硬件

• 1 x ESP32-S3-USB-Bridge 

• 1 x LCD 子板

• 1 x USB 2.0 数据线（标准 A 型转 Type-C 型）

• 1 x 电脑（Windows、Linux 或 macOS）

备注: 请确保使用适当的USB数据线。部分数据线仅可用于充电，无法用于数据传输和程序烧录。

硬件设置 准备开发板，加载第一个示例应用程序：

1. 插入 USB数据线，分别连接PC 与开发板USB口。

2. 确保开发板处于下载模式。

3. 指示灯亮起，烧录完成。

硬件设置完成，接下来可以进行软件设置。

软件设置 请前往 快速入门的详细安装步骤 小节查看如何快速设置开发环境。

了解开发应用程序的更多软件信息，请查看软件支持。

## 硬件参考

本节提供关于开发板硬件的更多信息。

GPIO 分配列表 下表为 ESP32-S3-MINI-1 模组管脚以及外接接口的 GPIO 分配列表，用于控制开发板以及外接目标芯片的特定组件或功能。


表 1: ESP32-S3-MINI-1 管脚及外接接口 GPIO 分配


<table><tr><td>管脚</td><td>管脚名称</td><td>功能</td></tr><tr><td>1</td><td>GND</td><td>接地</td></tr><tr><td>2</td><td>3V3</td><td>供电</td></tr><tr><td>3</td><td>IO0</td><td>模组 Boot 按键,用于进入下载模式,以及作为按键输入管脚</td></tr><tr><td>4</td><td>IO2</td><td>JTAG 管脚 TDO,用于测试数据输出</td></tr><tr><td>5</td><td>IO3</td><td>JTAG 管脚 TDI,用于测试数据输入</td></tr><tr><td>6</td><td>IO4</td><td>JTAG 管脚 TCK,用于同步测试数据传输</td></tr><tr><td>7</td><td>IO5</td><td>JTAG 管脚 TMS,用于测试模式选择</td></tr><tr><td>8</td><td>IO8</td><td>连接目标芯片的 Reset 管脚,按下为低电平</td></tr><tr><td>9</td><td>IO9</td><td>连接目标芯片的 Boot 管脚,按下为低电平</td></tr><tr><td>10</td><td>IO19</td><td>与 USB_D- 接口相连</td></tr><tr><td>11</td><td>IO20</td><td>与 USB_D+ 接口相连</td></tr><tr><td>12</td><td>IO40</td><td>RX,用于连接目标芯片的 UART TX 管脚</td></tr><tr><td>13</td><td>IO41</td><td>TX,用于连接目标芯片的 UART RX 管脚</td></tr><tr><td>14</td><td>IO42</td><td>WS2812 控制管脚</td></tr></table>

备注: 管脚 3-14 为开发板提供的外接接口。除上表所列内容外，所有引出 IO 均可作为其他用处，其中GPIO5 和 GPIO8 与外部按键相连。

## 供电说明

USB 供电 开发板有两种 USB供电方式：

• 通过 Type-A 端口供电

• 通过 Type-C 端口供电

电压转换电路 ESP32-S3-USB-Bridge 可以将 5 V 转化为 3.3 V 供模组使用。

硬件设置选项

自动下载 按下模组Boot 按键后重新上电，随后松开模组 Boot 按键，即可使开发板进入下载模式。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/295447b10b9310320fa2e2da11e258c4437982a3501abd645a19d4ecb4ebd867.jpg)



图 10: ESP32-S3-USB-Bridge - Type-A 电源供电


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/166440733d892a21778cdbc9df044826f044974f89ddc908189b151f0baf389c.jpg)



图 11: ESP32-S3-USB-Bridge - Type-C 电源供电


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/aa334cb2f05553a0b25430472366e552a3be33def567952b8f07d445fbc17a0b.jpg)



图 12: ESP32-S3-USB-Bridge - 电压转换


## 硬件版本

无历史版本。

## 样品获取

此开发板已开源至 立创开源硬件平台。如有需要，请自行打样。

## 相关文档

请前往 esp-dev-kits 文档 HTML 网页版本 下载以下文档。

• ESP32-S3 技术规格书

• ESP32-S3-MINI-1 技术规格书

• 乐鑫产品选型工具

• ESP32-S3-USB-Bridge PCB 布局图

• ESP32-S3-USB-Bridge 原理图

有关本开发板的更多设计文档，请联系我们的商务部门 sales@espressif.com。

ESP32-S3 系列开发板

![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/f4e9608f238b244b330c22fa975abf8f1c73cb362e65b34f36b0da1889ed5753.jpg)



ESP32-S3-DevKitC-1


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/b605450b25f732e189802a0ef11444e0fcca6d403891bfdfa77deb527801f9bf.jpg)



ESP32-S3-USB-OTG


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/f73301fe516797a5e9dec941718b57a5dc98f5dc9a7b5349ceecc9124e50f1f0.jpg)



ESP32-S3-LCD-EV-Board


![image](https://cdn-mineru.openxlab.org.cn/result/2026-07-25/2d489cdf-5a9d-45c3-b439-33872ba32c33/05811330feac0fe44d249fff906ab17adc41a172ea7e02e809a2132e126ea03d.jpg)



ESP-VoCat



ESP-DualKey


# Chapter 7

# 相关文档和资源

## 7.1 相关文档

• 《ESP32-S3 技术规格书》 –提供ESP32-S3 芯片的硬件技术规格。

• 《ESP32-S3 技术参考手册》 –提供ESP32-S3芯片的存储器和外设的详细使用说明。

• 《ESP32-S3 硬件设计指南》 –提供基于ESP32-S3 芯片的产品设计规范。

• ESP32-S3 产品/工艺变更通知 (PCN)

https://espressif.com/zh-hans/support/documents/pcns?keys=ESP32-S3 

• ESP32-S3公告–提供有关安全、bug、兼容性、器件可靠性的信息。

https://espressif.com/zh-hans/support/documents/advisories?keys=ESP32-S3 

• 证书

https://espressif.com/zh-hans/support/documents/certificates 

• 文档更新和订阅通知

https://espressif.com/zh-hans/support/download/documents 

## 7.2 开发者社区

• ESP32-S3 ESP-IDF 编程指南 –ESP-IDF 开发框架的文档中心。

• ESP-IoT-Solution 编程指南 –ESP-IoT-Solution 开发框架的文档中心。

• ESP-FAQ-由乐鑫官方推出的针对常见问题的总结。

• ESP-IDF 及 GitHub 上的其它开发框架

https://github.com/espressif 

• ESP32 论坛–工程师对工程师 (E2E) 的社区，您可以在这里提出问题、解决问题、分享知识、探索观点。https://esp32.com/

• The ESP Journal –分享乐鑫工程师的最佳实践、技术文章和工作随笔。

• SDK和演示、App、工具、AT等下载资源https://espressif.com/zh-hans/support/download/sdks-demos

## 7.3 产品

• ESP32-S3 系列芯片–ESP32-S3 全系列芯片。

https://espressif.com/zh-hans/products/socs?id=ESP32-S3 

• ESP32-S3 系列模组–ESP32-S3 全系列模组。

https://espressif.com/zh-hans/products/modules?id=ESP32-S3 

• ESP32-S3 系列开发板–ESP32-S3 全系列开发板。

https://espressif.com/zh-hans/products/devkits?id=ESP32-S3 

• ESP Product Selector（乐鑫产品选型工具）–通过筛选性能参数、进行产品对比快速定位您所需要的产品。

https://products.espressif.com/#/product-selector 

## 7.4 联系我们

• 商务问题、技术支持、电路原理图& PCB设计审阅、购买样品（线上商店）、成为供应商、意见与建议

https://espressif.com/zh-hans/contact-us/sales-questions 

## Chapter 8

## 免责声明和版权公告

本文档中的信息，包括供参考的 URL 地址，如有变更，恕不另行通知。

本文档可能引用了第三方的信息，所有引用的信息均为“按现状”提供，乐鑫不对信息的准确性、真实性做任何保证。

乐鑫不对本文档的内容做任何保证，包括内容的适销性、是否适用于特定用途，也不提供任何其他乐鑫提案、规格书或样品在他处提到的任何保证。

乐鑫不对本文档是否侵犯第三方权利做任何保证，也不对使用本文档内信息导致的任何侵犯知识产权的行为负责。本文档在此未以禁止反言或其他方式授予任何知识产权许可，不管是明示许可还是暗示许可。

Wi-Fi 联盟成员标志归 Wi-Fi 联盟所有。蓝牙标志是 Bluetooth SIG 的注册商标。

文档中提到的所有商标名称、商标和注册商标均属其各自所有者的财产，特此声明。