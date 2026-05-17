#include <iostream>


/**
 * 链表：
 * 1. 节点：链表由节点组成，每个节点包含数据和指向下一个节点的指针。(如果是双向链表，还包含指向前一个节点的指针)
 * 2. head：链表的起始节点，通常称为head。
 * 3. tail：链表的末尾节点，通常称为tail。
 */
struct ListNode {
    int value;
    ListNode* next;

    ListNode(int val) : value(val), next(nullptr) {}
    ListNode(int val, ListNode* nextNode) : value(val), next(nextNode) {}
    ListNode() : value(0), next(nullptr) {}
};

void push_front(ListNode*& head, int value) {
    head = new ListNode(value, head);
}

void push_back(ListNode*& head, int value) {
    ListNode* new_node = new ListNode(value);
    if (head == nullptr) {
        head = new_node;
        return;
    }

    ListNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    
    current->next = new_node;
}

ListNode* find_node(ListNode* head, int target) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->value == target) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

bool erase_node(ListNode*& head, int target) {
    if (head == nullptr) {
        return false;
    }

    if (head->value == target) {
        ListNode* old_head = head;
        head = head->next;
        delete old_head;
        return true;
    }

    ListNode* current = head;
    while (current->next != nullptr) {
        if (current->next->value == target) {
            ListNode* node_to_delete = current->next;
            current->next = node_to_delete->next;
            delete node_to_delete;
            return true;
        }
        current = current->next;
    }

    return false;
}

void print_list(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->value;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << " -> nullptr" << std::endl;
}

void clear_list(ListNode*& head) {
    while (head != nullptr) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

void normal_operation() {
    ListNode* head = nullptr;

    std::cout << "1. 创建空链表: ";
    print_list(head);

    push_back(head, 10);
    push_back(head, 20);
    push_back(head, 30);
    std::cout << "2. 尾插 10, 20, 30: ";
    print_list(head);

    push_front(head, 5);
    std::cout << "3. 头插 5: ";
    print_list(head);

    ListNode* found = find_node(head, 20);
    std::cout << "4. 查找 20: "
              << (found != nullptr ? "找到了该节点" : "未找到该节点")
              << std::endl;

    bool erased = erase_node(head, 20);
    std::cout << "5. 删除 20: "
              << (erased ? "删除成功, 当前链表: " : "删除失败, 当前链表: ");
    print_list(head);

    clear_list(head);
    std::cout << "6. 释放链表: ";
    print_list(head);
}


int main() {
    std::cout << "===================== Normal Operation =====================" << std::endl;
    normal_operation();

    return 0;
}