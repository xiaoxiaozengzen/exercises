# Overview

`algorithm`收集了一些列针对`range`数据的操作

`range`数据是访问一堆数据的迭代器或者指针，列入array或者其他STL容器。这些操作只会作用域迭代器指向的元素本身，而不会调用元素所在容器中的其他操作(例如，resize，reserve等)