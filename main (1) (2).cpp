#include <iostream>
using namespace std;

class Node
{
public:
     int data;
     Node *next;

public:
     Node(int num)
     {
          data = num;
          next = NULL;
     }
};

Node *buildList(int *nums, int count)
{
     Node *head = new Node(nums[0]);
     Node *tail = head;
     for (int i = 1; i < count; i++)
     {
          Node *newNode = new Node(nums[i]);
          tail->next = newNode;
          tail = newNode;
     }
     return head;
}

void printList(Node *ptr)
{
     if (ptr != NULL)
     {
          cout << ptr->data << " ";
          printList(ptr->next);
     }
     else
     {
          cout << endl;
     }
}

//;-----------------------
//; Write the DotProduct Function Here
//;-----------------------

int dotProduct(Node *ptr1, Node *ptr2)
{
     if (ptr1 == NULL || ptr2 == NULL)
          return 0;
          
     // in dot product, we keep multiplying elements
     // in order until we run out of elements.
     // also, we keep on sunming them.
     
     // this what's happening here as well.
     // we are first multiplying ptr1 and ptr2, then we
     // are adding them into whatever product we get from
     // remaining elements. this goes on until
     // the list is finished.
     return (ptr1->data * ptr2->data) + dotProduct(ptr1->next, ptr2->next);
}
//;-----------------------
//; Write the Duplicates Function Here
//;-----------------------

bool duplicatesRecursive(Node *ptr, int *visited, int visited_count)
{
     if (ptr == NULL)
          return false;
     
     // we keep a track of all the numbers we have seen
     // in the visited list.
     
     // we loop over the list and check whether we have
    // seen this specific number before. if yes, then it
    // means we have a duplicate.
     for (int i = 0; i < visited_count; i++)
     {
          if (ptr->data == visited[i])
          {
               return true;
          }
     }
     
     // if we don't find it in the visited list, we add the
     // number to the visited list.
     visited = (int *)realloc(visited, sizeof(int) * (visited_count + 1));
     visited[visited_count] = ptr->data;
     
     // now we make a recursive call to check the
    // remaining list.
     return duplicatesRecursive(ptr->next, visited, visited_count + 1);
}

bool duplicates(Node *ptr)
{
    // this is the wrapper function that calls our
    // recursive function.
    
    
     int *visited = nullptr; // keeps track of all # we have seen.
     int visited_count = 0;
     return duplicatesRecursive(ptr, visited, visited_count);
}

//;-----------------------
//; Write the MaxDistance Function Here
//;-----------------------

int singleMaxDistance(Node *ptr1, Node *ptr2)
{
     if (ptr2 == NULL)
          return 0;
     // this call calculates distance of a single node
     // from every node in list 2.
     
     // i.e. [1, 2, 3, 4...], [9, 10, 11...]
     // then singleMaxDistance(4, list2)
     // will give us the maximum distance of 4 with
     // any of the elements in list 2.
     return max(abs(ptr1->data - ptr2->data), singleMaxDistance(ptr1, ptr2->next));
}

int maxDistance(Node *ptr1, Node *ptr2, int maxSoFar = -1)
{
     if (ptr1 == NULL || ptr2 == NULL)
          return 0;
          
     // we just repeatedly call our singleMaxDistance
     // for every node in list1.
     // this basically works like two nested loops.
     return max(
         singleMaxDistance(ptr1, ptr2) > maxSoFar ? singleMaxDistance(ptr1, ptr2) : maxSoFar,
         maxDistance(ptr1->next, ptr2));
}

//;-----------------------
//; Extra Credit
//; Write a reverseList Function here
//; Add your own method calls to the end of the main method.
//;-----------------------

Node *reverseList(Node *ptr)
{
     if (ptr == NULL || ptr->next == NULL)
          return ptr;

     // one by one
     Node *newHead = reverseList(ptr->next);
     
     // first change the next node's next pointer
     ptr->next->next = ptr;
     
     // then change our next pointer
     ptr->next = NULL;
     
     // we do this for all nodes in the list through
     // recursion and ultimately we are left
     // with a list that is reversed 
     
     return newHead;
}

//;-----------------------
//; Extra Credit
//; Write a removeNum Function here
//; This removes all instances of `num` in the list
//; Add your own method calls to the end of the main method.
//;-----------------------

Node *removeNumRecursive(Node *ptr, int *visited, int visited_count)
{
     if (ptr == NULL)
          return NULL;
     for (int i = 0; i < visited_count; i++)
     {
          if (ptr->data == visited[i])
          {
              
              // this function is very similar to duplicates
              // but instead of returning true or false upon
             // finding a duplicate, we simply remove that
              // node.
              
              // to remove the current node, we copy the next
              // nodes data and remove the next node.
              
              // we do this because if we delete our current
              // node then the previous node wouldn't really
              // really know about it and program will crash.
               ptr->data = ptr->next->data;
               free(ptr->next);
               ptr->next = ptr->next->next;
          }
     }
     visited = (int *)realloc(visited, sizeof(int) * (visited_count + 1));
     visited[visited_count] = ptr->data;
     return removeNumRecursive(ptr->next, visited, visited_count + 1);
}

