# Project Orgel
### 赛博音乐盒计划第一部分
### Cyber Musicbox Project Part I

- [中文](#中文)
- [English](#english)

# 中文
>## 目录
- [项目状态](#项目状态)
- [配件](#配件)
- [某个简短的安装指南](#某个简短的安装指南)
    - [传动改造](#传动改造)
    - [八音盒及电机的固定](#八音盒及电机的固定)
    - [电路搭建](#电路搭建)
    - [控制程序烧录](#控制程序烧录)
- [使用指南](#使用指南)

>## 项目状态
* 基础原理验证 ✔
* 基础 UI ✔
* 更多可调节项目 ✔
* 电流自动优化 ❌
* UI 多语言支持 ❌
* 项目自述 🚧

>## 配件
* 八音盒 (废话) *1
* ESP32-D0DWQ6 开发板 30针 *1
* TMC2209 步进电机驱动模块 *1
* 42BYGH40/39 步进电机 *1  
 (可以是任意两相四线步进电机, 但其应能够提供足够力矩(>=300mN\*m).)
* 0.4模齿轮(60齿以上，120齿左右？) *1   
* 旋转编码器 *1
* SSD1306 0.96 寸 OLED 模块 *1
* 电源 (Plan A): USB-C PD 诱骗器 *1, 支持快充的手机充电器 *1, MP1584 DC-DC 降压模块 *1
* 电源 (Plan B): 3.3/5/12v 多路输出电源模块 *1, 12v/2A 电源适配器 *1
* 用于固定的M3螺丝、M3螺母若干

## 某个简短的安装指南
接下来的步骤组成了一个简短的安装指南。步骤供参考，可根据实际情况进行调整。
### 传动改造
如图所示，改装电动只需使用八音盒传动部分中的部分齿轮。由于避开了传动部分中的易损齿轮，对该齿轮损坏的八音盒进行改装不失为一个绝佳选择。

将八音盒原本用于连接手柄的传动齿轮拆下，以禁用手柄。

首先将八音盒手柄支架部分整体拆下。

随后使用尖嘴钳将齿轮支架稍稍掰弯以取出齿轮。

手柄也可以取下。

最后将支架装回八音盒。
### 八音盒及电机的固定
毫无疑问，电机需要与八音盒固定在一起以进行传动。该部分有较多方案可供选择，实际应用时可不必遵照。

需要注意的是，不论如何固定，电机齿轮必须尽量与八音盒齿轮紧密配合

考虑到八音盒可能需要一个共鸣腔，推荐将八音盒与电机固定在木盒中。如不考虑共鸣，或不方便对木盒进行钻孔/开槽，则也可固定在木块或其他材料上。此处以固定在木盒中为例。

由于42电机的体积较大，因此八音盒原配木盒大概率需要进行更换。目前市面上有多种尺寸木盒可供选择。此处示例中的木盒尺寸为 长20\*宽13.5*高9

将八音盒与电机放入盒中，对空间进行规划。用铅笔画出，随后钻孔/开槽，将八音盒与电机固定在木盒中。
### 电路搭建
本项目中的电路十分简单，如下图所示。

处于空间利用方面的考量，推荐使用PCB实现上图中电路。作者水平稀烂，只能画出一手烂板子。如果需要，请点击这里。

如果无法进行焊接，则可以考虑使用面包板完成接线。
### 控制程序烧录
进行改装的最后一步是将程序烧录至ESP32中。



## 使用指南
To be specified

# English
>## Table of Contents
- [Project Status](#project-ptatus)
- [Hardware Requirements](#hardware-requirements)
- [A Brief Installiation Guide](#a-brief-installiation-guide)
    - [Gear Modding](#gear-modding)
    - [Mounting](#mounting)
    - [Curcit](#circuit)
    - [Programming](#programming)
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
* 42BYGH40/39 Stepper *1  
 (Could be replaced with any 2-phase 4-wire step motor, however it should provide enough torque(>=300mN*m).)
* 0.4M gear(At least 60 teeth) *1   
* Rotatry Encoder *1
* SSD1306 0.96 inch OLED Screen *1
* Power Supply (Plan A): USB-C PD Trigger/Decoy *1, Phone charger with fast charging support *1, MP1584 DC-DC step-down moudle *1
* Power Supply (Plan B): 3.3/5/12v multi-output power moudle *1, 12v/2A AC/DC adapter *1
* M3 Screws & Nuts for Mounting

## A Brief Insalliation Guide
The following steps constitute a biref installiation guide, which you could refer to but don’t have to follow
### Gear Modding
blablabla
### Mounting
blablabla
### Circuit
blablabla
### Programming
blablabla

## Usage