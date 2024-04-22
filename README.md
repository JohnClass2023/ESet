# Project4: ESet

**Deadline: 2024/5/19 23:59**

## Background

`std::set` 固然好用，但它实在是太慢了！！

本次大作业中，我们想实现一个和它功能类似的数据结构，但更快、更好。我们还想探究 `std::set` 慢的原因。

本次大作业旨在练习动态查找表（跳表、AVL树、红黑树、无旋treap等）的实现和性能调优。

## Goal

#### 1. 成为set!

你需要start from scratch，实现一个 `template<class Key,class Compare = std::less<Key>>` 的 class，名为`ESet`。

`ESet` 拥有迭代器 `iterator`。在`ESet`中插入元素，之前老迭代器不会失效；删除时，指向删除点位置的迭代器失效，但是其他迭代器不会失效。Set的`iterator`本身不支持修改值，实质与`const_iterator`无异。

> **Aside：对于其它容器（比如双向链表），同时实现`iterator`和`const_iterator`的最佳方式是使用继承，而非复制一遍代码。**
>
> 比如，`std::vector`的迭代器实现是：
>
> ```c++
> typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
> typedef __gnu_cxx::__normal_iterator<const_pointer, vector> const_iterator;
> typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
> typedef std::reverse_iterator<iterator>		reverse_iterator;
> ```



为了减少本次大作业的workload，我们只需要ESet支持以下操作。如果你对操作细节有疑问，请参考 `std::set` 的相关功能。

- ```C++
  ESet();
  ~ESet();
  ```

  构造和析构函数。最高可接受复杂度 $O(1)$ 。

  

- ```c++
  template< class... Args >
  std::pair<iterator, bool> emplace( Args&&... args ); 
  ```

  将一个元素args放入ESet中。如已有该元素，则不插入。返回值第一维是对应位置的迭代器，第二维表示ESet是否真正发生过改变。最高可接受复杂度 $O(k\log n)$ ，其中`k`为参数的个数。

  > Note：在std::set中，使用emplace而非insert可以避免不必要的copy或move操作。
  >
  > 请注意，虽然函数原型是可变长参数，但你只需要处理emplace一个元素的情况即可。如传入多个元素，期望结果是编译错误（实际行为可以任选）。



- 	```c++
	size_t erase( const Key& key );
	```

  将key从ESet中删除。返回值为`ESet`中是否有key（0或1）。最高可接受复杂度 $O(\log n)$ 。

  

- ```c++
  iterator find( const Key& key );
  const_iterator find( const Key& key ) const;
  ```
  
  找到Key对应位置的iterator并返回。如果当前ESet是`const`的，返回的iterator也应是`const`的。如果没找到该元素，返回`end()`。最高可接受复杂度 $O(\log n)$ 。
  
  
  
- ```C++
  ESet( const ESet& other );
  ESet& operator=( const ESet& other );
  ```

​		复制一个ESet到另一个。复制之后两个ESet应该是分离的，即对其中一个的操作不会影响另一个。最高可接受复杂度 $O(n)$ 。



- ```c++
  ESet( ESet&& other );
  ESet& operator=( ESet&& other ) noexcept;
  ```
  
  移动一个ESet到另一个。移动之后不应该有新增的空间，other应当被销毁。最高可接受复杂度 $O(n)$ 。
  
  
  
- ```c++
  size_t range( const Key& l, const Key& r );
  ```

  返回[l,r]内元素的个数。若l>r，返回0。最高可接受复杂度 $O(\log n)$ 。

  
  
- ```c++
  size_t size() const noexcept;
  ```

  返回当前`ESet`总元素个数。最高可接受复杂度 $O(1)$ 。
  
  
  
- ```c++
  iterator lower_bound( const Key& key );
  iterator upper_bound( const Key& key );
  ```
  
  根据上/下界二分查找，返回对应位置的迭代器，期望功能同`lower_bound`和`upper_bound`的常规含义。最高可接受复杂度 $O(\log n)$ 。

  

- ```c++
  iterator begin() noexcept;
  iterator end() noexcept;
  ```
  
  首/尾迭代器。最高可接受复杂度 $O(1)$ 。



- ```C++
  *it; ++it; --it; it++; it--; it1!=it2; it1==it2;
  ```

	迭代器取值（返回值需要是`const`）、加减、比较。如果迭代器已经是`end()`，`(*it)`应当throw，++应当什么都不做；如果迭代器已经是`begin()`，--应当什么都不做。最高可接受复杂度 $O(\log n)$ 。

------

完成本任务后，你可以将`src.hpp`提交在ACMOJ的`ESet-Basic`上评测（github上也提供了测试点的子集）。评测点的数据规模是：

| 总操作数 N ~ 100000 |         |       |      |              |       |          |
| ------------------- | ------- | ----- | ---- | ------------ | ----- | -------- |
| 操作                | emplace | erase | find | `=` operator | range | it相关   |
| 个数约              | N/2     | N/6   | N/9  | 25           | N/18  | 剩余所有 |

作为一个鲁棒的数据结构，你不能提前假设N的大小，即不能使用静态数组。



#### 2. 嘲讽set！

众所周知，`std::set`底层使用红黑树实现。其它数据结构会比红黑树快吗？

现在，请你**完成红黑树的复现之后，另外使用2种方法重做任务一**。请自行构造调用程序，分别比较以上各操作的性能开销，并与原版`std::set`比较，以文档形式提交。你可以关注**每种操作的平均时长**、**每种操作的次数**、**调整平衡的次数**等数据，以探究哪种数据结构实现set是最优的。你可以考虑的数据结构有：

- 跳表
- AVL树
- B+树（内存层面）
- 无旋treap
- 其它平衡树
- ...

你能发现原版`std::set`的瓶颈，做到比它更好吗？



#### 3. 超越set！

现在，考虑set是一个用户数据库系统，我们需要高频对它做备份和fork操作。于是，我们希望`=`运算符（拷贝构造、移动构造）的复杂度为 $\textbf{O(1)}$ 。

>  ”啊？！这怎么可能？！“

实际上，`=`操作符本应该做的事情被均摊到`emplace`和`erase`里面去了。

> （纳尼？这样的话跑任务1岂不是会变慢？！你可以在完成本任务后对比一下）

请查阅*可持久化数据结构*相关的信息。

完成本任务后，你可以将代码提交在ACMOJ的`ESet-Speedtest`上评测。评测点的数据规模是：

| 总操作数 N ~ 5000000 |         |       |      |              |       |          |
| -------------------- | ------- | ----- | ---- | ------------ | ----- | -------- |
| 操作                 | emplace | erase | find | `=` operator | range | it相关   |
| 个数约               | N/2     | N/6   | N/9  | N/100        | N/18  | 剩余所有 |

OJ上对于本任务的时限较严。请找出一种最优的数据结构，想办法让你的代码跑得尽可能快！

`ESet-Speedtest` 是传统题目，需要有main函数。它的输入/输出格式请参考test/1.in和test/1.out。为加快速度，你可以不用1.cpp，而是重写它；或是定制你的`ESet` class。但是，请注意，作为一个鲁棒的数据结构，你不能提前假设N的大小，即不能使用静态数组。

speedtest通过即可得到相应的分数；前5名将会有图书奖品。

## Grading

- Task 1： 50%

- Task 2： 30%
  - Accuracy 15%
  - Report 15%
- Task 3： 10%
- QA&Code Review：10%

## Copyright

本次大作业参考了22级John班TA陆潇扬设计的ESet大作业，由23级John班TA汪畋宇重造。

本项目为23级John班数据结构课的第四个大作业，也可供后续John班参考使用。

