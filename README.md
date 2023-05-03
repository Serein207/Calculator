# Calculator
基于QT C++实现的计算器，功能近似于Windows标准计算器

.exe文件位于Calculator-Release中，请务必将此文件夹全部下载解压后运行

---

## v1.1

除以0和对0取模后计算结果为 `inf`

## v1.2

优化 `CE` 逻辑  
按下 `=` 后计算结果可继续参与运算

## v1.3

优化 `Del` 逻辑  
计算结果过大时显示 `MAX`  
计算结果为 `MAX` 或 `inf` 时变为0参与下次运算  
修复按下0时再按符号键会出现 `00` 的问题  
将 `+/-` 符号改为 `^` ，支持乘方运算
