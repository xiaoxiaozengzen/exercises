#include <functional>
#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief 哈希表：一般也叫散列表，是一种基于数组实现的数据结构，通过哈希函数将键映射到数组的索引位置，从而实现高效的插入、删除和查找操作。
 * 
 * @note 哈希函数
 *        - 哈希函数是将输入（键）映射到固定大小的输出（哈希值或散列值）的函数。
 *        - 一个好的哈希函数应该具有均匀分布性，能够将不同的输入映射到不同的输出，从而减少冲突的发生。
 * @note 哈希冲突
 *        - 哈希冲突是指不同的键通过哈希函数映射到相同的索引位置。
 *        - 解决哈希冲突的常见方法包括链地址法（Chaining）和开放地址法（Open Addressing）。
 * @note 负载因子
 *        - 负载因子是哈希表中元素数量与哈希表大小的比值。
 *        - 负载因子过高会导致冲突增加，从而影响性能。通常，当负载因子超过某个阈值时，会进行扩容操作。
 * @note 扩容
 *        - 扩容是指增加哈希表的大小，以减少负载因子和冲突。
 *        - 扩容通常涉及重新计算所有现有元素的哈希值并将它们重新插入到新的哈希表中。
 */

template <class K, class V>
struct HashNode {
  std::pair<K, V> _kv;    // 键值对
  HashNode<K, V>* _next;  // 后继指针
  // 结点构造函数
  HashNode(const std::pair<K, V> kv) : _kv(kv), _next(nullptr) {}
};

template <class K, class V>
class HashTable {
  typedef HashNode<K, V> Node;

 public:
  // 查找函数
  HashNode<K, V>* Find(const K& key) {
    if (_table.size() == 0) {
      return nullptr;
    }

    std::size_t pos = key % _table.size();  // 得到下标值
    HashNode<K, V>* cur = _table[pos];      // 找到哈希桶首地址
    while (cur)                             // 遍历链表
    {
      if (cur->_kv.first == key) {
        return cur;
      }
      cur = cur->_next;
    }
    return nullptr;
  }

  // 插入函数
  bool Insert(const std::pair<K, V>& kv) {
    if (Find(kv.first) != nullptr)  // 元素已经存在
    {
      return false;
    }

    // 扩容操作
    if (_size == _table.size()) {
      size_t oldSize = _table.size();
      size_t newSize = oldSize == 0 ? 10 : 2 * oldSize;
      std::vector<Node*> newTable;               // 建立新表
      newTable.resize(newSize);                  // 扩容
      for (std::size_t i = 0; i < oldSize; i++)  // 转移数据
      {
        Node* cur = _table[i];  // 下标i对应的链表的首地址
        while (cur) {
          Node* next = cur->_next;

          std::size_t hashi = cur->_kv.first % newSize;  // 新下标值
          cur->_next = newTable[hashi];                  // 重新链接
          newTable[hashi] = cur;

          cur = next;  // 链表向后迭代
        }
        _table[i] = nullptr;
      }
      _table.swap(newTable);  // 替换新哈希表
    }

    // 头插元素
    size_t hashi = kv.first % _table.size();
    Node* newnode = new Node(kv);
    newnode->_next = _table[hashi];
    _table[hashi] = newnode;
    _size++;

    return true;
  }

  // 删除函数
  bool Erase(const K& key) {
    size_t pos = key % _table.size();  // 得到key值对应的哈希桶下标
    Node* prev = nullptr;
    Node* cur = _table[pos];
    while (cur) {
      if (cur->_kv.first == key)  // 找到和key值对应的结点
      {
        if (prev == nullptr)  // 找到的结点在链表首部
        {
          _table[pos] = cur->_next;  // 直接将头部往后移动一个单位
        } else                       // 找到的结点不在链表首部
        {
          prev->_next = cur->_next;  // 直接跳过它即可
        }

        delete cur;  // 释放结点资源
        _size--;     // 更新计数器
        return true;
      }
      prev = cur;  // 迭代
      cur = cur->_next;
    }
    return false;
  }

 private:
  std::vector<Node*> _table;
  std::size_t _size = 0;
};

int main() {
  std::hash<std::string> hash_fn;
  std::cout << hash_fn("Hello, World!") << std::endl;
  return 0;
}