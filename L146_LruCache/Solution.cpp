class LRUCache
{
private:
    struct Item
    {
        int key;
        int value;

        Item(int k, int v) :
            key(k),
            value(v)
        {
        }
    };

    // Maximum number of items that can be kept by the cache.
    int m_capacity;
    // List of items where the least recently used item is at 
    // the list head and the most recently used item is at the 
    // list tail.
    list<Item> m_items;
    // Key-to-List-Iterator map for fast retrieval of an item
    // based on its key.
    unordered_map<int, list<Item>::iterator> m_itemMap;

    // Once an item is used, it becomes the most recently used 
    // item and should be promoted to the list tail.
    void Promote(list<Item>::iterator& it)
    {
        // Append the item to the list tail.
        auto itNew = m_items.insert(m_items.end(), *it);

        // Erase the old item.
        m_items.erase(it);

        it = itNew;
    }

public:
    LRUCache(int capacity) :
        m_capacity(capacity)
    {

    }

    int get(int key)
    {
        auto itItemMap = m_itemMap.find(key);

        if (itItemMap == m_itemMap.end())
        {
            // The item with this key doesn't exist 
            // in the cache.
            return -1;
        }

        // Find the item with this key, so promote 
        // the item to the list tail. Note that 
        // itItemMap->second is updated with the 
        // new value.
        Promote(itItemMap->second);

        return itItemMap->second->value;
    }

    void set(int key, int value)
    {
        auto itItemMap = m_itemMap.find(key);

        if (itItemMap != m_itemMap.end())
        {
            // The item with this key exists in the 
            // cache, so promote the item to the list 
            // tail. Note that itItemMap->second is 
            // updated with the new value.
            Promote(itItemMap->second);

            // Set the value.
            itItemMap->second->value = value;
        }
        else
        {
            // Check whether the cache has used all 
            // its capacity.
            if (m_itemMap.size() >= m_capacity)
            {
                // Erase the least recently used item.
                m_itemMap.erase(m_items.front().key);
                m_items.pop_front();
            }

            // Insert the item into the list and the key-to-list-iterator 
            // pair into the map.
            m_itemMap.insert(make_pair(
                key, m_items.insert(m_items.end(), Item(key, value))));
        }
    }
};