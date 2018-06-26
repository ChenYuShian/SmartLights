# 智慧燈具You and Me

## 隊伍：香港腳Virus

## **影片連結**

https://v.youku.com/v_show/id_XMzYxMDc2NTM2MA==.html?spm=a2hzp.8244740.0.0

## **Introduction**

顏色充斥著人類社會，而這些顏色對於人類的情緒是有一定程度的影響，人們可以隨意挑選自己當下喜歡的顏色增加生活品質。而最近另一個熱門的話題家庭自動化，可透過語音助理來達到遠端操控家中電器。我們最終目的是希望透過語音助理控制燈條顏色，我們使用三原色燈條、Amazon Echo Dot語音助理、Raspberry Pi控制板及這次比賽所用到的ARC開發板來模擬出智慧家庭的樣子。達到真正的家庭自動化，並增進人類生活品質。

## **System Architecture**

![image](https://github.com/ChenYuShian/SmartLightYouAndMe/blob/master/doc/pic/%E7%B3%BB%E7%B5%B1%E6%9E%B6%E6%A7%8B%E5%9C%96%20.png)


## **Appearance**
![image](https://github.com/ChenYuShian/SmartLightYouAndMe/blob/master/doc/pic/%E7%A1%AC%E9%AB%94%E6%9E%B6%E8%A8%AD%E5%9C%96.png)


## **軟體介紹**

##### **● AWS(Amazon Web Service)平台**
| File(s)  | Function  |
| :------------ |:---------------:|
| aws.js      | 接收ASK的Intent類別判斷結果並方送對應的HTTP Get Request給樹莓派。 |

##### **● Raspbeery Pi平台**
| File(s)  | Function  |
| :------------ |:---------------:|
| arcIOT.php    | 利用PHP的Get Function接收AWS的HTTP Request並將cgi參數解析傳給GPIO控制程式。 |
| arcIOT.c      | 實作底層GPIO傳送控制訊號給EMSK開發板。 |

##### **● EMSK開發板平台**
| File(s)  | Function  |
| :------------ |:---------------:|
| emsk_gpio.c    | 實作GPIO傳給RGB燈條。 |
