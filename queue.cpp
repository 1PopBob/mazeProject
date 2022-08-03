#include "queue.h"

Queue::Queue(int maxlen)
{
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

Queue::~Queue()
{
  delete[] contents;
}

void Queue::add_to_back(Location loc)
{

  contents[tail] = loc;
  tail++;
}

Location Queue::remove_from_front()
{
    int temp = head;
    head++;
    return contents[temp];
}

bool Queue::is_empty()
{
   return head == tail;
}

