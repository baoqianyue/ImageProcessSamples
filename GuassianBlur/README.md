## 高斯模糊     

使用公式：   

$$
G(x,y) = \frac{1}{2\Pi\sigma^2}e^{-\frac{x^2+y^2}{2\sigma^2}}
$$    

高斯滤波后的每个像素都是相邻像素的加权平均值  

相比于线性平滑滤波，高斯模糊的卷积核采用高斯分布生成权重，高斯模糊考虑了相邻像素与原始中心像素之间距离对权值的影响，因而保留的细节信息更多.      

## 代码实现   

[C++版本](./GaussianBlur.cpp)   
    自定义高斯模糊，核大小为`5x5`,并对图像边界进行了填充       

[Python版本](./GaussianBlur.py)        


## 参考    

[高斯模糊中半径的解释](http://www.cnblogs.com/hoodlum1980/archive/2008/03/03/1088567.html)      

[阮一峰的网络日志-高斯模糊的算法](http://www.ruanyifeng.com/blog/2012/11/gaussian_blur.html)

