#include <exception>
#include <iostream>
#include <memory>
#include <queue>

/**
 * @brief 树
 * @note 树是一种非线性的数据结构，由节点（Node）和边（Edge）组成。树的特点包括：
 *   1. 根节点（Root Node）：树的顶端节点，没有父节点。
 *   2. 叶节点（Leaf Node）：没有子节点的节点。
 *   3. 父节点、子节点（Parent and Child Nodes）：节点之间的连接关系。
 *   4. 高度（Height）：树的最大深度。
 *   5. 深度（Depth）：节点到根节点的路径长度。
 *   6. 子树（Subtree）：节点及其所有后代节点组成的树。
 */

/**
 * @brief 二叉搜索树
 * @note
 *   1. 若任意节点的左子树不空，则左子树上所有结点的值均小于它的根结点的值。
 *   2. 任意节点的右子树不空，则右子树上所有结点的值均大于它的根结点的值。
 *   3. 任意节点的左、右子树也分别为二叉搜索树
 *   4. 没有键值相等的节点（no duplicate nodes）。
 */

/**
 * @brief 红黑树，是一种自平衡的二叉搜索树
 * @note
 *  1. 每个节点要么是红色，要么是黑色。
 *  2. 根节点是黑色。
 *  3. 每个叶节点（NIL节点，空节点）是黑色，实际中通常用nullptr表示。
 *  4. 如果一个节点是红色的，则它的两个子节点都是黑色的（即不能有两个连续的红色节点）。
 *  5. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。
 * 
 * @note 红黑树跟二叉搜索树类似，只是每个节点额外存储了一个颜色属性（红色或黑色）
 * @note 插入和删除时，会通过旋转和重新着色来保持树的平衡。
 */


/**
 * @brief 二叉树节点
 */
template <typename T>
struct BSTNode {
  T data;                                 //数据域
  BSTNode<T>*left, *right;                //左子树、右子树
  BSTNode() : left(NULL), right(NULL) {}  //构造函数
  BSTNode(const T d, BSTNode<T>* L = NULL, BSTNode<T>* R = NULL) : data(d), left(L), right(R) {}
};

template <typename T>
class BST {
 public:
  //普通构造函数
  BST() : root(NULL) {}
  //析构
  ~BST() { Destroy(root); }
  //插入
  bool Insert(T x) { return Insert(x, root); }
  //删除
  bool Earse(T x) { return Earse(x, root); }
  //搜索
  bool Find(T x) { return (Find(x, root) != NULL) ? true : false; }
  //中序遍历
  void InOrder() { InOrder(root); }
  //前序遍历
  void Precedence() { Precedence(root); }
  //后序遍历
  void PostOrder() { PostOrder(root); }
  // 层次遍历
  void LevelOrder() { LevelOrder(root); }

 protected:
  /**
      为了向二叉搜索树中插入一个新元素，必须先检查这个元素是否在树中已经存在。
      所以在插入之前，先使用搜索算法在树中检查要插入元素有还是没有:
          如果搜索成功，说明树中已经有这个元素，不再插入；
          如果搜索不成功，说明树中原来没有关键码等于给定值的结点，把新元素加到搜索操作停止的地方。
      当ptr != NULL时，它一定指向一棵子树的根，可用它所包含的关键码与给定值比较继续搜索插入位置；
      如果
     ptr=NULL，一定是递归到空树的位置，此时将创建的新结点地址送给ptr，因为ptr是引用，新结点的地址自然送入上述某一个指针域，自动将新结点作为叶结点链入二叉搜索树中了。
      每次结点的插入，都要从根结点出发搜索插入位置，然后把新结点作为叶结点插入。这样不需移动结点，只需修改某个已有树中结点的一个空指针即可。
   */
  bool Insert(const T& e1, BSTNode<T>*& ptr)  //第二个参数是指针的引用
  {
    if (ptr == NULL) {
      ptr = new BSTNode<T>(e1);  //构造新结点
      if (ptr == NULL) {
        throw std::runtime_error("Memory allocation failure");
      }
      return true;
    } else if (e1 < ptr->data)  //小于，插入左子树
    {
    } else if (e1 > ptr->data)  //大于，插入右子树
    {
      Insert(e1, ptr->right);
    } else  // x已在树中，不插入
    {
      return false;
    }

    return false;
  }

  BSTNode<T>* Find(const T& e1, BSTNode<T>* ptr)  //查找
  {
    if (ptr == NULL) {
      return NULL;
    }

    if (e1 < ptr->data) {
      return Find(e1, ptr->left);
    } else if (e1 > ptr->data) {
      return Find(e1, ptr->right);
    } else {
      return ptr;
    }
  }

