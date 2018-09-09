## 像素归一化     

* 归一化函数   

    `normalize(src, dst, alpha, beta, norm_type)`      

* norm_type   

    归一化类型    
    
    * NORM_MINMAX    
    
        最大最小值归一化      

        使用公式：   

        $$
        \acute{X} = \frac{X - X_{min}}{X_{max} - X_{min}}
        $$         

    * NORM_INF     

        最大值归一化      

        使用公式：  

        $$
        \acute{X} = \frac{X}{X_{max}}
        $$     

    * NORM_L1     

        L1范数归一化     

    * NORM_L2    

        L2范数归一化      

* 代码实现      

    注意在进行像素计算时，需要先将像素数据类型转换为浮点型，在处理操作完成后，如果要显示像素，还要转换为整形来显示       

    [Python版本](./Normalize.py)   

