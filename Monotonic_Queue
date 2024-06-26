struct Monotonic_Queue{
        deque<int>q;
        int get_min(){
            return q.front();
        }
        void add(int x){
            while (!q.empty() && q.back() > x)
                q.pop_back();
            q.push_back(x);
        }
        void remove(int x){
            if (!q.empty() && q.front() == x)
                q.pop_front();
        }

    };