Node *removeNum(Node *ptr, int num)
{
     if (ptr == NULL)
          return NULL;
     int *visited = nullptr;
     int visited_count = 0;
     removeNumRecursive(ptr, visited, visited_count);
     return ptr;
}

//;-----------------------
//; Below are your test cases.
//;-----------------------

int main()
{
     Node *list1 = NULL;
     Node *list2 = NULL;
     cout << "Dot Product of two empty lists '() '()" << endl;
     cout << dotProduct(list1, list2) << endl
          << endl;
     int nums1[] = {1};
     int nums2[] = {4};
     list1 = buildList(nums1, 1);
     list2 = buildList(nums2, 1);
     cout << "Dot Product of single lists '(1) '(4)" << endl;
     cout << dotProduct(list1, list2) << endl
          << endl;
     int nums3[] = {8, -2, 4, 6};
     int nums4[] = {2, -12, -4, 7};
     list1 = buildList(nums3, 4); // ERROR: here it was buildList(nums3, 1)
     list2 = buildList(nums4, 4);
     cout << "Dot Product of longer lists '(8 -2 4 6) '(2 -12 -4 7)" << endl;
     cout << dotProduct(list1, list2) << endl
          << endl;

     cout << "Testing Duplicates Methods" << endl
          << endl;
     cout << "Duplicates of an empty lists? '()" << endl;
     list1 = NULL;
     cout << duplicates(list1) << endl
          << endl;

     cout << "Duplicates of a single list '(2)?" << endl
          << endl;
     int nums5[] = {2};
     list1 = buildList(nums5, 1);
     cout << duplicates(list1) << endl;

     cout << "Duplicates of the list '(82 62 42 92 32)?" << endl
          << endl;
     int nums6[] = {82, 62, 42, 92, 32}; // ERROR: here it was 82, 62, 42, 82, and 32.
     list1 = buildList(nums6, 5);
     cout << duplicates(list1) << endl
          << endl;

     cout << "Duplicates of the list '(82 62 42 82 32)?" << endl
          << endl;
     int nums7[] = {82, 62, 42, 82, 32};
     list1 = buildList(nums7, 5);
     cout << duplicates(list1) << endl
          << endl;

     cout << "Duplicates of the list '(82 62 42 32 32)?" << endl
          << endl;
     int nums8[] = {82, 62, 42, 32, 32};
     list1 = buildList(nums8, 5);
     cout << duplicates(list1) << endl
          << endl;

     cout << "Duplicates of the list '(32 62 42 32 12)?" << endl
          << endl;
     int nums9[] = {32, 62, 42, 32, 12};
     list1 = buildList(nums9, 5);
     cout << duplicates(list1) << endl
          << endl;

     cout << "Testing Max Distance Methods" << endl
          << endl;

     cout << "Max Distance of two empty lists '() '()" << endl
          << endl;
     list1 = NULL;
     list2 = NULL;
     cout << maxDistance(list1, list2) << endl
          << endl;

     int numsA[] = {2};
     int numsB[] = {8};
     list1 = buildList(numsA, 1);
     list2 = buildList(numsB, 1);
     cout << "Max Distance of two single lists '(2) '(8)" << endl
          << endl;
     cout << maxDistance(list1, list2) << endl
          << endl;

     int numsC[] = {-4};
     int numsD[] = {-12};
     list1 = buildList(numsC, 1);
     list2 = buildList(numsD, 1);
     cout << "Max Distance of two single lists '(-4) '(-12)" << endl
          << endl;
     cout << maxDistance(list1, list2) << endl
          << endl;

     int numsE[] = {3, 8, 12, 4, 2, 22, -4, 18};
     int numsF[] = {6, -4, 20, 6, 0, 22, 7, 3};
     list1 = buildList(numsE, 8);
     list2 = buildList(numsF, 8);
     cout << "Max Distance of two single lists '(3  8 12 4 2 22 -4 18) '(6 -4 20 6 0 22  7  3)" << endl
          << endl;
     cout << maxDistance(list1, list2) << endl
          << endl;

     int numsG[] = {3, 8, 12, 4, 2, 22, -4, 18};
     list1 = buildList(numsG, 8);
     cout << "Reverse of the list '(3  8 12 4 2 22 -4 18)'" << endl
          << endl;
     list2 = reverseList(list1);
     printList(list2);
     cout << endl;

     list1 = NULL;
     cout << "Reverse of the list '()'" << endl
          << endl;
     list2 = reverseList(list1);
     printList(list2);
     cout << endl;

     int numsH[] = {3, 8, 12, 3, 2};
     list1 = buildList(numsH, 5);
     cout << "Removing (3) from list: " << endl
          << endl;
     list1 = removeNum(list1, 3);
     printList(list1);
     cout << endl;
}
