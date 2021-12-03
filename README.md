# Project Orgel
### 赛博音乐盒计划第一部分
### Cyber Musicbox Project Part I

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

>## 项目状态
* 基础原理验证 ✔
* 基础 UI ✔
* 更多可在UI中调节的值 ✔
* 电流自动优化 ❌
* UI 多语言支持 ❌
* 项目自述 🚧

>## 配件
* 八音盒 (废话) *1
* ESP32-D0DWQ6 开发板 30针 *1
* TMC2209 步进电机驱动模块 *1
>⚠注意：模块需要支持以串口方式与MCU进行通信
* 42BYGH40/39 步进电机 (高40/39mm) *1  
>ℹ注：可以是任意两相四线步进电机, 但其应能够提供足够力矩(>=300mN\*m)
* 42步进电机支架 (可选) *1
* 0.4模齿轮(60齿以上) *1
>ℹ注：齿轮越大越好，降低电机转速是减小噪音的有效方法
>⚠注意：齿轮需要能够与电机输出轴匹配
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

>⚠注意：在手摇八音盒中，手柄部分通常为噪音的源头之一。为了达到静音目的，断开手柄与其他齿轮间的传动是必要的。移除手柄或②号齿轮均可实现。图为移除了手柄及②号齿轮的八音盒。![handle_removed][handle_removed_url]
### 八音盒及电机的固定
毫无疑问，电机需要与八音盒固定在一起以进行传动。该部分有较多方案可供选择，故此处将不做较多阐述，实际应用时可不必遵照。

>⚠注意：不论以何种方式固定，**电机齿轮必须尽量与八音盒齿轮紧密配合**，否则可能会产生噪音并损坏齿轮。

考虑到八音盒可能需要一个共鸣腔，推荐将八音盒与电机固定在木盒中。如不考虑共鸣，或不方便对木盒进行钻孔/开槽，则也可固定在木块或其他材料上。此处以固定在木盒中为例。

由于42电机的体积较大，因此八音盒原配木盒大概率需要进行更换。目前市面上有多种尺寸木盒可供选择。此处示例中的木盒尺寸为 长20cm\*宽13.5cm*高9cm

将八音盒与电机放入盒中，对空间进行规划。用铅笔标记螺丝孔位及纸带入口/出口，随后钻孔/开槽，将八音盒与电机固定在木盒中。
### 电路搭建
本项目中的电路十分简单，如下图所示。

![curcit_schema][schema_url]

处于空间利用方面的考量，推荐使用PCB实现上图中电路。水平稀烂，只能画出一手烂板子。如有需要，请点击[这里][gerber_url]。
>ℹ注：仅适用于尺寸为22\*17的MP1584模块与焊接了TX,RX针脚的乐积TMC2209模块

如果无法进行焊接，则可以考虑使用面包板完成接线。
### 控制程序烧录
改装的最后一步是将电机控制程序烧录至ESP32中。

首先需要在电脑上搭建Arduino-ESP32环境。[知乎用户铁熊的文章][zhihu_esp32_environment_url]可供参考。

在环境搭建完成后，还需要在库管理器中安装以下库：
```
tcMenu
TMCStepper
U8g2
```
准备完成后，使用Arduino IDE打开`Project-Oegel`文件夹中的`Project-Orgel.ino`进行烧录。

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
 - Motor菜单
     - Direction: 控制电机正反转
     - Gear Teeth: 电机齿轮齿数设置
     - Current: 电机运行电流设置，单位mA 参考值：1050mA
    >⚠注意：随着电流的增大，驱动器会产生更多热量并可能导致过热保护，电机可能会产生更大噪音。正常使用请不要将该值提升至1700mA以上。

Have fun!

# English
>## Table of Contents
- [Project Status](#project-ptatus)
- [Hardware Requirements](#hardware-requirements)
- [A Brief Modding Guide](#a-brief-modding-guide)
    - [Gear Modding](#gear-modding)
    - [Mounting](#mounting)
    - [Curcit](#circuit)
    - [Uploading Code](#uploading-code)
- [Usage](#usage)

>## Project Status 
* Make it work  ✔
* A Basic UI    ✔
* More Adjustable Values in UI ✔
* Current Auto-Optimizing   ❌
* UI MultiLanguage Support  ❌
* Readme 🚧

>## Hardware Requirements
* Musicbox (of course) *1
* ESP32-D0DWQ6 Dev Moudle 30pin *1
* TMC2209 Stepper Driver Module *1
>⚠Caution: the driver moudlue should be able to communicate with the MCU through UART or Serial port.
* 42BYGH40/39 NEMA17 Stepper *1  
>ℹNote: Could be replaced with any 2-phase 4-wire step motor, however it should provide enough torque(>=300mN*m).
* NEMA17 Motor Stand (optional) *1
* 0.4M gear(At least 60 teeth) *1  
>ℹNote：It is a good idea to have a bigger gear, reducing the motor speed is an effective way to reduce noise.
>⚠Caution: The gear should be able to match the output shaft of the motor.
* Rotatry Encoder *1
* SSD1306 0.96 inch OLED Screen *1
* Power Supply (Plan A): USB-C PD Trigger/Decoy *1, Phone charger with fast charging support *1, MP1584 DC-DC step-down moudle *1
* Power Supply (Plan B): 3.3/5/12v multi-output power moudle *1, 12v/2A AC/DC adapter *1
* Box or something else for mounting musicbox and motor *1
* M3 Screws & Nuts for Mounting

## A Brief Modding Guide
The following steps constitute a biref installiation guide, which you could refer to but don’t have to follow
### Gear Modding
To be added
### Mounting
To be added
### Circuit
To be added
### Uploading Code
To be added

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
     - Direction: The running direction of the motor.
     - Gear Teeth: Teeth number of the gear installed on the motor. Related to running speed.
     - Current: The runing current of motor in mA. Reference value: 1050mA. 
    >⚠Caution：The Driver moudle would produce more heat as the current goes up, and might trigger overheat protection. The motor will produce more noise as well. Do not raise this value over 1700mA in normal use.

Have fun!

[before_modding_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/before_modding.jpg
[after_modding_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/after_modding.jpg
[handle_removed_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/handle_removed.jpg

[schema_url]:https://github.com/mr258876/Project-Orgel/raw/main/PCB/Schematic_Project%20Orgel_2021-11-29.png
[gerber_url]:https://github.com/mr258876/Project-Orgel/raw/main/PCB/Gerber_PCB_Project%20Orgel.zip

[zhihu_esp32_environment_url]:https://zhuanlan.zhihu.com/p/107804270
[randomnerdtutorials_esp32_environment_url]:https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

[mainframe_zh_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/MainFrame_zh.jpg
[tomenu_zh_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/ToMenu_zh.jpg
[menu_zh_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/Menu_zh.jpg

[mainframe_en_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/MainFrame_en.jpg
[tomenu_en_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/ToMenu_en.jpg
[menu_en_url]:https://github.com/mr258876/Project-Orgel/raw/main/pics/Menu_en.jpg
