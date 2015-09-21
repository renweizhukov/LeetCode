// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator
{
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator
{
    // This flag indicates whether the iterator has been advanced by peek().
    bool m_iteratorHasAdvancedByPeek;
    // m_nextVal caches the value returned by the first peek() call.
    int m_nextVal;

public:
    PeekingIterator(const vector<int>& nums) :
        Iterator(nums),
        m_iteratorHasAdvancedByPeek(false),
        m_nextVal(0)
    {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek()
    {
        // If this is the first time that peek() is called, so get the next value 
        // and advance the iterator by one; otherwise, don't advance the iterator 
        // and return the cached next value.
        if (!m_iteratorHasAdvancedByPeek)
        {
            m_nextVal = Iterator::next();
            m_iteratorHasAdvancedByPeek = true;
        }

        return m_nextVal;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next()
    {
        if (m_iteratorHasAdvancedByPeek)
        {
            // Since the iterator has been advanced by peek(), keep the iterator 
            // unchanged and return the cached next value.
            m_iteratorHasAdvancedByPeek = false;
            return m_nextVal;
        }
        else
        {
            // The iterator has not been advanced by peek(), so call Iterator::next()
            // to get the next value.
            return Iterator::next();
        }
    }

    bool hasNext() const
    {
        if (m_iteratorHasAdvancedByPeek)
        {
            // Since the iterator has been advanced by peek(), there must be a next 
            // value.
            return true;
        }
        else
        {
            return Iterator::hasNext();
        }
    }
};