## 图像卷积操作         

使用公式：   

$$
w(x,y) \bigstar f(x,y) = \sum_{s=-a}^a\sum_{t=-b}^bw(s,t)f(x-s,y-t)   
$$

滤波器w(x,y)的大小为`mxn`,`a = (m-1)/2`,`b = (n-1)/2`   

这里`w`代表卷积模板,`f`代表原图像    

* 自定义卷积     

    卷积模板为全一，在卷积后，进行了平均操作，相当于一个**平滑线性滤波器**        

* 滤波函数    

    `blur(src, ksize=(15, 15), anchor=(-1, -1), borderType=4)`   

    * ksize   
     
        指定卷积模板的大小   
    
    * anchor     

        指定核的中心锚点     

    * borderType     

        边界填充方式，4为默认方式补零         

## 代码实现        

[C++版本](./Blur.cpp)     
[Python版本](./Blur.py)   

