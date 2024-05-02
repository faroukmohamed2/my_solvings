/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            if (!l1 && !l2)
        return nullptr;
    ListNode *cur2 = l2;
    ListNode *cur1 = l1;
    int value = 0, carry = 0;
    ListNode *t1 = l1;

    while (t1->next)
        t1 = t1->next;
    while (cur1 || cur2)
    {
        if (cur1)
        {
            if (!cur2)
                value = cur1->val + carry;
            else
                value = cur1->val + cur2->val + carry;
            carry = 0;
        }
        else if(cur2)
        {
            cur1 = new ListNode(0);
            t1->next = cur1;
            t1 = cur1;
            value = cur2->val + carry;
            carry = 0;
        }
        if (value >= 10) 
        {
            value -= 10;
            carry = 1;
        }
        if (cur1)
        cur1->val = value;
        cur1 = cur1->next;
        if (cur2)
            cur2 = cur2->next;
    }
    if (carry)
    {
        ListNode * last = new ListNode(carry);
        t1->next = last;
        t1 = last;
    }
    return l1;
    }
};