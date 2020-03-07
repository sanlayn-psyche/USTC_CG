# 作业说明

## 0. 测试数据

### 非封闭网格（一条边界）

> [objs 文件格式](obj.md) 

- [Balls.obj](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara/mesh/Balls.obj) 
- [Bunny_head.obj](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara/mesh/Bunny_head.obj) 
- [Cat_head.obj](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara/mesh/Cat_head.obj) 
- [David328.mtl](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara/mesh/David328.mtl) 
- [David328.obj](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara/mesh/David328.obj) 
- [Nefertiti_face.obj](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara/mesh/Nefertiti_face.obj) 

### 图片

![https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/02_ImageWarping/test.png](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/02_ImageWarping/test.png)

下载链接：[USTC_CG_Data@master/Homeworks/02_ImageWarping/test.png](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/02_ImageWarping/test.png) 

## 1. 基础知识

### 3D 网格曲面

3D 网格曲面是二维流形曲面的离散

2D 三角网格的顶点映射到 3D 中

![image-20200308055839320](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308055839320.jpg)

### 顶点的连接关系

![image-20200308060001167](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308060001167.jpg)

### 存储数据结构：半边结构

![image-20200308060027277](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308060027277.jpg)

### 顶点的微分坐标

$$
\delta_i=v_i-\sum_{j\in N(i)}w_jv_j
$$
![image-20200308052934359](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308052934359.jpg)

所有顶点联立，得到整个网格的 Laplacian 方程 $AV=b$ 

权重选取方法

- Uniform weight (geometry oblivious): $w_j = 1$ 
- Cotangent weight (geometry aware): $w_j =  (\cot \alpha + \cot\beta)$ 
- Normalization: $\overline{w}_j=w_j/\sum_k w_k$ 

## 2. 极小曲面

### 定义

平均曲率处处为 0 的曲面

![image-20200308060338091](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308060338091.jpg)

### 曲线的极小曲面

插值给定空间边界曲线

![image-20200308060458907](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308060458907.jpg)

### 理论

平均曲率处处为 0，即
$$
H(v_i)=0,\forall i
$$
又

![image-20200308061030193](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308061030193.jpg)
$$
\lim_{len(y)\to 0}\frac{1}{len(\gamma)}\int_{v\in \gamma}(v_i-v)\mathrm{d}s=H(v_i)\pmb{n}_i
$$
则微分坐标
$$
\delta_i=v_i-\frac{1}{d_i}\sum_{v\in N(i)}(v_i-v)=\frac{1}{d_i}\sum_{v\in N(i)}(v_i-v)=0
$$

### 计算方法

固定边界，微分坐标 = 0，将所有顶点的方程联立一起求解

![image-20200308061223252](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308061223252.jpg)

### 操作步骤

- 检测边界
- 固定边界
- 构建稀疏方程组
- 求解稀疏方程组
- 更新顶点坐标

> 高亏格曲面？
>
> ![image-20200308061348293](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308061348293.jpg)

## 3. 网格参数化

### 曲面展开

![image-20200308061556138](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308061556138.jpg)

### 纹理映射

![image-20200308053734074](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308053734074.jpg)

### 线性方法 Linear method[^Floater97] 

将边界固定到单位圆或单位正方形上

![image-20200308054033382](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308054033382.jpg)

### 2D Barycentric Embeddings

将 2D 边界固定到凸多边形上

![image-20200308061921615](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308061921615.jpg)

定义嵌入（embedding）如下
$$
Wx=b_x\\
Wy=b_y
$$
其中
$$
w_{ij}=\left\{\begin{array}{l}
<0 & (i,j)\in E\\
-\sum_{j\neq i} w_{ij} & (i,i)\\
0 & \text{otherwise}
\end{array}
\right.
$$
因此 $W$ 是对称矩阵，权重 $w_{ij}$ 控制了参数化形状

> **原理** 
>
> 定理 [Tutte, 63] [Maxwell, 1864]
>
> if $G=(V,E)$ is a 3-connected plarnar graph (triangular mesh), then any barycentric embedding provides a valid parameterization
>
> ---
>
> **示例** 
>
> ![image-20200308062006721](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308062006721.jpg)

### 参数化方法 [^Floater97] 

- Uniform weight (geometry oblivious): $w_j = 1$ 
- Cotangent weight (geometry aware): $w_j =  (\cot \alpha + \cot\beta)$ 
- shape preserving parametrization

如何判断哪个参数化方法更好？

### 示例

![image-20200308062240566](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308062240566.jpg)

![image-20200308062257708](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308062257708.jpg)

![image-20200308062312949](https://cdn.jsdelivr.net/gh/Ubpa/USTC_CG_Data@master/Homeworks/04_MinSurf&MeshPara//image-20200308062312949.jpg)

### 操作步骤

- 检测边界
- 将边界映射到**正方形边界**或**圆边界** 
- 构建稀疏方程组
- 求解稀疏方程组
- 更新顶点坐标
- 连接**纹理图像**，更新显示

## 参考文献

[^Floater97]: Floater M S. [**Parametrization and smooth approximation of surface triangulations**](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.102.6676&rep=rep1&type=pdf)[J]. Computer aided geometric design, 1997, 14(3): 231-250.