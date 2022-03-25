操作指南
============

上电开机
++++++++++

.. figure:: ../source/picture/01_开机界面.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.1.1 开机界面

在右上角接入 **24V** 直流电源后，``POWER`` 灯将会亮起，表示供电正常，您将会看到以上界面。

PLC运行参数配置
+++++++++++++++++

* 在对PLC进行编程之前，我们需要对PLC运行时一些必要的系统参数进行设置，设置步骤如下：

**1、进入菜单栏**

* ① 首先需要在开机界面按下 ``MENU`` 按钮进入密码输入界面。此时您需要判断是否设置过密码，如果设置过密码，则通过 ``DOWN`` （数字0-9递增） 和 ``UP`` （数字0-9递减）按钮输入4位密码。
* ② 值得注意的是，每输入一位密码我们都需要按下 ``MENU`` 按钮进行单位确认操作，否则操作可能无效，最后所有密码输入完毕后在按下 ``ENTER`` ,密码无误将会进入菜单界面。
* ③ 另外一种情况是用户如果是首次使用该设备，则不需要输入任何密码，直接在密码输入界面按下 ``ENTER`` 即可。
* ④ 如果您前期设置过密码，后面觉得不需要了，可以通过 菜单栏中的 ``恢复出厂设置`` 项解除密码。

.. figure:: ../source/picture/13_密码输入界面.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.2.1 密码输入界面

.. figure:: ../source/picture/02_主菜单1.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.2.2 菜单界面1

**2、设置PLC运行状态**

.. figure:: ../source/picture/06_PLC启动.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.3.1 PLC启动

* 在 **图 1.2.2 菜单界面1** 中选中 ``启停开关`` 后连续按下 **2** 次 ``ENTER`` 就会看到 **图 1.3.1 PLC启动** 界面，
  此时如果 ``RUN`` 灯亮起，则说明PLC启动成功，否则PLC ``故障``。

.. note:: 
    * PLC未能成功启动的原因可能如下：
    * ``RUN`` 指示灯故障，导致启动成功，但是状态指示灯没有亮起。
    * PLC程序块损坏，导致PLC无法切换至运行状态。
    * PLC的硬件启停线路损坏，无法正常启停。
    * PLC系统受不可抗拒因素造成损坏。

* 在 ``图 1.3.1 PLC启动`` 中再次按下 ``ENTER`` 则PLC处于停止状态。

.. figure:: ../source/picture/05_PLC停止.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.3.2 PLC停止

.. note::
    * PLC处于停止状态时，PLC的程序块可能不会正常工作！
    * 您在没有对PLC的 ``Port0`` 和 ``Port1`` 做其他通信初始化时，并且菜单项 ``通信协议`` 处于 ``PPI_P`` 时
      默认的 ``PPI`` 协议将不会受到影响，处于启用状态。

**3、设置通信方式**

在 **图 1.2.2 菜单界面1** 中选中 ``通信方式`` 后按下 ``ENTER`` 将会进入如下界面：

.. figure:: ../source/picture/07_通信方式_打开.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.4.1 打开无线模块

* **无线模块** 即我们内部的WIFI模块，默认该硬件模块处于启用状态。

.. note::
    * WIFI模块处于启用状态并且接入指定路由设备，连接至云端后，可以看到 ``NET`` 和 ``WAN`` 指示灯将会亮起。

在 **图 1.4.1 打开无线模块** 选择 ``关闭无线模块``， 则会得到如下界面：

.. figure:: ../source/picture/08_通信方式_关闭.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.4.2 关闭无线模块

.. note::
    * 关闭无线模块后，WIIF模块处于禁用状态，PLC的功耗将会降低，可以看到 ``NET`` 和 ``WAN`` 指示灯熄灭。


**4、设置工作模式**

工作模式主要针对的是在使用 **外部扩展口** 进行通讯时，实际的PLC硬件口 **PORT0** (内部网络)的工作模式。

.. csv-table:: 表1.1.1 PLC作为SAVLE
   :header: "请求对象", "工作模式", "响应对象", 默认波特率, 代号
   :widths: 10, 20, 20, 20, 20

   "WIFI", "分时复用", "PLC_Port0", 115200, "无线网"
   "LAN", "分时复用", "PLC_Port0", 115200, "以太网"
   "RS485", "分时复用", "PLC_Port0", 9600, "扩展网"

.. figure:: ../source/picture/09_工作模式_从机.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.5.1 PLC作Savle

