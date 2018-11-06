#图像轮廓分析   


## 图像联通组件寻找     

图像联通组件是图像轮廓分析的基础步骤，就是通过扫描图像的每一个像素点，对于像素值相同的并且连通(八连通或四连通)分为相同的group，最终，给图像中的每个像素点加上一个label，并返回。  
对于一副有N个像素的图像来说，最大联通组件个数为`N/2`，就是相邻的每个像素都是一个独立的group，在OpenCV中，调用查找函数时，必须保证图像像素背景是黑色，前景像素是白色(二值图像)  

* 两步法  

    * 扫描像素   

        ![one](./ConnectedComponent/img/one.png)

        查看当前像素的左侧一个和上侧一个像素是否相同和连通，如果图像左侧像素和上侧像素出现分歧，优先选择左侧像素为等价类    

    * 合并等价类    

        ![two](./ConnectedComponent/img/two.png)



```C++
//输出的带标记图像
Mat labels = Mat::zeros(img.size(), CV_32S);
//第一个参数必须为二值图像，黑色背景,因为这里黑色背景的label值为0
//第三个参数表示在八连通域查找
//第四个参数表示输出labels图像的数据类型，默认为带符号整形CV_32S
int num_labels = connectedComponents(binary, labels, 8, CV_32S);
```  



![result](./ConnectedComponent/img/result.png)  

* 代码实现   

    [C++版本](./ConnectedComponent/ConnectedComponent.cpp)  
    [Python版本](./ConnectedComponent/ConnectedComponent.py)   

## 带统计信息的图像联通组件查找    

在上一节内容的基础上，多返回了关于联通组件的一些位置信息    
* 组件左上角点的坐标   
* 组件的面积大小  
* 组件外接矩形的尺寸  
* 组件的面积  
* 组件的中心点坐标    