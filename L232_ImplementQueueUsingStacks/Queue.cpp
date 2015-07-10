class Queue
{
    stack<int> m_st;

public:
    // Push element x to the back of queue.
    void push(int x)
    {
        // Empty m_st and use another stack to temporarily 
        // hold the elements in m_st.
        stack<int> tmpSt;
        while (!m_st.empty())
        {
            tmpSt.push(m_st.top());
            m_st.pop();
        }

        // Push the new element to the bottom of m_st.
        m_st.push(x);

        // Put back the old elements to m_st. Notice that 
        // the order of the old elements remains unchanged 
        // because they are reversed twice.
        while (!tmpSt.empty())
        {
            m_st.push(tmpSt.top());
            tmpSt.pop();
        }
    }

    // Removes the element from in front of queue.
    void pop(void)
    {
        m_st.pop();
    }

    // Get the front element.
    int peek(void)
    {
        return m_st.top();
    }

    // Return whether the queue is empty.
    bool empty(void)
    {
        return m_st.empty();
    }
};