.. csv-table:: 表1.1.2 PLC作为MASTER
   :header: "请求对象", "工作模式", "响应对象", 默认波特率, 代号
   :widths: 10, 20, 20, 20, 20

   "PLC_Port0", "分时复用", "WIFI", 115200, "内部网"
   "PLC_Port0", "分时复用", "LAN", 115200, "内部网"
   "PLC_Port0", "分时复用", "RS485", 9600, "扩展网"

.. figure:: ../source/picture/10_工作模式_主机.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.5.2 PLC作Mster

.. note::
    * 对于PLC作为 **Master** 时，目前对应关系仅开放了 **表1.1.2** 中第三种模式。

**5、设置通讯协议**

通讯协议主要针对的是在使用 **外部扩展口** 进行通讯时，扩展口默认走的是PLC的 **PPI协议**。

.. csv-table:: 表1.1.3 协议说明
   :header: "协议名", "参数", "说明"
   :widths: 10, 30, 20

   "PPI_P", "1 bit Start + 1 bit Stop + 8 bit data + 1 bit even", "PLC默认通讯协议"
   "other", "1 bit Start + 1 bit Stop + 8 bit data", "典型Modbus协议"

.. figure:: ../source/picture/11_扩展协议PPI.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.6.1 扩展协议PPI

.. figure:: ../source/picture/12_扩展协议other.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.6.2 扩展协议other

**6、密码修改设置**

密码修改界面，主要用于锁定参数设置菜单，在首次设置新密码或者二次修改密码时使用。


.. figure:: ../source/picture/14_密码修改界面1.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.7.1 密码修改界面

.. figure:: ../source/picture/15_密码输入界面2.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.7.2 新密码输入

.. figure:: ../source/picture/16_密码输入界面3.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.7.3 新密码确认

.. note::
    * 和输入密码界面操作一致，同样需要对输入的每位密码通过 ``MENU`` 进行确认，输入完毕后按下 ``ENTER`` 进行存储。

**7、波特率设置**

配合 **4、工作模式** 来使用，详细配置请看以上章节4。

.. figure:: ../source/picture/17_波特率设置1.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.8.1 波特率设置1

.. figure:: ../source/picture/18_波特率设置2.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.8.2 波特率设置2

.. figure:: ../source/picture/19_波特率设置3.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.8.3 波特率设置3


**8、本机热点设置**

本机热点主要表现的是每台PLC的WIFI模块对外发射的 **AP_ID**, 为每台PLC的唯一设备序列号标识。
通过Web端配网接口输入目标路由器账号和密码，就可以连接到云端与PLC进行数据交互。


.. figure:: ../source/picture/20_本机热点.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.9.1 本机热点设置

.. note::
    * ``热点`` 可以在配完网络后可以进行关闭，来降低设备功耗。

**9、恢复出厂设置**

恢复出厂设置，主要用于PLC配置参数错乱、遗忘或者PLC部分功能异常时来使用，可能会解决您的大部分问题。
在当前界面连续2次按下 ``ENTER`` 后将会触发功能。

.. figure:: ../source/picture/21_恢复出厂设置.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.10.1 恢复出厂设置

.. note::
    * 恢复出厂设置后，所有参数将会重置，包括但不限于：
    * ①PLC启停状态。
    * ②PLC通信方式。
    * ③PLC工作模式。
    * ④PLC扩展协议。
    * ⑤PLC用户密码。
    * ⑥PLC热点名称及用户自定义路由账号、密码。（云端账号和连接不会丢失）
  
**10、无线网络配置步骤**

* 首先打开需要连接无线网络的PLC，找到本机热点界面，查看本机的序列号标识。

.. figure:: ../source/picture/本机热点序列号识别.jpg
    :align: center
    :alt: NULL
    :scale: 30%
    
    图 1.11.1 本机热点序列号标识

* 其次用手机或有连接无线网功能的电脑连接对应本机热点，如下图 **PLC27_AP**:

.. figure:: ../source/picture/连接WIFI.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.11.2 连接WIFI

* 然后根据 **配网地址10.10.100.254/index_cn.html** ,使用电脑浏览器或手机浏览器访问此地址，默认登录密码如下图所示,用户名和密码皆为 **admin**

.. figure:: ../source/picture/默认登录密码.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.11.3 默认登录密码

* 最后进入配置界面后点击 **WIFI参数** (其它参数请勿修改，否则后果自负)，点击找到 **STA** 参数设置 ，点击 **搜索** 找到需要连接的网络名称，输入密码后点击保存，至此完成该台PLC网络配置。

.. figure:: ../source/picture/配置界面.jpg
    :align: center
    :alt: NULL
    :scale: 50%
    
    图 1.11.4 配置界面

