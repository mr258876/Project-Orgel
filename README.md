# Project Orgel
>### 赛博音乐盒计划第一部分
>### Cyber Musicbox Project Part I

- [中文](#中文)
- [English](#english)

# 中文
>## 目录
- [项目状态](#项目状态)
- [配件](#配件)
- [某个简短的改装指南](#某个简短的改装指南)
    - [传动改造](#传动改造)
    - [八音盒及电机的固定](#八音盒及电机的固定)
    - [电路搭建](#电路搭建)
- [控制程序烧录](#控制程序烧录)
- [使用指南](#使用指南)
    - [初次使用](#初次使用)
    - [基本操作](#基本操作)
    - [菜单与设置](#菜单与设置)
    - [无线控制](#无线控制)

>## 项目状态
* 基础原理验证 ✔
* 基础 UI ✔
* 更多可在UI中调节的值 ✔
* UI 多语言支持 ✔
* 项目自述 ✔
* 无线控制 ✔
* 多平台支持 ✔


>## 配件
* 八音盒 (废话) *1
* 支持串口通信的单片机 *1
>ℹ注：推荐使用ESP32或nRF51802
* TMC2209 步进电机驱动模块 *1
>⚠注意：模块需要支持以串口方式与MCU进行通信
* 42BYGH40/39 步进电机 (高40/39mm) *1  
>ℹ注：可以是任意两相四线步进电机, 但其应能够提供足够力矩(推荐300mN\*m以上)
* 42步进电机支架 (可选) *1
* 0.4模齿轮(60齿以上，但不宜过大) *1
>ℹ注：齿轮越大越好，降低电机转速是减小噪音的有效方法
<br/>⚠注意：齿轮需要能够与电机输出轴匹配
* 旋转编码器 *1
* SSD1306 0.96 寸 OLED 模块 *1
* 电源 (Plan A): USB-C PD 诱骗器 *1, 支持PD快充协议的充电器 *1, MP1584 DC-DC 降压模块 *1
* 电源 (Plan B): 3.3/5/12v 多路输出电源模块 *1, 12v/2A 电源适配器 *1
* 用于固定八音盒与电机的木盒、木块等 *1
* 用于固定的M3螺丝、M3螺母若干




## 某个简短的改装指南
接下来的步骤组成了一个简短的安装指南。步骤供参考，可根据实际情况进行调整。
### 传动改造
如图所示，改装电动只需使用八音盒传动部分中的部分齿轮。由于避开了传动部分中的易损齿轮，对该齿轮损坏的八音盒进行改装不失为一个绝佳选择。
![before_modding][before_modding_url]
![after_modding][after_modding_url]

>⚠注意：在手摇八音盒中，手柄部分通常为噪音的源头之一。为了达到静音目的，断开手柄与其他齿轮间的传动是必要的。移除手柄或②号齿轮均可实现。图为移除了手柄及②号齿轮的八音盒。
![handle_removed][handle_removed_url]
### 八音盒及电机的固定
毫无疑问，电机需要与八音盒固定在一起以进行传动。该部分有较多方案可供选择，故此处将不做较多阐述，实际应用时可不必遵照。

>⚠注意：不论以何种方式固定，**电机齿轮必须尽量与八音盒齿轮紧密配合**，否则可能会产生噪音并损坏齿轮。

考虑到八音盒可能需要一个共鸣腔，推荐将八音盒与电机固定在木盒中。如不考虑共鸣，或不方便对木盒进行钻孔/开槽，则也可固定在木块或其他材料上。此处以固定在木盒中为例。

由于42电机的体积较大，因此八音盒原配木盒大概率需要进行更换。目前市面上有多种尺寸木盒可供选择。上一节示例中的木盒尺寸为 长20cm\*宽13.5cm*高9cm。

#### 使用3D打印支架进行固定

项目提供了提供一个支架3D模型可进行参考。支架由两部分组成，分别负责替换原有支架与步进电机的固定。

[模型可在此下载](/Models/)

### 电路搭建

本项目提供两个不同平台版本：一个较为简易的使用ESP32开发板与其他现成部件进行搭建的版本，与一个从零开始构建的nRF51平台版本。您可以根据实际需要进行选择。

#### ESP32版本
`ESP32`版本基于现成部件，电路十分简单，如下图所示。

![curcit_schema][schema_url]

处于空间利用方面的考量，推荐使用PCB实现上图中电路。[Gerber文件请点击这里][gerber_url]。
>ℹ注：仅适用于尺寸为22mm\*17mm的MP1584模块与焊接了TX,RX针脚的乐积TMC2209模块

如果无法进行焊接，该版本同样可以考虑使用面包板完成接线。

**ESP32版本参考BOM**
- 以下链接仅供参考，您可以根据实际情况自行购买
- 链接可能失效，如需更新请提起issue

| 商家 | 商品链接 | 款式 | 价格 (CNY) | 数量 | 备注 |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 尚雅木艺 | [实木带锁复古收纳盒定制长方形大小号木盒子定做木质包装盒礼品盒](https://item.taobao.com/item.htm?id=610812897067) | 20\*13.5\*9 | 17.9 | 1 | 需自行开孔/开槽 (大概是整个项目最困难的部分) |
| 淮安善能机械有限公司 | [0.4模 60齿 孔5/6 顶丝 善能机械 铝齿轮 齿轮定制 小模数齿轮](https://item.taobao.com/item.htm?id=587174945136) | 60齿外径24.8/齿厚4/孔5台阶顶丝 | 9 | 1 | 不包邮 |
| 信泰微电子 | [ESP32-D0WDQ6开发板 蓝牙+WIFI模块 Lua物联网 米思齐图形化编程](https://item.taobao.com/item.htm?id=647797965965) | 30针 | 19.8 | 1 | 可能不太好找同款 |
| 信泰微电子 | [数字旋转编码器模块 转动电位器 旋转电位器 带旋钮帽](https://item.taobao.com/item.htm?id=576520367466) | - | 3.8 | 1 | - |
| 信泰微电子 | [0.96寸蓝色 黄蓝双色 白色 I2C IIC通信 显示器 OLED液晶屏模块](https://item.taobao.com/item.htm?id=43639171586) | 新款 颜色任意 | 10 | 1 | - |
| 信泰微电子 | [DC-DC 电源模块 降压稳压模块 车载电源 12V 5V转3.3V 固定输出](https://item.taobao.com/item.htm?id=534263863865) | - | 2.5 | 1 | - |
| 信泰微电子 | [XH2.54 2.54mm间距 白色座 接插件 直针座 4P XH2.54-4P连接线座](https://item.taobao.com/item.htm?id=36638833821) | - | 0.05 | 1 | 实际需要1个,但是不知道只买1个发不发货 |
| 微盛恒创电子 | [PD2.03.0诱骗器 触发转接笔记本电压可调9V12V15V 20VTYPE-C母头](https://item.taobao.com/item.htm?id=643246818193) | 12V | 4.8 | 1 | - |
| 乐积科技 | [3D打印机配件 TMC2209驱动大电流高细分替换2208A4988 LV8729模块](https://item.taobao.com/item.htm?id=610229295552) | - | 18.6 | 1 | 需要补齐四根空脚 |
| 布加特官方店 | [42/57步进电机支架安装固定座卧式支架电机马达支架座配带螺丝](https://item.taobao.com/item.htm?id=571691530940) | - | 1.7 | 1 | - |
| 布加特官方店 | [3D打印机配件42步进电机 驱动马达两相四线1.8度雕刻机42歩进马达](https://item.taobao.com/item.htm?id=559102944871) | 任意款式 XH-2.54配线 | 21.5 | 1 | - |
| telesky旗舰店 | [单排母双排母2.54mm排针母座排座针插座插针2.0 1/2/3/4/6/10-40P](https://item.taobao.com/item.htm?id=559102944871) | 1*2p单排母座2.54mm 20个 | 2.44 | 1 | 可选, 实际需要2个 |
| telesky旗舰店 | [单排母双排母2.54mm排针母座排座针插座插针2.0 1/2/3/4/6/10-40P](https://item.taobao.com/item.htm?id=559102944871) | 1*4p单排母座2.54mm 20个 | 2.75 | 1 | 可选, 实际需要1个 |
| telesky旗舰店 | [单排母双排母2.54mm排针母座排座针插座插针2.0 1/2/3/4/6/10-40P](https://item.taobao.com/item.htm?id=559102944871) | 1*5p单排母座2.54mm 20个 | 2.98 | 1 | 可选, 实际需要1个 |
| telesky旗舰店 | [单排母双排母2.54mm排针母座排座针插座插针2.0 1/2/3/4/6/10-40P](https://item.taobao.com/item.htm?id=559102944871) | 1*8p单排母座2.54mm 20个 | 3.59 | 1 | 可选, 实际需要2个 |
| telesky旗舰店 | [单排母双排母2.54mm排针母座排座针插座插针2.0 1/2/3/4/6/10-40P](https://item.taobao.com/item.htm?id=559102944871) | 1*15p单排母座2.54mm 10个 | 2.52 | 1 | 可选, 实际需要2个 |

#### nRF51版本
`nRF51`版本将主控、步进电机驱动、DCDC电路等部分集成在一块PCB上，进而减小了控制板体积，但同时也提升了制作难度。电路图如下所示。

![curcit_schema_nrf51][schema_url_nrf51]

**项目BOM**

[项目BOM可在此处查看。][bom_url_nrf51]

**参考PCB**

[参考PCB可以在此处下载。][gerber_url_nrf51]

**焊接辅助工具**

[此处可查看对应焊接辅助工具。][solder_helper_url_nrf51]

## 控制程序烧录
改装的最后一步是将电机控制程序烧录至`ESP32`或`nRF51802/nRF51822`中。

您可以直接刷入 Release 中已编译好的固件，或自行使用Arduino编译并刷入。

### 刷入预编译固件

#### 为ESP32刷入预编译固件

0. 移步[乐鑫科技网站]("https://www.espressif.com.cn/zh-hans/support/download/other-tools")并下载`ESP Download Tool(Flash下载工具)`。</br>

1. 打开ESP Download Tool，芯片类型选择`ESP32`，工作模式选择`开发模式`。</br>
![image](/pics/flash_step1.png)</br>
2. 按照下图设置刷入的文件、flash地址、flash速度，串口及下载速度按实际情况选择。</br>
![image](/pics/flash_step2.png)</br>
3. 点击`下载`按钮。当状态显示`完成`后，断开开发板与电脑的连接。</br>

#### 为nRF51刷入预编译固件

>ℹ注：为了向nRF51芯片刷入程序，您额外需要一个适用于ARM架构单片机的编程器，例如`ST-Link`、`J-Link`等。下方的流程以在Windows环境下使用`ST-Link`刷入为例，您可能需要根据实际情况适当修改命令行参数。

0. 移步[OpenOCD Github页面](https://github.com/openocd-org/openocd/releases)，下载并解压`OpenOCD`。</br>
1. 将编程器连接至控制板。
```
编程器             控制板
______         _____________
3V3   | ----> | 3V3   SWCLK | <-----,
GND   | ----> | GND   SWDIO | <--,  |
SWDIO | ----, |_____________|    |  |
SWCLK | --, `--------------------`  |
______|   `-------------------------`
```
2. 打开命令提示符(`CMD`)或`PowerShell`，并切换路径至`OpenOCD`文件夹中的`bin`目录下。</br>
3. 使用以下命令刷入预编译固件。在刷入完成后，命令行中应出现`** Verified OK **`提示。
   - 此处假设`Project-Orgel-nRF51.hex`与`openocd.exe`置于同一目录下。
   - 您可以根据实际情况将`st-link.cfg`替换为其他受支持的编程器配置文件。
```powershell
./openocd.exe -f "interface/st-link.cfg" -f "target/nrf51.cfg" -c "init" -c "reset halt" -c "nrf51 mass_erase" -c "program Project-Orgel-nRF51.hex verify reset exit"
```

### 自行编译并刷入

#### 为ESP32编译程序并刷入
首先需要在电脑上搭建Arduino-ESP32环境。[知乎用户铁熊的文章][zhihu_esp32_environment_url]可供参考。

在环境搭建完成后，还需要在库管理器中安装以下库：
```
tcMenu      @4.4.0
TMCStepper  @0.7.3
U8g2        @2.34.4
NimBLE      @1.4.2
```

准备完成后，使用Arduino IDE打开`Project-Oegel`文件夹中的`Project-Orgel.ino`进行烧录。

>⚠注意：Arduino IDE中的`esp32开发板`版本不可使用`3.0.0`及以上版本！

#### 为nRF51编译程序并刷入

对于`nRF51`版本，您需要将`arduino-esp32`开发环境替换为[n-able-Arduino](https://github.com/h2zero/n-able-Arduino)，具体操作如下：
1. 在`文件`->`首选项`->`附加开发板管理器网址`中添加链接`https://h2zero.github.io/n-able-Arduino/package_n-able_boards_index.json`
2. 待安装完成后，在`工具`->`开发板`->`Arm (Nim)BLE Boards`菜单中选择`Waveshare BLE400`开发板。
3. 在`工具`->`Low Frequency Clock`菜单中选择`Synthesized`选项。
4. 在`工具`->`编程器`菜单中选择`st-link v2`选项。

对于`nRF51`版本，您还需要将上述列表中的`U8g2`库替换为`SSD1306UTF8`库(基于`SSD1306Ascii`库)，请从[此处](https://github.com/mr258876/SSD1306UTF8)下载。

>ℹ注：对于`nRF51`版本，您需要点击`项目`菜单中的`使用编程器上传`选项刷入自编译程序。

## 使用指南
>⚠注意：由于硬件组合及改装操作的多样性，在不同情形下运行可能触发未知的bug，如部分功能不可用等。该指南仅代表在测试硬件上的操作及运行效果。

>🛑警告：步进电机驱动器运行会产生高温。请小心烫伤。

### 初次使用
将程序首次烧录至ESP32时，所有设置为默认初始值0。请遵照下述方法设置`齿轮齿数`、`运行电流`并保存后再使用。
### 基本操作
在主视图中，旋转旋钮更改BPM。单击旋钮切换播放状态。
![mainframe_zh][mainframe_zh_url]
### 菜单与设置
在主视图中长按可进入主菜单。
![tomenu_zh][tomenu_zh_url]

在主菜单中选择`Back and Save`以保存设置并回到主菜单。在主菜单中无操作30秒会自动返回主界面。

>⚠注意：在更改菜单中选项值后必须通过`Back and Save`选项退出菜单，否则在重启后选项值将恢复更改前状态。

在菜单中旋转旋钮查看选项，单击旋钮以与选项交互。在交互状态下旋转旋钮以更改选项值，单击旋钮退出。
![menu_zh][menu_zh_url]

各可调节值说明：
 - 电机设置
     - 反向运转: 控制电机正反转
     - 齿轮齿数: 电机齿轮齿数设置
     - 运行电流: 电机运行电流设置，单位mA 参考值：1050mA
    >⚠注意：随着电流的增大，驱动器会产生更多热量并可能导致过热保护，电机可能会产生更大噪音。正常使用请不要将该值提升至1700mA以上。
 - 语言
     - ENG：英语
     - 中文：简体中文
 - 蓝牙
     - 开：开启蓝牙并启用无线控制功能
     - 关：关闭蓝牙并停用无线控制功能

### 无线控制

> 请打开设置中的蓝牙开关，随后访问[https://mr258876.github.io/Project-Orgel/](https://mr258876.github.io/Project-Orgel/)并按提示操作。

Have fun!

# English
>## Table of Contents
- [Project Orgel](#project-orgel)
- [中文](#中文)
  - [某个简短的改装指南](#某个简短的改装指南)
    - [传动改造](#传动改造)
    - [八音盒及电机的固定](#八音盒及电机的固定)
      - [使用3D打印支架进行固定](#使用3d打印支架进行固定)
    - [电路搭建](#电路搭建)
      - [ESP32版本](#esp32版本)
      - [nRF51版本](#nrf51版本)
  - [控制程序烧录](#控制程序烧录)
    - [刷入预编译固件](#刷入预编译固件)
      - [为ESP32刷入预编译固件](#为esp32刷入预编译固件)
      - [为nRF51刷入预编译固件](#为nrf51刷入预编译固件)
    - [自行编译并刷入](#自行编译并刷入)
      - [为ESP32编译程序并刷入](#为esp32编译程序并刷入)
      - [为nRF51编译程序并刷入](#为nrf51编译程序并刷入)
  - [使用指南](#使用指南)
    - [初次使用](#初次使用)
    - [基本操作](#基本操作)
    - [菜单与设置](#菜单与设置)
    - [无线控制](#无线控制)
- [English](#english)
  - [Hardware Requirements](#hardware-requirements)
  - [A Brief Modding Guide](#a-brief-modding-guide)
    - [Gear Modding](#gear-modding)
    - [Mounting](#mounting)
    - [Circuit](#circuit)
    - [Uploading Code](#uploading-code)
      - [Flash the compiled firmware](#flash-the-compiled-firmware)
      - [Compile and flash by yourself](#compile-and-flash-by-yourself)
  - [Usage](#usage)
    - [First Use](#first-use)
    - [Basic Operations](#basic-operations)
    - [Settings](#settings)
    - [Wireless Control](#wireless-control)

>## Project Status 
* Make it work  ✔
* A Basic UI    ✔
* More Adjustable Values in UI ✔
* UI MultiLanguage Support   ✔
* Readme  ✔
* Wireless Control ✔
* Multi Platform Support ✔


## Hardware Requirements
* Musicbox (of course) *1
* ESP32-D0DWQ6 Dev Moudle 30pin *1
* TMC2209 Stepper Driver Module *1
>⚠Caution: the driver moudlue should be able to communicate with the MCU through UART or Serial port.
* 42BYGH40/39 NEMA17 Stepper *1  
>ℹNote: Could be replaced with any 2-phase 4-wire step motor, however it should provide enough torque(recommand 300mN*m or above).
* NEMA17 Motor Stand (optional) *1
* 0.4M gear(At least 60 teeth, but not too big) *1  
>ℹNote：It is a good idea to have a bigger gear, reducing the motor speed is an effective way to reduce noise.
<br/>⚠Caution: The gear should be able to match the output shaft of the motor.
* Rotatry Encoder *1
* SSD1306 0.96 inch OLED Screen *1
* Power Supply (Plan A): USB-C PD Trigger/Decoy *1, Phone charger with fast charging support *1, MP1584 DC-DC step-down moudle *1
* Power Supply (Plan B): 3.3/5/12v multi-output power moudle *1, 12v/2A AC/DC adapter *1
* Box or something else for mounting musicbox and motor *1
* M3 Screws & Nuts for Mounting

## A Brief Modding Guide
The following steps constitute a biref modding guide, which you could refer to but don’t have to strictly follow.
### Gear Modding
Only some of all gears in the musicbox will be used after the modding, as shown in the picture below. Avoiding the vulnerable gear(gear #2), it is a good choice to mod a musicbox with that gear damaged.
![before_modding][before_modding_url]
![after_modding][after_modding_url]

>⚠Caution：The handle is usually one of the main noise source. In order to get silent, it is necessary to disconnect the transmission between the handle and other gears, which could be implemented by removing the handle or gear #2. A music box with handle and gear #2 removed is as shown. ![handle_removed][handle_removed_url]
### Mounting
Without doubt, the motor needs to be mounted with the musicbox. With many solutions avilable, there will not be much description here, and you don't have to follow.

>⚠Caution: No matter how they are mounted, **the gear of motor have to work as close as possible**, or there will might be noise and the gear may got damange.

Considering that the music box may need a resonance cavity, it is recommended to fix the music box and the motor in a wooden box. If resonance is not considered, or it is inconvenient to drill/slot the wooden box, it can also be fixed on a wooden block or other materials. Take fixing in a wooden box as an example

Due to the ize of the NEMA-17 motor, the original wooden box of the music box will most likely need to be replaced. There are many sizes of wooden boxes available on the market. The size of the wooden box in the example in the previous section is L20cm * W13.5cm * H9cm.
### Circuit
The circuit used in this project is simple, schematic as shown below.

![curcit_schema][schema_url]

Considerated in space utilization, using a PCB to imply the curcit is recommedned. As a beginner of drawing PCB, only a poor board could be provided. Click [here][gerber_url] if you would take a look.
>ℹNote：Only applies to MP1584 with size 2mm\*17mm and Lerdge TMC2209 module with TX/RX pin soldered.

Using a breadboard to apply the cutcit also works.

### Uploading Code
The last step is to upload the controlling program to the ESP32.

You can flash the compiled firmware directly into Release, or use Arduino to compile and flash it yourself.

#### Flash the compiled firmware

0. Go to [Espressif Technology website]("https://www.espressif.com.cn/en/support/download/other-tools") and download `ESP Download Tool`. </br>

1. Open ESP Download Tool, select `ESP32` for chip type, and `Development Mode` for working mode. </br>
![image](/pics/flash_step1.png)</br>
2. Set the flashed file, flash address, flash speed, serial port and download speed according to the actual situation according to the figure below. </br>
![image](/pics/flash_step2.png)</br>
3. Click the `Download` button. When the status shows `Done`, disconnect the development version from the computer. </br>

#### Compile and flash by yourself


First, you will need an Arduino-ESP32 environment. There's a [guide from randomnerdtutorials][randomnerdtutorials_esp32_environment_url] could be used as a reference.

For `ESP32` devices, he following libraries are also required after building up the environment:
```
tcMenu      @4.2.1
TMCStepper  @0.7.3
U8g2        @2.34.4
NimBLE      @1.4.2
```

For `nRF51` devices, you need to replace `U8g2` in the list above as an MODDED `SSD1306Ascii` library, which could be found [here](https://github.com/mr258876/SSD1306Ascii).

After that, open `Project-Orgel.ino` in folder `Project-Oegel` with Arduino-IDE to upload.

>⚠Note：`esp32` version in Arduino IDE should be below `3.0.0`, or compilation will fail!

## Usage
>⚠Caution: Due to the diversity of hardware bundles and differences in modding procedure, unknown bugs might appear in some situations (e.g. functions not working). This manual only represents the operations and results on the testing hardware.

>🛑Warning: The driver moudle would generate heat. Please be aware of burns.

### First Use
When first upload the code to ESP32, all setting values will be default to 0. Please set `Geat Teeth`, `Current` by following the methods below before use.
### Basic Operations
In the main view, change BPM by rotating the knob, switch playback status by pressing the knob once.
![mainframe_en][mainframe_en_url]
### Settings
Pressing down the knob and hold for few seconds to go to the menu.
![tomenu_en][tomenu_en_url]

Select `Back and Save` in menu to save the settings and back to main view. After entered the menu, it will go back to the main view without saving automatically with no action in 30 secs。

>⚠Caution: Exiting through `Back and Save` option is required after changing any value in the settings menu, or the values will restore after reboot.

In the menu, rotate the knob to go through, intract with options by pressing down once. Change the option value by rotating the knob when option is acticed, and pressing down once to go back to menu.
![menu_en][menu_en_url]

Explations on adjustable values:
 - Motor
     - Reversed: To reverse the motor operation direction.
     - Gear Teeth: Teeth number of the gear installed on the motor. Related to running speed.
     - Current: The runing current of motor in mA. Reference value: 1050mA. 
    >⚠Caution：The Driver moudle would produce more heat as the current goes up, and might trigger overheat protection. The motor will produce more noise as well. Do not raise this value over 1700mA in normal use.
 - Language
     - ENG: English
     - 中文: Simplified Chinese
 - Bluetooth
     - On: Turn on bluetooth, and enable wireless control
     - Off: Turn off bluetooth, and disable wireless control

### Wireless Control

> Turn ON the `bluetooth` option in settings menu, then visit [https://mr258876.github.io/Project-Orgel/](https://mr258876.github.io/Project-Orgel/).

Have fun!

[before_modding_url]:/pics/before_modding.jpg
[after_modding_url]:/pics/after_modding.jpg
[handle_removed_url]:/pics/handle_removed.jpg

[schema_url]:/PCB/Schematic_Project%20Orgel_2021-11-29.png
[gerber_url]:/PCB/Gerber_PCB_Project%20Orgel.zip

[bom_url_nrf51]:/PCB/BOM_Board1_Orgel%20nRF51_2024-07-24.xlsx
[schema_url_nrf51]:/PCB/SCH_Orgel%20nRF51_1-P1_2024-07-24.png
[gerber_url_nrf51]:/PCB/Gerber_PCB1_Orgel%20nRF51_2024-07-24.zip
[solder_helper_url_nrf51]:https://raw.githubusercontent.com/mr258876/Project-Orgel/raw/main/PCB/Solder_Helper_PCB1_Orgel%20nRF51_2024-7-24.html

[zhihu_esp32_environment_url]:https://zhuanlan.zhihu.com/p/107804270
[randomnerdtutorials_esp32_environment_url]:https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

[mainframe_zh_url]:/pics/MainFrame_zh.jpg
[tomenu_zh_url]:/pics/ToMenu_zh.jpg
[menu_zh_url]:/pics/Menu_zh.jpg

[mainframe_en_url]:/pics/MainFrame_en.jpg
[tomenu_en_url]:/pics/ToMenu_en.jpg
[menu_en_url]:/pics/Menu_en.jpg
