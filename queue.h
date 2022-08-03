
#ifndef QUEUE_H
#define QUEUE_H

struct Location {
   int row;
   int col;
};

class Queue{
   public:
   Queue(int maxlen);

   ~Queue();

   void add_to_back(Location loc);

   Location remove_from_front();

   bool is_empty();

   private:
   Location* contents;
   int tail;
   int head;
};

#endif
