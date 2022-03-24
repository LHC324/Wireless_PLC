产品概述
============

WLC-1210系列是一种可编程序逻辑控制器(Micro PLC)。它能够控制各种设备以满足自动化控制需求。
WLC-1210的用户程序中包括了位逻辑、计数器、定时器、复杂数学运算以及与其它智能模块通讯等指令内容，从而使它能够监视输入状态，改变输出状态以达到控制目的。紧凑的结构、灵活的配置和强 大的指令集使 **WLC-1210** 成为各种控制应用的理想解决方案。

.. figure:: ../source/picture/指示图.jpg
    :align: center
    :alt: NULL
    :scale: 80%

    图2.1.1  WLC-1210系列PLC的外部结构

WLC-1210的外部结构
++++++++++++++++++++++

WLC-1210将微处理器、集成电源、输入电路和输出电路集为一体，从而形成了一个功能强大的Micro PLC。参见图2.1.1。在下载了程序之后，WLC-1210将保留所需的逻辑，用于监控应用程序中的输入输出设备。

**1、输入端子**

输入端子是外部输入信号与PLC连接的接线端子，位于底部端盖下面。此外，外部端盖下面还有输入公共端子。输入端子工作电压为直流24V。


.. figure:: ../source/picture/输入端子.jpg
    :align: center
    :alt: NULL
    :scale: 10%

    图2.1.2  WLC-1210系列 PLC的输入端子


**2、输出端子**

输出端子是外部负载与PLC连接的接线端子，位于顶部端盖下面。此外，顶部端盖下面还有输出公共端子和PLC工作电源端子，电源为直流24V。

.. figure:: ../source/picture/输出端子.jpg
    :align: center
    :alt: NULL
    :scale: 10%

    图2.1.3  WLC-1210系列PLC的输出端子

    
**3、输入状态指示灯（LED）**

输入状态指示灯用于显示是否有输入控制信号接入PLC。当指示灯亮时，表示有控制信号接入PLC；当指示灯不亮时，表示没有控制信号接入PLC。

.. figure:: ../source/picture/输入状态指示灯.jpg
    :align: center
    :alt: NULL
    :scale: 30%

    图2.1.4  WLC-1210系列PLC的输入状态指示灯


**4、输出状态指示灯（LED）**

输出状态指示灯用于显示是否有输出信号驱动执行设备。当指示灯亮时，表示有输出信号驱动外部设备；当指示灯不亮时，表示没有输出信号驱动外部设备。

.. figure:: ../source/picture/输出状态指示灯.jpg
    :align: center
    :alt: NULL
    :scale: 30%

    图2.1.5  WLC-1210系列PLC的输出状态指示灯


**5、CPU状态指示灯（LED）**

CPU状态指示灯有RUN、STOP、ERROR三个，其中RUN、STOP指示灯用于显示当前工作状态。当RUN指示灯亮时，表示运行状态；当STOP指示灯亮时，表示停止状态；当ERROR指示灯亮时，表示系统故障，PLC停止工作。

.. figure:: ../source/picture/CPU状态指示灯.jpg
    :align: center
    :alt: NULL
    :scale: 30%

    图2.1.6  WLC-1210系列PLC的CPU状态指示灯


**6、扩展接口**

扩展接口包括485通信接口（485A,485B）、电压输出端口AVo（AVo:0-10V）、电流输出端口AIo（4-20mA）、两个输入VIN0、VIN2。

.. figure:: ../source/picture/扩展接口.jpg
    :align: center
    :alt: NULL
    :scale: 15%

    图2.1.7  WLC-1210系列PLC的扩展接口


**7、通信接口**

通信接口PORT0支持PPI、MODBUS通信协议，有自由方式通信能力，通过通信电缆实现PLC与编程器之间、PLC与计算机之间、PLC与PLC之间、PLC与其他设备之间的通信。

