#include <iostream>
using namespace std;
template <typename Key> class RedBlackTree
{
  private:
    const static bool RED = true, BLACK = false;
    struct Node
    {
        int size, count;
        bool color;
        Key key;
        Node *father, *leftChild, *rightChild;
        inline Node(Key key)
        {
            this->key = key, size = 1, count = 1, color = RED;
            father = leftChild = rightChild = nullptr;
        }
        inline bool left()
        {
            Node *father = this->father;
            return this == father->leftChild;
        }
        inline bool right()
        {
            Node *father = this->father;
            return this == father->rightChild;
        }
        inline bool allLeft()
        {
            Node *father = this->father, *grandfather = father->father;
            return this == father->leftChild && father == grandfather->leftChild;
        }
        inline bool allRight()
        {
            Node *father = this->father, *grandfather = father->father;
            return this == father->rightChild && father == grandfather->rightChild;
        }
        inline Node *uncle()
        {
            Node *father = this->father, *grandfather = father->father;
            return father == grandfather->leftChild ? grandfather->rightChild : grandfather->leftChild;
        }
        inline Node *brother()
        {
            Node *father = this->father;
            return left() ? father->rightChild : father->leftChild;
        }
    };

  public:
    Node *root;
    inline void rotateLeft(Node *node)
    {
        Node *oldRightChild = node->rightChild, *oldFather = node->father;
        oldRightChild->size = node->size, node->size = node->count;
        node->rightChild = oldRightChild->leftChild, node->father = oldRightChild;
        oldRightChild->leftChild = node, oldRightChild->father = oldFather;
        if (node->leftChild != nullptr)
            node->size += node->leftChild->size;
        if (node->rightChild != nullptr)
            node->size += node->rightChild->size, node->rightChild->father = node;
        if (root == node)
            root = oldRightChild;
        else
        {
            if (node == oldFather->leftChild)
                oldFather->leftChild = oldRightChild;
            else
                oldFather->rightChild = oldRightChild;
        }
    }
    inline void rotateRight(Node *node)
    {
        Node *oldLeftChild = node->leftChild, *oldFather = node->father;
        oldLeftChild->size = node->size, node->size = node->count;
        node->leftChild = oldLeftChild->rightChild, node->father = oldLeftChild;
        oldLeftChild->rightChild = node, oldLeftChild->father = oldFather;
        if (node->leftChild != nullptr)
            node->size += node->leftChild->size, node->leftChild->father = node;
        if (node->rightChild != nullptr)
            node->size += node->rightChild->size;
        if (root == node)
            root = oldLeftChild;
        else
        {
            if (node == oldFather->leftChild)
                oldFather->leftChild = oldLeftChild;
            else
                oldFather->rightChild = oldLeftChild;
        }
    }
    inline void rotate(Node *node, bool condition)
    {
        if (condition)
            rotateLeft(node);
        else
            rotateRight(node);
    }

  public:
    RedBlackTree()
    {
        root = nullptr;
    }
    inline void insert(Key key)
    {
        Node *node = root, *father = nullptr, *grandfather = nullptr, *uncle = nullptr;
        while (node != nullptr && node->key != key)
            ++node->size, father = node, node = key < node->key ? node->leftChild : node->rightChild;
        if (node != nullptr)
            return ++node->count, ++node->size, void();
        node = new Node(key);
        if (father == nullptr)
            root = node;
        else
        {
            node->father = father;
            if (key < father->key)
                father->leftChild = node;
            else
                father->rightChild = node;
            for (bool temp; node != root && node->color == RED && node->father->color == RED;)
            {
                father = node->father, grandfather = father->father, uncle = node->uncle();
                if (uncle != nullptr && uncle->color == RED)
                    father->color = BLACK, uncle->color = BLACK, node = grandfather;
                else if (node->allLeft())
                    rotateRight(grandfather), father->color = BLACK, node = father;
                else if (node->allRight())
                    rotateLeft(grandfather), father->color = BLACK, node = father;
                else
                    temp = node->left(), rotate(father, !temp), rotate(grandfather, temp), node->color = BLACK;
                grandfather->color = RED;
            }
        }
        root->color = BLACK;
    }
    inline void erase(Key key)
    {
        Node *node = root, *oldNode = nullptr, *child = nullptr;
        while (node != nullptr && node->key != key)
            --node->size, node = key < node->key ? node->leftChild : node->rightChild;
        --node->size;
        if (--node->count)
            return;
        if (node->leftChild != nullptr && node->rightChild != nullptr)
        {
            for (oldNode = node, node = node->rightChild; node->leftChild != nullptr;)
                node = node->leftChild;
            oldNode->key = node->key, oldNode->count = node->count;
            for (Node *newNode = node; newNode != oldNode; newNode = newNode->father)
                newNode->size -= oldNode->count;
        }
        oldNode = node;
        if ((node->leftChild != nullptr || node->rightChild != nullptr) && node->color == BLACK)
        {
            if (node->leftChild != nullptr)
                node->leftChild->color = BLACK;
            else
                node->rightChild->color = BLACK;
            node->color = RED;
        }
        if (node->color == RED)
        {
            if (node->leftChild != nullptr)
                child = node->leftChild;
            else if (node->rightChild != nullptr)
                child = node->rightChild;
            if (child != nullptr)
                child->father = node->father;
        }
        else
        {
            Node *brother = nullptr, *closeNephew = nullptr, *distantNephew = nullptr;
            while (node != root)
            {
                brother = node->brother();
                closeNephew = node->left() ? brother->leftChild : brother->rightChild;
                distantNephew = node->left() ? brother->rightChild : brother->leftChild;
                if (brother->color == RED)
                    rotate(node->father, node->left()), brother->color = BLACK, node->father->color = RED;
                else if (distantNephew != nullptr && distantNephew->color == RED)
                {
                    rotate(node->father, node->left()), swap(brother->color, node->father->color),
                        distantNephew->color = BLACK;
                    break;
                }
                else if (closeNephew != nullptr && closeNephew->color == RED)
                    rotate(brother, !node->left()), brother->color = RED, closeNephew->color = BLACK;
                else
                {
                    brother->color = RED;
                    if (node->father->color == RED)
                    {
                        node->father->color = BLACK;
                        break;
                    }
                    else
                        node = node->father;
                }
            }
        }
        if (oldNode == root)
            root = child;
        else if (oldNode->left())
            oldNode->father->leftChild = child;
        else
            oldNode->father->rightChild = child;
        return delete (oldNode), void();
    }
    inline int queryRank(Key key)
    {
        int ans = 1;
        for (Node *node = root; node != nullptr;)
        {
            if (node->key == key)
            {
                ans += node->leftChild == nullptr ? 0 : node->leftChild->size;
                break;
            }
            else if (node->key > key)
                node = node->leftChild;
            else
                ans += (node->leftChild == nullptr ? 0 : node->leftChild->size) + node->count, node = node->rightChild;
        }
        return ans;
    }
    inline Key queryKth(int rank)
    {
        for (Node *node = root; node != nullptr;)
        {
            if (node->leftChild == nullptr)
            {
                if (rank <= node->count)
                    return node->key;
                else
                    rank -= node->count, node = node->rightChild;
            }
            else if (rank > node->leftChild->size && rank <= node->leftChild->size + node->count)
                return node->key;
            else if (rank <= node->leftChild->size)
                node = node->leftChild;
            else
                rank -= node->leftChild->size + node->count, node = node->rightChild;
        }
    }
    inline Key queryPrecursor(Key key)
    {
        Node *node = root, *father = nullptr;
        while (node != nullptr)
        {
            if (key <= node->key)
                node = node->leftChild;
            else
                father = node, node = node->rightChild;
        }
        return father->key;
    }
    inline Key querySuccessor(Key key)
    {
        Node *node = root, *father = nullptr;
        while (node != nullptr)
        {
            if (key < node->key)
                father = node, node = node->leftChild;
            else
                node = node->rightChild;
        }
        return father->key;
    }
};
inline int read()
{
    int ans = 0, tag = 0;
    char c = 0;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            tag = 1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        ans = (ans << 1) + (ans << 3) + c - '0', c = getchar();
    return tag ? -ans : ans;
}
inline void write(int x)
{
    int top = 0, num[16];
    if (x < 0)
        putchar('-'), x = -x;
    for (; x; x /= 10)
        num[++top] = x % 10;
    for (; top; --top)
        putchar(num[top] + '0');
    putchar('\n');
}
int n, x, ans = 0, last = 0, m;
RedBlackTree<int> rbt;
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        x = read();
        rbt.insert(x);
    }
    for (int i = 1, opt, v; i <= m; ++i)
    {
        opt = read(), v = read();
        v ^= last;
        if (opt == 1)
            rbt.insert(v);
        else if (opt == 2)
            rbt.erase(v);
        else if (opt == 3)
        {
            last = rbt.queryRank(v);
            ans ^= last;
        }
        else if (opt == 4)
        {
            last = rbt.queryKth(v);
            ans ^= last;
        }
        else if (opt == 5)
        {
            last = rbt.queryPrecursor(v);
            ans ^= last;
        }
        else
        {
            last = rbt.querySuccessor(v);
            ans ^= last;
        }
    }
    printf("%d",ans);
}