  /**
      如果想要删除叶结点，只需将其父结点指向它的指针清零，再释放它即可。
      1.如果被删结点右子树为空，可以拿它的左子女结点顶替它的位置，再释放它。
      2.如果被删结点左子树为空，可以拿它的右子女结点顶替它的位置，再释放它。
      3.如果被删结点左、右子树都不空，可以在它的右子树中寻找中序下的第一个结点（关键码最小），用它的值填补到被删结点中，再来处理这个结点的删除问题，
      这是一个递归处理。
      例如，在上图中想要删除关键码为 78
     的结点，它的左、右子树都不空。在它的右子树中找中序下的第一个结点，其关键码为
     81。把它的值填补到被删结点中去， 下面的问题就是删除关键码为 81
     的结点了。这个结点左子树为空，用它的右子女（关键码为 88）代替它的位置就可以了。
   */
  bool Earse(const T e, BSTNode<T>*& ptr)  //删除
  {
    BSTNode<T>* temp = nullptr;
    if (ptr == NULL) {
      return false;
    } else {
      if (e < ptr->data) {
        Earse(e, ptr->left);
      } else if (e > ptr->data) {
        Earse(e, ptr->right);
      } else if (ptr->left != nullptr &&
                 ptr->right != nullptr) {  // 1.要删除的结点ptr同时有左右子树
        temp = ptr->right;                 //在右子树中搜索中序下的第一个结点
        while (temp->left != NULL) {
          temp = temp->left;
        }
        //用右子树中序下的第一个结点的值填充要删除的结点
        ptr->data = temp->data;
        //然后再新填充值ptr的右子树中删除temp的data值
        Earse(ptr->data, ptr->right);
      } else {
        temp = ptr;             // temp记住要删除的ptr结点
        if (ptr->left == NULL)  //只有右子树
        {
          ptr = ptr->right;
        } else  //只有左子树
        {
          ptr = ptr->left;
        }
        delete temp;  //删除结点
        temp = NULL;
        return true;
      }

      return false;
    }
  }

  // 中序遍历:左子树---> 根结点 ---> 右子树

  void InOrder(BSTNode<T>* root) {
    if (root != NULL) {
      InOrder(root->left);
      std::cout << root->data << " ";
      InOrder(root->right);
    }
  }

  // 前序遍历:根结点 ---> 左子树 ---> 右子树
  void Precedence(BSTNode<T>* root) {
    if (root != NULL) {
      std::cout << root->data << " ";
      Precedence(root->left);
      Precedence(root->right);
    }
  }

  // 后序遍历:左子树 ---> 右子树 ---> 根结点
  void PostOrder(BSTNode<T>* root) {
    if (root != NULL) {
      PostOrder(root->left);
      PostOrder(root->right);
      std::cout << root->data << " ";
    }
  }

  void LevelOrder(BSTNode<T>* root) {
    if (root == NULL) {
      return;
    }
    std::queue<BSTNode<T>*> q;
    q.push(root);
    while (!q.empty()) {
      int size = q.size();
      for (int i = 0; i < size; ++i) {
        auto t = q.front();
        q.pop();
        if (t->left) {
          q.push(t->left);
        }

        if (t->right) {
          q.push(t->right);
        }

        std::cout << t->data << " ";
      }
    }
  }

  //销毁以root为根的二叉树搜索树函数
  void Destroy(BSTNode<T>*& root) {
    if (root == NULL) {
      return;
    }
    if (root->left != NULL) {
      Destroy(root->left);
    }
    if (root->right != NULL) {
      Destroy(root->right);
    }
    delete root;
    root = NULL;
  }

 private:
  BSTNode<T>* root;  //根结点
};

int main() {
  BST<int> bst;
  bst.Insert(1);
  bst.Insert(2);
  bst.Insert(3);
  bst.Insert(4);
  bst.Insert(5);
  bst.Insert(6);
  bst.Insert(7);
  bst.Insert(8);
  bst.Insert(9);
  bool ret = bst.Insert(6);
  if (ret) {
    std::cout << "insert 6 success" << std::endl;
  } else {
    std::cout << "insert 6 failed" << std::endl;
  }

  bool ret2 = bst.Find(6);
  if (ret2) {
    std::cout << "find 6 success" << std::endl;
  } else {
    std::cout << "find 6 failed" << std::endl;
  }

  bool ret3 = bst.Find(7);
  if (ret3) {
    std::cout << "find 7 success" << std::endl;
  } else {
    std::cout << "find 7 failed" << std::endl;
  }

  bool ret4 = bst.Earse(9);
  if (ret4) {
    std::cout << "remove 9 success" << std::endl;
  } else {
    std::cout << "remove 9 failed" << std::endl;
  }

  bst.InOrder();
  std::cout << std::endl;
  bst.Precedence();
  std::cout << std::endl;
  bst.PostOrder();
  std::cout << std::endl;
  bst.LevelOrder();
  std::cout << std::endl;
}