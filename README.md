因为在学习过程中将PC更改为了ubuntu 但是因各种问题和操作失误
造成代码资料等丢失之后发现github可以方便的将在学习过程中的代码等可以对其保存
于是就创建了一个存储库将学习过程中的文档和源码放在github中


单源最短路径问题
实现邻接表的最短路径查找
Dijkstra算法实现
依据如果在地图中
有三个顶点ABC
其中A为源点 若A到B为最短 并且B到C也是最短
那么A到C为 最短路径为A ... B ... C
注意在地图中 并不是只有一条B 到C的路径所以需要不停的去匹配每个已经确定的最短路径
找到它们中的下一个最短路径直到找到C点
使用C语言 环境为gcc version 8.2.0 (Ubuntu 8.2.0-7ubuntu1) 

在代码注释中有很详细的注释

在windos环境下读取地图文件时会有读取格式不匹配的问题