.. figure:: ../source/picture/通信接口.jpg
    :align: center
    :alt: NULL
    :scale: 30%

    图2.1.8  WLC-1210系列PLC的通信接口


WLC-1210的安装
++++++++++++++++++++++

可以在一个面板或标准DIN导轨上安装WLC-1210,WLC-1210可采用水平或垂直方式安装。

.. note:: 
    * WLC-1210 PLC是开放式控制器。它要求在外壳、机柜或电气控制室中安装WLC-1210。只有授权人员才能进入壳、机柜或电气控制室。
    * 不遵守这些安装要求会导致人员死亡或重伤，和/或损坏设备。
    * 当安装WLC-1210 PLC时始终遵守这些要求。
    
**1、将WLC-1210与热源、高电压和电子噪声隔开**

* 按照惯例,在安装元器件时，总是把产生高电压和高电子噪声设备与诸如WLC-1210这样的低压、逻辑型的设备分隔开。

* 在控制柜背板上安排WLC-1210时，应区分发热装置并把电子器件安排在控制柜中温度较低的区域内。电子器件在高温环境下工作会缩短其无故障时间。

* 还要考虑面板中设备的布线。避免将低压信号和通讯电缆与交流供电线和高能量、开关频率很高的直流线路布置在一个线槽中。

**2、先决条件**

* 在安装和拆卸任何电气设备之前，必须确认该设备的电源已断开。同样，也要确保与该设备关联的设备供电已被切断。

* 试图在带电情况下安装或拆卸WLC-1210及其相关设备有可能导致触电或者设备误动作。

**3、WLC-1210的外部结构与接线**

.. figure:: ../source/picture/外部结构与接线图.jpg
    :align: center
    :alt: NULL
    :scale: 60%

    图2.2.1  WLC-1210系列PLC的外部结构与接线图

图2.2.1是WLC-1210的外部接线图。在PLC编程中，外部接线图也是其重要的组成部分。

* ① 输入端子：WLC-1210共有12点输入，端子编号采用8进制。输入端子只有一组，I0.0-I1.3,其公共端为COM。输入端工作电压为直流24V。

.. figure:: ../source/picture/输入接线图.jpg
    :align: center
    :alt: NULL
    :scale: 50%

    图2.2.2  WLC-1210系列PLC的输入接线图


* ② 输出端子：WLC-1210共有10点输出，端子编号也采用8进制。输出端子共分为3组，Q0.0-Q0.2为第一组，公共端CM1；Q0.3-Q0.6为第二组，公共端CM2；Q0.7-Q1.1为第三组，公共端CM3。根据负载性质不同，其输出回路电源支持交流和直流。
  
.. figure:: ../source/picture/输出接线图.jpg
    :align: center
    :alt: NULL
    :scale: 50%

    图2.2.3  WLC-1210系列PLC的输出接线图


* ③ 扩展端口：扩展接口包括485通信接口（485A,485B）、电压输出端口AVo（AVo:0-10V）、电流输出端口AIo（4-20mA）、两个输入VIN0、VIN2。

.. figure:: ../source/picture/扩展端口接线图.jpg
    :align: center
    :alt: NULL
    :scale: 45%

    图2.2.4  WLC-1210系列PLC的扩展端口接线图 

* ④ 电源接线：24V直流电源接入。

.. figure:: ../source/picture/电源接线图.jpg
    :align: center
    :alt: NULL
    :scale: 50%

    图2.2.5  WLC-1210系列PLC的电源接线图



WLC-1210的软件使用说明
++++++++++++++++++++++

WLC-1210是全兼容西门子S7-200系列CPU224XP的物联网PLC，使用STEP7--Micro/WIN编程软件。PLC类型选择CPU 224XP，如下图所示。

.. figure:: ../source/picture/STEP7选择PLC类型.jpg
    :align: center
    :alt: NULL
    :scale: 55%

    图2.2.6  STEP7--Micro/WIN 选择PLC类型


其余详细内容，请参考西门子S7-200编程手册。