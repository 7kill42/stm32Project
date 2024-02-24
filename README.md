# 华为云物联网平台

## 1.设备信息

端口号：1883
域名：80acf24fac.st1.iotda-device.cn- north-4.myhuaweicloud.com
IP地址：117.78.5.125

## 2.创建产品

## 3.创建设备

{
    "device_id": "658a588316c4bf77631fde30_dev1",
    "secret": "11111111"
}

## 4.生成MQTT三元组（3.1.1版本）

 MQTT设备ID、密码、用户ID
ClientId ：658a588316c4bf77631fde30_dev1_0_0_2024011510
Username：658a588316c4bf77631fde30_dev1
Password：87b00f753d6f0c010a885c70e05634ddf4759575ebf610156906dee9ddc3da6e

## 5.设备上传属性数据

上报主题 和订阅云平台的消息

MQTT协议：订阅主题/上报主题

属性上报：$oc/devices/658a588316c4bf77631fde30_dev1/sys/properties/report
device_id 要自己填充
数据内容：
{"services":[{"service_id":"dev","properties":{"alarm":0,"smokeConcentration":34.2,"temperature":12.1,"humidity":12.2}}]}

订阅主题：订阅云平台下发的消息
$oc/devices/{device_id}/sys/messages/down
device_id 要自己填充

## 6.设备上云

先使用MQTT客户端模拟设备上云，实现数据上传
